#!/usr/bin/env python3
"""Slow-L1 lottery-ticket sparsity anneal, scored under FREE indexing (cost =
#nonzero int8 weights + f32 side tensors only; index/bitmask assumed free).

Starts from a trained large dense model (nn_460k), then over a long run raises a
global magnitude-prune target sparsity on a slow cubic schedule while an L1 penalty
on the surviving prunable weights ramps up — so sparsity rises gradually, true zeros
are realized by the mask, and the net keeps adapting.  At many checkpoints it logs
(step, sparsity, nonzero, free-KB, float+int8 ppl/top-1/top-3) to lottery_results.csv
(one row per checkpoint, appended immediately so stalls lose nothing).  That
trajectory IS the sparse frontier; overlay it on the dense-NN curve.
"""
import os, sys, csv, time, math
import numpy as np
import torch, torch.nn as nn
import nn_common as C
import nn_train as T
from run_sparsenn import dequant_to_student, eval_on, PRUNE
from run_frontier import build_eval, load_data

HERE = os.path.dirname(os.path.abspath(__file__))
DEV = T.DEV
BASE = sys.argv[1] if (len(sys.argv) > 1 and not sys.argv[1].startswith("-")) else "nn_460k"
TOTAL = int(sys.argv[2]) if (len(sys.argv) > 2 and sys.argv[2].isdigit()) else 45000
S_FINAL = float(sys.argv[3]) if len(sys.argv) > 3 else 0.94
LR_PEAK = float(sys.argv[4]) if len(sys.argv) > 4 else 8e-4
LR_MODE = sys.argv[5] if len(sys.argv) > 5 else "cosine"   # "cosine" or "wsd"
CSV = os.path.join(HERE, sys.argv[6] if len(sys.argv) > 6 else "lottery_results.csv")
L1MAX = 5e-5
WARM, COOL, MASK_FREQ, EVAL_FREQ = 2000, 3000, 250, 2500

def lr_at_lottery(step):
    """WSD: warmup -> LONG constant high LR (through the whole sparsity ramp) ->
    short decay; lets surviving weights re-adapt at high LR while others drop."""
    if LR_MODE != "wsd":
        p = step / TOTAL
        return 2e-5 + 0.5*(LR_PEAK-2e-5)*(1+math.cos(math.pi*p))
    dec = TOTAL - COOL
    if step < WARM: return 2e-5 + (LR_PEAK-2e-5)*(step/max(1.0,WARM))
    if step < dec:  return LR_PEAK
    p = (step-dec)/max(1.0, TOTAL-dec)
    return 2e-5 + 0.5*(LR_PEAK-2e-5)*(1+math.cos(math.pi*p))

def sched_sparsity(step):
    if step < WARM: return 0.0
    if step >= TOTAL - COOL: return S_FINAL
    r = (step - WARM) / (TOTAL - COOL - WARM)          # 0..1
    return S_FINAL * (1 - (1 - r)**3)                  # cubic ramp (Zhu-Gupta)

def l1_coef(step):
    if step < WARM: return 0.0
    r = min(1.0, (step - WARM) / (TOTAL - COOL - WARM))
    return L1MAX * r

def global_mask(net, s):
    params = dict(net.named_parameters())
    if s <= 0: return {n: torch.ones_like(params[n]) for n in PRUNE}
    allw = torch.cat([params[n].data.abs().flatten() for n in PRUNE])
    k = int(s * allw.numel())
    thr = allw.kthvalue(max(1, k)).values
    return {n: (params[n].data.abs() > thr).float() for n in PRUNE}

def apply_mask(net, mask):
    params = dict(net.named_parameters())
    with torch.no_grad():
        for n in PRUNE: params[n].data *= mask[n]

