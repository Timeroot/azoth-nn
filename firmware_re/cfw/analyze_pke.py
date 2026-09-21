#!/usr/bin/env python3
"""Summarize pke_results.csv: per-config aggregation (mean+-std over seeds), the
accuracy-per-deployed-KB Pareto frontier per variant, and the 400KB operating-point
comparison (baseline GRU vs PKE integrations). Also pulls the shipped dense-GRU
scaling points from frontier_results.csv (same held-out set) as the reference
'spend bytes on more GRU' curve. Read-only; safe to run anytime."""
import os, csv, collections, math
HERE = os.path.dirname(os.path.abspath(__file__))
CSV = os.path.join(HERE, "pke_results.csv")
FR  = os.path.join(HERE, "frontier_results.csv")

def load():
    if not os.path.exists(CSV): return []
    return list(csv.DictReader(open(CSV)))

def agg(rows):
    """group by (variant,config) -> mean/std of ppl,t1,t3 over seeds."""
    g = collections.defaultdict(list)
    for r in rows: g[(r["variant"], r["config"])].append(r)
    out = []
    for (v,c), rs in g.items():
        ppl = [float(r["ppl"]) for r in rs]; t1=[float(r["t1"]) for r in rs]
        t3=[float(r["t3"]) for r in rs]; fppl=[float(r["float_ppl"]) for r in rs]
        n=len(ppl); mean=lambda a: sum(a)/len(a)
        std=lambda a: (sum((x-mean(a))**2 for x in a)/len(a))**.5 if len(a)>1 else 0.0
        out.append(dict(variant=v, config=c, kb=float(rs[0]["kb"]),
                        kb_int8=float(rs[0]["kb_int8"]), kb_pke=float(rs[0]["kb_pke"]),
                        n=n, ppl=mean(ppl), ppl_std=std(ppl), fppl=mean(fppl),
                        t1=mean(t1), t3=mean(t3), macc=int(rs[0]["macc"])))
    return out

def pareto(points):
    """non-dominated by (kb small, ppl small)."""
    pts = sorted(points, key=lambda p:(p["kb"], p["ppl"]))
    front=[]; best=1e9
    for p in pts:
        if p["ppl"] < best - 1e-9:
            front.append(p); best=p["ppl"]
    return front

def main():
    rows = load()
    print(f"pke_results.csv: {len(rows)} rows\n")
    A = agg(rows)
    for variant in ["standalone","gru","confirm"]:
        vs = sorted([a for a in A if a["variant"]==variant], key=lambda a:a["kb"])
        if not vs: continue
        print(f"==== {variant} ({len(vs)} configs) ====")
        print(f"  {'config':32s} {'KB':>7s} {'pke':>6s} {'int8ppl':>8s} {'std':>6s} "
              f"{'float':>7s} {'t1':>6s} {'t3':>6s} {'n':>2s}")
        for a in vs:
            print(f"  {a['config']:32s} {a['kb']:7.1f} {a['kb_pke']:6.2f} {a['ppl']:8.3f} "
                  f"{a['ppl_std']:6.3f} {a['fppl']:7.3f} {a['t1']:6.3f} {a['t3']:6.3f} {a['n']:2d}")
        print()

    # shipped dense-GRU reference (same eval set) from frontier_results.csv
    if os.path.exists(FR):
        dn = [r for r in csv.DictReader(open(FR)) if r["approach"]=="dense_nn"]
        if dn:
            print("==== shipped dense GRU (frontier_results.csv, same eval set, ref) ====")
            for r in sorted(dn, key=lambda r:float(r["kb"])):
                print(f"  {r['name']:12s} {float(r['kb']):7.1f}KB  ppl {float(r['ppl']):.3f} "
                      f"t1 {float(r['t1']):.3f} t3 {float(r['t3']):.3f}")
            print()

    # Pareto: baseline GRU vs all PKE-integrated (this-harness, matched budget)
    base = [a for a in A if a["variant"]=="gru" and a["config"].startswith("base_")]
    pke  = [a for a in A if a["variant"]=="gru" and not a["config"].startswith("base_")]
    if base:
        print("==== Pareto frontier: baseline GRU (matched-budget, this harness) ====")
        for p in pareto(base):
            print(f"  {p['kb']:7.1f}KB  ppl {p['ppl']:.3f}  t1 {p['t1']:.3f}  ({p['config']})")
    if pke:
        print("==== Pareto frontier: PKE-integrated GRU ====")
        for p in pareto(pke):
            print(f"  {p['kb']:7.1f}KB  ppl {p['ppl']:.3f}  t1 {p['t1']:.3f}  ({p['config']})")
    if base and pke:
        print("==== combined Pareto (GRU + PKE) ====")
        for p in pareto(base+pke):
            tag = "PKE" if not p["config"].startswith("base_") else "GRU"
            print(f"  {p['kb']:7.1f}KB  ppl {p['ppl']:.3f}  [{tag}] {p['config']}")

    # 400KB operating point
    conf = [a for a in A if a["variant"]=="confirm"]
    if conf:
        print("\n==== 400KB OPERATING POINT (confirm, mean+-std over seeds) ====")
        for a in sorted(conf, key=lambda a:a["config"]):
            print(f"  {a['config']:24s} {a['kb']:7.1f}KB  int8 ppl {a['ppl']:.3f} +-{a['ppl_std']:.3f}"
                  f"  float {a['fppl']:.3f}  t1 {a['t1']:.3f}  t3 {a['t3']:.3f}  (n={a['n']})")

if __name__ == "__main__":
    main()
