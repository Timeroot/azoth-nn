// @0x2c144  size=48

void FUN_0002c144(int param_1)

{
  ushort uVar1;
  
  if (param_1 - 0xd4U < 3) {
    uVar1 = *DAT_0002c174 | 0xa000;
    if (param_1 == 0xd4) {
      *(ushort *)(DAT_0002c178 + 0x2fe) = uVar1;
      return;
    }
    if (param_1 == 0xd5) {
      *(ushort *)(DAT_0002c178 + 0x2fc) = uVar1;
      return;
    }
    if (param_1 == 0xd6) {
      *(ushort *)(DAT_0002c178 + 0x300) = uVar1;
    }
  }
  return;
}

