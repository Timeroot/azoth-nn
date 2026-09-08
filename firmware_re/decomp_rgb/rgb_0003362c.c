// FUN_0003362c @0003362c size=38

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0003362c(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  int iVar1;
  int iVar2;
  
  FUN_0001c5e0(DAT_00033654,0x15);
  iVar2 = DAT_00033654;
  *(undefined1 *)(DAT_00033654 + 1) = param_1;
  *(undefined1 *)(iVar2 + 2) = param_2;
  *(undefined1 *)(iVar2 + 3) = param_3;
  *(undefined1 *)(iVar2 + 4) = param_4;
  iVar1 = _DAT_00029cec;
  FUN_0001c590(*(int *)(_DAT_00029cec + 0x14) * 0x15 + _DAT_00029cf0,iVar2,0x15);
  iVar2 = *(int *)(iVar1 + 0x14) - *(int *)(iVar1 + 0x18);
  if (((iVar2 != -1) && (iVar2 < 2)) &&
     (iVar2 = *(int *)(iVar1 + 0x14) + 1, *(int *)(iVar1 + 0x14) = iVar2, 2 < iVar2)) {
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  return;
}

