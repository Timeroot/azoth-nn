// @0x26024  size=108

void FUN_00026024(undefined4 param_1,undefined2 *param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint in_fpscr;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint local_18;
  
  local_18 = param_4;
  FUN_0002cb20(2);
  uVar2 = 0;
  iVar1 = 0;
  do {
    FUN_0002cb54(2,&local_18);
    iVar1 = iVar1 + 1;
    uVar2 = uVar2 + (local_18 & 0xffff);
  } while (iVar1 < 0xfa);
  FUN_0002cb0c(2);
  fVar3 = (float)VectorUnsignedToFloat(param_1,(byte)(in_fpscr >> 0x16) & 3);
  fVar4 = (float)VectorUnsignedToFloat((uVar2 / 0xfa) * 0x708,(byte)(in_fpscr >> 0x16) & 3);
  uVar5 = VectorFloatToUnsigned(((fVar3 * DAT_00026090) / fVar4) * DAT_00026094,3);
  *(short *)(DAT_00026098 + 6) = (short)uVar5;
  *param_2 = (short)uVar5;
  param_2[1] = (short)(uVar2 / 0xfa);
  return;
}

