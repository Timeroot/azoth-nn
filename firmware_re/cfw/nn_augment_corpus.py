#!/usr/bin/env python3
"""Sample a few MB of local Python source -> corpus_code.txt, to give the char
predictor real usage of digits, brackets/operators, code punctuation, tabs and
newlines (prose alone has almost none of `[]{}<>|` etc).  The v3 corpus is then
prose (corpus_big.txt) + this code sample, so predictions for prefixes like
"def f(", "x = 3", "http", "import" are meaningful.  No network needed."""
import os, sys, random, numpy

HERE = os.path.dirname(os.path.abspath(__file__))
TARGET_MB = float(sys.argv[1]) if len(sys.argv) > 1 else 3.0

def roots():
    rs = set()
    import torch
    for m in (numpy, torch):
        rs.add(os.path.dirname(os.path.dirname(m.__file__)))
    rs.add(os.path.dirname(os.__file__))          # stdlib
    return rs

def main():
    random.seed(1234)
    files = []
    for r in roots():
        for dp, dn, fn in os.walk(r):
            low = dp.lower()
            if "test" in low or "__pycache__" in low:
                continue
            for f in fn:
                if f.endswith(".py"):
                    files.append(os.path.join(dp, f))
    random.shuffle(files)
    out = []; total = 0; used = 0
    for path in files:
        if total >= TARGET_MB * 1e6:
            break
        try:
            t = open(path, "r", encoding="utf-8", errors="ignore").read()
        except Exception:
            continue
        # skip machine-generated / giant one-liners; keep human-looking code
        if len(t) < 200 or len(t) > 60000:
            continue
        out.append(t); total += len(t); used += 1
    big = "\n\n".join(out)
    open(os.path.join(HERE, "corpus_code.txt"), "w", encoding="utf-8").write(big)
    print(f"wrote corpus_code.txt: {used} files, {len(big):,} chars "
          f"({len(big)/1e6:.1f} MB)")

if __name__ == "__main__":
    main()
