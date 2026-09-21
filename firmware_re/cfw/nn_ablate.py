#!/usr/bin/env python3
"""Controlled architecture search / ablation for the Azoth char predictor.

Toggles ONE thing at a time from a clean single-GRU baseline, trains every arm to
convergence under an IDENTICAL schedule (warm-restart cosine LR, early-stop on
held-out ppl with patience), evaluates on the SAME held-out set, and reports
params / MACs / state bytes / float+int8 ppl/top-1/top-3 (multiple seeds on key
arms).  A fast 27-symbol letters task is the cheap testbed; winning choices are
re-confirmed on the 72-symbol deployment task.

Architectures (GenNet):
  * single GRU (no slow layer)            -- baseline, and a param-matched "wide" one
  * two-timescale: fast GRU + slow cell updated per word (slow = gru | lstm | rnn)
  * aux heads (char+2 / char+3 / word), anneal-then-continue schedule
  * distillation (from a teacher trained for the same vocab)
  * word-boundary definition: non-alpha (default) vs space-only

int8 column = per-output-row symmetric fake-quant of every weight matrix, run
through the same torch forward (fair int8 estimate across all arms; the DEPLOYED
model additionally gets the exact nn_common/nn.c int8 path).
"""
import argparse, os, time, json, copy, math
import numpy as np
import torch, torch.nn as nn, torch.nn.functional as F
import nn_common as C

HERE = os.path.dirname(os.path.abspath(__file__))
DEV = "cuda" if torch.cuda.is_available() else "cpu"


# ------------------------------------------------------------- vocab handling -
def vocab_syms(mode):
    if mode == "72":
        return C.V
    return 27          # a-z + space

def load_symbols(mode, path):
    if mode == "72":
        return C.load_symbols(path)
    # 27-vocab letters testbed: lowercase, a-z -> 0..25, everything else -> space(26)
    t = open(path, "r", encoding="utf-8", errors="ignore").read().lower()
    arr = np.frombuffer(t.encode("latin-1", "ignore"), np.uint8)
    lut = np.full(256, 26, np.uint8)
    for i in range(26):
        lut[ord('a') + i] = i
    out = lut[arr]
    # collapse repeated spaces
    keep = ~((out == 26) & (np.roll(out, 1) == 26))
    keep[0] = True
    return out[keep].astype(np.int64)

def is_alpha_mask(x, mode):
    """word-INTERIOR chars.  27: a-z (0..25).  72: a-z or CAPESC(39)."""
    if mode == "72":
        return (x < 26) | (x == C.CAPESC)
    return x < 26

def boundary_mask(x, mode, boundary):
    if boundary == "space":
        sp = C.SP if mode == "72" else 26
        return (x == sp).float()
    return (~is_alpha_mask(x, mode)).float()      # non-alpha (default)


# ------------------------------------------------------------------ data prep -
def next_word_target(data, mode):
    alpha = is_alpha_mask(data, mode)
    idx = np.where(alpha)[0]
    if len(idx) == 0:
        return np.full(len(data), 26 if mode != "72" else C.SP, np.int64)
    pos = np.searchsorted(idx, np.arange(len(data)), side="right")
    valid = pos < len(idx)
    sp = C.SP if mode == "72" else 26
    na = np.full(len(data), sp, np.int64)
    na[valid] = data[idx[pos[valid].clip(max=len(idx)-1)]]
    return na

