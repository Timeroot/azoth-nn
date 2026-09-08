# ROG Azoth OLED — Reverse-Engineered USB Protocol

Everything here was reverse-engineered on a **wired ROG Azoth** by direct probing +
USBPcap captures of Armoury Crate + static strings from `ArmouryKbSDK.dll`. It lets
you drive the OLED with no Armoury Crate. Model code is **M701** (HAL class
`CHalFunction_M701`).

## Device / transport

| | |
|---|---|
| VID | `0x0B05` |
| PID | `0x1A83` wired · `0x1ACE` 2.4G dongle |
| OLED interface | vendor HID, **usage page `0xFF00`, usage `0x0001`** (MI_01 on wired; pick by usage page, not interface number) |
| Report ID | **`0x02`** — the leading byte of every command IS the HID report id. On Windows pass the buffer starting `0x02` (do **not** prepend `0x00`). `OutputReportByteLength` = 65 = report-id + 64 data. |
| Transport | interrupt OUT `0x02`, interrupt IN `0x82` (ACKs). No control transfers. |

All commands below are written as the **data after the report id**. On the wire each
report is `02` + these bytes, zero-padded to 64 data bytes.

## Panel format

- **208 × 64 px, 4-bit greyscale (16 levels)**, 2 px per byte.
- Nibble order: **low nibble = left pixel**, high nibble = right pixel. `byte =
  (right<<4) | left`.
- Row-major, origin top-left, no flip. Row stride = 104 bytes = 6656 bytes/frame.
- (The community doc IcyBlue17/ROG-AzothOLED-HIDProtocol said "104×64 8-bit" — that
  was 104 *bytes*/row misread as pixels, and it was for the dongle.)

## Command map (report-id `0x02` + …)

### Picture / animation — `0x61`
| bytes | meaning |
|---|---|
| `12 03` then `12 01` | enter **picture mode** (needed once before an upload) |
| `61 00 00 00 <n>` + `50 55` | **select firmware preset** `n` (built-in, stored in keyboard, loops smoothly). `n=0` is the safe default — also our crash recovery. |
| `61 01 00 00 <count_LE16>` | **start upload**; `count` = number of `61 02` data packets that follow. ⚠ **two** `00` bytes then the LE16 count at offset 4–5. |
| `61 02 <idx_LE16> <60 bytes>` | **data packet**; `idx` is a **16-bit LE** counter from `count-1` down to `0`. 60 payload bytes/packet. |
| `61 03` | **end** |
| `50 55` | **commit** (finalizes + saves to flash) |

**Payload stream** (spread across the `61 02` packets, 60 bytes each):
```
header:  <N> 00 <dur0_LE16> <dur1_LE16> … <dur{N-1}_LE16>      (2 + 2N bytes)
pixels:  <framebuffer 0 (6656 B)> <framebuffer 1> … <framebuffer N-1>
```
- `N` = frame count. A **still image is just N=1** → header `01 00 E8 03` (1 frame,
  `0x03E8`=1000 ms). A GIF is N≥2, `count = N×111`.
- Durations are per-frame playback time in ms (LE16). The keyboard stores every
  frame and **loops them in firmware** — smooth, no per-frame blank.

**Upload handshake (critical).** The firmware **echoes each packet back on IN
`0x82`** as its ACK: for a data packet `61 02 <idx>` it replies `61 02 <idx> <status>`
(`status 00` = OK). You must **wait for the echo of that index before sending the
next packet, and retry if it doesn't come**. Blasting packets ahead of the ACKs
corrupts the saved GIF. A malformed packet is NAK'd with `ff aa …`. Armoury Crate
paces ~15.6 ms/packet doing this.

### Text banner — `0x62`
The PC renders the text (font/size/style) to a 208×64 image and uploads it exactly
like `0x61` (start/data/end/commit, ~80 packets), so it **blanks** like a still
image. HAL: `SetOled_CustomBanner` / `_Data`, sub-ids `…_BANNER_MODE`, `…_FONT`,
`…_SHOW_ONLY`.

### Music mode — `0x67`
Live audio-visualizer + scrolling song-name **stream** (continuous, no blank) while
music plays. HAL: `SetOled_MusicMode`. Three sub-ops (byte[1]):

| sub | format | role |
|---|---|---|
| `00` | `67 00 00 00 02 02 <n_pkts> 00 <width_LE16> 20` | **header** announcing a name/art update: `n_pkts` = how many `67 01` packets follow, `width` = bitmap width px, `20`=32 = height |
| `01` | `67 01 <idx> <payload>` | **song-name / art bitmap**, `idx` ascending `0..n_pkts-1`, ~61 payload bytes each. Rendered on the PC to a `width×32` image (widths seen 208/268/382 — **wider than the 208 screen, so it scrolls**). Pixels, **not ASCII**. |
| `02` | `67 02 00 xx <bars>` | **visualizer**, ~**31 bars/frame**, streamed continuously (~7/s). All-zero when audio is paused. |

