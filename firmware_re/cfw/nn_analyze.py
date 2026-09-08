#!/usr/bin/env python3
"""Post-hoc analysis of the deployed quantized model:
  1) magnitude-pruning sweep on the recurrent matrices (Whh,Wih) -> sparsity vs
     held-out ppl/top-1/top-3, to judge whether a CSR sparse forward is worth it.

Operates directly on nn_weights.bin / nn_manifest.json (the int8 weights that ship).
"""
import os, copy, json
import numpy as np
import nn_common as C
from nn_train import get_data, eval_quant

HERE = os.path.dirname(os.path.abspath(__file__))


def prune_rows(q, frac):
    """Zero the smallest-|value| entries per output row (row-wise magnitude prune)."""
    if frac <= 0:
        return q
    q = q.copy()
    a = np.abs(q.astype(np.int32))
    k = int(round(frac * q.shape[1]))
    if k <= 0:
        return q
    idx = np.argpartition(a, k - 1, axis=1)[:, :k]
    np.put_along_axis(q, idx, 0, axis=1)
    return q


def main():
    corpus = os.path.join(HERE, "corpus_big.txt")
    _, val = get_data(corpus); val_np = val.numpy()
    base = C.load_qmodel(os.path.join(HERE, "nn_weights.bin"),
                         os.path.join(HERE, "nn_manifest.json"))
    print(f"model {base.arch} L{base.layers} H{base.Hs} E{base.E} "
          f"out_skip={base.out_skip}")
    print(f"{'sparsity':>9s} {'ppl':>7s} {'top1':>6s} {'top3':>6s}  {'nz-recur':>10s}")
    total_rec = sum(base.p[f'Whh{l}'].size + base.p[f'Wih{l}'].size
                    for l in range(base.layers))
    for frac in [0.0, 0.3, 0.5, 0.6, 0.7, 0.8, 0.9]:
        qm = copy.deepcopy(base)
        nz = 0
        for l in range(qm.layers):
            qm.p[f"Whh{l}"] = prune_rows(qm.p[f"Whh{l}"], frac)
            qm.p[f"Wih{l}"] = prune_rows(qm.p[f"Wih{l}"], frac)
            nz += int((qm.p[f"Whh{l}"] != 0).sum() + (qm.p[f"Wih{l}"] != 0).sum())
        m = eval_quant(qm, val_np, npos=40000)
        print(f"{frac:9.2f} {m['ppl']:7.3f} {m['top1']:6.3f} {m['top3']:6.3f}  "
              f"{nz/total_rec:10.3f}")


if __name__ == "__main__":
    main()
