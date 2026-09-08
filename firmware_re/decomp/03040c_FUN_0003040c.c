// @0x3040c  size=66

undefined4 FUN_0003040c(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  FUN_0002cc30(&DAT_000d5000,param_1,param_2);
  for (iVar1 = 0; iVar1 < param_2; iVar1 = iVar1 + 1) {
  }
  uVar2 = FUN_00044cd8(param_1,param_2 + -4);
  if (((uVar2 & 0xff) == (uint)*(byte *)(param_1 + param_2 + -4)) &&
     (uVar2 >> 8 == (uint)*(byte *)(param_1 + param_2 + -3))) {
    return 1;
  }
  return 0;
}

