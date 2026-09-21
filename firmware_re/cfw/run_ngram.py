#!/usr/bin/env python3
"""N-gram / Markov hybrid study (option a: static interpolation with the NN).
Reports: n-gram-alone ppl by order, on-device table-KB estimate, NN vs NN+ngram
ppl/top-1/top-3 (lambda sweep), and ppl-gain-per-KB vs spending KB on more NN."""
import os, sys, json, time
import numpy as np
import nn_common as C
import nn_ngram as NG

HERE = os.path.dirname(os.path.abspath(__file__))
V = C.V
NN_PREFIX = sys.argv[1] if (len(sys.argv) > 1 and not sys.argv[1].startswith("-")) else "nn_64k"
NMAX = int(sys.argv[2]) if (len(sys.argv) > 2 and sys.argv[2].isdigit()) else 6


def load_data():
    corp = [os.path.join(HERE, "corpus_big.txt"), os.path.join(HERE, "corpus_code.txt")]
    trs, vas = [], []
    for p in corp:
        if not os.path.exists(p): continue
        a = C.load_symbols(p); nv = min(300_000, len(a)//20)
        trs.append(a[:len(a)-nv]); vas.append(a[len(a)-nv:])
    return np.concatenate(trs), np.concatenate(vas)


def nn_logits_over(tt, seqs):
    """int8 two-timescale forward over given [B,S] sequences -> logits[B,S,V]."""
    p = tt.p; HF, HS, FLn = tt.HF, tt.HS, tt.FL
    B, S = seqs.shape
    hfl = [np.zeros((B, HF), np.float32) for _ in range(FLn)]
    hs = np.zeros((B, HS), np.float32)
    def dq(x, W, Sc, Bi): return (x @ W.T.astype(np.float32)) * Sc + Bi
    out = np.zeros((B, S, V), np.float32)
    for t in range(S):
        sym = seqs[:, t]; x = p["EMB"][sym].astype(np.float32); inp = x
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
        hsc = ((1-z2)*n2 + z2*hs).astype(np.float32)
        hs = np.where(bnd[:,None], hsc, hs).astype(np.float32)
        feat = np.concatenate([hf, hs], 1)
        if tt.out_skip: feat = np.concatenate([feat, x], 1)
        out[:, t] = dq(feat, p["OUT"], p["OUT_s"], p["Bout"])
    return out


def metrics(prob, tgt):
    eps = 1e-12
    nll = -np.log(prob[np.arange(len(tgt)), tgt] + eps).mean()
    order = np.argsort(-prob, 1)[:, :3]
    return float(np.exp(nll)), float((order[:,0]==tgt).mean()), float((order==tgt[:,None]).any(1).mean())


def main():
    t0 = time.time()
    tr, va = load_data()
    print(f"train {len(tr):,} val {len(va):,}  building {NMAX}-gram ...", flush=True)
    ng = NG.Ngram(N=NMAX, D=0.75).fit(tr)
    print(f"built in {time.time()-t0:.0f}s", flush=True)

    B, S = 120, 320
    off = 1000
    seqs = va[off:off+B*S].reshape(B, S)
    tgt = va[off+1:off+B*S+1].reshape(B, S).reshape(-1)

    def ctx_codes(nmax):
        # context for predicting the char AFTER position t = the k=n-1 chars ENDING
        # at t inclusive (seqs[:,t-k+1..t]), MSB first -> matches fit()'s encoding.
        out = {}
        for n in range(2, nmax+1):
            k = n-1; codes = np.zeros((B, S), np.int64)
            for j in range(k):
                d = k-1-j; col = np.zeros((B, S), np.int64)
                col[:, d:] = seqs[:, :S-d]
                codes = codes*V + col
            ok = np.arange(S) >= (k-1)
            out[n] = np.where(ok[None, :], codes, -1).reshape(-1)   # -1 -> backs off
        return out

    # --- n-gram-alone ppl by order ---
    print("\n== n-gram-alone (interpolated abs-discounting) ==", flush=True)
    rows = []
    for nmax in range(2, NMAX+1):
        cc = ctx_codes(nmax)
        p_ng = ng.dist(cc); p_ng = p_ng / p_ng.sum(1, keepdims=True)
        ppl, t1, t3 = metrics(p_ng, tgt)
        e = sum(int((ng.orders[n]["pc"] >= 2).sum()) for n in range(2, nmax+1))
        print(f"  {nmax}-gram: ppl {ppl:6.3f} t1 {t1:.3f} t3 {t3:.3f}  ~{e:,} entries ~{e*2/1024:.0f}KB", flush=True)
        rows.append(dict(order=nmax, ppl=ppl, t1=t1, t3=t3, entries=e, kb=round(e*2/1024, 1)))

    # --- NN alone + interpolation ---
    print(f"\n== NN ({NN_PREFIX}) + n-gram interpolation ==", flush=True)
    man = NN_PREFIX+".json" if os.path.exists(os.path.join(HERE, NN_PREFIX+".json")) else "nn_manifest.json"
    tt = C.load_ttmodel(os.path.join(HERE, NN_PREFIX+".bin"), os.path.join(HERE, man))
    logit = nn_logits_over(tt, seqs).reshape(-1, V)
    m = logit.max(1, keepdims=True); p_nn = np.exp(logit-m); p_nn /= p_nn.sum(1, keepdims=True)
    p_ng = ng.dist(ctx_codes(NMAX)); p_ng = p_ng / p_ng.sum(1, keepdims=True)
    nnppl, nnt1, nnt3 = metrics(p_nn, tgt)
    ngppl, ngt1, ngt3 = metrics(p_ng, tgt)
    print(f"  NN alone   : ppl {nnppl:6.3f} t1 {nnt1:.3f} t3 {nnt3:.3f}", flush=True)
    print(f"  {NMAX}-gram    : ppl {ngppl:6.3f} t1 {ngt1:.3f} t3 {ngt3:.3f}", flush=True)
    best = None
    for lam in [0.5, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95]:
        ppl, t1, t3 = metrics(lam*p_nn + (1-lam)*p_ng, tgt)
        print(f"  interp lam={lam:.2f}: ppl {ppl:6.3f} t1 {t1:.3f} t3 {t3:.3f}", flush=True)
        if best is None or ppl < best['ppl']: best = dict(lam=lam, ppl=ppl, t1=t1, t3=t3)
    e = sum(int((ng.orders[n]["pc"] >= 2).sum()) for n in range(2, NMAX+1))
    out = dict(nn_prefix=NN_PREFIX, nn=dict(ppl=nnppl, t1=nnt1, t3=nnt3),
               ngram_by_order=rows, ngram_full=dict(ppl=ngppl, t1=ngt1, t3=ngt3),
               best_interp=best, ngram_entries=e, ngram_kb=round(e*2/1024, 1))
    json.dump(out, open(os.path.join(HERE, "nn_ngram_results.json"), "w"), indent=1)
    print(f"\nBEST interp lam={best['lam']} ppl {best['ppl']:.3f} vs NN {nnppl:.3f} "
          f"(-{nnppl-best['ppl']:.3f}); ngram ~{e*2/1024:.0f}KB. ({time.time()-t0:.0f}s)", flush=True)

if __name__ == "__main__":
    main()
