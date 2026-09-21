#!/usr/bin/env python3
"""Count-based char n-gram for the 72-vocab task, with three smoothings and an
EXACT deployable-table-size model, for the accuracy-per-flash-KB frontier.

Smoothings (all give proper, normalized interpolated distributions):
  'ad'  - interpolated absolute discounting (single discount D)   [KN-style]
  'wb'  - interpolated Witten-Bell
  'mkn' - interpolated *modified* Kneser-Ney (3 discounts D1/D2/D3+ from
          count-of-counts; per-context backoff mass)

Storage model (`packed_bytes`): device stores, for orders 2..N, the pruned
(context, successor, int8-logprob) entries in a CSR-style layout —
  successors[]  1 byte each,  probs[]  1 byte each,  and per distinct context a
  packed key (7 bits/symbol) + a uint32 offset — so the exact flash cost of a
  given (order, count-threshold) is computed, not guessed.
"""
import numpy as np
import nn_common as C

V = C.V

class Ngram:
    def __init__(self, N=6, D=0.75):
        self.N = N; self.D = D; self.orders = {}

    def fit(self, data):
        data = np.asarray(data, np.int64)
        uni = np.bincount(data, minlength=V).astype(np.float64)
        self.uni = uni / uni.sum()
        for n in range(2, self.N + 1):
            k = n - 1
            ctx = np.zeros(len(data) - k, np.int64)
            for j in range(k):
                ctx = ctx * V + data[j:len(data) - k + j]
            nxt = data[k:]
            pair = ctx * V + nxt
            pk, pc = np.unique(pair, return_counts=True)
            pctx = pk // V
            cu, cidx, ccnt = np.unique(pctx, return_index=True, return_counts=True)
            pcf = pc.astype(np.float64)
            ctot = np.add.reduceat(pcf, cidx)
            cN1 = np.add.reduceat((pc == 1).astype(np.float64), cidx)
            cN2 = np.add.reduceat((pc == 2).astype(np.float64), cidx)
            cnd = ccnt.astype(np.float64)
            # modified-KN discounts from count-of-counts
            n1 = float((pc == 1).sum()); n2 = float((pc == 2).sum())
            n3 = float((pc == 3).sum()); n4 = float((pc == 4).sum())
            Y = n1 / (n1 + 2*n2) if (n1 + 2*n2) > 0 else 0.5
            D1 = 1 - 2*Y*n2/n1 if n1 > 0 else 0.5
            D2 = 2 - 3*Y*n3/n2 if n2 > 0 else 1.0
            D3 = 3 - 4*Y*n4/n3 if n3 > 0 else 1.5
            self.orders[n] = dict(pk=pk, pc=pcf, pctx=pctx, cu=cu, ctot=ctot,
                                  cnd=cnd, cN1=cN1, cN2=cN2,
                                  D1=max(D1,0.0), D2=max(D2,0.0), D3=max(D3,0.0))
        return self

    def dist(self, ctx_codes_by_order, smoothing='mkn', min_count=1):
        M = len(next(iter(ctx_codes_by_order.values())))
        p = np.tile(self.uni, (M, 1))
        for n in range(2, self.N + 1):
            if n not in ctx_codes_by_order: continue
            o = self.orders[n]; codes = ctx_codes_by_order[n]
            higher = np.zeros((M, V)); gamma = np.ones(M)
            pos = np.searchsorted(o["cu"], codes)
            valid = (pos < len(o["cu"])) & (o["cu"][np.clip(pos,0,len(o["cu"])-1)] == codes)
            D1, D2, D3 = o["D1"], o["D2"], o["D3"]
            for i in np.nonzero(valid)[0]:
                c = codes[i]
                lo = np.searchsorted(o["pk"], c*V); hi = np.searchsorted(o["pk"], c*V+V)
                chars = (o["pk"][lo:hi] % V); cnts = o["pc"][lo:hi]
                if min_count > 1:                       # pruned deployed table
                    m = cnts >= min_count
                    if not m.any(): valid[i] = False; continue
                    chars = chars[m]; cnts = cnts[m]
                tot = cnts.sum(); nd = len(cnts)
                if smoothing == 'ad':
                    higher[i, chars] = np.maximum(cnts - self.D, 0.0) / tot
                    gamma[i] = (self.D * nd) / tot
                elif smoothing == 'wb':
                    higher[i, chars] = cnts / (tot + nd)
                    gamma[i] = nd / (tot + nd)
                else:  # mkn
                    disc = np.where(cnts == 1, D1, np.where(cnts == 2, D2, D3))
                    higher[i, chars] = np.maximum(cnts - disc, 0.0) / tot
                    N1 = (cnts == 1).sum(); N2 = (cnts == 2).sum(); N3 = (cnts >= 3).sum()
                    gamma[i] = (D1*N1 + D2*N2 + D3*N3) / tot
            p = np.where(valid[:, None], higher + gamma[:, None] * p, p)
        return p

    def packed_bytes(self, min_count=1, upto=None, quant_bytes=1):
        """Exact deployable flash bytes for orders 2..upto with count>=min_count."""
        upto = upto or self.N
        total = 0; per = {}
        for n in range(2, upto + 1):
            o = self.orders[n]; keep = o["pc"] >= min_count
            E = int(keep.sum())
            kept_ctx = np.unique(o["pctx"][keep])
            Cn = len(kept_ctx)
            keybytes = -(-(n-1)*7 // 8)                 # ceil((n-1)*7/8) bits->bytes
            b = E*(1 + quant_bytes) + Cn*(keybytes + 4)
            per[n] = dict(entries=E, contexts=Cn, bytes=b)
            total += b
        return total, per
