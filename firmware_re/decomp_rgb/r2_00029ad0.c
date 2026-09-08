// FUN_00029ad0 @00029ad0 size=198

void FUN_00029ad0(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = 0;
  do {
    while( true ) {
      FUN_0002cbd0(10);
      iVar1 = FUN_0003ddfc(0x1c);
      if ((iVar1 == 0) && (iVar1 = FUN_0003dfe8(), iVar1 != 0)) {
        iVar1 = 1;
      }
      else {
        iVar1 = 0;
      }
      if (iVar1 == iVar5) break;
      iVar4 = FUN_0003ddfc(0x1c);
      if ((iVar4 == 0) && (iVar4 = FUN_0003dfe8(), iVar4 != 0)) {
        iVar5 = 1;
      }
      else {
        iVar5 = 0;
      }
      iVar4 = 1;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 10);
  iVar4 = FUN_0003ddfc(0x1c);
  if ((iVar4 == 0) && (iVar4 = FUN_0003dfe8(), iVar4 != 0)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  iVar4 = DAT_00029b98;
  *(undefined4 *)(DAT_00029b98 + 0x18) = uVar2;
  iVar5 = FUN_0003ddfc(0x2f);
  *(uint *)(iVar4 + 0x1c) = (uint)(iVar5 == 0);
  iVar5 = FUN_0003ddfc(0x2e);
  *(uint *)(iVar4 + 0x20) = (uint)(iVar5 == 0);
  if (*(int *)(iVar4 + 0x1c) == 0) {
    if (*(int *)(iVar4 + 0x20) == 0) {
      if (*(int *)(iVar4 + 0x18) == 0) goto LAB_00029b70;
      uVar3 = *DAT_00029b9c | 4;
    }
    else {
      uVar3 = *DAT_00029b9c | 1;
    }
  }
  else {
    uVar3 = *DAT_00029b9c | 2;
  }
  *DAT_00029b9c = uVar3;
LAB_00029b70:
  if (*(int *)(iVar4 + 0x18) == 0) {
    if (*(int *)(iVar4 + 0x1c) != 0) {
      FUN_0003dabe(0x2f,0);
    }
    if (*(int *)(iVar4 + 0x20) != 0) {
      FUN_0003dabe(0x2e,0);
      return;
    }
  }
  return;
}

