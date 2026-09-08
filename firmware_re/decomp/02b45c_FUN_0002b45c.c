// @0x2b45c  size=100

void FUN_0002b45c(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = DAT_0002b4c0;
  if (*(int *)(DAT_0002b4c0 + 0x18) == 0) {
    bVar1 = *(byte *)(DAT_0002b4c8 + 0x2b8);
    if (*(int *)(DAT_0002b4c0 + 0x44) == 0) {
      if ((bVar1 != 0) && (*DAT_0002b4c4 <= bVar1)) {
        *(undefined4 *)(DAT_0002b4c0 + 0x44) = 1;
        FUN_0002d5cc(8,1000,0);
        FUN_0002e274(0x10);
        FUN_0003362c(0x81,2,0);
        return;
      }
    }
    else if ((bVar1 == 0) || (bVar1 < *DAT_0002b4c4)) {
      FUN_0003362c(0x81,2,0);
      FUN_0002e250();
      *(undefined4 *)(iVar2 + 0x44) = 0;
    }
  }
  return;
}

