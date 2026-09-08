#!/usr/bin/env python3
"""Compile a C renderer, link it at a fixed flash address, objcopy to raw bytes,
prepend a tiny asm shim that detours FUN_00031658, inject + checksum + write image.
Usage: python build_c.py <source.c>  (default balls.c)"""
import struct, subprocess, sys, os
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

STOCK = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT   = r"C:\Users\Timeroot\azoth\fw_balls.bin"
GCC   = open(r"C:\Users\Timeroot\azoth\firmware_re\armgcc_path.txt").read().strip()
OBJCOPY = GCC.replace("gcc.exe", "objcopy.exe")
HERE  = os.path.dirname(os.path.abspath(__file__))

HOOK_AT  = 0x31658
RESUME   = 0x31660
CODE_AT  = 0x4d500          # shim goes here
RENDER_AT= 0x4d520          # C blob goes here (shim is <32 bytes)
CKSUM_AT = 0x4dffc
APP_LO   = 0x1c000

src = sys.argv[1] if len(sys.argv) > 1 else "balls.c"
src = os.path.join(HERE, src)
elf = os.path.join(HERE, "out.elf")
binf= os.path.join(HERE, "out.bin")

# linker script: place render first at RENDER_AT
ld = os.path.join(HERE, "link.ld")
open(ld, "w").write(f"""
ENTRY(render)
SECTIONS {{
  . = 0x{RENDER_AT:x};
  .text : {{ *(.text.render) *(.text*) *(.rodata*) *(.data*) }}
  /DISCARD/ : {{ *(.ARM.exidx*) *(.comment) }}
}}
""")

cc = [GCC, "-mcpu=cortex-m4", "-mthumb", "-Os", "-ffreestanding", "-fno-builtin",
      "-fomit-frame-pointer", "-nostdlib", "-Wall", "-Wextra",
      "-T", ld, "-o", elf, src]
print("CC:", " ".join(cc))
subprocess.run(cc, check=True)
subprocess.run([OBJCOPY, "-O", "binary", elf, binf], check=True)
cblob = open(binf, "rb").read()
print(f"C blob: {len(cblob)} bytes @ 0x{RENDER_AT:x}")

# check for unresolved external calls (would mean missing libc helper)
nm = subprocess.run([GCC.replace("gcc.exe","nm.exe"), elf], capture_output=True, text=True)
undef = [l for l in nm.stdout.splitlines() if " U " in l]
if undef:
    print("!! UNDEFINED SYMBOLS (need runtime helpers):"); print("\n".join(undef)); sys.exit(1)

# asm shim: replicate the 4 overwritten flush insns' frame, call render(fb,len), resume
ks = Ks(KS_ARCH_ARM, KS_MODE_THUMB | KS_MODE_LITTLE_ENDIAN)
shim_asm = f"""
    push {{r4, r5, r6, lr}}
    mov  r4, r0
    mov  r5, r1
    bl   #{RENDER_AT}
    movs r0, #0x10
    movw r3, #{RESUME & 0xffff}
    movt r3, #{(RESUME>>16)&0xffff}
    orr  r3, r3, #1
    bx   r3
"""
shim, _ = ks.asm(shim_asm, CODE_AT)
shim = bytes(shim)
assert CODE_AT + len(shim) <= RENDER_AT, f"shim too big ({len(shim)}B)"
print(f"shim: {len(shim)} bytes @ 0x{CODE_AT:x}")

# --- inject ---
d = bytearray(open(STOCK, "rb").read())
assert RENDER_AT + len(cblob) < CKSUM_AT, "C blob overruns checksum word"
region = d[CODE_AT:RENDER_AT+len(cblob)]
assert set(region) <= {0}, "target region not free!"
d[CODE_AT:CODE_AT+len(shim)] = shim
d[RENDER_AT:RENDER_AT+len(cblob)] = cblob
tramp = bytes([0x00,0x4b, 0x18,0x47]) + struct.pack("<I", CODE_AT | 1)
d[HOOK_AT:HOOK_AT+len(tramp)] = tramp
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4), x)) & 0xffffffff
newck = sum32(d[APP_LO:CKSUM_AT])
d[CKSUM_AT:CKSUM_AT+4] = struct.pack("<I", newck)
open(OUT, "wb").write(d)
print(f"checksum = 0x{newck:08x}; wrote {OUT}")

# show a bit of the compiled render for sanity
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
print("--- render() head ---")
for i in list(md.disasm(cblob, RENDER_AT))[:12]:
    print("  %06x: %-11s %s %s" % (i.address, " ".join("%02x"%b for b in i.bytes), i.mnemonic, i.op_str))
