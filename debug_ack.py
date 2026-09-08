import hid, time
VID, PIDS = 0x0B05, (0x1A83, 0x1ACE)
path = None
for pid in PIDS:
    for d in hid.enumerate(VID, pid):
        if (d.get("usage_page") or 0) == 0xFF00 and (d.get("usage") or 0) == 0x0001:
            path = d["path"]
dev = hid.device(); dev.open_path(path)

def wr(data):
    dev.write(bytes(data) + bytes(65 - len(data)))

def drain(tag, n=4):
    for _ in range(n):
        r = dev.read(65, 120)
        print(f"  {tag}: {bytes(r).hex() if r else 'EMPTY'}")

wr([0x02, 0x12, 0x03]); time.sleep(0.02)
wr([0x02, 0x12, 0x01]); time.sleep(0.02)
print("start 61 01 00 00 4d 01 (fixed: two 00s):")
wr([0x02, 0x61, 0x01, 0x00, 0x00, 0x4d, 0x01])
drain("after-start")
payload = [0x03, 0x00, 0x2c, 0x01, 0x2c, 0x01, 0x2c, 0x01] + [0xff] * 52
print("data0 61 02 4c 01 ...:")
wr([0x02, 0x61, 0x02, 0x4c, 0x01] + payload)
drain("after-data0", 6)
# NOTE: intentionally NO 61 03 / 50 55 commit -> nothing saved, safe
dev.close()
print("done (no commit sent)")
