#!/usr/bin/env python3
"""Ground-truth reference for the on-device C forward pass (vocab V=32).

Loads nn_weights.bin + nn_manifest.json and runs the SAME int8xfloat GRU forward
as nn.c (identical Pade tanh/sigmoid; per-output-row dequant
out = (sum_i w_int8[i]*x_float[i])*row_scale + bias; optional input->output skip),
then prints the top-3 next-symbol predictions for a list of test prefixes,
including capitals ('^' = capital-escape) and punctuation.

Device-match note: nn.c seeds the hidden state by stepping a single space (sym 26)
from a zero state before any key is typed, so for a prefix P the on-device state
has processed [space] + P.  This script does the same (prepend the seed space).

Prefixes use the same preprocessing as training/on-device input: an uppercase
letter becomes '^' + lowercase, '!'/'?' -> '.', etc.  A literal '^' in a prefix
is kept (it is the capital-escape symbol).

Expected tiny diff vs nn.c: both sum in float32 (nn_common.lin_q matches nn.c's
sequential k-loop order); only FPU fma contraction (~1e-6) can differ, which never
changes the top-3 ranking here (see the #3-#4 margins printed below).
"""
import os
import nn_common as C

HERE = os.path.dirname(os.path.abspath(__file__))

PREFIXES = ["the ", "q", "th", "predic", "hello ", "comput", "in", "and ",
            "peopl", "keyboa", "langua", "wolrd", "because ", "i am ",
            # capitals / punctuation / capital-escape
            "^the ", "i'm", "hello^", "dr^", "u.s^", "don't", "mr", "^i ",
            "wasn'", "e.g", "well-", "^new ^yor"]


def show_syms(syms):
    return "".join(C.sym_str(int(s)) for s in syms)


def main():
    qm = C.load_qmodel(os.path.join(HERE, "nn_weights.bin"),
                       os.path.join(HERE, "nn_manifest.json"))
    print(f"model: {qm.arch} layers={qm.layers} Hs={qm.Hs} E={qm.E} "
          f"out_skip={qm.out_skip} state_floats={qm.state_size()}")
    print("(each prefix seeded with a leading space, matching nn.c;"
          " '_'=space, '^'=capital-escape)\n")
    print(f"{'prefix':>14s}  {'encoded':>16s}   top-3         margin")
    print("  " + "-"*58)
    for pref in PREFIXES:
        enc = C.encode(pref)
        syms = [C.SP] + enc
        st = qm.init_state()
        for s in syms:
            st = qm.step(s, st)
        lg = qm.logits(st)
        order = list(lg.argsort()[::-1])
        pretty = " ".join(C.sym_str(int(t)) for t in order[:3])
        margin = float(lg[order[2]] - lg[order[3]])
        disp = pref.replace(" ", "_")
        print(f"{disp:>14s}  {show_syms(enc):>16s}   {pretty:<12s}  {margin:5.3f}")


if __name__ == "__main__":
    main()
