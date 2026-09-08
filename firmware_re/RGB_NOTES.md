# ROG Azoth RGB backlight — reverse engineering

Enough to drive the per-key backlight arbitrarily from custom firmware. Verified by
flashing a per-index rainbow (build_led.py) — each key showed a distinct color.

## Hardware
- **~120 per-key RGB LEDs**, driven by an **I2C LED-matrix driver at address 0x30**
  (IS31FL37xx-family: page-based registers, PWM per channel). Sent in **two 60-LED
  halves**. Colors are gamma-corrected + reordered (GRB-ish) before the I2C write.
- 9 lighting modes (Fn+Left/Right cycles them). Mode index lives in RAM; `FUN_0002b8d4`
  is the Fn brightness/mode control (`if (9 < mode) return` => modes 0..8).

## Software pipeline (mode -> pixels -> wire)
1. **Effects** write a **6x16 color palette** (RAM `0x2000aa24`, 288 B = 6 rows x 16 cols
   x RGB) + **per-LED palette indices** (flash `0x47510`, 2 bytes/LED = (row,col)).
   Effect renderers: `FUN_00033578`, `FUN_00027430`, `FUN_00030958` (the 9 modes);
   color helpers `FUN_000271e8` (HSV/RGB interp), `FUN_0002716c` (region fill),
   `FUN_000271c0` (clear buffers).
2. **`FUN_00031798`** (called every main-loop iter from the worker `FUN_000332f4`) is the
   LED state machine: composes a **180-byte RGB framebuffer** (60 LEDs x 3) at
   `0x2000ab68` (=`DAT_00031980`-0xb4) by looking up palette[index]*brightness, double-
   buffered; then hands it to the send.
3. **`FUN_00031b28(subop, half, rgb_buf)`** — on subop 0 reads the 180-byte RGB buffer,
   runs each LED through gamma (`FUN_0002829c`), and **scatters** it into the I2C page
   buffer (`DAT_00031c7c`) per the physical CS/SW matrix wiring (stride 0x1e, groups of
   6/9). subop 3 sends: **`FUN_00029704(page_buf, len, 0x30)`** = I2C write to driver 0x30
   (via `FUN_000297c4` TWIM master). Two halves -> two transfers.

## Key tables (flash)
- **key->LED map**: `0x47207`, indexed by HID keycode -> LED number.
- **LED->palette-index**: `0x47510` (per-LED (row,col) into the 6x16 palette).
- **default palette / color tables**: near `0x47268`, `0x4725c`.

## How to drive it arbitrarily (the override)
Detour **`FUN_00031b28`** (entry is `push.w {r2-r10,lr}` = 4 bytes; replace with `b.w
myled`, replicate the push, resume at 0x31b2c). On subop 0, overwrite the 60x3 RGB buffer
(`param_3` = r2) with your own colors, keyed by LED index `half*60 + i`. The firmware then
gamma-corrects, physically scatters, and I2C-writes it. This is exactly how the OLED flush
detour works. See cfw/build_led.py (rainbow test) and cfw/combo_nn.c `led_fill()`.

## Physical mapping (empirical, TODO)
LED buffer index -> physical key is **scattered** (driver CS/SW wiring): consecutive
indices land on physically distant keys (observed: idx-adjacent keys share hue; e.g.
Esc..F5 one hue, but 8 and Del are isolated). To get index->(key / x,y): probe one LED at
a time on-device and record the lit key, or reverse the scatter in `FUN_00031b28` +
`0x47207`. Modes 5 (reactive/trail), 8 (h-lines), 9 (rain) encode key/x/y and can help.
Not needed for non-spatial effects (hue animations, prediction-tint).
