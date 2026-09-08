// @0x2bfe4  size=94

void FUN_0002bfe4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  
  iVar1 = DAT_0002c048;
  iVar2 = DAT_0002c044;
  if ((*(byte *)(DAT_0002c044 + 8) == 8) ||
     (*(char *)(DAT_0002c048 + (uint)*(byte *)(DAT_0002c044 + 8) * 8 + 0x2c2) == '\0')) {
    iVar3 = 0;
    do {
      bVar4 = *(char *)(iVar2 + 8) + 1;
      *(byte *)(iVar2 + 8) = bVar4;
      if (7 < bVar4) {
        *(undefined1 *)(iVar2 + 8) = 0;
      }
    } while ((*(char *)(iVar1 + (uint)*(byte *)(iVar2 + 8) * 8 + 0x2c2) == '\0') &&
            (iVar3 = iVar3 + 1, iVar3 < 8));
  }
  iVar2 = iVar1 + (uint)*(byte *)(iVar2 + 8) * 8;
  *(undefined2 *)(iVar1 + 0x272) = *(undefined2 *)(iVar2 + 0x2c6);
  *(undefined2 *)(iVar1 + 0x274) = *(undefined2 *)(iVar2 + 0x2c4);
  *(undefined2 *)(iVar1 + 0x276) = *(undefined2 *)(iVar2 + 0x2c8);
  FUN_0002e38c();
  return;
}

