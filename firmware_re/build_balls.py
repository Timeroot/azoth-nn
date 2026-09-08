#!/usr/bin/env python3
"""Detour the OLED flush FUN_00031658: draw our content into the buffer being DMA'd
(param_1 = r0), then resume the real flush. Rides the firmware's working display path.
TEST=3: static gray + white square (validate hook+geometry).
TEST=4: bouncing balls (time base = firmware frame counter @0x20003560)."""
import struct, sys
from keystone import Ks, KS_ARCH_ARM, KS_MODE_THUMB, KS_MODE_LITTLE_ENDIAN
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

STOCK = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
OUT   = r"C:\Users\Timeroot\azoth\fw_balls.bin"

HOOK_AT   = 0x31658          # flush entry
RESUME    = 0x31660          # after the 4 overwritten insns (push;movr4;movr5;movs r0,#0x10 lives at 60)
TCOUNT    = 0x20003560       # firmware frame counter (increments each render, wraps at 10000)
CODE_AT   = 0x4d500
CKSUM_AT  = 0x4dffc
APP_LO    = 0x1c000

CNT       = 0x2003f000       # free RAM (above stack top 0x2003a878, below RAM end 0x20040000)
DIRTY_TRIG= 0x200034ba       # "content-changed" flag; set each flush -> continuous refresh

TEST = int(sys.argv[1]) if len(sys.argv) > 1 else 3
ks = Ks(KS_ARCH_ARM, KS_MODE_THUMB | KS_MODE_LITTLE_ENDIAN)
def L(reg,val): return f"movw {reg}, #{val & 0xffff}\n movt {reg}, #{(val>>16)&0xffff}\n"
RES = f"movw r3, #{RESUME&0xffff}\n movt r3, #{(RESUME>>16)&0xffff}\n orr r3,r3,#1\n bx r3\n"

if TEST == 3:
    asm = f"""
        push {{r4, r5, r6, lr}}
        mov  r4, r0                // fb (buffer being flushed)
        mov  r5, r1                // len
        {L('r2',0x44444444)}
        movs r3, #0
        {L('r6',0x2000)}
    clr:
        str  r2, [r4, r3]
        adds r3, r3, #4
        cmp  r3, r6
        bne  clr
        movs r1, #20               // y
    srow:
        lsls r6, r1, #7
        add  r6, r6, r4
        adds r6, r6, #10           // xbyte = 20/2
        movs r2, #0xFF
        movs r3, #0
    scol:
        strb r2, [r6, r3]
        adds r3, r3, #1
        cmp  r3, #8
        bne  scol
        adds r1, r1, #1
        cmp  r1, #36
        bne  srow
        movs r0, #0x10             // resume: original had movs r0,#0x10 at 0x31660
        {RES}
    """

elif TEST == 4:
    # 3 bouncing balls, 10x10, from frame counter t (r8) via triangle wave (no udiv).
    # visible 208x64; ball 10px -> Mx=198, My=54.
    asm = f"""
        push {{r4, r5, r6, lr}}
        mov  r4, r0                // fb
        mov  r5, r1                // len
        push {{r7, r8}}
        // ---- private frame counter in free RAM (magic-init), masked to 16 bits ----
        {L('r3',CNT)}
        ldr  r0, [r3, #4]
        {L('r1',0xBA11B011)}
        cmp  r0, r1
        beq  have_cnt
        movs r0, #0
        str  r0, [r3]
        str  r1, [r3, #4]
    have_cnt:
        ldr  r0, [r3]
        adds r0, r0, #1
        uxth r0, r0                // mask 0xffff so triangle loop stays bounded
        str  r0, [r3]
        mov  r8, r0                // t
        // ---- sustain continuous flush: set content-changed flag ----
        {L('r3',DIRTY_TRIG)}
        movs r0, #1
        strb r0, [r3]
        // ---- clear fb to black ----
        movs r2, #0
        movs r3, #0
        {L('r6',0x2000)}
    clr:
        str  r2, [r4, r3]
        adds r3, r3, #4
        cmp  r3, r6
        bne  clr
        // ball 0: sx=2 sy=1 color=0xFF
        lsl.w r0, r8, #1
        movs r1, #246
        bl   tri
        mov  r6, r0
        mov  r0, r8
        movs r1, #54
        bl   tri
        mov  r1, r0
        mov  r0, r6
        movs r2, #0xFF
        bl   ball
        // ball 1: sx=1 sy=3 ox=60 oy=20 color=0xAA
        mov  r0, r8
        adds r0, r0, #60
        movs r1, #246
        bl   tri
        mov  r6, r0
        lsl.w r0, r8, #1
        add.w r0, r0, r8           // t*3
        adds r0, r0, #20
        movs r1, #54
        bl   tri
        mov  r1, r0
        mov  r0, r6
        movs r2, #0xAA
        bl   ball
        // ball 2: sx=3 sy=2 ox=120 oy=40 color=0x66
        lsl.w r0, r8, #1
        add.w r0, r0, r8           // t*3
        adds r0, r0, #120
        movs r1, #246
        bl   tri
        mov  r6, r0
        lsl.w r0, r8, #1           // t*2
        adds r0, r0, #40
        movs r1, #54
        bl   tri
        mov  r1, r0
        mov  r0, r6
        movs r2, #0x66
        bl   ball
        pop  {{r7, r8}}
        movs r0, #0x10
        {RES}

    // tri(r0=p, r1=M) -> r0 in [0,M]; clobbers r2
    tri:
        lsls r2, r1, #1            // 2M
    tmod:
        cmp  r0, r2
        blo  tdone
        subs r0, r0, r2
        b    tmod
    tdone:
        cmp  r0, r1
        bls  tok
        subs r0, r2, r0
    tok:
        bx   lr

    // ball(r0=px, r1=py, r2=color); fb=r4; clobbers r0,r3,r6,r7
    ball:
        bic  r0, r0, #1
        lsrs r0, r0, #1            // xbyte
        movs r3, #0                // row
    brow:
        add  r6, r1, r3
        lsls r6, r6, #7
        add  r6, r6, r4
        add  r6, r6, r0
        movs r7, #0                // col
    bcol:
        strb r2, [r6, r7]
        adds r7, r7, #1
        cmp  r7, #5
        bne  bcol
        adds r3, r3, #1
        cmp  r3, #10
        bne  brow
        bx   lr
    """

code, cnt = ks.asm(asm, CODE_AT)
code = bytes(code)
print(f"TEST {TEST}: {len(code)} bytes, {cnt} insns")
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
for i in md.disasm(code, CODE_AT):
    print("  %06x: %-11s %s %s" % (i.address, " ".join("%02x"%b for b in i.bytes), i.mnemonic, i.op_str))

d = bytearray(open(STOCK, "rb").read())
assert CODE_AT + len(code) < CKSUM_AT
assert set(d[CODE_AT:CODE_AT+len(code)]) <= {0}, "code region not free!"
d[CODE_AT:CODE_AT+len(code)] = code
tramp = bytes([0x00,0x4b, 0x18,0x47]) + struct.pack("<I", CODE_AT | 1)
d[HOOK_AT:HOOK_AT+len(tramp)] = tramp
print("trampoline @0x%x:" % HOOK_AT, tramp.hex())
def sum32(x): return sum(struct.unpack("<%dI"%(len(x)//4), x)) & 0xffffffff
newck = sum32(d[APP_LO:CKSUM_AT])
d[CKSUM_AT:CKSUM_AT+4] = struct.pack("<I", newck)
print("checksum = 0x%08x" % newck)
open(OUT, "wb").write(d)
print("wrote", OUT)
