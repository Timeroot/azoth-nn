#!/usr/bin/env python3
"""Shared code for the on-device char NN v3 (BIG vocab + two-timescale GRU).

Vocab (V=72):
    0..25   a-z
    26..35  0-9
    36      space
    37      \\t   TAB
    38      \\n   NEWLINE
    39      CAPITAL ESCAPE  (its OWN token, NOT the literal '^' char; emitted
                             immediately BEFORE an originally-uppercase letter,
                             so "X" -> [CAPESC][x], "I'm" -> [CAPESC] i ' m)
    40..71  ASCII punctuation, in ASCII code order:
            ! " # $ % & ' ( ) * + , - . /  :  ;  <  =  >  ?  @  [  \\  ]  ^  _  `  {  |  }  ~

Two-timescale architecture:
    * FAST char-level GRU (state hf[HF]) updates every character.
    * SLOW word-level GRU (state hs[HS]) updates ONLY at a word boundary -- i.e.
      right after a NON-alphabetic char is typed (alphabetic := a-z or CAPESC).
      The slow update consumes the current fast state:  hs = GRU_slow(hf, hs).
    * Char prediction reads BOTH states:  logits = OUT @ [hf ; hs] (+ emb skip).
Combined persistent state hf+hs must be <= 256 float32 (1 KB).

Provides: corpus preprocessing -> symbol stream; per-output-row int8 symmetric
quant; the int8xfloat32 forward used on device; the libm-free Pade tanh/sigmoid;
and weight packing/loading.  Imported by nn_train.py and nn_ref.py so the
quantized reference math is identical everywhere and matches nn.c.
"""
import re, os, json
import numpy as np

# ------------------------------------------------------------------ vocab ----
_PUNCT = ('!"#$%&\'()*+,-./' ':;<=>?@' '[\\]^_`' '{|}~')   # 32 chars, ASCII order
SYMS   = (list("abcdefghijklmnopqrstuvwxyz") + list("0123456789")
          + [" ", "\t", "\n", "\x00"]           # 36 space, 37 tab, 38 nl, 39 CAPESC
          + list(_PUNCT))                        # 40..71
V   = len(SYMS)                                  # 72
assert V == 72, V

SP     = 36
TAB    = 37
NL     = 38
CAPESC = 39
_CAPCH = "\x01"          # sentinel char used in preprocessed text for CAPESC

# byte -> token LUT (default = space; only hit by residual junk after cleaning)
_LUT = np.full(256, SP, np.uint8)
for i, c in enumerate(SYMS):
    if c != "\x00":                       # CAPESC has no literal char of its own
        _LUT[ord(c)] = i
_LUT[ord(_CAPCH)] = CAPESC

# set of vocab code points that survive preprocessing as literal chars
_KEEP = set(ord(c) for c in SYMS if c != "\x00") | {ord(_CAPCH)}

def is_alpha(sym):
    """Word-INTERIOR char: a-z or CAPESC.  Everything else = word boundary."""
    return sym < 26 or sym == CAPESC

def sym_str(i):
    i = int(i)
    return {SP: "_", TAB: "\\t", NL: "\\n", CAPESC: "^^"}.get(i, SYMS[i])

# ------------------------------------------------------------------ corpus ----
_UNI = {"’": "'", "‘": "'", "ʼ": "'",         # curly apostrophes
        "“": '"', "”": '"',                        # curly double quotes
        "«": '"', "»": '"',
        "—": "-", "–": "-", "―": "-",         # em / en / bar dash
        "…": ".", " ": " ", "•": "*"}         # ellipsis, nbsp, bullet

def preprocess(text):
    """Raw text -> cleaned string over the 72-symbol alphabet (CAPESC = _CAPCH)."""
    text = text.replace("\r\n", "\n").replace("\r", "\n")     # normalize newlines
    text = text.translate({ord(k): v for k, v in _UNI.items()})
    text = re.sub(r"[A-Z]", lambda m: _CAPCH + m.group().lower(), text)  # cap escape
    # keep vocab chars (incl \t \n and the CAPESC sentinel); junk -> space
    out = []
    for ch in text:
        out.append(ch if ord(ch) in _KEEP else " ")
    text = "".join(out)
    text = re.sub(r"[ ]{2,}", " ", text)          # collapse runs of >=2 spaces (keep \t \n)
    return text

def load_symbols(path):
    t = preprocess(open(path, "r", encoding="utf-8", errors="ignore").read())
    arr = np.frombuffer(t.encode("latin-1", "ignore"), dtype=np.uint8)
    return _LUT[arr].astype(np.int64)

def encode(text):
    """Encode a (mixed-case, punctuated) prefix string via the real preprocessing."""
    t = preprocess(text)
    arr = np.frombuffer(t.encode("latin-1", "ignore"), dtype=np.uint8)
    return _LUT[arr].astype(np.int64).tolist()

