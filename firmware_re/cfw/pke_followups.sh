#!/usr/bin/env bash
# Exploratory FOLLOW-UPS, run AFTER the 400KB confirm headline (waits for it; never
# blocks it). Single writer resumes into pke_results.csv. Order: fixed sparse-high-dim
# (hard L1 anneal + STE prune) -> fuse_ft (2-branch training curriculum).
cd "$(dirname "$0")" || exit 1
until grep -q "=== pke_chain done" pke_run.log 2>/dev/null; do sleep 60; done
echo "=== followups start $(date) ===" >> pke_run.log
python -u run_pke.py --phase sparse2 >> pke_run.log 2>&1
python -u run_pke.py --phase fuse    >> pke_run.log 2>&1
echo "=== followups done $(date) ===" >> pke_run.log
