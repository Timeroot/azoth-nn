#!/usr/bin/env python3
"""Sparse-pruned NN frontier point: take a big dense model (nn_460k), magnitude-
prune its int8 weight matrices to several sparsities with fine-tune recovery, store
sparse (bitmask + int8 values), and compare ppl at matched DEPLOYED KB vs the dense
scaling curve.  Appends rows to frontier_results.csv."""
import os, sys, json, csv, time, math
import numpy as np
import torch, torch.nn as nn, torch.nn.functional as F
import nn_common as C
import nn_train as T
from run_frontier import build_eval, load_data

HERE = os.path.dirname(os.path.abspath(__file__))
DEV = T.DEV
BASE = sys.argv[1] if (len(sys.argv) > 1 and not sys.argv[1].startswith("-")) else "nn_460k"
_sp = sys.argv[2] if (len(sys.argv) > 2 and "," in sys.argv[2]) else "0.5,0.75,0.9"
SPARSITIES = [float(x) for x in _sp.split(",")]
FT_STEPS = int(sys.argv[3]) if (len(sys.argv) > 3 and sys.argv[3].isdigit()) else 9000

PRUNE = ["fast.weight_ih_l0","fast.weight_hh_l0","fast.weight_ih_l1","fast.weight_hh_l1",
         "slow.weight_ih","slow.weight_hh","out.weight"]

def dequant_to_student(prefix):
    tt = C.load_ttmodel(os.path.join(HERE, prefix+".bin"), os.path.join(HERE, prefix+".json"))
    net = T.Student(tt.HF, tt.HS, tt.E, out_skip=tt.out_skip, aux=False, FL=tt.FL).to(DEV)
    sd = net.state_dict(); p = tt.p
    def deq(name): return torch.tensor(p[name].astype(np.float32) * p[name+"_s"][:,None], device=DEV)
    with torch.no_grad():
        sd["emb.weight"].copy_(torch.tensor(p["EMB"], device=DEV))
        sd["out.weight"].copy_(deq("OUT")); sd["out.bias"].copy_(torch.tensor(p["Bout"], device=DEV))
        sd["slow.weight_ih"].copy_(deq("Wis")); sd["slow.weight_hh"].copy_(deq("Whs"))
        sd["slow.bias_ih"].copy_(torch.tensor(p["Bis"], device=DEV)); sd["slow.bias_hh"].copy_(torch.tensor(p["Bhs"], device=DEV))
        for l in range(tt.FL):
            sd[f"fast.weight_ih_l{l}"].copy_(deq(f"Wif{l}")); sd[f"fast.weight_hh_l{l}"].copy_(deq(f"Whf{l}"))
            sd[f"fast.bias_ih_l{l}"].copy_(torch.tensor(p[f"Bif{l}"], device=DEV))
            sd[f"fast.bias_hh_l{l}"].copy_(torch.tensor(p[f"Bhf{l}"], device=DEV))
    net.load_state_dict(sd); return net, tt

def make_masks(net, sparsity):
    masks = {}
    sd = dict(net.named_parameters())
    for name in PRUNE:
        w = sd[name].data
        k = int(sparsity * w.numel())
        if k <= 0: masks[name] = torch.ones_like(w); continue
        thr = w.abs().flatten().kthvalue(k).values
        masks[name] = (w.abs() > thr).float()
    return masks

def apply_masks(net, masks):
    sd = dict(net.named_parameters())
    with torch.no_grad():
        for name, m in masks.items(): sd[name].data *= m

@torch.no_grad()
def eval_on(net, seqs, tgt, fakequant=True):
    net.eval()
    # per-row int8 fake-quant of the pruned matrices for a realistic deployed number
    orig = {}
    if fakequant:
        sd = dict(net.named_parameters())
        for name in PRUNE:
            w = sd[name].data; orig[name] = w.clone()
            amax = w.abs().amax(1, keepdim=True).clamp_min(1e-8); s = amax/127.0
            sd[name].data = torch.round(w/s).clamp(-127,127)*s
    x = torch.tensor(seqs, dtype=torch.long, device=DEV)
    logits = net(x)[0].reshape(-1, C.V).float().cpu().numpy()
    if fakequant:
        sd = dict(net.named_parameters())
        for name in PRUNE: sd[name].data = orig[name]
    m = logits.max(1, keepdims=True); pr = np.exp(logits-m); pr /= pr.sum(1, keepdims=True)
    nll = -np.log(pr[np.arange(len(tgt)), tgt]+1e-12).mean()
    order = np.argsort(-pr,1)[:,:3]
    return float(np.exp(nll)), float((order[:,0]==tgt).mean()), float((order==tgt[:,None]).any(1).mean())

