// @0x3dbe0 size=26

void FUN_0003dbe0(uint param_1)

{
  int iVar1;
  
  if (param_1 < 0x20) {
    iVar1 = 0x50000000;
  }
  else {
    param_1 = param_1 & 0x1f;
    iVar1 = DAT_0003dbfc;
  }
  *(int *)(iVar1 + 0x50c) = 1 << (param_1 & 0xff);
  return;
}

