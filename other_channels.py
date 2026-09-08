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

TRANSFER = {0: "ISO", 1: "INTR", 2: "CTRL", 3: "BULK"}
# find keyboard dev (most interrupt OUT on 0x02)
cnt = Counter()
rows = []
for t, pkt in recs:
    if len(pkt) < 27:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    xfer = pkt[22]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    payload = pkt[hlen:hlen + dlen]
    rows.append((t - base, dev, ep, xfer, dlen, hlen, payload, pkt))
    if ep == 0x02 and xfer == 1 and dlen == 64:
        cnt[dev] += 1
KB = cnt.most_common(1)[0][0]
print(f"keyboard dev={KB}")

print("\n=== ALL (transfer, endpoint, dir) to/from keyboard: histogram ===")
h = Counter()
for t, dev, ep, xfer, dlen, hlen, pl, pkt in rows:
    if dev != KB:
        continue
    d = "IN" if ep & 0x80 else "OUT"
    h[(TRANSFER.get(xfer, xfer), f"ep{ep:02x}", d)] += 1
for k, v in sorted(h.items()):
    print(f"  {k}: {v}")

print("\n=== CONTROL transfers to keyboard (setup + data) ===")
n = 0
for t, dev, ep, xfer, dlen, hlen, pl, pkt in rows:
    if dev != KB or xfer != 2:
        continue
    # USBPcap control header has an extra 'stage' byte + 8-byte setup at end of header
    setup = pkt[hlen - 8:hlen] if hlen >= 8 else b""
    print(f"  {t:7.2f} ep{ep:02x} hlen={hlen} dlen={dlen} setup={setup.hex()} data={pl[:16].hex()}")
    n += 1
    if n > 40:
        break

print("\n=== non-0x02/0x82 INTERRUPT/BULK OUT to keyboard (other interfaces) ===")
n = 0
for t, dev, ep, xfer, dlen, hlen, pl, pkt in rows:
    if dev != KB or ep in (0x02, 0x82) or (ep & 0x80):
        continue
    if dlen == 0:
        continue
    print(f"  {t:7.2f} ep{ep:02x} {TRANSFER.get(xfer)} dlen={dlen} {pl[:16].hex()}")
    n += 1
    if n > 40:
        break
