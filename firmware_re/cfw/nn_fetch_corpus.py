#!/usr/bin/env python3
"""Download several public-domain Project Gutenberg .txt files and concatenate them
(with the existing corpus_raw.txt) into corpus_big.txt. Mixes genres: novels, essays,
philosophy, adventure, science. Strips Gutenberg headers/footers. Browser UA."""
import os, re, urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120 Safari/537.36"

# (gutenberg id, label) -- diverse public-domain works
BOOKS = [
    (84,   "Frankenstein"),
    (1661, "Sherlock Holmes"),
    (2701, "Moby Dick"),
    (1400, "Great Expectations"),
    (98,   "Tale of Two Cities"),
    (74,   "Tom Sawyer"),
    (345,  "Dracula"),
    (174,  "Dorian Gray"),
    (1260, "Jane Eyre"),
    (158,  "Emma"),
    (2600, "War and Peace"),
    (76,   "Huckleberry Finn"),
    (1232, "The Prince (essay)"),
    (3300, "Wealth of Nations (essay)"),
    (1080, "A Modest Proposal (essay)"),
    (2542, "A Doll's House (play)"),
    (5200, "Metamorphosis"),
    (16,   "Peter Pan"),
    (25344,"Scarlet Letter"),
    (1497, "Republic (Plato, essay)"),
]

def fetch(gid):
    urls = [
        f"https://www.gutenberg.org/cache/epub/{gid}/pg{gid}.txt",
        f"https://www.gutenberg.org/files/{gid}/{gid}-0.txt",
        f"https://www.gutenberg.org/files/{gid}/{gid}.txt",
    ]
    for u in urls:
        try:
            req = urllib.request.Request(u, headers={"User-Agent": UA})
            with urllib.request.urlopen(req, timeout=60) as r:
                raw = r.read().decode("utf-8", errors="ignore")
            if len(raw) > 2000:
                return raw
        except Exception as e:
            last = e
    print(f"  !! failed {gid}: {last}")
    return None

def strip_gutenberg(t):
    # remove header up to START marker and footer from END marker
    m = re.search(r"\*\*\*\s*START OF (THE|THIS) PROJECT GUTENBERG.*?\*\*\*", t, re.I|re.S)
    if m: t = t[m.end():]
    m = re.search(r"\*\*\*\s*END OF (THE|THIS) PROJECT GUTENBERG", t, re.I)
    if m: t = t[:m.start()]
    return t

def main():
    chunks = []
    base = os.path.join(HERE, "corpus_raw.txt")
    if os.path.exists(base):
        chunks.append(open(base, "r", encoding="utf-8", errors="ignore").read())
        print(f"seed corpus_raw.txt: {len(chunks[0])} chars")
    for gid, label in BOOKS:
        raw = fetch(gid)
        if raw is None: continue
        t = strip_gutenberg(raw)
        chunks.append(t)
        print(f"  {gid:6d} {label:32s} {len(t):>9d} chars")
    big = "\n\n".join(chunks)
    out = os.path.join(HERE, "corpus_big.txt")
    open(out, "w", encoding="utf-8").write(big)
    # quick estimate of cleaned symbol count
    cleaned = re.sub(r"[^a-z]+", " ", big.lower())
    print(f"\nwrote {out}: {len(big):,} raw chars, ~{len(cleaned):,} cleaned symbols")

if __name__ == "__main__":
    main()
