// FUN_00026920 @00026920 size=142

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00026920(void)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = *(int *)(DAT_000269b0 + 0x1c);
  iVar6 = *(int *)(DAT_000269b0 + 0x20);
  iVar3 = *(int *)(DAT_000269b0 + 0x18);
  iVar4 = FUN_0003ddfc(0x2f);
  iVar1 = _DAT_000269b4;
  if (((iVar4 == 0) == (iVar5 != 0)) && (iVar4 = FUN_0003ddfc(0x2e), (iVar4 == 0) == (iVar6 != 0)))
  {
    iVar4 = FUN_0003ddfc(0x1c);
    if ((iVar4 == 0) && (iVar4 = FUN_0003dfe8(), iVar4 != 0)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2 == (iVar3 != 0)) {
      *(undefined4 *)(iVar1 + 0xc) = 0;
      return;
    }
  }
  iVar3 = *(int *)(iVar1 + 0xc) + 1;
  *(int *)(iVar1 + 0xc) = iVar3;
  if (iVar3 < 10) {
    return;
  }
  FUN_000277cc(s_mode_change_000269b7 + 1);
  FUN_00037fd0();
  FUN_0002cbd0(10);
  FUN_0002cd9c();
  return;
}

