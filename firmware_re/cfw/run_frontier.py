#!/usr/bin/env python3
"""Unified accuracy-per-flash-KB frontier: dense NN vs pure Markov (orders 2-8,
modified-KN & Witten-Bell) vs sparse Markov — all on ONE consistent held-out set.
(Sparse-pruned NN points are appended by run_sparsenn.py.)  Writes frontier_results.csv."""
import os, json, csv, time
import numpy as np
import nn_common as C
import nn_ngram as NG
from run_ngram import nn_logits_over, metrics

HERE = os.path.dirname(os.path.abspath(__file__))
V = C.V

def load_data():
    corp = [os.path.join(HERE, "corpus_big.txt"), os.path.join(HERE, "corpus_code.txt")]
    trs, vas = [], []
    for p in corp:
        if not os.path.exists(p): continue
        a = C.load_symbols(p); nv = min(300_000, len(a)//20)
        trs.append(a[:len(a)-nv]); vas.append(a[len(a)-nv:])
    return np.concatenate(trs), np.concatenate(vas)

def build_eval(va, B=200, S=400):
    """B sequences from evenly-spaced starts across held-out (covers prose+code)."""
    starts = np.linspace(0, len(va)-S-2, B).astype(np.int64)
    seqs = np.stack([va[s:s+S] for s in starts])
    tgt  = np.stack([va[s+1:s+S+1] for s in starts]).reshape(-1)
    return seqs, tgt

def ctx_codes(seqs, nmax):
    B, S = seqs.shape; out = {}
    for n in range(2, nmax+1):
        k = n-1; codes = np.zeros((B, S), np.int64)
        for j in range(k):
            d = k-1-j; col = np.zeros((B, S), np.int64); col[:, d:] = seqs[:, :S-d]
            codes = codes*V + col
        ok = np.arange(S) >= (k-1)
        out[n] = np.where(ok[None, :], codes, -1).reshape(-1)
    return out

def main():
    t0 = time.time(); rows = []
    tr, va = load_data()
    seqs, tgt = build_eval(va)
    print(f"eval set: {seqs.shape[0]}x{seqs.shape[1]} = {len(tgt):,} positions", flush=True)

    # ---- dense NN candidates (int8) on this eval set ----
    print("\n== dense NN (int8) ==", flush=True)
    for pre in ["nn_64k","nn_128k","nn_256k","nn_256k_fl2","nn_400k","nn_460k"]:
        if not os.path.exists(os.path.join(HERE, pre+".bin")): continue
        tt = C.load_ttmodel(os.path.join(HERE, pre+".bin"), os.path.join(HERE, pre+".json"))
        logit = nn_logits_over(tt, seqs).reshape(-1, V)
        m = logit.max(1, keepdims=True); p = np.exp(logit-m); p /= p.sum(1, keepdims=True)
        ppl,t1,t3 = metrics(p, tgt)
        kb = os.path.getsize(os.path.join(HERE, pre+".bin"))/1024
        print(f"  {pre:12s} {kb:6.1f}KB  ppl {ppl:6.3f} t1 {t1:.3f} t3 {t3:.3f}", flush=True)
        rows.append(dict(approach="dense_nn", name=pre, kb=round(kb,1), ppl=round(ppl,3),
                         t1=round(t1,4), t3=round(t3,4)))

    # ---- Markov: build 8-gram once ----
    print("\n== building 8-gram ==", flush=True)
    ng = NG.Ngram(N=8, D=0.75).fit(tr)
    print(f"  built ({time.time()-t0:.0f}s)", flush=True)
    cc_full = ctx_codes(seqs, 8)

    # pure Markov: orders 2..8, modified-KN and Witten-Bell, exact packed KB
    for smoothing in ["mkn", "wb"]:
        print(f"\n== pure Markov ({smoothing}) ==", flush=True)
        for order in range(2, 9):
            cc = {n: cc_full[n] for n in range(2, order+1)}
            p = ng.dist(cc, smoothing=smoothing); p = p/p.sum(1, keepdims=True)
            ppl,t1,t3 = metrics(p, tgt)
            kb = ng.packed_bytes(min_count=1, upto=order)[0]/1024
            print(f"  {order}-gram {kb:8.1f}KB  ppl {ppl:6.3f} t1 {t1:.3f} t3 {t3:.3f}", flush=True)
            rows.append(dict(approach=f"markov_{smoothing}", name=f"{order}gram", kb=round(kb,1),
                             ppl=round(ppl,3), t1=round(t1,4), t3=round(t3,4)))

    # sparse Markov: 8-gram pruned to fit small budgets
    print("\n== sparse Markov (8-gram pruned to budget, mkn) ==", flush=True)
    for target_kb in [64, 128, 256, 460]:
        # raise min_count until packed table <= target
        mc = 1
        while True:
            kb = ng.packed_bytes(min_count=mc, upto=8)[0]/1024
            if kb <= target_kb or mc > 200: break
            mc += 1
        p = ng.dist(cc_full, smoothing='mkn', min_count=mc); p = p/p.sum(1, keepdims=True)
        ppl,t1,t3 = metrics(p, tgt)
        print(f"  target {target_kb}KB -> min_count {mc}, actual {kb:.1f}KB, ppl {ppl:6.3f} t1 {t1:.3f} t3 {t3:.3f}", flush=True)
        rows.append(dict(approach="markov_sparse", name=f"8gram_mc{mc}_{target_kb}KB",
                         kb=round(kb,1), ppl=round(ppl,3), t1=round(t1,4), t3=round(t3,4)))

    with open(os.path.join(HERE, "frontier_results.csv"), "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["approach","name","kb","ppl","t1","t3"])
        w.writeheader(); w.writerows(rows)
    print(f"\nwrote frontier_results.csv ({len(rows)} rows, {time.time()-t0:.0f}s)", flush=True)

if __name__ == "__main__":
    main()
