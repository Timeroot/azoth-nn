// @0x329d4  size=38

void FUN_000329d4(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_000329fc;
  if (param_1 == 0) {
    *(undefined4 *)(DAT_000329fc + 0x14) = 0;
  }
  else {
    *(uint *)(DAT_000329fc + 0x14) =
         *(ushort *)(DAT_00032a04 + (*(byte *)(DAT_00032a00 + 0x2b9) & 7) * 2) / 0x1e;
  }
  *(undefined4 *)(iVar1 + 0x10) = 0;
  return;
}

