# azoth-nn — a neural next-key predictor running on an ASUS ROG Azoth keyboard

This repo is the result of reverse-engineering the **ASUS ROG Azoth** mechanical
keyboard (an nRF52840 / Cortex-M4F @ 64 MHz board) far enough to run **custom
firmware**, and then training a small **character-level language model** that runs
*on the keyboard itself* — predicting your next keystroke in real time, showing its
guesses on the little OLED, and lighting the predicted keys on the RGB backlight.

It contains two things:

1. **The firmware side** — how to build and flash custom firmware onto the board, drive
   the OLED and per-key RGB, read live keypresses, and (the hard part) fit and run a
   neural net in the tiny flash budget.
2. **The model side** — a full training/ablation pipeline (`firmware_re/cfw/`) and a
   multi-week research study on how to get the best character predictor per byte of
   flash. The write-up with all results is in
   [`firmware_re/cfw/nn_README.md`](firmware_re/cfw/nn_README.md).

> ⚠️ This is hobbyist reverse-engineering of *my own* keyboard. It is not affiliated
> with or endorsed by ASUS. Flashing custom firmware is **at your own risk** — read the
> safety section below first.

---

## 1. What it does

The stock firmware renders the OLED and lights the keys from a host app (Armory Crate).
We instead **detour** two functions in the running firmware — the OLED flush and the
LED send — so our own code draws the screen and colors the keys every frame, and reads
the live HID report to see what you type. On top of that hook we run a quantized
char-LM:

- **type** → the model updates its hidden state from your keystroke,
- the **OLED** shows the last character plus the top predicted next-characters,
- the **backlight** paints every key blue and the predicted next-key(s) **red**.

