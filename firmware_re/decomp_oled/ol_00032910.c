// FUN_00032910 @00032910 size=20

void FUN_00032910(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = DAT_00032924;
  *(undefined4 *)(DAT_00032924 + 0x5c) = param_1;
  *(undefined2 *)(iVar1 + -0x40 + (uint)*(byte *)(iVar1 + -0x7b) * 2) = 0;
  return;
}

