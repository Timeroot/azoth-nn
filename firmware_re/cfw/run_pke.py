#!/usr/bin/env python3
"""Positional k-gram Embedding (PKE) ablation + accuracy-per-flash-KB Pareto study.

PKE table E[k, V, D]: for EACH of the last k characters, an embedding depending on
BOTH the character AND its position offset (n*k*D params -- tiny, e.g. 72*7*16 = 8064
values). Combine the k looked-up vectors by SUM (-> D-dim) or CONCAT (-> k*D-dim).
Stored/accounted at fp16 (far-back positions learn small-magnitude vectors).

Integration variants (all evaluated on the SAME run_frontier held-out set, scored as
int8-GRU + fp16-PKE + f32-side deployed KB):
  standalone : PKE -> dense MLP -> softmax (no recurrent state).
  baseline   : STANDARD dense two-timescale GRU (no PKE) -- the "spend bytes on GRU" arm.
  mlp_head   : plain parallel MLP head on emb-window (no PKE positional table, no GRU) -- baseline.
  replace    : PKE vector feeds the fast GRU input each step instead of emb(last).
  addstate   : PKE (projected) ADDED to the GRU pre-output state [hf;hs].
  concat     : logits head from [GRU feat ; PKE vector].

Unified interface: every model maps x[B,L] (long) -> logits[B,L,V]; one WSD training
loop; per-row int8 fake-quant of all 2D weights + fp16 PKE for eval (matches the
deployed quant scheme and nn_common.count_bytes accounting). Rows checkpointed to
pke_results.csv immediately; driver is RESUMABLE (skips done (variant,config,seed)).

Usage:  python run_pke.py --phase {standalone,gru,confirm,all}  [--steps N] [--seeds ...]
Detached-friendly: prints flush=True progress; safe to nohup.
"""
import os, sys, csv, time, math, json, argparse
import numpy as np
import torch, torch.nn as nn, torch.nn.functional as F
import torch.utils.checkpoint as _ckpt
import nn_common as C
from run_frontier import load_data, build_eval

HERE = os.path.dirname(os.path.abspath(__file__))
DEV  = "cuda" if torch.cuda.is_available() else "cpu"
if DEV == "cuda":
    torch.backends.cuda.matmul.allow_tf32 = True
    torch.backends.cudnn.allow_tf32 = True
    torch.backends.cudnn.benchmark = True
V    = C.V
CSV  = os.path.join(HERE, "pke_results.csv")
FIELDS = ["variant","config","seed","kb","kb_int8","kb_pke","kb_f32","macc",
          "params","float_ppl","ppl","t1","t3","best_step","stop_reason",
          "mon_ppl","batch","seq","time_s"]

# ----------------------------------------------------------------- PKE window --
def pke_windows(pke_table, x, k, combine):
    """pke_table [k,V,D]; x [B,L] long -> per-position window vector.
    slot 0 = oldest (offset -(k-1)), slot k-1 = current char x[t] (incl). Left-pad
    the start of the stream with space (C.SP), matching the on-device buffer."""
    B, L = x.shape
    pad = x.new_full((B, k-1), C.SP)
    ext = torch.cat([pad, x], 1)                 # [B, k-1+L]
    vecs = [pke_table[j][ext[:, j:j+L]] for j in range(k)]   # each [B,L,D]
    stk = torch.stack(vecs, 2)                   # [B,L,k,D]
    if combine == "sum":
        return stk.sum(2)                        # [B,L,D]
    return stk.reshape(B, L, -1)                 # [B,L,k*D]


# --------------------------------------------------------------- models --------
class StandaloneMLP(nn.Module):
    """PKE (or plain emb-window) -> MLP -> V.  No recurrent state.
    If use_pke=False this is the plain 'k-gram-MLP head' baseline (one shared emb,
    no per-position table); accounted with a [V,D] emb (f32) instead of the PKE table."""
    def __init__(self, k, D, H, layers, combine, use_pke=True):
        super().__init__()
        self.k, self.D, self.combine, self.use_pke = k, D, combine, use_pke
        if use_pke:
            self.pke_table = nn.Parameter(0.02 * torch.randn(k, V, D))
        else:
            self.emb = nn.Embedding(V, D)
        inp = D if combine == "sum" else k*D
        mods = [nn.Linear(inp, H), nn.GELU()]
        for _ in range(layers-1):
            mods += [nn.Linear(H, H), nn.GELU()]
        mods += [nn.Linear(H, V)]
        self.mlp = nn.Sequential(*mods)

    def forward(self, x):                          # x [B,L]
        if self.use_pke:
            w = pke_windows(self.pke_table, x, self.k, self.combine)
        else:
            B, L = x.shape
            pad = x.new_full((B, self.k-1), C.SP); ext = torch.cat([pad, x], 1)
            vecs = [self.emb(ext[:, j:j+L]) for j in range(self.k)]
            stk = torch.stack(vecs, 2)
            w = stk.sum(2) if self.combine == "sum" else stk.reshape(B, L, -1)
        return self.mlp(w)


