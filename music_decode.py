import struct
from collections import Counter

PCAP = r"C:\Users\Timeroot\azoth\azoth_features.pcap"
DEV = 3
data = open(PCAP, "rb").read()
off, recs = 24, []
while off + 16 <= len(data):
    ts_sec, ts_usec, incl, orig = struct.unpack_from("<IIII", data, off)
    off += 16
    recs.append((ts_sec + ts_usec / 1e6, data[off:off + incl]))
    off += incl
base = recs[0][0]
pkts = []
for t, pkt in recs:
    if len(pkt) < 28:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    p = pkt[hlen:hlen + dlen]
    if dev == DEV and ep == 0x02 and dlen == 64 and p:
        pkts.append((t - base, p))
m = [(t, p) for t, p in pkts if p[0] == 0x67]

def txt(b):
    return "".join(chr(c) if 32 <= c < 127 else "." for c in b)

print("=== sub=00 headers (full) ===")
for t, p in [x for x in m if x[1][1] == 0x00]:
    print(f"  {t:6.1f}  " + " ".join(f"{b:02x}" for b in p[:32]))
    print(f"          {txt(p)}")

print("\n=== sub=01 indexed: idx range & reassembled ASCII per burst ===")
s1 = [(t, p) for t, p in m if p[1] == 0x01]
print(f"  count={len(s1)}  idx(byte2) seen: {sorted(set(p[2] for _,p in s1))[:5]}..{sorted(set(p[2] for _,p in s1))[-3:]}")
# group into bursts by time gap, reassemble payload (bytes after 67 01 idx)
bursts, cur, last = [], [], None
for t, p in s1:
    if last is not None and t - last > 1.0:
        bursts.append(cur); cur = []
    cur.append((t, p)); last = t
if cur: bursts.append(cur)
for bi, bu in enumerate(bursts):
    body = b"".join(p[3:] for _, p in sorted(bu, key=lambda x: -x[1][2]))
    s = txt(body)
    printable = "".join(ch for ch in s if ch != ".")
    print(f"  burst {bi} @ {bu[0][0]:.1f}s  {len(bu)} pkts  text-ish: {printable[:80]!r}")

print("\n=== sub=02 visualizer: UTF-8 decode -> bar heights ===")
s2 = [(t, p) for t, p in m if p[1] == 0x02]
print(f"  byte[3] (xx) values: {sorted(set(p[3] for _,p in s2))}")
def bars(p):
    body = bytes(p[4:]).rstrip(b"\x00")
    try:
        cps = [ord(c) for c in body.decode("utf-8", "replace")]
    except Exception:
        cps = list(body)
    return [c if c != 0xFFFD else -1 for c in cps]   # -1 = mangled (was some high value)
step = max(1, len(s2) // 22)
for i in range(0, len(s2), step):
    t, p = s2[i]
    b = bars(p)
    tag = "SILENT" if sum(1 for x in b if x > 0) <= 1 else f"{len(b)} bars"
    print(f"  {t:6.1f} [{tag:8}] " + " ".join(f"{x:3d}" for x in b))
