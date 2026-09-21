#!/usr/bin/env python3
"""Training pipeline for the Azoth on-device char predictor v3.

BIG vocab (V=72: a-z, 0-9, space/tab/newline, CAPESC token, 32 ASCII punct) +
TWO-TIMESCALE GRU (fast char-level state + slow word-level state) + auxiliary
next-token heads (char+2 / char+3 / next-word, annealed to 0) + distillation
from a large LSTM teacher.

Modes:
  --train_teacher      train the LSTM teacher -> nn_teacher.pt (new 72-vocab)
  --export             train the student config and export nn_weights.{bin,h} + manifest
  --ablate_aux         short A/B: student with aux vs without (prints deltas)
  (default)            train student, print metrics (no export)

Deployment constraints: blob <= 64KB @0x50000 ending <0x60000; persistent state
hf+hs <= 256 float32 (1KB); <=~1.5M MAC/step; int8 per-output-row quant.
"""
import argparse, os, time, json, copy, math
import numpy as np
import torch, torch.nn as nn, torch.nn.functional as F
import nn_common as C

HERE = os.path.dirname(os.path.abspath(__file__))
DEV = "cuda" if torch.cuda.is_available() else "cpu"

# student config (overridable via CLI --HF/--HS/--E/--FL for the scaling series)
HF, HS, EDIM, OUT_SKIP, FL = 84, 32, 28, True, 1


# ------------------------------------------------------------ student model ---
class Student(nn.Module):
    """Two-timescale GRU with aux heads.  Fast = FL stacked GRU layers (cuDNN) run
    over the whole sequence; slow GRU is a masked per-word recurrence over the TOP
    fast states (vectorized input projection for speed)."""
    def __init__(self, HF, HS, E, out_skip=True, aux=True, FL=1):
        super().__init__()
        self.HF, self.HS, self.E, self.out_skip, self.aux, self.FL = \
            HF, HS, E, out_skip, aux, FL
        self.emb  = nn.Embedding(C.V, E)
        self.fast = nn.GRU(E, HF, num_layers=FL, batch_first=True)
        self.slow = nn.GRUCell(HF, HS)
        outin = HF + HS + (E if out_skip else 0)
        self.out = nn.Linear(outin, C.V)
        if aux:
            self.aux2 = nn.Linear(HF + HS, C.V)   # predict char t+2
            self.aux3 = nn.Linear(HF + HS, C.V)   # predict char t+3
            self.wout = nn.Linear(HS, C.V)        # predict next word's first char

    def run_slow(self, hf_seq, bmask):
        B, L, _ = hf_seq.shape; H = self.HS; s = self.slow
        gi_all = torch.addmm(s.bias_ih, hf_seq.reshape(B*L, -1), s.weight_ih.t()
                             ).reshape(B, L, -1)
        Whh_t = s.weight_hh.t(); bhh = s.bias_hh
        hs = hf_seq.new_zeros(B, H); outs = []
        for t in range(L):
            gi = gi_all[:, t]; gh = torch.addmm(bhh, hs, Whh_t)
            r = torch.sigmoid(gi[:, :H] + gh[:, :H])
            z = torch.sigmoid(gi[:, H:2*H] + gh[:, H:2*H])
            n = torch.tanh(gi[:, 2*H:3*H] + r * gh[:, 2*H:3*H])
            cand = (1 - z) * n + z * hs
            m = bmask[:, t:t+1]
            hs = m * cand + (1.0 - m) * hs
            outs.append(hs)
        return torch.stack(outs, 1)               # [B,L,HS]

    def forward(self, x):
        e = self.emb(x)                           # [B,L,E]
        hf_seq, _ = self.fast(e)                  # top-layer [B,L,HF]
        bmask = (~((x < 26) | (x == C.CAPESC))).float()   # 1 at word boundary
        hs_seq = self.run_slow(hf_seq, bmask)
        feat = torch.cat([hf_seq, hs_seq], -1)
        of = torch.cat([feat, e], -1) if self.out_skip else feat
        logits = self.out(of)
        if not self.aux:
            return logits, None
        aux = (self.aux2(feat), self.aux3(feat), self.wout(hs_seq), bmask)
        return logits, aux


