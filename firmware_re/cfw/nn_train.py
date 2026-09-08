#!/usr/bin/env python3
"""Full training pipeline for the Azoth on-device char predictor (vocab V=32).

Modes:
  --sweep                 architecture search (hard-label CE, short runs)
  --train_teacher         train a large LSTM teacher -> nn_teacher.pt
  --arch ... --export     train one student config; --distill uses the teacher
  (default)               train one student config and print metrics

Reports held-out perplexity + top-1/top-3 next-char accuracy for float and int8
(or int4) quantized models.  Exports nn_weights.bin / nn_weights.h / nn_manifest.json.

Constraints: recurrent state <=256 float32 (1KB), params <=500KB, ~<=1.5M MAC/step.
"""
import argparse, os, time, json, math
import numpy as np
import torch, torch.nn as nn, torch.nn.functional as F
import nn_common as C

HERE = os.path.dirname(os.path.abspath(__file__))
DEV = "cuda" if torch.cuda.is_available() else "cpu"


# --------------------------------------------------------------- torch model --
class Net(nn.Module):
    def __init__(self, arch, layers, H, E, out_skip=False, dropout=0.0):
        super().__init__()
        self.arch, self.layers, self.H, self.E = arch, layers, H, E
        self.out_skip = out_skip
        self.emb = nn.Embedding(C.V, E)
        rnn = nn.LSTM if arch == "lstm" else nn.GRU
        self.rnn = rnn(E, H, num_layers=layers, batch_first=True,
                       dropout=dropout if layers > 1 else 0.0)
        self.out = nn.Linear(H + (E if out_skip else 0), C.V)

    def forward(self, x, state=None):
        e = self.emb(x)
        y, state = self.rnn(e, state)
        feat = torch.cat([y, e], -1) if self.out_skip else y
        return self.out(feat), state


def export_tensors(net):
    sd = net.state_dict()
    t = {"EMB": sd["emb.weight"].cpu().numpy(),
         "OUT": sd["out.weight"].cpu().numpy(),
         "Bout": sd["out.bias"].cpu().numpy()}
    for l in range(net.layers):
        t[f"Wih{l}"] = sd[f"rnn.weight_ih_l{l}"].cpu().numpy()
        t[f"Whh{l}"] = sd[f"rnn.weight_hh_l{l}"].cpu().numpy()
        t[f"Bih{l}"] = sd[f"rnn.bias_ih_l{l}"].cpu().numpy()
        t[f"Bhh{l}"] = sd[f"rnn.bias_hh_l{l}"].cpu().numpy()
    return t


