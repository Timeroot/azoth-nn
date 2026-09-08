#!/usr/bin/env python3
"""LED-control validation: detour FUN_00031b28 (LED buffer->I2C driver). On the
color-load subop (param_1==0), overwrite the 60x3 RGB buffer (r2) with a per-index
rainbow, then run the original (gamma+scatter+I2C @0x30). Reveals the physical
LED-index layout and proves arbitrary backlight control. Based on STOCK firmware."""
import struct
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

STOCK = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT   = r"C:\Users\Timeroot\azoth\fw_balls.bin"
HOOK  = 0x31b28            # FUN_00031b28 entry (push.w is first 4 bytes)
RESUME= 0x31b2c            # after the push.w
CODE  = 0x4d500
CKSUM = 0x4dffc
APP_LO= 0x1c000

ks=Ks(KS_ARCH_ARM,KS_MODE_THUMB|KS_MODE_LITTLE_ENDIAN)
# my_led: entry r0=subop, r1=half, r2=rgbbuf, lr=return. Preserve r0-r5,lr around fill.
asm=f"""
    push {{r0,r1,r2,r3,r4,r5,lr}}
    cmp  r0, #0
    bne  skip
    movs r4, #60
    muls r4, r4, r1            // base = half*60
    movs r3, #0                // i
loop:
    add  r5, r4, r3            // idx = base+i
    lsls r0, r3, #1
    add  r0, r0, r3
    add  r0, r0, r2            // &buf[i*3]
    movs r1, #11
    muls r1, r1, r5
    strb r1, [r0, #0]          // R
    movs r1, #7
    muls r1, r1, r5
    adds r1, r1, #83
    strb r1, [r0, #1]          // G
    movs r1, #13
    muls r1, r1, r5
    adds r1, r1, #150
    strb r1, [r0, #2]          // B
    adds r3, r3, #1
    cmp  r3, #60
    bne  loop
skip:
    pop  {{r0,r1,r2,r3,r4,r5,lr}}
    push.w {{r2,r3,r4,r5,r6,r7,r8,r9,r10,lr}}
    b.w  #{RESUME}
"""
code,_=ks.asm(asm,CODE); code=bytes(code)
md=Cs(CS_ARCH_ARM,CS_MODE_THUMB)
print(f"my_led: {len(code)} bytes @0x{CODE:x}")
# verify the replicated push.w matches the original 2d e9 fc 47
for i in md.disasm(code,CODE):
    if i.mnemonic.startswith("push") and i.address>CODE+8:
        print("  replicated:", " ".join("%02x"%b for b in i.bytes), i.mnemonic, i.op_str)

d=bytearray(open(STOCK,"rb").read())
assert set(d[CODE:CODE+len(code)])<= {0}, "code region not free"
d[CODE:CODE+len(code)]=code
# trampoline: replace the 4-byte push.w at HOOK with b.w my_led
tramp,_=ks.asm(f"b.w #{CODE}",HOOK); tramp=bytes(tramp)
assert len(tramp)==4, f"tramp {len(tramp)}"
print("trampoline @0x%x:"%HOOK, tramp.hex())
d[HOOK:HOOK+4]=tramp
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4),x))&0xffffffff
newck=sum32(d[APP_LO:CKSUM]); d[CKSUM:CKSUM+4]=struct.pack("<I",newck)
open(OUT,"wb").write(d)
print("checksum=0x%08x wrote %s"%(newck,OUT))