**UTF-8 quirk:** Armoury Crate serializes the whole `0x67` channel through a UTF-8
string path, so any data byte ≥ `0x80` is expanded to a multi-byte sequence (or
mangled to `ef bf bd` = U+FFFD). This corrupts loud visualizer bars and makes the
song-name bitmap non-reconstructable from a capture. (The `0x61` image channel is
**not** UTF-8-encoded — clean binary.) To drive the song-name bitmap ourselves
without hitting this, keep pixel bytes < `0x80` (use grey nibble ≤ 7 for "on"
pixels), which round-trips cleanly regardless of whether the firmware UTF-8-decodes.

**Music-mode entry** (captured from selecting it in the AC UI) — a `0x22`
transaction wrapping the mode set, all ACK'd:
```
12 03 · 12 00 · 12 01 · 22 01 · 12 12 · 7d 20 02 · 22 02
```
**Name-header layouts** (`67 00 …`): with-visualizer = `67 00 00 00 02 02 <npk> 00
<w_LE16> 20` (name height 32); music-info-only = `67 00 00 00 00 00 <npk_LE16>
<w_LE16> 40` (name fills height 64). `npk = ceil(w * h/2 / 60)`; widths seen up to
662 (long scrolling titles).

**Open problem / not yet reproducible:** driving the name ourselves fails — the
`67 00` header is **NAK'd `ff aa`** even sent byte-identical to AC's, after the full
verified entry sequence (`12 03·12 00·12 01·22 01·12 12·7d 20 02·22 02`, all ACK'd),
and with a sustained live `67 02` visualizer stream. AC's own `67 00` in the capture
*succeeds* (echo ACK) right after ~10s of continuous visualizer.

Verified there is **no other channel**: the entire host→keyboard transcript is
interrupt OUT on ep `0x02` (only control transfers are enumeration at t=0; no Feature
reports; no other OUT endpoints; IN eps `0x81`/`0x83` are the keyboard's own key/
media inputs to the host). Ruled out exhaustively — the NAK persists with: exact
entry sequence (incl. the enum-time `12 14 02` OLED-init), exact AC header bytes,
sustained live visualizer, a **freshly re-enumerated** keyboard, and **Armoury Crate
fully killed** (processes+services). Our mode-entry commands ACK but don't even
visibly switch the OLED to music mode, while our `0x61` writes DO change it — so the
writes land, but the music state machine won't advance. So the gate is a **firmware
state-machine subtlety on the `0x02` interface** that byte-accurate replay can't
trigger — not a channel, not software ownership, not state/timing we can set.
Reproducing it needs nRF52 **firmware** RE (no clean image on disk). The `music`
command in azotholed.py implements the full flow but hits this NAK. (Music-mode name updates DO
render with no blank for AC, so it's still the best smooth-live-text candidate if the
gate is ever cracked.)

### System-info widgets (smooth, firmware-rendered — no blank)
These just feed **values** to built-in widgets, so they update in place ~1/s.
| cmd | format |
|---|---|
| `66 00 <nfields-1> 00` + fields `<TYPE> <unit> <val_LE16>` | metric screen |
| `63 00 00 00 <fmt> <yr_LE16> <mon> <day> <hr> <min>` | date/time; `fmt` `01`=12h `00`=24h |
| `64 00 00 00 <pct>` | battery % |

`0x66` **TYPE** codes: `00` CPU %, `01` CPU temp, `02` CPU freq, `05` CPU volt,
`11` DRAM %, `12` GPU freq, `30` GPU temp, `32` DRAM freq. `unit` byte = `ff`/`00`/`01`
(display/format hint). `nfields-1` = `00` (one value) or `01` (two side-by-side).

### Settings
| cmd | meaning |
|---|---|
| `71 00 00 00 <opt>` + `50 55` | **Control Knob** function select (cycled through `01`/`02`/`03` = Media-Track / brightness-adjust toggles) |
| `51 39 …` | **Power-Saving Mode** toggle |
| `51 3a 00 00 <pct>` | **battery lighting-alert** threshold % (saw `14`=20, `1e`=30, `32`=50) |

HAL also exposes `OLED_BRIGHTNESS`, `OLED_SWITCH` (on/off), `OLED_NOTIFICATION`
(Windows Alarm/Calendar/Mail), `AMOLED_SWITCH_MODE` / `AMOLED_MODE` — captured names,
exact bytes not all isolated yet.

## Bad states & recovery

| state | cause | recovery |
|---|---|---|
| **Crash-loop** (boot anim → pause → black → restart), keys fine | a bad animation that **committed** (`50 55`) corrupt frames to flash (overrun with no ACK-wait, or malformed bytes). Replug does **not** help — it's saved. | spam **preset-select** `61 00 00 00 00` + commit until it catches (`fix_preset.py`). |
| **OLED black / hung**, no reboot, keys fine | malformed upload that was **not** committed (e.g. bad start packet, aborted mid-upload) | **unplug/replug** (nothing was saved) |
| `ff aa …` reply | firmware **NAK** — packet rejected (e.g. the missing-`00` start bug below) | fix the packet |

Our tool aborts an upload **without committing** if any packet isn't ACK'd, so a
failed attempt lands in the recoverable "black" state, not the crash-loop.

## Gotchas that cost us time (in order discovered)

1. Report id is `0x02`; don't prepend `0x00` (that's the Mac-vs-Windows framing).
2. Payload is **60** bytes/packet on Windows (65-byte wire report), not 59.
3. **Nibble order is swapped** (low nibble = left pixel) — else steep diagonals jitter.
4. Row stride is exactly **208** (integer) — 204/205 were red herrings from earlier
   wrong pixel models.
