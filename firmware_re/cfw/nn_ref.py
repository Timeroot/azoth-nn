#!/usr/bin/env python3
"""Ground-truth reference for the on-device C forward pass (v3, vocab V=72).

Loads nn_weights.bin + nn_manifest.json and runs the SAME int8xfloat32
TWO-TIMESCALE GRU forward as nn.c (identical Pade tanh/sigmoid; per-output-row
dequant; fast char state updated every step, slow word state updated only after
a non-alphabetic char; OUT reads [hf ; hs ; emb(last)] with the input->output
skip), then prints the top-3 next-symbol predictions for a list of test prefixes
covering capitals, punctuation, digits and newlines.

Device-match note: nn.c seeds the state by stepping a single space (sym 36) from
a zero state before any key is typed, so for a prefix P the on-device state has
processed [space] + P.  This script does the same.

Prefix notation (a convenience for writing capitals): a '^' immediately before a
lowercase letter is read as CAPITAL ESCAPE, so "^the" == "The".  A real uppercase
letter works too.  A '^' NOT before a lowercase letter is the literal caret char
(token 65), e.g. "2^8".  Space shown as '_', tab '\\t', newline '\\n', CAPESC '^^'.
"""
import os, re, sys
import nn_common as C

HERE = os.path.dirname(os.path.abspath(__file__))
# Optional model prefix (loads <prefix>.bin + <prefix>.json), so any candidate in
# the scaling series can be inspected, e.g.  python nn_ref.py nn_256k
PREFIX = sys.argv[1] if len(sys.argv) > 1 else "nn_weights"
_BIN = os.path.join(HERE, PREFIX + ".bin")
_MAN = os.path.join(HERE, (PREFIX + ".json") if os.path.exists(os.path.join(HERE, PREFIX + ".json")) else "nn_manifest.json")

PREFIXES = [
    "the ", "The ", "^the ", "q", "th", "predic", "hello, World!", "i'm",
    "don't", "wasn'", "e.g", "well-", "^new ^york", "^i ", "because ",
    # digits / math / code
    "x = 3", "3.14", "0x", "2^8", "a[0]", "def f(", "print(", "import ",
    "self.", "return ", "for i in ", "if (", "http", "https://", "www.",
    "foo_bar", "{", "</", "#include", "1234567",
    # whitespace context
    "line one\n", "a\tb",
]


def encode_prefix(s):
    s = re.sub(r"\^([a-z])", lambda m: m.group(1).upper(), s)   # ^x -> capital X
    return C.encode(s)


def show(syms):
    return "".join(C.sym_str(int(s)) for s in syms)


def main():
    tt = C.load_ttmodel(_BIN, _MAN)
    print(f"model: {PREFIX}  two-timescale GRU  HF={tt.HF} HS={tt.HS} E={tt.E} "
          f"FL={tt.FL} out_skip={tt.out_skip} state_floats={tt.state_size()}")
    print("(each prefix seeded with a leading space, matching nn.c)\n")
    print(f"{'prefix':>18s}  {'top-3':<14s}  margin")
    print("  " + "-"*46)
    for pref in PREFIXES:
        enc = encode_prefix(pref)
        st = tt.init_state()
        for s in [C.SP] + enc:
            st = tt.step(s, st)
        lg = tt.logits(st)
        order = list(lg.argsort()[::-1])
        pretty = " ".join(C.sym_str(int(t)) for t in order[:3])
        margin = float(lg[order[2]] - lg[order[3]])
        disp = pref.replace("\n", "\\n").replace("\t", "\\t").replace(" ", "_")
        print(f"{disp:>18s}  {pretty:<14s}  {margin:5.3f}")


if __name__ == "__main__":
    main()
