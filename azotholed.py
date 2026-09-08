"""Drive the ROG Azoth OLED directly over USB HID (no Armoury Crate).

The keyboard exposes a vendor-defined HID interface (usage page 0xFF00,
usage 0x0001).  On this WIRED unit (PID 0x1A83) that is interface MI_01;
on the 2.4G dongle (PID 0x1ACE) it is MI_02 - we pick it by usage page,
not by interface number, so both work.

DISPLAY (determined empirically on this wired unit):
  * 208 x 64 pixels, 4-bit greyscale (16 levels).
  * Packed 2 pixels per byte, big-endian nibbles: byte = (left<<4)|right,
    so 104 bytes/row * 64 rows = 6656 bytes.  (The reference protocol doc's
    "104x64 8-bit" was 104 *bytes* per row misread as pixels.)
  * Row-major, origin top-left, no flip.

HID protocol (report id 0x02; 64 data bytes each; ~10 ms apart):
  picture mode : 02 12 03   then   02 12 01
  start        : 02 61 01 00 00 71
  data (x113)  : 02 61 02 <idx> 00 <payload>     idx = 0x70 .. 0x00
                 payload stream = [01 00 E8 03] + 6656 packed bytes, cut into
                 59-byte chunks (first chunk = 4 meta + 55 data)
  end          : 02 61 03
  commit       : 02 50 55

Windows: hid_write() takes byte[0] as the report id, and OutputReportByteLength
is 65, so we send [0x02, <64 bytes>].

Usage:
  python azotholed.py test                 # geometry / greyscale test frame
  python azotholed.py image <path>         # show an image (any format)
  python azotholed.py text "hi" ["line2"]  # render a few lines of text
  python azotholed.py clock                # one-shot current time
  python azotholed.py off                  # blank the screen
"""
import sys, time
import hid
from PIL import Image, ImageDraw, ImageFont

VID, PID_WIRED, PID_DONGLE = 0x0B05, 0x1A83, 0x1ACE
NBYTES = 6656                                # framebuffer size (fixed by protocol)
NPIX4 = NBYTES * 2                           # 13312 four-bit pixels

# Geometry, determined empirically on this wired unit.  The visible panel is
# ~204 px wide x 64 tall, 4-bit grey, packed as a LINEAR nibble stream.  The
# effective width is fractional (~204.5), so rows are laid at a fractional pixel
# stride to keep verticals straight; XOFF nudges the whole frame horizontally.
OLED_W, OLED_H = 208, 64                     # visible pixels we draw into
STRIDE = 208.0                               # constant pixel stride per row
XOFF = 0                                     # horizontal shift (pixels)
SHEAR = 0.0                                  # px/row: smooth affine skew comp.
NIB_SWAP = True                              # low nibble = left (even) pixel

META = bytes([0x01, 0x00, 0xE8, 0x03])
REPORT_LEN = 65                             # Windows: report-id + 64 data
GAP = 0.010
UPLOAD_GAP = 0.016                          # per-packet pace for animation upload
                                            # (Armoury Crate's PCAP median ~15.6ms)


# ----------------------------------------------------------------- device
def open_oled():
    path = None
    for pid in (PID_WIRED, PID_DONGLE):
        for d in hid.enumerate(VID, pid):
            if (d.get("usage_page") or 0) == 0xFF00 and (d.get("usage") or 0) == 0x0001:
                path = d["path"]; break
        if path:
            break
    if not path:
        sys.exit("OLED HID interface (usage_page 0xFF00) not found - keyboard "
                 "plugged in / awake?")
    dev = hid.device()
    dev.open_path(path)
    return dev


def send(dev, data):
    """One report; data[0] (0x02) is the HID report id."""
    if data[0] != 0x02:
        raise ValueError("OLED reports must start with report id 0x02")
    if len(data) > REPORT_LEN:
        raise ValueError(f"report too long: {len(data)}")
    n = dev.write(bytes(data) + bytes(REPORT_LEN - len(data)))
    if n < 0:
        raise IOError(f"hid write failed: {dev.error()}")
    time.sleep(GAP)
    return n


