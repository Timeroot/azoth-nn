# Flash budget for a big on-device model (self-programming path)

Goal: deploy a model much larger than the ~70KB the DFU can write, by putting weights
in the flash region above the DFU ceiling and having the app self-program them there
(overriding the GIF/asset region — user-authorized).

## Flash map (stock V04_00_13, 1MB image 0x00000..0xff000)
- `0x00000..0x1c000` : MBR/bootloader + low structures (reset vec @0x4 = 0xa81, SP 0x20000400).
- `0x1c000..~0x4e000`: **app code+data**, DFU-written, checksummed over `[0x1c000,0x4dffc)`.
- `0x4e000..0x0db000`: **564 KB ERASED (0xFF)** — physically free. Our weights currently
  sit at `0x50000`. The DFU ceiling `0x61000` is inside this zone.
- `0x0db000..0x0e7000`: ~48 KB data (settings/asset area; some zeroed).
- `0x0e7000..0x0f3000`: 48 KB erased.
- `0x0f3000..0x0ff000`: bootloader/softdevice-ish data + zero fill.

## The two limits (do not confuse them)
1. **DFU write ceiling = `0x61000` (HARD).** `peripheral_fwu_pro` silently drops writes
   at/above `0x61000` (ACKs them, but they don't land). So DFU-flashable weight space is
   `[0x50000, 0x61000)` = 69,632 B (plus we can reclaim `[0x4e000,0x50000)`=8KB and the
   shim gaps → ~77 KB max for a DFU-only model). Device checksum only covers
   `[0x1c000,0x4dffc)`, so DFU "success" does NOT verify weights.
2. **CPU read range = all 1MB.** Flash is memory-mapped; `render()` can READ weights
   anywhere (incl. `0x61000+`) with a plain pointer. Only *writing* high flash is the issue.

=> For a model >77 KB, weights go to `0x61000+` and are written by **runtime self-programming**,
not DFU. Usable high region `[0x61000, 0x0db000)` ≈ **490 KB** (overrides GIF assets there).

## Reusable firmware flash primitives (found by disassembly, stock bin)
Call these directly from custom code (they wrap NVMC 0x4001E000; CONFIG=0x504, READY=0x400,
ERASEPAGE=0x508). Thumb addresses (LSB set):
- **`flash_erase_page(uint32_t pageAddr)` @ `0x3df55`** — CONFIG=EEN(2), ERASEPAGE=pageAddr,
  wait READY, CONFIG=0. Page size 4 KB (erase on 0x1000 boundaries).
- **`flash_write_words(uint32_t* dst, const uint32_t* src, uint32_t nWords)` @ `0x3df89`** —
  CONFIG=WEN(1), copy nWords words dst<-src (wait READY each), CONFIG=0. dst/src word-aligned.
(Other NVMC users at 0x1a0cc, 0x1a980, 0x4039c, plus bootloader copies at 0x0dc1c4/0x0e1780/
0x0f4xxx/0x0f7xxx.)

## Deployment sketch (for the big model, to build WITH the user present — brick risk)
1. Custom HID command (extend the FF00/usage1 vendor interface, like azotholed.py): host
   streams the weight blob in chunks with an offset.
2. Firmware handler: for each 4KB page touched, `flash_erase_page(0x61000+pageoff)` once, then
   `flash_write_words(...)` the chunk. Verify by reading back + a checksum command.
3. `combo` weight pointers point at `0x61000+` instead of `0x50000`.
4. Guard: refuse offsets outside `[0x61000, 0xdb000)` so a bad command can't erase the app
   (bricking). Recovery if it happens: Fn+L+B → reflash stock V04_00_13.

## Decision gate
Build the self-programmer ONLY if the training scaling curve shows models >77 KB give a
worthwhile ppl gain. If ppl plateaus by ~64-77 KB, ship the best DFU-flashable model and skip
the risk entirely. Do the actual self-program test with the user present (daily-driver keyboard).
