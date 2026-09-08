// FUN_00030f3c @00030f3c size=96

void FUN_00030f3c(uint param_1)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  
  bVar1 = (byte)(1 << (param_1 & 7));
  if (param_1 - 4 < 0x7c) {
    pbVar2 = (byte *)(DAT_00030f9c + (param_1 >> 3));
    *pbVar2 = *pbVar2 | bVar1;
    return;
  }
  if (7 < param_1 - 0xe0) {
    if (param_1 == 0xe8) {
      *(byte *)(DAT_00030f9c + 0x11) = *(byte *)(DAT_00030f9c + 0x11) | 1;
      return;
    }
    uVar3 = param_1 - 0x87;
    if (4 < uVar3) {
      if (1 < param_1 - 0x90) {
        return;
      }
      uVar3 = param_1 - 0x8b;
    }
    *(byte *)(DAT_00030f9c + 0xe) = *(byte *)(DAT_00030f9c + 0xe) | (byte)(1 << (uVar3 & 0xff));
    return;
  }
  *(byte *)(DAT_00030f9c + 0x10) = *(byte *)(DAT_00030f9c + 0x10) | bVar1;
  return;
}