The model is trained on public-domain English prose. Here is a genuine **greedy (t=0)
rollout** from each model, primed with `"the "` (`_` = space, real newlines shown, `^` =
the model's "next letter is a capital" escape token):

**Small model** (`nn_64k`, 62 KB, int8 perplexity ≈ 4.88, top-1 ≈ 54 %):
```
the strange of the strange of the strange of the strange

 and so the strength of the stream to the strength of the strange of the

 property of the property of the strange of the stre
```

**Big model** (`nn_460k`, 468 KB, int8 perplexity ≈ 3.39, top-1 ≈ 63 %):
```
the same time the same time the same time the same time the

 produce of the country which is the same time to be a proper proportion to

 the property of the country. ^the price of th
```

Greedy decoding loops (as char-LMs do), but you can see the bigger model produces much
more coherent runs and correctly handles capitalization/punctuation. In *use* it's not
generating text — it's predicting your next key, where top-1 ≈ 54 %/63 % and top-3 ≈
75 %/82 % are what matter.

---

## 2. Flashing safety, and how to un-brick it

**Read this before flashing anything.** Custom firmware can and will occasionally hang
or fail to enumerate — I bricked the app several times during this project. The good
news is that **it is very hard to *permanently* brick**, because of how the board is
split:

- **Bootloader** (USB PID `0x1A84`) — a small, *separate, protected* program that only
  knows how to receive a firmware image over USB and write it to flash. **Normal
  firmware flashing never touches the bootloader.** It is your safety net.
- **App firmware** (USB PID `0x1A83`) — the actual keyboard: matrix scanning, USB HID,
  OLED, RGB, etc. This is what you overwrite when you flash. If *this* is broken, the
  keyboard may not type or enumerate — but the bootloader is still fine.

Because the two are independent, a bad app image only makes the app unusable; the
bootloader can always be re-entered to install a good one.

### Recovery: hold **Fn + B + L** while plugging in

If a flash bricks the app (no typing, no OLED, doesn't enumerate normally):

1. Unplug the keyboard.
2. Hold **Fn + B + L** (mnemonic: **B**oot **L**oader) and, while holding them, plug the
   USB cable back in. This forces the board straight into the bootloader instead of the
   (broken) app.
3. In this mode the standard ASUS driver / Armory Crate recognizes it as a keyboard in
   firmware-update mode and offers to restore/update the firmware — the intended, fully
   supported recovery path — so you can reflash the **stock** image and you're back to a
   normal keyboard. (You can also reflash from the CLI; see below.)

Nothing you flash to the app can take away this escape hatch. The one thing that *would*
be dangerous is corrupting the bootloader region itself, which normal DFU flashing
cannot do — but the "big model" self-programming path (section 4) writes flash directly,
so it is written to only ever touch a bounded high-flash region and **never** the
bootloader or app code.

### Flashing details (the CLI path)

The board's DFU is checksum-only: the updater tool writes the app region
`[0x1c000, …)`, and a simple 32-bit sum over `[0x1c000, 0x4dffc)` is stored at
`0x4dffc` and checked. Our build scripts (`build_combo3.py`, `build_phase1a.py`) patch
the stock image, fix up that checksum, and emit a flashable `.bin`. To flash you:

1. put the board in bootloader mode — either Fn+B+L, or send the app the
   "enter bootloader" HID magic (`firmware_re/enter_boot.py`, which sends
   `02 7b aa 41 53 55 53 aa` to the vendor interface so it re-enumerates as `1A84`);
2. run ASUS's `peripheral_fwu_pro` updater on the `.bin`.

To get back to stock, just flash the original `M701_KEYBOARD_V04_00_13.bin` the same way.

---

## 3. The easy path: a small model in one flashed image

The simplest deployment is a model small enough to live **inside a single DFU-flashed
firmware image**. The DFU updater can write flash up to a hard ceiling at `0x61000`, and
the weights sit at `0x50000`, so a single image gives you a **~70 KB weight budget**
(`[0x50000, 0x61000)`). That's enough for the `nn_64k` tier:

- **`nn_64k`** — 62 KB int8 weights, 72-symbol vocabulary (letters, digits, punctuation,
  space, Tab, newline, and a capitalization-escape token), a two-timescale GRU.
- **int8 perplexity ≈ 4.88**, top-1 ≈ 54 %, top-3 ≈ 75 % on held-out text.
- Its t=0 rollout is the "small model" sample in section 1.

How it works on-device: the build injects the weight blob at `0x50000`, the flush-detour
`render()` runs the forward pass each OLED frame (int8 weights × float activations on the
Cortex-M4F FPU; a libm-free Padé tanh/sigmoid), and updates the OLED + backlight. The
on-device forward pass is `firmware_re/cfw/nn.c` (a bit-exact match of the numpy reference
`nn_ref.py`), and `combo3_nn.c` is the full integrated firmware (predictor + OLED +
backlight + input handling, including one-level backspace undo and ignoring non-text
keys). No self-programming, no special tooling — just flash the image and it runs.

*(Note: the integrated `combo3` demo in this repo currently ships an earlier, smaller
letters-only predictor; the 72-vocab two-timescale models above are trained, quantized,
and verified against `nn.c`, and are the drop-in weights/forward for a full build.)*

---

## 4. The hard path: a 400 KB model (self-programming)

A 400 KB+ model gives a big quality jump (`nn_460k`: int8 perplexity **3.39** vs 4.88,
top-1 **63 %** vs 54 %) — but it does **not** fit under the DFU's `0x61000` ceiling. The
trick relies on a distinction we mapped out (see
[`firmware_re/FLASH_BUDGET.md`](firmware_re/FLASH_BUDGET.md)):

- The DFU updater **refuses to write** at/above `0x61000` (it even ACKs the writes, then
  silently drops them — a fun bug to discover).
- But the CPU can **read** all 1 MB of flash directly (it's memory-mapped), and there is
  **~490 KB of free flash above `0x61000`** (`[0x61000, 0xdb000)`, where GIF/asset data
  normally lives).

So the plan is: the app **programs its own flash**. The nRF52840's flash controller
(NVMC) can erase/write pages at runtime; we drive it from a custom HID command:

1. A host tool (`firmware_re/wflash.py`) streams the weight blob to the keyboard over a
   custom `WF` HID command.
2. The firmware's command handler erases the target 4 KB pages at `0x61000+` and writes
   the words with the NVMC (bounds-checked to **only** touch `[0x61000, 0xdb000)` — never
   app code or the bootloader).
3. `render()` then points its weight pointers at `0x61000+` and reads the big model in
   place.

This is riskier than DFU (a self-program bug can corrupt flash), which is exactly why the
handler is bounded and why the recovery combo in section 2 matters. The primitive is
proven end-to-end in `firmware_re/cfw/phase1a_flash.c`, which writes a known pattern above
the ceiling and reads it back — the "big model can be deployed" existence proof. Wiring
the full 460 KB upload into `combo3` is the natural next step and is what the pieces here
are built for.

---

## 5. Everything else that was reverse-engineered

Getting to "run a neural net on it" required mapping out most of the firmware. Highlights
(full notes in [`firmware_re/RGB_NOTES.md`](firmware_re/RGB_NOTES.md) and
[`firmware_re/FLASH_BUDGET.md`](firmware_re/FLASH_BUDGET.md)):

- **OLED (256×64, 4bpp):** framebuffer at RAM `0x2000dd60`, stride `0x80`, low nibble =
  left pixel; a `DIRTY` flag at `0x200034ba` sustains continuous flushing. We hook the
  flush routine (`0x31658`) to draw our own screen. `azotholed.py` also drives the OLED
  purely over USB HID (no custom firmware needed) — the on-wire image format (4-bit grey,
  a fixed pixel stride, a shear/offset quirk) was worked out empirically.
- **Per-key RGB (~117 LEDs):** an IS31FL37xx-family I²C driver at address `0x30`, fed
  through a 6×16 color palette and a per-LED palette-index table, composed into a 60-LED×2-
  half framebuffer, then gamma-corrected and *scattered* to the physical CS/SW wiring. We
  hook the LED send (`0x31b28`) to recolor it.
- **Key → LED mapping:** solved statically. `keycode --(flash 0x47184)--> a grid id`
  where `col=(id-32)/9, row=(id-32)%9`; then invert the buffer→(row,col) table at
  `0x47510` to get the physical LED slot. (The spacebar has no per-key LED; it's driven
  via an internal scancode.) This is what lets us light *the specific key* the model
  predicts.
- **The knobs / modes:** Fn+Left/Right cycles a 0–9 lighting-mode index at RAM
  `0x200031bd`; Fn+Up/Down changes a per-mode brightness reached through a pointer table
  at `0x200031d8`. Our firmware reads these to switch between vanilla / rainbow / predict
  backlight and predictions / bouncing-balls / typing-ticker OLED modes.
- **Live keystrokes:** the HID report keycode array is at RAM `0x2000b6f8`, the count at
  `0x20003370`; Shift is detected from keycodes `0xe1`/`0xe5` in the report.
- **USB / HID protocol:** the vendor interface is FF00 / usage `0x0001` on PID `0x1A83`;
  we reversed the OLED upload commands, the "enter bootloader" magic
  (`02 7b aa 41 53 55 53 aa`), and the DFU update command format
  (`m 1A83 1A84 112 <APP_KB> FF00 FF00 4 <bin>`), including the checksum-only verification.
- **Flash map & self-program routines:** the app/bootloader/free-flash layout, the hard
  `0x61000` DFU ceiling, and the NVMC erase/write mechanics — all in `FLASH_BUDGET.md`.

---

## Repo layout

```
firmware_re/
  cfw/                 model training + on-device C forward + firmware build
    run_pke.py         the training driver (trains every model variant/ablation)
    nn_common.py       vocab, int8 quant, the numpy reference forward
    nn_ref.py          bit-exact reference / top-3 predictions for a model
    nn.c               the on-device (Cortex-M4) forward pass
    combo3_nn.c        integrated firmware: predictor + OLED + backlight + input
    build_combo3.py    patches the stock image into a flashable predictor firmware
    phase1a_flash.c    proven high-flash self-program primitive
    build_phase1a.py   build for the above
    nn_460k.*          the big model (int8 ppl 3.39) — weights + layout
    nn_fmlp_res_193k.* the research-best small-model variant
    nn_README.md       the full training/ablation study + Pareto results
    *_results.csv, grok_*.json   all experiment logs
  enter_boot.py        send the "enter bootloader" HID magic
  wflash.py            host-side weight uploader (self-program path)
  FLASH_BUDGET.md      flash map + self-program deployment plan
  RGB_NOTES.md         backlight/OLED/key-map reverse engineering notes
```

Training needs Python + PyTorch + a CUDA GPU and a text corpus (regenerate it with
`nn_fetch_corpus.py` / `nn_augment_corpus.py`); the firmware build needs
`arm-none-eabi-gcc`, `keystone`, and the stock firmware image.

The research write-up — how positional embeddings, sparsity, n-grams, a two-branch
"fuse" model, and very-long "grokking" training all compare on accuracy-per-flash-byte —
is in **[`firmware_re/cfw/nn_README.md`](firmware_re/cfw/nn_README.md)**.