def get_data(mode, paths, seed=0):
    trs, vas = [], []
    for p in paths:
        if not os.path.exists(p):
            continue
        a = load_symbols(mode, p)
        nv = min(250_000, len(a) // 20)
        trs.append(a[:len(a)-nv]); vas.append(a[len(a)-nv:])
    tr = np.concatenate(trs); va = np.concatenate(vas)
    return (tr, next_word_target(tr, mode)), (va, next_word_target(va, mode))

def make_batcher(data, na, L, B, seed):
    dt = torch.tensor(data, dtype=torch.long); nt = torch.tensor(na, dtype=torch.long)
    N = len(data); g = torch.Generator().manual_seed(seed)
    def batch():
        idx = torch.randint(0, N - L - 3, (B,), generator=g)
        seq = torch.stack([dt[i:i+L+3] for i in idx])
        return (seq[:, :L].to(DEV), seq[:, 1:L+1].to(DEV), seq[:, 2:L+2].to(DEV),
                seq[:, 3:L+3].to(DEV),
                torch.stack([nt[i:i+L] for i in idx]).to(DEV))
    return batch


# ------------------------------------------------------------------ model -----
class GenNet(nn.Module):
    def __init__(self, V, HF, HS, E, out_skip=True, slow="gru",
                 aux=(), boundary="nonalpha", mode="72"):
        super().__init__()
        self.V, self.HF, self.HS, self.E = V, HF, HS, E
        self.out_skip, self.slow_kind, self.aux, self.boundary, self.mode = \
            out_skip, slow, tuple(aux), boundary, mode
        self.emb = nn.Embedding(V, E)
        self.fast = nn.GRU(E, HF, batch_first=True)
        if HS > 0:
            self.slow = {"gru": nn.GRUCell, "lstm": nn.LSTMCell,
                         "rnn": nn.RNNCell}[slow](HF, HS)
        outin = HF + HS + (E if out_skip else 0)
        self.out = nn.Linear(outin, V)
        feat = HF + HS
        if "char2" in self.aux: self.h2 = nn.Linear(feat, V)
        if "char3" in self.aux: self.h3 = nn.Linear(feat, V)
        if "word"  in self.aux: self.hw = nn.Linear(HS if HS > 0 else HF, V)

    def run_slow(self, hf_seq, bmask):
        """Masked per-word recurrence.  Precompute the (larger) input-side
        projection for ALL timesteps in one matmul; the loop only does the small
        recurrent matmul + gate combine.  Same math as nn.{GRU,LSTM,RNN}Cell."""
        B, L, _ = hf_seq.shape; H = self.HS; sk = self.slow_kind
        s = self.slow
        gi_all = torch.addmm(s.bias_ih, hf_seq.reshape(B*L, -1), s.weight_ih.t()
                             ).reshape(B, L, -1)                       # [B,L,g*H]
        Whh_t = s.weight_hh.t(); bhh = s.bias_hh
        hs = hf_seq.new_zeros(B, H); cs = hf_seq.new_zeros(B, H)
        outs = []
        for t in range(L):
            m = bmask[:, t:t+1]
            gi = gi_all[:, t]; gh = torch.addmm(bhh, hs, Whh_t)
            if sk == "gru":
                r = torch.sigmoid(gi[:, :H] + gh[:, :H])
                z = torch.sigmoid(gi[:, H:2*H] + gh[:, H:2*H])
                n = torch.tanh(gi[:, 2*H:3*H] + r * gh[:, 2*H:3*H])
                nh = (1 - z) * n + z * hs
            elif sk == "lstm":
                pre = gi + gh
                i = torch.sigmoid(pre[:, :H]); f = torch.sigmoid(pre[:, H:2*H])
                g = torch.tanh(pre[:, 2*H:3*H]); o = torch.sigmoid(pre[:, 3*H:4*H])
                nc = f * cs + i * g; cs = m * nc + (1 - m) * cs
                nh = o * torch.tanh(cs)
            else:  # rnn (tanh)
                nh = torch.tanh(gi + gh)
            hs = m * nh + (1 - m) * hs
            outs.append(hs)
        return torch.stack(outs, 1)

    def forward(self, x):
        e = self.emb(x)
        hf_seq, _ = self.fast(e)
        if self.HS > 0:
            bmask = boundary_mask(x, self.mode, self.boundary)
            hs_seq = self.run_slow(hf_seq, bmask)
            feat = torch.cat([hf_seq, hs_seq], -1)
        else:
            bmask = None; hs_seq = None
            feat = hf_seq
        of = torch.cat([feat, e], -1) if self.out_skip else feat
        logits = self.out(of)
        aux = {}
        if "char2" in self.aux: aux["char2"] = self.h2(feat)
        if "char3" in self.aux: aux["char3"] = self.h3(feat)
        if "word"  in self.aux: aux["word"]  = (self.hw(hs_seq if hs_seq is not None else hf_seq), bmask)
        return logits, aux


# ------------------------------------------------------------- budget counters -
def counts(V, HF, HS, E, out_skip, slow="gru"):
    g = {"gru": 3, "lstm": 4, "rnn": 1}[slow]
    outin = HF + HS + (E if out_skip else 0)
    i8 = 3*HF*E + 3*HF*HF                          # fast GRU
    if HS > 0:
        i8 += g*HS*HF + g*HS*HS                    # slow cell
    i8 += V*outin                                  # output
    fl = V*E                                       # emb
    fl += 3*HF + 3*HF                              # fast scales+bias (approx: quantised rows)
    if HS > 0: fl += g*HS + g*HS
    fl += V + V                                    # out scale+bias
    bytes_ = i8 + fl*4
    macc = 3*HF*E + 3*HF*HF + V*outin              # per-char
    macw = (g*HS*HF + g*HS*HS) if HS > 0 else 0    # per-word
    state = HF + HS + (HS if slow == "lstm" and HS > 0 else 0)   # lstm carries c too
    return dict(bytes=bytes_, i8=i8, macc=macc, macw=macw, state=state,
                params=None)

def torch_params(net):
    return sum(p.numel() for p in net.parameters())


# ------------------------------------------------------------------ schedule --
def aux_weight(step, S, coef, full, anneal):
    f = step / S
    if f < full:   return coef
    if f < anneal: return coef * (anneal - f) / (anneal - full)
    return 0.0

def lr_at(step, S, lr0, lr1, lr_min, anneal, warm):
    if not warm:
        p = step / S
        return lr_min + 0.5*(lr0-lr_min)*(1+math.cos(math.pi*p))
    S2 = anneal * S
    if step < S2:
        p = step / S2
        return lr_min + 0.5*(lr0-lr_min)*(1+math.cos(math.pi*p))
    p = (step - S2) / max(1.0, S - S2)
    return lr_min + 0.5*(lr1-lr_min)*(1+math.cos(math.pi*p))


# ------------------------------------------------------------------ eval -------
@torch.no_grad()
def eval_float(net, val, V, L=200, B=256, nb=30, fakequant=False):
    dt = torch.tensor(val, dtype=torch.long); N = len(val)
    if fakequant:
        orig = {}
        for name, p in net.named_parameters():
            if p.dim() == 2 and ("weight" in name) and ("emb" not in name):
                orig[name] = p.data.clone()
                amax = p.data.abs().amax(1, keepdim=True).clamp_min(1e-8)
                scale = amax / 127.0
                p.data = torch.round(p.data / scale).clamp(-127, 127) * scale
    net.eval(); tot = top1 = top3 = 0; nll = 0.0
    lossf = nn.CrossEntropyLoss(reduction="sum")
    g = torch.Generator().manual_seed(0)
    for _ in range(nb):
        idx = torch.randint(0, N - L - 1, (B,), generator=g)
        x = torch.stack([dt[i:i+L] for i in idx]).to(DEV)
        y = torch.stack([dt[i+1:i+L+1] for i in idx]).to(DEV)
        out = net(x); out = out[0] if isinstance(out, tuple) else out
        lg = out.reshape(-1, V); yt = y.reshape(-1)
        nll += lossf(lg, yt).item(); tot += yt.numel()
        t3 = lg.topk(3, 1).indices
        top1 += (t3[:, 0] == yt).sum().item()
        top3 += (t3 == yt[:, None]).any(1).sum().item()
    if fakequant:
        for name, p in net.named_parameters():
            if name in orig: p.data = orig[name]
    return dict(ppl=float(np.exp(nll/tot)), top1=top1/tot, top3=top3/tot)


# ------------------------------------------------------------------ train ------
def train_arm(cfg, data, val, V, mode, teacher=None, quiet=True):
    (tr, tna) = data; (va, vna) = val
    torch.manual_seed(cfg["seed"]); np.random.seed(cfg["seed"])
    net = GenNet(V, cfg["HF"], cfg["HS"], cfg["E"], cfg["skip"], cfg["slow"],
                 cfg["aux"], cfg["boundary"], mode).to(DEV)
    opt = torch.optim.Adam(net.parameters(), lr=cfg["lr0"])
    ce = nn.CrossEntropyLoss()
    S = cfg["steps"]; batch = make_batcher(tr, tna, cfg["L"], cfg["B"], cfg["seed"])
    best = {"ppl": 1e9}; best_state = None; since = 0; curve = []; t0 = time.time()
    for step in range(S):
        for gp in opt.param_groups:
            gp["lr"] = lr_at(step, S, cfg["lr0"], cfg["lr1"], cfg["lr_min"],
                             cfg["anneal"], cfg["warm"])
        net.train()
        x, y1, y2, y3, w1 = batch()
        logits, aux = net(x)
        ls = logits.reshape(-1, V); yt = y1.reshape(-1)
        if teacher is not None:
            with torch.no_grad():
                tl = teacher(x).reshape(-1, V)
            T, al = cfg["T"], cfg["alpha"]
            kd = F.kl_div(F.log_softmax(ls/T, -1), F.softmax(tl/T, -1),
                          reduction="batchmean") * (T*T)
            loss = al*kd + (1-al)*ce(ls, yt)
        else:
            loss = ce(ls, yt)
        w = aux_weight(step, S, cfg["aux_coef"], cfg["aux_full"], cfg["anneal"]) if cfg["aux"] else 0.0
        if w > 0:
            if "char2" in aux: loss = loss + w*ce(aux["char2"].reshape(-1, V), y2.reshape(-1))
            if "char3" in aux: loss = loss + w*ce(aux["char3"].reshape(-1, V), y3.reshape(-1))
            if "word" in aux:
                wl, bm = aux["word"]; bmf = bm.reshape(-1) > 0.5
                if bmf.any():
                    loss = loss + w*ce(wl.reshape(-1, V)[bmf], w1.reshape(-1)[bmf])
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(net.parameters(), 1.0); opt.step()
        if step % cfg["eval_every"] == 0 or step == S-1:
            fm = eval_float(net, va, V, nb=cfg["eval_nb"])
            curve.append({"step": step, **fm})
            if fm["ppl"] < best["ppl"] - 1e-4:
                best = {"step": step, **fm}; since = 0
                best_state = copy.deepcopy({k: v.detach().cpu() for k, v in net.state_dict().items()})
            else:
                since += 1
            if not quiet:
                print(f"    step {step:6d} ppl {fm['ppl']:.3f} t1 {fm['top1']:.3f} "
                      f"best {best['ppl']:.3f}@{best.get('step')} ({time.time()-t0:.0f}s)")
            if since >= cfg["patience"]:
                break
    net.load_state_dict({k: v.to(DEV) for k, v in best_state.items()})
    fmF = eval_float(net, va, V, nb=50)
    fmQ = eval_float(net, va, V, nb=50, fakequant=True)
    ct = counts(V, cfg["HF"], cfg["HS"], cfg["E"], cfg["skip"], cfg["slow"])
    ct["params"] = torch_params(net)
    return net, dict(float=fmF, int8=fmQ, counts=ct, best_step=best.get("step"),
                     curve=curve), best


# ------------------------------------------------------------------ teacher ----
class Teacher(nn.Module):
    def __init__(self, V, H=384, layers=2, E=64):
        super().__init__()
        self.emb = nn.Embedding(V, E)
        self.rnn = nn.LSTM(E, H, num_layers=layers, batch_first=True, dropout=0.1)
        self.out = nn.Linear(H, V)
    def forward(self, x): return self.out(self.rnn(self.emb(x))[0])

def train_teacher(data, val, V, steps, L, B, H=384, layers=2, E=64, seed=1234):
    (tr, tna) = data; (va, vna) = val
    torch.manual_seed(seed)
    net = Teacher(V, H, layers, E).to(DEV)
    opt = torch.optim.Adam(net.parameters(), lr=2e-3, weight_decay=1e-5)
    sch = torch.optim.lr_scheduler.CosineAnnealingLR(opt, steps)
    ce = nn.CrossEntropyLoss(); batch = make_batcher(tr, tna, L, B, seed); t0 = time.time()
    for s in range(steps):
        x, y1, _, _, _ = batch()
        loss = ce(net(x).reshape(-1, V), y1.reshape(-1))
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(net.parameters(), 1.0); opt.step(); sch.step()
        if s % 1000 == 0:
            print(f"  [teacher] {s} loss {loss.item():.3f} ({time.time()-t0:.0f}s)")
    net.eval()
    fm = eval_float(net, va, V, nb=40)
    print(f"  [teacher] ppl {fm['ppl']:.3f} t1 {fm['top1']:.3f} t3 {fm['top3']:.3f}")
    return net, fm
