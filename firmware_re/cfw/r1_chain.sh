#!/usr/bin/env bash
# Remaining rank-1 head study, single-process sequential, resumable (each phase skips if
# its _r1_ckpt exists / row present). p1_std matches p1_rank1 batch (160); the joint p2
# runs use the smaller batch 128 (more activations when branches unfrozen). Works around
# the wedged CUDA context (~3.9GB) via checkpointing + small batch.
cd "$(dirname "$0")" || exit 1
export PYTORCH_CUDA_ALLOC_CONF=expandable_segments:True
run() { echo "=== $1 start $(date) ===" >> pke_run.log
        python -u run_pke.py --phase rank1head --r1_variant "$2" --r1_phase "$3" --r1_batch "$4" >> pke_run.log 2>&1
        echo "=== $1 done $(date) ===" >> pke_run.log; }
run r1_std_p1    std   p1 160
run r1_rank1_p2  rank1 p2 128
run r1_std_p2    std   p2 128
echo "=== r1_chain done $(date) ===" >> pke_run.log
