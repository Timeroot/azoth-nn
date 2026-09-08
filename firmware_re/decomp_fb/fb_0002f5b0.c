
void FUN_0002f5b0(void)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  byte *pbVar5;
  byte bVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  
  iVar4 = DAT_0002f958;
  if ((*(char *)(DAT_0002f958 + 0x14) != '\0') &&
     (iVar7 = *(int *)(DAT_0002f958 + 0x9c) + 1, *(int *)(DAT_0002f958 + 0x9c) = iVar7, 0x3b < iVar7
     )) {
    *(undefined4 *)(iVar4 + 0x9c) = 0;
    *(undefined1 *)(iVar4 + 0x15) = 1;
  }
  iVar7 = DAT_0002f960;
  bVar1 = *(byte *)(DAT_0002f95c + 7);
  uVar8 = 4;
  switch(*(undefined4 *)(iVar4 + 0x48)) {
  case 0:
    if (*(char *)(iVar4 + 0x13) != '\0') {
      *(undefined4 *)(iVar4 + 0x48) = 1;
      if (*(int *)(iVar4 + 0xf4) == 1) {
        *(undefined4 *)(iVar4 + 0x90) = 0x40;
        *(undefined4 *)(iVar4 + 0x94) = 0;
      }
      else {
        *(undefined4 *)(iVar4 + 0x90) = 0x20;
        if (*(int *)(iVar4 + 0xf4) == 2) {
          *(undefined4 *)(iVar4 + 0x94) = 0x20;
        }
        else {
          *(undefined4 *)(iVar4 + 0x94) = 0;
        }
      }
      *(undefined4 *)(iVar4 + 0x98) = 0;
      return;
    }
    if (*(char *)(iVar4 + 0x15) == '\0') {
      return;
    }
    break;
  case 1:
    if (*(char *)(iVar4 + 2) != '\0' || *(char *)(iVar4 + 0x11) != '\0') {
      return;
    }
    for (uVar11 = 0; uVar11 < *(uint *)(iVar4 + 0x90) >> 2; uVar11 = uVar11 + 1) {
      FUN_0001c5e0(iVar7 + (*(int *)(iVar4 + 0x98) + *(int *)(iVar4 + 0x94) + uVar11) * 0x80 + 0xc,
                   0x68);
    }
    uVar11 = *(int *)(iVar4 + 0x98) + (*(uint *)(iVar4 + 0x90) >> 2);
    *(uint *)(iVar4 + 0x98) = uVar11;
    if (uVar11 < *(uint *)(iVar4 + 0x90)) {
      return;
    }
    uVar8 = 2;
    *(undefined4 *)(iVar4 + 0x98) = 0;
    break;
  case 2:
    uVar3 = (ushort)*(byte *)(DAT_0002f964 + (uint)bVar1);
    uVar11 = ((uint)((short)uVar3 * 0xc) >> 7 & 0xf) << 4 | 0xc;
    bVar1 = (byte)uVar11 & 0xf0 |
            (byte)((uint)((int)(short)((ushort)uVar11 & 0xf) * (int)(short)uVar3) >> 7) & 0xf;
    iVar9 = *(int *)(iVar4 + 0xf8);
    if (iVar9 == 1) {
      iVar10 = *(int *)(DAT_0002f958 + 0x94);
      iVar9 = *(int *)(DAT_0002f958 + 0x98);
      uVar16 = *(uint *)(DAT_0002f958 + 0x90);
      for (uVar11 = 0; pbVar5 = DAT_0002f968, uVar11 < uVar16 >> 3; uVar11 = uVar11 + 1) {
        iVar14 = 4;
        iVar18 = 0;
        do {
          if ((uVar16 - (uVar11 + iVar9)) - 1 <= (uint)pbVar5[iVar18]) {
            iVar15 = iVar14 + (uVar11 + iVar10 + iVar9) * 0x80 + 0xc;
            *(byte *)(iVar7 + iVar15) = bVar1;
            *(byte *)(iVar15 + iVar7 + 1) = bVar1;
          }
          iVar14 = iVar14 + 3;
          iVar18 = iVar18 + 1;
        } while (iVar14 < 100);
      }
      uVar11 = iVar9 + (uVar16 >> 3);
      *(uint *)(DAT_0002f958 + 0x98) = uVar11;
      if (uVar11 < uVar16) {
        return;
      }
    }
    else {
      if (iVar9 != 2) {
        if (iVar9 != 3) {
          return;
        }
        iVar15 = *(int *)(iVar4 + 0x90);
        iVar18 = *(int *)(iVar4 + 0x94);
        iVar14 = *(int *)(iVar4 + 0xf4);
        iVar9 = 4;
        iVar10 = 0;
        bVar6 = *DAT_0002f968;
        do {
          iVar12 = iVar10;
          bVar2 = bVar6;
          if (iVar14 == 1) {
            uVar11 = 0x1f;
          }
          else {
            uVar11 = 0xf;
          }
          while( true ) {
            uVar16 = (uint)bVar2;
            if (uVar11 < uVar16) {
              uVar13 = uVar16 - uVar11 >> 1;
              for (uVar17 = 0; uVar17 <= uVar13; uVar17 = uVar17 + 1) {
                iVar10 = ((iVar18 + iVar15) - uVar11) - uVar17;
                *(byte *)(iVar9 + iVar10 * 0x80 + iVar7 + -0x74) = bVar1;
                *(byte *)(iVar9 + (iVar10 - (uVar16 - uVar11 >> 2)) * 0x80 + iVar7 + -0x73) = bVar1;
                *(byte *)(iVar9 + (iVar10 - uVar13) * 0x80 + iVar7 + -0x72) = bVar1;
              }
            }
            else {
              uVar13 = uVar11 - uVar16 >> 1;
              for (uVar17 = 0; uVar17 <= uVar13; uVar17 = uVar17 + 1) {
                iVar10 = ((iVar18 + iVar15) - uVar11) + uVar17;
                *(byte *)(iVar9 + iVar10 * 0x80 + iVar7 + -0x74) = bVar1;
                *(byte *)(iVar9 + (iVar10 + (uVar11 - uVar16 >> 2)) * 0x80 + iVar7 + -0x73) = bVar1;
                *(byte *)(iVar9 + (iVar10 + uVar13) * 0x80 + iVar7 + -0x72) = bVar1;
              }
            }
            iVar9 = iVar9 + 3;
            iVar10 = iVar12 + 1;
            if (99 < iVar9) goto LAB_0002f83e;
            if (iVar10 == 0) break;
            uVar11 = (uint)DAT_0002f968[iVar12];
            iVar12 = iVar10;
            bVar2 = DAT_0002f968[iVar10];
          }
        } while( true );
      }
      iVar10 = *(int *)(DAT_0002f958 + 0x98);
      uVar16 = *(uint *)(DAT_0002f958 + 0x90);
      iVar9 = *(int *)(DAT_0002f958 + 0x94);
      for (uVar11 = 0; uVar11 < uVar16 >> 3; uVar11 = uVar11 + 1) {
        iVar14 = 4;
        iVar18 = 0;
        do {
          iVar15 = iVar14 + (iVar9 + uVar11 + iVar10) * 0x80 + 0xc;
          if (iVar10 + uVar11 < uVar16 >> 1) {
            uVar17 = ((uVar16 >> 1) - (uVar11 + iVar10)) - 1;
            bVar6 = DAT_0002f968[iVar18];
          }
          else {
            uVar17 = (uVar11 + iVar10) - (uVar16 >> 1);
            bVar6 = DAT_0002f968[iVar18];
          }
          if (uVar17 <= bVar6) {
            *(byte *)(iVar7 + iVar15) = bVar1;
            *(byte *)(iVar15 + iVar7 + 1) = bVar1;
          }
          iVar14 = iVar14 + 3;
          iVar18 = iVar18 + 1;
        } while (iVar14 < 100);
      }
      uVar11 = iVar10 + (uVar16 >> 3);
      *(uint *)(DAT_0002f958 + 0x98) = uVar11;
      if (uVar11 < uVar16) {
        return;
      }
    }
LAB_0002f83e:
    uVar8 = 3;
    break;
  case 3:
    if (*(char *)(iVar4 + 0x15) == '\0') {
      *(undefined4 *)(iVar4 + 0x48) = 0;
      *(undefined1 *)(iVar4 + 2) = 1;
    }
    else {
      *(undefined4 *)(iVar4 + 0x48) = 4;
    }
    *(undefined1 *)(iVar4 + 0x13) = 0;
    return;
  case 4:
    if (*(int *)(iVar4 + 0xf4) == 0) {
      *(undefined4 *)(iVar4 + 0x90) = 0x40;
      *(undefined4 *)(iVar4 + 0x94) = 0;
    }
    else {
      *(undefined4 *)(iVar4 + 0x90) = 0x20;
      if (*(int *)(iVar4 + 0xf4) == 2) {
        *(undefined4 *)(iVar4 + 0x94) = 0;
      }
      else {
        *(undefined4 *)(iVar4 + 0x94) = 0x20;
      }
    }
    *(undefined4 *)(iVar4 + 0x98) = 0;
    *(undefined1 *)(iVar4 + 0x15) = 0;
    uVar8 = 5;
    break;
  case 5:
    iVar18 = *(int *)(DAT_0002f964 + -0xe);
    iVar14 = *(int *)(DAT_0002f964 + -10);
    uVar16 = *(uint *)(DAT_0002f964 + -0x7e);
    iVar9 = *(int *)(DAT_0002f964 + -0x16);
    iVar10 = *(int *)(DAT_0002f964 + -0x82);
    uVar11 = *(uint *)(DAT_0002f964 + -0x86);
    for (uVar17 = 0; uVar17 < uVar11 >> 3; uVar17 = uVar17 + 1) {
      iVar15 = 0;
      do {
        iVar12 = iVar18 + iVar15;
        if (iVar12 < iVar14 + 0xd0) {
          if (iVar12 < iVar14 + 0x68) {
            bVar6 = *(byte *)(uVar16 * iVar9 + DAT_0002f96c + iVar15 + iVar18);
            goto LAB_0002f8dc;
          }
          bVar6 = 0;
        }
        else {
          bVar6 = *(byte *)(DAT_0002f96c + ((uVar16 * iVar9 + iVar12) - iVar14) + -0xd0);
LAB_0002f8dc:
          if (bVar6 != 0) {
            bVar2 = *(byte *)(DAT_0002f964 + (uint)bVar1);
            uVar13 = bVar6 & 0xffffff0f |
                     ((uint)((int)(short)(ushort)(bVar6 >> 4) * (int)(short)(ushort)bVar2) >> 7 &
                     0xf) << 4;
            bVar6 = (byte)uVar13 & 0xf0 |
                    (byte)((uint)((int)(short)((ushort)uVar13 & 0xf) * (int)(short)(ushort)bVar2) >>
                          7) & 0xf;
          }
        }
        iVar12 = iVar15 + (uVar16 + iVar10) * 0x80;
        iVar15 = iVar15 + 1;
        *(byte *)(iVar12 + iVar7 + 0xc) = bVar6;
      } while (iVar15 < 0x68);
      uVar16 = uVar16 + 1;
    }
    *(uint *)(DAT_0002f958 + 0x98) = uVar16;
    if (uVar11 <= uVar16) {
      *(undefined4 *)(iVar4 + 0x48) = 0;
      *(undefined1 *)(iVar4 + 2) = 1;
      iVar4 = DAT_0002f964;
      if ((iVar14 != 0) && (*(int *)(DAT_0002f964 + -0xe) = iVar18 + 1, iVar14 + 0xd0 <= iVar18 + 1)
         ) {
        *(undefined4 *)(iVar4 + -0xe) = 0;
      }
    }
  default:
    goto switchD_0002f5e8_default;
  }
  *(undefined4 *)(iVar4 + 0x48) = uVar8;
switchD_0002f5e8_default:
  return;
}

