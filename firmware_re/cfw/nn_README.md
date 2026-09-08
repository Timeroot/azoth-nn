# Char next-key predictor v2 — ROG Azoth (nRF52840 / Cortex-M4F @ 64 MHz)

A character-level next-key neural net running on the keyboard MCU. It reads the
live HID report, keeps a recurrent hidden state across keystrokes, and shows the
top-3 predicted symbols on the OLED. v2 adds a **32-symbol vocab** (capitals via a
caret escape + punctuation), a **distilled** GRU trained from a large LSTM teacher,
and a full architecture / quantization / pruning study.

## TL;DR — final model

| | value |
|---|---|
| architecture | **single-layer GRU, H=256, E=96, input→output skip** |
| vocab | 32 symbols (a–z, space, `'` `.` `,` `-`, `^`=capital-escape) |
| training | hard-CE + **distillation** (teacher = 3-layer LSTM H512), T=1.5 α=0.7, 28k steps |
| quantization | int8 per-output-row symmetric (embedding + biases float32) |
| **float** held-out | ppl **3.127**, top-1 **64.07%**, top-3 **83.19%** |
| **int8** held-out | ppl **3.146**, top-1 **64.10%**, top-3 **83.22%** (quantization ~lossless) |
| params on flash | **306,432 B = 299.2 KB** (≤ 500 KB) |
| recurrent state | **256 float32 = 1024 B** (= the 1 KB budget) |
| transient scratch | 6,144 B at 0x2003b000 (≤ 16 KB) |
| MAC / keystroke step | **281,600** (≤ 1.5 M budget) |
| nn.c code size | 1,640 B, compiles clean with the required flags |

Baseline to beat (v1, 27-vocab): float ppl 3.07 / top-1 64.3% / top-3 83.3%. v2
targets a **harder 32-symbol task** (now predicts capitalization + punctuation);
see "vocab expansion" below for the apples-to-apples cost.

---

## 1. Vocabulary & preprocessing (V=32)

| id | sym | id | sym | id | sym |
|----|-----|----|-----|----|-----|
| 0–25 | a–z | 26 | space | 27 | `'` apostrophe |
| 28 | `.` period | 29 | `,` comma | 30 | `-` dash |
| 31 | `^` **capital escape** | | | | |

`^` is emitted **immediately before** an originally-uppercase letter:
`"I'm hungry, Mom!"` → `^i'm hungry, ^mom.`

Preprocessing (`nn_common.preprocess`, applied to corpus **and** to on-device input):
1. Normalize Unicode punctuation: curly quotes `’‘` → `'`; `“”«»` → space;
   em/en dashes `—–` → space; ellipsis `…` → `.`; nbsp → space.
2. Each `A–Z` → `^` + lowercase.
3. `!` and `?` → `.`
4. Any run of remaining non-alphabet chars (whitespace, digits, other punct) →
   a single space; collapse repeated spaces.

Corpus symbol mix (16.86 M symbols): space 17.9%, `^` 1.95%, `,` 1.42%, `.` 1.01%,
`'` 0.20%, `-` 0.12% (rest letters). Corpus = Pride & Prejudice + 19 Gutenberg
works (`nn_fetch_corpus.py` → `corpus_big.txt`), mixed genres.

## On-device INPUT mapping (HID report → symbol stream)  — implemented in nn.c

`RPT[]` = live u16 keycode array @`0x2000b6f8`, count @`0x20003370` (as in gru.c).

- **Shift held** = keycode `0xe1` (LShift) or `0xe5` (RShift) present in the report.
- **Main key** = first non-modifier (`<0xe0` or `>0xe7`) keycode `>= 0x04`.
- Mapping (`map_key`), emitting 1–2 symbols per keystroke:

