#!/usr/bin/env python3
"""Retrain (to convergence) and EXPORT the best small-mid PKE candidate:
`fmlp_res_k7_D8_Hf2kD_s170` (~193 KB deployed, the biggest per-KB win of the PKE study,
int8 ~3.655 vs baseline ~3.72 at that KB). The confirm/sweep did not persist weights, so
we retrain once and pack a PKE-aware deployable blob + an nn_weights.h-style layout note.

Deployed layout (int8 GRU weights per-row + fp16 PKE + f32 side):
  int8 (per-output-row symmetric; +f32 scale per row):
    Wif0[3HF,E], Whf0[3HF,HF], Wis[3HS,HF], Whs[3HS,HS], OUT[V,HF+HS+E],
    GMAP0[Hf,k*D], GMAP2[E,Hf]        (the residual f-map g = Linear->ReLU->Linear)
  fp16:  PKE[k,V,D]
  f32 :  EMB[V,E], all biases, all row-scales
On device (fmlp_res forward, per typed symbol s):
  win  = concat_j PKE[j][ ctx[j] ]          # k*D, ctx = last k syms (oldest..newest=s), pad=space
  gin  = EMB[s] + GMAP2( relu( GMAP0(win)+bG0 ) )+bG2     # E-dim residual input
  hf   = GRU_fast(gin, hf)                                # then standard two-timescale GRU
  ... slow update at word boundary ...  logits = OUT@[hf;hs;EMB[s]] + bOUT
"""
import os, json, time
import numpy as np
import torch
import nn_common as C
import run_pke as P
from run_frontier import load_data, build_eval

HERE = os.path.dirname(os.path.abspath(__file__))
PRE = "nn_fmlp_res_193k"

def main():
    t0 = time.time()
    tr, va = load_data(); seqs, tgt = build_eval(va)
    build = lambda: P.TTGRU(152, 64, 48, 1, pke=(7, 8, "concat"), integ="fmlp_res", fmlp_hidden=112)
    print("training fmlp_res_k7_D8_Hf2kD_s170 to convergence ...", flush=True)
    net, m = P.train_model(build, tr, va, seed=0, tag="export_fmlpres",
                           patience=10, eval_every=1000, decay_steps=5000, max_steps=90000)
    fppl, _, _ = P.evaluate(net, seqs, tgt, quant=False)
    qppl, t1, t3 = P.evaluate(net, seqs, tgt, quant=True)
    i8b, pkeb, f32b = P.deploy_bytes(net); kb = (i8b+pkeb+f32b)/1024.0
    print(f"converged: float {fppl:.4f} int8 {qppl:.4f} t1 {t1:.4f} t3 {t3:.4f} | "
          f"{kb:.1f}KB (i8 {i8b/1024:.1f}+pke {pkeb/1024:.2f}+f32 {f32b/1024:.1f}) "
          f"best@{m['best_step']} {m['stop_reason']} ({time.time()-t0:.0f}s)", flush=True)
    assert m["stop_reason"] == "decayed", "candidate hit step cap -> undertrained; not exporting"

    sd = {k: v.detach().cpu().numpy() for k, v in net.state_dict().items()}
    HF, HS, E, k, D, Hf = 152, 64, 48, 7, 8, 112
    # int8 per-row tensors -> (name, quantized, scale)
    i8_specs = []
    for name, W in [("Wif0", sd["fast.weight_ih_l0"]), ("Whf0", sd["fast.weight_hh_l0"]),
                    ("Wis", sd["slow.weight_ih"]), ("Whs", sd["slow.weight_hh"]),
                    ("OUT", sd["out.weight"]),
                    ("GMAP0", sd["gmap.0.weight"]), ("GMAP2", sd["gmap.2.weight"])]:
        q, s = C.quant_rows(W, 8); i8_specs.append((name, q.astype(np.int8), s.astype(np.float32)))
    pke = sd["pke_table"].astype(np.float16)            # fp16 [k,V,D]
    f32_specs = [("EMB", sd["emb.weight"].astype(np.float32))]
    for name, q, s in i8_specs: f32_specs.append((name+"_scale", s))
    for name, B in [("Bif0", sd["fast.bias_ih_l0"]), ("Bhf0", sd["fast.bias_hh_l0"]),
                    ("Bis", sd["slow.bias_ih"]), ("Bhs", sd["slow.bias_hh"]),
                    ("Bout", sd["out.bias"]),
                    ("BG0", sd["gmap.0.bias"]), ("BG2", sd["gmap.2.bias"])]:
        f32_specs.append((name, B.astype(np.float32)))

    blob = bytearray(); offs = {}; shapes = {}; dtypes = {}
    for name, q, s in i8_specs:
        offs[name] = len(blob); shapes[name] = list(q.shape); dtypes[name] = "int8"
        blob += q.tobytes()
        while len(blob) % 4: blob.append(0)
    offs["PKE"] = len(blob); shapes["PKE"] = list(pke.shape); dtypes["PKE"] = "float16"
    blob += pke.tobytes()
    while len(blob) % 4: blob.append(0)
    for name, a in f32_specs:
        offs[name] = len(blob); shapes[name] = list(a.shape); dtypes[name] = "float32"
        blob += np.ascontiguousarray(a, np.float32).tobytes()
    open(os.path.join(HERE, PRE+".bin"), "wb").write(blob)

    manifest = dict(model="fmlp_res", HF=HF, HS=HS, E=E, V=C.V, k=k, D=D, Hf=Hf,
                    combine="concat", OUTIN=HF+HS+E, bytes=len(blob),
                    int8=i8b, pke_fp16=pkeb, f32=f32b, kb=round(kb, 1),
                    metrics=dict(float_ppl=round(fppl,4), int8_ppl=round(qppl,4),
                                 t1=round(t1,4), t3=round(t3,4)),
                    offsets=offs, shapes=shapes, dtypes=dtypes)
    json.dump(manifest, open(os.path.join(HERE, PRE+".json"), "w"), indent=1)

    with open(os.path.join(HERE, PRE+".h"), "w") as f:
        f.write("/* auto-generated fmlp_res candidate (PKE-augmented). Layout note for a\n"
                "   future nn.c port; NOT yet consumed by the shipped nn.c. */\n")
        f.write(f"#define FR_VOCAB {C.V}\n#define FR_EDIM {E}\n#define FR_HF {HF}\n#define FR_HS {HS}\n")
        f.write(f"#define FR_K {k}\n#define FR_D {D}\n#define FR_HF_MLP {Hf}\n")
        f.write(f"#define FR_OUTIN {HF+HS+E}\n#define FR_BYTES {len(blob)}\n")
        for name in offs:
            f.write(f"#define FROFF_{name.upper()} {offs[name]}u  /* {dtypes[name]} {shapes[name]} */\n")
    print(f"exported {PRE}.bin ({len(blob)} B / {len(blob)/1024:.1f}KB) + .json + .h  "
          f"({time.time()-t0:.0f}s)", flush=True)
    print("=== EXPORT DONE ===", flush=True)

if __name__ == "__main__":
    main()
