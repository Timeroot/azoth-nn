#!/usr/bin/env python3
"""Build the big GRU (H=256) predictor: compile nn.c, place code in the app tail,
inject nn_weights.bin (266KB int8) at flash 0x50000, FPU shim + flush detour,
expand DFU write range, checksum. Produces fw_balls.bin (does NOT flash)."""
import struct, subprocess, os, math
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN

STOCK = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT   = r"C:\Users\Timeroot\azoth\fw_balls.bin"
GCC   = open(r"C:\Users\Timeroot\azoth\firmware_re\armgcc_path.txt").read().strip()
OBJCOPY = GCC.replace("gcc.exe","objcopy.exe")
HERE  = os.path.dirname(os.path.abspath(__file__))

HOOK_AT=0x31658; RESUME=0x31660; CODE_AT=0x4d500; RENDER_AT=0x4d560
DATA_AT=0x50000; CKSUM_AT=0x4dffc; APP_LO=0x1c000; CPACR=0xE000ED88

elf=os.path.join(HERE,"nn.elf"); ld=os.path.join(HERE,"nn_link.ld")
open(ld,"w").write(f"ENTRY(render)\nSECTIONS {{ . = 0x{RENDER_AT:x}; .text : {{ *(.text.render) *(.text*) *(.rodata*) }} /DISCARD/ : {{ *(.ARM.exidx*) *(.comment) *(.ARM.attributes) }} }}\n")
subprocess.run([GCC,"-mcpu=cortex-m4","-mthumb","-mfpu=fpv4-sp-d16","-mfloat-abi=softfp",
      "-Os","-ffreestanding","-fno-builtin","-fomit-frame-pointer","-nostdlib",
      "-T",ld,"-o",elf,os.path.join(HERE,"nn.c")],check=True)
nm=subprocess.run([GCC.replace("gcc.exe","nm.exe"),elf],capture_output=True,text=True)
undef=[l for l in nm.stdout.splitlines() if " U " in l]
if undef: print("UNDEFINED:","\n".join(undef)); raise SystemExit(1)
lo=os.path.join(HERE,"nn_lo.bin"); subprocess.run([OBJCOPY,"-O","binary","-j",".text",elf,lo],check=True)
code=open(lo,"rb").read()
weights=open(os.path.join(HERE,"nn_weights.bin"),"rb").read()
print(f"code {len(code)}B @0x{RENDER_AT:x}   weights {len(weights)}B @0x{DATA_AT:x}")

ks=Ks(KS_ARCH_ARM,KS_MODE_THUMB|KS_MODE_LITTLE_ENDIAN)
shim,_=ks.asm(f"""
 push {{r4,r5,r6,lr}}
 mov r4,r0
 mov r5,r1
 movw r3,#{CPACR&0xffff}
 movt r3,#{(CPACR>>16)&0xffff}
 ldr r0,[r3]
 orr r0,r0,#0x00F00000
 str r0,[r3]
 isb sy
 mov r0,r4
 mov r1,r5
 bl #{RENDER_AT}
 movs r0,#0x10
 movw r3,#{RESUME&0xffff}
 movt r3,#{(RESUME>>16)&0xffff}
 orr r3,r3,#1
 bx r3
""",CODE_AT); shim=bytes(shim)
assert CODE_AT+len(shim)<=RENDER_AT

d=bytearray(open(STOCK,"rb").read())
assert RENDER_AT+len(code)<CKSUM_AT
assert set(d[CODE_AT:RENDER_AT+len(code)])<= {0}
d[CODE_AT:CODE_AT+len(shim)]=shim
d[RENDER_AT:RENDER_AT+len(code)]=code
d[DATA_AT:DATA_AT+len(weights)]=weights
d[HOOK_AT:HOOK_AT+8]=bytes([0x00,0x4b,0x18,0x47])+struct.pack("<I",CODE_AT|1)
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4),x))&0xffffffff
ck=sum32(d[APP_LO:CKSUM_AT]); d[CKSUM_AT:CKSUM_AT+4]=struct.pack("<I",ck)
open(OUT,"wb").write(d)
app_kb=math.ceil((DATA_AT+len(weights)-APP_LO)/1024)
print(f"checksum=0x{ck:08x}  wrote {OUT}")
print(f">>> FLASH APP_SIZE = {app_kb} KB")
open(os.path.join(HERE,"nn_app_kb.txt"),"w").write(str(app_kb))