# ----------------------------------------------------------------- packing
def pack4_frac(im, sf=STRIDE, wv=OLED_W, hv=OLED_H, xoff=XOFF, shear=SHEAR):
    """Pack a wv x hv image into the 6656-byte framebuffer as a LINEAR 4-bit
    nibble stream (2 px/byte, high nibble first) at a CONSTANT pixel stride sf.

    The panel's effective width is slightly non-integer, so instead of varying
    the stride (which leaves vertical seams) we pre-skew the source by `shear`
    px/row with a smooth bilinear affine, cancelling the residual lean without
    seams."""
    im = im.convert("L")
    if im.size != (wv, hv):
        im = im.resize((wv, hv), Image.LANCZOS)
    if shear:
        im = im.transform((wv, hv), Image.AFFINE, (1, shear, 0, 0, 1, 0),
                          resample=Image.BILINEAR)
    px = im.load()
    buf = bytearray(NBYTES)
    for y in range(hv):
        # snap each row start to an EVEN nibble so a source column always lands
        # on the same (high/low) nibble - otherwise parity flips row-to-row and
        # scrambles fine detail into "static".  Even steps (204/206) still track
        # the fractional stride and keep verticals straight.
        base = int(round(y * sf / 2.0)) * 2 + (xoff & ~1)
        for x in range(wv):
            p = base + x
            if 0 <= p < NPIX4:
                nib = px[x, y] >> 4
                hi = (p & 1) if NIB_SWAP else not (p & 1)
                if hi:
                    buf[p >> 1] |= nib << 4
                else:
                    buf[p >> 1] |= nib
    return bytes(buf)


