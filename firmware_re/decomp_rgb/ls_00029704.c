// FUN_00029704 @00029704 size=46

int FUN_00029704(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_00029734;
  if (0 < *(int *)(DAT_00029734 + 0xc)) {
    return 1;
  }
  iVar2 = FUN_000297c4(DAT_00029738,param_3,param_1,param_2,0);
  if (iVar2 != 0) {
    *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + 1;
    return iVar2;
  }
  *(undefined4 *)(iVar1 + 0xc) = 0;
  return 0;
}

