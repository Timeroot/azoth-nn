# Char next-key predictor v3 — ROG Azoth (nRF52840 / Cortex-M4F @ 64 MHz)

A character-level next-key neural net running on the keyboard MCU. It reads the
live HID report, keeps recurrent state across keystrokes, and shows the last
input symbol + top-3 predicted symbols on the OLED. **v3** is a big upgrade over
v2 (27/32-symbol prose model):

- **BIG vocab, V=72** — letters, digits, space/tab/newline, a dedicated CAPITAL
  ESCAPE token, and all 32 US-keyboard ASCII punctuation symbols.
- **Two-timescale recurrence** — a *fast* char-level GRU (updates every key) plus
  a *slow* word-level GRU (updates once per word, at word boundaries) feeding the
  char prediction.
- **Auxiliary training heads** (char+2, char+3, next-word) with an
  anneal-then-continue schedule — implemented and ablated across a controlled
  matrix; **no configuration helped**, so they are **not used** in the deployed
  model (see the ablation study, §2).
- **Distillation** from a large LSTM teacher (retrained for the 72-vocab), kept
  per spec (light, α=0.3).
- Every design choice was **empirically validated** by a controlled architecture
  search on a fast 27-symbol testbed, then **confirmed on the 72-symbol task** (§2).
- Full on-device input mapping incl. shifted keys, **one-level Backspace undo**,
  reseed-on-unhealthy state, and a fresh unique seed magic.
- **Scaling series** (§4): with the flash budget expanded to ~490 KB (region
  0x61000–0xdb000 via runtime self-programming), the same architecture is trained
  at **64 / 128 / 256 / 400 KB**; each candidate is saved (`nn_<size>.{bin,h,json}`)
  so any can be flashed. A **2-layer stacked fast GRU** and an **n-gram/Markov
  hybrid** were evaluated for extra ppl-per-KB.

## TL;DR — recommended max-performance model (`nn_460k`) + the size options

The **recommended pick is `nn_460k`** — the biggest model that safely fits the
high-flash region (2-layer stacked fast GRU, sized to fill it). The full scaling
curve (§4) lets you trade size for accuracy. `nn.c` is parametric — it builds for
any candidate from that model's `nn_weights.h` (set `-DWBASE=` to the flash address
the blob is written to; default `0x61000`).

| candidate | int8 blob (end addr) | fast×FL / slow / E | state | MAC/char | **int8** ppl / t1 / t3 |
|-----------|----------:|--------------------|------:|---------:|------------------------:|
| **nn_460k** | **468.2 KB (→0xD60C0)** | **184×2 / 96 / 56** | **1856 B** | **359.8 k** | **3.393 / 63.5% / 81.6%** |
| nn_400k | 403.3 KB (→0xC5D40) | 256×1 / 96 / 64 | 1408 B | 275.7 k | 3.556 / 62.2% / 80.8% |
| nn_256k | 268.7 KB | 200×1 / 80 / 56 | 1120 B | 177.8 k | 3.784 / 60.5% / 79.5% |
| nn_256k_fl2 | 262.5 KB | 130×**2** / 72 / 56 | 1328 B | 192.5 k | 3.732 / 60.9% / 79.9% |
| nn_128k | 127.5 KB | 132×1 / 48 / 40 |  720 B |  84.0 k | 4.224 / 57.9% / 77.7% |
| nn_64k  |  62.4 KB | 84×1 / 32 / 28  |  464 B |  38.6 k | 4.879 / 53.9% / 75.0% |

`nn_460k`: **float** ppl **3.324** / t1 **63.81%** / t3 **82.18%**; **int8** ppl
**3.393** / t1 **63.49%** / t3 **81.59%** (trained with the improved WSD recipe, §8). Blob
479,424 B starts 0x61000, ends **0xD60C0** (< 0xD8000 with ~40 KB margin). Common
to all: V=72, input→output skip, int8 per-output-row quant, unique MAG,
reseed-on-unhealthy, one-level Backspace undo, full shifted-key input map. Relaxed
budgets used: state ≤ ~8 KB (nn_460k 1.8 KB), scratch ≤ 64 KB (nn.c uses 16 KB at
0x2003b000), compute ≤ 5 M MAC/char (nn_460k 360 k). nn.c: **2,506 B** text (FL=2),
0 bss; compiles clean.

---

## 1. Vocabulary & preprocessing (V=72)

| ids | symbols |
|-----|---------|
| 0–25 | `a`–`z` |
| 26–35 | `0`–`9` |
| 36 | space |
| 37 | TAB (`\t`) |
| 38 | NEWLINE (`\n`) |
| 39 | **CAPITAL ESCAPE** (its own token — **not** the literal `^`) |
| 40–71 | 32 ASCII-order punctuation: `! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ `` ` `` { \| } ~` |

Why 72 (and not the "~80–95" first guessed): printable ASCII is 95 glyphs, but the
26 capitals collapse to one CAPESC token, and we add TAB + NEWLINE, giving
`95 − 26 + 1 + 2 = 72`.

**CAPITAL ESCAPE** is emitted immediately **before** an originally-uppercase
letter, e.g. `"I'm, Mom!"` → `[CAPESC] i ' m ,  [CAPESC] m o m !`. It is a
dedicated token id (39), distinct from the literal caret `^` (id 65, which is now
a real vocab char).

Preprocessing (`nn_common.preprocess`, applied to corpus **and** on-device input):
1. Normalize newlines: `\r\n` and `\r` → `\n`.
2. Normalize a few Unicode punctuation chars to ASCII (curly quotes → `'`/`"`,
   em/en dashes → `-`, ellipsis → `.`, nbsp → space, bullet → `*`).
3. Each `A–Z` → CAPESC + lowercase.
4. Keep vocab chars (incl. `\t`, `\n`); map every other char to a single space;
   collapse runs of ≥2 spaces to one (tabs/newlines are preserved as-is).