class TTGRU(nn.Module):
    """Two-timescale GRU (fast char GRU x FL layers + slow per-word GRUCell), output
    over [hf;hs;emb(last)] (input->output skip). Optional PKE integration:
      integ None      -> standard baseline GRU.
      integ 'replace' -> fast GRU input = PKE window vector (instead of emb).
      integ 'addstate'-> PKE (projected to HF+HS) added to [hf;hs] before the head.
      integ 'concat'  -> PKE window vector concatenated into the output-head input."""
    def __init__(self, HF, HS, E, FL=1, out_skip=True,
                 pke=None, integ=None, fmlp_hidden=None, target_nnz=16, l1coef=2e-4):
        super().__init__()
        self.HF, self.HS, self.E, self.FL, self.out_skip = HF, HS, E, FL, out_skip
        self.integ = integ; self.target_nnz = target_nnz; self.l1coef = l1coef
        self.emb = nn.Embedding(V, E)             # skip emb (and fast input unless replaced)
        if pke is not None:
            self.k, self.D, self.combine = pke
            self.pke_table = nn.Parameter(0.02 * torch.randn(self.k, V, self.D))
            self.pke_out = self.D if self.combine == "sum" else self.k*self.D
        # fast GRU input source
        if integ == "replace":          fast_in = self.pke_out      # raw PKE window
        else:                           fast_in = E                 # emb, or f(PKE)->E, or proj->E
        if integ == "replace_fmlp":     # PKE concat -> 2-layer MLP f -> E  (position-mixing)
            Hf = fmlp_hidden or self.pke_out
            self.fmap = nn.Sequential(nn.Linear(self.pke_out, Hf), nn.ReLU(),
                                      nn.Linear(Hf, E))
        if integ == "fmlp_res":         # RESIDUAL: GRU input = emb(last) + g(PKE concat),
            Hf = fmlp_hidden or self.pke_out          # g's final layer zero-init so
            self.gmap = nn.Sequential(nn.Linear(self.pke_out, Hf), nn.ReLU(),
                                      nn.Linear(Hf, E))# training STARTS at baseline and g
            nn.init.zeros_(self.gmap[-1].weight)      # can only ADD positional info ->
            nn.init.zeros_(self.gmap[-1].bias)        # guaranteed >= baseline, no recon burden
        if integ == "sparse_res":       # sparse high-dim table (STE top-nnz) -> residual g -> E
            Hf = fmlp_hidden or self.pke_out
            self.gmap = nn.Sequential(nn.Linear(self.pke_out, Hf), nn.ReLU(),
                                      nn.Linear(Hf, E))
            nn.init.zeros_(self.gmap[-1].weight); nn.init.zeros_(self.gmap[-1].bias)
            self.prune_active = False     # trainer flips this on to bake in the hard prune
        if integ == "sparse":           # high-dim sparse PKE (summed) -> proj -> E
            self.sparse_proj = nn.Linear(self.pke_out, E)
        self.fast = nn.GRU(fast_in, HF, num_layers=FL, batch_first=True)
        self.slow = nn.GRUCell(HF, HS)
        outin = HF + HS + (E if out_skip else 0)
        if integ == "addstate":
            self.pke_proj = nn.Linear(self.pke_out, HF + HS, bias=False)
        if integ == "concat":
            outin += self.pke_out
        self.out = nn.Linear(outin, V)

    def run_slow(self, hf_seq, bmask):
        B, L, _ = hf_seq.shape; H = self.HS; s = self.slow
        gi_all = torch.addmm(s.bias_ih, hf_seq.reshape(B*L, -1), s.weight_ih.t()).reshape(B, L, -1)
        Whh_t = s.weight_hh.t(); bhh = s.bias_hh
        hs = hf_seq.new_zeros(B, H); outs = []
        for t in range(L):
            gi = gi_all[:, t]; gh = torch.addmm(bhh, hs, Whh_t)
            r = torch.sigmoid(gi[:, :H] + gh[:, :H])
            z = torch.sigmoid(gi[:, H:2*H] + gh[:, H:2*H])
            n = torch.tanh(gi[:, 2*H:3*H] + r * gh[:, 2*H:3*H])
            cand = (1 - z) * n + z * hs
            m = bmask[:, t:t+1]; hs = m * cand + (1.0 - m) * hs
            outs.append(hs)
        return torch.stack(outs, 1)

    def forward(self, x):
        e = self.emb(x)                                    # [B,L,E]
        if self.integ == "replace":
            gin = pke_windows(self.pke_table, x, self.k, self.combine)
        elif self.integ == "replace_fmlp":
            gin = self.fmap(pke_windows(self.pke_table, x, self.k, self.combine))
        elif self.integ == "fmlp_res":
            gin = e + self.gmap(pke_windows(self.pke_table, x, self.k, self.combine))
        elif self.integ == "sparse_res":
            tbl = self._pruned_table() if self.prune_active else self.pke_table
            gin = e + self.gmap(pke_windows(tbl, x, self.k, self.combine))
        elif self.integ == "sparse":
            gin = self.sparse_proj(pke_windows(self.pke_table, x, self.k, self.combine))
        else:
            gin = e
        hf_seq, _ = self.fast(gin)
        bmask = (~((x < 26) | (x == C.CAPESC))).float()
        hs_seq = self.run_slow(hf_seq, bmask)
        feat = torch.cat([hf_seq, hs_seq], -1)             # [B,L,HF+HS]
        if self.integ == "addstate":
            pin = pke_windows(self.pke_table, x, self.k, self.combine)
            feat = feat + self.pke_proj(pin)
        of = torch.cat([feat, e], -1) if self.out_skip else feat
        if self.integ == "concat":
            pin = pke_windows(self.pke_table, x, self.k, self.combine)
            of = torch.cat([of, pin], -1)
        return self.out(of)

    # -- custom hooks (l1 for sparse; per-model quant + byte accounting) --------
    def _pruned_table(self):
        """straight-through top-`target_nnz` prune per (pos,char) entry: forward uses
        the pruned table, gradient flows to all coords (so training learns to
        concentrate mass into the kept coords -> deployed prune is lossless)."""
        p = self.pke_table; k, Vn, Dh = p.shape
        flat = p.reshape(k*Vn, Dh)
        m = min(self.target_nnz, Dh)
        thr = flat.abs().kthvalue(Dh - m + 1, dim=1, keepdim=True).values
        keep = (flat.abs() >= thr).to(flat.dtype)
        ste = flat + (flat*keep - flat).detach()
        return ste.reshape(k, Vn, Dh)

    def l1_penalty(self):
        if self.integ in ("sparse", "sparse_res"):
            return self.l1coef * self.pke_table.abs().mean()
        return next(self.parameters()).new_zeros(())

    def fq_apply_custom(self):
        """per-row int8 fake-quant of all 2D weights (not emb); PKE table stored
        fp16, except integ=='sparse' where each (pos,char) entry keeps only its
        top-`target_nnz` coords (a bitmask+values deployment) then fp16."""
        saved = _fq_weights(self)
        if not hasattr(self, "pke_table"):
            return saved
        p = self.pke_table; saved["pke_table"] = p.data.clone()
        if self.integ in ("sparse", "sparse_res"):
            k, Vn, Dh = p.shape; flat = p.data.reshape(k*Vn, Dh)
            m = min(self.target_nnz, Dh)
            thr = flat.abs().kthvalue(Dh - m + 1, dim=1, keepdim=True).values
            keep = flat.abs() >= thr
            flat = torch.where(keep, flat, torch.zeros_like(flat)).half().float()
            p.data = flat.reshape(k, Vn, Dh)
        else:
            p.data = p.data.half().float()
        return saved

    def deploy_bytes_custom(self):
        i8 = pke = f32 = 0
        for name, q in self.named_parameters():
            n = q.numel()
            if "pke_table" in name:
                if self.integ in ("sparse", "sparse_res"):
                    k, Vn, Dh = self.pke_table.shape
                    pke += k*Vn*((Dh + 7)//8) + k*Vn*min(self.target_nnz, Dh)*2
                else:
                    pke += n * 2
            elif "emb" in name:
                f32 += n * 4
            elif q.dim() == 2 and "weight" in name:
                i8 += n * 1 + q.shape[0] * 4
            else:
                f32 += n * 4
        return i8, pke, f32


class FuseFT(nn.Module):
    """Two-branch fusion for the training-curriculum experiment.
      GRU branch  -> pre-logit rep of dim d_B = HF+HS(+E)   (the [hf;hs;emb] vector)
      PKE branch  -> concat positional emb [k,V,D] -> MLP -> penultimate rep dim d_A
      fused head  -> Linear([GRU_rep ; PKE_rep], V)
    `gru_head`/`pke_head` are training-only (branch pretraining) and NOT deployed.
    forward(x, mode): 'gru' / 'pke' (branch pretrain) or 'fuse' (default, deployed)."""
    def __init__(self, HF, HS, E, FL, k, D, dA, pke_H=128, pke_L=1, out_skip=True):
        super().__init__()
        self.HF, self.HS, self.E, self.FL, self.out_skip = HF, HS, E, FL, out_skip
        self.emb = nn.Embedding(V, E)
        self.fast = nn.GRU(E, HF, num_layers=FL, batch_first=True)
        self.slow = nn.GRUCell(HF, HS)
        self.d_B = HF + HS + (E if out_skip else 0)
        self.k, self.D, self.combine = k, D, "concat"
        self.pke_table = nn.Parameter(0.02 * torch.randn(k, V, D))
        mods = [nn.Linear(k*D, pke_H), nn.GELU()]
        for _ in range(pke_L-1): mods += [nn.Linear(pke_H, pke_H), nn.GELU()]
        mods += [nn.Linear(pke_H, dA)]
        self.pke_mlp = nn.Sequential(*mods); self.dA = dA
        self.gru_head = nn.Linear(self.d_B, V)     # training-only
        self.pke_head = nn.Linear(dA, V)           # training-only
        self.fuse = nn.Linear(self.d_B + dA, V)    # deployed logit layer
        self.head = None                           # optional post-merge block (rank1 study)

    def gru_rep(self, x):
        e = self.emb(x); hf_seq, _ = self.fast(e)
        B, L, _ = hf_seq.shape; H = self.HS; s = self.slow
        gi = torch.addmm(s.bias_ih, hf_seq.reshape(B*L, -1), s.weight_ih.t()).reshape(B, L, -1)
        Wt = s.weight_hh.t(); bh = s.bias_hh
        bmask = (~((x < 26) | (x == C.CAPESC))).float()
        hs = hf_seq.new_zeros(B, H); outs = []
        for t in range(L):
            g = gi[:, t]; gh = torch.addmm(bh, hs, Wt)
            r = torch.sigmoid(g[:, :H] + gh[:, :H]); z = torch.sigmoid(g[:, H:2*H] + gh[:, H:2*H])
            n = torch.tanh(g[:, 2*H:3*H] + r*gh[:, 2*H:3*H])
            hs = bmask[:, t:t+1]*((1-z)*n + z*hs) + (1-bmask[:, t:t+1])*hs
            outs.append(hs)
        hs_seq = torch.stack(outs, 1)
        feat = torch.cat([hf_seq, hs_seq], -1)
        return torch.cat([feat, e], -1) if self.out_skip else feat

    def pke_rep(self, x):
        return self.pke_mlp(pke_windows(self.pke_table, x, self.k, self.combine))

    def forward(self, x, mode="fuse"):
        if mode == "gru": return self.gru_head(self.gru_rep(x))
        if mode == "pke": return self.pke_head(self.pke_rep(x))
        m = torch.cat([self.gru_rep(x), self.pke_rep(x)], -1)
        if self.head is not None: m = self.head(m)
        return self.fuse(m)

    def deploy_bytes_custom(self):
        i8 = pke = f32 = 0
        for name, q in self.named_parameters():
            if "gru_head" in name or "pke_head" in name:
                continue                                    # training-only, not deployed
            n = q.numel()
            if "pke_table" in name:            pke += n * 2
            elif "emb" in name:                f32 += n * 4
            elif q.dim() == 2 and "weight" in name: i8 += n * 1 + q.shape[0] * 4
            else:                              f32 += n * 4
        return i8, pke, f32


# ------------------------------------------------------ deploy-byte accounting -
def deploy_bytes(model):
    """int8 per-row for every 2D 'weight' (numel + rows*4 f32 scale); fp16 for the
    PKE table; f32 for emb + biases + 1D params. Mirrors the deployed quant scheme
    and (for a bare TTGRU) equals nn_common.count_bytes."""
    if hasattr(model, "deploy_bytes_custom"):
        return model.deploy_bytes_custom()
    i8 = pke = f32 = 0
    for name, p in model.named_parameters():
        n = p.numel()
        if "pke_table" in name:
            pke += n * 2
        elif "emb" in name:
            f32 += n * 4
        elif p.dim() == 2 and "weight" in name:
            i8 += n * 1 + p.shape[0] * 4
        else:
            f32 += n * 4
    return i8, pke, f32

def macc_estimate(model):
    tot = 0
    for name, p in model.named_parameters():
        if p.dim() == 2 and "weight" in name:
            tot += p.numel()                      # ~1 MAC / weight / step (upper-ish)
    return tot


# --------------------------------------------------------- fake-quant for eval -
def _fq_weights(model):
    """per-row int8 fake-quant of all 2D 'weight' params except emb/pke_table."""
    saved = {}
    for name, p in model.named_parameters():
        if "pke_table" in name or "emb" in name:
            continue
        if p.dim() == 2 and "weight" in name:
            saved[name] = p.data.clone()
            amax = p.data.abs().amax(1, keepdim=True).clamp_min(1e-8); s = amax/127
            p.data = torch.round(p.data / s).clamp(-127, 127) * s
    return saved

def fq_apply(model):
    if hasattr(model, "fq_apply_custom"):
        return model.fq_apply_custom()
    saved = _fq_weights(model)
    for name, p in model.named_parameters():
        if "pke_table" in name:
            saved[name] = p.data.clone(); p.data = p.data.half().float()
    return saved

def fq_restore(model, saved):
    for name, p in model.named_parameters():
        if name in saved:
            p.data = saved[name]

def metrics(prob, tgt):
    eps = 1e-12
    nll = -np.log(prob[np.arange(len(tgt)), tgt] + eps).mean()
    order = np.argsort(-prob, 1)[:, :3]
    return float(np.exp(nll)), float((order[:,0]==tgt).mean()), float((order==tgt[:,None]).any(1).mean())

@torch.no_grad()
def evaluate(model, seqs, tgt, quant=True):
    model.eval()
    saved = fq_apply(model) if quant else {}
    x = torch.tensor(seqs, dtype=torch.long, device=DEV)
    # chunk over sequences to bound memory
    outs = []
    for i in range(0, x.shape[0], 50):
        outs.append(model(x[i:i+50]).float().reshape(-1, V).cpu().numpy())
    logits = np.concatenate(outs, 0)
    if quant: fq_restore(model, saved)
    m = logits.max(1, keepdims=True); pr = np.exp(logits - m); pr /= pr.sum(1, keepdims=True)
    return metrics(pr, tgt)


# --------------------------------------------------------------- training ------
# EDGE-INFERENCE methodology: training compute is free; every point is trained to
# CONVERGENCE. WSD schedule = warmup -> LONG constant high-LR plateau -> short cosine
# decay, where the decay is TRIGGERED by a held-out plateau (generous patience) rather
# than a fixed horizon, so no point is undertrained. Best checkpoint (over the whole
# run incl. decay) is kept. The monitor signal is a fixed random held-out slice,
# DISJOINT from the fixed run_frontier scoring set, to limit test-set selection bias.
def make_batcher(data, L, B):
    dt = torch.tensor(data, dtype=torch.long); N = len(data)
    def batch():
        idx = torch.randint(0, N - L - 2, (B,))
        seq = torch.stack([dt[i:i+L+1] for i in idx])
        return seq[:, :L].to(DEV), seq[:, 1:L+1].to(DEV)
    return batch

_MON_GEN = torch.Generator().manual_seed(20260910)
def _mon_windows(va_t, B=160, S=160):
    N = va_t.shape[0]
    idx = torch.randint(0, N - S - 1, (B,), generator=_MON_GEN)
    x = torch.stack([va_t[i:i+S]     for i in idx]).to(DEV)
    y = torch.stack([va_t[i+1:i+S+1] for i in idx]).to(DEV)
    return x, y

@torch.no_grad()
def eval_mon(net, mon_x, mon_y):
    net.eval()
    lg = net(mon_x).reshape(-1, V)
    return float(torch.exp(F.cross_entropy(lg, mon_y.reshape(-1))))

def train_model(build_fn, tr, va_np, seed, tag="", lr0=2.5e-3, lr_min=2e-5,
                B=512, L=96, warm=800, eval_every=1000, patience=8,
                decay_steps=5000, max_steps=90000, improve=2e-3,
                sparse=False, l1_max=3e-3, anneal_end=20000, prune_at=25000):
    torch.manual_seed(seed); np.random.seed(seed)
    net = build_fn().to(DEV)
    is_sparse = sparse and hasattr(net, "prune_active")
    opt = torch.optim.Adam(net.parameters(), lr=lr0)
    ce = nn.CrossEntropyLoss(); batch = make_batcher(tr, L, B)
    va_t = torch.tensor(va_np, dtype=torch.long)
    mon_x, mon_y = _mon_windows(va_t)
    t0 = time.time()
    best = {"ppl": 1e9, "step": -1}; best_sd = None; since = 0
    phase = "plateau"; decay_start = None; step = 0
    while step < max_steps:
        if step < warm:                     lr = lr_min + (lr0-lr_min)*step/warm
        elif phase == "plateau":            lr = lr0
        else:
            p = (step - decay_start)/decay_steps
            lr = lr_min + 0.5*(lr0-lr_min)*(1 + math.cos(math.pi*min(p, 1.0)))
        for g in opt.param_groups: g["lr"] = lr
        if is_sparse:                       # HARD L1 anneal + bake-in STE prune
            net.l1coef = l1_max * min(1.0, step / max(1.0, anneal_end))
            if step == prune_at and not net.prune_active:
                net.prune_active = True
                print(f"    [{tag}] -> PRUNE baked in (STE top-{net.target_nnz}) at {step}",
                      flush=True)
        net.train()
        x, y = batch()
        loss = ce(net(x).reshape(-1, V), y.reshape(-1))
        if hasattr(net, "l1_penalty"): loss = loss + net.l1_penalty()
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(net.parameters(), 1.0); opt.step()
        step += 1
        if step % eval_every == 0:
            if is_sparse:                   # ALWAYS monitor the PRUNED (deployed) model
                was = net.prune_active; net.prune_active = True
                mppl = eval_mon(net, mon_x, mon_y); net.prune_active = was
                with torch.no_grad():
                    pf = net.pke_table.reshape(-1, net.pke_table.shape[-1]).abs()
                    tkm = torch.topk(pf, min(net.target_nnz, pf.shape[1]), 1).values.sum(1)
                    conc = float((tkm/(pf.sum(1)+1e-9)).mean())
                print(f"    [{tag}] conc(top{net.target_nnz})={conc:.3f} l1c={net.l1coef:.1e}",
                      flush=True)
            else:
                mppl = eval_mon(net, mon_x, mon_y)
            if mppl < best["ppl"] - improve:
                best = {"ppl": mppl, "step": step}
                best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
                since = 0
            else:
                since += 1
            print(f"    [{tag}] step {step} lr {lr:.2e} {phase} mon {mppl:.3f} "
                  f"best {best['ppl']:.3f}@{best['step']} since {since} ({time.time()-t0:.0f}s)",
                  flush=True)
            if phase == "plateau" and since >= patience:
                phase = "decay"; decay_start = step
                print(f"    [{tag}] -> DECAY triggered at step {step}", flush=True)
            if phase == "decay" and step >= decay_start + decay_steps:
                break
    stop_reason = "decayed" if phase == "decay" else "cap"
    if best_sd is not None:
        net.load_state_dict({k: v.to(DEV) for k, v in best_sd.items()})
    return net, dict(best_step=best["step"], mon_ppl=round(best["ppl"], 3),
                     stop_reason=stop_reason, time_s=round(time.time()-t0, 1))


# ------------------------------------------------- generic WSD trainer (fuse) --
def _wsd_train(net, fwd, params, tr, va_t, mon_x, mon_y, tag, seed,
               lr0=2.5e-3, lr_min=2e-5, B=512, L=96, warm=800, eval_every=1000,
               patience=8, decay_steps=5000, max_steps=90000, improve=2e-3, clip=1.0):
    """Train `params` (others frozen) with WSD plateau->triggered-decay + best
    checkpoint, using forward `fwd(net,x)->logits`. Restores best net state."""
    torch.manual_seed(seed); params = [p for p in params]
    opt = torch.optim.Adam(params, lr=lr0); ce = nn.CrossEntropyLoss()
    batch = make_batcher(tr, L, B); t0 = time.time()
    best = {"ppl": 1e9, "step": -1}; best_sd = None; since = 0
    phase = "plateau"; ds = None; step = 0
    while step < max_steps:
        if step < warm:          lr = lr_min + (lr0-lr_min)*step/warm
        elif phase == "plateau": lr = lr0
        else:
            p = (step-ds)/decay_steps; lr = lr_min + 0.5*(lr0-lr_min)*(1+math.cos(math.pi*min(p,1.0)))
        for g in opt.param_groups: g["lr"] = lr
        net.train(); x, y = batch()
        loss = ce(fwd(net, x).reshape(-1, V), y.reshape(-1))
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(params, clip); opt.step(); step += 1
        if step % eval_every == 0:
            net.eval()
            with torch.no_grad():
                lg = fwd(net, mon_x).reshape(-1, V)
                mppl = float(torch.exp(F.cross_entropy(lg, mon_y.reshape(-1))))
            if mppl < best["ppl"] - improve:
                best = {"ppl": mppl, "step": step}
                best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}; since = 0
            else: since += 1
            print(f"    [{tag}] step {step} {phase} mon {mppl:.3f} best {best['ppl']:.3f}@{best['step']} "
                  f"since {since} ({time.time()-t0:.0f}s)", flush=True)
            if phase == "plateau" and since >= patience: phase = "decay"; ds = step
            if phase == "decay" and step >= ds + decay_steps: break
    if best_sd is not None: net.load_state_dict({k: v.to(DEV) for k, v in best_sd.items()})
    return dict(best_step=best["step"], mon_ppl=round(best["ppl"], 3),
                stop_reason=("decayed" if phase == "decay" else "cap"))

