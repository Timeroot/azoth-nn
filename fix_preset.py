"""Recovery: spam the 'select firmware preset' command to knock the keyboard out
of a bad saved-custom-animation loop.  Retries opening the (re-enumerating)
device and fires the sequence every ~0.4s for a while.

  python fix_preset.py [preset_number]   # default 0
"""
import time, sys
import hid

VID, PIDS = 0x0B05, (0x1A83, 0x1ACE)
n = int(sys.argv[1]) if len(sys.argv) > 1 else 0
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 40.0

seq = [
    bytes([0x02, 0x12, 0x03]),           # picture mode
    bytes([0x02, 0x12, 0x01]),
    bytes([0x02, 0x61, 0x00, 0x00, 0x00, n]),   # select preset n
    bytes([0x02, 0x50, 0x55]),           # commit
]


def find():
    for pid in PIDS:
        for d in hid.enumerate(VID, pid):
            if (d.get("usage_page") or 0) == 0xFF00 and (d.get("usage") or 0) == 0x0001:
                return d["path"]
    return None


end = time.time() + secs
sent = 0
print(f"hammering preset {n} for {secs:.0f}s (Ctrl-C to stop)...", flush=True)
while time.time() < end:
    p = find()
    if not p:
        time.sleep(0.15)
        continue
    try:
        dev = hid.device()
        dev.open_path(p)
    except Exception:
        time.sleep(0.15)
        continue
    try:
        for pkt in seq:
            dev.write(bytes(pkt) + bytes(65 - len(pkt)))
            time.sleep(0.01)
        sent += 1
        print(f"  sent preset {n}  (#{sent})", flush=True)
    except Exception:
        pass
    try:
        dev.close()
    except Exception:
        pass
    time.sleep(0.4)
print(f"done - sent {sent} times", flush=True)
