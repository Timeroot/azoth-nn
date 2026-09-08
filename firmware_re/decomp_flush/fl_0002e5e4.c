
void FUN_0002e5e4(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = DAT_0002e658;
  if (*(char *)(DAT_0002e658 + 0x11) == '\0') goto LAB_0002e632;
  iVar2 = *(int *)(DAT_0002e658 + 0xf0);
  if (iVar2 == 0) {
    FUN_000311fc();
    uVar3 = 1;
LAB_0002e626:
    *(undefined4 *)(iVar1 + 0xf0) = uVar3;
  }
  else {
    if (iVar2 == 1) {
      if (*(int *)(*(int *)(DAT_0002e65c + 4) + 0x500) == 7) {
        iVar2 = FUN_00031658(DAT_0002e660,0x2000);
        if (iVar2 != 0) goto LAB_0002e632;
        uVar3 = 2;
        goto LAB_0002e626;
      }
    }
    else {
      if ((iVar2 != 2) || (iVar2 = FUN_0002a034(DAT_0002e65c), iVar2 != 0)) goto LAB_0002e632;
      FUN_000312ec(DAT_0002e65c);
      *(undefined1 *)(iVar1 + 0x11) = 0;
    }
    *(undefined4 *)(iVar1 + 0xf0) = 0;
  }
LAB_0002e632:
  if (*(char *)(iVar1 + 0x16) != '\0') {
    if (*(char *)(iVar1 + 10) != *(char *)(iVar1 + 0x11)) {
      *(char *)(iVar1 + 10) = *(char *)(iVar1 + 0x11);
    }
    if (*(int *)(iVar1 + 0xa0) != *(int *)(iVar1 + 0xf0)) {
      *(int *)(iVar1 + 0xa0) = *(int *)(iVar1 + 0xf0);
    }
  }
  return;
}

