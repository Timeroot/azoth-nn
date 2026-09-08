import struct
from collections import Counter

PCAP = r"C:\Users\Timeroot\azoth\azoth_musicmode.pcap"
data = open(PCAP, "rb").read()
off, recs = 24, []
while off + 16 <= len(data):
    ts_sec, ts_usec, incl, orig = struct.unpack_from("<IIII", data, off)
    off += 16
    recs.append((ts_sec + ts_usec / 1e6, data[off:off + incl]))
    off += incl
base = recs[0][0]

# find keyboard device address (most 64B OUT)
cnt = Counter()
parsed = []
for t, pkt in recs:
    if len(pkt) < 28:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    p = pkt[hlen:hlen + dlen]
    parsed.append((t - base, dev, ep, p))
    if ep == 0x02 and dlen == 64:
        cnt[dev] += 1
KB = cnt.most_common(1)[0][0]
print(f"keyboard dev={KB}  ({cnt[KB]} OUT pkts)")

# data-packet stream prefixes to suppress
def is_stream(p):
    return (p[:2] in (b"\x61\x02", b"\x62\x01", b"\x67\x01", b"\x67\x02"))

print("\n=== control/header OUT commands (streams collapsed) ===")
prev_stream = None
for t, dev, ep, p in parsed:
    if dev != KB or ep != 0x02 or not p:
        continue
    if is_stream(p):
        key = p[:2].hex()
        if key != prev_stream:
            print(f"  {t:7.2f}   <<{key} stream…>>")
            prev_stream = key
        continue
    prev_stream = None
    print(f"  {t:7.2f}   " + " ".join(f"{b:02x}" for b in p[:14]))
