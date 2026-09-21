#!/usr/bin/env python3
"""Phase-1 flash-writer TEST firmware. DFU-flashable (all < 0x61000).
Two detours: OLED flush @0x31658 -> render (hex readout of high flash), and the
HID command dispatch FUN_0003a0f0 @0x3a0f0 -> hid_cmd ('WF' upload commands)."""
import struct, subprocess, os, math
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN

STOCK=r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT=r"C:\Users\Timeroot\azoth\fw_phase1.bin"
GCC=open(r"C:\Users\Timeroot\azoth\firmware_re\armgcc_path.txt").read().strip()
OBJCOPY=GCC.replace("gcc.exe","objcopy.exe"); NM=GCC.replace("gcc.exe","nm.exe")
HERE=os.path.dirname(os.path.abspath(__file__))

FLUSH_HOOK=0x31658; FLUSH_RES=0x31660
HID_HOOK=0x3a0f0;   HID_RES=0x3a0f4          # after the 4 replaced bytes (push;mov r4,r0)
FSHIM=0x4d500; HIDSHIM=0x4d540
RENDER_AT=0x50000                            # no weights in phase1; plenty of room
CKSUM=0x4dffc; APP_LO=0x1c000

elf=os.path.join(HERE,"phase1.elf"); ld=os.path.join(HERE,"phase1.ld")
open(ld,"w").write(f"ENTRY(render)\nSECTIONS {{ . = 0x{RENDER_AT:x}; .text : {{ *(.text.render) *(.text.hidcmd) *(.text*) *(.rodata*) }} /DISCARD/ : {{ *(.ARM.exidx*) *(.comment) *(.ARM.attributes) }} }}\n")
subprocess.run([GCC,"-mcpu=cortex-m4","-mthumb","-mfpu=fpv4-sp-d16","-mfloat-abi=softfp",
  "-Os","-ffreestanding","-fno-builtin","-fomit-frame-pointer","-nostdlib",
  "-T",ld,"-o",elf,os.path.join(HERE,"phase1_flash.c")],check=True)
nm=subprocess.run([NM,elf],capture_output=True,text=True)
if [l for l in nm.stdout.splitlines() if " U " in l]:
    print("UNDEF:"); print(nm.stdout); raise SystemExit(1)
syms={l.split()[2]:int(l.split()[0],16) for l in nm.stdout.splitlines() if len(l.split())==3}
hid_addr=syms["hid_cmd"]; print(f"render@0x{RENDER_AT:x} hid_cmd@0x{hid_addr:x}")
subprocess.run([OBJCOPY,"-O","binary","-j",".text",elf,os.path.join(HERE,"phase1_lo.bin")],check=True)
code=open(os.path.join(HERE,"phase1_lo.bin"),"rb").read()
print(f"code {len(code)}B")

ks=Ks(KS_ARCH_ARM,KS_MODE_THUMB|KS_MODE_LITTLE_ENDIAN)
def asmb(src,addr): b,_=ks.asm(src,addr); return bytes(b)
# flush shim: call render(fb,len), resume at 0x31660 with r0=0x10 (mimics original)
fshim=asmb(f"""
 push {{r4,r5,lr}}
 mov r4,r0
 mov r5,r1
 mov r0,r4
 mov r1,r5
 bl #{RENDER_AT}
 movs r0,#0x10
 movw r3,#{FLUSH_RES&0xffff}
 movt r3,#{(FLUSH_RES>>16)&0xffff}
 orr r3,r3,#1
 bx r3
""",FSHIM); assert FSHIM+len(fshim)<=HIDSHIM,len(fshim)
# hid shim: hid_cmd(p1,p2); if handled -> return to caller, else replicate prologue+resume
h_head=asmb(f"push {{r0,r1,lr}}\n bl #{hid_addr}", HIDSHIM)
cbnz_at=HIDSHIM+len(h_head)
h_body=asmb(f"pop {{r0,r1,lr}}\n push {{r3,r4,r5,r6,r7,lr}}\n mov r4,r0\n b.w #{HID_RES}", cbnz_at+2)
swallow_at=cbnz_at+2+len(h_body)
h_cbnz=asmb(f"cbnz r0, #{swallow_at}", cbnz_at)
h_tail=asmb("pop {r0,r1,lr}\n bx lr", swallow_at)
hidshim=h_head+h_cbnz+h_body+h_tail; assert HIDSHIM+len(hidshim)<=RENDER_AT,len(hidshim)

d=bytearray(open(STOCK,"rb").read())
assert set(d[FSHIM:HIDSHIM+len(hidshim)])<= {0},"shim region not free"
assert RENDER_AT+len(code) < 0x61000,"code past DFU ceiling"
d[FSHIM:FSHIM+len(fshim)]=fshim
d[HIDSHIM:HIDSHIM+len(hidshim)]=hidshim
d[RENDER_AT:RENDER_AT+len(code)]=code
# trampolines
d[FLUSH_HOOK:FLUSH_HOOK+8]=bytes([0x00,0x4b,0x18,0x47])+struct.pack("<I",FSHIM|1)
assert d[HID_HOOK:HID_HOOK+4]==bytes([0xf8,0xb5,0x04,0x46]),"FUN_0003a0f0 prologue moved"
d[HID_HOOK:HID_HOOK+4]=asmb(f"b.w #{HIDSHIM}",HID_HOOK)
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4),x))&0xffffffff
ck=sum32(d[APP_LO:CKSUM]); d[CKSUM:CKSUM+4]=struct.pack("<I",ck)
open(OUT,"wb").write(d)
app_kb=math.ceil((RENDER_AT+len(code)-APP_LO)/1024)
print(f"checksum=0x{ck:08x} wrote {OUT}  APP_SIZE={app_kb}KB")
open(os.path.join(HERE,"phase1_app_kb.txt"),"w").write(str(app_kb))
