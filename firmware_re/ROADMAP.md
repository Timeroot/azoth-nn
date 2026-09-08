# ROG Azoth Firmware RE — project roadmap

**Goal:** statically reverse the full HID command protocol + state machine out of
`M701_KEYBOARD_V04_00_13.bin` (nRF52840, unencrypted). No hardware, no flashing —
just read the truth out of the image. End product: a complete command reference
(every opcode, sub-op, field, and the mode/state machine incl. the music-mode gate
that NAKs `67 00`) folded into `../PROTOCOL.md`.

## Target image
- `../M701_fw/.../Firmware/M701_KEYBOARD_V04_00_13.bin`, load base `0x0`, ARM
  Cortex-M4 little-endian, **Thumb**. Layout in `../PROTOCOL.md` (MBR / S140 /
  app / bootloader). Focus: **app `0x27000–0x48000`** and **2nd block `0xd0000–0xf3000`**
  (the HID/OLED handler + only debug strings live there). Ignore the SoftDevice.

## Tooling
- **Ghidra headless** (`analyzeHeadless`) — import at base 0x0 as ARM:LE:32:Cortex
  (Thumb), auto-analyze, then drive with Python/Java scripts to enumerate functions,
  xrefs (resolves `movw/movt` address loads that raw grep can't), and decompile.
- Capstone helpers already here: `../fwre.py`, `../disasm.py`, `../recon.py`.
- Scripts live in this dir; Ghidra project in `ghidra_proj/`.

## Known anchors (starting points)
- Debug string `RX: size: %lu char: %c` @ `0xde440` — almost certainly printed by
  the **HID output-report handler**. Find its xref → the handler. THE linchpin.
- OLED `commit 50 55` byte-pairs @ `0x2dba5/2dba9/4711e`; `d0 40` (208×64) ×66.
- `ff aa` NAK bytes @ `0x0126fb`; cluster of `#0xaa` immediates near `0x3a132–186`
  (candidate ack/NAK response builder).
- Strings: "Demo Mode"/"Normal Mode"/"USB_Demo_Mode"/"enter/leave CDC mode" — mode
  concept; investigate relation to picture/music/sysinfo modes.
- Cmd bytes to trace: `12`(mode,incl `12 14`,`12 12`), `22`(txn wrapper 01/02),
  `7d 20 02`(music), `61`(image/anim + preset `61 00`), `62`(text), `63`(time),
  `64`(battery), `66`(sysinfo), `67`(music name/vis), `50 55`(commit).

## Phases
1. **[setup]** Install Ghidra + JDK; import + auto-analyze the bin; sanity-check
   function recovery (reset handler, USBD IRQ, the `0xde440` xref).
2. **[handler]** Locate the USB HID output-report receive path → the per-command
   dispatch. Confirm via the `0xde440` log xref and the cmd-byte compares.
3. **[dispatch]** Map the dispatch: for each opcode, the handler function + its
   sub-op switch. Build a table.
4. **[state machine]** Reverse the mode state var(s): what `12 12`/`7d 20 02`/`22`
   set, what `67 00` checks before accepting vs `ff aa`. → **solves music gate.**
5. **[per-command]** Decompile each handler; document exact field layouts, lengths,
   the ACK/echo + NAK logic, packet indexing, framebuffer addressing.
6. **[write-up]** Fold the complete protocol into `../PROTOCOL.md`; note any
   commands/features not previously observed on the wire.

## How to run (established)
- Ghidra 12.1.3 headless works on JDK 26. Project: `ghidra_proj/azoth`, program
  `M701_KEYBOARD_V04_00_13.bin` (already imported+analyzed, base 0x0, ARM:LE:32:Cortex).
- Run a Java GhidraScript (NOT .py — plain headless lacks PyGhidra):
  `& (gc headless_path.txt) ghidra_proj azoth -process M701_KEYBOARD_V04_00_13.bin
   -noanalysis -scriptPath ghidra_scripts -postScript <name>.java`
- Scripts so far: `azoth_dispatch.java` (rank fns by cmd-byte cmps), `azoth_find.java`
  (rank fns by distinctive constants), `azoth_dump.java` (decompile fn+callees to
  `decomp/`), `azoth_boot.java`, `azoth_query.java`.

## Progress log
### Session 1 (2026-09-07) — Ghidra set up, key functions located
- **OLED command handler = `FUN_0002330c` @0x2330c** (big; confirmed via framebuffer
  size **6656**(0x1a00 ×5) + meta **1000**(0x3e8) + commit 0x50). Decomp in
  `decomp/02330c_FUN_0002330c.c`. Dispatches on cmd byte: `0x12` mode, `0x22` txn,
  `0x66/0x67` sysinfo/music, `0x61` etc. Contains a **`switch(pkt[1])` (sub-op)** with
  cases 0..0x15; **case 0x13 sets the response byte to `0xaa` (the NAK)** — the music
  gate is a sub-op/state check in this switch. ← PULL THIS THREAD FOR MUSIC.
- Other OLED-ish: `FUN_0003a0f0` (6656 ×4), `FUN_0002e9e8` (1000 ×2).
- Decoy/utility fns identified: `FUN_000db850` = **vfprintf** (the 61/63/64/66/67 =
  printf letters a/c/d/f/g — false positive); `FUN_000de37c` = **debug-CDC RX** (owns
  the "RX: size: %lu char: %c" string, bit-bangs a GPIO).
- **Software DFU entry = `FUN_0002a058`**: writes magic → **GPREGRET** (`DAT_0002a08c`)
  then `FUN_0002cd9c` (system reset). Bootloader reads GPREGRET on boot.
- **Bootloader (0xf3000-0xff000) NOT auto-analyzed** (separate vector table; reset
  0xf34a4). Reads **P1.IN @0xf36ec/0xf3f20** → candidate hardware key-combo DFU entry
  = the brick-recovery path. Strings there: "enter bootloader", "Gaming Keyboard
  Bootloader", "Default configuration".
- FN+ESC reset (user report): strings "System reset" @0xdc8ac + "Default
  configuration" ×3 → it's a **settings-reset-to-default + soft reboot**, NOT a
  firmware wipe or bootloader entry (so it recovers bad *settings*, not bad firmware).
  "Reset processing/successful" are rendered bitmaps, not ASCII.

### Session 1 cont. — command dispatch fully traced
- **Dispatcher `FUN_0002330c`**: reads cmd=pkt[0]; big if/else. Cmds 0x63/64/65/66/67
  jump to `LAB_00024226` → **`FUN_0002d7a0(cmd, pkt[1], u16@pkt[2], pkt+4, state)`**.
  Its return: **2 = send ACK-echo** (`FUN_00024efc`), **1 = NAK `ff aa`**
  (`switchD_00024374_caseD_5`→default→LAB_00024cce), **0 = silent (no response)**.
- **`FUN_0002d7a0` = the upload/display processor**, `switch(cmd)`: case 0x61 image,
  0x62 text, 99(0x63) datetime, 100(0x64) battery, 0x65/0x66 sysinfo metrics
  (`if(1<nfields) return 1`), **0x67 music** @line 585. NOTE param_4 = pkt+4 (ppuVar5
  is undefined** so +1 word = +4 bytes); so param_4[k] = pkt[4+k].
- **case 0x67 (music) DECODED — subops:**
  - **subop 0 (name header):** pkt[4]: 0=name-only (height pkt[10..11] must be 0x40=64),
    else with-vis (height must be 0x20=32); width=pkt[8..9], width/2 must be in
    [104,520] (px 208-1040); stores npk=pkt[6..7] into DAT_0002dc18+0x61 counter.
    On dim failure → return 1 (NAK `ff aa`). On success → **return iVar15 which is
    initialized to 2 (line 99) → return 2 = send ACK-echo** (header DOES echo, matches
    AC). So a *valid* header acks; only a bad-dimension header NAKs here.
  - **subop 1 (name data):** `if(counter==0) return 1`; `if(counter-1 != idx) return 1`;
    else store (FUN_0002e288), decrement counter, **return 2 = echo ACK.**
  - **subop 2 (visualizer):** FUN_0002e304, **return 0 = silent** (matches fire-and-forget).
- **KEY: a valid `67 00` header ACKs (return 2); it only NAKs here on bad dims.** Our
  AC-exact header passes all dim checks, yet we saw `ff aa` — so the NAK is emitted
  **UPSTREAM of case 0x67**, i.e. a top-level state gate in FUN_0002330c routes/rejects
  our packet before it reaches FUN_0002d7a0. Prime suspect: `if (DAT_00023700[1] ==
  '\0')` @line 57 (the else-branch = mid-multi-packet-upload data path) and/or a
  music-mode-active flag. THIS is the real gate. Trace the `ff aa` emit site
  (LAB_00024cce / the `caseD_5`→default path) and what state must hold to reach
  case 0x67 with an ack. AC establishes that state in its full session; our replay
  doesn't — matches every earlier observation.

### Session 2 — dispatch internals nailed
- **NAK mechanism CONFIRMED**: `FUN_00024f7c(code)` = `FUN_00024efc(0xff,0xaa,code,0,0)`
  → sends **`ff aa <code>`**. We always got `ff aa 00` = code 0 = the **generic default
  reject** (`switchD_0002346a_default`, uVar22=0). So our `67 00` is NOT reaching its
  own case (which would ACK a valid header) — it's falling into the default path.
- **`7d 20 02` = a capability QUERY** (returns support status, refs `GET_SUPPORT`
  string), NOT a mode-set. `12 12`/`12 14` are likewise queries; `12 00/01/03` are the
  mode switches (they're special-cased at line 64 to NOT reset `*DAT_00023708`).
- **BONUS: factory/debug command set found** (a big switch at ~line 1600, likely under
  cmd 0xfa): ASCII sub-cmds `READ`,`WRITE`,`VERIFY`,`EN_RF`,`EN_PAIR`,`CLEAR`,`LV_RF`
  with error codes 0x15-0x1a. Worth mapping later (RF pairing / flash r/w).
- **Music gate — remaining unknown**: which state makes `67 00` reach case 0x67 vs the
  default reject. `FUN_0002330c` gates on `if (DAT_00023700[1]==0)` @line 57 (else =
  mid-multi-packet-upload path). Strong hypothesis: our repeated *incomplete* uploads
  (header sent, aborted before all data) leave `DAT_00023700[1]!=0` (stuck "expecting N
  more packets"), so the next header is misparsed as continuation data → default reject.
  This static-flow is very messy; **best cracked either dynamically (SWD) or by an
  empirical test**: after a power-cycle, send ONE complete music name upload (header +
  all npk data packets) so the counter reaches 0, and see if it then works — OR just
  find what sets/clears `DAT_00023700[1]` (search its writes).

### Session 2 — BOOTLOADER RECOVERY CONFIRMED
- Bootloader is a separate program (own vtable @0xf3000, reset 0xf34a4 = trampoline to
  fn-ptrs @0xf34c0/c4 → main 0xf4b74, matrix scan 0xf35ec). Had to clearListing +
  set TMode=1 + disassemble to analyze; scripts `azoth_bootasm2.java`, dumps in
  `decomp_boot/`.
- **`FUN_000f35ec` = bootloader key-matrix DFU-entry check.** Scans 7 cols × 14 rows
  (drives GPIO pin=col+9 via OUTSET/OUTCLR@+0x508/+0x50c, reads IN@`*DAT_000f36ec`,
  14-bit mask 0x3fff), debounces into `DAT_000f36fc[0..6]`. Requires EXACTLY:
  `col3 bit9 (0x200) + col4 bit6 (0x40) + col5 bit10 (0x400)`, cols 0/1/2/6 == 0, held
  ~30 iters (cVar7 to 0x1e) → **`return 1` = ENTER DFU**. So **a HARDWARE 3-key combo
  held at plug-in forces the bootloader = no-SWD brick recovery. CONFIRMED it exists.**
- REMAINING: map (col3,row9)/(col4,row6)/(col5,row10) → physical keys via the app's
  matrix→HID keymap table (search app for the scancode LUT). Then we have the exact
  recovery combo, and firmware patching becomes safe-with-recovery.

### Session 2 wrap — status of each roadmap goal
- **Command map** — DONE (folded into `../PROTOCOL.md`): dispatcher `FUN_0002330c`,
  processor `FUN_0002d7a0` (cases 0x61/62/63/64/65/66/67 decoded incl. exact field
  layouts), the 2/1/0 return→ACK/`ff aa`/silent protocol, plus the factory command set.
- **Music gate** — handler fully decoded; **RESULT: no firmware mode-gate on a valid
  `67 00` header** (dims ok → `case 0x67` → return 2 = ACK). But raw debug shows `ff aa`
  for a byte-identical header, which the decompiled path does NOT explain. Unreconciled
  static-vs-observed discrepancy → the last hard nut. `DAT_00023700[1]` = response-in-
  progress flag (not a gate). RESOLUTION NEEDS **dynamic/SWD** (breakpoint the handler)
  OR a very careful re-trace of the messy computed-goto dispatch flow. A cheap probe:
  clean live re-test (kill AC, replug, thorough read-drain, don't match stale ACKs).
- **Bootloader recovery** — RESOLVED: hardware DFU combo = **`Fn + L + B`** held at
  power-on (rear switch in wired position). Matrix wiring proven identical bootloader↔app
  (NO permutation): cols = `P0.(9+col)`; rows = sense bits 0..13; keymap index =
  `layer*98+col*14+row` (`FUN_0002a498`). **KEY FIX: the keymap base is `0x476a3`, NOT
  `0x476a4`** — proven because the 32-bit literal `0x000476a3` occurs exactly once (at
  `DAT_0002a7a8`=`0x2a7a8`) and `0x476a4` never appears. Base `0x476a3` puts Esc at
  (col0,row0) and makes each column a clean physical row. Combo cells (col3 bit9)+(col4
  bit6)+(col5 bit10) therefore = **L + B + Fn**. (Bootloader keymap copy is the same −1
  fix: base `0x0fa4d8` @`0xf3e84`.) ⚠️ An earlier pass used base `0x476a4` and wrongly
  concluded the combo hit an unpopulated cell / was "dead" — that was an off-by-one; the
  combo is real. Software DFU (`FUN_0002a058` GPREGRET+reset) also confirmed as a 2nd path.

### Session 3 (2026-09-07) — MATRIX FULLY REVERSED; recovery combo = Fn+L+B
- **Off-by-one base bug found & fixed** (user caught it): keymap base is `0x476a3` not
  `0x476a4`. Proof: literal `0x000476a3` occurs exactly once in the image (@`0x2a7a8` =
  `DAT_0002a7a8`); `0x476a4` never appears as a literal. Correct base ⇒ Esc at (col0,row0),
  every matrix column = one clean physical keyboard row (leftmost key at row0), and row
  numbers match physical key counting (`;`=col3/row10, `N`=col4/row7). This reverses the
  mid-session "dead combo" conclusion.
- **Hardware DFU combo = `Fn + L + B`** (col3/r9=L, col4/r6=B, col5/r10=Fn) held at
  power-on with rear switch wired. Confirmed by both app keymap (@0x476a3) and bootloader
  keymap (@0x0fa4d8), which agree.
- **Fn is code-driven** (`FUN_0002c19c`): Fn+1..6=profiles(I-V/Default), Fn+F12=remappable
  slot, Fn+Esc=Reset, Fn+Tab=PC/Mac, Fn+P=PrtSc, Fn+Ins/Del/PgUp/PgDn=Pause/ScrlLk/Home/
  End, Fn+Win=Lock, Fn+LAlt=Macro, Fn+RCtrl=Menu, Fn+arrows=light. Dumps in `decomp_fn/`.

### (superseded) Session 3 first pass — reached wrong "combo dead" via base 0x476a4
- Read the app key scanner chain: `FUN_0002a498` (keymap consumer, index
  `layer*0x62 + col*0xe + row`), `FUN_0002b0b8` (matrix scan loop, col pins mask `0xfe00`
  = P0.9-15, row discharge `0x3fff`), `FUN_000432a4` (col drive = `OUTSET 0x200<<col`),
  `FUN_000f37c0` (bootloader rear-switch gate = P0.IN bits 14/15).
- **Proved NO col/row permutation** between bootloader raw-GPIO scan and app keymap — same
  pins, same order, same direction. Keymap @0x476a4 validated against user's physical
  layout (P stays P across all 6 profile copies; the 98-byte stride = 6 profiles, not the
  Fn overlay — Fn layer is stored/computed elsewhere).
- **Combo = `;` + `N` + (col5,row10)=0x00**. User confirms no pairing button exists ⇒
  (col5,row10) has no switch ⇒ **hardware DFU combo unreachable**. Corrected PROTOCOL.md
  and the Session 2 "combo exists" claim. Recovery now understood as **software-DFU-only**.
- New scripts: `ghidra_scripts/azoth_colscan.java`; dumps in `decomp_scan/col_*.c`,
  `decomp_boot/bl_0f37c0.c`. Keymap validator extended in `keymap.py`.

### Remaining follow-ups (all well-defined)
1. **Music**: dynamic (SWD) breakpoint on `FUN_0002d7a0`/the reject site to see why our
   header NAKs; or careful static re-trace of the `0x67` path through the computed gotos.
2. **Recovery keys**: ✅ DONE — combo = **`Fn + L + B`** at power-on (rear switch wired).
   Keymap base corrected to `0x476a3` (was off-by-one). Combo is real & user-triggerable.
   Nice-to-have backstop: verify whether the nRF bootloader **also auto-stays in DFU on
   app-validation failure** (CRC/vector check in the `0xf4b74` main path) — a 3rd recovery
   path. Not blocking, since Fn+L+B already recovers a dead app.
3. Decode remaining opcodes fully (0x71/0x72 per-key, 0xc0 stream, 0xfa/0xfc RGB, the
   0xfa factory sub-cmds) for a 100% command map.
2. **Full command map** — from FUN_0002330c + FUN_0002d7a0, document every opcode/sub-op
   + field layout into PROTOCOL.md (0x50,0x61,0x62,0x63,0x64,0x66,0x67,0x69,0x71,0x72,
   0x7d,0xc0,0xfa,0xfc + the 0x12/0x21/0x22 group).
3. **Music gate** — resolve `DAT_00023700[1]` writers (what sets/clears it).
1. **Music gate**: read `decomp/02330c_FUN_0002330c.c` around the `switch(pkt[1])`
   case 0x13 (~line 311) — what state var / DAT_ is checked before `67 00` is accepted
   vs `0xaa`. That's the answer to why our `music` command NAKs.
2. **Brick-recovery combo**: force Ghidra to disassemble the bootloader from its
   vector table @0xf3000 (script: DisassembleThumb at reset 0xf34a4 + create fn), then
   decompile the P1.IN key-check → which physical key(s) force DFU. Confirms a no-SWD
   recovery path (de-risks any future patching).
3. Map the full command dispatch in `FUN_0002330c` → every opcode/sub-op → PROTOCOL.md.