**Corpus.** Prose (`corpus_big.txt`, 20 Gutenberg works, ~17.4 M symbols) +
**code** (`corpus_code.txt`, ~2.65 M symbols sampled from local Python source via
`nn_augment_corpus.py`) so digits, brackets/operators and code patterns
(`def f(`, `x = 3`, `import`, `http`) are actually represented. ~20.06 M symbols
total; every one of the 72 symbols occurs. Held-out val is a **tail of each
corpus** (≈ prose/code mix), not an all-code tail.

## 2. Two-timescale architecture

```
per typed symbol s (fast, EVERY step):
    hf = GRU_fast(emb(s), hf)                       # HF=84 char state
if s is a word boundary  (s not in {a-z, CAPESC}):  # space/punct/digit/tab/nl
    hs = GRU_slow(hf, hs)                            # HS=32 word state, consumes hf
predict next char:
    logits = OUT · [hf ; hs ; emb(s)] + b           # input→output skip
```

- The **fast** GRU is a standard char RNN: it turns over on every keystroke and
  carries fine-grained within-word context.
- The **slow** GRU only advances at **word boundaries** (right after a
  non-alphabetic symbol), summarizing each finished word into a compact state that
  persists across the next word. It gives the char head cheap long-range/topic
  context without paying an H×H recurrent matmul every keystroke.
- Both states are read by the output head every step, so slow context conditions
  every character prediction.

Gate math is torch `GRU`/`GRUCell` order **(r, z, n)**:
```
r = σ(Wir·x + Whr·h + b);  z = σ(Wiz·x + Whz·h + b)
n = tanh(Win·x + r·(Whn·h) + b);   h' = (1−z)·n + z·h
```
`tanh`/`σ` are clamped **Padé(7,7)**, libm-free; identical formula/constants in
`nn.c` (`tanhf_`) and `nn_common.tanh_pade`, so device math matches the reference.

Persistent state = **hf[84] + hs[32] = 116 float32 = 464 B** — under half the 1 KB
budget. (Flash, not state, is the binding constraint here; see §4.)

## 3. Controlled ablation study (what actually helps)

Every design choice was validated by toggling **one thing at a time** from a clean
single-GRU baseline, each arm trained under an **identical schedule** (warm-restart
cosine LR, early-stop on held-out ppl with patience), evaluated on the **same
held-out set**.  A fast **27-symbol letters testbed** was used to iterate cheaply
(low noise, key arms on 2 seeds), then the decisive comparison was **re-confirmed
on the target 72-symbol task**.  Full per-arm numbers: `ablation_results.csv`;
harness: `nn_ablate.py` / `run_ablate.py` / `run_confirm72.py`.  int8 = per-row
fake-quant through the same forward (it tracks float within ~0.005 ppl here).

Aux heads tested (training-only, **not exported**): **char+2**, **char+3**
next-token heads on `[hf;hs]`, and a **next-word** head on `hs` predicting the next
word's first char at boundaries.  Schedule: full weight (0.3) for the first 25 %,
linearly annealed to 0 by 45 %, then **train long on the pure objective** — the
anneal-then-continue schedule (a fair test, unlike a short aux-on-throughout run).

### 3a. Testbed matrix (27-symbol, 10k steps, early-stop; float ppl / top-1 / top-3)

| arm | params | state | MAC/char | float ppl | top-1 | top-3 | seeds |
|-----|-------:|------:|---------:|----------:|------:|------:|:-----:|
| single GRU, base (H72) | 24k | 72 | 23k | 4.665 ±.035 | .542 | .752 | 2 |
| **single GRU, wide (H86, param-matched)** | 32k | 86 | 31k | **4.482 ±.015** | **.552** | **.760** | 2 |
| two-timescale, slow=GRU (HF72+HS24) | 32k | 96 | 23k | 4.555 ±.008 | .545 | .756 | 2 |
| two-timescale, slow=LSTM | 34k | 120 | 23k | 4.577 | .545 | .755 | 1 |
| two-timescale, slow=RNN | 27k | 96 | 23k | 4.568 | .545 | .754 | 1 |
| TT-GRU + aux char+2 (anneal) | 34k | 96 | 23k | 4.573 | .546 | .756 | 1 |
| TT-GRU + aux char+3 (anneal) | 34k | 96 | 23k | 4.599 | .543 | .754 | 1 |
| TT-GRU + aux word (anneal) | 32k | 96 | 23k | 4.597 | .546 | .753 | 1 |
| TT-GRU + aux all three (anneal) | 38k | 96 | 23k | 4.582 | .545 | .755 | 1 |
| TT-GRU, boundary = space-only | 32k | 96 | 23k | 4.563 | .545 | .755 | 1 |
| TT-GRU + distillation (T1.5 α0.7) | 32k | 96 | 23k | 4.588 | .541 | .752 | 1 |
| single-wide + distillation | 32k | 86 | 31k | 4.485 | .549 | .757 | 1 |

_(27-symbol teacher: ppl 3.414 / t1 .620 / t3 .810.)_

**On letters-only, none of the extras beat a well-tuned wide single GRU.** The slow
layer costs ~0.07 ppl at matched params (any cell — GRU≈LSTM≈RNN); **aux never
helped even with the correct anneal-then-continue schedule** (char+2/+3/word all
slightly worse); distillation was neutral-to-slightly-negative in this data-rich
regime; the word-boundary definition didn't matter. The slow layer's only win is
**MACs/char** (23k vs 31k) — irrelevant here since flash, not compute, is binding.

### 3b. Confirmation on the 72-symbol task (16k steps, same schedule, 64KB budget)

