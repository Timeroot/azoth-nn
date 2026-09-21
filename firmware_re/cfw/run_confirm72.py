#!/usr/bin/env python3
"""Confirm on the TARGET 72-vocab task whether the testbed's architecture finding
transfers: a param-matched WIDE single GRU vs the two-timescale GRU, both at the
64KB deployment flash budget.  Also a tt_gru no-distill point.  Appends rows to
ablation_results.csv incrementally and logs progress for tailing."""
import os, csv, time
import nn_ablate as A

HERE = os.path.dirname(os.path.abspath(__file__))
V = 72; MODE = "72"
CORP = [os.path.join(HERE, "corpus_big.txt"), os.path.join(HERE, "corpus_code.txt")]
HF, HS, E, L = 84, 32, 28, 96
STEPS, PAT, EE, ENB = 16000, 8, 1000, 16

def wide_H():
    """largest single-GRU H whose deployment blob stays <= ~63.9KB (matched budget)."""
    best = HF
    for h in range(HF, HF+200):
        if A.counts(V, h, 0, E, True, "gru")["bytes"] <= 63936:
            best = h
    return best

def base(**kw):
    c = dict(HF=HF, HS=HS, E=E, skip=True, slow="gru", aux=(), boundary="nonalpha",
             seed=1337, steps=STEPS, L=L, B=256, lr0=2e-3, lr1=1.2e-3, lr_min=2e-5,
             anneal=0.45, warm=True, aux_coef=0.3, aux_full=0.25, eval_every=EE,
             eval_nb=ENB, patience=PAT, T=1.5, alpha=0.3)
    c.update(kw); return c

def append_row(name, r, seed):
    ct = r["counts"]
    row = [name, seed, f"{r['float']['ppl']:.4f}", f"{r['float']['top1']:.4f}",
           f"{r['float']['top3']:.4f}", f"{r['int8']['ppl']:.4f}", f"{r['int8']['top1']:.4f}",
           ct["params"]//1000, ct["state"], ct["macc"]//1000]
    with open(os.path.join(HERE, "ablation_results.csv"), "a", newline="") as f:
        csv.writer(f).writerow(row)

def main():
    HW = wide_H()
    print(f"72-vocab confirm: HF={HF} HS={HS} E={E} wideH={HW} steps={STEPS}", flush=True)
    tr, va = A.get_data(MODE, CORP)
    print(f"train {len(tr[0]):,} val {len(va[0]):,}", flush=True)
    arms = [("single_wide72", base(HS=0, HF=HW)),
            ("tt_gru72",       base())]     # clean arch comparison, same schedule
    teacher = None
    for name, c in arms:
        t0 = time.time()
        use_t = name.endswith("distill")
        if use_t and teacher is None:
            print("training 72-vocab teacher...", flush=True)
            teacher, tfm = A.train_teacher(tr, va, V, 6000, L, 256, H=384)
            print(f"teacher ppl {tfm['ppl']:.3f} t1 {tfm['top1']:.3f}", flush=True)
        net, r, best = A.train_arm(c, tr, va, V, MODE,
                                   teacher=(teacher if use_t else None), quiet=False)
        append_row(name, r, c["seed"])
        print(f"DONE {name}: float ppl {r['float']['ppl']:.4f} t1 {r['float']['top1']:.4f} "
              f"t3 {r['float']['top3']:.4f} | int8 ppl {r['int8']['ppl']:.4f} "
              f"t1 {r['int8']['top1']:.4f} | params {r['counts']['params']//1000}k "
              f"state {r['counts']['state']} macC {r['counts']['macc']//1000}k "
              f"({time.time()-t0:.0f}s)", flush=True)

if __name__ == "__main__":
    main()
