// @0x3ded4 size=20

void FUN_0003ded4(uint param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = param_1;
  iVar1 = FUN_0003dd7c(&local_8);
  *(int *)(iVar1 + 0x508) = 1 << (local_8 & 0xff);
  return;
}

