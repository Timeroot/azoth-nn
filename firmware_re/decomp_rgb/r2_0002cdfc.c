// FUN_0002cdfc @0002cdfc size=150

int FUN_0002cdfc(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_000403a4();
  iVar1 = DAT_0002ce74;
  iVar3 = DAT_0002ce70;
  if (param_1 == 1) {
    return iVar2;
  }
  if (param_1 == 2) {
    FUN_000432e8(0xd3);
    if (*(int *)(iVar3 + 0x5c) != 0) {
      *(undefined4 *)(iVar1 + 0x18) = 1;
      *(undefined4 *)(iVar1 + 0x1c) = 1;
      return 1;
    }
    iVar3 = 5000;
  }
  else {
    if (param_1 != 4) {
      return iVar2;
    }
    if (*(int *)(DAT_0002ce74 + 0x18) != 2) {
      return *(int *)(DAT_0002ce74 + 0x18);
    }
    iVar2 = FUN_00034674();
    if ((iVar2 == 0) || (*(int *)(iVar3 + 4) == 0)) {
      *(undefined4 *)(iVar1 + 0x18) = 4;
      *(undefined4 *)(iVar1 + 0x1c) = 1000;
      return 0;
    }
    if ((*DAT_0002ce78 == 0) || (*DAT_0002ce78 == *(int *)(iVar1 + 0x20))) {
      *(undefined4 *)(iVar1 + 0x18) = 4;
      *(undefined4 *)(iVar1 + 0x1c) = 1000;
      iVar3 = FUN_0003481c(1);
      if ((iVar3 != 0) || (iVar3 = 0, *DAT_00035408 != '\0')) {
        FUN_00034a90(&stack0xfffffff8);
        iVar3 = 1;
      }
      return iVar3;
    }
    iVar3 = 0x32;
  }
  *(undefined4 *)(iVar1 + 0x18) = 2;
  *(int *)(iVar1 + 0x1c) = iVar3;
  return iVar3;
}

