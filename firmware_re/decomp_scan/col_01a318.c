// @0x1a318 size=48

undefined4 FUN_0001a318(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  if (*DAT_0001a45c == DAT_0001a460) {
    if (0x10 < param_1) {
      return 0x2008;
    }
  }
  else if (0x13 < param_1) {
    return 0x2008;
  }
  iVar1 = DAT_0001a468 + param_1 * 8;
  *(undefined4 *)(iVar1 + 0x510) = param_2;
  *(undefined4 *)(iVar1 + 0x514) = param_3;
  return 0;
}