5. The `0x61` still-image upload **blanks** the panel and has ~1–2 s
   commit-to-display latency → live per-frame streaming is impossible; use the
   **multi-frame store** instead.
6. Data-packet index is **16-bit LE** (`61 02 <lo> <hi>`), not `<idx> 00`. (Single
   frames have idx < 256 so the bug was invisible until multi-frame.)
7. **Start packet needs two `00`s**: `61 01 00 00 <count_LE16>`. We had one, so the
   count landed at the wrong offset → NAK `ff aa` → corrupt/crash. **This was the
   final bug.**
8. Must honor the **ACK-echo handshake** (wait for `61 02 <idx>` echo, retry).

## Tools in this directory

- **`azotholed.py`** — the driver. Commands: `test`, `image <path>`, `text "…"`,
  `clock`, `off`, `gif <animated.gif>`, `ballsgif [frames] [balls] [ms]`,
  `balls` (live, slow/flickery — obsoleted by `ballsgif`), plus calibration debug
  (`probe`, `fcal`, `shear`, `variants`). Key funcs: `pack_fast`, `upload_frames`
  (multi-frame + handshake), `load_gif_frames`.
- **`azoth_gui.py`** — Tkinter packet sender (raw report + sliders + presets). Run
  with real `python.exe` (the `pythonw` store-alias is a no-op stub).
- **`fix_preset.py`** — recovery: hammers preset-select to escape a crash-loop.
- **`capture2.ps1`** — elevated USBPcap capture on `\\.\USBPcap2` (`-A
  --inject-descriptors`), stoppable via `stop.flag`.
- Analysis: `verify.py` (offline-build our packets), `debug_ack.py` (dump ACKs),
  `re_dll.py` (PE exports/strings), `triage.py` (firmware entropy/strings).

## Firmware-verified command reference (from Ghidra RE of the app)

Decompiled from `M701_KEYBOARD_V04_00_13.bin` (see `firmware_re/`). The USB HID
output-report handler is **`FUN_0002330c`** (dispatch on `pkt[0]`); the display/upload
commands `0x61,0x62,0x63,0x64,0x65,0x66,0x67` are processed by
**`FUN_0002d7a0(cmd, pkt[1], u16@pkt[2], pkt+4, state)`** whose **return value IS the
response protocol**:
- **2 → send ACK-echo** via `FUN_00024efc(pkt[0], …)` (echoes cmd+idx+status).
- **1 → NAK**: `FUN_00024f7c(code)` = `FUN_00024efc(0xff,0xaa,code,0,0)` ⇒ **`ff aa <code>`**.
- **0 → silent** (no response) — used for fire-and-forget (e.g. the visualizer).

`FUN_0002d7a0` `switch(cmd)` (param_4 = pkt+4, so param_4[k] = pkt[4+k]):
- **`0x61` image** — subop0 header (`if pkt[4]>5 → NAK`), subop1/2/3 frame states.
- **`0x62` text banner** — subop0 validates dims (width `0xd0`=208, or count `0xff`
  & height `0x40`), rejects if `height*(width/2)+6 > 0x9000` (36864 = max frame).
