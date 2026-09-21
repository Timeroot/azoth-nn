#!/usr/bin/env python3
"""Run the controlled ablation matrix (default: fast 27-vocab letters testbed).
One thing toggled per arm; identical schedule; same held-out; float+int8; key
arms on 2 seeds.  Saves nn_ablation_<mode>.json and prints a table."""
import os, sys, json, time
import numpy as np
import nn_ablate as A

HERE = os.path.dirname(os.path.abspath(__file__))
MODE = sys.argv[1] if len(sys.argv) > 1 else "27"
V = A.vocab_syms(MODE)
CORP = [os.path.join(HERE, "corpus_big.txt"), os.path.join(HERE, "corpus_code.txt")]

# ---- testbed sizes (small = fast, low-noise) ----
if MODE == "27":
    HF, HS, E, L = 72, 24, 24, 64
    STEPS, PAT, EE, ENB = 10000, 8, 500, 16
    TE_STEPS, TE_H = 4000, 256
    KEY_SEEDS = [1337, 7]
else:  # 72 confirm at deployment size
    HF, HS, E, L = 84, 32, 28, 96
    STEPS, PAT, EE, ENB = 40000, 10, 1000, 16
    TE_STEPS, TE_H = 7000, 384
    KEY_SEEDS = [1337, 7]

BASE = dict(HF=HF, HS=HS, E=E, skip=True, slow="gru", aux=(), boundary="nonalpha",
            seed=1337, steps=STEPS, L=L, B=256, lr0=3e-3 if MODE=="27" else 2e-3,
            lr1=1.5e-3 if MODE=="27" else 1.2e-3, lr_min=2e-5, anneal=0.45,
            warm=True, aux_coef=0.3, aux_full=0.25, eval_every=EE, eval_nb=ENB,
            patience=PAT, T=1.5, alpha=0.7)

def cfg(**kw):
    c = dict(BASE); c.update(kw); return c

def wide_H():
    """single-GRU width whose int8 weight count ~matches the two-timescale arm."""
    tt = A.counts(V, HF, HS, E, True, "gru")["i8"]
    best = HF
    for h in range(HF, HF+120):
        if A.counts(V, h, 0, E, True, "gru")["i8"] >= tt:
            best = h; break
    return best
HW = wide_H()


def main():
    t0 = time.time()
    print(f"MODE={MODE} V={V} testbed HF={HF} HS={HS} E={E} L={L} wideH={HW}")
    (tr, va) = A.get_data(MODE, CORP)
    print(f"train {len(tr[0]):,} val {len(va[0]):,}")

    teacher = None
    print("training teacher...")
    teacher, tfm = A.train_teacher(tr, va, V, TE_STEPS, L, 256, H=TE_H)

    ARMS = []  # (name, cfg, seeds, use_teacher)
    ARMS.append(("single_base",  cfg(HS=0),                       KEY_SEEDS, False))
    ARMS.append(("single_wide",  cfg(HS=0, HF=HW),                KEY_SEEDS, False))
    ARMS.append(("tt_gru",       cfg(slow="gru"),                 KEY_SEEDS, False))
    ARMS.append(("tt_lstm",      cfg(slow="lstm"),                [1337],    False))
    ARMS.append(("tt_rnn",       cfg(slow="rnn"),                 [1337],    False))
    ARMS.append(("tt_gru_aux_char2", cfg(aux=("char2",)),         [1337],    False))
    ARMS.append(("tt_gru_aux_char3", cfg(aux=("char3",)),         [1337],    False))
    ARMS.append(("tt_gru_aux_word",  cfg(aux=("word",)),          [1337],    False))
    ARMS.append(("tt_gru_aux_all",   cfg(aux=("char2","char3","word")), [1337], False))
    ARMS.append(("tt_gru_bnd_space", cfg(boundary="space"),       [1337],    False))
    ARMS.append(("tt_gru_distill",   cfg(),                       [1337],    True))
    ARMS.append(("wide_distill",     cfg(HS=0, HF=HW),            [1337],    True))

    results = {}
    for name, c, seeds, use_t in ARMS:
        runs = []
        for sd in seeds:
            cc = dict(c); cc["seed"] = sd
            net, r, best = A.train_arm(cc, tr, va, V, MODE,
                                       teacher=(teacher if use_t else None), quiet=True)
            runs.append(r)
            print(f"  {name:20s} seed {sd:5d} | float ppl {r['float']['ppl']:.3f} "
                  f"t1 {r['float']['top1']:.3f} t3 {r['float']['top3']:.3f} | "
                  f"int8 ppl {r['int8']['ppl']:.3f} t1 {r['int8']['top1']:.3f} | "
                  f"P{r['counts']['params']//1000}k st{r['counts']['state']} "
                  f"macC{r['counts']['macc']//1000}k @{r['best_step']} ({time.time()-t0:.0f}s)")
        results[name] = summarize(name, c, runs)
    json.dump(results, open(os.path.join(HERE, f"nn_ablation_{MODE}.json"), "w"), indent=1)
    print_table(results)
    print(f"\nteacher: ppl {tfm['ppl']:.3f} t1 {tfm['top1']:.3f} t3 {tfm['top3']:.3f}")
    print(f"total {time.time()-t0:.0f}s")

def summarize(name, c, runs):
    def agg(field, sub):
        vals = [r[field][sub] for r in runs]
        return {"mean": float(np.mean(vals)), "std": float(np.std(vals)), "n": len(vals)}
    ct = runs[0]["counts"]
    return {"name": name, "slow": c["slow"] if c["HS"] > 0 else "-", "HS": c["HS"],
            "HF": c["HF"], "aux": list(c["aux"]), "boundary": c["boundary"],
            "params": ct["params"], "state": ct["state"], "macc": ct["macc"],
            "bytes": ct["bytes"],
            "float_ppl": agg("float", "ppl"), "float_t1": agg("float", "top1"),
            "float_t3": agg("float", "top3"),
            "int8_ppl": agg("int8", "ppl"), "int8_t1": agg("int8", "top1"),
            "int8_t3": agg("int8", "top3"),
            "best_step": [r["best_step"] for r in runs]}

def print_table(results):
    print("\n==== ABLATION TABLE (mode %s) ====" % MODE)
    h = (f"{'arm':22s} {'params':>7s} {'st':>4s} {'macC':>6s} "
         f"{'fppl':>7s} {'ft1':>6s} {'ft3':>6s} {'qppl':>7s} {'qt1':>6s} {'seeds':>5s}")
    print(h)
    for name, r in results.items():
        fp = r["float_ppl"]; print(
            f"{name:22s} {r['params']//1000:6d}k {r['state']:4d} {r['macc']//1000:5d}k "
            f"{fp['mean']:7.3f} {r['float_t1']['mean']:6.3f} {r['float_t3']['mean']:6.3f} "
            f"{r['int8_ppl']['mean']:7.3f} {r['int8_t1']['mean']:6.3f} {fp['n']:5d}"
            + (f"  (+-{fp['std']:.3f})" if fp['n'] > 1 else ""))

if __name__ == "__main__":
    main()
