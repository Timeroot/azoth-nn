
void FUN_0002e518(void)

{
  int iVar1;
  
  iVar1 = DAT_0002e540;
  *(undefined1 *)(DAT_0002e540 + 3) = 1;
  FUN_0002f970();
  if ((*(byte *)(iVar1 + 2) & ~*(byte *)(iVar1 + 0x11)) != 0) {
    *(undefined1 *)(iVar1 + 0x11) = 1;
    *(undefined1 *)(iVar1 + 2) = 0;
    *(undefined4 *)(iVar1 + 0xf0) = 0;
  }
  FUN_0002e5e4();
  return;
}