# ------------------------------------------------ Pade tanh / sigmoid (f32) ---
# Identical constants/order to nn.c's tanhf_ / sig_.  All ops in float32.
def tanh_pade(x):
    x = np.asarray(x, dtype=np.float32)
    hi = x > np.float32(4.9); lo = x < np.float32(-4.9)
    x2 = (x * x).astype(np.float32)
    num = (x * (np.float32(135135.0) + x2 * (np.float32(17325.0)
              + x2 * (np.float32(378.0) + x2)))).astype(np.float32)
    den = (np.float32(135135.0) + x2 * (np.float32(62370.0)
              + x2 * (np.float32(3150.0) + x2 * np.float32(28.0)))).astype(np.float32)
    out = (num / den).astype(np.float32)
    out[hi] = np.float32(1.0); out[lo] = np.float32(-1.0)
    return out

def sig_pade(x):
    x = np.asarray(x, dtype=np.float32)
    return (np.float32(0.5) * (np.float32(1.0)
            + tanh_pade(np.float32(0.5) * x))).astype(np.float32)

# ----------------------------------------------------------- quantization ----
def quant_rows(W, bits=8):
    """Per-output-row symmetric int8 quant.  W:[rows,cols] float32."""
    W = np.asarray(W, dtype=np.float32)
    qmax = 127
    amax = np.max(np.abs(W), axis=1)
    scale = (amax / np.float32(qmax)).astype(np.float32)
    scale[scale == 0] = np.float32(1e-8)
    q = np.round(W / scale[:, None]).astype(np.int32)
    q = np.clip(q, -qmax, qmax).astype(np.int8)
    return q, scale

def lin_q(x, q, scale, bias):
    """out[o] = (sum_i q[o,i]*x[i]) * scale[o] + bias[o]  (float32), mirrors nn.c.
    Accumulates SEQUENTIALLY over inner index k (vectorized across rows) so the
    float32 summation order matches nn.c's `for(k) a += (float)w*x` loop."""
    x = np.asarray(x, dtype=np.float32)
    qf = q.astype(np.float32)
    acc = np.zeros(q.shape[0], dtype=np.float32)
    for k in range(x.shape[0]):
        acc = (acc + qf[:, k] * x[k]).astype(np.float32)
    return (acc * scale + bias).astype(np.float32)

# ------------------------------------------------------- two-timescale model --
class TTModel:
    """int8xfloat32 two-timescale GRU forward, matched to nn.c.

    params dict keys (float32 unless noted):
      EMB[V,E]
      Wif[3HF,E] int8, Wif_s[3HF], Bif[3HF], Whf[3HF,HF] int8, Whf_s[3HF], Bhf[3HF]
      Wis[3HS,HF] int8, Wis_s[3HS], Bis[3HS], Whs[3HS,HS] int8, Whs_s[3HS], Bhs[3HS]
      OUT[V,OUTIN] int8, OUT_s[V], Bout[V]   (OUTIN = HF+HS (+E if out_skip))
    """
    def __init__(self, HF, HS, E, V_, p, out_skip=False, FL=1):
        self.HF, self.HS, self.E, self.V, self.FL = HF, HS, E, V_, FL
        self.p = p; self.out_skip = out_skip

    def state_size(self):
        return self.FL * self.HF + self.HS

    def init_state(self):
        return {"hf": [np.zeros(self.HF, np.float32) for _ in range(self.FL)],
                "hs": np.zeros(self.HS, np.float32),
                "x":  np.zeros(self.E,  np.float32)}

    def _gru(self, x, h, H, Wi, Si, Bi, Wh, Sh, Bh):
        gi = lin_q(x, Wi, Si, Bi)
        gh = lin_q(h, Wh, Sh, Bh)
        r = sig_pade(gi[0:H]     + gh[0:H])
        z = sig_pade(gi[H:2*H]   + gh[H:2*H])
        n = tanh_pade(gi[2*H:3*H] + r * gh[2*H:3*H])
        return ((np.float32(1.0) - z) * n + z * h).astype(np.float32)

    def step(self, sym, st):
        p = self.p
        x = p["EMB"][sym].astype(np.float32); st["x"] = x
        inp = x
        for l in range(self.FL):
            st["hf"][l] = self._gru(inp, st["hf"][l], self.HF,
                p[f"Wif{l}"], p[f"Wif{l}_s"], p[f"Bif{l}"],
                p[f"Whf{l}"], p[f"Whf{l}_s"], p[f"Bhf{l}"])
            inp = st["hf"][l]
        if not is_alpha(int(sym)):          # word boundary -> update slow state
            st["hs"] = self._gru(st["hf"][self.FL-1], st["hs"], self.HS,
                                 p["Wis"], p["Wis_s"], p["Bis"],
                                 p["Whs"], p["Whs_s"], p["Bhs"])
        return st

    def logits(self, st):
        feat = np.concatenate([st["hf"][self.FL-1], st["hs"]]).astype(np.float32)
        if self.out_skip:
            feat = np.concatenate([feat, st["x"]]).astype(np.float32)
        return lin_q(feat, self.p["OUT"], self.p["OUT_s"], self.p["Bout"])

    def top3(self, st):
        return list(np.argsort(-self.logits(st))[:3])