def deployed_kb(net, tt, masks):
    """sparse: bitmask(N/8)+int8 nnz for pruned mats; dense int8 for none; +f32 emb/scales/biases."""
    sd = dict(net.named_parameters()); i8 = 0
    # pruned matrices: bitmask + nnz values + per-row scale (f32)
    for name in PRUNE:
        w = sd[name].data; N = w.numel(); nnz = int(masks[name].sum().item())
        i8 += math.ceil(N/8) + nnz           # mask bytes + int8 value bytes
    rows = 0
    for name in PRUNE: rows += sd[name].shape[0]
    fl = tt.V*tt.E                            # EMB
    fl += rows                                # per-row scales (f32) for pruned mats
    # biases (f32): fast/slow ih+hh + out
    fl += sum(sd[k].numel() for k in sd if k.endswith(".bias") or "bias_" in k)
    return i8 + fl*4, i8, fl

def main():
    t0 = time.time()
    tr, va = load_data(); seqs, tgt = build_eval(va)
    (trd, tna) = (tr, T.next_word_target(tr))
    batch = T.make_batcher(trd, tna, 96, 256)
    fpath = os.path.join(HERE, "frontier_results.csv")
    def done_names():
        if not os.path.exists(fpath): return set()
        import csv as _c
        return {r["name"] for r in _c.DictReader(open(fpath))}
    def append_row(row):
        exist = os.path.exists(fpath) and os.path.getsize(fpath) > 0
        with open(fpath, "a", newline="") as f:
            w = csv.DictWriter(f, fieldnames=["approach","name","kb","ppl","t1","t3"])
            if not exist: w.writeheader()
            w.writerow(row)
    base_net, tt = dequant_to_student(BASE)
    ppl0,t10,t30 = eval_on(base_net, seqs, tgt)
    print(f"{BASE} dequant baseline: ppl {ppl0:.3f} t1 {t10:.3f} t3 {t30:.3f}", flush=True)
    for sp in SPARSITIES:
        nm = f"{BASE}_sp{int(sp*100)}"
        if nm in done_names():
            print(f"  skip {nm} (already in CSV)", flush=True); continue
        net, tt = dequant_to_student(BASE)
        masks = make_masks(net, sp); apply_masks(net, masks)
        opt = torch.optim.Adam(net.parameters(), lr=6e-4)
        sched = torch.optim.lr_scheduler.CosineAnnealingLR(opt, FT_STEPS)
        ce = nn.CrossEntropyLoss(); net.train()
        for step in range(FT_STEPS):
            x,y1,_,_,_ = batch()
            loss = ce(net(x)[0].reshape(-1,C.V), y1.reshape(-1))
            opt.zero_grad(); loss.backward(); nn.utils.clip_grad_norm_(net.parameters(),1.0)
            opt.step(); sched.step(); apply_masks(net, masks)
            if step % 1500 == 0:
                print(f"  sp{sp} step {step} loss {loss.item():.3f} ({time.time()-t0:.0f}s)", flush=True)
        ppl,t1,t3 = eval_on(net, seqs, tgt)
        kb_tot, i8, fl = deployed_kb(net, tt, masks)
        kb = kb_tot/1024
        row = dict(approach="sparse_nn", name=nm, kb=round(kb,1), ppl=round(ppl,3),
                   t1=round(t1,4), t3=round(t3,4))
        append_row(row)                          # per-arm checkpoint (resumable)
        print(f"  sparse {int(sp*100)}%: deployed {kb:.1f}KB  ppl {ppl:.3f} t1 {t1:.3f} "
              f"t3 {t3:.3f}  [appended] ({time.time()-t0:.0f}s)", flush=True)
    print("sparse-NN done", flush=True)

if __name__ == "__main__":
    main()