| keycode | unshifted | + Shift |
|---------|-----------|---------|
| `0x04–0x1d` (a–z) | letter | **`^` then letter** |
| `0x2c` space / `0x28` enter | space | space |
| `0x34` `'` | `'` | `"` → space |
| `0x37` `.` | `.` | `>` → space |
| `0x36` `,` | `,` | `<` → space |
| `0x2d` `-` | `-` | `_` → space |
| `0x1e` `1` | space | `!` → `.` |
| `0x38` `/` | space | `?` → `.` |
| anything else | space | space |

Edge-detect token = `(shift<<16)|keycode` stored in `M[1]`; a symbol stream is
emitted only when the token changes (repeats/held keys suppressed; runs of
"other" keys collapse to one space). Key-up (empty report) resets the token so
double letters work.

## Display glyphs

`FONT[32][8]` extends gru.c's 27 glyphs with 5 new 8×8 bitmaps: `'` (upper tick),
`.` (low dot), `,` (low dot+tail), `-` (mid bar), `^` (up-chevron). Predictions and
the last-typed context char render with the same `draw_char` routine/scaling.

---

## 2. Architecture search (5000 steps, hard-label, new vocab)

All fit ≤500 KB flash & ≤1.5 M MAC; `st`=recurrent floats (must be ≤256 = 1 KB).

| config | float ppl | f-t1 | f-t3 | int8 ppl | q-t1 | q-t3 | KB | st | MACk |
|--------|----------:|-----:|-----:|---------:|-----:|-----:|---:|---:|-----:|
| **gru L1 H256 E96** | 3.234 | .633 | .828 | 3.267 | .632 | .825 | 296 | 256 | 278 |
| gru L1 H256 E96 **skip** | 3.240¹ | .634 | .827 | 3.267 | .632 | .826 | 270 | 256 | 256 |
| gru L1 H256 E64 | 3.237 | .633 | .827 | 3.269 | .632 | .825 | 268 | 256 | 253 |
| gru L2 H128 E64 | 3.312 | .627 | .824 | 3.351 | .625 | .822 | 192 | 256 | 176 |
| gru L2 H128 E96 skip | 3.321 | .625 | .822 | 3.354 | .624 | .822 | 211 | 256 | 191 |
| lstm L1 H128 E64 | 3.612 | .605 | .810 | 3.648 | .602 | .810 | 116 | 256 | 102 |

¹ skip's E64 5k run; at the final 28k-step budget H256+E96+skip is the winner.

**Findings.** The **1 KB recurrent-state cap is the binding constraint**, not flash or
compute — so the widest single-layer state (H=256) wins. Splitting the 256-float
budget into 2 layers (128+128) is consistently ~0.08 ppl worse; LSTM (H≤128 to fit
h+c in 256) is much worse. Bigger embedding (E64→96) and the input→output skip give
small but positive top-1 gains and spend spare flash usefully. **Chosen: GRU L1
H256 E96 + skip.**

## 3. Distillation (teacher → student, same student size, 7000 steps)

Teacher = **3-layer LSTM H512 E96, 5.47 M params**, held-out ppl **2.772** /
top-1 **67.7%** / top-3 **85.5%**. Student trained with
`loss = α·T²·KL(softmax(s/T)‖softmax(teacher/T)) + (1−α)·CE(s, hard)`.

| student objective | float ppl | top-1 | top-3 |
|-------------------|----------:|------:|------:|
| hard-label (α=0) | 3.209 | .6356 | .8283 |
| T2.0 α0.3 | 3.207 | .6334 | .8278 |
| T2.0 α0.5 | 3.208 | .6332 | .8277 |
| T4.0 α0.5 | 3.263 | .6271 | .8249 |
| **T1.5 α0.7** | **3.191** | .6354 | **.8287** |
| T3.0 α0.3 | 3.224 | .6306 | .8269 |

**Finding.** With 16 M training symbols the student is not data-starved, so
distillation gives only a **modest** win — and **only at low temperature**. High
T (≥3) over-softens and *hurts* (the softened target diverges from hard-label CE).
Sharp targets (**T=1.5, α=0.7**) beat hard-label by **−0.018 ppl / +0.0004 top-3**
at equal steps. The final model uses T=1.5 α=0.7 and trains 28k steps → ppl 3.127.

## 4. Pruning (magnitude, post-hoc, no retrain) — recurrent matrices

| row-sparsity | ppl | top-1 | top-3 |
|-------------:|----:|------:|------:|
| 0.00 | 3.163 | .640 | .832 |
| 0.30 | 3.656 | .592 | .806 |
| 0.50 | 5.525 | .487 | .727 |
| 0.70 | 11.94 | .334 | .597 |

**Finding.** The GRU uses its recurrent weights **densely**: even 30% sparsity
collapses accuracy. A CSR/sparse int8 forward is **not worth** the code complexity
or the accuracy hit — and flash isn't the bottleneck anyway. **Ship dense int8.**

## 5. Quantization: int8 vs int4 (recurrent matrices)

| scheme | ppl | top-1 | top-3 | on-flash |
|--------|----:|------:|------:|---------:|
| **int8** (per-row) | 3.146 | .6410 | .8322 | 299 KB |
| int4 (per-row, nibble-packed) | 3.578 | .5998 | .8109 | 167 KB |

**Finding.** int8 per-output-row is **effectively lossless** (quant ppl 3.146 vs
float 3.127 — within eval noise, top-1 unchanged). int4 saves 132 KB but costs
~4 pts top-1; since we're **state-bound, not flash-bound**, int4 buys nothing we
need. **Ship int8.**

---

## Quantization scheme (deployed)

- **int8, per-output-row symmetric.** For each weight row `o`:
  `scale[o]=max_i|W[o,i]|/127`, `q[o,i]=round(W[o,i]/scale[o])∈[-127,127]`,
  scales stored float32.
- Quantized: `Wih`[3H,E], `Whh`[3H,H], `out`[V,H+E]. **Embedding float32** (input
  table, only 12 KB, avoids input-side quant error). Biases float32.
- On-device linear: `acc = Σ_i (float)w_int8[i]·x_float[i];  out = acc·scale + bias`.

## GRU math (matches torch `nn.GRU`, gate row order r,z,n)

```
r = σ(Wir·x+bir + Whr·h+bhr)
z = σ(Wiz·x+biz + Whz·h+bhz)
n = tanh(Win·x+bin + r·(Whn·h+bhn))
h'= (1−z)·n + z·h
logits = Wout·[h ; emb(last_sym)] + bout     # input→output skip
```
`tanh`/`σ` = clamped **Padé(7,7)**, libm-free; identical formula/constants in
`nn.c` (`tanhf_`) and `nn_common.tanh_pade`.

## Flash layout — `nn_weights.bin` @ 0x50000 (306,432 B, offsets in nn_weights.h)

int8 blocks first (each 4-byte-padded), then float32 blocks:

| tensor | dtype | shape | offset | bytes |
|--------|-------|-------|-------:|------:|
| Wih0 | int8 | [768,96] | 0 | 73,728 |
| Whh0 | int8 | [768,256] | 73,728 | 196,608 |
| out | int8 | [32,352] | 270,336 | 11,264 |
| EMB | f32 | [32,96] | 281,600 | 12,288 |
| Wih0_scale | f32 | [768] | 293,888 | 3,072 |
| Whh0_scale | f32 | [768] | 296,960 | 3,072 |
| out_scale | f32 | [32] | 300,032 | 128 |
| Bih0 | f32 | [768] | 300,160 | 3,072 |
| Bhh0 | f32 | [768] | 303,232 | 3,072 |
| Bout | f32 | [32] | 306,304 | 128 |

int8 = 281,600 B; float32 = 6,208 floats = 24,832 B; total **306,432 B**.

## RAM layout

| region | address | size | contents |
|--------|---------|------|----------|
| `M` metadata | 0x2003f000 | 12 B | magic, last_token, display sym |
| `PREDS` | 0x2003f00c | 3 B | top-3 predicted symbols |
| **persistent `HID`** | 0x2003f100 | **1024 B** | GRU hidden state h[256] f32 |
| scratch `GI` | 0x2003b000 | 3072 B | input-side gate acc [3H] |
| scratch `GH` | 0x2003bc00 | 3072 B | hidden-side gate acc [3H] |

Persistent recurrent state = **256 float32 = 1024 B = exactly the 1 KB budget**.
Scratch = 6144 B ≤ 16 KB, at fixed addresses above 0x2003a878, below the state.
No large stack arrays.

## Compute / step

`3·H·E + 3·H·H + V·(H+E) = 73,728 + 196,608 + 11,264 = 281,600 MAC` — dominated by
the H×H recurrent matmul; ~1/5 of the 1.5 M budget. int8-load→f32→fma at a few
cycles ≈ ~1 M cycles ≈ ~16 ms, well inside the ~100 ms+ between keystrokes.

## Deltas vs baseline

- **Vocab expansion (27→32), same regime (H256, 15k, hard-label):** old-vocab
  3.066 / .643 / .833 → new-vocab 3.161 / .640 / .831. Cost ≈ **+0.095 ppl,
  −0.3 pt top-1** to gain capitalization + 5 punctuation symbols. (ppls are over
  different alphabets, so not strictly comparable — the model now solves a
  strictly harder prediction problem.)
- **Distillation, same student & 7k steps:** hard 3.209 → **T1.5α0.7 3.191**
  (−0.018 ppl, top-3 +0.0004, top-1 tied).
- **Longer training + distillation (final, 28k):** **ppl 3.127 / top-1 64.07% /
  top-3 83.19%** float; **3.146 / 64.10% / 83.22%** int8.

## Files

- `nn_fetch_corpus.py` → `corpus_big.txt` (16.86 M symbols, 20 works).
- `nn_common.py` — vocab/preprocessing, int8/int4 quant, int8×float forward,
  Padé tanh/σ, pack/load. Shared by trainer & reference.
- `nn_train.py` — full pipeline: `--sweep` (arch search), `--train_teacher`,
  `--distill` (KD+CE), `--export`. Final:
  `--arch gru --layers 1 --H 256 --E 96 --out_skip --distill --T 1.5 --alpha 0.7
  --steps 28000 --export`.
- `nn_distill_sweep.py` — the (T,α) tuning above. `nn_analyze.py` — pruning sweep.
  `nn_intbits.py` — int8-vs-int4. Metrics saved to `nn_*_.json`.
- `nn.c` — on-device HID input mapping + forward + `render()`; reads weights from
  flash 0x50000; same STRIDE/DIRTY/RPT/RPTCNT/draw contract as gru.c.
- `nn_weights.bin` (flash blob) / `nn_weights.h` (dims+offsets) /
  `nn_manifest.json` (machine-readable layout).
- `nn_ref.py` — bit-close reference; prints top-3 for prefixes incl. capitals/
  punctuation (`^the `, `i'm`, `hello^`, `dr^`, `u.s^`, `^new ^yor`, …).
- `nn_teacher.pt` — the distillation teacher (for reproducibility).

## Reference ↔ device agreement

`nn_ref.py` and `nn.c` use identical math: same Padé tanh/σ, same per-row dequant,
same input→output skip, and `nn_common.lin_q` accumulates **sequentially over the
inner index k** exactly like nn.c's `for(k) a += (float)w[k]*x[k]`. Only possible
diff = FPU fma contraction (~1e-6). Smallest top3/top4 logit margin across the test
prefixes is 0.014 — ~100× the noise — so on-device top-3 matches the reference.

Build check (does **not** flash; operator flashes hardware):
```
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp \
  -Os -ffreestanding -fno-builtin -nostdlib -c nn.c
```
Compiles clean → 1640 B of code, 0 B bss.

Reproducible: seeds fixed (`torch.manual_seed`, `numpy` seeds) throughout.
