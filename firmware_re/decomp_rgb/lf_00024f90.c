// FUN_00024f90 @00024f90 size=108

void FUN_00024f90(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    FUN_0001c5e0(DAT_00024ffc,0x17);
    return;
  }
  if (param_1 - 4 < 0x8e) {
    uVar1 = (uint)*(byte *)(DAT_00025000 + param_1 * 2);
    *(byte *)(uVar1 + DAT_00024ffc) =
         *(byte *)(uVar1 + DAT_00024ffc) | (byte)(1 << *(sbyte *)(DAT_00025000 + param_1 * 2 + 1));
  }
  else if (param_1 - 0xe0 < 8) {
    uVar1 = (uint)*(byte *)(DAT_00025000 + (param_1 & 0xaf) * 2);
    *(byte *)(uVar1 + DAT_00024ffc) =
         *(byte *)(uVar1 + DAT_00024ffc) |
         (byte)(1 << *(sbyte *)(DAT_00025000 + (param_1 & 0xaf) * 2 + 1));
  }
  else if (param_1 == 0xe8) {
    *(byte *)((uint)*(byte *)(DAT_00025000 + 0x150) + DAT_00024ffc) =
         *(byte *)((uint)*(byte *)(DAT_00025000 + 0x150) + DAT_00024ffc) |
         (byte)(1 << *(sbyte *)(DAT_00025000 + 0x151));
  }
  return;
}