def fuse_run(cfg_name, c, tr, va, seqs, tgt, seed, tk):
    """3-stage fusion curriculum: (0) pretrain GRU + PKE branches to convergence
    (cached per size/branch, reused across fuse seeds); (A) freeze both branches,
    train ONLY the fused logit layer -> control; (B) unfreeze all, joint finetune."""
    va_t = torch.tensor(va, dtype=torch.long); mon_x, mon_y = _mon_windows(va_t)
    torch.manual_seed(1000+seed)
    net = FuseFT(c["HF"],c["HS"],c["E"],c["FL"],c["k"],c["D"],c["dA"],c["pke_H"],c["pke_L"]).to(DEV)
    gc = os.path.join(HERE, f"_fusecache_gru_{c['HF']}_{c['HS']}_{c['E']}_{c['FL']}.pt")
    pc = os.path.join(HERE, f"_fusecache_pke_{c['k']}_{c['D']}_{c['dA']}_{c['pke_H']}_{c['pke_L']}.pt")
    if os.path.exists(gc):
        sd = torch.load(gc)
        for m in ("emb","fast","slow","gru_head"): getattr(net, m).load_state_dict(sd[m])
        print(f"  [fuse] loaded GRU-branch cache {os.path.basename(gc)}", flush=True)
    else:
        pr = list(net.emb.parameters())+list(net.fast.parameters())+list(net.slow.parameters())+list(net.gru_head.parameters())
        m = _wsd_train(net, lambda n,x:n(x,"gru"), pr, tr,va_t,mon_x,mon_y, f"{cfg_name}:preGRU", 0, **tk)
        torch.save({k:getattr(net,k).state_dict() for k in ("emb","fast","slow","gru_head")}, gc)
        print(f"  [fuse] GRU-branch pretrained {m}", flush=True)
    if os.path.exists(pc):
        sd = torch.load(pc); net.pke_table.data = sd["pke_table"].to(DEV)
        net.pke_mlp.load_state_dict(sd["pke_mlp"]); net.pke_head.load_state_dict(sd["pke_head"])
        print(f"  [fuse] loaded PKE-branch cache {os.path.basename(pc)}", flush=True)
    else:
        pr = [net.pke_table]+list(net.pke_mlp.parameters())+list(net.pke_head.parameters())
        m = _wsd_train(net, lambda n,x:n(x,"pke"), pr, tr,va_t,mon_x,mon_y, f"{cfg_name}:prePKE", 0, **tk)
        torch.save({"pke_table":net.pke_table.detach().cpu(),"pke_mlp":net.pke_mlp.state_dict(),
                    "pke_head":net.pke_head.state_dict()}, pc)
        print(f"  [fuse] PKE-branch pretrained {m}", flush=True)
    # Stage A: freeze both branches, train ONLY the fused head
    for p in net.parameters(): p.requires_grad = False
    for p in net.fuse.parameters(): p.requires_grad = True
    mA = _wsd_train(net, lambda n,x:n(x,"fuse"), net.fuse.parameters(), tr,va_t,mon_x,mon_y, f"{cfg_name}:A", seed, **tk)
    fA,_,_ = evaluate(net, seqs, tgt, quant=False); qA,tA1,tA3 = evaluate(net, seqs, tgt, quant=True)
    # Stage B: unfreeze all (except training-only heads), joint finetune
    for p in net.parameters(): p.requires_grad = True
    allp = [p for n_,p in net.named_parameters() if "gru_head" not in n_ and "pke_head" not in n_]
    mB = _wsd_train(net, lambda n,x:n(x,"fuse"), allp, tr,va_t,mon_x,mon_y, f"{cfg_name}:B", seed, **tk)
    fB,_,_ = evaluate(net, seqs, tgt, quant=False); qB,tB1,tB3 = evaluate(net, seqs, tgt, quant=True)
    return net, dict(A=(fA,qA,tA1,tA3,mA), B=(fB,qB,tB1,tB3,mB))

