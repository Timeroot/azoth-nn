// FUN_000298c4 @000298c4 size=98

void FUN_000298c4(byte *param_1,byte *param_2)

{
  int iVar1;
  
  iVar1 = DAT_00029928;
  if (param_1 != (byte *)0x0 || param_2 != (byte *)0x0) {
    if (param_1 != (byte *)0x0) {
      if ((*(byte *)(DAT_00029928 + 2) & 2) != (*param_1 & 2)) {
        FUN_0002e274(1);
      }
      if ((*(byte *)(iVar1 + 2) & 4) != (*param_1 & 4)) {
        FUN_0002e274(2);
      }
      *(byte *)(iVar1 + 2) = *param_1 & 7 | *(byte *)(iVar1 + 2) & 0xf8;
    }
    if (param_2 != (byte *)0x0) {
      *(byte *)(iVar1 + 2) = (*param_2 & 5) << 3 | *(byte *)(iVar1 + 2) & 199;
    }
  }
  return;
}

