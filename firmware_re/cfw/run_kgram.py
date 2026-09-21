#!/usr/bin/env python3
"""Fixed-context k-gram neural LM (Bengio-NPLM style) on the 72-vocab task, placed
on the same accuracy-per-flash-KB frontier.  Positional embedding [k,V,D]: look up
emb[j][char] for each of the last k chars; COMBINE by sum (compact) or concat
(k*D wide); feed an MLP head -> next char.  Sweep k/D/H/layers/combine.  Also test
whether interpolating it with the dense GRU helps (complementarity, like the n-gram
test).  No recurrent state (just buffer last k chars).  Checkpoints per config to
kgram_results.csv; appends frontier rows.  Detached-driver friendly."""
import os, sys, csv, time
import numpy as np
import torch, torch.nn as nn
import nn_common as C
from run_frontier import build_eval, load_data
from run_ngram import nn_logits_over

HERE = os.path.dirname(os.path.abspath(__file__)); DEV = "cuda" if torch.cuda.is_available() else "cpu"
V = C.V
CSV = os.path.join(HERE, "kgram_results.csv")
FR  = os.path.join(HERE, "frontier_results.csv")

class KGramMLP(nn.Module):
    def __init__(self, k, D, H, layers, combine):
        super().__init__(); self.k, self.combine = k, combine
        self.pos = nn.Parameter(0.02*torch.randn(k, V, D))
        inp = D if combine == "sum" else k*D
        mods = [nn.Linear(inp, H), nn.ReLU()]
        for _ in range(layers-1): mods += [nn.Linear(H, H), nn.ReLU()]
        mods += [nn.Linear(H, V)]
        self.mlp = nn.Sequential(*mods)
    def forward(self, ctx):                       # ctx [B,k] long (oldest..newest)
        B = ctx.shape[0]
        e = torch.stack([self.pos[j][ctx[:, j]] for j in range(self.k)], 1)  # [B,k,D]
        x = e.sum(1) if self.combine == "sum" else e.reshape(B, -1)
        return self.mlp(x)

def kb_and_macs(net, k, D, H, layers, combine):
    inp = D if combine == "sum" else k*D
    i8 = 0
    for m in net.mlp:
        if isinstance(m, nn.Linear): i8 += m.weight.numel()
    fl = k*V*D                                    # pos emb (float)
    for m in net.mlp:
        if isinstance(m, nn.Linear): fl += m.bias.numel()
    macs = inp*H + (layers-1)*H*H + H*V
    return (i8 + fl*4)/1024.0, macs

def make_batcher(data, k, B):
    dt = torch.tensor(data, dtype=torch.long); N = len(data)
    def batch():
        i = torch.randint(k, N-2, (B,))
        ctx = torch.stack([dt[i-k+1+j] for j in range(k)], 1).to(DEV)   # [B,k]
        y = dt[i+1].to(DEV)
        return ctx, y
    return batch

def eval_probs(net, seqs, tgt, k, fakequant=True):
    net.eval(); B, S = seqs.shape
    orig = {}
    if fakequant:
        for name, p in net.named_parameters():
            if "mlp" in name and p.dim() == 2:
                orig[name] = p.data.clone()
                amax = p.data.abs().amax(1, keepdim=True).clamp_min(1e-8); s = amax/127
                p.data = torch.round(p.data/s).clamp(-127,127)*s
    sq = torch.tensor(seqs, dtype=torch.long)
    # per-position k-context (pad start with space=36)
    pad = torch.full((B, k-1), C.SP, dtype=torch.long)
    ext = torch.cat([pad, sq], 1)                 # [B, k-1+S]
    ctxs = torch.stack([ext[:, j:j+S] for j in range(k)], -1).reshape(-1, k).to(DEV)  # [B*S,k]
    with torch.no_grad():
        logit = net(ctxs).float().cpu().numpy()
    if fakequant:
        for name, p in net.named_parameters():
            if name in orig: p.data = orig[name]
    m = logit.max(1, keepdims=True); pr = np.exp(logit-m); pr /= pr.sum(1, keepdims=True)
    return pr

def metrics(pr, tgt):
    nll = -np.log(pr[np.arange(len(tgt)), tgt]+1e-12).mean()
    o = np.argsort(-pr,1)[:,:3]
    return float(np.exp(nll)), float((o[:,0]==tgt).mean()), float((o==tgt[:,None]).any(1).mean())

