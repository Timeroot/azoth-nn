#!/usr/bin/env bash
# Phase 2 (joint finetune) RE-RUN at a GENTLE finetune LR (3e-4) so it refines the 3.314
# basin instead of the 2.5e-3 plateau blowing it out. Each p2 loads its p1 head ckpt as
# start, unfreezes all. Single-process sequential; B=128 to fit the ~4GB free.
cd "$(dirname "$0")" || exit 1
export PYTORCH_CUDA_ALLOC_CONF=expandable_segments:True
run() { echo "=== $1 start $(date) ===" >> pke_run.log
        python -u run_pke.py --phase rank1head --r1_variant "$2" --r1_phase p2 --r1_batch 128 --r1_lr 3e-4 >> pke_run.log 2>&1
        echo "=== $1 done $(date) ===" >> pke_run.log; }
run r1_rank1_p2 rank1
run r1_std_p2   std
echo "=== r1_chain2 done $(date) ===" >> pke_run.log
