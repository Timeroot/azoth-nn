#!/usr/bin/env python3
"""Combined firmware: char-GRU predictor on the OLED (flush detour @0x31658 -> render)
AND a prediction-tinted flowing rainbow on the backlight (LED detour @0x31b28 ->
led_fill). Weights from combo_weights.bin at 0x50000."""
import struct, subprocess, os, math
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN

STOCK=r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT=r"C:\Users\Timeroot\azoth\fw_balls.bin"
GCC=open(r"C:\Users\Timeroot\azoth\firmware_re\armgcc_path.txt").read().strip()
OBJCOPY=GCC.replace("gcc.exe","objcopy.exe"); NM=GCC.replace("gcc.exe","nm.exe")
HERE=os.path.dirname(os.path.abspath(__file__))

FLUSH_HOOK=0x31658; FLUSH_RES=0x31660
LED_HOOK=0x31b28;   LED_RES=0x31b2c
FSHIM=0x4d500; LSHIM=0x4d538; RENDER_AT=0x4d560
DATA_AT=0x50000; CKSUM=0x4dffc; APP_LO=0x1c000; CPACR=0xE000ED88

elf=os.path.join(HERE,"combo.elf"); ld=os.path.join(HERE,"combo_link.ld")
open(ld,"w").write(f"ENTRY(render)\nSECTIONS {{ . = 0x{RENDER_AT:x}; .text : {{ *(.text.render) *(.text.ledfill) *(.text*) *(.rodata*) }} /DISCARD/ : {{ *(.ARM.exidx*) *(.comment) *(.ARM.attributes) }} }}\n")
subprocess.run([GCC,"-mcpu=cortex-m4","-mthumb","-mfpu=fpv4-sp-d16","-mfloat-abi=softfp",
  "-Os","-ffreestanding","-fno-builtin","-fomit-frame-pointer","-nostdlib",
  "-T",ld,"-o",elf,os.path.join(HERE,"combo_nn.c")],check=True)
nm=subprocess.run([NM,elf],capture_output=True,text=True)
if [l for l in nm.stdout.splitlines() if " U " in l]:
    print("UNDEF:"); print(nm.stdout); raise SystemExit(1)
syms={l.split()[2]:int(l.split()[0],16) for l in nm.stdout.splitlines() if len(l.split())==3}
led_addr=syms["led_fill"]; print(f"render@0x{RENDER_AT:x} led_fill@0x{led_addr:x}")
subprocess.run([OBJCOPY,"-O","binary","-j",".text",elf,os.path.join(HERE,"combo_lo.bin")],check=True)
code=open(os.path.join(HERE,"combo_lo.bin"),"rb").read()
weights=open(os.path.join(HERE,"combo_weights.bin"),"rb").read()
print(f"code {len(code)}B  weights {len(weights)}B")

ks=Ks(KS_ARCH_ARM,KS_MODE_THUMB|KS_MODE_LITTLE_ENDIAN)
fshim,_=ks.asm(f"""
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
 movw r3,#{FLUSH_RES&0xffff}
 movt r3,#{(FLUSH_RES>>16)&0xffff}
 orr r3,r3,#1
 bx r3
""",FSHIM); fshim=bytes(fshim); assert FSHIM+len(fshim)<=LSHIM,len(fshim)
lshim,_=ks.asm(f"""
 push {{r0,r1,r2,r3,r12,lr}}
 bl #{led_addr}
 pop {{r0,r1,r2,r3,r12,lr}}
 push.w {{r2,r3,r4,r5,r6,r7,r8,r9,r10,lr}}
 b.w #{LED_RES}
""",LSHIM); lshim=bytes(lshim); assert LSHIM+len(lshim)<=RENDER_AT,len(lshim)

d=bytearray(open(STOCK,"rb").read())
assert set(d[FSHIM:RENDER_AT+len(code)])<= {0},"region not free"
d[FSHIM:FSHIM+len(fshim)]=fshim
d[LSHIM:LSHIM+len(lshim)]=lshim
d[RENDER_AT:RENDER_AT+len(code)]=code
d[DATA_AT:DATA_AT+len(weights)]=weights
# trampolines
d[FLUSH_HOOK:FLUSH_HOOK+8]=bytes([0x00,0x4b,0x18,0x47])+struct.pack("<I",FSHIM|1)  # ldr r3,[pc];bx r3;.word
lt,_=ks.asm(f"b.w #{LSHIM}",LED_HOOK); lt=bytes(lt); assert len(lt)==4
d[LED_HOOK:LED_HOOK+4]=lt
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4),x))&0xffffffff
ck=sum32(d[APP_LO:CKSUM]); d[CKSUM:CKSUM+4]=struct.pack("<I",ck)
open(OUT,"wb").write(d)
app_kb=math.ceil((DATA_AT+len(weights)-APP_LO)/1024)
print(f"checksum=0x{ck:08x} wrote {OUT}  APP_SIZE={app_kb}KB")
open(os.path.join(HERE,"combo_app_kb.txt"),"w").write(str(app_kb))