def append(path, row, fields):
    ex = os.path.exists(path) and os.path.getsize(path) > 0
    with open(path, "a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        if not ex: w.writeheader()
        w.writerow(row)

def done_names():
    if not os.path.exists(CSV): return set()
    return {r["name"] for r in csv.DictReader(open(CSV))}

def main():
    t0 = time.time()
    tr, va = load_data(); seqs, tgt = build_eval(va)
    STEPS = 15000
    CFGS = [
        ("sum_k8_D64_H256_L2",   dict(k=8,  D=64,  H=256, layers=2, combine="sum")),
        ("concat_k4_D64_H256_L2",dict(k=4,  D=64,  H=256, layers=2, combine="concat")),
        ("concat_k8_D48_H256_L2",dict(k=8,  D=48,  H=256, layers=2, combine="concat")),
        ("concat_k8_D64_H512_L3",dict(k=8,  D=64,  H=512, layers=3, combine="concat")),
        ("concat_k16_D32_H384_L2",dict(k=16, D=32, H=384, layers=2, combine="concat")),
        ("sum_k16_D128_H512_L2", dict(k=16, D=128, H=512, layers=2, combine="sum")),
    ]
    done = done_names()
    best = None
    for name, c in CFGS:
        if name in done:
            print(f"skip {name}", flush=True); continue
        torch.manual_seed(0)
        net = KGramMLP(**c).to(DEV)
        opt = torch.optim.Adam(net.parameters(), lr=1.5e-3)
        sch = torch.optim.lr_scheduler.CosineAnnealingLR(opt, STEPS)
        ce = nn.CrossEntropyLoss(); batch = make_batcher(tr, c["k"], 512); net.train()
        for step in range(STEPS):
            ctx, y = batch()
            loss = ce(net(ctx), y)
            opt.zero_grad(); loss.backward(); opt.step(); sch.step()
            if step % 5000 == 0:
                print(f"  {name} step {step} loss {loss.item():.3f} ({time.time()-t0:.0f}s)", flush=True)
        pr = eval_probs(net, seqs, tgt, c["k"], fakequant=True)
        ppl,t1,t3 = metrics(pr, tgt)
        kb, macs = kb_and_macs(net, **c)
        append(CSV, dict(name=name, kb=round(kb,1), macs=macs, ppl=round(ppl,3),
                         t1=round(t1,4), t3=round(t3,4)),
               ["name","kb","macs","ppl","t1","t3"])
        append(FR, dict(approach="kgram_mlp", name=name, kb=round(kb,1), ppl=round(ppl,3),
                        t1=round(t1,4), t3=round(t3,4)),
               ["approach","name","kb","ppl","t1","t3"])
        print(f"  {name}: {kb:.1f}KB macC {macs} ppl {ppl:.3f} t1 {t1:.3f} t3 {t3:.3f} [appended]", flush=True)
        if best is None or ppl < best[1]: best = (name, ppl, pr, c)

    # ---- does the k-gram MLP help the dense GRU? (interpolation complementarity test) ----
    if best is not None and "kgram_interp_nn460k" not in done_names():
        name, bppl, pr_kg, c = best
        tt = C.load_ttmodel(os.path.join(HERE,"nn_460k.bin"), os.path.join(HERE,"nn_460k.json"))
        logit = nn_logits_over(tt, seqs).reshape(-1, V)
        m = logit.max(1, keepdims=True); p_nn = np.exp(logit-m); p_nn /= p_nn.sum(1, keepdims=True)
        nnppl,_,_ = metrics(p_nn, tgt)
        bestlam = None
        for lam in [0.6,0.7,0.8,0.9,0.95,1.0]:
            ip,it1,it3 = metrics(lam*p_nn + (1-lam)*pr_kg, tgt)
            if bestlam is None or ip < bestlam[1]: bestlam = (lam, ip, it1, it3)
            print(f"  interp lam={lam}: ppl {ip:.3f}", flush=True)
        append(CSV, dict(name="kgram_interp_nn460k", kb=0, macs=0, ppl=round(bestlam[1],3),
                         t1=round(bestlam[2],4), t3=round(bestlam[3],4)),
               ["name","kb","macs","ppl","t1","t3"])
        print(f"  GRU(nn_460k) alone {nnppl:.3f}; +bestKgram interp -> {bestlam[1]:.3f} "
              f"(lam={bestlam[0]}); best standalone kgram={name} {bppl:.3f}", flush=True)
    print(f"kgram done ({time.time()-t0:.0f}s)", flush=True)

if __name__ == "__main__":
    main()
