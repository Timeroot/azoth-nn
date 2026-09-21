set -e
cd "$(dirname "$0")"
export PYTHONUNBUFFERED=1
echo "=== $(date) (a) SPARSE-ANNEAL REDO (WSD long high-LR plateau, peak 2e-3) ==="
python run_lottery.py nn_460k 45000 0.94 2e-3 wsd lottery_wsd_results.csv
echo "=== $(date) SPARSE-REDO DONE ==="
echo "=== $(date) (b) UNROLLED RANK-1 vs STANDARD ==="
python run_rank1.py
echo "=== $(date) RANK1 DONE ==="
echo "=== $(date) QUEUE DONE ==="