def fuse_cfgs():
    base = dict(FL=1, k=7, D=16, dA=48, pke_H=128, pke_L=1)
    return [("fuse_s170_k7D16", dict(base, HF=152, HS=64, E=48)),
            ("fuse_s360_k7D16", dict(base, HF=272, HS=96, E=64))]


# ------------------------------------------------- grokking / very-long train --
# Probe the very-long-training regime: converge normally, then a BIG warm restart
# (LR spiked back to ~peak) with a slow cosine decay over 8x the convergence steps.
# Does extended training keep improving (grok) or return to plateau? Does the
# fmlp_res vs fuse_ft gap change? Full held-out ppl-vs-step trajectory logged.
# fmlp_res sized to match the fuse s170 (~213KB) for a direct comparison.
GROK_FMLP = lambda: TTGRU(152, 64, 48, 1, pke=(7,16,"concat"), integ="fmlp_res", fmlp_hidden=150)

def _grok_lr(step, total, peak, lr_min=2e-5, warm=300):
    if step < warm: return lr_min + (peak-lr_min)*step/warm
    p = (step-warm)/max(1.0, total-warm)
    return lr_min + 0.5*(peak-lr_min)*(1+math.cos(math.pi*min(p, 1.0)))

def _grok_lr_hot(step, peak=2.6e-3, hold=2.3e-3, warm=300, taper_over=200000):
    """HELD-HIGH schedule (extendability probe): warmup -> peak -> mild taper to `hold`
    -> constant `hold`. Independent of horizon, so relaunching continues at LR=hold
    (stays 'hot', no re-anneal needed)."""
    if step < warm: return 2e-5 + (peak-2e-5)*step/warm
    if step < warm + taper_over:
        return peak + (hold-peak)*(step-warm)/taper_over
    return hold

def grok_extend(which, net, fwd, params, tr, va_t, mon_x, mon_y, N, conv_mon, ext_steps,
                peak=2.6e-3, lr_min=2e-5, eval_every=2000, ckpt_every=20000, B=512, L=96,
                hot=False):
    """Warm-restart continue-train for ext_steps; resumable via disk ckpt; logs the
    held-out(mon) trajectory (global step = N + ext step). Keeps best checkpoint.
    hot=True uses the HELD-HIGH LR schedule (no anneal-to-zero) so relaunching with a
    larger ext_steps simply CONTINUES at high LR."""
    ckpt = os.path.join(HERE, f"_grok_ckpt_{which}.pt")
    opt = torch.optim.Adam(params, lr=peak); ce = nn.CrossEntropyLoss()
    batch = make_batcher(tr, L, B)
    traj = [{"gstep": N, "mon_ppl": round(conv_mon, 4), "phase": "converged"}]
    best = {"ppl": conv_mon, "gstep": N}
    best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
    step = 0
    if os.path.exists(ckpt):
        d = torch.load(ckpt)
        net.load_state_dict({k: v.to(DEV) for k, v in d["sd"].items()})
        opt.load_state_dict(d["opt"]); step = d["step"]; traj = d["traj"]
        best = d["best"]; best_sd = d["best_sd"]; N = d.get("N", N)
        print(f"    [grok_{which}] RESUMED ext step {step}/{ext_steps} (N={N})", flush=True)
    t0 = time.time()
    while step < ext_steps:
        lr_now = _grok_lr_hot(step, peak) if hot else _grok_lr(step, ext_steps, peak, lr_min)
        for g in opt.param_groups: g["lr"] = lr_now
        net.train(); x, y = batch()
        loss = ce(fwd(net, x).reshape(-1, V), y.reshape(-1))
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(params, 1.0); opt.step(); step += 1
        if step % eval_every == 0:
            net.eval()
            with torch.no_grad():
                mppl = float(torch.exp(F.cross_entropy(fwd(net, mon_x).reshape(-1, V), mon_y.reshape(-1))))
            lr = opt.param_groups[0]["lr"]
            traj.append({"gstep": N+step, "mon_ppl": round(mppl, 4), "phase": "ext", "lr": lr})
            if mppl < best["ppl"] - 1e-4:
                best = {"ppl": mppl, "gstep": N+step}
                best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
            print(f"    [grok_{which}] ext {step}/{ext_steps} gstep {N+step} lr {lr:.2e} "
                  f"mon {mppl:.4f} best {best['ppl']:.4f}@{best['gstep']} ({time.time()-t0:.0f}s)", flush=True)
        if step % ckpt_every == 0:
            torch.save({"sd": {k: v.cpu() for k, v in net.state_dict().items()},
                        "opt": opt.state_dict(), "step": step, "traj": traj,
                        "best": best, "best_sd": best_sd, "N": N}, ckpt)
    net.load_state_dict({k: v.to(DEV) for k, v in best_sd.items()})
    return traj, best

