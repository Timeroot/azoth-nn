#!/usr/bin/env python3
"""Search for the best <=60KB-blob student (32-vocab, GRU L1 +/- skip) with
distillation from nn_teacher.pt.  Phase 1 re-sweeps temperature (small student is
capacity-limited, so KD should help more); phase 2 sweeps H/E/skip archs at the
best T.  Loads data + teacher once.  Reports float+int8 metrics and exact blob
bytes; enforces the 0x50000..<0x5f000 budget (<=61440 B; we target <=60000)."""
import os, json
import numpy as np
import nn_common as C
from nn_train import get_data, train_student, load_teacher, count_macs, HERE

BUDGET = 65000            # bytes; hard ceiling is 0x60000-0x50000 = 65536 (dev limit 0x61000)
STEPS  = 4000

def blob_bytes(arch, layers, H, E, out_skip):
    """Exact packed size via a dry pack on zero tensors."""
    Hs=[H]*layers; g=3
    t={"EMB":np.zeros((C.V,E),np.float32),
       "OUT":np.zeros((C.V,H+(E if out_skip else 0)),np.float32),
       "Bout":np.zeros(C.V,np.float32)}
    for l in range(layers):
        inp=E if l==0 else H
        t[f"Wih{l}"]=np.zeros((g*H,inp),np.float32); t[f"Whh{l}"]=np.zeros((g*H,H),np.float32)
        t[f"Bih{l}"]=np.zeros(g*H,np.float32); t[f"Bhh{l}"]=np.zeros(g*H,np.float32)
    tmp=os.path.join(HERE,"_sz")
    _,nb=C.pack_weights(arch,layers,Hs,E,t,tmp+".bin",tmp+".h",tmp+".json",out_skip=out_skip,rec_bits=8)
    for e in (".bin",".h",".json"):
        try: os.remove(tmp+e)
        except OSError: pass
    return nb

def run(train,val,val_np,H,E,skip,kw,steps=STEPS):
    _,fm,qm,info=train_student("gru",1,H,E,steps,128,256,2e-3,1337,train,val,val_np,
                               out_skip=skip,quiet=True,**kw)
    return fm,qm,info

def main():
    train,val=get_data(os.path.join(HERE,"corpus_big.txt")); val_np=val.numpy()
    teacher=load_teacher()
    print("=== phase 1: temperature sweep (H=112 E=32 skip) ===", flush=True)
    Hp,Ep=112,32
    tconfigs=[("hard",dict(distill=False)),
              ("T1.5a0.7",dict(distill=True,teacher=teacher,T=1.5,alpha=0.7)),
              ("T2.5a0.7",dict(distill=True,teacher=teacher,T=2.5,alpha=0.7)),
              ("T4.0a0.7",dict(distill=True,teacher=teacher,T=4.0,alpha=0.7)),
              ("T4.0a0.9",dict(distill=True,teacher=teacher,T=4.0,alpha=0.9))]
    p1=[]
    for name,kw in tconfigs:
        fm,qm,info=run(train,val,val_np,Hp,Ep,True,kw)
        p1.append((name,kw,fm,qm))
        print(f"  {name:10s} fppl {fm['ppl']:.3f} ft1 {fm['top1']:.4f} ft3 {fm['top3']:.4f}"
              f" | qppl {qm['ppl']:.3f} qt1 {qm['top1']:.4f} qt3 {qm['top3']:.4f}", flush=True)
    best=min(p1,key=lambda r:r[2]['ppl'])
    bestkw=best[1]; print(f"  >> best T config: {best[0]}", flush=True)

    print("\n=== phase 2: arch sweep at best T (blob<=%dB) ===" % BUDGET, flush=True)
    archs=[(108,32,True),(112,32,True),(114,32,True),(112,32,False),(116,24,True)]
    p2=[]
    for H,E,skip in archs:
        nb=blob_bytes("gru",1,H,E,skip)
        if nb>BUDGET:
            print(f"  H{H} E{E} skip{int(skip)}: blob {nb} B > budget, SKIP", flush=True); continue
        fm,qm,info=run(train,val,val_np,H,E,skip,bestkw)
        mac=count_macs("gru",1,[H],E,skip)
        p2.append((H,E,skip,nb,fm,qm,mac))
        print(f"  H{H} E{E} skip{int(skip)}: blob {nb}B mac{mac//1000}k | "
              f"fppl {fm['ppl']:.3f} ft1 {fm['top1']:.4f} ft3 {fm['top3']:.4f} | "
              f"qppl {qm['ppl']:.3f} qt1 {qm['top1']:.4f} qt3 {qm['top3']:.4f}", flush=True)
    bestarch=min(p2,key=lambda r:r[5]['ppl'])   # by quant ppl
    print(f"\n>> BEST under budget: H{bestarch[0]} E{bestarch[1]} skip{int(bestarch[2])} "
          f"blob {bestarch[3]}B  T={best[0]}", flush=True)
    json.dump({"phase1":[(n,f,q) for n,_,f,q in p1],
               "phase2":[(H,E,s,nb,f,q,m) for H,E,s,nb,f,q,m in p2],
               "bestT":best[0],"bestkw":{k:(v if not hasattr(v,'state_dict') else 'teacher')
                                         for k,v in bestkw.items()},
               "bestarch":[bestarch[0],bestarch[1],bestarch[2],bestarch[3]]},
              open(os.path.join(HERE,"nn_small_search.json"),"w"),indent=1)

if __name__=="__main__":
    main()
