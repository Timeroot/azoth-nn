import struct
from PIL import Image

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
m = []
for t, pkt in recs:
    if len(pkt) < 28:
        continue
    hlen = pkt[0] | (pkt[1] << 8)
    dev = pkt[19] | (pkt[20] << 8)
    ep = pkt[21]
    dlen = struct.unpack_from("<I", pkt, 23)[0]
    p = pkt[hlen:hlen + dlen]
    if dev == DEV and ep == 0x02 and dlen == 64 and p and p[0] == 0x67:
        m.append((t - base, p))

# sub=00 headers give (n_pkts, width, height) for the following sub=01 burst
headers = [(t, p[6], p[8] | (p[9] << 8), p[10]) for t, p in m if p[1] == 0x00]
print("headers (t, npkts, width, height):", [(round(t, 1), n, w, h) for t, n, w, h in headers])

s1 = [(t, p) for t, p in m if p[1] == 0x01]
# split into bursts by time gap
bursts, cur, last = [], [], None
for t, p in s1:
    if last is not None and t - last > 1.0:
        bursts.append(cur); cur = []
    cur.append((t, p)); last = t
if cur:
    bursts.append(cur)

for bi, bu in enumerate(bursts):
    # reassemble payload in idx order (byte[2] ascending)
    body = b"".join(p[3:] for _, p in sorted(bu, key=lambda x: x[1][2]))
    # match a header by nearest time before the burst
    hdr = min(headers, key=lambda h: abs(h[0] - bu[0][0]))
    _, npk, w, h = hdr
    need = (w * h + 1) // 2
    body = (body + b"\x00" * need)[:need]
    im = Image.new("L", (w, h))
    px = im.load()
    i = 0
    for y in range(h):
        for x in range(0, w, 2):
            b = body[i]; i += 1
            px[x, y] = (b & 0x0F) * 17
            if x + 1 < w:
                px[x + 1, y] = (b >> 4) * 17
    # scale up 3x for legibility
    im = im.resize((w * 3, h * 3), Image.NEAREST)
    out = rf"C:\Users\Timeroot\azoth\songname_{bi}_{w}x{h}.png"
    im.save(out)
    print(f"burst {bi}: {len(bu)} pkts, {w}x{h} -> {out}")