- **`0x63` (99) date/time** — formats yr/mon/day/hr/min with `:`; optional seconds.
- **`0x64` (100) battery**.
- **`0x65`/`0x66` sysinfo widgets** — `0x66`: `if (nfields>1) NAK`; builds the label
  (nibble `pkt>>4` selects CPU/GPU/DRAM/…) + value strings.
- **`0x67` MUSIC** (fully decoded):
  - **subop 0 (name header):** `pkt[4]`: 0 = name-only (**height pkt[10..11] must be
    `0x40`=64**), else with-visualizer (**height must be `0x20`=32**); **width =
    pkt[8..9], width/2 ∈ [104,520]** (px 208-1040); stores **npk = pkt[6..7]** into the
    packet counter (`DAT_0002dc18+0x61`). Bad dims → NAK; else **ACK** (`iVar15`
    defaults to 2). *Answered with an echo when valid.*
  - **subop 1 (name data):** `if counter==0 → NAK`; `if counter-1 != idx → NAK`; else
    store frame + decrement counter → **ACK**. (So data before a valid header NAKs.)
  - **subop 2 (visualizer):** store, **return 0 = silent** (matches fire-and-forget).

Other opcodes handled directly in `FUN_0002330c`: `0x12` (mode/query — subops `00/01/03`
are the mode switches, special-cased; `12/13/14/15` are queries, some NAK), `0x21/0x22`
(txn wrapper), `0x50 55` (commit), `0x69/0x71/0x72` (per-key / effect controls), `0x7d`
(**capability query** e.g. `7d 20 02` → returns support status; NOT a mode-set), `0xc0`
(streamed per-key data, sub `0x81`), `0xfa`/`0xfc` (RGB / factory). **Bonus:** a factory
command set with ASCII sub-cmds `READ/WRITE/VERIFY/EN_RF/EN_PAIR/CLEAR/LV_RF` (RF
pairing + flash r/w), error codes `0x15-0x1a`.

**Music-gate status — REVISED by RE:** the decompile shows **no firmware mode-gate on a
valid `67 00` header** — it reaches `case 0x67`, dims are validated, and it returns 2 =
ACK regardless of any "music mode" state. `DAT_00023700[1]` (the dispatcher's line-57
guard) is just the **response-in-progress flag** (set for chunked replies, cleared when
sent — not an upload/mode state). So our repeated `ff aa` was **not** a firmware gate:
most likely our `music` tool matched a **stale ACK** from the preceding entry commands
(`12`/`22`/`7d`), or was skipped while a chunked response was mid-send. **Implication:
music-name streaming *should* work** with a tool that syncs reads between commands.
**Honest caveat:** raw debug showed `ff aa` for the header even after draining, which
the decompiled `case 0x67` path does not explain (valid dims → ACK). So there's an
unreconciled static-vs-observed discrepancy — a subtle upstream path in the (very
messy) dispatcher flow, or read-timing. Definitive resolution wants dynamic (SWD)
debug; statically it's the remaining loose end. A clean live re-test (kill AC, replug,
proper read-drain) is the cheap next probe.

## Bootloader & brick recovery (firmware-verified)

**Two DFU-entry paths, both usable.** The hardware key-combo is **`Fn + L + B`**.

**1. Hardware matrix combo — `Fn + L + B` held at power-on.** Bootloader `FUN_000f35ec`
scans 7 cols × 14 rows and, *only while the rear 3-way switch is in the wired/USB
position* (gated by `FUN_000f37c0`, which reads P0.IN bits 14/15 = the Off/2.4G/BT slide
switch), requires the matrix to read **exactly** `col3==0x200 (bit9) + col4==0x40 (bit6)
+ col5==0x400 (bit10)`, cols 0/1/2/6 == 0, held ~30 scan cycles → `return 1` = enter DFU.
So: **set the rear switch to wired/USB, hold Fn + L + B, and plug in / power on** → DFU,
no SWD, no case-opening.

Matrix wiring is **fully pinned, no permutation** between bootloader and app:
- Columns: pin = `P0.(9+col)` for col 0..6 (bootloader `1<<(col+9)`; app `FUN_000432a4`
  = `OUTSET = 0x200<<col`; scanner `FUN_0002b0b8` mask `0xfe00`).
- Rows: sense bits 0..13 in both (`& 0x3fff`).
- App keymap index = `layer*98 + col*14 + row` (`FUN_0002a498`), **base pointer
  `DAT_0002a7a8 = 0x476a3`** (proven: that 32-bit literal occurs exactly once in the
  image, at `0x2a7a8`; `0x476a4` never appears). Base `0x476a3` puts **Esc at (col0,row0)**
  and makes every matrix column a clean physical keyboard row (leftmost key at row0).
  ⚠️ *Earlier notes used `0x476a4` — an off-by-one that mis-shifted every row and wrongly
  made (col5,row10) look empty. The bootloader keymap copy has the same −1 fix: base
  `0x0fa4d8` (literal @`0xf3e84`).*

