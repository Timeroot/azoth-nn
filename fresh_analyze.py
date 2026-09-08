import struct
from collections import Counter

PCAP = r"C:\Users\Timeroot\azoth\azoth_fresh.pcap"
data = open(PCAP, "rb").read()
off, recs = 24, []
while off + 16 <= len(data):
    ts_sec, ts_usec, incl, orig = struct.unpack_from("<IIII", data, off)
    off += 16
    recs.append((ts_sec + ts_usec / 1e6, data[off:off + incl]))
    off += incl
base = recs[0][0]
cnt = Counter()
rows = []
for t, pkt in recs:
    if len(pkt) < 27:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    p = pkt[hlen:hlen + dlen]
    rows.append((t - base, dev, ep, dlen, p))
    if ep == 0x02 and dlen == 64:
        cnt[dev] += 1
KB = cnt.most_common(1)[0][0]
print(f"keyboard dev={KB}")

def is_stream(p):
    return len(p) >= 2 and p[:2] in (b"\x61\x02", b"\x62\x01", b"\x67\x01", b"\x67\x02")

# build quick ack lookup: for each OUT 67 00 at time t, find the 0x82 IN just after
ins = [(t, p) for t, dev, ep, dlen, p in rows if dev == KB and ep == 0x82 and dlen]

def ack_after(t0):
    for t, p in ins:
        if t >= t0 and t < t0 + 0.05:
            return p[:6].hex()
    return "?"

print("\n=== control/header OUT (streams collapsed), whole session ===")
prev = None
for t, dev, ep, dlen, p in rows:
    if dev != KB or ep != 0x02 or not p:
        continue
    if is_stream(p):
        k = p[:2].hex()
        if k != prev:
            print(f"  {t:7.2f}   <<{k} stream…>>")
            prev = k
        continue
    prev = None
    note = ""
    if p[:2] == b"\x67\x00":
        note = f"   -> ack {ack_after(t)}"
    print(f"  {t:7.2f}   " + " ".join(f"{b:02x}" for b in p[:12]) + note)
