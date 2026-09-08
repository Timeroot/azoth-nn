import hid, time
VID, PIDS = 0x0B05, (0x1A83, 0x1ACE)
path = None
for pid in PIDS:
    for d in hid.enumerate(VID, pid):
        if (d.get("usage_page") or 0) == 0xFF00 and (d.get("usage") or 0) == 0x0001:
            path = d["path"]
dev = hid.device(); dev.open_path(path)

def w(data):
    dev.write(bytes(data) + bytes(65 - len(data)))

def read_match(want, ms=200):
    end = time.perf_counter() + ms/1000
    while time.perf_counter() < end:
        r = dev.read(65, 40)
        if r:
            b = bytes(r)
            for s in (0, 1):
                if len(b) >= s+len(want) and all(b[s+k] == want[k] for k in range(len(want))):
                    return b[:8].hex()
    return None

# entry
for c in ([0x02,0x12,0x03],[0x02,0x12,0x00],[0x02,0x12,0x01],[0x02,0x22,0x01],
          [0x02,0x12,0x12],[0x02,0x7d,0x20,0x02],[0x02,0x22,0x02]):
    w(c); time.sleep(0.03)
    try: dev.read(65, 40)
    except: pass
print("entered music mode")

# sustained visualizer stream ~3.5s at ~7/s
import math
for k in range(25):
    bars = [int(20+18*math.sin(k/2+i/3)) for i in range(40)]
    w([0x02,0x67,0x02,0x00,0x00]+bars)
    time.sleep(0.14)
print("streamed 25 visualizer frames")

# now inject AC-exact name header (w=456 npk=122 h=32) mid-stream
hdr = [0x02,0x67,0x00,0x00,0x02,0x02,0x7a,0x00,0xc8,0x01,0x20]
w(hdr)
ack = read_match((0x67,0x00), 300)
print("name header ack:", ack)
# a couple name data packets (idx 121 down), payload low bytes
for idx in (121, 120, 119):
    w([0x02,0x67,0x01, idx&0xff, (idx>>8)&0xff] + [0x33]*60)
    print(f"  sub01 idx={idx} ack:", read_match((0x67,0x01,idx&0xff,(idx>>8)&0xff), 200))
dev.close()
print("done")
