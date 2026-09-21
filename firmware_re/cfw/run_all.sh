set -e
cd "$(dirname "$0")"
export PYTHONUNBUFFERED=1
echo "=== $(date) START teacher ==="
python nn_train.py --train_teacher --teacher_steps 7000
echo "=== $(date) START aux ablation ==="
python nn_train.py --ablate_aux --steps 6000
echo "=== $(date) START final student (distill+aux) ==="
python nn_train.py --steps 16000 --distill --T 1.5 --alpha 0.7 --aux_coef 0.3 --export
echo "=== $(date) ALL DONE ==="
