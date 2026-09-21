set -e
cd "$(dirname "$0")"
export PYTHONUNBUFFERED=1
COMMON="--distill --alpha 0.3 --no_aux --eval_every 2000 --patience 100 --sched wsd"
echo "=== $(date) 460k WSD 48k (new deployable pick) ==="
python nn_train.py --HF 184 --HS 96 --E 56 --FL 2 --lr 2.5e-3 --steps 48000 $COMMON --export --out_prefix nn_460k_wsd
echo "=== $(date) 256k WSD 48k (re-check mid) ==="
python nn_train.py --HF 200 --HS 80 --E 56 --FL 1 --lr 2.5e-3 --steps 48000 $COMMON --export --out_prefix nn_256k_wsd
echo "=== $(date) 128k batch512 WSD 48k (batch study) ==="
python nn_train.py --HF 132 --HS 48 --E 40 --FL 1 --lr 3.5e-3 --batch 512 --steps 48000 $COMMON --export --out_prefix nn_128k_b512
echo "=== $(date) RETRAIN DONE ==="
