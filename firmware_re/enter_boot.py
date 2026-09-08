#!/usr/bin/env python3
"""Send the ASUS bootloader-entry magic to the Azoth (PID 0x1A83), FF00/usage1,
so it re-enumerates as PID 0x1A84 (DFU). Magic: 02 7b aa 41 53 55 53 aa."""
import hid, sys, time
VID, PID_APP, PID_BOOT = 0x0B05, 0x1A83, 0x1A84
MAGIC = [0x02,0x7b,0xaa,0x41,0x53,0x55,0x53,0xaa]
RLEN = 65

def find(pid):
    for d in hid.enumerate(VID, pid):
        if (d.get("usage_page") or 0)==0xFF00 and (d.get("usage") or 0)==0x0001:
            return d["path"]
    return None

if find(PID_BOOT):
    print("Already in BOOT mode (1A84)."); sys.exit(0)
p = find(PID_APP)
if not p:
    print("Device not found in APP mode (1A83)."); sys.exit(1)
dev = hid.device(); dev.open_path(p)
dev.write(bytes(MAGIC) + bytes(RLEN-len(MAGIC)))
print("magic sent; waiting for re-enumeration...")
dev.close()
for _ in range(40):
    time.sleep(0.25)
    if find(PID_BOOT):
        print("Device now in BOOT mode (1A84)."); sys.exit(0)
print("Did not see BOOT mode after 10s."); sys.exit(2)
