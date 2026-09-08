// @0x3db90 size=20

void FUN_0003db90(uint param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = param_1;
  iVar1 = FUN_0003dc64(&local_8);
  *(int *)(iVar1 + 0x50c) = 1 << (local_8 & 0xff);
  return;
}

