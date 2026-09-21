#!/usr/bin/env python3
"""Upload weights to the Azoth's high flash (0x61000+) via the custom 'WF' HID
command (see phase1_flash.c / the combo self-programmer).

Report (65B): [0x02 report-id][ 'W' 'F' sub ... ]  -> device sees payload d[0]='W'.
  sub 0x01 ERASE page:  d[3]=page_index
  sub 0x02 WRITE block:  d[3..6]=byte offset LE, d[7]=len(<=52,*4), d[8..]=payload
  sub 0x03 RESET counters

Usage:
  python wflash.py test                 # Phase-1: reset, erase page 0, write a pattern
  python wflash.py upload <file.bin>    # erase needed pages + stream file to 0x61000
"""
import sys, time, hid, struct

VID, PID = 0x0B05, 0x1A83
RLEN = 65
CHUNK = 52                      # payload bytes per write report (mult of 4)

def open_dev():
    path=None
    for d in hid.enumerate(VID, PID):
        if (d.get("usage_page") or 0)==0xFF00 and (d.get("usage") or 0)==0x0001:
            path=d["path"]; break
    if not path: sys.exit("WF HID interface (FF00/usage1, PID 1A83) not found")
    dev=hid.device(); dev.open_path(path); return dev

def cmd(dev, sub, body=b""):
    rep = bytes([0x02, ord('W'), ord('F'), sub]) + body
    rep = rep + bytes(RLEN-len(rep))
    if dev.write(rep) < 0: raise IOError(dev.error())

def erase_page(dev, idx):        cmd(dev, 0x01, bytes([idx]))
def reset(dev):                  cmd(dev, 0x03)
def write_block(dev, off, data): # data <= CHUNK bytes, len mult of 4
    assert off%4==0 and len(data)%4==0 and len(data)<=CHUNK
    cmd(dev, 0x02, struct.pack("<I", off)+bytes([len(data)])+data)

def sum32(b):
    if len(b)%4: b=b+bytes(4-len(b)%4)
    return sum(struct.unpack("<%dI"%(len(b)//4), b)) & 0xffffffff

def do_test(dev):
    reset(dev); time.sleep(0.05)
    erase_page(dev, 0); time.sleep(0.15)
    pat = bytes((i*7+3)&0xff for i in range(52))
    write_block(dev, 0, pat)
    print("wrote 52-byte pattern at 0x61000")
    print("first 8 bytes should read:", ' '.join(f'{b:02x}' for b in pat[:8]))
    print("SUMV (running sum32 of written words) should be:", f"0x{sum32(pat):08x}")
    print("-> check the OLED: E=0001 W=0001, row1 sum, row2 first bytes")

def do_upload(dev, path):
    blob=open(path,"rb").read()
    n=len(blob); npages=(n+0xfff)//0x1000
    print(f"uploading {n} bytes ({n/1024:.1f}KB) to 0x61000, {npages} pages")
    reset(dev); time.sleep(0.05)
    for p in range(npages):
        erase_page(dev, p); time.sleep(0.09)
        if p%16==0: print(f"  erased page {p}/{npages}")
    print("erase done; writing blocks...")
    off=0; t0=time.time()
    while off < n:
        chunk=blob[off:off+CHUNK]
        if len(chunk)%4: chunk=chunk+bytes(4-len(chunk)%4)
        write_block(dev, off, chunk)
        off+=CHUNK
        if (off//CHUNK)%1000==0: print(f"  {off}/{n} ({off*100//n}%)")
    dt=time.time()-t0
    print(f"done: {n} bytes in {dt:.1f}s.  expected SUMV(padded4) = 0x{sum32(blob):08x}")
    print("-> compare row1 (SUMV) on the OLED, and the first bytes on row2")

if __name__=="__main__":
    if len(sys.argv)<2: sys.exit(__doc__)
    dev=open_dev()
    if sys.argv[1]=="test": do_test(dev)
    elif sys.argv[1]=="upload": do_upload(dev, sys.argv[2])
    else: sys.exit("unknown mode")
    dev.close()