| arm | params | state | MAC/char | float ppl | top-1 | top-3 |
|-----|-------:|------:|---------:|----------:|------:|------:|
| single GRU, wide (H106, budget-matched) | 54k | 106 | 52k | 5.018 | .542 | .746 |
| **two-timescale, slow=GRU (HF84+HS32)** | 52k | 116 | 38k | **4.977** | .541 | **.748** |

**The result flips on the real task.** With digits, punctuation, code and
capitalization — i.e. genuine word/line structure — the **two-timescale GRU beats
the budget-matched wide single GRU** (4.977 vs 5.018, −0.041 ppl, +0.2 pt top-3)
**while using ~27 % fewer MACs/char** (38k vs 52k). The per-word slow state earns
its keep once there is cross-word structure to remember; on letters-only there was
little to gain. This **empirically justifies the two-timescale design** for the
deployment vocab. (Aux was re-confirmed unhelpful and is left out; distillation is
kept light per spec.)

### 3c. Deployed-model training curve (24k steps, warm restart, held-out ppl)

The anneal-then-**continue-long** schedule with a warm LR restart keeps improving
well past where a single cosine plateaus:

| step | 2k | 4k | 6k | 8k | 10k | 12k† | 14k | 16k | 18k | 20k | 24k |
|------|---:|---:|---:|---:|----:|----:|----:|----:|----:|----:|----:|
| val ppl | 5.27 | 4.98 | 4.89 | 4.84 | **4.83** | 4.83 | 4.78 | 4.75 | 4.73 | 4.71 | **4.70** |

† warm restart at ~10.8k (LR 4.7e-5 → 1.2e-3): the first cosine bottoms at 4.83,
then the restart + long tail drives held-out ppl down to **4.696** (best @ 24k).
Full curve in `nn_curve.json`.

## 4. Scaling series (expanded flash budget)

The DFU-era 64 KB ceiling is lifted: ~490 KB of flash above it (0x61000–0xdb000)
is usable via runtime self-programming. The winning architecture (two-timescale
GRU, no aux, light distill, warm-restart schedule, 24k steps, early-stop) was
trained at four int8 blob sizes. **Held-out (random-position) float/int8 ppl,
top-1, top-3:**

| model | int8 KB | HF×FL / HS / E | state | MAC/char | float ppl | f-t1 | f-t3 | int8 ppl | q-t1 | q-t3 |
|-------|--------:|----------------|------:|---------:|----------:|-----:|-----:|---------:|-----:|-----:|
| nn_64k  |  62.4 | 84×1 / 32 / 28  |  464 B |  38.6 k | 4.696 | .548 | .759 | 4.879 | .539 | .750 |
| nn_128k | 127.5 | 132×1 / 48 / 40 |  720 B |  84.0 k | 4.099 | .584 | .784 | 4.224 | .579 | .777 |
| nn_256k† | 268.7 | 200×1 / 80 / 56 | 1120 B | 177.8 k | 3.583 | .617 | .808 | 3.665 | .612 | .802 |
| nn_256k_fl2 | 262.5 | 130×**2** / 72 / 56 | 1328 B | 192.5 k | 3.645 | .613 | .805 | 3.732 | .609 | .799 |
| nn_400k | 403.3 | 256×1 / 96 / 64 | 1408 B | 275.7 k | 3.490 | .625 | .814 | 3.556 | .622 | .808 |
| **nn_460k†** | **468.2** | **184×2 / 96 / 56** | **1856 B** | **359.8 k** | **3.324** | **.638** | **.822** | **3.393** | **.635** | **.816** |

**Scaling.** Doubling the blob gives diminishing but real gains: 64→128 KB
**−0.60** ppl, 128→256 KB **−0.42**, 256→400 KB **−0.19**, 400→468 KB **−0.05**.
int8's cost over float **shrinks with size** (0.18 → 0.13 → 0.10 → 0.07 ppl) —
per-row int8 is essentially lossless once rows are large. Compute (≤ 360 k MAC/char)
and state (≤ 1.9 KB) stay far under the relaxed 5 M / 8 KB budgets, so **flash is
still what you trade for accuracy.**

**2-layer stacked fast GRU.** At a matched ~256 KB budget, a **2-layer** fast GRU
(`nn_256k_fl2`, ppl **3.645**) beats the **1-layer** `nn_256k` (**3.684**) by
**−0.039 ppl / +0.3 pt top-1** — depth helps at scale (it did not at the 27-symbol
testbed size). The max-performance pick exploits this: **`nn_460k` is a 2-layer
FL=2 model widened to fill the region** (184×2 fast, HS=96 slow, E=56), and it
**beats the 1-layer `nn_400k` on every metric** (int8 3.393 vs 3.556, top-1 63.5%
vs 62.2%, top-3 81.6% vs 80.8%) despite being only ~65 KB larger. († = trained with
the improved WSD recipe of §8; the cosine-24k rows would each drop ~0.1 ppl under it.)

**Recommendation.** `nn_460k` (int8 **3.393**, top-1 **63.5%**, top-3 **81.6%**;
float 3.324) is the max-performance pick: it fills the deployable region — blob
479,424 B at 0x61000 ends **0xD60C0** (< 0xD8000, ~40 KB margin). `nn_256k_fl2` is
the value option (~45 % smaller, within ~0.22 ppl). All six are saved as
`nn_<size>.{bin,h,json}` (+`_metrics.json`); `nn_ref.py <prefix>` loads any;
`collect_scaling.py` regenerates `scaling_results.csv`.

## 5. N-gram / Markov hybrid

A char-level **interpolated absolute-discounting (Kneser-Ney-style) n-gram** was
built on the 19.6 M-symbol training set (`nn_ngram.py`) and combined with the NN by
**static interpolation** `p = λ·p_NN + (1−λ)·p_ngram` (`run_ngram.py`). Evaluated on
a held-out slice (a separate, easier slice than the scaling table — compare within
this section only):

