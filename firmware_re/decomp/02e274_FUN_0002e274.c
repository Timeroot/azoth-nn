// @0x2e274  size=14

void FUN_0002e274(uint param_1)

{
  uint *puVar1;
  int iVar2;
  
  iVar2 = DAT_0002e284;
  puVar1 = (uint *)(DAT_0002e284 + 0x38);
  *(undefined4 *)(DAT_0002e284 + 0x34) = 6;
  *(uint *)(iVar2 + 0x38) = *puVar1 | param_1;
  return;
}

