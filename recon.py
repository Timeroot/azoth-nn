import struct, re
BASE = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware"
fw = open(BASE + r"\M701_KEYBOARD_V04_00_13.bin", "rb").read()
print(f"FW image size: {len(fw)} = 0x{len(fw):x}  (nRF52840 flash = 0x100000)")

def looks_vtable(off):
    if off + 8 > len(fw):
        return None
    sp, rv = struct.unpack_from("<II", fw, off)
    if 0x20000000 <= sp <= 0x20040000 and (rv & 1) and (rv & ~1) < len(fw) + 0x100000:
        return sp, rv
    return None

print("\n=== candidate vector tables (SP in RAM + thumb reset) across flash ===")
for off in range(0, len(fw), 0x1000):
    v = looks_vtable(off)
    if v:
        print(f"  0x{off:06x}: SP=0x{v[0]:08x} reset=0x{v[1]:08x}")

# nRF SoftDevice info struct magic 0x51B1E5DB appears in SD; MBR at 0x0
print("\n=== markers ===")
for magic, name in [(b"\xdb\xe5\xb1\x51", "SD_INFO magic (SoftDevice present)"),
                    (b"NORDIC", "NORDIC"), (b"nRF", "nRF")]:
    hits = [hex(m.start()) for m in re.finditer(re.escape(magic), fw)][:6]
    print(f"  {name}: {hits}")

# region entropy (spot encrypted/SD vs code vs empty)
import math
from collections import Counter
def ent(b):
    if not b: return 0
    c = Counter(b); n = len(b)
    return -sum(v/n*math.log2(v/n) for v in c.values())
print("\n=== entropy by 64KB region ===")
for off in range(0, len(fw), 0x10000):
    seg = fw[off:off+0x10000]
    ff = seg.count(0xFF); z = seg.count(0x00)
    print(f"  0x{off:06x}: ent={ent(seg):.2f}  0xFF={ff*100//len(seg)}%  0x00={z*100//len(seg)}%")
