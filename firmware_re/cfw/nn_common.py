#!/usr/bin/env python3
"""Shared code for the on-device char NN.

Vocab (V=32):
    0..25  a-z
    26     space / word separator
    27     '  apostrophe
    28     .  period       (also '!' and '?' map here)
    29     ,  comma
    30     -  dash
    31     ^  CAPITAL ESCAPE  (emitted immediately BEFORE an originally-uppercase
                               letter: "I'm, Mom!" -> "^i'm, ^mom.")

Provides: corpus preprocessing -> symbol stream, int8 per-output-row symmetric
quantization (+ int4 variant), the int8/int4 x float32 forward pass used on
device, the libm-free Pade tanh/sigmoid, and weight packing/loading.

Imported by nn_train.py and nn_ref.py so the quantized reference math is identical
everywhere and matches nn.c.
"""
import re, os, json
import numpy as np

# ---- vocab ----
SYMS = list("abcdefghijklmnopqrstuvwxyz") + [" ", "'", ".", ",", "-", "^"]
V     = len(SYMS)                 # 32
SP    = 26
APOS  = 27
DOT   = 28
COMMA = 29
DASH  = 30
CARET = 31
_LUT = np.full(256, SP, np.uint8)
for i, c in enumerate(SYMS):
    _LUT[ord(c)] = i

def sym_str(i):
    return "_" if i == SP else SYMS[i]

# ------------------------------------------------------------------ corpus ----
_UNI = {"’": "'", "‘": "'", "ʼ": "'",      # curly / modifier apostrophes
        "“": " ", "”": " ", "«": " ", "»": " ",  # double quotes
        "—": " ", "–": " ", "―": " ",      # em / en / horizontal dash
        "…": ".", " ": " "}                     # ellipsis, nbsp

def preprocess(text):
    """Raw text -> cleaned string over the 32-symbol alphabet (as chars)."""
    text = text.translate({ord(k): v for k, v in _UNI.items()})       # normalize unicode
    text = re.sub(r"[A-Z]", lambda m: "^" + m.group().lower(), text)  # capital escape
    text = re.sub(r"[!?]", ".", text)                                 # ! ? -> .
    text = re.sub(r"[^a-z',.^-]+", " ", text)     # collapse all else (ws/digits/…) -> space
    text = re.sub(r" +", " ", text).strip()
    return text

def load_symbols(path):
    t = open(path, "r", encoding="utf-8", errors="ignore").read()
    t = preprocess(t)
    arr = np.frombuffer(t.encode("latin-1", "ignore"), dtype=np.uint8)
    return _LUT[arr].astype(np.int64)

def encode(text):
    """Encode a (possibly mixed-case, punctuated) prefix string to symbols."""
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
    """Per-output-row symmetric int quant.  W:[rows,cols] float32.
    bits=8 -> int8 in [-127,127];  bits=4 -> int in [-7,7] (stored int8)."""
    W = np.asarray(W, dtype=np.float32)
    qmax = 127 if bits == 8 else 7
    amax = np.max(np.abs(W), axis=1)
    scale = (amax / np.float32(qmax)).astype(np.float32)
    scale[scale == 0] = np.float32(1e-8)
    q = np.round(W / scale[:, None]).astype(np.int32)
    q = np.clip(q, -qmax, qmax).astype(np.int8)
    return q, scale

def lin_q(x, q, scale, bias):
    """out[o] = (sum_i q[o,i]*x[i]) * scale[o] + bias[o]   (float32), mirrors nn.c.

    Accumulates SEQUENTIALLY over the inner index k (vectorized across output rows)
    so the float32 summation order matches nn.c's `for(k) a += (float)w*x` loop.
    Only remaining possible diff vs nn.c is FPU fma contraction (~1e-6)."""
    x = np.asarray(x, dtype=np.float32)
    qf = q.astype(np.float32)
    acc = np.zeros(q.shape[0], dtype=np.float32)
    for k in range(x.shape[0]):
        acc = (acc + qf[:, k] * x[k]).astype(np.float32)
    return (acc * scale + bias).astype(np.float32)

# ---------------------------------------------------------- forward (ref) ----
class QModel:
    """int8/int4 x float32 forward for a 1- or 2-layer GRU/LSTM with optional
    input-to-output skip (OUT reads [h_last ; emb(last_sym)])."""
    def __init__(self, arch, layers, Hs, E, params, out_skip=False):
        self.arch = arch; self.layers = layers; self.Hs = Hs
        self.E = E; self.p = params; self.out_skip = out_skip

    def state_size(self):
        mul = 2 if self.arch == "lstm" else 1
        return mul * sum(self.Hs)

    def init_state(self):
        return {"h": [np.zeros(H, np.float32) for H in self.Hs],
                "c": [np.zeros(H, np.float32) for H in self.Hs],
                "x": np.zeros(self.E, np.float32)}

    def step(self, sym, st):
        p = self.p
        x = p["EMB"][sym].astype(np.float32)
        st["x"] = x
        for l in range(self.layers):
            H = self.Hs[l]; h = st["h"][l]
            gi = lin_q(x, p[f"Wih{l}"], p[f"Sih{l}"], p[f"Bih{l}"])
            gh = lin_q(h, p[f"Whh{l}"], p[f"Shh{l}"], p[f"Bhh{l}"])
            if self.arch == "gru":
                r = sig_pade(gi[0:H] + gh[0:H])
                z = sig_pade(gi[H:2*H] + gh[H:2*H])
                n = tanh_pade(gi[2*H:3*H] + r * gh[2*H:3*H])
                h = ((np.float32(1.0) - z) * n + z * h).astype(np.float32)
                st["h"][l] = h; x = h
            else:
                c = st["c"][l]; pre = (gi + gh).astype(np.float32)
                i = sig_pade(pre[0:H]); f = sig_pade(pre[H:2*H])
                g = tanh_pade(pre[2*H:3*H]); o = sig_pade(pre[3*H:4*H])
                c = (f * c + i * g).astype(np.float32)
                h = (o * tanh_pade(c)).astype(np.float32)
                st["c"][l] = c; st["h"][l] = h; x = h
        return st

    def logits(self, st):
        h = st["h"][self.layers - 1]
        feat = np.concatenate([h, st["x"]]).astype(np.float32) if self.out_skip else h
        return lin_q(feat, self.p["OUT"], self.p["Sout"], self.p["Bout"])

    def top3(self, st):
        return list(np.argsort(-self.logits(st))[:3])


