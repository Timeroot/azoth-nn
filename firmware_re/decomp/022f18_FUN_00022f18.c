// @0x22f18  size=52

void FUN_00022f18(int param_1)

{
  FUN_0001c5e0(param_1 + 4,0x1ee);
  *(byte *)(param_1 + 0xd) = (*(byte *)(param_1 + 0xd) & 7) + 8 & 0xf8;
  *(undefined1 *)(param_1 + 0xc) = 7;
  *(byte *)(param_1 + 0x13) = (*(byte *)(param_1 + 0x13) & 7) + 8 & 0xf8;
  *(undefined1 *)(param_1 + 0x12) = 4;
  return;
}

