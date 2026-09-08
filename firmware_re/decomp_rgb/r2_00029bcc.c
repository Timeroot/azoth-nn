// FUN_00029bcc @00029bcc size=222

void FUN_00029bcc(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  
  iVar2 = DAT_00029cb0;
  iVar1 = DAT_00029cac;
  iVar3 = *(int *)(DAT_00029cac + 0x18);
  if (*(int *)(DAT_00029cac + 0x14) != iVar3) {
    *(uint *)(DAT_00029cb0 + 8) = *(uint *)(DAT_00029cb0 + 8) | 0x40;
    *(uint *)(iVar2 + 0xc) = *(uint *)(iVar2 + 0xc) | 0x40;
  }
  iVar5 = DAT_00029cb0;
  uVar6 = (*(ushort *)(iVar2 + 0xc) & 0x1ff) >> 6;
  if ((uVar6 & 1) == 0) {
    return;
  }
  if (((int)(uVar6 << 0x1e) < 0) && ((int)((uint)(*(byte *)(iVar2 + 8) >> 6) << 0x1e) < 0)) {
    puVar4 = (undefined1 *)(DAT_00029cb0 + 0x68);
    *puVar4 = 3;
    *(undefined1 *)(iVar5 + 0x69) = 0x71;
    iVar3 = FUN_000319a0(0x83,puVar4,0x15,0);
    if (iVar3 != 0) goto LAB_00029c98;
    *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xffffff7f;
    uVar6 = *(uint *)(iVar2 + 0xc) & 0xffffff7f;
  }
  else {
    if ((-1 < (int)(uVar6 << 0x1d)) || (-1 < (int)((uint)(*(ushort *)(iVar2 + 8) >> 6) << 0x1d))) {
      if ((*(byte *)(iVar2 + 8) >> 6 & 1) != 0) {
        iVar3 = iVar3 * 0x15;
        iVar5 = DAT_00029cb0 + 0x14;
        *(undefined1 *)(iVar5 + iVar3) = 3;
        iVar3 = FUN_000319a0(0x83,iVar5 + iVar3,0x15,0);
        if ((iVar3 == 0) &&
           (iVar3 = *(int *)(iVar1 + 0x18) + 1, *(int *)(iVar1 + 0x18) = iVar3, 2 < iVar3)) {
          *(undefined4 *)(iVar1 + 0x18) = 0;
        }
        *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xffffffbf;
      }
      goto LAB_00029c98;
    }
    puVar4 = (undefined1 *)(DAT_00029cb0 + 0x7d);
    *puVar4 = 3;
    *(undefined1 *)(iVar5 + 0x7e) = 0x72;
    iVar3 = FUN_000319a0(0x83,puVar4,0x15,0);
    if (iVar3 != 0) goto LAB_00029c98;
    *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xfffffeff;
    uVar6 = *(uint *)(iVar2 + 0xc) & 0xfffffeff;
  }
  *(uint *)(iVar2 + 0xc) = uVar6;
LAB_00029c98:
  if ((*(uint *)(iVar2 + 0xc) & 0x1ff) >> 7 == 0) {
    *(uint *)(iVar2 + 0xc) = *(uint *)(iVar2 + 0xc) & 0xffffffbf;
  }
  return;
}

