// @0x3dbb8 size=20

void FUN_0003dbb8(uint param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = param_1;
  iVar1 = FUN_0003dcb8(&local_8);
  *(int *)(iVar1 + 0x50c) = 1 << (local_8 & 0xff);
  return;
}