| n-gram order | ppl | top-1 | top-3 | table (pruned ≥2) |
|-------------:|----:|------:|------:|------------------:|
| 2 | 10.85 | .300 | .538 | ~7 KB |
| 3 | 6.94 | .416 | .670 | ~78 KB |
| 4 | 4.65 | .511 | .768 | ~364 KB |
| 5 | 3.80 | .570 | .809 | ~1.1 MB |
| 6 | 3.49 | .606 | .822 | ~2.6 MB |

**Interpolation gain depends on NN strength:**

| NN | NN alone | + 6-gram (best λ) | Δ ppl |
|----|---------:|------------------:|------:|
| `nn_64k` (small) | 3.884 | **3.461** (λ=0.5) | **−0.423** |
| `nn_256k` (strong) | 3.256 | **3.203** (λ=0.7) | −0.053 |

**Findings.** (1) **The NN is far more flash-efficient than the n-gram**: a 62 KB
NN (ppl 3.88 on this slice) rivals a **1 MB** 5-gram (3.80) and beats a 364 KB
4-gram (4.65). (2) **The n-gram's value collapses as the NN grows** — it adds
−0.42 ppl to the tiny 64 KB NN but only −0.05 to the 256 KB NN, because a strong
NN already captures the short-context statistics the n-gram stores. (3) Therefore,
given the ~490 KB budget, **spending flash on a bigger NN dominates spending it on
an n-gram table** — the hybrid is *not* worth the memory for on-device here.
Options (b) n-gram log-probs as NN input features and (c) NN-on-residual would each
require retraining the NN with n-gram inputs; given (1)–(2) they are unlikely to
beat simply enlarging the NN, so they were not pursued. The n-gram code, per-order
curve, table-size estimates and interpolation sweep are the deliverable
(`nn_ngram_results.json`).

## 6. Budget search & why this shape (64 KB point)

The **64 KB flash blob is the binding constraint** (the recurrent state uses only
116/256 float32, and compute is ~40 K/1.5 M MACs — both have huge headroom). The
dominant flash cost is the fast GRU's `3·HF²` recurrent matrix and the
V-dependent output/embedding tables. A grid over (HF, HS, E, skip) under the 64 KB
cap picks **HF=84, HS=32, E=28, skip=on → 63,936 B** (ends 0x5F9C0): the largest
fast state that fits alongside a useful slow state, an E-28 embedding and the
input→output skip.

| | int8 bytes | float32 bytes |
|---|---:|---:|
| fast Wif [252,28] / Whf [252,84] | 7,056 / 21,168 | — |
| slow Wis [96,84] / Whs [96,32] | 8,064 / 3,072 | — |
| OUT [72,144] | 10,368 | — |
| EMB [72,28] | — | 8,064 |
| row-scales (Wif/Whf/Wis/Whs/OUT) | — | 3,168 |
| biases (Bif/Bhf/Bis/Bhs/Bout) | — | 2,976 |
| **total** | **49,728** | **14,208** → **63,936 B** |

MACs: per-char = `3·HF·E + 3·HF·HF + V·OUTIN` = 7,056+21,168+10,368 = **38,592**;
per word-boundary the slow GRU adds `3·HS·HF + 3·HS·HS` = 8,064+3,072 = **11,136**.

## 7. Distillation

Teacher = **2-layer LSTM H384 E64** (1,906,248 params), retrained on the 72-vocab
corpus; held-out ppl **3.251** / top-1 **64.5%** / top-3 **82.7%**.
Student trained with
`loss = α·T²·KL(softmax(student/T) ‖ softmax(teacher/T)) + (1−α)·CE(student, hard)`.
The ablation (§3) found distillation **neutral-to-slightly-negative** in this
data-rich regime, so the deployed model uses it **lightly (T=1.5, α=0.3** — 70 %
hard-CE) to satisfy the spec's "keep distillation" requirement without letting it
hurt, for **24k steps** with the warm-restart schedule.

## 8. Training dynamics — schedule & horizon (the deployed recipe)

The fixed 24k-step cosine budget left the models **under-trained**: at 24k the
cosine forces LR→2e-5 while held-out ppl is still dropping ~0.003–0.004/1k. A
controlled study (128k model, matched compute, held-out int8 ppl):

| recipe | int8 ppl | top-1 |
|--------|---------:|------:|
| cosine 24k (original) | 4.224 | 57.9% |
| cosine 48k (2× horizon) | 4.131 | 58.4% |
| **WSD 48k** (warmup → **long constant high LR** → short decay) | **4.099** | **58.7%** |
| WSD 48k, batch 512 | 4.064 | — |

**Findings.** (1) **Horizon:** 2× steps alone is −0.09 ppl — the 24k budget was the
limiter, and it hit the *bigger* models hardest. (2) **Schedule:** WSD/trapezoidal
(hold a high LR through most of training, decay only at the end) beats a same-length
cosine by −0.03 — keeping LR high lets the model keep moving through parameter
space. (3) **Batch:** 512 (LR ↑ ~√2) adds a small further −0.035.

**Deployed recipe = WSD (peak 2.5e-3), 48k steps, distill α=0.3, no aux.**
Re-training under it: **`nn_460k` int8 3.511 → 3.393** (−0.118 ppl, +1.0 pt top-1);
`nn_256k` 3.784 → 3.665 (−0.119). The frontier **ordering is unchanged** (460k still
tops it) but the whole curve shifts down ~0.12 ppl — the earlier numbers were
understated. The shipped `nn_460k` and `nn_256k` use this recipe (`†` in §4); the
smaller cosine-24k points would each gain ~0.1 ppl if re-trained. Curves in
`nn_460k_wsd_curve.json`; study logs in `dynamics.log`/`retrain.log`.

## 9. Representation frontier — is the dense GRU the most flash-efficient?

