// @0x3df10 size=34

void FUN_0003df10(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint local_8;
  
  local_8 = param_1;
  iVar1 = FUN_0003dc9c(&local_8);
  uVar2 = 1 << (local_8 & 0xff);
  *(uint *)(iVar1 + 0x508) = uVar2 & ~*(uint *)(iVar1 + 0x504);
  *(uint *)(iVar1 + 0x50c) = uVar2 & *(uint *)(iVar1 + 0x504);
  return;
}

