// @0x29534  size=76

void FUN_00029534(int param_1)

{
  int iVar1;
  ushort uVar2;
  
  uVar2 = 0;
  if (*(int *)(*(int *)(param_1 + 4) + 0x500) == 6) {
    do {
      iVar1 = FUN_00029ff8(param_1);
      if (iVar1 == 0) break;
      FUN_0002cbd0(1);
      uVar2 = uVar2 + 1;
    } while (uVar2 < 10);
    FUN_0003f3bc(param_1 + 4);
    FUN_0003f568(param_1 + 4);
  }
  if (param_1 == DAT_00029580) {
    *(undefined1 *)(DAT_00029584 + 2) = 0;
  }
  else if (param_1 == DAT_00029580 + 0x10) {
    *(undefined1 *)(DAT_00029584 + 3) = 0;
    return;
  }
  return;
}

