#!/usr/bin/env python3
"""Collect nn_*_metrics.json into a scaling table; append rows to scaling_results.csv."""
import os, json, glob, csv
HERE = os.path.dirname(os.path.abspath(__file__))
ORDER = ["nn_460k", "nn_400k", "nn_256k", "nn_256k_fl2", "nn_128k", "nn_64k"]
rows = []
for pre in ORDER:
    mp = os.path.join(HERE, pre + "_metrics.json")
    if not os.path.exists(mp):
        continue
    m = json.load(open(mp)); c = m["cfg"]; f = m["float"]; q = m["int8"]
    rows.append(dict(model=pre, KB=round(c["bytes"]/1024, 1), HF=c["HF"], HS=c["HS"],
                     E=c["E"], FL=c.get("FL", 1), state_B=c.get("state_bytes", (c.get("FL",1)*c["HF"]+c["HS"])*4),
                     macC=c.get("macc", 0),
                     float_ppl=round(f["ppl"], 3), float_t1=round(f["top1"], 4), float_t3=round(f["top3"], 4),
                     int8_ppl=round(q["ppl"], 3), int8_t1=round(q["top1"], 4), int8_t3=round(q["top3"], 4)))
if rows:
    with open(os.path.join(HERE, "scaling_results.csv"), "w", newline="") as fh:
        w = csv.DictWriter(fh, fieldnames=list(rows[0].keys())); w.writeheader(); w.writerows(rows)
    print(f"{'model':12s} {'KB':>6s} {'HFxFL/HS/E':>12s} {'stB':>5s} {'macC':>7s} "
          f"{'fppl':>6s} {'ft1':>6s} {'ft3':>6s} {'qppl':>6s} {'qt1':>6s} {'qt3':>6s}")
    for r in rows:
        print(f"{r['model']:12s} {r['KB']:6.1f} {str(r['HF'])+'x'+str(r['FL'])+'/'+str(r['HS'])+'/'+str(r['E']):>12s} "
              f"{r['state_B']:5d} {r['macC']:7d} {r['float_ppl']:6.3f} {r['float_t1']:6.4f} "
              f"{r['float_t3']:6.4f} {r['int8_ppl']:6.3f} {r['int8_t1']:6.4f} {r['int8_t3']:6.4f}")
else:
    print("no metrics yet")