def cal_pattern(wv, hv):
    im = Image.new("L", (wv, hv), 0)
    d = ImageDraw.Draw(im)
    d.rectangle([0, 0, wv - 1, hv - 1], outline=255)
    d.rectangle([3, 3, 22, 22], fill=255)
    d.text((wv // 2 - 12, 2), "F", fill=255, font=_font(min(52, hv - 6)))
    d.line([0, hv // 2, wv - 1, hv // 2], fill=255)      # centre H line
    d.line([wv // 2, 0, wv // 2, hv - 1], fill=255)      # centre V line
    return im


PAYLOAD = 60          # pixel bytes per data packet (Windows wire report is 65:
                      # report-id 0x02 + 64 data; header 02 61 02 idx 00 = 5)


def set_picture_mode(dev):
    send(dev, bytes([0x02, 0x12, 0x03]))
    send(dev, bytes([0x02, 0x12, 0x01]))


def upload(dev, packed, start=True, end=True, commit=True):
    """Upload one framebuffer via the 0x61 picture channel (no mode switch).
    The start/end/commit steps are optional so we can test in-place updates."""
    if len(packed) != NBYTES:
        raise ValueError(f"need {NBYTES} bytes, got {len(packed)}")
    if start:
        send(dev, bytes([0x02, 0x61, 0x01, 0x00, 0x00, 0x71]))
    stream = META + packed
    idx = 0x70
    for off in range(0, len(stream), PAYLOAD):
        send(dev, bytes([0x02, 0x61, 0x02, idx, 0x00]) + stream[off:off + PAYLOAD])
        idx -= 1
    while idx >= 0:
        send(dev, bytes([0x02, 0x61, 0x02, idx, 0x00]))
        idx -= 1
    if end:
        send(dev, bytes([0x02, 0x61, 0x03]))
    if commit:
        send(dev, bytes([0x02, 0x50, 0x55]))


def show(dev, packed):
    set_picture_mode(dev)
    upload(dev, packed)


def upload_frames(dev, frames, durations=None):
    """Upload N framebuffers as ONE looping animation (exactly how Armoury Crate
    stores a GIF - the firmware keeps every frame and loops them, no per-frame
    blank).  frames = list of 6656-byte packed framebuffers; durations = ms each.

    Stream = header `<N> 00 <dur_LE16>*N` + concatenated framebuffers.  Sent as:
      start   `61 01 00 00 <totalpkts_LE16>`
      data    `61 02 <idx_LE16> <60 payload bytes>`   idx = total-1 .. 0
      end     `61 03`
      commit  `50 55`
    (The single-frame still image is just the N=1 case: header `01 00 E8 03`.)"""
    n = len(frames)
    if durations is None:
        durations = [200] * n
    header = bytes([n, 0x00])
    for d in durations:
        header += bytes([d & 0xFF, (d >> 8) & 0xFF])
    stream = header + b"".join(frames)
    total = (len(stream) + PAYLOAD - 1) // PAYLOAD

    # Armoury Crate's CHalFunction_M701::SetOled_CustomAnimation_Data does a real
    # request/response handshake: the firmware ECHOES `61 02 <idx_LE16>` + status
    # for each packet.  We must wait for the echo of THIS index before the next
    # packet, and retry if it doesn't come; only commit if every packet acked, so
    # a failed upload never saves a corrupt GIF (which is what crash-loops it).
    def wr(data, want=None, tries=1):
        """Write; if `want`=(lo,hi) wait for an ack echoing 61 02 lo hi. Return ok."""
        for _ in range(tries):
            dev.write(bytes(data) + bytes(REPORT_LEN - len(data)))
            if want is None:
                try: dev.read(65, 50)
                except Exception: pass
                time.sleep(UPLOAD_GAP)
                return True
            deadline = time.perf_counter() + 0.20
            while time.perf_counter() < deadline:
                try: r = bytes(dev.read(65, 40))
                except Exception: r = b""
                if not r:
                    continue
                for s in (0, 1):                       # tolerate optional report-id byte
                    if (len(r) >= s + 4 and r[s] == 0x61 and r[s + 1] == 0x02
                            and r[s + 2] == want[0] and r[s + 3] == want[1]):
                        time.sleep(UPLOAD_GAP)         # AC's post-ack settle
                        return True
        return False

    wr(bytes([0x02, 0x12, 0x03]))
    wr(bytes([0x02, 0x12, 0x01]))
    wr(bytes([0x02, 0x61, 0x01, 0x00, 0x00, total & 0xFF, (total >> 8) & 0xFF]))
    for i in range(total):
        idx = total - 1 - i
        lo, hi = idx & 0xFF, (idx >> 8) & 0xFF
        ok = wr(bytes([0x02, 0x61, 0x02, lo, hi]) + stream[i * PAYLOAD:(i + 1) * PAYLOAD],
                want=(lo, hi), tries=6)
        if not ok:
            raise RuntimeError(f"no ACK for packet idx {idx} (i={i}); aborting "
                               f"WITHOUT commit so nothing corrupt is saved")
    wr(bytes([0x02, 0x61, 0x03]))
    wr(bytes([0x02, 0x50, 0x55]))


def _send_wait(dev, data, want=None, tries=6, settle=0.008):
    """Write a report; if `want` given, wait for an IN report starting with those
    bytes (the firmware's echo-ACK), retrying.  Returns True on ack/ok."""
    for _ in range(tries):
        dev.write(bytes(data) + bytes(REPORT_LEN - len(data)))
        if want is None:
            try: dev.read(65, 40)
            except Exception: pass
            time.sleep(settle)
            return True
        deadline = time.perf_counter() + 0.2
        while time.perf_counter() < deadline:
            try: r = bytes(dev.read(65, 40))
            except Exception: r = b""
            if not r:
                continue
            for s in (0, 1):                       # tolerate optional report-id byte
                if len(r) >= s + len(want) and all(r[s + k] == want[k] for k in range(len(want))):
                    time.sleep(settle)
                    return True
    return False


def _pack4_width(im, width, height=32, cap=7):
    """Pack a width x height image to 4-bit (low nibble=left), nibbles capped at
    `cap` so every byte stays < 0x80 (dodges the music channel's UTF-8 mangling)."""
    im = im.convert("L").resize((width, height), Image.LANCZOS)
    px = im.load()
    out = bytearray()
    for y in range(height):
        for x in range(0, width, 2):
            lo = min(cap, px[x, y] >> 4)
            hi = min(cap, px[x + 1, y] >> 4) if x + 1 < width else 0
            out.append((hi << 4) | lo)
    return bytes(out)


# The command sequence Armoury Crate sends to enter music mode (from a capture of
# selecting it in the UI): a 0x22 transaction wrapper around 12 12 / 7d 20 02.
MUSIC_ENTER = ([0x12, 0x14, 0x02],                                # OLED init/enable
               [0x12, 0x03], [0x12, 0x00], [0x12, 0x01], [0x22, 0x01],
               [0x12, 0x12], [0x7d, 0x20, 0x02], [0x22, 0x02])


def music_songname(interval=5.0, count=0):
    """Enter music mode and push a new full-screen 'song name' bitmap every
    `interval` s (no visualizer), to see if the name updates in place (no blank).
    Music-info-only header: 67 00 00 00 00 00 <npk_LE16> <w_LE16> 40 (height 64);
    sub=01 data 67 01 <idx_LE16> ... idx down, ACK-echo handshake."""
    dev = open_oled()
    try:
        for c in MUSIC_ENTER:
            _send_wait(dev, bytes([0x02]) + bytes(c))
            time.sleep(0.03)
        n = 0
        while count <= 0 or n < count:
            n += 1
            msg = f"CLAUDE #{n:02d}  {time.strftime('%H:%M:%S')}"
            f = _font(40)
            probe = ImageDraw.Draw(Image.new("L", (4, 4)))
            w = int(probe.textlength(msg, font=f)) + 16
            w = max(208, w); w -= w % 2
            im = Image.new("L", (w, 64), 0)
            ImageDraw.Draw(im).text((8, 10), msg, fill=255, font=f)
            pix = _pack4_width(im, w, 64)
            npk = (len(pix) + 59) // 60
            hdr = bytes([0x02, 0x67, 0x00, 0x00, 0x00, 0x00, npk & 0xFF, (npk >> 8) & 0xFF,
                         w & 0xFF, (w >> 8) & 0xFF, 0x40])
            hok = _send_wait(dev, hdr, want=(0x67, 0x00))
            ok = hok
            for i in range(npk):
                idx = npk - 1 - i
                chunk = pix[i * 60:(i + 1) * 60]
                if not _send_wait(dev, bytes([0x02, 0x67, 0x01, idx & 0xFF, (idx >> 8) & 0xFF]) + chunk,
                                  want=(0x67, 0x01, idx & 0xFF, (idx >> 8) & 0xFF)):
                    ok = False; break
            print(f"  update {n}: '{msg}'  w={w} {npk}pkts hdr_ok={hok} all_ok={ok}", flush=True)
            time.sleep(interval)
    except KeyboardInterrupt:
        print("stopped", flush=True)
    finally:
        dev.close()


def balls_gif_frames(nframes=16, nballs=4, seed=None):
    """Render N frames of bouncing balls -> list of packed framebuffers."""
    import random
    rng = random.Random(seed)
    x0, y0, x1, y1 = 1, 1, OLED_W - 2, OLED_H - 2
    balls = [[rng.uniform(x0 + 10, x1 - 10), rng.uniform(y0 + 10, y1 - 10),
              rng.choice([-1, 1]) * rng.uniform(2.5, 4.5),
              rng.choice([-1, 1]) * rng.uniform(2.0, 3.5),
              rng.randint(4, 8), rng.choice([110, 150, 200, 255])] for _ in range(nballs)]
    frames = []
    for _ in range(nframes):
        im = Image.new("L", (OLED_W, OLED_H), 0)
        d = ImageDraw.Draw(im)
        d.rectangle([0, 0, OLED_W - 1, OLED_H - 1], outline=255)
        for b in balls:
            b[0] += b[2]; b[1] += b[3]
            if b[0] - b[4] <= x0: b[0] = x0 + b[4]; b[2] = abs(b[2])
            if b[0] + b[4] >= x1: b[0] = x1 - b[4]; b[2] = -abs(b[2])
            if b[1] - b[4] <= y0: b[1] = y0 + b[4]; b[3] = abs(b[3])
            if b[1] + b[4] >= y1: b[1] = y1 - b[4]; b[3] = -abs(b[3])
            d.ellipse([b[0] - b[4], b[1] - b[4], b[0] + b[4], b[1] + b[4]],
                      fill=b[5], outline=255)
        frames.append(pack_fast(im))
    return frames


def load_gif_frames(path):
    """Animated image file -> (list of packed framebuffers, list of durations ms)."""
    im = Image.open(path)
    frames, durs = [], []
    try:
        i = 0
        while True:
            im.seek(i)
            frames.append(pack_fast(img_to_frame(im.convert("RGB"))))
            durs.append(int(im.info.get("duration", 200)) or 200)
            i += 1
    except EOFError:
        pass
    return frames, durs


def pack_fast(im):
    """Vectorised packer for the final geometry (stride 208, no shear/xoff,
    low-nibble = left pixel).  ~100x faster than pack4_frac for streaming."""
    import numpy as np
    if im.size != (OLED_W, OLED_H):
        im = im.resize((OLED_W, OLED_H), Image.LANCZOS)
    a = (np.asarray(im.convert("L"), dtype=np.uint8) >> 4)      # (64,208) nibbles
    left, right = a[:, 0::2], a[:, 1::2]                         # even/odd columns
    packed = (right.astype(np.uint8) << 4) | left               # low nibble = left
    return packed.tobytes()


# ----------------------------------------------------------------- images
def img_to_frame(im):
    """Fit any image into 208x64, letterboxed on black."""
    im = im.convert("L")
    canvas = Image.new("L", (OLED_W, OLED_H), 0)
    im.thumbnail((OLED_W, OLED_H), Image.LANCZOS)
    canvas.paste(im, ((OLED_W - im.width) // 2, (OLED_H - im.height) // 2))
    return canvas


def _font(size):
    for name in ("segoeui.ttf", "arialbd.ttf", "arial.ttf", "consola.ttf"):
        try:
            return ImageFont.truetype(name, size)
        except Exception:
            pass
    return ImageFont.load_default()


def text_frame(lines):
    im = Image.new("L", (OLED_W, OLED_H), 0)
    d = ImageDraw.Draw(im)
    n = max(1, len(lines))
    size = max(12, min(56, (OLED_H - 2) // n))
    f = _font(size)
    y = 1
    for ln in lines:
        d.text((4, y), ln, fill=255, font=f)
        y += size
    return im


def test_frame():
    im = Image.new("L", (OLED_W, OLED_H), 0)
    d = ImageDraw.Draw(im)
    d.rectangle([0, 0, OLED_W - 1, OLED_H - 1], outline=255)     # flush border
    d.rectangle([3, 3, 22, 22], fill=255)                        # true 20x20 square
    d.text((OLED_W // 2 - 12, 2), "F", fill=255, font=_font(52)) # orientation
    d.ellipse([OLED_W - 44, OLED_H - 24, OLED_W - 4, OLED_H - 4], outline=255)  # round circle
    for gx in range(OLED_W):                                     # smooth 16-level ramp
        im.putpixel((gx, 30), int(gx * 255 / (OLED_W - 1)))
        im.putpixel((gx, 31), int(gx * 255 / (OLED_W - 1)))
    return im


def _rev4(n):
    return ((n & 1) << 3) | ((n & 2) << 1) | ((n & 4) >> 1) | ((n & 8) >> 3)


def variants_frame():
    """Six 'A's left->right, each with a different 4-bit level mapping.
    Level L is written as (L<<4) so the normal packer's >>4 recovers exactly L.
      1 truncate (px>>4)        2 bit-reversed nibble    3 rounded
      4 1-bit threshold         5 gamma 0.5              6 inverted
    If all six look equally noisy -> it's the pixel-pair (nibble) order, not the
    level map."""
    maps = [
        lambda v: v >> 4,
        lambda v: _rev4(v >> 4),
        lambda v: min(15, (v + 8) // 17),
        lambda v: 15 if v >= 128 else 0,
        lambda v: min(15, round(((v / 255) ** 0.5) * 15)),
        lambda v: 15 - (v >> 4),
    ]
    base = Image.new("L", (OLED_W, OLED_H), 0)
    d = ImageDraw.Draw(base)
    cw = OLED_W / 6.0
    f = _font(46)
    for i in range(6):
        d.text((int(i * cw) + 6, 4), "A", fill=255, font=f)
        d.text((int(i * cw) + 2, 0), str(i + 1), fill=255, font=_font(10))
    src = base.load()
    out = Image.new("L", (OLED_W, OLED_H), 0)
    op = out.load()
    for x in range(OLED_W):
        fn = maps[min(int(x / cw), 5)]
        for y in range(OLED_H):
            op[x, y] = (fn(src[x, y]) & 0xF) << 4
    return out


def animate_balls(nballs=4, seconds=0.0, fps=25):
    """Bouncing balls in a box, streamed live.  seconds<=0 = run forever."""
    global GAP
    import random
    x0, y0, x1, y1 = 1, 1, OLED_W - 2, OLED_H - 2          # inner box walls
    balls = []
    for _ in range(nballs):
        r = random.randint(4, 8)
        balls.append([random.uniform(x0 + r, x1 - r), random.uniform(y0 + r, y1 - r),
                      random.choice([-1, 1]) * random.uniform(1.2, 2.6),
                      random.choice([-1, 1]) * random.uniform(1.0, 2.2),
                      r, random.choice([120, 170, 210, 255])])
    dev = open_oled()
    GAP = 0.002
    set_picture_mode(dev)                                  # ONCE - it clears to black
    t0 = time.time()
    frames = 0
    try:
        while seconds <= 0 or time.time() - t0 < seconds:
            fstart = time.time()
            im = Image.new("L", (OLED_W, OLED_H), 0)
            d = ImageDraw.Draw(im)
            d.rectangle([0, 0, OLED_W - 1, OLED_H - 1], outline=255)
            for b in balls:
                b[0] += b[2]; b[1] += b[3]
                if b[0] - b[4] <= x0: b[0] = x0 + b[4]; b[2] = abs(b[2])
                if b[0] + b[4] >= x1: b[0] = x1 - b[4]; b[2] = -abs(b[2])
                if b[1] - b[4] <= y0: b[1] = y0 + b[4]; b[3] = abs(b[3])
                if b[1] + b[4] >= y1: b[1] = y1 - b[4]; b[3] = -abs(b[3])
                d.ellipse([b[0] - b[4], b[1] - b[4], b[0] + b[4], b[1] + b[4]],
                          fill=b[5], outline=255)
            upload(dev, pack_fast(im))
            frames += 1
            dt = time.time() - fstart
            if frames % 25 == 0:
                print(f"  ~{frames/(time.time()-t0):.1f} fps", flush=True)
            wait = 1.0 / fps - dt
            if wait > 0:
                time.sleep(wait)
    except KeyboardInterrupt:
        print("\nstopping", flush=True)
    finally:
        dev.close()


def render(frame, xoff=XOFF):
    """Push one PIL frame to the OLED."""
    dev = open_oled()
    try:
        show(dev, pack4_frac(frame, STRIDE, OLED_W, OLED_H, xoff))
    finally:
        dev.close()


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "test"
    if cmd == "image":
        frame = img_to_frame(Image.open(sys.argv[2]))
    elif cmd == "text":
        frame = text_frame(sys.argv[2:] or ["ROG"])
    elif cmd == "clock":
        frame = text_frame([time.strftime("%H:%M:%S  %a %d %b")])
    elif cmd == "off":
        frame = Image.new("L", (OLED_W, OLED_H), 0)
    elif cmd == "probe":
        kind = sys.argv[2] if len(sys.argv) > 2 else "h"
        im = Image.new("L", (OLED_W, OLED_H), 0)
        p = im.load()
        for y in range(OLED_H):
            for x in range(OLED_W):
                if kind == "hline":
                    on = (y == 32)             # single white row
                elif kind == "block":
                    on = (y < 32)              # top half white (comb edge test)
                elif kind == "white":
                    on = True                  # solid white
                elif kind == "h":
                    on = (y % 2 == 0)          # 1px horizontal stripes
                elif kind == "v":
                    on = (x % 2 == 0)          # 1px vertical stripes
                elif kind == "h2":
                    on = (y % 4 < 2)           # 2px horizontal stripes
                else:
                    on = (x % 4 < 2)           # 2px vertical stripes
                p[x, y] = 255 if on else 0
        dev = open_oled()
        try:
            show(dev, pack4_frac(im, STRIDE, OLED_W, OLED_H, 0, 0.0))
        finally:
            dev.close()
        print(f"probe {kind}", flush=True)
        return
    elif cmd == "balls":
        n = int(sys.argv[2]) if len(sys.argv) > 2 else 4
        secs = float(sys.argv[3]) if len(sys.argv) > 3 else 0.0
        f = float(sys.argv[4]) if len(sys.argv) > 4 else 2.5
        animate_balls(n, secs, fps=f)
        return
    elif cmd == "gif":
        frames, durs = load_gif_frames(sys.argv[2])
        dev = open_oled()
        try:
            upload_frames(dev, frames, durs)
        finally:
            dev.close()
        print(f"uploaded {len(frames)}-frame looping animation, durations={durs}ms", flush=True)
        return
    elif cmd == "music":
        interval = float(sys.argv[2]) if len(sys.argv) > 2 else 5.0
        count = int(sys.argv[3]) if len(sys.argv) > 3 else 0
        music_songname(interval, count)
        return
    elif cmd == "ballsgif":
        nf = int(sys.argv[2]) if len(sys.argv) > 2 else 16
        nb = int(sys.argv[3]) if len(sys.argv) > 3 else 4
        dur = int(sys.argv[4]) if len(sys.argv) > 4 else 60
        frames = balls_gif_frames(nf, nb)
        print(f"rendered {nf} balls frames; uploading (~{nf*111*0.019:.0f}s)...", flush=True)
        dev = open_oled()
        try:
            upload_frames(dev, frames, [dur] * nf)
        finally:
            dev.close()
        print(f"uploaded {nf}-frame bouncing-balls loop @ {dur}ms/frame", flush=True)
        return
    elif cmd == "variants":
        frame = variants_frame()
    elif cmd == "shear":
        sh = float(sys.argv[2]) if len(sys.argv) > 2 else SHEAR
        dev = open_oled()
        try:
            show(dev, pack4_frac(variants_frame(), STRIDE, OLED_W, OLED_H, XOFF, sh))
        finally:
            dev.close()
        print(f"shear={sh} px/row", flush=True)
        return
    elif cmd == "fcal":
        # tuning: fcal <stride> <width> <xoff>
        sf = float(sys.argv[2]) if len(sys.argv) > 2 else STRIDE
        wv = int(sys.argv[3]) if len(sys.argv) > 3 else OLED_W
        xo = int(sys.argv[4]) if len(sys.argv) > 4 else XOFF
        dev = open_oled()
        try:
            show(dev, pack4_frac(cal_pattern(wv, OLED_H), sf, wv, OLED_H, xo))
        finally:
            dev.close()
        print(f"fcal stride={sf} width={wv} xoff={xo}", flush=True)
        return
    else:
        frame = test_frame()
    render(frame)
    print(f"sent '{cmd}' to OLED ({OLED_W}x{OLED_H}, 4-bit grey)", flush=True)


if __name__ == "__main__":
    main()
