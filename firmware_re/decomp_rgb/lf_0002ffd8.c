// FUN_0002ffd8 @0002ffd8 size=286

void FUN_0002ffd8(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = DAT_000300f8;
  if (param_1 == 0) {
    iVar2 = FUN_00029f38(*(undefined4 *)(DAT_000300f8 + 0x1c),*(undefined4 *)(DAT_000300f8 + 0x20),
                         0x1e);
    if (iVar2 != 0) {
      if (*(int *)(iVar1 + 0x1c) == 0) {
        *(undefined4 *)(iVar1 + 0x1c) = 0x1d;
      }
      else {
        *(int *)(iVar1 + 0x1c) = *(int *)(iVar1 + 0x1c) + -1;
      }
    }
    FUN_0001c590(DAT_00030104 + *(int *)(iVar1 + 0x1c) * 8,param_2,param_3);
    iVar2 = *(int *)(iVar1 + 0x1c);
    *(undefined4 *)(DAT_00030104 + 0xf3 + iVar2 * 4) = param_3;
    iVar2 = iVar2 + 1;
    *(int *)(iVar1 + 0x1c) = iVar2;
    if (0x1d < iVar2) {
      *(undefined4 *)(iVar1 + 0x1c) = 0;
    }
  }
  else if (param_1 == 3) {
    iVar2 = FUN_00029f38(*(undefined4 *)(DAT_000300f8 + 0x24),*(undefined4 *)(DAT_000300f8 + 0x28),
                         0x1e);
    if (iVar2 != 0) {
      if (*(int *)(iVar1 + 0x24) == 0) {
        *(undefined4 *)(iVar1 + 0x24) = 0x1d;
      }
      else {
        *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + -1;
      }
    }
    FUN_0001c590(*(int *)(iVar1 + 0x24) * 0xf + DAT_00030108,param_2,param_3);
    iVar2 = *(int *)(iVar1 + 0x24);
    *(undefined4 *)(DAT_0003010c + iVar2 * 4) = param_3;
    iVar2 = iVar2 + 1;
    *(int *)(iVar1 + 0x24) = iVar2;
    if (0x1d < iVar2) {
      *(undefined4 *)(iVar1 + 0x24) = 0;
    }
  }
  else if (param_1 == 1) {
    iVar2 = FUN_00029f38(*(undefined4 *)(DAT_000300f8 + 0x2c),*(undefined4 *)(DAT_000300f8 + 0x30),
                         0x1e);
    if (iVar2 != 0) {
      if (*(int *)(iVar1 + 0x2c) == 0) {
        *(undefined4 *)(iVar1 + 0x2c) = 0x1d;
      }
      else {
        *(int *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + -1;
      }
    }
    FUN_0001c590(DAT_0003010c + 0x78 + *(int *)(iVar1 + 0x2c) * 0x40,param_2,param_3);
    iVar2 = *(int *)(iVar1 + 0x2c);
    *(undefined4 *)(DAT_000300fc + -0x78 + iVar2 * 4) = param_3;
    iVar2 = iVar2 + 1;
    *(int *)(iVar1 + 0x2c) = iVar2;
    if (0x1d < iVar2) {
      *(undefined4 *)(iVar1 + 0x2c) = 0;
    }
  }
  else if (param_1 == 2) {
    iVar2 = FUN_00029f38(*(undefined4 *)(DAT_000300f8 + 0x34),*(undefined4 *)(DAT_000300f8 + 0x38),
                         0x28);
    iVar3 = *(int *)(iVar1 + 0x34);
    if (iVar2 != 0) {
      if (iVar3 == 0) {
        iVar3 = 0x27;
      }
      else {
        iVar3 = iVar3 + -1;
      }
      *(int *)(iVar1 + 0x34) = iVar3;
    }
    FUN_0001c590(iVar3 * 0x15 + DAT_000300fc,param_2,param_3);
    iVar2 = *(int *)(iVar1 + 0x34);
    *(undefined4 *)(DAT_00030100 + iVar2 * 4) = param_3;
    iVar2 = iVar2 + 1;
    *(int *)(iVar1 + 0x34) = iVar2;
    if (0x27 < iVar2) {
      *(undefined4 *)(iVar1 + 0x34) = 0;
    }
  }
  return;
}

