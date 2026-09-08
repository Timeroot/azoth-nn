
void FUN_0003dc00(uint param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = param_1;
  iVar1 = FUN_0003dcf0(&local_8);
  *(int *)(iVar1 + 0x50c) = 1 << (local_8 & 0xff);
  return;
}