def free_kb(net, mask, tt):
    params = dict(net.named_parameters())
    nonzero = int(sum(int(mask[n].sum().item()) for n in PRUNE))
    rows = sum(params[n].shape[0] for n in PRUNE)
    f32 = tt.V*tt.E + rows + sum(params[k].numel() for k in params
                                 if k.endswith(".bias") or "bias_" in k)
    return nonzero, (nonzero + f32*4)/1024.0

def append_row(row):
    exist = os.path.exists(CSV) and os.path.getsize(CSV) > 0
    with open(CSV, "a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["step","sparsity","nonzero","free_kb",
            "float_ppl","float_t1","float_t3","int8_ppl","int8_t1","int8_t3"])
        if not exist: w.writeheader()
        w.writerow(row)

def main():
    t0 = time.time()
    tr, va = load_data(); seqs, tgt = build_eval(va)
    batch = T.make_batcher(tr, T.next_word_target(tr), 96, 256)
    net, tt = dequant_to_student(BASE)
    try: net.fast.flatten_parameters()
    except Exception: pass
    ce = nn.CrossEntropyLoss()
    opt = torch.optim.Adam(net.parameters(), lr=LR_PEAK)
    mask = global_mask(net, 0.0)
    fp0,ft10,ft30 = eval_on(net, seqs, tgt, fakequant=False)
    print(f"{BASE} base float ppl {fp0:.3f} t1 {ft10:.3f} (LR_MODE={LR_MODE} peak={LR_PEAK})", flush=True)
    best_pts = []
    for step in range(TOTAL + 1):
        for g in opt.param_groups: g["lr"] = lr_at_lottery(step)
        if step % MASK_FREQ == 0:
            mask = global_mask(net, sched_sparsity(step)); apply_mask(net, mask)
        if step % EVAL_FREQ == 0:
            fppl,ft1,ft3 = eval_on(net, seqs, tgt, fakequant=False)
            qppl,qt1,qt3 = eval_on(net, seqs, tgt, fakequant=True)
            nz, kb = free_kb(net, mask, tt)
            s = sched_sparsity(step)
            append_row(dict(step=step, sparsity=round(s,4), nonzero=nz, free_kb=round(kb,1),
                            float_ppl=round(fppl,3), float_t1=round(ft1,4), float_t3=round(ft3,4),
                            int8_ppl=round(qppl,3), int8_t1=round(qt1,4), int8_t3=round(qt3,4)))
            print(f"  step {step:6d} s={s:.3f} nz={nz} {kb:6.1f}KB | float {fppl:.3f} "
                  f"int8 {qppl:.3f} t1 {qt1:.3f} ({time.time()-t0:.0f}s)", flush=True)
            net.train()
        if step == TOTAL: break
        x,y1,_,_,_ = batch()
        logits = net(x)[0].reshape(-1, C.V)
        loss = ce(logits, y1.reshape(-1))
        lc = l1_coef(step)
        if lc > 0:
            params = dict(net.named_parameters())
            l1 = sum((params[n]*mask[n]).abs().sum() for n in PRUNE)
            loss = loss + lc * l1
        opt.zero_grad(); loss.backward()
        nn.utils.clip_grad_norm_(net.parameters(), 1.0); opt.step()
        apply_mask(net, mask)
    # report the best free-index point around ~270KB (matched to dense nn_256k)
    import csv as _c
    pts = [r for r in _c.DictReader(open(CSV))]
    near = min(pts, key=lambda r: abs(float(r["free_kb"]) - 270))
    print(f"float : ppl {float(near['float_ppl']):.4f} top1 {float(near['float_t1']):.4f} "
          f"top3 {float(near['float_t3']):.4f}  (free {near['free_kb']}KB, sparsity {near['sparsity']})", flush=True)
    print(f"int8  : ppl {float(near['int8_ppl']):.4f} top1 {float(near['int8_t1']):.4f} "
          f"top3 {float(near['int8_t3']):.4f}", flush=True)
    print(f"lottery anneal done ({time.time()-t0:.0f}s)", flush=True)

if __name__ == "__main__":
    main()