def export_tensors(net):
    sd = net.state_dict()
    def g(k): return sd[k].cpu().numpy()
    t = {"EMB": g("emb.weight"), "OUT": g("out.weight"), "Bout": g("out.bias"),
         "Wis": g("slow.weight_ih"), "Whs": g("slow.weight_hh"),
         "Bis": g("slow.bias_ih"),   "Bhs": g("slow.bias_hh")}
    for l in range(net.FL):
        t[f"Wif{l}"] = g(f"fast.weight_ih_l{l}"); t[f"Whf{l}"] = g(f"fast.weight_hh_l{l}")
        t[f"Bif{l}"] = g(f"fast.bias_ih_l{l}");   t[f"Bhf{l}"] = g(f"fast.bias_hh_l{l}")
    return t


# ----------------------------------------------------------------- teacher ----
class Teacher(nn.Module):
    def __init__(self, H=384, layers=2, E=64):
        super().__init__()
        self.emb = nn.Embedding(C.V, E)
        self.rnn = nn.LSTM(E, H, num_layers=layers, batch_first=True, dropout=0.1)
        self.out = nn.Linear(H, C.V)
    def forward(self, x):
        return self.out(self.rnn(self.emb(x))[0])


# ----------------------------------------------------------------- data prep --
def load_corpus(paths):
    arrs = [C.load_symbols(p) for p in paths if os.path.exists(p)]
    return np.concatenate(arrs)

def next_word_target(data):
    """na[i] = symbol of the next alphabetic char strictly after i (else space)."""
    alpha = (data < 26) | (data == C.CAPESC)
    idx = np.where(alpha)[0]
    n = len(data)
    pos = np.searchsorted(idx, np.arange(n), side="right")
    valid = pos < len(idx)
    na = np.full(n, C.SP, np.int64)
    na[valid] = data[idx[pos[valid].clip(max=len(idx)-1)]]
    return na