def grok_readout(which, tr, va, seqs, tgt, anneal_steps=8000, peak=2.3e-3, lr_min=2e-5):
    """NON-DESTRUCTIVE annealed readout: load the CURRENT hot checkpoint's weights into a
    fresh model, run a SHORT cosine anneal on that copy, evaluate int8 fixed-eval ppl, and
    append the result to grok_{which}_readouts.csv. The hot ckpt on disk is NEVER written,
    so the main hot run stays intact and continuable."""
    va_t = torch.tensor(va, dtype=torch.long); mon_x, mon_y = _mon_windows(va_t)
    ckpt = os.path.join(HERE, f"_grok_ckpt_{which}.pt")
    d = torch.load(ckpt); ext_step = d["step"]
    HF, HS, E = (272, 96, 64) if which == "fuse_s360" else (152, 64, 48)
    c = dict(FL=1, k=7, D=16, dA=48, pke_H=128, pke_L=1, HF=HF, HS=HS, E=E)
    net = FuseFT(**c).to(DEV)
    net.load_state_dict({k: v.to(DEV) for k, v in d["sd"].items()})   # current HOT weights
    fwd = lambda n, x: n(x, "fuse")
    params = [p for n_, p in net.named_parameters() if "gru_head" not in n_ and "pke_head" not in n_]
    opt = torch.optim.Adam(params, lr=peak); ce = nn.CrossEntropyLoss()
    batch = make_batcher(tr, 96, 512); best = {"ppl": 1e9}; best_sd = None
    print(f"[grok_readout {which}] annealing a COPY of ext-{ext_step} hot ckpt "
          f"({anneal_steps} steps, {peak:.1e}->{lr_min:.0e})", flush=True)
    for step in range(anneal_steps):
        lr = lr_min + 0.5*(peak-lr_min)*(1+math.cos(math.pi*step/anneal_steps))
        for g in opt.param_groups: g["lr"] = lr
        net.train(); x, y = batch()
        loss = ce(fwd(net, x).reshape(-1, V), y.reshape(-1))
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(params, 1.0); opt.step()
        if step % 1000 == 0 or step == anneal_steps-1:
            net.eval()
            with torch.no_grad():
                mppl = float(torch.exp(F.cross_entropy(fwd(net, mon_x).reshape(-1, V), mon_y.reshape(-1))))
            if mppl < best["ppl"]:
                best = {"ppl": mppl, "step": step}
                best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
    net.load_state_dict({k: v.to(DEV) for k, v in best_sd.items()})
    q = evaluate(net, seqs, tgt, quant=True)
    ref = 3.354
    path = os.path.join(HERE, f"grok_{which}_readouts.csv")
    ex = os.path.exists(path) and os.path.getsize(path) > 0
    with open(path, "a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["ext_step","anneal_int8_ppl","t1","t3","delta_vs_ref","ref"])
        if not ex: w.writeheader()
        w.writerow(dict(ext_step=ext_step, anneal_int8_ppl=round(q[0],4), t1=round(q[1],4),
                        t3=round(q[2],4), delta_vs_ref=round(q[0]-ref,4), ref=ref))
    print(f"[grok_readout {which}] ext-{ext_step}: annealed int8 ppl {q[0]:.4f} "
          f"(t1 {q[1]:.3f}) delta vs {ref} = {q[0]-ref:+.4f}  -> grok_{which}_readouts.csv "
          f"(hot ckpt untouched)", flush=True)

def grok_run(which, tr, va, seqs, tgt, ext_steps_override=0, cont=False):
    va_t = torch.tensor(va, dtype=torch.long); mon_x, mon_y = _mon_windows(va_t)
    conv_tk = dict(patience=8, eval_every=1000, decay_steps=5000, max_steps=90000)
    hot = (which == "fuse_s360")                   # large-size probe: held-high LR
    ckpt = os.path.join(HERE, f"_grok_ckpt_{which}.pt")
    if which == "fmlp":
        net, m = train_model(GROK_FMLP, tr, va, seed=0, tag="grok_fmlp_conv", **conv_tk)
        N = m["best_step"]; conv_mon = m["mon_ppl"]
        fwd = lambda n, x: n(x); params = list(net.parameters())
    else:  # fuse s170 or s360 (reuses cached branch pretrains from the fuse phase)
        HF, HS, E = (272, 96, 64) if which == "fuse_s360" else (152, 64, 48)
        c = dict(FL=1, k=7, D=16, dA=48, pke_H=128, pke_L=1, HF=HF, HS=HS, E=E)
        if cont and os.path.exists(ckpt):          # CONTINUE: skip re-convergence, load ext ckpt
            net = FuseFT(**c).to(DEV); N = 0; conv_mon = 1e9
            print(f"[grok_{which}] CONTINUE from {os.path.basename(ckpt)} (skip convergence)", flush=True)
        else:
            net, r = fuse_run(f"grok_{which}_conv", c, tr, va, seqs, tgt, 0, conv_tk)
            N = r["B"][4]["best_step"]; conv_mon = r["B"][4]["mon_ppl"]
        fwd = lambda n, x: n(x, "fuse")
        params = [p for n_, p in net.named_parameters() if "gru_head" not in n_ and "pke_head" not in n_]
    conv = None if cont else evaluate(net, seqs, tgt, quant=True)
    ext_steps = ext_steps_override or min(8*max(N, 1), 480000)   # honor 8x (override to continue)
    cs = f"{conv[0]:.4f}" if conv else "n/a(continue)"
    print(f"[grok_{which}] N={N} conv_int8_ppl={cs} extending to {ext_steps} steps "
          f"({'HELD-HIGH LR' if hot else 'cosine'} peak 2.6e-3)", flush=True)
    traj, best = grok_extend(which, net, fwd, params, tr, va_t, mon_x, mon_y, N,
                             conv_mon if not cont else 1e9, ext_steps, hot=hot)
    ext = evaluate(net, seqs, tgt, quant=True)
    i8, pke, f32 = deploy_bytes(net); kb = (i8+pke+f32)/1024.0
    json.dump(dict(which=which, N=N, ext_steps=ext_steps, kb=round(kb,1),
                   conv_int8_ppl=(round(conv[0],4) if conv else None),
                   conv_int8_t1=(round(conv[1],4) if conv else None),
                   ext_int8_ppl=round(ext[0],4), ext_int8_t1=round(ext[1],4),
                   best_mon=best, trajectory=traj),
              open(os.path.join(HERE, f"grok_{which}_traj.json"), "w"), indent=1)
    append_row(dict(variant="grok", config=f"grok_{which}_ext", seed=0, kb=round(kb,1),
        kb_int8=round(i8/1024,1), kb_pke=round(pke/1024,2), kb_f32=round(f32/1024,1),
        macc=macc_estimate(net), params=sum(p.numel() for p in net.parameters()),
        float_ppl=0.0, ppl=round(ext[0],3), t1=round(ext[1],4), t3=round(ext[2],4),
        best_step=best["gstep"], stop_reason="grok_ext", mon_ppl=round(best["ppl"],3),
        batch=512, seq=96, time_s=0))
    dstr = f"(delta {ext[0]-conv[0]:+.4f}) " if conv else ""
    print(f"[grok_{which}] DONE: converged int8 {cs} -> extended int8 {ext[0]:.4f} "
          f"{dstr}best_mon {best['ppl']:.4f}@gstep{best['gstep']} "
          f"-> grok_{which}_traj.json", flush=True)


# ------------------------------------ rank-1 head study (on the best fuse_s360) --
class HeadBlock(nn.Module):
    """Post-merge residual block on the d-dim merged vector, matched params (2dh+h)
    and MACs (2dh) between the two variants (from run_rank1.py). Uses nn.Linear so
    weights are named '.weight' -> counted int8 per-row and fake-quantized like every
    other deployed matrix (identical deployment cost for std and rank1):
      std  (parallel): x = x + lin2(relu(lin1(x)))          (all h units see the same x)
      rank1 (serial):  for i: s=relu(x.W1[i]+b1[i]); x=x + s*W2[:,i]   (serial depth-h)"""
    def __init__(self, d, h, variant):
        super().__init__(); self.d, self.h, self.variant = d, h, variant
        self.lin1 = nn.Linear(d, h)                    # W1[h,d] (=B), b1[h]
        self.lin2 = nn.Linear(h, d, bias=False)        # W2[d,h] (=A^T)
        with torch.no_grad(): self.lin2.weight.mul_(0.05)
    def forward(self, x):
        if self.variant == "std":
            return x + self.lin2(torch.relu(self.lin1(x)))
        if self.training:                              # checkpoint: recompute the deep serial
            if not x.requires_grad: x = x.requires_grad_(True)   # frozen branches (Phase 1)
            return _ckpt.checkpoint(self._rank1, x, use_reentrant=False)  # graph -> O(1) mem
        return self._rank1(x)
    def _rank1(self, x):
        W1, b1, W2 = self.lin1.weight, self.lin1.bias, self.lin2.weight
        for i in range(self.h):                        # unrolled rank-1 residual (serial)
            s = torch.relu(x @ W1[i] + b1[i])
            x = x + s.unsqueeze(-1) * W2[:, i]
        return x

_FS360 = dict(FL=1, k=7, D=16, dA=48, pke_H=128, pke_L=1, HF=272, HS=96, E=64)
_FS_ANNEAL = os.path.join(HERE, "_fuse_s360_annealed.pt")

def _anneal_and_save_fs360(tr, va, seqs, tgt, anneal_steps=8000, peak=2.3e-3, lr_min=2e-5):
    """Anneal the ext-140k hot ckpt to convergence and SAVE it (the 3.314 basin) so the
    rank-1-head study can freeze real annealed branches."""
    va_t = torch.tensor(va, dtype=torch.long); mon_x, mon_y = _mon_windows(va_t)
    d = torch.load(os.path.join(HERE, "_grok_ckpt_fuse_s360.pt"), map_location="cpu")
    net = FuseFT(**_FS360).to(DEV); net.load_state_dict({k: v.to(DEV) for k, v in d["sd"].items()})
    fwd = lambda n, x: n(x, "fuse")
    params = [p for n_, p in net.named_parameters() if "gru_head" not in n_ and "pke_head" not in n_]
    opt = torch.optim.Adam(params, lr=peak); ce = nn.CrossEntropyLoss(); batch = make_batcher(tr, 96, 512)
    best = {"ppl": 1e9}; best_sd = None
    print(f"[fs360-anneal] annealing ext-{d['step']} hot ckpt {anneal_steps} steps", flush=True)
    for step in range(anneal_steps):
        for g in opt.param_groups: g["lr"] = lr_min + 0.5*(peak-lr_min)*(1+math.cos(math.pi*step/anneal_steps))
        net.train(); x, y = batch(); loss = ce(fwd(net, x).reshape(-1, V), y.reshape(-1))
        opt.zero_grad(); loss.backward(); nn.utils.clip_grad_norm_(params, 1.0); opt.step()
        if step % 1000 == 0 or step == anneal_steps-1:
            net.eval()
            with torch.no_grad():
                mppl = float(torch.exp(F.cross_entropy(fwd(net, mon_x).reshape(-1, V), mon_y.reshape(-1))))
            if mppl < best["ppl"]:
                best = {"ppl": mppl, "step": step}
                best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
    net.load_state_dict({k: v.to(DEV) for k, v in best_sd.items()})
    q = evaluate(net, seqs, tgt, quant=True)
    torch.save({"sd": {k: v.cpu() for k, v in net.state_dict().items()}, "int8_ppl": q[0]}, _FS_ANNEAL)
    print(f"[fs360-anneal] saved {os.path.basename(_FS_ANNEAL)} int8 {q[0]:.4f} (ref 3.314)", flush=True)
    return q[0]

def rank1head_run(variant, phase, tr, va, seqs, tgt, h=36, steps=144000, B=160, lr0=2.5e-3,
                  warm=800, clip=1.0):
    """variant std|rank1 ; phase p1 (freeze branches, train head) | p2 (joint FT).
    Resumable per (variant,phase) via _r1_ckpt_{variant}_{phase}.pt."""
    va_t = torch.tensor(va, dtype=torch.long); mon_x, mon_y = _mon_windows(va_t)
    d = torch.load(_FS_ANNEAL, map_location="cpu")
    net = FuseFT(**_FS360).to(DEV); net.load_state_dict({k: v.to(DEV) for k, v in d["sd"].items()})
    dmerge = net.d_B + net.dA
    net.head = HeadBlock(dmerge, h, variant).to(DEV)
    prev = os.path.join(HERE, f"_r1_ckpt_{variant}_p1.pt")
    if phase == "p2" and os.path.exists(prev):        # start p2 from p1's trained head
        net.load_state_dict({k: v.to(DEV) for k, v in torch.load(prev, map_location="cpu")["sd"].items()})
    branch = ("emb.", "fast.", "slow.", "pke_table", "pke_mlp.")
    if phase == "p1":
        for n_, p in net.named_parameters(): p.requires_grad = ("head." in n_ or n_.startswith("fuse."))
    else:
        for p in net.parameters(): p.requires_grad = True
    params = [p for n_, p in net.named_parameters()
              if p.requires_grad and "gru_head" not in n_ and "pke_head" not in n_]
    tag = f"r1head_{variant}_{phase}"
    m = _wsd_train(net, lambda n, x: n(x, "fuse"), params, tr, va_t, mon_x, mon_y, tag, 0,
                   patience=10, eval_every=2000, decay_steps=8000, max_steps=steps, B=B, lr0=lr0,
                   warm=warm, clip=clip)
    q = evaluate(net, seqs, tgt, quant=True)
    i8, pke, f32 = deploy_bytes(net); kb = (i8+pke+f32)/1024.0
    torch.save({"sd": {k: v.cpu() for k, v in net.state_dict().items()}}, os.path.join(HERE, f"_r1_ckpt_{variant}_{phase}.pt"))
    append_row(dict(variant="rank1head", config=f"{variant}_{phase}_h{h}", seed=0, kb=round(kb,1),
        kb_int8=round(i8/1024,1), kb_pke=round(pke/1024,2), kb_f32=round(f32/1024,1),
        macc=macc_estimate(net), params=sum(p.numel() for p in net.parameters()),
        float_ppl=0.0, ppl=round(q[0],3), t1=round(q[1],4), t3=round(q[2],4),
        best_step=m["best_step"], stop_reason=m["stop_reason"], mon_ppl=m["mon_ppl"],
        batch=512, seq=96, time_s=0))
    blk_params = 2*dmerge*h + h
    print(f"[{tag}] DONE: int8 {q[0]:.4f} (t1 {q[1]:.3f}) vs bare-fuse 3.314 = {q[0]-3.314:+.4f} | "
          f"{kb:.1f}KB | head-block params {blk_params} MACs {2*dmerge*h} ({m['stop_reason']})", flush=True)


def _r1ext_build():
    net = FuseFT(**_FS360).to(DEV)
    net.head = HeadBlock(net.d_B + net.dA, 36, "rank1").to(DEV)
    fwd = lambda n, x: n(x, "fuse")
    params = [p for n_, p in net.named_parameters() if "gru_head" not in n_ and "pke_head" not in n_]
    return net, fwd, params

def r1_extend_run(mode, tr, va, seqs, tgt, ext_steps=200000, cont=False,
                  peak=8e-4, hold=6e-4, warm=6000, clip=0.5, lr_min=2e-5, B=128):
    """GENTLE long continue-train of the stabilized rank1-p2 head (the fragile depth-36
    serial head): slow warmup 2e-5->peak, brief taper to a MODERATE hold (not high), clip
    0.5 throughout, checkpointed/continuable. readout mode: non-destructive short cosine
    anneal of a COPY of the current hot ckpt -> int8 vs 3.316 (own start) and 3.314 (bare)."""
    va_t = torch.tensor(va, dtype=torch.long); mon_x, mon_y = _mon_windows(va_t)
    net, fwd, params = _r1ext_build()
    ext_ckpt = os.path.join(HERE, "_r1_ext_ckpt.pt")
    start = os.path.join(HERE, "_r1_ckpt_rank1_p2.pt")
    ce = nn.CrossEntropyLoss()
    if mode == "readout":
        d = torch.load(ext_ckpt, map_location="cpu"); es = d["step"]
        net.load_state_dict({k: v.to(DEV) for k, v in d["sd"].items()})
        opt = torch.optim.Adam(params, lr=hold); batch = make_batcher(tr, 96, B); A = 8000
        best = {"ppl": 1e9}; best_sd = None
        for step in range(A):
            for g in opt.param_groups: g["lr"] = lr_min + 0.5*(hold-lr_min)*(1+math.cos(math.pi*step/A))
            net.train(); x, y = batch(); loss = ce(fwd(net, x).reshape(-1, V), y.reshape(-1))
            opt.zero_grad(); loss.backward(); nn.utils.clip_grad_norm_(params, clip); opt.step()
            if step % 1000 == 0 or step == A-1:
                net.eval()
                with torch.no_grad():
                    mppl = float(torch.exp(F.cross_entropy(fwd(net, mon_x).reshape(-1, V), mon_y.reshape(-1))))
                if mppl < best["ppl"]:
                    best = {"ppl": mppl}; best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
        net.load_state_dict({k: v.to(DEV) for k, v in best_sd.items()}); q = evaluate(net, seqs, tgt, quant=True)
        path = os.path.join(HERE, "r1_ext_readouts.csv"); ex = os.path.exists(path) and os.path.getsize(path) > 0
        with open(path, "a", newline="") as f:
            w = csv.DictWriter(f, fieldnames=["ext_step","anneal_int8_ppl","t1","d_vs_3316","d_vs_3314"])
            if not ex: w.writeheader()
            w.writerow(dict(ext_step=es, anneal_int8_ppl=round(q[0],4), t1=round(q[1],4),
                            d_vs_3316=round(q[0]-3.316,4), d_vs_3314=round(q[0]-3.314,4)))
        print(f"[r1_readout] ext-{es}: annealed int8 {q[0]:.4f} (t1 {q[1]:.3f}) "
              f"d_vs_3.316 {q[0]-3.316:+.4f} d_vs_3.314 {q[0]-3.314:+.4f} -> r1_ext_readouts.csv", flush=True)
        return
    # extend
    src = ext_ckpt if (cont and os.path.exists(ext_ckpt)) else start
    d = torch.load(src, map_location="cpu"); net.load_state_dict({k: v.to(DEV) for k, v in d["sd"].items()})
    opt = torch.optim.Adam(params, lr=peak); batch = make_batcher(tr, 96, B)
    traj = []; best = {"ppl": 1e9, "step": 0}; best_sd = None; step = 0
    if src == ext_ckpt:
        step = d.get("step", 0); traj = d.get("traj", []); best = d.get("best", best); best_sd = d.get("best_sd")
    def lr_at(s):
        if s < warm: return lr_min + (peak-lr_min)*s/warm
        if s < warm+20000: return peak + (hold-peak)*(s-warm)/20000
        return hold
    t0 = time.time()
    print(f"[r1_ext] {'CONTINUE' if src==ext_ckpt else 'START from p2 ckpt'} step {step} -> {ext_steps} "
          f"(warm {warm} peak {peak:.1e} hold {hold:.1e} clip {clip})", flush=True)
    while step < ext_steps:
        for g in opt.param_groups: g["lr"] = lr_at(step)
        net.train(); x, y = batch(); loss = ce(fwd(net, x).reshape(-1, V), y.reshape(-1))
        opt.zero_grad(); loss.backward(); nn.utils.clip_grad_norm_(params, clip); opt.step(); step += 1
        if step % 2000 == 0:
            net.eval()
            with torch.no_grad():
                mppl = float(torch.exp(F.cross_entropy(fwd(net, mon_x).reshape(-1, V), mon_y.reshape(-1))))
            traj.append({"step": step, "mon": round(mppl, 4)})
            if mppl < best["ppl"] - 1e-4:
                best = {"ppl": mppl, "step": step}; best_sd = {k: v.detach().cpu().clone() for k, v in net.state_dict().items()}
            print(f"[r1_ext] step {step}/{ext_steps} lr {lr_at(step):.2e} mon {mppl:.4f} "
                  f"best {best['ppl']:.4f}@{best['step']} ({time.time()-t0:.0f}s)", flush=True)
        if step % 20000 == 0:
            torch.save({"sd": {k: v.cpu() for k, v in net.state_dict().items()}, "step": step,
                        "traj": traj, "best": best, "best_sd": best_sd}, ext_ckpt)
    torch.save({"sd": {k: v.cpu() for k, v in net.state_dict().items()}, "step": step,
                "traj": traj, "best": best, "best_sd": best_sd}, ext_ckpt)
    print(f"[r1_ext] DONE ext {step} best_mon {best['ppl']:.4f}@{best['step']}", flush=True)


# --------------------------------------------------------------- CSV / resume --
def load_done():
    if not os.path.exists(CSV): return set()
    return {(r["variant"], r["config"], r["seed"]) for r in csv.DictReader(open(CSV))}

def append_row(row):
    ex = os.path.exists(CSV) and os.path.getsize(CSV) > 0
    with open(CSV, "a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=FIELDS)
        if not ex: w.writeheader()
        w.writerow(row)

def run_one(variant, cfg_name, build_fn, tr, va, seqs, tgt, seed, done, B=512, L=96, **tk):
    key = (variant, cfg_name, str(seed))
    if key in done:
        print(f"  skip {variant}/{cfg_name}/seed{seed}", flush=True); return
    print(f"  RUN  {variant}/{cfg_name}/seed{seed} (train-to-convergence B={B} L={L})", flush=True)
    net, m = train_model(build_fn, tr, va, seed, tag=f"{cfg_name}", B=B, L=L, **tk)
    fppl, _, _ = evaluate(net, seqs, tgt, quant=False)
    qppl, t1, t3 = evaluate(net, seqs, tgt, quant=True)
    i8, pke, f32 = deploy_bytes(net)
    kb = (i8 + pke + f32) / 1024.0
    flag = "  <-- SUSPECT UNDERTRAINED (hit cap)" if m["stop_reason"] == "cap" else ""
    row = dict(variant=variant, config=cfg_name, seed=seed,
               kb=round(kb,1), kb_int8=round(i8/1024,1), kb_pke=round(pke/1024,2),
               kb_f32=round(f32/1024,1), macc=macc_estimate(net),
               params=sum(p.numel() for p in net.parameters()),
               float_ppl=round(fppl,3), ppl=round(qppl,3), t1=round(t1,4), t3=round(t3,4),
               best_step=m["best_step"], stop_reason=m["stop_reason"],
               mon_ppl=m["mon_ppl"], batch=B, seq=L, time_s=m["time_s"])
    append_row(row)
    print(f"  DONE {variant}/{cfg_name}/seed{seed}: {kb:.1f}KB (i8 {i8/1024:.1f}"
          f"+pke {pke/1024:.2f}+f32 {f32/1024:.1f}) float {fppl:.3f} int8 ppl {qppl:.3f} "
          f"t1 {t1:.3f} t3 {t3:.3f} | best@{m['best_step']} {m['stop_reason']} "
          f"mon {m['mon_ppl']:.3f} [appended]{flag}", flush=True)


# --------------------------------------------------------------- config lists --
def standalone_cfgs():
    # (name, k, D, H, layers, combine, use_pke)
    L = [
        ("mlp_head_k7_D32_H256_L2",  7, 32, 256, 2, "sum",    False),  # plain emb baseline
        ("pke_sum_k4_D32_H256_L2",   4, 32, 256, 2, "sum",    True),
        ("pke_sum_k7_D16_H256_L2",   7, 16, 256, 2, "sum",    True),
        ("pke_sum_k7_D32_H256_L2",   7, 32, 256, 2, "sum",    True),
        ("pke_sum_k12_D16_H256_L2", 12, 16, 256, 2, "sum",    True),
        ("pke_sum_k12_D32_H256_L2", 12, 32, 256, 2, "sum",    True),
        ("pke_cat_k4_D16_H256_L2",   4, 16, 256, 2, "concat", True),
        ("pke_cat_k4_D32_H256_L2",   4, 32, 256, 2, "concat", True),
        ("pke_cat_k7_D8_H256_L2",    7,  8, 256, 2, "concat", True),
        ("pke_cat_k7_D16_H256_L2",   7, 16, 256, 2, "concat", True),
        ("pke_cat_k12_D8_H256_L2",  12,  8, 256, 2, "concat", True),
        ("pke_sum_k7_D16_H128_L1",   7, 16, 128, 1, "sum",    True),
        ("pke_sum_k7_D32_H512_L3",   7, 32, 512, 3, "sum",    True),
    ]
    out = []
    for name, k, D, H, ly, comb, up in L:
        out.append((name, lambda k=k,D=D,H=H,ly=ly,comb=comb,up=up:
                    StandaloneMLP(k, D, H, ly, comb, use_pke=up)))
    return out

# GRU size points (HF, HS, E, FL) tracing the baseline curve
GRU_SIZES = [
    ("s100", 96,  40, 40, 1),
    ("s170", 152, 64, 48, 1),
    ("s260", 208, 80, 56, 1),
    ("s360", 272, 96, 64, 1),
]

def base_cfgs():
    """Baseline dense two-timescale GRU across sizes = the 'spend bytes on more GRU'
    reference frontier (the arm PKE must beat at matched deployed-KB)."""
    return [(f"base_{s}", lambda HF=HF,HS=HS,E=E,FL=FL: TTGRU(HF,HS,E,FL))
            for s, HF, HS, E, FL in GRU_SIZES]

def gru_cfgs():
    """ADDITIVE/subsuming integrations (each recovers baseline exactly by zeroing the
    PKE contribution, so at convergence must be >= baseline -- a correctness guard).
    Full-replace is excluded: it is conclusively dominated (reconstruction burden,
    optimization-limited, size-independent) -- see the replace_fmlp sweep."""
    HFm, HSm, Em = 152, 64, 48
    out = []
    for D in [16, 32]:
        out.append((f"addstate_k7_D{D}_s170",
            lambda D=D: TTGRU(HFm,HSm,Em,1, pke=(7,D,"concat"), integ="addstate")))
    for D in [8, 16]:
        out.append((f"concat_k7_D{D}_s170",
            lambda D=D: TTGRU(HFm,HSm,Em,1, pke=(7,D,"concat"), integ="concat")))
    # concat across a second size -> a PKE-integration frontier reference
    out.append(("concat_k7_D16_s360",
        lambda: TTGRU(272,96,64,1, pke=(7,16,"concat"), integ="concat")))
    return out

def fmlp_cfgs():
    """PRIORITY variant: PKE concat -> 2-layer MLP f (with ReLU) -> fast-GRU input,
    replacing emb(last). SUBSUMES the baseline GRU (f can select just the newest
    position -> a plain per-char emb), so with enough steps it should be >= baseline.
    Sweep table D, f hidden Hf, k, and GRU size."""
    HFm, HSm, Em = 152, 64, 48
    out = []
    for D in [4, 8, 16, 32]:                         # D sweep, Hf=k*D, k7, s170
        out.append((f"replace_fmlp_k7_D{D}_HfkD_s170",
            lambda D=D: TTGRU(HFm,HSm,Em,1, pke=(7,D,"concat"),
                              integ="replace_fmlp", fmlp_hidden=7*D)))
    for Hf, tag in [(Em, "E"), (2*7*16, "2kD")]:     # Hf variants at k7 D16
        out.append((f"replace_fmlp_k7_D16_Hf{tag}_s170",
            lambda Hf=Hf: TTGRU(HFm,HSm,Em,1, pke=(7,16,"concat"),
                                integ="replace_fmlp", fmlp_hidden=Hf)))
    out.append(("replace_fmlp_k12_D16_HfkD_s170",     # k12
        lambda: TTGRU(HFm,HSm,Em,1, pke=(12,16,"concat"),
                      integ="replace_fmlp", fmlp_hidden=12*16)))
    for sname, HF, HS, E, FL in GRU_SIZES:            # across GRU sizes (frontier)
        if sname == "s170": continue
        out.append((f"replace_fmlp_k7_D16_Hf2kD_{sname}",
            lambda HF=HF,HS=HS,E=E,FL=FL: TTGRU(HF,HS,E,FL, pke=(7,16,"concat"),
                                                integ="replace_fmlp", fmlp_hidden=224)))
    return out

def fmlpres_cfgs():
    """RESIDUAL f-map (expected winner among replace-style): GRU input =
    emb(last) + g(concat PKE), g's final layer zero-init -> starts at baseline, only
    ADDS positional info (no reconstruction burden -> not optimization-limited like
    full-replace). Sweep D, f hidden Hf, and GRU size."""
    HFm, HSm, Em = 152, 64, 48
    out = []
    for D in [8, 16, 32]:                             # D sweep at s170, Hf=2kD
        out.append((f"fmlp_res_k7_D{D}_Hf2kD_s170",
            lambda D=D: TTGRU(HFm,HSm,Em,1, pke=(7,D,"concat"),
                              integ="fmlp_res", fmlp_hidden=2*7*D)))
    for Hf, tag in [(Em, "E"), (7*16, "kD")]:         # Hf variants at k7 D16
        out.append((f"fmlp_res_k7_D16_Hf{tag}_s170",
            lambda Hf=Hf: TTGRU(HFm,HSm,Em,1, pke=(7,16,"concat"),
                                integ="fmlp_res", fmlp_hidden=Hf)))
    for sname, HF, HS, E, FL in GRU_SIZES:            # across GRU sizes (frontier)
        if sname == "s170": continue
        out.append((f"fmlp_res_k7_D16_Hf2kD_{sname}",
            lambda HF=HF,HS=HS,E=E,FL=FL: TTGRU(HF,HS,E,FL, pke=(7,16,"concat"),
                                                integ="fmlp_res", fmlp_hidden=224)))
    return out

def sparse_cfgs():
    """Exploratory: high-dim per-(pos,char) embedding (summed) with an L1 penalty so
    each entry keeps only ~nnz coords, deployed as a bitmask (Dh/8 B) + nnz fp16
    values. Fed (projected) to the fast-GRU input. Does sparse-high-dim beat dense
    concat at matched bytes?"""
    HFm, HSm, Em = 152, 64, 48
    out = []
    for Dh, nnz in [(112, 16), (112, 8), (224, 16)]:
        out.append((f"sparse_k7_Dh{Dh}_nnz{nnz}_s170",
            lambda Dh=Dh,nnz=nnz: TTGRU(HFm,HSm,Em,1, pke=(7,Dh,"sum"),
                                        integ="sparse", target_nnz=nnz, l1coef=2e-4)))
    return out

def sparse2_cfgs():
    """FIXED sparse-high-dim (follow-up): high-dim per-(pos,char) table (Dh),
    summed, fed as the PKE table inside the WINNING residual fmlp_res (emb + g(PKE)).
    Trained with a HARD L1 ANNEAL + a straight-through top-nnz prune baked in, so the
    deployed bitmask+nnz-fp16 table is lossless. Tests: can a sparse-high-dim table
    beat the dense-concat table at fmlp_res's KB operating points?"""
    HFm, HSm, Em = 152, 64, 48
    out = []
    for Dh, nnz in [(112, 16), (112, 8), (224, 16)]:
        out.append((f"sparse_res_k7_Dh{Dh}_nnz{nnz}_s170",
            lambda Dh=Dh,nnz=nnz: TTGRU(HFm,HSm,Em,1, pke=(7,Dh,"sum"),
                integ="sparse_res", fmlp_hidden=224, target_nnz=nnz)))
    out.append(("sparse_res_k7_Dh112_nnz16_s260",
        lambda: TTGRU(208,80,56,1, pke=(7,112,"sum"), integ="sparse_res",
                      fmlp_hidden=224, target_nnz=16)))
    return out

def confirm_cfgs():
    """400KB operating point: baseline GRU vs best PKE integration, multi-seed.
    Sizes chosen (in code we print deploy KB) so int8 GRU (+fp16 PKE) lands ~400KB."""
    # NOTE: winning integration(s) confirmed here at 400KB, multi-seed. Adjust the
    # non-baseline entries after the sweep so we confirm only the arm(s) that won.
    # all sized to ~405KB deployed (matched budget) for a fair comparison. The
    # additive/subsuming forms (fmlp_res, addstate, concat) are the ones expected to
    # beat baseline; full-replace is dropped (optimization-limited, see the sweep).
    out = []
    out.append(("confirm_base_400",     lambda: TTGRU(256,96,64,1)))                       # 403.3KB
    out.append(("confirm_fmlpres_400",  lambda: TTGRU(228,96,64,1, pke=(7,16,"concat"),    # 403.7KB
                                                      integ="fmlp_res", fmlp_hidden=224)))
    out.append(("confirm_addstate_400", lambda: TTGRU(230,96,64,1, pke=(7,16,"concat"),    # 403.7KB
                                                      integ="addstate")))
    out.append(("confirm_concat_400",   lambda: TTGRU(246,96,64,1, pke=(7,16,"concat"),    # 406.4KB
                                                      integ="concat")))
    return out


# --------------------------------------------------------------- main ----------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--phase", default="all",
                    choices=["standalone","base","gru","fmlp","fmlpres","sparse",
                             "sparse2","fuse","grok","rank1head","r1ext","confirm","all"])
    ap.add_argument("--seeds", type=int, nargs="+", default=None)
    ap.add_argument("--grok_which", choices=["fmlp","fuse","fuse_s360"], default="fmlp")
    ap.add_argument("--grok_ext_steps", type=int, default=0, help="override extension horizon (to continue)")
    ap.add_argument("--grok_continue", action="store_true", help="skip re-convergence; continue from grok ckpt")
    ap.add_argument("--grok_readout", action="store_true", help="non-destructive annealed readout of the hot ckpt")
    ap.add_argument("--r1_variant", choices=["std","rank1"], default="rank1")
    ap.add_argument("--r1_phase", choices=["anneal","p1","p2"], default="anneal")
    ap.add_argument("--r1_batch", type=int, default=160)
    ap.add_argument("--r1_lr", type=float, default=2.5e-3)
    ap.add_argument("--r1_warm", type=int, default=800)
    ap.add_argument("--r1_clip", type=float, default=1.0)
    ap.add_argument("--r1ext_mode", choices=["extend","readout"], default="extend")
    ap.add_argument("--r1ext_cont", action="store_true")
    ap.add_argument("--r1ext_steps", type=int, default=200000)
    ap.add_argument("--patience", type=int, default=8, help="evals w/o improvement -> decay")
    ap.add_argument("--eval_every", type=int, default=1000)
    ap.add_argument("--max_steps", type=int, default=90000, help="safety cap")
    ap.add_argument("--decay_steps", type=int, default=5000)
    args = ap.parse_args()

    print(f"device {DEV} torch {torch.__version__}", flush=True)
    tr, va = load_data(); seqs, tgt = build_eval(va)
    print(f"train {len(tr):,} val {len(va):,}  eval {seqs.shape[0]}x{seqs.shape[1]}"
          f" = {len(tgt):,} positions", flush=True)
    done = load_done()
    tk = dict(patience=args.patience, eval_every=args.eval_every,
              max_steps=args.max_steps, decay_steps=args.decay_steps)

    def do(phase, variant, cfgs, seeds):
        print(f"\n=== PHASE {phase} (train-to-convergence, patience {args.patience}) ===",
              flush=True)
        for name, bfn in cfgs:
            for sd in seeds:
                run_one(variant, name, bfn, tr, va, seqs, tgt, sd, done, **tk)

    if args.phase in ("standalone","all"):
        do("standalone", "standalone", standalone_cfgs(), args.seeds or [0])
    if args.phase in ("base","all"):
        for s, HF, HS, E, FL in GRU_SIZES:
            print(f"  size {s}: HF{HF} HS{HS} E{E} FL{FL} -> "
                  f"{C.count_bytes(HF,HS,E,True,FL)[0]/1024:.1f}KB", flush=True)
        do("base", "gru", base_cfgs(), args.seeds or [0])
    if args.phase in ("fmlp","all"):
        do("fmlp", "gru", fmlp_cfgs(), args.seeds or [0])
    # fmlp_res (residual f-map, priority) runs at the START of the gru phase so it
    # follows the replace sweep and precedes addstate/concat; own PHASE milestone.
    if args.phase in ("fmlpres","gru","all"):
        do("fmlpres", "gru", fmlpres_cfgs(), args.seeds or [0])
    if args.phase in ("gru","all"):
        do("gru", "gru", gru_cfgs(), args.seeds or [0])
    if args.phase in ("sparse","all"):
        do("sparse", "gru", sparse_cfgs(), args.seeds or [0])
    if args.phase in ("sparse2",):
        # FIXED sparse-high-dim follow-up (hard L1 anneal + STE prune); a couple seeds.
        stk = dict(tk, sparse=True, l1_max=3e-3, anneal_end=20000, prune_at=25000)
        print(f"\n=== PHASE sparse2 (hard-L1-anneal + STE prune, to convergence) ===",
              flush=True)
        for name, bfn in sparse2_cfgs():
            for sd in (args.seeds or [0, 1]):
                run_one("sparse2", name, bfn, tr, va, seqs, tgt, sd, done, **stk)
    if args.phase in ("fuse",):
        # training-curriculum fusion: Phase A (frozen branches) vs Phase B (joint FT).
        print(f"\n=== PHASE fuse (2-branch curriculum, to convergence) ===", flush=True)
        for name, c in fuse_cfgs():
            seeds = args.seeds or ([0, 1] if "s170" in name else [0])
            for sd in seeds:
                if ("fuse", name+"_B", str(sd)) in done:
                    print(f"  skip fuse/{name}/seed{sd}", flush=True); continue
                print(f"  RUN  fuse/{name}/seed{sd}", flush=True)
                net, r = fuse_run(name, c, tr, va, seqs, tgt, sd, tk)
                i8, pke, f32 = deploy_bytes(net); kb = (i8+pke+f32)/1024.0
                params = sum(p.numel() for n_,p in net.named_parameters()
                             if "gru_head" not in n_ and "pke_head" not in n_)
                for stg in ("A", "B"):
                    fppl, qppl, t1, t3, m = r[stg]
                    append_row(dict(variant="fuse", config=name+"_"+stg, seed=sd,
                        kb=round(kb,1), kb_int8=round(i8/1024,1), kb_pke=round(pke/1024,2),
                        kb_f32=round(f32/1024,1), macc=macc_estimate(net), params=params,
                        float_ppl=round(fppl,3), ppl=round(qppl,3), t1=round(t1,4), t3=round(t3,4),
                        best_step=m["best_step"], stop_reason=m["stop_reason"],
                        mon_ppl=m["mon_ppl"], batch=512, seq=96, time_s=0))
                dA_ = r["B"][1] - r["A"][1]
                print(f"  DONE fuse/{name}/seed{sd}: {kb:.1f}KB | PhaseA int8 {r['A'][1]:.3f} "
                      f"-> PhaseB int8 {r['B'][1]:.3f}  (delta {dA_:+.3f}) [appended]", flush=True)
    if args.phase == "grok":
        print(f"\n=== PHASE grok ({args.grok_which}{' READOUT' if args.grok_readout else ''}) ===", flush=True)
        if args.grok_readout:
            grok_readout(args.grok_which, tr, va, seqs, tgt)
        else:
            grok_run(args.grok_which, tr, va, seqs, tgt,
                     ext_steps_override=args.grok_ext_steps, cont=args.grok_continue)
    if args.phase == "rank1head":
        print(f"\n=== PHASE rank1head ({args.r1_variant} {args.r1_phase}) ===", flush=True)
        if args.r1_phase == "anneal":
            _anneal_and_save_fs360(tr, va, seqs, tgt)
        else:
            rank1head_run(args.r1_variant, args.r1_phase, tr, va, seqs, tgt, B=args.r1_batch,
                          lr0=args.r1_lr, warm=args.r1_warm, clip=args.r1_clip)
    if args.phase == "r1ext":
        print(f"\n=== PHASE r1ext ({args.r1ext_mode}) ===", flush=True)
        r1_extend_run(args.r1ext_mode, tr, va, seqs, tgt,
                      ext_steps=args.r1ext_steps, cont=args.r1ext_cont)
    if args.phase in ("confirm","all"):
        # SEED-OUTER: seed0 of ALL configs first (full 4-way comparison after ~4 runs),
        # then seeds 1,2 to refine mean+-std.
        seeds = args.seeds or [0, 1, 2]
        cfgs = confirm_cfgs()
        print(f"\n=== PHASE confirm (train-to-convergence, SEED-OUTER, seeds {seeds}) ===",
              flush=True)
        for sd in seeds:
            for name, bfn in cfgs:
                run_one("confirm", name, bfn, tr, va, seqs, tgt, sd, done, **tk)

    print("run_pke: all requested work complete.", flush=True)

if __name__ == "__main__":
    main()
