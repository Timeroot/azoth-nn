// @0x149a4 size=38

void FUN_000149a4(uint param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_00014a54 + param_1 * 8;
  *(int *)(iVar2 + 0x510) = DAT_00014a2c + -0xc;
  *(undefined4 *)(iVar2 + 0x514) = param_2;
  uVar1 = 1 << (param_1 & 0xff);
  *DAT_00014a30 = uVar1;
  *(uint *)(DAT_00014a38 + 0x38) = *(uint *)(DAT_00014a38 + 0x38) | uVar1;
  return;
}

