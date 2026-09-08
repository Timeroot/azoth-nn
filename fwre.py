import re, sys, struct
FW = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
d = open(FW, "rb").read()
print(f"size {len(d)}  reset=0x{struct.unpack_from('<I',d,4)[0]&~1:x}")

print("\n=== readable strings (words, len>=5) ===")
seen = set()
for m in re.finditer(rb"[\x20-\x7e]{5,}", d):
    s = m.group().decode("ascii")
    if re.search(r"[A-Za-z]{4,}", s) and s not in seen:
        seen.add(s)
        print(f"  0x{m.start():06x}  {s}")
        if len(seen) > 70:
            break

print("\n=== 'ff aa' NAK byte sites (context) ===")
for m in re.finditer(rb"\xff\xaa", d):
    o = m.start()
    print(f"  0x{o:06x}  ..{d[o-4:o+8].hex()}..")

print("\n=== capstone: cmp/sub #imm sites for OLED command bytes ===")
try:
    from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_LITTLE_ENDIAN
except ImportError:
    print("  capstone not installed"); sys.exit()
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_LITTLE_ENDIAN)
md.detail = False
WANT = {0x61, 0x66, 0x67, 0x12, 0x22, 0x7d, 0x50, 0xaa, 0x63, 0x64}
hits = {}
# linear sweep, thumb; note data regions produce noise but cmp #imm is a decent anchor
for base in range(0, len(d) - 0x1000, 0x1000):
    for insn in md.disasm(d[base:base + 0x1000], base):
        if insn.mnemonic in ("cmp", "cmp.w", "subs", "cmp.n") and "#" in insn.op_str:
            m = re.search(r"#(?:0x)?([0-9a-fA-F]+)", insn.op_str)
            if m:
                try: v = int(m.group(1), 16)
                except ValueError: continue
                if v in WANT:
                    hits.setdefault(v, []).append(insn.address)
for v in sorted(hits):
    addrs = hits[v]
    print(f"  #0x{v:02x}: {len(addrs)} sites  e.g. {[hex(a) for a in addrs[:8]]}")