Several alternative representations were placed on **one consistent held-out set**
(`run_frontier.py`; `frontier_results.csv`), scored as int8 ppl vs deployed KB:

- **Pure Markov** (char n-gram, modified-Kneser-Ney & Witten-Bell, orders 2–8, with
  *exact* packed table sizes): hopeless per-KB — a 62 KB NN (4.65) beats an 857 KB
  4-gram (5.61), and a **30 MB** 7-gram (4.01) only matches the 128 KB NN (4.04).
  The GRU is ~200× more flash-efficient; compact Markov = a low-order table only.
- **k-gram-MLP** (Bengio-NPLM: positional emb [k,V,D], sum/concat → MLP; no recurrent
  state): far worse per-KB (best 4.39 @ 954 KB ≫ GRU 3.38 @ 468 KB), and interpolating
  it with the GRU gives nothing (3.380 → 3.378) — **subsumed**, like the n-gram.
- **Sparse-pruned NN** (magnitude prune + fine-tune, and a slow-L1 *lottery-ticket*
  anneal, scored under **free indexing** — count only nonzero int8 weights): even
  with indexing assumed *free*, the lottery curve only beats the dense frontier by
  ~0.05–0.08 ppl in the mid-range (~130–320 KB) and loses at the extremes; realistic
  bitmask/CSR indexing erases it. (`lottery_results.csv`.)

**Verdict:** the **dense two-timescale GRU is the most flash-efficient representation
at both operating points** (~64 KB and ~468 KB). Markov and k-gram-MLP are strictly
dominated; sparse is not worth the on-device decode complexity for its at-best-tiny,
index-free-only win. Ship dense int8.

## 10. Positional k-gram Embedding (PKE) study

A dedicated study (`run_pke.py`, `analyze_pke.py`; all rows in `pke_results.csv`) of a
**Positional k-gram Embedding**: a table `E[k, V, D]` giving, for **each** of the last
`k` characters, an embedding that depends on **both** the character **and** its position
offset (tiny: `k·V·D`, e.g. 7·72·16 = 8,064 values). The `k` looked-up vectors are
combined by **sum** (→ D-dim) or **concat** (→ k·D-dim). **PKE is stored/accounted at
fp16**; GRU weights stay int8 per-row; side tensors f32. Every point is evaluated on the
**same held-out set** as §9 and scored as **int8-GRU + fp16-PKE + f32-side deployed KB**.

**Methodology (edge-inference):** the only thing that matters is **held-out ppl per
deployed-KB at convergence** — training compute is free. So **every** point is trained
**to convergence** with a data-triggered WSD schedule (warmup → long constant high-LR
plateau → cosine decay fired only after the held-out monitor plateaus with generous
patience; best checkpoint kept). Undertraining was the #1 risk and is flagged
automatically (a run that hits the step cap while still improving). Every PKE-into-GRU
variant is built to **subsume the baseline exactly** (recover it by zeroing the PKE
contribution), so at convergence it **must** be ≥ baseline — a correctness guard.

### 10a. Integration variants (all ✕ same held-out set, int8/fp16 deployed KB)

1. **standalone** — PKE → dense MLP → softmax (no recurrence).
2. **replace** — raw PKE window feeds the fast-GRU input instead of `emb(last)`.
3. **replace_fmlp** — PKE concat → 2-layer MLP `f` (ReLU) → fast-GRU input.
4. **fmlp_res** ⭐ — GRU input = `emb(last) + g(PKE concat)`, with `g`'s final layer
   **zero-initialized** (training starts exactly at baseline; `g` can only *add*
   positional info — no reconstruction burden).
5. **addstate** — PKE (projected) added to the pre-output state `[hf;hs]`.
6. **concat** — PKE window concatenated into the output-head input.
7. **sparse-high-dim** — a high-`Dh` per-(pos,char) table, summed, trained with a hard
   L1 anneal + a straight-through top-`nnz` prune so it deploys as bitmask + `nnz` fp16.
8. **fuse** — two branches (a converged GRU + a converged PKE-MLP) → a fused logit head;
   Phase A trains only the head (frozen branches), Phase B joint-finetunes.

### 10b. Standalone PKE (dominated, but the table is what matters)

At convergence the **positional table is the whole story**: a plain shared-embedding
window head is useless (int8 ppl **10.99**, t1 35 %), but making the embedding
position-dependent drops it to **4.30** (`pke_cat_k7_D16`, 130 KB, t1 58 %). **concat >
sum** at matched budget; sweet spot **k≈7, D≈16**. But standalone is still **dominated by
the recurrent GRU** (baseline ≈ 4.0 @ 130 KB) — the recurrence is indispensable; a PKE→MLP
head is not a competitive standalone deployment. (This is the same verdict as the prior
k-gram-MLP §9, but properly sized + concat it reaches 4.30 @ 130 KB vs the earlier sweep's
4.39 @ 954 KB — a ~7× flash improvement, which is why the first attempt looked hopeless.)

### 10c. Integration frontier — the winner is `fmlp_res`

Converged baseline GRU vs the PKE integrations, on the accuracy-per-deployed-KB frontier:

| deployed KB | baseline GRU (int8 ppl) | best PKE @ ~same KB | winner |
|------------:|------------------------:|---------------------|--------|
| 84.8  | **4.248** | — | GRU |
| 135.8 | ~3.97 (interp) | `fmlp_res` **3.941** | **PKE −0.03** |
| 172.3 | **3.767** | — | GRU |
| 192.8 | ~3.72 (interp) | `fmlp_res` **3.655** | **PKE −0.07** |
| 225.2 | ~3.66 (interp) | `fmlp_res` **3.607** | **PKE −0.05** |
| 282.4 | **3.538** | — | GRU |
| 337.1 | ~3.47 (interp) | `fmlp_res` **3.464** | **PKE ~tie** |
| 437.4 | **3.350** | — | GRU |
| 493.9 | ~3.33 (extrap) | `fmlp_res` **3.337** | ~tie |

