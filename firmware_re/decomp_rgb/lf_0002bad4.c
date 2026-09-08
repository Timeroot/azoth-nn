// FUN_0002bad4 @0002bad4 size=66

void FUN_0002bad4(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    FUN_0001c5e0(DAT_0002bb18,0x18);
    return;
  }
  if (param_1 - 0xe0U < 8) {
    param_1 = param_1 + -0x70;
  }
  else if (0x8d < param_1 - 4U) {
    return;
  }
  if (param_1 != 0) {
    uVar1 = (uint)(*(byte *)(DAT_0002bb1c + param_1) >> 4);
    *(ushort *)(DAT_0002bb18 + uVar1 * 2) =
         *(ushort *)(DAT_0002bb18 + uVar1 * 2) |
         (ushort)(1 << (*(byte *)(DAT_0002bb1c + param_1) & 0xf));
  }
  return;
}