# ----------------------------------------------------------------- data prep --
def get_data(corpus):
    data = C.load_symbols(corpus)
    n = len(data); n_val = min(500_000, n // 20)
    return (torch.tensor(data[:n - n_val], dtype=torch.long),
            torch.tensor(data[n - n_val:], dtype=torch.long))

def make_batcher(data, L, B):
    N = len(data)
    def batch():
        idx = torch.randint(0, N - L - 1, (B,))
        x = torch.stack([data[i:i + L] for i in idx]).to(DEV)
        y = torch.stack([data[i + 1:i + L + 1] for i in idx]).to(DEV)
        return x, y
    return batch


# ------------------------------------------------------- float held-out eval --
@torch.no_grad()
def eval_float(net, val, L=200, B=256, nb=40):
    net.eval(); N = len(val)
    tot_loss = tot = top1 = top3 = 0
    lossf = nn.CrossEntropyLoss(reduction="sum")
    g = torch.Generator().manual_seed(0)
    for _ in range(nb):
        idx = torch.randint(0, N - L - 1, (B,), generator=g)
        x = torch.stack([val[i:i + L] for i in idx]).to(DEV)
        y = torch.stack([val[i + 1:i + L + 1] for i in idx]).to(DEV)
        logits, _ = net(x)
        lg = logits.reshape(-1, C.V); yt = y.reshape(-1)
        tot_loss += lossf(lg, yt).item(); tot += yt.numel()
        t3 = lg.topk(3, dim=1).indices
        top1 += (t3[:, 0] == yt).sum().item()
        top3 += (t3 == yt[:, None]).any(1).sum().item()
    ce = tot_loss / tot
    return dict(ppl=float(np.exp(ce)), top1=top1 / tot, top3=top3 / tot, ce=ce)


# ------------------------------------------ quantized held-out eval (numpy) ---
def eval_quant(qm, val_np, npos=60000, seed=0):
    arch, layers, Hs = qm.arch, qm.layers, qm.Hs; p = qm.p
    rng = np.random.default_rng(seed)
    B = 256; seqlen = npos // B; N = len(val_np)
    starts = rng.integers(0, N - seqlen - 1, size=B)
    seqs = np.stack([val_np[s:s + seqlen + 1] for s in starts])
    h = [np.zeros((B, H), np.float32) for H in Hs]
    c = [np.zeros((B, H), np.float32) for H in Hs]
    tot = top1 = top3 = 0; nll = 0.0
    for t in range(seqlen):
        sym = seqs[:, t]; x = p["EMB"][sym].astype(np.float32); e0 = x
        for l in range(layers):
            H = Hs[l]
            gi = (x @ p[f"Wih{l}"].T.astype(np.float32) * p[f"Sih{l}"] + p[f"Bih{l}"]).astype(np.float32)
            gh = (h[l] @ p[f"Whh{l}"].T.astype(np.float32) * p[f"Shh{l}"] + p[f"Bhh{l}"]).astype(np.float32)
            if arch == "gru":
                r = C.sig_pade(gi[:, 0:H] + gh[:, 0:H])
                z = C.sig_pade(gi[:, H:2*H] + gh[:, H:2*H])
                n = C.tanh_pade(gi[:, 2*H:3*H] + r * gh[:, 2*H:3*H])
                h[l] = ((1 - z) * n + z * h[l]).astype(np.float32)
            else:
                pre = gi + gh
                i = C.sig_pade(pre[:, 0:H]); f = C.sig_pade(pre[:, H:2*H])
                gg = C.tanh_pade(pre[:, 2*H:3*H]); o = C.sig_pade(pre[:, 3*H:4*H])
                c[l] = (f * c[l] + i * gg).astype(np.float32)
                h[l] = (o * C.tanh_pade(c[l])).astype(np.float32)
            x = h[l]
        feat = np.concatenate([h[layers-1], e0], 1) if qm.out_skip else h[layers-1]
        logits = feat @ p["OUT"].T.astype(np.float32) * p["Sout"] + p["Bout"]
        tgt = seqs[:, t + 1]
        m = logits.max(1, keepdims=True)
        lse = m[:, 0] + np.log(np.exp(logits - m).sum(1))
        nll += (lse - logits[np.arange(B), tgt]).sum()
        order = np.argsort(-logits, axis=1)[:, :3]
        top1 += (order[:, 0] == tgt).sum(); top3 += (order == tgt[:, None]).any(1).sum()
        tot += B
    return dict(ppl=float(np.exp(nll / tot)), top1=top1 / tot, top3=top3 / tot)


# ------------------------------------------------------------------- budgets --
def count_bytes(arch, layers, Hs, E, out_skip=False, rec_bits=8):
    g = 4 if arch == "lstm" else 3
    i8 = 0; fl = C.V * E
    for l in range(layers):
        inp = E if l == 0 else Hs[l-1]
        rb = rec_bits  # int4 still stored 1 byte/elt here (packing note in README)
        i8 += g*Hs[l]*inp + g*Hs[l]*Hs[l]
        fl += g*Hs[l] + g*Hs[l] + g*Hs[l] + g*Hs[l]
    outin = Hs[-1] + (E if out_skip else 0)
    i8 += C.V * outin
    fl += C.V + C.V
    packed_i8 = i8 if rec_bits == 8 else _packed_int4_bytes(arch, layers, Hs, E, out_skip)
    return packed_i8 + fl*4, packed_i8, fl

def _packed_int4_bytes(arch, layers, Hs, E, out_skip):
    g = 4 if arch == "lstm" else 3
    rec = 0
    for l in range(layers):
        inp = E if l == 0 else Hs[l-1]
        rec += g*Hs[l]*inp + g*Hs[l]*Hs[l]
    out = C.V * (Hs[-1] + (E if out_skip else 0))
    return (rec + 1)//2 + out    # recurrent nibble-packed, OUT int8

def count_macs(arch, layers, Hs, E, out_skip=False):
    g = 4 if arch == "lstm" else 3
    mac = 0
    for l in range(layers):
        inp = E if l == 0 else Hs[l-1]
        mac += g*Hs[l]*inp + g*Hs[l]*Hs[l]
    mac += C.V * (Hs[-1] + (E if out_skip else 0))
    return mac


# ------------------------------------------------------- teacher (LSTM) -------
def train_teacher(train, val, val_np, H=512, layers=3, E=96, steps=12000,
                  L=160, B=128, lr=2e-3, seed=1234):
    torch.manual_seed(seed); np.random.seed(seed)
    net = Net("lstm", layers, H, E, out_skip=False, dropout=0.1).to(DEV)
    opt = torch.optim.Adam(net.parameters(), lr=lr, weight_decay=1e-5)
    sched = torch.optim.lr_scheduler.CosineAnnealingLR(opt, steps)
    lossf = nn.CrossEntropyLoss()
    batch = make_batcher(train, L, B); net.train(); t0 = time.time()
    for step in range(steps):
        x, y = batch()
        logits, _ = net(x)
        loss = lossf(logits.reshape(-1, C.V), y.reshape(-1))
        opt.zero_grad(); loss.backward()
        torch.nn.utils.clip_grad_norm_(net.parameters(), 1.0)
        opt.step(); sched.step()
        if step % 1000 == 0:
            print(f"  [teacher] step {step:5d} loss {loss.item():.3f} "
                  f"ppl {np.exp(loss.item()):.2f} ({time.time()-t0:.0f}s)")
    fm = eval_float(net, val)
    print(f"  [teacher] held-out ppl {fm['ppl']:.3f} top1 {fm['top1']:.3f} "
          f"top3 {fm['top3']:.3f}  params {sum(p.numel() for p in net.parameters()):,}")
    torch.save({"sd": net.state_dict(), "cfg": dict(arch="lstm", layers=layers,
                H=H, E=E)}, os.path.join(HERE, "nn_teacher.pt"))
    json.dump(fm, open(os.path.join(HERE, "nn_teacher_metrics.json"), "w"), indent=1)
    return net, fm

def load_teacher():
    ck = torch.load(os.path.join(HERE, "nn_teacher.pt"), map_location=DEV)
    c = ck["cfg"]; net = Net(c["arch"], c["layers"], c["H"], c["E"]).to(DEV)
    net.load_state_dict(ck["sd"]); net.eval()
    return net


# --------------------------------------------------------------- train student --
def train_student(arch, layers, H, E, steps, L, B, lr, seed, train, val, val_np,
                  out_skip=False, distill=False, teacher=None, T=3.0, alpha=0.6,
                  rec_bits=8, quiet=False):
    torch.manual_seed(seed); np.random.seed(seed)
    net = Net(arch, layers, H, E, out_skip=out_skip).to(DEV)
    opt = torch.optim.Adam(net.parameters(), lr=lr)
    sched = torch.optim.lr_scheduler.CosineAnnealingLR(opt, steps)
    ce = nn.CrossEntropyLoss()
    batch = make_batcher(train, L, B); net.train(); t0 = time.time()
    for step in range(steps):
        x, y = batch()
        logits, _ = net(x)
        ls = logits.reshape(-1, C.V); yt = y.reshape(-1)
        if distill:
            with torch.no_grad():
                tl, _ = teacher(x); tl = tl.reshape(-1, C.V)
            kd = F.kl_div(F.log_softmax(ls / T, -1), F.softmax(tl / T, -1),
                          reduction="batchmean") * (T * T)
            loss = alpha * kd + (1 - alpha) * ce(ls, yt)
        else:
            loss = ce(ls, yt)
        opt.zero_grad(); loss.backward()
        torch.nn.utils.clip_grad_norm_(net.parameters(), 1.0)
        opt.step(); sched.step()
        if not quiet and step % 1000 == 0:
            print(f"  step {step:5d} loss {loss.item():.3f} ({time.time()-t0:.0f}s)")
    fm = eval_float(net, val)
    Hs = [H]*layers
    tens = export_tensors(net)
    tmp = os.path.join(HERE, "_tmp")
    C.pack_weights(arch, layers, Hs, E, tens, tmp+".bin", tmp+".h", tmp+".json",
                   out_skip=out_skip, rec_bits=rec_bits)
    qm = C.load_qmodel(tmp+".bin", tmp+".json")
    qmet = eval_quant(qm, val_np)
    pb, i8, fl = count_bytes(arch, layers, Hs, E, out_skip, rec_bits)
    info = dict(param_bytes=pb, int8=i8, floats=fl,
                macs=count_macs(arch, layers, Hs, E, out_skip),
                state_floats=(2 if arch == "lstm" else 1)*sum(Hs))
    return net, fm, qmet, info


# ---------------------------------------------------------------------- main --
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--arch", default="gru", choices=["gru", "lstm"])
    ap.add_argument("--layers", type=int, default=1)
    ap.add_argument("--H", type=int, default=256)
    ap.add_argument("--E", type=int, default=64)
    ap.add_argument("--out_skip", action="store_true")
    ap.add_argument("--rec_bits", type=int, default=8, choices=[4, 8])
    ap.add_argument("--steps", type=int, default=15000)
    ap.add_argument("--seq", type=int, default=128)
    ap.add_argument("--batch", type=int, default=256)
    ap.add_argument("--lr", type=float, default=2e-3)
    ap.add_argument("--seed", type=int, default=1337)
    ap.add_argument("--distill", action="store_true")
    ap.add_argument("--T", type=float, default=3.0)
    ap.add_argument("--alpha", type=float, default=0.6)
    ap.add_argument("--corpus", default=os.path.join(HERE, "corpus_big.txt"))
    ap.add_argument("--export", action="store_true")
    ap.add_argument("--sweep", action="store_true")
    ap.add_argument("--train_teacher", action="store_true")
    ap.add_argument("--teacher_H", type=int, default=512)
    ap.add_argument("--teacher_layers", type=int, default=3)
    ap.add_argument("--teacher_steps", type=int, default=12000)
    args = ap.parse_args()

    corpus = args.corpus if os.path.exists(args.corpus) else os.path.join(HERE, "corpus_raw.txt")
    print("corpus:", corpus, "device:", DEV, "V:", C.V)
    train, val = get_data(corpus); val_np = val.numpy()
    print(f"train {len(train):,}  val {len(val):,} symbols")

    if args.train_teacher:
        train_teacher(train, val, val_np, args.teacher_H, args.teacher_layers,
                      96, args.teacher_steps)
        return

    if args.sweep:
        cfgs = [
            ("gru", 1, 256, 64, False), ("gru", 1, 256, 96, False),
            ("gru", 1, 256, 64, True),  ("gru", 2, 128, 64, False),
            ("gru", 2, 128, 96, True),  ("lstm", 1, 128, 64, False),
        ]
        rows = []
        for arch, ly, H, E, sk in cfgs:
            name = f"{arch} L{ly} H{H} E{E}{' skip' if sk else ''}"
            print(f"\n=== {name} ===")
            _, fm, qm, info = train_student(arch, ly, H, E, 5000, args.seq,
                args.batch, args.lr, args.seed, train, val, val_np,
                out_skip=sk, quiet=True)
            rows.append((name, fm, qm, info))
            print(f"  float ppl {fm['ppl']:.3f} t1 {fm['top1']:.3f} t3 {fm['top3']:.3f}"
                  f" | quant ppl {qm['ppl']:.3f} t1 {qm['top1']:.3f} t3 {qm['top3']:.3f}"
                  f" | {info['param_bytes']//1024}KB st{info['state_floats']} "
                  f"mac{info['macs']//1000}k")
        print("\n==== SWEEP SUMMARY (5000 steps, hard-label) ====")
        hdr = f"{'config':20s} {'fppl':>6s} {'ft1':>5s} {'ft3':>5s} {'qppl':>6s} {'qt1':>5s} {'qt3':>5s} {'KB':>4s} {'st':>4s} {'MACk':>6s}"
        print(hdr)
        for name, fm, qm, info in rows:
            print(f"{name:20s} {fm['ppl']:6.3f} {fm['top1']:5.3f} {fm['top3']:5.3f} "
                  f"{qm['ppl']:6.3f} {qm['top1']:5.3f} {qm['top3']:5.3f} "
                  f"{info['param_bytes']//1024:4d} {info['state_floats']:4d} {info['macs']//1000:6d}")
        json.dump([{"name": n, "float": fm, "quant": qm, "info": i} for n, fm, qm, i in rows],
                  open(os.path.join(HERE, "nn_sweep.json"), "w"), indent=1)
        return

    teacher = None
    if args.distill:
        teacher = load_teacher()
        print("loaded teacher for distillation (T=%.1f alpha=%.2f)" % (args.T, args.alpha))
    print(f"\nTraining student {args.arch} L{args.layers} H{args.H} E{args.E}"
          f"{' skip' if args.out_skip else ''} rec_bits={args.rec_bits} "
          f"steps={args.steps} distill={args.distill}")
    net, fm, qm, info = train_student(args.arch, args.layers, args.H, args.E,
        args.steps, args.seq, args.batch, args.lr, args.seed, train, val, val_np,
        out_skip=args.out_skip, distill=args.distill, teacher=teacher,
        T=args.T, alpha=args.alpha, rec_bits=args.rec_bits)
    print("\n---- held-out metrics ----")
    print(f"float : ppl {fm['ppl']:.4f} top1 {fm['top1']:.4f} top3 {fm['top3']:.4f}")
    print(f"quant : ppl {qm['ppl']:.4f} top1 {qm['top1']:.4f} top3 {qm['top3']:.4f}")
    print(f"params {info['param_bytes']} ({info['param_bytes']/1024:.1f}KB) "
          f"state {info['state_floats']}f MAC/step {info['macs']}")

    if args.export:
        Hs = [args.H]*args.layers
        tens = export_tensors(net)
        np.savez(os.path.join(HERE, "nn_student_float.npz"),
                 arch=args.arch, layers=args.layers, H=args.H, E=args.E,
                 out_skip=args.out_skip, **tens)
        man, nb = C.pack_weights(args.arch, args.layers, Hs, args.E,
            tens,
            os.path.join(HERE, "nn_weights.bin"), os.path.join(HERE, "nn_weights.h"),
            os.path.join(HERE, "nn_manifest.json"),
            out_skip=args.out_skip, rec_bits=args.rec_bits)
        pb = info['param_bytes']
        assert pb <= 500*1024, f"params {pb} exceed 500KB"
        assert info['state_floats'] <= 256, "state exceeds 1KB"
        print(f"\nexported nn_weights.bin ({nb} B on flash), nn_weights.h, nn_manifest.json"
              f"  [param budget {pb} B]")
        json.dump({"float": fm, "quant": qm, "info": info, "cfg": vars(args)},
                  open(os.path.join(HERE, "nn_metrics.json"), "w"), indent=1)


if __name__ == "__main__":
    main()
