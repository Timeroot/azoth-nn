// @0x3de12 size=22

uint FUN_0003de12(uint param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = param_1;
  iVar1 = FUN_0003dd44(&local_8);
  return *(uint *)(iVar1 + 0x510) >> (local_8 & 0xff) & 1;
}