# ------------------------------------------------------- pack / load .bin ----
def _i8_names(FL):
    names = []
    for l in range(FL):
        names += [f"Wif{l}", f"Whf{l}"]
    return names + ["Wis", "Whs", "OUT"]

def _bias_names(FL):
    names = []
    for l in range(FL):
        names += [f"Bif{l}", f"Bhf{l}"]
    return names + ["Bis", "Bhs", "Bout"]

def pack_weights(HF, HS, E, tensors, out_bin, out_h, out_json, out_skip=False, FL=1):
    """Pack stacked two-timescale weights: int8 blocks first (4-byte padded), f32 next."""
    int8_specs = []
    for name in _i8_names(FL):
        q, s = quant_rows(tensors[name], 8)
        int8_specs.append((name, q, s))
    float_specs = [("EMB", np.asarray(tensors["EMB"], np.float32).ravel())]
    for name, q, s in int8_specs:
        float_specs.append((name + "_scale", s.astype(np.float32)))
    for name in _bias_names(FL):
        float_specs.append((name, np.asarray(tensors[name], np.float32).ravel()))

    blob = bytearray(); offs = {}; shapes = {}
    for name, q, s in int8_specs:
        offs[name] = len(blob); shapes[name] = list(q.shape)
        blob += q.tobytes()
        while len(blob) % 4: blob.append(0)
    float_base = len(blob)
    for name, a in float_specs:
        offs[name] = len(blob); shapes[name] = list(a.shape)
        blob += a.astype(np.float32).tobytes()
    open(out_bin, "wb").write(blob)

    OUTIN = HF + HS + (E if out_skip else 0)
    manifest = {"HF": HF, "HS": HS, "E": E, "V": V, "FL": FL, "out_skip": out_skip,
                "OUTIN": OUTIN, "bytes": len(blob), "float_base": float_base,
                "offsets": offs, "shapes": shapes}
    json.dump(manifest, open(out_json, "w"), indent=1)

    with open(out_h, "w") as f:
        f.write("/* auto-generated. nn_weights layout at the model's flash base. */\n")
        f.write(f"#define VOCAB {V}\n#define EDIM {E}\n")
        f.write(f"#define HF {HF}\n#define HS {HS}\n#define NLAYERS_FAST {FL}\n")
        f.write(f"#define OUT_SKIP {1 if out_skip else 0}\n")
        f.write(f"#define OUTIN {OUTIN}\n")
        f.write(f"#define WEIGHTS_BYTES {len(blob)}\n")
        for name in offs:
            f.write(f"#define OFF_{name.upper()} {offs[name]}u\n")
    return manifest, len(blob)


def load_ttmodel(bin_path, manifest_path):
    m = json.load(open(manifest_path))
    blob = np.frombuffer(open(bin_path, "rb").read(), dtype=np.uint8)
    off = m["offsets"]; shp = m["shapes"]
    def get_i8(name):
        n = int(np.prod(shp[name]))
        return blob[off[name]:off[name] + n].view(np.int8).reshape(shp[name])
    def get_f32(name):
        n = int(np.prod(shp[name])); b = off[name]
        return np.frombuffer(blob[b:b + n*4].tobytes(), np.float32).reshape(shp[name])
    HF, HS, E = m["HF"], m["HS"], m["E"]; FL = m.get("FL", 1)
    p = {"EMB": get_f32("EMB").reshape(V, E),
         "OUT": get_i8("OUT"), "OUT_s": get_f32("OUT_scale"), "Bout": get_f32("Bout")}
    for name in _i8_names(FL):
        if name == "OUT": continue
        p[name] = get_i8(name); p[name + "_s"] = get_f32(name + "_scale")
    for name in _bias_names(FL):
        if name == "Bout": continue
        p[name] = get_f32(name)
    return TTModel(HF, HS, E, V, p, out_skip=m.get("out_skip", False), FL=FL)


def count_bytes(HF, HS, E, out_skip=False, FL=1):
    OUTIN = HF + HS + (E if out_skip else 0)
    fast = 3*HF*E + 3*HF*HF + (FL-1)*(6*HF*HF)   # layer0 (ih+hh) + extra layers
    i8 = fast + 3*HS*HF + 3*HS*HS + V*OUTIN
    fl = V*E + 12*HF*FL + 12*HS + 2*V            # EMB + all row-scales + biases
    return i8 + fl*4, i8, fl

def count_macs_char(HF, HS, E, out_skip=False, FL=1):
    OUTIN = HF + HS + (E if out_skip else 0)
    return 3*HF*E + 3*HF*HF + (FL-1)*(6*HF*HF) + V*OUTIN

def count_macs_word(HF, HS):
    return 3*HS*HF + 3*HS*HS