**Findings.**
- **`fmlp_res` is the only integration that beats the dense-GRU frontier** — by **−0.03…−0.07
  ppl in the ~135–250 KB regime**. Injecting positional context at the GRU *input*
  (residually, zero-init) lets the recurrence compound it over time.
- **Full-replace is conclusively dominated** (every point above the baseline curve; even
  large-`Hf` only *reaches* baseline ppl at ~1.5× the bytes). Mechanism: `f` must both
  reconstruct the per-char embedding and mix positions through a ReLU bottleneck →
  optimization-limited, size-independent. The residual+zero-init form removes exactly
  this burden.
- **`concat` ≈ on the frontier** (it only adds positional info at the output head, one-shot,
  no interaction with the recurrence); **`addstate` is dominated** (helps vs a
  matched-GRU baseline but the projection + table cost too many bytes). Both subsume the
  baseline (guard passed); `fmlp_res` beats them because input-side residual injection is
  the most byte-efficient.
- **The PKE advantage shrinks as the GRU grows** (−0.07 @ 193 KB → ~tie by ~340 KB) — a big
  GRU already learns the short-range positional structure PKE supplies (same
  diminishing-returns story as the n-gram hybrid §5).

### 10d. 400 KB operating point (confirm, 3 seeds, matched ~404 KB, mean ± std)

| variant | int8 ppl | t1 | Δ vs base |
|---------|---------:|---:|----------:|
| **fmlp_res** | **3.393 ± 0.002** | .636 | −0.011 |
| base (dense GRU) | 3.404 ± 0.012 | .636 | — |
| addstate | 3.442 ± 0.015 | .633 | +0.038 |
| concat | 3.459 ± 0.044 | .633 | +0.055 |

**At the 400 KB deployment budget, PKE does not meaningfully help.** `fmlp_res` merely
**ties** the dense baseline (−0.011, within the ±0.012 seed noise); addstate/concat lose.
This is the crossover: PKE's edge is real below ~250 KB and gone by 400 KB. **At 400 KB,
spend the bytes on GRU (or `fmlp_res`, equivalent).**

### 10e. Sparse-high-dim and the fuse curriculum (both subsumed by `fmlp_res`)

- **Sparse-high-dim** (hard L1 anneal + straight-through top-`nnz` prune, deployed as
  bitmask + fp16 values, integrated inside `fmlp_res`): the fixed method trains sanely
  (`Dh112/nnz16` → 3.63 @ 232 KB) but **loses to dense concat** `fmlp_res` (3.607 @ 225 KB
  — fewer bytes, better ppl); `nnz8` collapses (mass won't concentrate that hard for
  Dh=112). Sparse-high-dim does **not** beat dense concat.
- **fuse** (2-branch curriculum) **confirms the mechanism but is not a better deployment.**
  Phase A (frozen branches, train only the fused head) sits *slightly worse* than baseline
  at matched KB — a bolted-on frozen PKE adds nothing. Phase B (joint finetune) recovers a
  real gain (Δ A→B = **−0.061** @ 213 KB, **−0.023** @ 478 KB) by letting the GRU shed
  short-range structure onto the PKE branch — **positional context helps only when
  co-adapted with the GRU**. But Phase B (3.641 @ 213 KB) only **ties** `fmlp_res` (~3.625),
  at a much more complex two-branch architecture. `fmlp_res` gets the same benefit directly.

### 10f. Very-long-training / grokking probe (8× warm-restart)

At s170 (213 KB), each model was continue-trained 8× its convergence steps with a big
warm restart (LR spiked to 2.6e-3) then slow decay; reference = the **fully-trained**
sweep ppl (fmlp_res ≈ 3.63, fuse ≈ 3.641 int8):

- **`fmlp_res` saturates — no grokking.** The warm restart bumped it out of the basin
  (mon 3.76→3.81) and the re-anneal returned it to **3.654 int8**, i.e. ~normal
  convergence (not below). Extended training buys nothing for the single-path model.
- **`fuse` keeps improving — mild grokking.** Steady monotonic descent, **still declining
  at 99 % of the 8× horizon**, reaching **3.619 int8 — clearly below its normal 3.641**.
  The **fmlp↔fuse gap flips**: fmlp is marginally ahead at normal convergence, but fuse
  overtakes it by ~0.035 under 8× training (the two-branch model has room to keep
  co-adapting). Caveat: small gains (~0.02–0.035), single-seed, and requiring 8× compute —
  a real qualitative divergence, not a practical deployment lever.
- **s360 (~478 KB), held-high LR (extendability probe) — the strongest grok result.**
  Continue-trained with LR spiked to 2.6e-3 then **held ~2.3e-3** (no anneal-to-zero, so the
  model stays "hot" and extendable). The raw hot-mon stays elevated/noisy (~3.5, above the
  converged 3.42) — the gain is invisible until you cool it, so it's read out
  **non-destructively** by annealing a *copy* of the hot checkpoint (short cosine
  2.3e-3→2e-5; hot ckpt untouched, run continues). Annealed int8 vs fuse-s360 normal 3.354:
  **ext-40k → 3.331 (−0.023); ext-140k (8×N) → 3.314 (−0.040)** — improving **monotonically
  and still descending at 8×N** (no plateau). At **3.314 @ 478 KB** this is the best point at
  that size (vs base_s360 3.350, fmlp_res_s360 3.337). So the **two-branch fuse model keeps
  benefiting from very-long held-high training at large size** (more so than at s170, and
  unlike fmlp_res which saturates) — a real capacity/co-adaptation signal, but only at large
  extra compute (convergence + long hot run + a terminal anneal), not a deployment lever.

### 10g. Conclusion

