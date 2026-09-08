"""Resolve movw/movt (and ldr-literal) address loads in the Azoth firmware to build
an xref map, then report what references the HID/OLED strings & data of interest.
Runs without Ghidra."""
import re, struct
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_LITTLE_ENDIAN

FW = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
d = open(FW, "rb").read()
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_LITTLE_ENDIAN)

# code regions worth sweeping (skip SoftDevice + erased gap)
REGIONS = [(0x27000, 0x48000), (0xd0000, 0xf3000)]

# target -> list of code addresses that load that address
xrefs = {}
def note(src, tgt):
    if 0x1000 <= tgt < 0xff000:
        xrefs.setdefault(tgt, []).append(src)

for lo, hi in REGIONS:
    reg_lo = {}                 # regname -> (value_low, addr_of_movw)
    for insn in md.disasm(d[lo:hi], lo):
        m, ops = insn.mnemonic, insn.op_str
        if m == "movw":
            mm = re.match(r"(\w+), #(?:0x)?([0-9a-fA-F]+)", ops)
            if mm: reg_lo[mm.group(1)] = int(mm.group(2), 16)
        elif m == "movt":
            mm = re.match(r"(\w+), #(?:0x)?([0-9a-fA-F]+)", ops)
            if mm and mm.group(1) in reg_lo:
                note(insn.address, reg_lo[mm.group(1)] | (int(mm.group(2), 16) << 16))
        elif m in ("ldr",) and "[pc" in ops:            # literal pool load
            mm = re.search(r"\[pc, #(?:0x)?(-?[0-9a-fA-F]+)\]", ops)
            if mm:
                pool = (insn.address + 4 & ~3) + int(mm.group(1), 16)
                if 0 <= pool < len(d) - 4:
                    note(insn.address, struct.unpack_from("<I", d, pool)[0])

def report(name, lo, hi):
    print(f"\n=== xrefs into {name} (0x{lo:x}-0x{hi:x}) ===")
    for tgt in sorted(t for t in xrefs if lo <= t < hi):
        s = ""
        mm = re.match(rb"[\x20-\x7e]{4,}", d[tgt:tgt+40])
        if mm: s = "  '" + mm.group().decode() + "'"
        print(f"  ->0x{tgt:06x} by {[hex(a) for a in xrefs[tgt][:6]]}{s}")

report("RX-log / de000 string+code block", 0xde000, 0xde800)
report("ff-aa NAK area", 0x12600, 0x12800)
report("aa-immediate cluster", 0x3a000, 0x3a400)
print(f"\ntotal distinct targets xref'd: {len(xrefs)}")
