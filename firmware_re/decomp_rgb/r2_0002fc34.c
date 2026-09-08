// FUN_0002fc34 @0002fc34 size=58

void FUN_0002fc34(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = DAT_0002fc74;
  uVar3 = *DAT_0002fc70;
  if ((int)(uVar3 << 0x1e) < 0) {
    *(undefined4 *)(DAT_0002fc74 + 0x18) = 0;
    uVar2 = 5000;
LAB_0002fc6a:
    *(undefined4 *)(iVar1 + 0x1c) = uVar2;
    return;
  }
  if ((uVar3 & 1) == 0) {
    if ((int)(uVar3 << 0x1d) < 0) {
      *(undefined4 *)(DAT_0002fc78 + 4) = 0;
      *(undefined4 *)(iVar1 + 0x18) = 0;
      *(undefined4 *)(iVar1 + 0x20) = *DAT_0002fc7c;
      uVar2 = 1000;
      goto LAB_0002fc6a;
    }
  }
  else {
    *(undefined4 *)(DAT_0002fc74 + 0x18) = 1;
    *(undefined4 *)(iVar1 + 0x1c) = 0;
  }
  return;
}

