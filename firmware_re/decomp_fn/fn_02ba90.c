// @0x2ba90 size=54

undefined1 FUN_0002ba90(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_0002bac8;
  if (param_1 == 0xd3) {
    if (*(char *)(DAT_0002bac8 + 2) == '\0') {
      *(undefined1 *)(DAT_0002bac8 + 1) = 1;
    }
    if (*(char *)(DAT_0002bacc + 0x20) == '\0') {
      iVar2 = DAT_0002bacc + (uint)(*(byte *)(DAT_0002bad0 + 0xa3) >> 4) * 2;
      *(ushort *)(iVar2 + 2) =
           *(ushort *)(iVar2 + 2) | (ushort)(1 << (*(byte *)(DAT_0002bad0 + 0xa3) & 0xf));
    }
  }
  return *(undefined1 *)(iVar1 + 1);
}

