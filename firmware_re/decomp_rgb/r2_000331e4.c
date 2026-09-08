// FUN_000331e4 @000331e4 size=126

void FUN_000331e4(void)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(DAT_00033264 + 0x140) != 1) {
    return;
  }
  *(undefined4 *)(DAT_00033264 + 0x140) = 0;
  iVar2 = FUN_00039ebc();
  iVar1 = DAT_0003326c;
  if (iVar2 == 0) {
    return;
  }
  if (*(int *)(DAT_00033268 + 0x60) != 0) {
    return;
  }
  if (*(char *)(DAT_0003326c + 2) == '\0') {
    iVar2 = 0x1c2;
  }
  else {
    iVar2 = 1000;
    if (*DAT_00033270 == 1000) goto LAB_0003321a;
  }
  *DAT_00033270 = iVar2;
LAB_0003321a:
  iVar2 = FUN_0003d224();
  if ((iVar2 == 0) && (*DAT_00033274 == '\0')) {
    FUN_0003d528(DAT_0003326c + 0x50,0);
  }
  iVar2 = FUN_0003d350();
  if (iVar2 != 0) {
    FUN_0003d498(*(undefined4 *)
                  (DAT_00033278 + (*(int *)(iVar1 + 0x2c) + *(int *)(iVar1 + 0x34)) * 4));
    FUN_0003d47c(*(undefined1 *)(iVar1 + 2));
    FUN_0003d500();
    *(undefined1 *)(iVar1 + 0xb) = 0;
    *(undefined1 *)(iVar1 + 0xc) = 0;
    *(undefined4 *)(iVar1 + 0x44) = 0;
  }
  return;
}

