#!/usr/bin/env python3
"""Controlled probe: UNROLLED rank-1 (serial) residual block vs STANDARD (parallel)
residual block, at MATCHED params and MATCHED MAC/char, on a tiny char testbed.

Shared backbone (identical for both): emb-sum of last k chars -> state x in R^d ->
ONE residual block -> Linear(d,V).  Only the block differs; both use the SAME
parameters B[h,d], A[h,d], b[h] (identical init), params = 2dh+h, MACs = 2dh:
  STANDARD (parallel): a = relu(x @ B^T + b);  x = x + a @ A        (all h units see the same x)
  UNROLLED (serial):   for i: s = relu(x . B[i] + b[i]); x = x + s * A[i]   (x updated each step -> depth-h)

Runs several tiny sizes x >=5 seeds each; reports held-out ppl mean +- std + top-1.
The user suspects the serial variant has higher variance; we quantify it."""
import os, sys, csv, time
import numpy as np
import torch, torch.nn as nn
import nn_common as C
from run_frontier import build_eval, load_data

HERE = os.path.dirname(os.path.abspath(__file__)); DEV = "cuda" if torch.cuda.is_available() else "cpu"
V = C.V; K = 4
CSV = os.path.join(HERE, "rank1_results.csv")

class ResNet(nn.Module):
    def __init__(self, d, h, variant, scaleA=0.05):
        super().__init__(); self.d, self.h, self.variant = d, h, variant
        self.emb = nn.Embedding(V, d)
        self.B = nn.Parameter(torch.randn(h, d) / (d**0.5))
        self.A = nn.Parameter(torch.randn(h, d) * scaleA)
        self.b = nn.Parameter(torch.zeros(h))
        self.out = nn.Linear(d, V)
    def forward(self, ctx):                       # ctx [Bt,K]
        x = self.emb(ctx).sum(1)                  # [Bt,d]
        if self.variant == "standard":
            a = torch.relu(x @ self.B.t() + self.b)   # [Bt,h]
            x = x + a @ self.A                        # [Bt,d]
        else:                                     # unrolled rank-1, serial
            for i in range(self.h):
                s = torch.relu(x @ self.B[i] + self.b[i])     # [Bt]
                x = x + s.unsqueeze(1) * self.A[i].unsqueeze(0)
        return self.out(x)

def batcher(data, B):
    dt = torch.tensor(data, dtype=torch.long); N = len(data)
    def b():
        i = torch.randint(K, N-2, (B,))
        ctx = torch.stack([dt[i-K+1+j] for j in range(K)], 1).to(DEV)
        return ctx, dt[i+1].to(DEV)
    return b

def evalppl(net, seqs, tgt):
    net.eval(); B, S = seqs.shape
    sq = torch.tensor(seqs, dtype=torch.long)
    pad = torch.full((B, K-1), C.SP, dtype=torch.long)
    ext = torch.cat([pad, sq], 1)
    ctxs = torch.stack([ext[:, j:j+S] for j in range(K)], -1).reshape(-1, K).to(DEV)
    with torch.no_grad():
        lg = net(ctxs).float().cpu().numpy()
    m = lg.max(1, keepdims=True); pr = np.exp(lg-m); pr /= pr.sum(1, keepdims=True)
    nll = -np.log(pr[np.arange(len(tgt)), tgt]+1e-12).mean()
    return float(np.exp(nll)), float((np.argmax(pr,1)==tgt).mean())

def append(row, fields):
    ex = os.path.exists(CSV) and os.path.getsize(CSV) > 0
    with open(CSV, "a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        if not ex: w.writeheader()
        w.writerow(row)

def done():
    if not os.path.exists(CSV): return set()
    return {(r["variant"], r["size"], r["seed"]) for r in csv.DictReader(open(CSV))}

def main():
    t0 = time.time()
    tr, va = load_data(); seqs, tgt = build_eval(va)
    STEPS, SEEDS = 6000, [0,1,2,3,4]
    SIZES = [("d32_h32", 32,32), ("d48_h64", 48,64), ("d32_h64", 32,64)]
    fields = ["variant","size","seed","params","macs","ppl","t1"]
    have = done()
    agg = {}
    for sname, d, h in SIZES:
        for variant in ["standard", "unrolled"]:
            ppls, t1s = [], []
            for seed in SEEDS:
                key = (variant, sname, str(seed))
                if key in have:
                    r = [x for x in csv.DictReader(open(CSV)) if (x["variant"],x["size"],x["seed"])==key][0]
                    ppls.append(float(r["ppl"])); t1s.append(float(r["t1"])); continue
                torch.manual_seed(seed)
                net = ResNet(d, h, variant).to(DEV)
                opt = torch.optim.Adam(net.parameters(), lr=2e-3)
                sch = torch.optim.lr_scheduler.CosineAnnealingLR(opt, STEPS)
                ce = nn.CrossEntropyLoss(); b = batcher(tr, 512); net.train()
                for step in range(STEPS):
                    ctx,y = b(); loss = ce(net(ctx), y)
                    opt.zero_grad(); loss.backward(); opt.step(); sch.step()
                ppl,t1 = evalppl(net, seqs, tgt)
                params = 2*d*h + h; macs = 2*d*h
                append(dict(variant=variant,size=sname,seed=seed,params=params,macs=macs,
                            ppl=round(ppl,3),t1=round(t1,4)), fields)
                ppls.append(ppl); t1s.append(t1)
                print(f"  {variant:9s} {sname} seed{seed}: ppl {ppl:.3f} t1 {t1:.3f} ({time.time()-t0:.0f}s)", flush=True)
            agg[(variant,sname)] = (np.mean(ppls), np.std(ppls), np.mean(t1s))
    # summary table
    print("\n==== RANK-1 vs STANDARD (ppl mean +- std over seeds, top-1) ====", flush=True)
    print(f"{'size':10s} {'standard ppl':>20s} {'unrolled ppl':>20s} {'std t1':>7s} {'unr t1':>7s}", flush=True)
    for sname,_,_ in SIZES:
        st = agg[("standard",sname)]; un = agg[("unrolled",sname)]
        print(f"{sname:10s} {st[0]:8.3f} +-{st[1]:5.3f}      {un[0]:8.3f} +-{un[1]:5.3f}   "
              f"{st[2]:.3f}  {un[2]:.3f}", flush=True)
    # markers for the watcher (use the mid size)
    st = agg[("standard","d48_h64")]; un = agg[("unrolled","d48_h64")]
    print(f"float : ppl {st[0]:.4f} (standard d48_h64)  vs  {un[0]:.4f} (unrolled)", flush=True)
    print(f"int8  : ppl {st[0]:.4f} std+-{st[1]:.3f} / unrolled {un[0]:.4f}+-{un[1]:.3f}", flush=True)
    print(f"rank1 done ({time.time()-t0:.0f}s)", flush=True)

if __name__ == "__main__":
    main()
