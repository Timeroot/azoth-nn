#!/usr/bin/env python3
"""Compare int8 vs int4 quantization of the recurrent matrices for the final
student (loaded from nn_student_float.npz).  Reports held-out ppl/top1/top3 and
the on-flash byte size for each, to decide whether int4 buys useful capacity."""
import os
import numpy as np
import nn_common as C
from nn_train import get_data, eval_quant, count_bytes

HERE = os.path.dirname(os.path.abspath(__file__))

def main():
    d = np.load(os.path.join(HERE, "nn_student_float.npz"), allow_pickle=True)
    arch = str(d["arch"]); layers = int(d["layers"]); H = int(d["H"]); E = int(d["E"])
    out_skip = bool(d["out_skip"]); Hs = [H]*layers
    tens = {k: d[k] for k in d.files if k not in ("arch","layers","H","E","out_skip")}
    _, val = get_data(os.path.join(HERE, "corpus_big.txt")); val_np = val.numpy()
    print(f"student {arch} L{layers} H{H} E{E} skip={out_skip}")
    tmp = os.path.join(HERE, "_ib")
    for bits in (8, 4):
        C.pack_weights(arch, layers, Hs, E, tens, tmp+".bin", tmp+".h", tmp+".json",
                       out_skip=out_skip, rec_bits=bits)
        qm = C.load_qmodel(tmp+".bin", tmp+".json")
        m = eval_quant(qm, val_np)
        pb, i8, fl = count_bytes(arch, layers, Hs, E, out_skip, bits)
        print(f"  int{bits}: ppl {m['ppl']:.3f} top1 {m['top1']:.4f} "
              f"top3 {m['top3']:.4f}  on-flash {pb} B ({pb/1024:.1f} KB)")
    for ext in (".bin",".h",".json"):
        try: os.remove(tmp+ext)
        except OSError: pass

if __name__ == "__main__":
    main()
