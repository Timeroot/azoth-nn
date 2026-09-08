#!/usr/bin/env python3
"""Build the GRU predictor: compile with FPU, place code in the app tail and the
20KB float weights in the erased flash region at 0x50000, inject, expand the DFU
write range, checksum, write image."""
import struct, subprocess, sys, os, math
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

STOCK = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT   = r"C:\Users\Timeroot\azoth\fw_balls.bin"
GCC   = open(r"C:\Users\Timeroot\azoth\firmware_re\armgcc_path.txt").read().strip()
OBJCOPY = GCC.replace("gcc.exe","objcopy.exe")
HERE  = os.path.dirname(os.path.abspath(__file__))

HOOK_AT  = 0x31658
RESUME   = 0x31660
CODE_AT  = 0x4d500          # shim
RENDER_AT= 0x4d560          # C code + rodata (font) in app tail
DATA_AT  = 0x50000          # weights in erased region (non-destructive)
CKSUM_AT = 0x4dffc
APP_LO   = 0x1c000
CPACR    = 0xE000ED88

src = os.path.join(HERE, sys.argv[1] if len(sys.argv)>1 else "gru.c")
elf = os.path.join(HERE,"out.elf")

ld = os.path.join(HERE,"link.ld")
open(ld,"w").write(f"""
ENTRY(render)
SECTIONS {{
  . = 0x{RENDER_AT:x};
  .text : {{ *(.text.render) *(.text*) *(.rodata*) }}
  . = 0x{DATA_AT:x};
  .weights : {{ *(.weights) }}
  /DISCARD/ : {{ *(.ARM.exidx*) *(.comment) *(.ARM.attributes) }}
}}
""")

cc = [GCC,"-mcpu=cortex-m4","-mthumb","-mfpu=fpv4-sp-d16","-mfloat-abi=softfp",
      "-Os","-ffreestanding","-fno-builtin","-fomit-frame-pointer","-nostdlib",
      "-Wall","-Wextra","-T",ld,"-o",elf,src]
print("CC:", " ".join(cc[-6:]))
subprocess.run(cc, check=True)

# unresolved symbol check
nm = subprocess.run([GCC.replace("gcc.exe","nm.exe"),elf],capture_output=True,text=True)
undef=[l for l in nm.stdout.splitlines() if " U " in l]
if undef: print("!! UNDEFINED:"); print("\n".join(undef)); sys.exit(1)

lo = os.path.join(HERE,"lo.bin"); wb = os.path.join(HERE,"w.bin")
subprocess.run([OBJCOPY,"-O","binary","-j",".text",elf,lo],check=True)
subprocess.run([OBJCOPY,"-O","binary","-j",".weights",elf,wb],check=True)
code=open(lo,"rb").read(); weights=open(wb,"rb").read()
print(f"code+font: {len(code)} B @0x{RENDER_AT:x}   weights: {len(weights)} B @0x{DATA_AT:x}")

# shim: match flush frame, enable FPU (CPACR), call render(fb,len), resume
ks=Ks(KS_ARCH_ARM,KS_MODE_THUMB|KS_MODE_LITTLE_ENDIAN)
shim_asm=f"""
    push {{r4,r5,r6,lr}}
    mov  r4, r0
    mov  r5, r1
    movw r3, #{CPACR & 0xffff}
    movt r3, #{(CPACR>>16)&0xffff}
    ldr  r0, [r3]
    orr  r0, r0, #0x00F00000
    str  r0, [r3]
    isb  sy
    mov  r0, r4
    mov  r1, r5
    bl   #{RENDER_AT}
    movs r0, #0x10
    movw r3, #{RESUME&0xffff}
    movt r3, #{(RESUME>>16)&0xffff}
    orr  r3, r3, #1
    bx   r3
"""
shim,_=ks.asm(shim_asm,CODE_AT); shim=bytes(shim)
assert CODE_AT+len(shim)<=RENDER_AT, f"shim too big {len(shim)}"
print(f"shim: {len(shim)} B @0x{CODE_AT:x}")

# inject
d=bytearray(open(STOCK,"rb").read())
assert RENDER_AT+len(code) < CKSUM_AT, "code overruns checksum"
assert set(d[CODE_AT:RENDER_AT+len(code)])<= {0}, "code region not free"
d[CODE_AT:CODE_AT+len(shim)]=shim
d[RENDER_AT:RENDER_AT+len(code)]=code
d[DATA_AT:DATA_AT+len(weights)]=weights
tramp=bytes([0x00,0x4b,0x18,0x47])+struct.pack("<I",CODE_AT|1)
d[HOOK_AT:HOOK_AT+len(tramp)]=tramp
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4),x))&0xffffffff
newck=sum32(d[APP_LO:CKSUM_AT]); d[CKSUM_AT:CKSUM_AT+4]=struct.pack("<I",newck)
open(OUT,"wb").write(d)

# APP_SIZE (KB) must cover up to DATA_AT+weights
app_kb = math.ceil((DATA_AT+len(weights) - APP_LO)/1024)
print(f"checksum=0x{newck:08x}  wrote {OUT}")
print(f">>> FLASH APP_SIZE = {app_kb} KB   (cmd: m 1A83 1A84 112 {app_kb} FF00 FF00 4 <bin> CVER:n)")
open(os.path.join(HERE,"app_kb.txt"),"w").write(str(app_kb))
