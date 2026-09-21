#!/usr/bin/env bash
# GENTLE long continue-train of the stabilized rank1-p2 head, with non-destructive
# annealed readouts at ~60k/140k/200k to show the trend vs 3.316 (own start) / 3.314
# (bare fuse). Single-process sequential; checkpointed/continuable; clip 0.5 throughout.
cd "$(dirname "$0")" || exit 1
export PYTORCH_CUDA_ALLOC_CONF=expandable_segments:True
P="python -u run_pke.py --phase r1ext"
echo "=== r1ext_chain start $(date) ===" >> pke_run.log
$P --r1ext_mode extend --r1ext_steps 60000                  >> pke_run.log 2>&1
$P --r1ext_mode readout                                     >> pke_run.log 2>&1
$P --r1ext_mode extend --r1ext_cont --r1ext_steps 140000    >> pke_run.log 2>&1
$P --r1ext_mode readout                                     >> pke_run.log 2>&1
$P --r1ext_mode extend --r1ext_cont --r1ext_steps 200000    >> pke_run.log 2>&1
$P --r1ext_mode readout                                     >> pke_run.log 2>&1
echo "=== r1ext_chain done $(date) ===" >> pke_run.log