def get_data(paths):
    """Hold out a tail from EACH corpus so val matches the train mix (prose+code),
    rather than making val 100% code (which the naive last-N split would do)."""
    trs, vas = [], []
    for p in paths:
        if not os.path.exists(p):
            continue
        a = C.load_symbols(p)
        nv = min(300_000, len(a) // 20)
        trs.append(a[:len(a) - nv]); vas.append(a[len(a) - nv:])
    tr = np.concatenate(trs); va = np.concatenate(vas)
    return (tr, next_word_target(tr)), (va, next_word_target(va))

def make_batcher(data, na, L, B):
    dt = torch.tensor(data, dtype=torch.long)
    nt = torch.tensor(na, dtype=torch.long)
    N = len(data)
    def batch():
        idx = torch.randint(0, N - L - 3, (B,))
        seq = torch.stack([dt[i:i + L + 3] for i in idx])
        x  = seq[:, :L].to(DEV)
        y1 = seq[:, 1:L+1].to(DEV)
        y2 = seq[:, 2:L+2].to(DEV)
        y3 = seq[:, 3:L+3].to(DEV)
        w1 = torch.stack([nt[i:i + L] for i in idx]).to(DEV)
        return x, y1, y2, y3, w1
    return batch


# ------------------------------------------------------- float held-out eval --
@torch.no_grad()
def eval_float(fwd, val, na, L=200, B=256, nb=40):
    N = len(val); dt = torch.tensor(val, dtype=torch.long)
    tot = top1 = top3 = 0; nll = 0.0
    lossf = nn.CrossEntropyLoss(reduction="sum")
    g = torch.Generator().manual_seed(0)
    for _ in range(nb):
        idx = torch.randint(0, N - L - 1, (B,), generator=g)
        x = torch.stack([dt[i:i + L] for i in idx]).to(DEV)
        y = torch.stack([dt[i+1:i+L+1] for i in idx]).to(DEV)
        logits = fwd(x)
        lg = logits.reshape(-1, C.V); yt = y.reshape(-1)
        nll += lossf(lg, yt).item(); tot += yt.numel()
        t3 = lg.topk(3, 1).indices
        top1 += (t3[:, 0] == yt).sum().item()
        top3 += (t3 == yt[:, None]).any(1).sum().item()
    return dict(ppl=float(np.exp(nll/tot)), top1=top1/tot, top3=top3/tot)


# ------------------------------------------ quantized two-timescale eval (np) -
def eval_quant(tt, val_np, npos=80000, seed=0):
    p = tt.p; HF, HS, FLn = tt.HF, tt.HS, tt.FL
    rng = np.random.default_rng(seed)
    B = 256; seqlen = npos // B; N = len(val_np)
    starts = rng.integers(0, N - seqlen - 1, size=B)
    seqs = np.stack([val_np[s:s+seqlen+1] for s in starts])
    hfl = [np.zeros((B, HF), np.float32) for _ in range(FLn)]
    hs = np.zeros((B, HS), np.float32)
    def dq(x, W, S, Bi): return (x @ W.T.astype(np.float32)) * S + Bi
    tot = top1 = top3 = 0; nll = 0.0
    for t in range(seqlen):
        sym = seqs[:, t]; x = p["EMB"][sym].astype(np.float32)
        inp = x
        for l in range(FLn):
            gi = dq(inp, p[f"Wif{l}"], p[f"Wif{l}_s"], p[f"Bif{l}"])
            gh = dq(hfl[l], p[f"Whf{l}"], p[f"Whf{l}_s"], p[f"Bhf{l}"])
            r = C.sig_pade(gi[:,0:HF]+gh[:,0:HF]); z = C.sig_pade(gi[:,HF:2*HF]+gh[:,HF:2*HF])
            n = C.tanh_pade(gi[:,2*HF:3*HF]+r*gh[:,2*HF:3*HF])
            hfl[l] = ((1-z)*n + z*hfl[l]).astype(np.float32); inp = hfl[l]
        hf = hfl[FLn-1]
        bnd = ~((sym < 26) | (sym == C.CAPESC))
        gis = dq(hf, p["Wis"], p["Wis_s"], p["Bis"]); ghs = dq(hs, p["Whs"], p["Whs_s"], p["Bhs"])
        r2 = C.sig_pade(gis[:,0:HS]+ghs[:,0:HS]); z2 = C.sig_pade(gis[:,HS:2*HS]+ghs[:,HS:2*HS])
        n2 = C.tanh_pade(gis[:,2*HS:3*HS]+r2*ghs[:,2*HS:3*HS])
        hs_cand = ((1-z2)*n2 + z2*hs).astype(np.float32)
        hs = np.where(bnd[:,None], hs_cand, hs).astype(np.float32)
        feat = np.concatenate([hf, hs], 1)
        if tt.out_skip: feat = np.concatenate([feat, x], 1)
        logits = dq(feat, p["OUT"], p["OUT_s"], p["Bout"])
        tgt = seqs[:, t+1]
        m = logits.max(1, keepdims=True)
        lse = m[:,0] + np.log(np.exp(logits-m).sum(1))
        nll += (lse - logits[np.arange(B), tgt]).sum()
        order = np.argsort(-logits, 1)[:, :3]
        top1 += (order[:,0]==tgt).sum(); top3 += (order==tgt[:,None]).any(1).sum(); tot += B
    return dict(ppl=float(np.exp(nll/tot)), top1=top1/tot, top3=top3/tot)


# --------------------------------------------------------------------- train --
def train_teacher(train, val, steps, H, layers, E, L, B, lr, seed=1234):
    (tr, tna), (va, vna) = train, val
    torch.manual_seed(seed); np.random.seed(seed)
    net = Teacher(H, layers, E).to(DEV)
    opt = torch.optim.Adam(net.parameters(), lr=lr, weight_decay=1e-5)
    sched = torch.optim.lr_scheduler.CosineAnnealingLR(opt, steps)
    lossf = nn.CrossEntropyLoss()
    batch = make_batcher(tr, tna, L, B); net.train(); t0 = time.time()
    for step in range(steps):
        x, y1, _, _, _ = batch()
        logits = net(x)
        loss = lossf(logits.reshape(-1, C.V), y1.reshape(-1))
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(net.parameters(), 1.0); opt.step(); sched.step()
        if step % 500 == 0:
            print(f"  [teacher] {step:5d} loss {loss.item():.3f} ppl {np.exp(loss.item()):.2f} ({time.time()-t0:.0f}s)")
    net.eval()
    fm = eval_float(lambda x: net(x), va, vna)
    print(f"  [teacher] held-out ppl {fm['ppl']:.3f} t1 {fm['top1']:.3f} t3 {fm['top3']:.3f} "
          f"params {sum(p.numel() for p in net.parameters()):,}")
    torch.save({"sd": net.state_dict(), "cfg": dict(H=H, layers=layers, E=E)},
               os.path.join(HERE, "nn_teacher.pt"))
    json.dump(fm, open(os.path.join(HERE, "nn_teacher_metrics.json"), "w"), indent=1)
    return net

def load_teacher():
    ck = torch.load(os.path.join(HERE, "nn_teacher.pt"), map_location=DEV)
    c = ck["cfg"]; net = Teacher(c["H"], c["layers"], c["E"]).to(DEV)
    net.load_state_dict(ck["sd"]); net.eval()
    return net


def aux_weight(step, max_steps, coef, full_frac, anneal_frac):
    """coef for [0,full); linear coef->0 over [full,anneal); 0 after."""
    f = step / max_steps
    if f < full_frac:   return coef
    if f < anneal_frac: return coef * (anneal_frac - f) / (anneal_frac - full_frac)
    return 0.0

SCHED = "cosine"          # "cosine" (+optional warm restart) or "wsd" (trapezoidal)

def lr_at(step, max_steps, lr0, lr1, lr_min, anneal_frac, warm_restart):
    """cosine lr0->lr_min (+optional SGDR restart at anneal_frac), OR
    WSD/trapezoidal: linear warmup -> LONG constant lr0 -> short cosine decay."""
    if SCHED == "wsd":
        warm = 0.03 * max_steps; dec = 0.85 * max_steps    # decay over last 15%
        if step < warm:
            return lr_min + (lr0 - lr_min) * (step / max(1.0, warm))
        if step < dec:
            return lr0                                     # long constant high LR
        p = (step - dec) / max(1.0, max_steps - dec)
        return lr_min + 0.5*(lr0-lr_min)*(1+math.cos(math.pi*p))
    if not warm_restart:
        p = step / max_steps
        return lr_min + 0.5*(lr0-lr_min)*(1+math.cos(math.pi*p))
    S2 = anneal_frac * max_steps
    if step < S2:
        p = step / S2
        return lr_min + 0.5*(lr0-lr_min)*(1+math.cos(math.pi*p))
    p = (step - S2) / max(1.0, max_steps - S2)
    return lr_min + 0.5*(lr1-lr_min)*(1+math.cos(math.pi*p))


def train_student(train, val, max_steps, L, B, seed, aux=True, aux_coef=0.3,
                  aux_full=0.25, aux_anneal=0.45, distill=False, teacher=None,
                  T=1.5, alpha=0.7, lr0=2e-3, lr1=1.2e-3, lr_min=2e-5,
                  warm_restart=True, eval_every=1000, eval_nb=16, patience=12,
                  quiet=False, tag="", curve_out=None):
    (tr, tna), (va, vna) = train, val
    torch.manual_seed(seed); np.random.seed(seed)
    net = Student(HF, HS, EDIM, OUT_SKIP, aux=aux, FL=FL).to(DEV)
    opt = torch.optim.Adam(net.parameters(), lr=lr0)
    ce = nn.CrossEntropyLoss()
    batch = make_batcher(tr, tna, L, B); t0 = time.time()
    best = {"ppl": 1e9}; best_state = None; since_best = 0; curve = []
    for step in range(max_steps):
        for g in opt.param_groups:
            g["lr"] = lr_at(step, max_steps, lr0, lr1, lr_min, aux_anneal, warm_restart)
        net.train()
        x, y1, y2, y3, w1 = batch()
        logits, auxout = net(x)
        ls = logits.reshape(-1, C.V); yt = y1.reshape(-1)
        if distill:
            with torch.no_grad():
                tl = teacher(x).reshape(-1, C.V)
            kd = F.kl_div(F.log_softmax(ls/T, -1), F.softmax(tl/T, -1),
                          reduction="batchmean") * (T*T)
            loss = alpha*kd + (1-alpha)*ce(ls, yt)
        else:
            loss = ce(ls, yt)
        w = aux_weight(step, max_steps, aux_coef, aux_full, aux_anneal) if aux else 0.0
        if w > 0:
            a2, a3, wl, bmask = auxout
            la = ce(a2.reshape(-1, C.V), y2.reshape(-1)) \
               + ce(a3.reshape(-1, C.V), y3.reshape(-1))
            bm = bmask.reshape(-1) > 0.5
            if bm.any():
                la = la + ce(wl.reshape(-1, C.V)[bm], w1.reshape(-1)[bm])
            loss = loss + w * la
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(net.parameters(), 1.0); opt.step()

        if step % eval_every == 0 or step == max_steps-1:
            net.eval()
            fm = eval_float(lambda z: net(z)[0], va, vna, nb=eval_nb)
            curve.append({"step": step, "ppl": fm["ppl"], "top1": fm["top1"],
                          "top3": fm["top3"], "lr": opt.param_groups[0]["lr"], "aux_w": w})
            improved = fm["ppl"] < best["ppl"] - 1e-4
            if improved:
                best = {"step": step, **fm}; best_state = copy.deepcopy(
                    {k: v.detach().cpu() for k, v in net.state_dict().items()})
                since_best = 0
            else:
                since_best += 1
            if not quiet:
                print(f"  [{tag}] step {step:6d} lr {opt.param_groups[0]['lr']:.2e} "
                      f"auxw {w:.3f} | val ppl {fm['ppl']:.3f} t1 {fm['top1']:.3f} "
                      f"t3 {fm['top3']:.3f} | best {best['ppl']:.3f}@{best.get('step',0)} "
                      f"({time.time()-t0:.0f}s)")
            if since_best >= patience:
                if not quiet: print(f"  [{tag}] early stop at {step} (patience {patience})")
                break
    if best_state is not None:
        net.load_state_dict({k: v.to(DEV) for k, v in best_state.items()})
    net.eval()
    fm = eval_float(lambda z: net(z)[0], va, vna, nb=40)   # full final eval
    if curve_out:
        json.dump({"tag": tag, "best": best, "curve": curve},
                  open(curve_out, "w"), indent=1)
    return net, fm, curve, best


def pack_and_eval(net, va, vna):
    tens = export_tensors(net)
    tmp = os.path.join(HERE, "_tmp")
    C.pack_weights(HF, HS, EDIM, tens, tmp+".bin", tmp+".h", tmp+".json", out_skip=OUT_SKIP, FL=FL)
    tt = C.load_ttmodel(tmp+".bin", tmp+".json")
    qm = eval_quant(tt, va)
    return tens, qm


# --------------------------------------------------------------------- main ---
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--steps", type=int, default=14000)
    ap.add_argument("--seq", type=int, default=96)
    ap.add_argument("--batch", type=int, default=256)
    ap.add_argument("--seed", type=int, default=1337)
    ap.add_argument("--aux_coef", type=float, default=0.3)
    ap.add_argument("--aux_full", type=float, default=0.25)
    ap.add_argument("--aux_anneal", type=float, default=0.45)
    ap.add_argument("--no_aux", action="store_true")
    ap.add_argument("--distill", action="store_true")
    ap.add_argument("--T", type=float, default=1.5)
    ap.add_argument("--alpha", type=float, default=0.7)
    ap.add_argument("--lr", type=float, default=2e-3)       # lr0
    ap.add_argument("--lr1", type=float, default=1.2e-3)    # warm-restart peak
    ap.add_argument("--lr_min", type=float, default=2e-5)
    ap.add_argument("--no_warm", action="store_true")
    ap.add_argument("--eval_every", type=int, default=1000)
    ap.add_argument("--patience", type=int, default=12)
    ap.add_argument("--tag", default="run")
    ap.add_argument("--export", action="store_true")
    ap.add_argument("--train_teacher", action="store_true")
    ap.add_argument("--ablate_aux", action="store_true")
    ap.add_argument("--fair_compare", action="store_true")
    ap.add_argument("--teacher_H", type=int, default=384)
    ap.add_argument("--teacher_layers", type=int, default=2)
    ap.add_argument("--teacher_steps", type=int, default=7000)
    ap.add_argument("--HF", type=int, default=None)
    ap.add_argument("--HS", type=int, default=None)
    ap.add_argument("--E", type=int, default=None)
    ap.add_argument("--FL", type=int, default=None)
    ap.add_argument("--out_prefix", default="nn_weights")   # size-named export base
    ap.add_argument("--sched", default="cosine", choices=["cosine", "wsd"])
    args = ap.parse_args()

    global HF, HS, EDIM, FL, SCHED
    if args.HF: HF = args.HF
    if args.HS: HS = args.HS
    if args.E:  EDIM = args.E
    if args.FL: FL = args.FL
    SCHED = args.sched

    corpora = [os.path.join(HERE, "corpus_big.txt"), os.path.join(HERE, "corpus_code.txt")]
    print("device:", DEV, "V:", C.V, "cfg HF", HF, "HS", HS, "E", EDIM, "FL", FL, "skip", OUT_SKIP)
    train, val = get_data(corpora); (va, vna) = val
    print(f"train {len(train[0]):,}  val {len(va):,} symbols")
    tot, i8, fl = C.count_bytes(HF, HS, EDIM, OUT_SKIP, FL)
    print(f"blob bytes {tot} ({tot/1024:.1f}KB int8 {i8} + f32 {fl*4})  state {FL*HF+HS}f "
          f"macC {C.count_macs_char(HF,HS,EDIM,OUT_SKIP,FL)} macW {C.count_macs_word(HF,HS)}")

    if args.train_teacher:
        train_teacher(train, val, args.teacher_steps, args.teacher_H,
                      args.teacher_layers, 64, args.seq, args.batch, 2e-3)
        return

    common = dict(distill=args.distill, T=args.T, alpha=args.alpha, lr0=args.lr,
                  lr1=args.lr1, lr_min=args.lr_min, warm_restart=not args.no_warm,
                  eval_every=args.eval_every, patience=args.patience)

    if args.fair_compare:
        # FAIR long-horizon test: anneal-then-continue (aux) vs no-aux, SAME budget
        # (same LR schedule incl warm restart), early-stopped on held-out ppl.
        teacher = load_teacher() if args.distill else None
        print(f"\n=== FAIR COMPARE (max {args.steps} steps, distill={args.distill}) ===")
        netA, fmA, cA, bA = train_student(train, val, args.steps, args.seq, args.batch,
            args.seed, aux=True, aux_coef=args.aux_coef, aux_full=args.aux_full,
            aux_anneal=args.aux_anneal, teacher=teacher, tag="aux",
            curve_out=os.path.join(HERE, "nn_curve_aux.json"), **common)
        _, qA = pack_and_eval(netA, va, vna)
        netN, fmN, cN, bN = train_student(train, val, args.steps, args.seq, args.batch,
            args.seed, aux=False, teacher=teacher, tag="noaux",
            curve_out=os.path.join(HERE, "nn_curve_noaux.json"), **common)
        _, qN = pack_and_eval(netN, va, vna)
        print("\n---- FAIR COMPARE result (best-checkpoint, full eval) ----")
        print(f"  aux-anneal : float ppl {fmA['ppl']:.4f} t1 {fmA['top1']:.4f} t3 {fmA['top3']:.4f}"
              f" | int8 ppl {qA['ppl']:.4f} t1 {qA['top1']:.4f} t3 {qA['top3']:.4f} (best@{bA.get('step')})")
        print(f"  no-aux     : float ppl {fmN['ppl']:.4f} t1 {fmN['top1']:.4f} t3 {fmN['top3']:.4f}"
              f" | int8 ppl {qN['ppl']:.4f} t1 {qN['top1']:.4f} t3 {qN['top3']:.4f} (best@{bN.get('step')})")
        print(f"  delta(aux-noaux) float dppl {fmA['ppl']-fmN['ppl']:+.4f} "
              f"dt1 {fmA['top1']-fmN['top1']:+.4f} dt3 {fmA['top3']-fmN['top3']:+.4f}")
        json.dump({"aux": {"float": fmA, "int8": qA, "best": bA},
                   "no_aux": {"float": fmN, "int8": qN, "best": bN}},
                  open(os.path.join(HERE, "nn_aux_ablation.json"), "w"), indent=1)
        # export the better one (by int8 ppl)
        if args.export:
            best_net = netA if qA["ppl"] <= qN["ppl"] else netN
            fm = fmA if qA["ppl"] <= qN["ppl"] else fmN
            qm = qA if qA["ppl"] <= qN["ppl"] else qN
            tens, _ = pack_and_eval(best_net, va, vna)
            _do_export(tens, fm, qm, args);
            print(f"  exported the {'AUX' if best_net is netA else 'NO-AUX'} model")
        return

    teacher = None
    if args.distill:
        teacher = load_teacher(); print("loaded teacher (T=%.1f a=%.2f)" % (args.T, args.alpha))
    print(f"\nTrain student max_steps={args.steps} aux={not args.no_aux} distill={args.distill}")
    net, fm, cv, best = train_student(train, val, args.steps, args.seq, args.batch,
        args.seed, aux=not args.no_aux, aux_coef=args.aux_coef, aux_full=args.aux_full,
        aux_anneal=args.aux_anneal, teacher=teacher, tag=args.tag,
        curve_out=os.path.join(HERE, args.out_prefix + "_curve.json"), **common)
    tens, qm = pack_and_eval(net, va, vna)
    print("\n---- held-out metrics (best checkpoint) ----")
    print(f"best @ step {best.get('step')}")
    print(f"float : ppl {fm['ppl']:.4f} top1 {fm['top1']:.4f} top3 {fm['top3']:.4f}")
    print(f"int8  : ppl {qm['ppl']:.4f} top1 {qm['top1']:.4f} top3 {qm['top3']:.4f}")

    if args.export:
        _do_export(tens, fm, qm, args)


def _do_export(tens, fm, qm, args):
        pre = args.out_prefix
        man, nb = C.pack_weights(HF, HS, EDIM, tens,
            os.path.join(HERE, pre+".bin"), os.path.join(HERE, pre+".h"),
            os.path.join(HERE, pre+".json"), out_skip=OUT_SKIP, FL=FL)
        # flash budget now ~490KB (0x61000..0xdb000 via runtime self-programming)
        assert nb <= 490*1024, f"blob {nb} exceeds ~490KB flash budget"
        assert FL*HF + HS <= 2048, "persistent state exceeds ~8KB"
        state_b = (FL*HF + HS) * 4
        print(f"\nexported {pre}.bin = {nb} B ({nb/1024:.1f}KB) state {state_b}B "
              f"macC {C.count_macs_char(HF,HS,EDIM,OUT_SKIP,FL)}")
        json.dump({"float": fm, "int8": qm, "cfg": dict(HF=HF, HS=HS, E=EDIM, FL=FL,
                   out_skip=OUT_SKIP, bytes=nb, state_bytes=state_b,
                   macc=C.count_macs_char(HF,HS,EDIM,OUT_SKIP,FL)), "args": vars(args)},
                  open(os.path.join(HERE, pre+"_metrics.json"), "w"), indent=1)


if __name__ == "__main__":
    main()
