// @0xf35ec

undefined4 FUN_000f35ec(void)

{
  char cVar1;
  short sVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  ushort uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  
  iVar6 = DAT_000f36f8;
  iVar5 = DAT_000f36f4;
  iVar4 = DAT_000f36f0;
  puVar3 = DAT_000f36ec;
  uVar8 = 0;
  cVar7 = '\0';
  do {
    iVar9 = FUN_000f37c0();
    if (iVar9 == 0) {
      uVar12 = 0;
      do {
        uVar10 = (uVar12 & 0xff) + 9;
        if (uVar10 < 0x20) {
          iVar9 = 0x50000000;
        }
        else {
          uVar10 = uVar10 & 0x1f;
          iVar9 = iVar4;
        }
        *(int *)(iVar9 + 0x508) = 1 << (uVar10 & 0xff);
        FUN_000f3f50(0x1e);
        uVar11 = *puVar3;
        uVar10 = (uVar12 & 0xff) + 9;
        if (uVar10 < 0x20) {
          iVar9 = 0x50000000;
        }
        else {
          uVar10 = uVar10 & 0x1f;
          iVar9 = iVar4;
        }
        *(int *)(iVar9 + 0x50c) = 1 << (uVar10 & 0xff);
        uVar10 = (uint)*(ushort *)(iVar6 + uVar12 * 2);
        bVar13 = uVar10 == (uVar11 & 0x3fff);
        if (bVar13) {
          uVar10 = (uint)*(byte *)(iVar5 + uVar12);
        }
        else {
          *(ushort *)(iVar6 + uVar12 * 2) = (ushort)((uVar11 << 0x12) >> 0x12);
          *(undefined1 *)(iVar5 + uVar12) = 0xf;
        }
        if ((!bVar13 || uVar10 != 0) &&
           (cVar1 = *(char *)(iVar5 + uVar12), *(char *)(iVar5 + uVar12) = cVar1 + -1,
           cVar1 == '\x01')) {
          DAT_000f36fc[uVar12] = *(short *)(iVar6 + uVar12 * 2);
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 < 7);
      sVar2 = *DAT_000f36fc;
      bVar13 = sVar2 != 0;
      if (!bVar13) {
        sVar2 = DAT_000f36fc[1];
      }
      if (bVar13 || sVar2 != 0) {
LAB_000f36b8:
        cVar7 = '\0';
      }
      else {
        sVar2 = DAT_000f36fc[2];
        bVar13 = sVar2 != 0;
        if (!bVar13) {
          sVar2 = DAT_000f36fc[3];
        }
        if (bVar13 || sVar2 != 0x200) goto LAB_000f36b8;
        sVar2 = DAT_000f36fc[4];
        bVar13 = sVar2 == 0x40;
        if (bVar13) {
          sVar2 = DAT_000f36fc[5];
        }
        bVar14 = bVar13 && sVar2 == 0x400;
        if (bVar13 && sVar2 == 0x400) {
          bVar14 = DAT_000f36fc[6] == 0;
        }
        if (!bVar14) goto LAB_000f36b8;
        if (cVar7 == '\x1e') {
          return 1;
        }
        cVar7 = cVar7 + '\x01';
      }
      FUN_000f3f50(1000);
    }
    uVar8 = uVar8 + 1;
    if (99 < uVar8) {
      return 0;
    }
  } while( true );
}

