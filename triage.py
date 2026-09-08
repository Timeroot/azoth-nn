import sys, math, re

path = sys.argv[1]
data = open(path, "rb").read()
print(f"file: {path}")
print(f"size: {len(data)} bytes ({len(data)/1024:.1f} KB)")

def ent(b):
    if not b: return 0.0
    from collections import Counter
    c = Counter(b); n = len(b)
    return -sum((v/n) * math.log2(v/n) for v in c.values())

print(f"overall entropy: {ent(data):.3f} bits/byte  (>7.5 ~ encrypted/compressed)")
# sliding window entropy to spot plaintext code regions
win = 2048
lows = []
for i in range(0, len(data) - win, win):
    e = ent(data[i:i+win])
    if e < 6.5:
        lows.append((i, e))
print(f"low-entropy (<6.5) windows: {len(lows)} of {len(data)//win}"
      + (f"  first at 0x{lows[0][0]:x}" if lows else ""))

# vector table sanity: nRF52 flash usually starts with initial SP then reset vec
import struct
if len(data) >= 8:
    sp, rv = struct.unpack_from("<II", data, 0)
    print(f"word0 (SP?)=0x{sp:08x}  word1 (reset?)=0x{rv:08x}")

print("\n=== known constants ===")
for name, pat in [
    ("meta 01 00 E8 03", b"\x01\x00\xe8\x03"),
    ("commit 50 55", b"\x50\x55"),
    ("start 61 01 00 00 00 71", b"\x61\x01\x00\x00\x00\x71"),
    ("dims D0 40 (208,64)", b"\xd0\x40"),
    ("IMMI", b"IMMI"), ("immis", b"immis"),
    ("Azoth", b"Azoth"), ("AZOTH", b"AZOTH"),
    ("GIF", b"GIF"), ("anim", b"anim"),
]:
    hits = [m.start() for m in re.finditer(re.escape(pat), data)]
    print(f"  {name:26s}: {len(hits)} hit(s)" + (f"  @ {[hex(h) for h in hits[:6]]}" if hits else ""))

print("\n=== ASCII strings (len>=5, first 60) ===")
for m in list(re.finditer(rb"[\x20-\x7e]{5,}", data))[:60]:
    print(f"  0x{m.start():06x}  {m.group().decode('ascii', 'replace')}")
