// @0xf3e8c

void FUN_000f3e8c(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  bool bVar10;
  bool bVar11;
  
  iVar4 = DAT_000f3f2c;
  iVar3 = DAT_000f3f28;
  iVar2 = DAT_000f3f24;
  puVar1 = DAT_000f3f20;
  uVar8 = 0;
  iVar9 = DAT_000f3f2c + -0x70;
  do {
    uVar5 = (uVar8 & 0xff) + 9;
    if (uVar5 < 0x20) {
      iVar7 = 0x50000000;
    }
    else {
      uVar5 = uVar5 & 0x1f;
      iVar7 = iVar2;
    }
    *(int *)(iVar7 + 0x508) = 1 << (uVar5 & 0xff);
    FUN_000f3f50(0x1e);
    uVar6 = *puVar1;
    uVar5 = (uVar8 & 0xff) + 9;
    if (uVar5 < 0x20) {
      iVar7 = 0x50000000;
    }
    else {
      uVar5 = uVar5 & 0x1f;
      iVar7 = iVar2;
    }
    *(int *)(iVar7 + 0x50c) = 1 << (uVar5 & 0xff);
    uVar5 = (uint)*(ushort *)(iVar4 + uVar8 * 2);
    bVar10 = uVar5 == (uVar6 & 0x3fff);
    if (bVar10) {
      uVar5 = (uint)*(byte *)(iVar3 + uVar8);
    }
    else {
      *(ushort *)(iVar4 + uVar8 * 2) = (ushort)((uVar6 << 0x12) >> 0x12);
      *(undefined1 *)(iVar3 + uVar8) = 0xf;
    }
    bVar11 = bVar10 && uVar5 == 0;
    if (!bVar10 || uVar5 != 0) {
      bVar11 = *(char *)(iVar3 + uVar8) == '\x01';
      *(char *)(iVar3 + uVar8) = *(char *)(iVar3 + uVar8) + -1;
      if (bVar11) {
        *(undefined2 *)(iVar9 + uVar8 * 2) = *(undefined2 *)(iVar4 + uVar8 * 2);
      }
    }
    if (bVar11) {
      uVar8 = uVar8 + 1;
    }
  } while (uVar8 < 7);
  return;
}

