#!/usr/bin/env python3
"""Train a small char-level GRU (27 syms: a-z + space) and export float32 weights
as weights.h (placed in a .weights flash section on-device). Matches torch GRUCell
math so the C forward pass reproduces it exactly."""
import re, os, torch, torch.nn as nn
HERE = os.path.dirname(os.path.abspath(__file__))
SP = 26; V = 27; E = 8; H = 32
dev = "cuda" if torch.cuda.is_available() else "cpu"

def load(path):
    t = open(path,"r",encoding="utf-8",errors="ignore").read().lower()
    t = re.sub(r"[^a-z]+"," ",t); t = re.sub(r" +"," ",t).strip()
    return [ord(c)-97 if c!=" " else SP for c in t]
data = torch.tensor(load(os.path.join(HERE,"corpus_raw.txt")), dtype=torch.long)
print("symbols:", len(data), "device:", dev)

class M(nn.Module):
    def __init__(s):
        super().__init__()
        s.emb = nn.Embedding(V,E)
        s.gru = nn.GRU(E,H,batch_first=True)
        s.out = nn.Linear(H,V)
    def forward(s,x,h=None):
        e = s.emb(x); y,h = s.gru(e,h); return s.out(y),h
m = M().to(dev)
opt = torch.optim.Adam(m.parameters(), lr=2e-3)
lossf = nn.CrossEntropyLoss()

L=120; B=256
def batch():
    idx = torch.randint(0, len(data)-L-1, (B,))
    x = torch.stack([data[i:i+L] for i in idx]).to(dev)
    y = torch.stack([data[i+1:i+L+1] for i in idx]).to(dev)
    return x,y

STEPS=4000
for step in range(STEPS):
    x,y = batch()
    logits,_ = m(x)
    loss = lossf(logits.reshape(-1,V), y.reshape(-1))
    opt.zero_grad(); loss.backward(); opt.step()
    if step%500==0: print(f"step {step}  loss {loss.item():.3f}  ppl {torch.exp(loss).item():.2f}")
print("final loss", loss.item())

# sanity: greedy top-3 for a few prefixes
m.eval()
def s(i): return "_" if i==SP else chr(97+i)
def enc(text): return [ord(c)-97 if c!=" " else SP for c in text.lower()]
with torch.no_grad():
    for pref in ["the ","q","th","predic","hello ","comput","in","and ","peopl"]:
        xs = torch.tensor([enc(pref)],device=dev)
        logits,_ = m(xs)
        top = logits[0,-1].topk(3).indices.tolist()
        print(f"  '{pref}' -> {' '.join(s(t) for t in top)}")

# ---- export weights (torch GRU gate order: r,z,n in rows 0:H,H:2H,2H:3H) ----
sd = m.state_dict()
def arr(t): return t.detach().cpu().flatten().tolist()
W = {
 "EMB":   arr(sd["emb.weight"]),               # [V,E]
 "W_ih":  arr(sd["gru.weight_ih_l0"]),          # [3H,E]
 "W_hh":  arr(sd["gru.weight_hh_l0"]),          # [3H,H]
 "B_ih":  arr(sd["gru.bias_ih_l0"]),            # [3H]
 "B_hh":  arr(sd["gru.bias_hh_l0"]),            # [3H]
 "W_out": arr(sd["out.weight"]),                # [V,H]
 "B_out": arr(sd["out.bias"]),                  # [V]
}
def emit(name, vals):
    body = ",".join(f"{v:.6g}f" for v in vals)
    return f'__attribute__((section(".weights"),used)) static const float {name}[{len(vals)}]={{{body}}};\n'
with open(os.path.join(HERE,"weights.h"),"w") as f:
    f.write(f"/* auto-generated char-GRU weights. V={V} E={E} H={H} */\n")
    f.write(f"#define V {V}\n#define E {E}\n#define H {H}\n")
    for k,v in W.items(): f.write(emit(k,v))
nparams = sum(len(v) for v in W.values())
print(f"wrote weights.h : {nparams} floats = {nparams*4} bytes")
