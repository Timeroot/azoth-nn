import struct

PCAP = r"C:\Users\Timeroot\azoth\azoth_musicmode.pcap"
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
    if len(pkt) < 27:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    p = pkt[hlen:hlen + dlen]
    if dev == 26 and ep in (0x02, 0x82) and dlen:
        ev.append((t - base, ep, p))

# collapse the visualizer stream, but show 67 00 / 67 01-first / acks around 52-55s
print("=== ep02 OUT (>) + 82 ack (<), 52.0..54.5s, visualizer collapsed ===")
last_vis = None
for t, ep, p in ev:
    if not (52.0 <= t <= 54.5):
        continue
    tag = ">" if ep == 0x02 else "<"
    if ep == 0x02 and p[:2] == b"\x67\x02":
        if last_vis != "v":
            print(f"  {t:7.3f} > <<67 02 visualizer…>>")
            last_vis = "v"
        continue
    if ep == 0x02:
        last_vis = None
    print(f"  {t:7.3f} {tag} {' '.join(f'{b:02x}' for b in p[:14])}")