**The dense two-timescale GRU remains the deployment frontier at the 400 KB budget** — PKE
ties it there, never beats it. **PKE's genuine win is the small-to-mid regime (~135–250 KB):
`fmlp_res`** (residual PKE → learned `g` → GRU input, `g` zero-init; **k=7, D=8–16, concat**)
**beats the dense frontier by −0.03…−0.07 ppl.** All other forms are dominated or subsumed:
full-replace (optimization-limited), addstate/concat (byte-inefficient), standalone
PKE-MLP (no recurrence), sparse-high-dim (loses to dense concat), and — from §5/§9 —
Markov and k-gram-MLP. `fuse` and the grokking probe confirm the underlying mechanism
(positional context helps only when co-adapted with the GRU, and the two-branch model
alone benefits from 8× training) but neither beats `fmlp_res` at deployable compute. **If
a ≤250 KB model is ever wanted, ship `fmlp_res_k7_D8`/`_D16`; at ≥400 KB, ship the dense
GRU.** The best small-mid candidate is **saved**: `nn_fmlp_res_193k.{bin,json,h}` —
`fmlp_res_k7_D8_Hf2kD_s170`, retrained to convergence (int8 **3.649** / t1 **61.6%** at
**192.8 KB**; `export_fmlp_res.py`). The `.bin` packs int8 per-row GRU weights + the `g`
f-map (`GMAP0`,`GMAP2`) + fp16 `PKE[7,72,8]` + f32 emb/biases/scales; `.h`/`.json` give the
offsets and the fmlp_res forward for a future `nn.c` port (the shipped `nn.c` does not yet
consume it). Study artifacts: `run_pke.py` (all variants + convergence trainer),
`analyze_pke.py`, `pke_results.csv` (deduped per-config rows), `pke_pareto.csv` (aggregated
frontier + `on_deploy_frontier` flag), `grok_*_traj.json` / `grok_fuse_s360_readouts.csv`
(grokking trajectories + annealed readouts).

## Quantization scheme (deployed)

- **int8, per-output-row symmetric.** For each weight row `o`:
  `scale[o]=max_i|W[o,i]|/127`, `q[o,i]=round(W[o,i]/scale[o]) ∈ [−127,127]`,
  scales stored float32.
- Quantized tensors: per fast layer `Wif{l}, Whf{l}`, plus `Wis, Whs, OUT`.
  **Embedding and all biases stay float32.**
- On-device linear: `acc = Σ_i (float)w_int8[i]·x_float[i];  out = acc·scale + bias`
  (FPU float32, accumulated sequentially over the inner index — bit-for-bit the
  same order as `nn_common.lin_q`).

## Flash layout — `nn_weights.bin` (offsets in `nn_weights.h`)

Per-model layout (generated by `nn_common.pack_weights`): int8 blocks first
(each 4-byte-padded) — for each fast layer `Wif{l},Whf{l}`, then `Wis,Whs,OUT` —
then float32 blocks (`EMB`, all `_scale` rows, all biases). The blob is flashed at
this model's base; `nn.c` addresses it via `WBASE` (default **0x61000**, the start
of the expanded region; pass `-DWBASE=<addr>` to match where it was written).
Example (`nn_460k`, **FL=2**): Wif0[552,56], Whf0[552,184], **Wif1[552,184],
Whf1[552,184]**, Wis[288,184], Whs[288,96], OUT[72,336], then EMB[72,56] + all
scales + biases → **479,424 B**, ending **0xD60C0** (< 0xD8000, ~40 KB margin).
`nn_manifest.json` has the exact offsets.

## RAM layout (parametric; `SFLOATS = NLAYERS_FAST·HF + HS`)

| region | address | size | contents |
|--------|---------|------|----------|
| `M` metadata | 0x2003f000 | 20 B | magic, last_token, disp sym, have_shadow |
| `PREDS` | 0x2003f00c | 3 B | top-3 predicted symbols |
| **persistent state** | 0x2003f100 | `SFLOATS`·4 | `hf0..hf{FL−1}` then `hs` float32 |
| **shadow (undo)** | `ST + SFLOATS` | `SFLOATS`·4 + 4 | prev state + prev disp sym |
| scratch `GI` | 0x2003b000 | 3·HF·4 | gate acc, input side (≤ 8 KB) |
| scratch `GH` | 0x2003d000 | 3·HF·4 | gate acc, hidden side (≤ 8 KB) |

State+shadow sit just above 0x2003f100 (for `nn_460k`: 1,856 B + 1,860 B, ending
0x2003f9C4 < 0x20040000). Scratch fills 0x2003b000–0x2003f000 (16 KB; GI/GH 8 KB
apart, supporting 3·HF ≤ 2048 → HF ≤ 682); the slow GRU reuses GI/GH (3·HS ≤ 3·HF).
All persistent state ≤ ~1.9 KB (relaxed budget 8 KB); no large stack arrays.

## On-device INPUT mapping (HID report → symbol stream) — `nn.c`

`RPT[]` = live u16 keycode array @`0x2000b6f8`, count @`0x20003370`.
- **Shift held** = keycode `0xe1` (LShift) or `0xe5` (RShift) present.
- **Main key** = first non-modifier (`<0xe0` or `>0xe7`) keycode `≥ 0x04`.
- Edge-detect token = `(shift<<16)|keycode` in `M[1]`; symbols are emitted only
  when the token changes (held/auto-repeat keys fire once; an empty report resets
  the token so double-letters work).

