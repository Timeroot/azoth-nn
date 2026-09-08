#!/usr/bin/env python3
"""Train a letter trigram model (27 symbols: a-z + space) from a corpus and emit
trigram.h: for each (c2,c1) context, the top-3 next symbols, packed 5b each into
a uint16. Backoff: trigram -> bigram -> unigram so every context has 3 preds."""
import re, collections, os
HERE = os.path.dirname(os.path.abspath(__file__))
SP = 26  # space / word separator

def load(path):
    t = open(path, "r", encoding="utf-8", errors="ignore").read().lower()
    t = re.sub(r"[^a-z]+", " ", t)          # non-letters -> space
    t = re.sub(r" +", " ", t).strip()
    return [ord(c)-97 if c != " " else SP for c in t]

syms = load(os.path.join(HERE, "corpus_raw.txt"))
print("corpus symbols:", len(syms))

tri = collections.Counter()   # (c2,c1,n)
big = collections.Counter()   # (c1,n)
uni = collections.Counter()   # (n)
for i in range(2, len(syms)):
    c2,c1,n = syms[i-2], syms[i-1], syms[i]
    tri[(c2,c1,n)] += 1; big[(c1,n)] += 1; uni[n] += 1

uni_rank = [s for s,_ in sorted(uni.items(), key=lambda kv:-kv[1])]

def top3(c2, c1):
    ranked = []
    seen = set()
    # trigram candidates
    cands = sorted(((n,cnt) for (a,b,n),cnt in tri.items() if a==c2 and b==c1),
                   key=lambda kv:-kv[1])
    for n,_ in cands:
        if n not in seen: seen.add(n); ranked.append(n)
    # bigram backoff
    bc = sorted(((n,cnt) for (b,n),cnt in big.items() if b==c1), key=lambda kv:-kv[1])
    for n,_ in bc:
        if n not in seen: seen.add(n); ranked.append(n)
    # unigram backoff
    for n in uni_rank:
        if n not in seen: seen.add(n); ranked.append(n)
    return ranked[:3]

table = []
for c2 in range(27):
    for c1 in range(27):
        p = top3(c2,c1)
        while len(p) < 3: p.append(SP)
        v = (p[0] & 31) | ((p[1] & 31)<<5) | ((p[2] & 31)<<10)
        table.append(v)

# sanity print a few
def s(i): return "_" if i==SP else chr(97+i)
for ctx in [(SP,SP),(ord('t')-97,ord('h')-97),(ord('q')-97,SP),(SP,ord('t')-97),
            (ord('i')-97,ord('n')-97),(ord('a')-97,ord('n')-97)]:
    c2,c1=ctx; v=table[c2*27+c1]
    print(f"  '{s(c2)}{s(c1)}' -> {s(v&31)} {s((v>>5)&31)} {s((v>>10)&31)}")

with open(os.path.join(HERE,"trigram.h"),"w") as f:
    f.write("/* auto-generated letter-trigram top-3 table (27 syms: a-z,space)\n")
    f.write(" * index = c2*27 + c1 ; uint16 = p0|p1<<5|p2<<10 (5 bits each) */\n")
    f.write("#define TRI_N 27\n")
    f.write("static const unsigned short TRI[729] = {\n")
    for i in range(0,729,12):
        f.write("  " + ",".join("0x%04x"%v for v in table[i:i+12]) + ",\n")
    f.write("};\n")
print("wrote trigram.h (", len(table)*2, "bytes table )")
