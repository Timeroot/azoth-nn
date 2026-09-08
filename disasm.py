import sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_LITTLE_ENDIAN
FW = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
d = open(FW, "rb").read()
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_LITTLE_ENDIAN)

def dis(start, length, label=""):
    print(f"\n===== {label}  0x{start:x}..0x{start+length:x} =====")
    for insn in md.disasm(d[start:start + length], start):
        b = insn.bytes.hex()
        print(f"  0x{insn.address:06x}  {b:<8}  {insn.mnemonic:8} {insn.op_str}")

for spec in sys.argv[1:]:
    a, l = spec.split(":")
    dis(int(a, 16), int(l), spec)
