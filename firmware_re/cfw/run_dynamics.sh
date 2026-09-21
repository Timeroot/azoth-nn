set -e
cd "$(dirname "$0")"
export PYTHONUNBUFFERED=1
C128="--HF 132 --HS 48 --E 40 --FL 1 --distill --alpha 0.3 --no_aux --eval_every 2000 --patience 100"
echo "=== $(date) A: 128k cosine 48k (2x horizon) ==="
python nn_train.py $C128 --steps 48000 --sched cosine --lr 2e-3 --out_prefix nn_dyn_128k_cos48
echo "=== $(date) B: 128k WSD 48k (long high-LR plateau) ==="
python nn_train.py $C128 --steps 48000 --sched wsd --lr 2.5e-3 --out_prefix nn_dyn_128k_wsd48
echo "=== $(date) DYNAMICS-AB DONE ==="
