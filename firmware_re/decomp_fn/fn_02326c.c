// @0x2326c size=152

void FUN_0002326c(uint param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = DAT_00023304;
  bVar1 = *(byte *)(DAT_00023304 + 0x81);
  if ((bVar1 & 1) != 0) {
    FUN_0001c5e0(DAT_00023304 + 1,0x38);
    *(byte *)(iVar3 + 0x81) = bVar1 & 0xfe;
  }
  bVar1 = *(byte *)(iVar3 + 0x81);
  if ((int)((uint)bVar1 << 0x1e) < 0) {
    FUN_0001c5e0(DAT_00023304 + 0x39,0x38);
    *(byte *)(iVar3 + 0x81) = bVar1 & 0xfd;
  }
  bVar1 = *(byte *)(iVar3 + 0x81);
  if ((int)((uint)bVar1 << 0x1d) < 0) {
    FUN_0001c5e0(DAT_00023304 + 0x71,0x10);
    *(byte *)(iVar3 + 0x81) = bVar1 & 0xfb;
  }
  if (param_1 - 4 < 0x8e) {
    iVar2 = (uint)*(byte *)(DAT_00023308 + param_1 * 2) * 8 + 1;
    iVar3 = (uint)*(byte *)(DAT_00023308 + param_1 * 2 + 1) + iVar3;
    *(char *)(iVar3 + iVar2) = *(char *)(iVar3 + iVar2) + '\x01';
  }
  else if (param_1 - 0xe0 < 8) {
    iVar2 = (uint)*(byte *)(DAT_00023308 + (param_1 & 0xaf) * 2) * 8 + 1;
    iVar3 = (uint)*(byte *)(DAT_00023308 + (param_1 & 0xaf) * 2 + 1) + iVar3;
    *(char *)(iVar3 + iVar2) = *(char *)(iVar3 + iVar2) + '\x01';
    return;
  }
  return;
}