Under the correct base the three combo cells are:
| cell | bits | keycode @0x476a3 |
|---|---|---|
| (col3,row9) | bit9 | **`L`** (0x0f) |
| (col4,row6) | bit6 | **`B`** (0x05) |
| (col5,row10) | bit10 | **`Fn`** (0x e8, vendor) |

**2. Software DFU (also CONFIRMED — what Armoury Crate uses).** `FUN_0002a058` logs
`"enter bootloader"`, writes the DFU magic to GPREGRET (`*DAT_0002a08c = DAT_0002a088`)
and resets → re-enumerates as boot PID `1A84`; `peripheral_fwu_pro.exe` reflashes the
**app region only**, bootloader + SoftDevice preserved. Works while the app still boots
and enumerates USB.

**Net brick-safety picture:** two independent recovery paths — the **`Fn+L+B` power-on
combo** works even if the app is completely dead (bootloader-resident), and **software
DFU** works while the app runs. DFU always flashes the app region only. Remaining
nice-to-have: confirm the nRF bootloader also auto-stays in DFU on app-validation failure
(CRC/vector) — a third backstop. *(Open item — see ROADMAP.)*

## Firmware image & DFU (recon)

Image `M701_KEYBOARD_V04_00_13.bin` (from ASUS `M701_FirmwareAutoUpdate_1.0.0.14.zip`),
`0xFF000` bytes, **unencrypted** nRF52840 (Cortex-M4, Thumb-2), loads at `0x0`.

**Flash layout** (candidate vector tables + entropy/marker scan):
| range | contents |
|---|---|
| `0x0–0x1000` | Nordic **MBR** (vtable SP `0x20000400`, reset `0xa80`) |
| `0x1000–0x27000` | **SoftDevice S140** (SD_INFO magic `0x51b1e5db` @ `0x3004`) |
| `~0x27000–0x48000` | **application** (main code) |
| `0x50000–0xd0000` | erased (`0xFF`) |
| `0xd0000–0xf3000` | **2nd code block** — HID/OLED handler + the only debug strings (e.g. `RX: size: %lu char: %c` @ `0xde440`); OLED cmd handling lives here |
| `0xf3000–0xff000` | **bootloader** |

APProtect is disabled (per SySS blog) → an SWD probe can dump/debug the live chip.

**DFU / flashing** (`peripheral_fwu_pro.exe`): entry is a **software** `"Jump to
Bootloader"` command to the running app → it re-enumerates as boot PID **`1A84`**;
the tool then erases+programs the **app region only** (`APP_SIZE`), leaving the
**bootloader intact**. Args seen: `m 1A83 1A84 112 200 FF00 FF00 4 <bin>` =
`[S/M] APP_PID BOOT_PID BOOT_SIZE APP_SIZE APP_UP BOOT_UP PAGE_SIZE <bin>`. Has
checksum verify ("Programming Success/Fail, retry"), a `LB` leave-boot flag.

**Brick risk (no-SWD):** bootloader + SoftDevice are preserved on an app flash, and
there is a **usable hardware DFU combo — `Fn + L + B` at power-on** (rear switch in
wired position; see *Bootloader & brick recovery* above) — so even a fully dead app can
be reflashed over USB. Plus the **software DFU path** (`0x2a058` → GPREGRET → reset) for
when the app still runs. This makes custom-firmware experimentation meaningfully safer,
though still not zero-risk. **See `firmware_re/ROADMAP.md`** for the static-RE project
that avoids flashing entirely (just read the protocol out of the image).

## Armoury Crate internals (from `ArmouryKbSDK.dll`, x86 native)

HAL class **`CHalFunction_M701`**. Relevant methods: `SetOled_DefaultAnimation`,
`SetOled_CustomAnimation` (+`_Data`), `SetOled_CustomBanner` (+`_Data`),
`SetOled_HardwareInfo`, `SetOledHwInfoThread`, `OledTimeThread`,
`GetOled_AvailableHardwareInfo`. Dispatched via export `ExecuteFunction` by
`SDK_COMMON_KB_FUNC_ID_OLED_*` ids. Uses overlapped I/O (Create/Set/ResetEvent +
WriteFile/ReadFile) and retries (`Result = FALSE, Retry = %d`). CPU metrics come
from bundled `cpuidsdk64.dll`; the DLL also bundles libcurl (for asset downloads).
