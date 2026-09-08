import struct

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
ev = []
for t, pkt in recs:
    if len(pkt) < 28:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    p = pkt[hlen:hlen + dlen]
    if dev == DEV and ep in (0x02, 0x82) and dlen > 0:
        ev.append((t - base, ep, p))

# window: from just before music (music OUT starts ~122.4) up to first name burst end
print("=== all non-(67 02) OUT commands 85..123s (find music entry) ===")
for t, ep, p in ev:
    if ep == 0x02 and 85.0 <= t <= 123.0 and not (p[0] == 0x67 and p[1] == 0x02):
        print(f"  {t:7.2f} {' '.join(f'{b:02x}' for b in p[:12])}")
