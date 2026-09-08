import struct, subprocess, os, math
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN
STOCK=r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT=r"C:\Users\Timeroot\azoth\fw_balls.bin"
GCC=open(r"C:\Users\Timeroot\azoth\firmware_re\armgcc_path.txt").read().strip()
OBJCOPY=GCC.replace("gcc.exe","objcopy.exe"); HERE=os.path.dirname(os.path.abspath(__file__))
HOOK=0x31658; RES=0x31660; CODE=0x4d500; RENDER=0x4d520; CK=0x4dffc; APP_LO=0x1c000
FILL_LO=0x4e000; FILL_HI=0xc0000
elf=os.path.join(HERE,"scan.elf"); ld=os.path.join(HERE,"scan.ld")
open(ld,"w").write(f"ENTRY(render)\nSECTIONS {{ . = 0x{RENDER:x}; .text : {{ *(.text.render) *(.text*) *(.rodata*) }} /DISCARD/ : {{ *(.ARM.exidx*) *(.comment) *(.ARM.attributes) }} }}\n")
subprocess.run([GCC,"-mcpu=cortex-m4","-mthumb","-Os","-ffreestanding","-fno-builtin","-fomit-frame-pointer","-nostdlib","-T",ld,"-o",elf,os.path.join(HERE,"scan.c")],check=True)
subprocess.run([OBJCOPY,"-O","binary","-j",".text",elf,os.path.join(HERE,"scan_lo.bin")],check=True)
code=open(os.path.join(HERE,"scan_lo.bin"),"rb").read()
ks=Ks(KS_ARCH_ARM,KS_MODE_THUMB|KS_MODE_LITTLE_ENDIAN)
shim,_=ks.asm(f"push {{r4,r5,r6,lr}}\n mov r4,r0\n mov r5,r1\n bl #{RENDER}\n movs r0,#0x10\n movw r3,#{RES&0xffff}\n movt r3,#{(RES>>16)&0xffff}\n orr r3,r3,#1\n bx r3\n",CODE); shim=bytes(shim)
d=bytearray(open(STOCK,"rb").read())
d[CODE:CODE+len(shim)]=shim; d[RENDER:RENDER+len(code)]=code
for i in range(FILL_LO,FILL_HI): d[i]=0x5A
d[HOOK:HOOK+8]=bytes([0x00,0x4b,0x18,0x47])+struct.pack("<I",CODE|1)
def s32(x): return sum(struct.unpack("<%dI"%(len(x)//4),x))&0xffffffff
ck=s32(d[APP_LO:CK]); d[CK:CK+4]=struct.pack("<I",ck)
open(OUT,"wb").write(d)
app_kb=math.ceil((FILL_HI-APP_LO)/1024)
print(f"code {len(code)}B shim {len(shim)}B, filled 0x5A [{FILL_LO:x},{FILL_HI:x}), ck=0x{ck:08x}, APP_SIZE={app_kb}")
