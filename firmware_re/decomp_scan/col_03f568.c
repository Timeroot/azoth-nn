// @0x3f568 size=108

void FUN_0003f568(int *param_1)

{
  uint uVar1;
  int *piVar2;
  
  piVar2 = (int *)(DAT_0003f5d4 + (uint)*(byte *)(param_1 + 1) * 0x34);
  if ((*piVar2 != 0) && (uVar1 = (*param_1 << 0xc) >> 0x18, -1 < (int)uVar1)) {
    *(int *)(&DAT_e000e180 + (uVar1 >> 5) * 4) = 1 << (uVar1 & 0x1f);
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
  }
  FUN_0003f3bc(param_1);
  FUN_0003ec96(*param_1);
  if (*(char *)((int)piVar2 + 0x32) == '\0') {
    FUN_0003da9a(*(undefined4 *)(*param_1 + 0x508));
    FUN_0003da9a(*(undefined4 *)(*param_1 + 0x50c));
  }
  *(undefined1 *)((int)piVar2 + 0x2d) = 0;
  return;
}

