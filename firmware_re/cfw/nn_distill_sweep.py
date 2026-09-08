#!/usr/bin/env python3
"""Tune distillation (T, alpha) for the fixed student gru L1 H256 E96 skip.
Loads data + teacher once; trains a hard-label baseline and several distill
configs at a reduced step count; prints held-out float+quant metrics.
"""
import os, json
import numpy as np
from nn_train import get_data, train_student, load_teacher, HERE

STEPS = 7000
def main():
    corpus = os.path.join(HERE, "corpus_big.txt")
    train, val = get_data(corpus); val_np = val.numpy()
    teacher = load_teacher()
    cfg = dict(arch="gru", layers=1, H=256, E=96, out_skip=True)
    runs = [
        ("hard",            dict(distill=False)),
        ("T2.0 a0.3",       dict(distill=True, teacher=teacher, T=2.0, alpha=0.3)),
        ("T2.0 a0.5",       dict(distill=True, teacher=teacher, T=2.0, alpha=0.5)),
        ("T4.0 a0.5",       dict(distill=True, teacher=teacher, T=4.0, alpha=0.5)),
        ("T1.5 a0.7",       dict(distill=True, teacher=teacher, T=1.5, alpha=0.7)),
        ("T3.0 a0.3",       dict(distill=True, teacher=teacher, T=3.0, alpha=0.3)),
    ]
    rows = []
    for name, kw in runs:
        _, fm, qm, info = train_student(cfg["arch"], cfg["layers"], cfg["H"],
            cfg["E"], STEPS, 128, 256, 2e-3, 1337, train, val, val_np,
            out_skip=cfg["out_skip"], quiet=True, **kw)
        rows.append((name, fm, qm))
        print(f"{name:12s} float ppl {fm['ppl']:.3f} t1 {fm['top1']:.4f} "
              f"t3 {fm['top3']:.4f} | quant ppl {qm['ppl']:.3f} "
              f"t1 {qm['top1']:.4f} t3 {qm['top3']:.4f}", flush=True)
    print("\n==== DISTILL SWEEP (student gru L1 H256 E96 skip, %d steps) ====" % STEPS)
    for name, fm, qm in rows:
        print(f"{name:12s} fppl {fm['ppl']:.3f} ft1 {fm['top1']:.4f} ft3 {fm['top3']:.4f}")
    json.dump([{"name": n, "float": f, "quant": q} for n, f, q in rows],
              open(os.path.join(HERE, "nn_distill_sweep.json"), "w"), indent=1)

if __name__ == "__main__":
    main()
