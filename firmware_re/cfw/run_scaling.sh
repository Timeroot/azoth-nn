set -e
cd "$(dirname "$0")"
export PYTHONUNBUFFERED=1
COMMON="--distill --alpha 0.3 --T 1.5 --no_aux --steps 24000 --eval_every 1000 --patience 8 --export"
echo "=== $(date) 128k ==="
python nn_train.py --HF 132 --HS 48 --E 40 --FL 1 --out_prefix nn_128k $COMMON
echo "=== $(date) 256k ==="
python nn_train.py --HF 200 --HS 80 --E 56 --FL 1 --out_prefix nn_256k $COMMON
echo "=== $(date) 400k ==="
python nn_train.py --HF 256 --HS 96 --E 64 --FL 1 --out_prefix nn_400k $COMMON
echo "=== $(date) 256k_fl2 (arch: 2-layer fast) ==="
python nn_train.py --HF 130 --HS 72 --E 56 --FL 2 --out_prefix nn_256k_fl2 $COMMON
echo "=== $(date) SCALING DONE ==="