# ------------------------------------------------------- pack / load .bin ----
def pack_weights(arch, layers, Hs, E, tensors, out_bin, out_h, out_json,
                 out_skip=False, rec_bits=8):
    """Pack weights.  int8 blocks first (4-byte padded), then float32 blocks.
    Recurrent matrices (Whh, and Wih) use rec_bits (8 or 4); OUT stays int8."""
    g = 3 if arch == "gru" else 4
    int8_specs = []; float_specs = []
    float_specs.append(("EMB", np.asarray(tensors["EMB"], np.float32).ravel()))
    for l in range(layers):
        qih, sih = quant_rows(tensors[f"Wih{l}"], rec_bits)
        qhh, shh = quant_rows(tensors[f"Whh{l}"], rec_bits)
        int8_specs.append((f"Wih{l}", qih, sih))
        int8_specs.append((f"Whh{l}", qhh, shh))
    qout, sout = quant_rows(tensors["OUT"], 8)
    int8_specs.append(("OUT", qout, sout))
    for name, q, s in int8_specs:
        float_specs.append((name + "_scale", s.astype(np.float32)))
    for l in range(layers):
        float_specs.append((f"Bih{l}", np.asarray(tensors[f"Bih{l}"], np.float32)))
        float_specs.append((f"Bhh{l}", np.asarray(tensors[f"Bhh{l}"], np.float32)))
    float_specs.append(("Bout", np.asarray(tensors["Bout"], np.float32)))

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

    manifest = {"arch": arch, "layers": layers, "Hs": Hs, "E": E, "V": V,
                "gates": g, "out_skip": out_skip, "rec_bits": rec_bits,
                "bytes": len(blob), "float_base": float_base,
                "offsets": offs, "shapes": shapes}
    json.dump(manifest, open(out_json, "w"), indent=1)

    with open(out_h, "w") as f:
        f.write("/* auto-generated. nn_weights.bin layout at flash base 0x50000. */\n")
        f.write(f"#define ARCH_LSTM {1 if arch=='lstm' else 0}\n")
        f.write(f"#define NLAYERS {layers}\n#define VOCAB {V}\n#define EDIM {E}\n")
        f.write(f"#define GATES {g}\n#define OUT_SKIP {1 if out_skip else 0}\n")
        f.write(f"#define REC_BITS {rec_bits}\n")
        for i, H in enumerate(Hs):
            f.write(f"#define H{i} {H}\n")
        f.write(f"#define HLAST {Hs[-1]}\n")
        f.write(f"#define OUTIN {Hs[-1] + (E if out_skip else 0)}\n")
        f.write(f"#define WEIGHTS_BYTES {len(blob)}\n")
        for name in offs:
            f.write(f"#define OFF_{name.upper()} {offs[name]}u\n")
    return manifest, len(blob)


def load_qmodel(bin_path, manifest_path):
    m = json.load(open(manifest_path))
    blob = np.frombuffer(open(bin_path, "rb").read(), dtype=np.uint8)
    off = m["offsets"]; shp = m["shapes"]
    def get_i8(name):
        n = int(np.prod(shp[name]))
        return blob[off[name]:off[name] + n].view(np.int8).reshape(shp[name])
    def get_f32(name):
        n = int(np.prod(shp[name])); b = off[name]
        return np.frombuffer(blob[b:b + n*4].tobytes(), dtype=np.float32).reshape(shp[name])
    layers = m["layers"]; Hs = m["Hs"]; E = m["E"]
    p = {"EMB": get_f32("EMB").reshape(V, E),
         "OUT": get_i8("OUT"), "Sout": get_f32("OUT_scale"), "Bout": get_f32("Bout")}
    for l in range(layers):
        p[f"Wih{l}"] = get_i8(f"Wih{l}"); p[f"Sih{l}"] = get_f32(f"Wih{l}_scale")
        p[f"Whh{l}"] = get_i8(f"Whh{l}"); p[f"Shh{l}"] = get_f32(f"Whh{l}_scale")
        p[f"Bih{l}"] = get_f32(f"Bih{l}"); p[f"Bhh{l}"] = get_f32(f"Bhh{l}")
    return QModel(m["arch"], layers, Hs, E, p, out_skip=m.get("out_skip", False))
