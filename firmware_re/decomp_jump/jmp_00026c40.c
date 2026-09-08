// FUN_00026c40 @00026c40 size=158

void FUN_00026c40(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = DAT_00026ce4;
  iVar1 = DAT_00026ce0;
  if (*(int *)(DAT_00026ce0 + 8) != 0) {
    if (*(char *)(DAT_00026ce0 + 4) != '\0') {
      *(undefined1 *)(DAT_00026ce0 + 4) = 0;
      iVar2 = 4;
      if ((*(byte *)(iVar4 + 2) & 1) != 0) {
        FUN_000298b8(*(undefined1 *)(iVar4 + 5));
        iVar2 = *(byte *)(iVar4 + 4) + 5;
      }
      if ((int)((uint)*(byte *)(iVar4 + 2) << 0x1c) < 0) {
        if (*(byte *)(iVar4 + iVar2) < 5) {
          FUN_0001c590(DAT_00026ce0 + 0x24,iVar4 + iVar2 + 1);
          FUN_00024e98(DAT_00026ce0 + 0x24,5);
          *(undefined4 *)(DAT_00026ce0 + 0x24) = 0;
        }
        else {
          iVar3 = iVar2 + iVar4;
          if (*(char *)(iVar3 + 1) == '{') {
            if ((((*(char *)(iVar3 + 2) == -0x56) && (*(char *)(iVar3 + 3) == 'A')) &&
                (*(char *)(iVar3 + 4) == 'S')) &&
               (((*(char *)(iVar3 + 5) == 'U' && (*(char *)(iVar3 + 6) == 'S')) &&
                (*(char *)(iVar3 + 7) == -0x56)))) {
              FUN_0002a058();
            }
          }
          else {
            FUN_00024e98(iVar3 + 1,*(byte *)(iVar4 + iVar2));
          }
        }
      }
      *(undefined4 *)(iVar1 + 8) = 0;
      *(undefined2 *)(iVar1 + 6) = 0;
    }
    iVar4 = *(int *)(iVar1 + 0x14) + -1;
    *(int *)(iVar1 + 0x14) = iVar4;
    if (iVar4 == 0) {
      *(undefined4 *)(iVar1 + 8) = 0;
      *(undefined2 *)(iVar1 + 6) = 0;
    }
  }
  return;
}

