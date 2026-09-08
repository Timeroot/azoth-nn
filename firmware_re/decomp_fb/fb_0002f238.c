
void FUN_0002f238(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  uint uVar12;
  byte *pbVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  
  iVar4 = DAT_0002f598;
  iVar6 = DAT_0002f594;
  iVar2 = DAT_0002f590;
  piVar11 = (int *)(DAT_0002f590 + 0x80);
  iVar3 = *(int *)(DAT_0002f590 + 0x44);
  iVar17 = DAT_0002f594 + 0x418;
  if (iVar3 == 0) {
    uVar12 = *(uint *)(DAT_0002f590 + 0xec);
    if (uVar12 == 0) {
      return;
    }
    *(undefined4 *)(DAT_0002f590 + 0x44) = 1;
    if ((uVar12 & 1) != 0) {
      iVar4 = 0;
      *(undefined4 *)(iVar2 + 0x78) = 0;
      *(undefined4 *)(iVar2 + 0x7c) = 0;
      do {
        if (*(int *)(iVar6 + iVar4 * 0x20 + 0x14) != 0) break;
        iVar4 = iVar4 + 1;
        *(int *)(iVar2 + 0x7c) = iVar4;
      } while (iVar4 < 3);
    }
    if ((int)(uVar12 << 0x1d) < 0) {
      iVar6 = 0;
      *piVar11 = 0;
      do {
        if (*(int *)(iVar17 + iVar6 * 0xc) != 0xff) break;
        iVar6 = iVar6 + 1;
        *piVar11 = iVar6;
      } while (iVar6 < 2);
    }
    FUN_0002d760();
    *(undefined4 *)(iVar2 + 0x84) = 0;
    return;
  }
  if (iVar3 == 1) {
    iVar6 = 0;
    do {
      FUN_0001c5e0(iVar4 + (*(int *)(iVar2 + 0x84) + iVar6) * 0x80 + 0xc,0x68);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0x10);
    iVar6 = *(int *)(iVar2 + 0x84) + 0x10;
    *(int *)(iVar2 + 0x84) = iVar6;
    if (iVar6 < 0x40) {
      return;
    }
    goto LAB_0002f370;
  }
  piVar18 = (int *)(DAT_0002f594 + 0xe0);
  if (iVar3 == 2) {
    if (*(char *)(DAT_0002f590 + 3) == '\0') {
      return;
    }
    iVar4 = FUN_00029fd4();
    if (iVar4 != 0) {
      return;
    }
    uVar12 = *(uint *)(iVar2 + 0xec);
    if ((int)(uVar12 << 0x1e) < 0) {
      uVar8 = 800;
      iVar4 = DAT_0002f5a0 + *piVar18 * 0x322;
      iVar6 = DAT_0002f594 + 0xf8;
    }
    else if ((uVar12 & 1) == 0) {
      if (-1 < (int)(uVar12 << 0x1d)) goto LAB_0002f3f4;
      uVar8 = 0xa0;
      iVar4 = DAT_0002f5a8 + *(int *)(iVar17 + *piVar11 * 0xc) * 0xa2;
      iVar6 = DAT_0002f5ac;
    }
    else {
      uVar8 = 0x60;
      iVar4 = DAT_0002f5a4 +
              (uint)*(byte *)(iVar6 + *(int *)(iVar2 + 0x7c) * 0x20 + *(int *)(iVar2 + 0x78)) * 0x62
      ;
      iVar6 = DAT_0002f594 + 0x80;
    }
    FUN_000283e0(iVar4 + 2,iVar6,uVar8);
LAB_0002f3f4:
    *(undefined1 *)(iVar2 + 3) = 0;
    *(undefined4 *)(iVar2 + 0x44) = 3;
    return;
  }
  if (iVar3 != 3) {
    return;
  }
  iVar17 = FUN_00029fd4();
  iVar3 = DAT_0002f59c;
  if (iVar17 != 0) {
    return;
  }
  uVar12 = *(uint *)(iVar2 + 0xec);
  iVar17 = iVar2 + 0x116;
  if ((int)(uVar12 << 0x1e) < 0) {
    iVar15 = *(int *)(iVar6 + 0xe4);
    iVar6 = *(int *)(iVar6 + 0xe8);
    iVar10 = 0;
    do {
      iVar7 = 0;
      do {
        pbVar13 = (byte *)(iVar7 + iVar10 * 0x14 + DAT_0002f594 + 0xf8);
        bVar1 = *pbVar13;
        uVar5 = bVar1 & 0xffffff0f |
                ((uint)((int)(short)(ushort)(bVar1 >> 4) *
                       (int)(short)(ushort)*(byte *)(iVar17 + (uint)*(byte *)(iVar3 + 7))) >> 7 &
                0xf) << 4;
        bVar1 = (byte)uVar5 & 0xf0 |
                (byte)((uint)((int)(short)((ushort)uVar5 & 0xf) *
                             (int)(short)(ushort)*(byte *)(iVar17 + (uint)*(byte *)(iVar3 + 7))) >>
                      7) & 0xf;
        *pbVar13 = bVar1;
        iVar14 = iVar7 + (iVar6 + iVar10) * 0x80;
        iVar7 = iVar7 + 1;
        *(byte *)(iVar14 + iVar15 + iVar4 + 0xc) = bVar1;
      } while (iVar7 < 0x14);
      iVar10 = iVar10 + 1;
    } while (iVar10 < 0x28);
    uVar5 = 0xfffffffd;
LAB_0002f4c6:
    *(uint *)(DAT_0002f590 + 0xec) = uVar12 & uVar5;
  }
  else if ((uVar12 & 1) == 0) {
    if ((int)(uVar12 << 0x1d) < 0) {
      iVar6 = *(int *)(DAT_0002f590 + 0x80);
      iVar10 = 0;
      iVar15 = DAT_0002f5ac + -0x18 + iVar6 * 0xc;
      do {
        iVar7 = 0;
        do {
          pbVar13 = (byte *)(iVar7 + iVar10 * 10 + DAT_0002f5ac);
          bVar1 = *pbVar13;
          uVar5 = bVar1 & 0xffffff0f |
                  ((uint)((int)(short)(ushort)(bVar1 >> 4) *
                         (int)(short)(ushort)*(byte *)(iVar17 + (uint)*(byte *)(iVar3 + 7))) >> 7 &
                  0xf) << 4;
          bVar1 = (byte)uVar5 & 0xf0 |
                  (byte)((uint)((int)(short)((ushort)uVar5 & 0xf) *
                               (int)(short)(ushort)*(byte *)(iVar17 + (uint)*(byte *)(iVar3 + 7)))
                        >> 7) & 0xf;
          *pbVar13 = bVar1;
          iVar14 = iVar7 + (*(int *)(iVar15 + 8) + iVar10) * 0x80;
          iVar7 = iVar7 + 1;
          *(byte *)(*(int *)(iVar15 + 4) + iVar4 + iVar14 + 0xc) = bVar1;
          iVar9 = DAT_0002f5ac;
          iVar14 = DAT_0002f590;
        } while (iVar7 < 10);
        iVar10 = iVar10 + 1;
      } while (iVar10 < 0x10);
      piVar11 = (int *)(DAT_0002f590 + 0x80);
      iVar6 = iVar6 + 1;
      *piVar11 = iVar6;
      for (; (iVar6 < 2 && (*(int *)(iVar9 + -0x18 + iVar6 * 0xc) == 0xff)); iVar6 = iVar6 + 1) {
      }
      *piVar11 = iVar6;
      if (1 < iVar6) {
        *(uint *)(iVar14 + 0xec) = uVar12 & 0xfffffffb;
      }
    }
  }
  else {
    iVar10 = *(int *)(iVar2 + 0x7c);
    iVar6 = iVar6 + iVar10 * 0x20;
    iVar7 = *(int *)(iVar6 + 0x18);
    iVar3 = *(int *)(iVar2 + 0x78);
    iVar15 = 0;
    iVar14 = DAT_0002f594 + iVar10 * 0x20;
    do {
      iVar9 = 0;
      do {
        pbVar13 = (byte *)(iVar9 + iVar15 * 6 + DAT_0002f594 + 0x80);
        bVar1 = *pbVar13;
        uVar5 = bVar1 & 0xffffff0f |
                ((uint)((int)(short)(ushort)(bVar1 >> 4) *
                       (int)(short)(ushort)*(byte *)(iVar17 + (uint)*(byte *)(DAT_0002f59c + 7))) >>
                 7 & 0xf) << 4;
        bVar1 = (byte)uVar5 & 0xf0 |
                (byte)((uint)((int)(short)((ushort)uVar5 & 0xf) *
                             (int)(short)(ushort)*(byte *)(iVar17 + (uint)*(byte *)(DAT_0002f59c + 7
                                                                                   ))) >> 7) & 0xf;
        *pbVar13 = bVar1;
        iVar16 = iVar7 + iVar3 * 6 + (*(int *)(iVar14 + 0x1c) + iVar15) * 0x80 + iVar9;
        iVar9 = iVar9 + 1;
        *(byte *)(iVar16 + iVar4 + 0xc) = bVar1;
        iVar16 = DAT_0002f594;
      } while (iVar9 < 6);
      iVar15 = iVar15 + 1;
    } while (iVar15 < 0x10);
    iVar6 = *(int *)(iVar6 + 0x14);
    iVar3 = iVar3 + 1;
    *(int *)(iVar2 + 0x78) = iVar3;
    if (iVar6 == iVar3) {
      *(undefined4 *)(iVar2 + 0x78) = 0;
      iVar10 = iVar10 + 1;
      *(int *)(iVar2 + 0x7c) = iVar10;
      while ((iVar10 < 3 && (*(int *)(iVar16 + iVar10 * 0x20 + 0x14) == 0))) {
        iVar10 = iVar10 + 1;
      }
      *(int *)(iVar2 + 0x7c) = iVar10;
      if (2 < iVar10) {
        uVar5 = 0xfffffffe;
        goto LAB_0002f4c6;
      }
    }
  }
  if (*(int *)(DAT_0002f590 + 0xec) == 0) {
    *(undefined4 *)(iVar2 + 0x44) = 0;
    *(undefined1 *)(iVar2 + 2) = 1;
    return;
  }
LAB_0002f370:
  *(undefined4 *)(iVar2 + 0x44) = 2;
  return;
}