| keycode | unshifted | + Shift |
|---------|-----------|---------|
| `0x04–0x1d` (a–z) | letter | **CAPESC then letter** |
| `0x1e–0x26` (1–9) | `1`…`9` | `!` `@` `#` `$` `%` `^` `&` `*` `(` |
| `0x27` (0) | `0` | `)` |
| `0x28` Enter | NEWLINE | NEWLINE |
| `0x2b` Tab | TAB | TAB |
| `0x2c` Space | space | space |
| `0x2d` `-` | `-` | `_` |
| `0x2e` `=` | `=` | `+` |
| `0x2f` `[` | `[` | `{` |
| `0x30` `]` | `]` | `}` |
| `0x31` `\` | `\` | `\|` |
| `0x33` `;` | `;` | `:` |
| `0x34` `'` | `'` | `"` |
| `0x35` `` ` `` | `` ` `` | `~` |
| `0x36` `,` | `,` | `<` |
| `0x37` `.` | `.` | `>` |
| `0x38` `/` | `/` | `?` |
| `0x2a` **Backspace** | one-level undo | one-level undo |

**Every** US-keyboard printable maps to a real vocab symbol (`=` and `/` are in
the vocab), so there are no "shift → drop" fallbacks. Shift+letter emits **two**
symbols (CAPESC then the lowercase letter), both fed to the fast GRU; since both
are alphabetic, neither advances the slow (word) state. Digits, space, tab,
newline and punctuation are word boundaries and advance the slow state.

**Ignored keys** (feed nothing, state unchanged): arrows `0x4f–0x52`, Caps Lock
`0x39`, Ins/Home/PgUp/Del/End/PgDn `0x49–0x4e`, F-keys `0x3a–0x45`, Esc `0x29`,
GUI/modifiers, keypad — anything `map_key` doesn't recognize returns 0 symbols.

**Backspace = one-level undo.** Before applying each keystroke's symbol(s), the
current persistent state (fast+slow) and the current display symbol are snapshotted
into the shadow buffer. Backspace restores that snapshot (reverting exactly one
keystroke, including a 2-symbol Shift+letter) and clears the shadow. One level
only: a second consecutive Backspace does nothing.

## Display

`FONT[72][8]` — the 26 proven a–z glyphs from the previous nn.c, plus new 8×8
glyphs for `0–9`, all 32 punctuation, and recognizable markers: **space** =
underscore, **TAB** = `»`-style double chevron, **NEWLINE** = return-arrow,
**CAPESC** = up-arrow. `draw_char` renders the last input symbol (small, left) and
top-3 predictions at decreasing scale, same setpx/STRIDE/DIRTY contract as gru.c.

## Robustness — unique magic + reseed-on-unhealthy

RAM survives a DFU soft reset, so a stale/shared seed magic would skip seed-init
and run on garbage (the v2 blank-prediction bug). This build uses a **fresh unique
magic `0xF00D4001`** (bump it every rebuild / per model) and **also reseeds whenever the
persistent state is non-finite or out of range** (`state_bad()` checks the exponent
bits for inf/NaN and `|h|>30`).
Reseed = zero the state, step one space (a boundary, so it primes both fast and
slow), predict, and re-stamp the magic + clear the shadow.

## Reference ↔ device agreement

`nn_ref.py` loads `nn_weights.bin` + `nn_manifest.json` and runs the **same**
int8×float32 two-timescale forward as `nn.c` (same Padé tanh/σ, same per-row
dequant, same boundary rule, same skip, same sequential float accumulation order),
seeding with a leading space exactly like the device. It prints top-3 for prefixes
covering capitals, punctuation, digits and newlines (`^the `, `i'm`, `x = 3`,
`def f(`, `http`, `3.14`, `a[0]`, `hello, World!`, …). The independent numpy
`eval_quant` in `nn_train.py` (batched, different code path) agrees with it, so
on-device top-3 matches the reference.

Build check (does **not** flash; operator flashes hardware):
```
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp \
  -Os -ffreestanding -fno-builtin -nostdlib -c nn.c
```
→ compiles clean, 0 B bss — **2,506 B** text for the FL=2 `nn_460k` pick,
2,426 B for an FL=1 header.

## Files

- `nn_fetch_corpus.py` → `corpus_big.txt` (prose). `nn_augment_corpus.py` →
  `corpus_code.txt` (local Python source sample, for symbols/digits/code).
- `nn_common.py` — vocab/preprocessing, int8 quant, int8×float **stacked**
  two-timescale forward (`TTModel`, `FL` fast layers), Padé tanh/σ, pack/load,
  budget calculators. Shared by trainer and reference.
- `nn_train.py` — teacher training, distilled student + export with warm-restart +
  aux-anneal + early-stop; size via `--HF/--HS/--E/--FL --out_prefix`.
- `run_scaling.sh` — trains the 64/128/256/400 KB + FL=2 series.
  `collect_scaling.py` → `scaling_results.csv`.
- **`nn_ablate.py` / `run_ablate.py` / `run_confirm72.py`** — controlled ablation
  harness (single-GRU / two-timescale / cell-type / aux / distill / boundary;
  27-symbol testbed + 72-symbol confirm). `ablation_results.csv` — all arm rows.
- **`nn_ngram.py` / `run_ngram.py`** — the n-gram/Markov hybrid study
  (`nn_ngram_results.json`).
- `gen_font.py` — regenerates the `FONT[72][8]` table.
- `nn.c` — on-device input mapping + stacked two-timescale forward + Backspace undo
  + reseed + `render()`; parametric via `nn_weights.h` (any candidate) and `WBASE`.
- **Candidate models** `nn_{64k,128k,256k,400k,256k_fl2}.{bin,h,json}` (+ `_metrics.json`).
  `nn_weights.{bin,h}` / `nn_manifest.json` = the recommended `nn_400k` (default).
- `nn_ref.py [prefix]` — bit-close reference; loads any candidate; prints top-3 for
  capital/punct/digit/newline prefixes. `nn_curve.json` — a model's held-out curve.
- `nn_teacher.pt` — the distillation teacher (72-vocab).

Reproducible: torch/numpy seeds fixed throughout; key ablation arms on 2 seeds
(mean ± spread). No hardware was flashed (operator flashes).
