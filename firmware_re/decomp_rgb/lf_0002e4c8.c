// FUN_0002e4c8 @0002e4c8 size=44

void FUN_0002e4c8(void)

{
  int iVar1;
  
  iVar1 = DAT_0002e4f4;
  if (*(char *)(DAT_0002e4f4 + 8) == '\0') {
    *(undefined1 *)(DAT_0002e4f4 + 8) = 1;
    FUN_00032550(*(undefined1 *)((uint)*(byte *)(DAT_0002e4f8 + 7) + DAT_0002e4fc));
    if (*(int *)(iVar1 + 0x4c) == 1) {
      *(undefined4 *)(iVar1 + 0x4c) = 4;
    }
    FUN_0002e250();
  }
  *(undefined4 *)(iVar1 + 0x54) = 0x3c;
  return;
}

