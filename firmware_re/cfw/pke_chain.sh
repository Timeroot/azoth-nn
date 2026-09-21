#!/usr/bin/env bash
# Detached, resumable PKE study chain. Single writer to pke_results.csv.
# EDGE-INFERENCE methodology: every point is trained TO CONVERGENCE (WSD plateau ->
# held-out-triggered decay, generous patience, best checkpoint). Undertraining is the
# #1 risk; the trainer flags any config that hit the step cap while still improving.
# Each phase skips already-done (variant,config,seed) rows, so a reboot loses at most
# the in-flight config; just re-launch this script.
# Order: baseline GRU frontier -> replace_fmlp (PRIORITY) -> addstate/concat/replace
#        -> standalone -> sparse -> 400KB confirm (3 seeds).
cd "$(dirname "$0")" || exit 1
echo "=== pke_chain start $(date) ===" >> pke_run.log
python -u run_pke.py --phase base       >> pke_run.log 2>&1
python -u run_pke.py --phase fmlp       >> pke_run.log 2>&1
python -u run_pke.py --phase gru        >> pke_run.log 2>&1
python -u run_pke.py --phase standalone >> pke_run.log 2>&1
python -u run_pke.py --phase sparse     >> pke_run.log 2>&1
python -u run_pke.py --phase confirm --seeds 0 1 2 >> pke_run.log 2>&1
echo "=== pke_chain done $(date) ===" >> pke_run.log
