// FUN_0002a0c0 @0002a0c0 size=694

void FUN_0002a0c0(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  bool bVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined1 uVar10;
  uint uVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  uint uVar19;
  int iVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  uint uVar26;
  uint uVar27;
  undefined4 uVar28;
  
  iVar24 = DAT_0002a384;
  puVar6 = DAT_0002a380;
  bVar5 = false;
  if ((int)((uint)*(byte *)(DAT_0002a37c + (uint)*(byte *)(DAT_0002a378 + 6)) << 0x19) < 0) {
    uVar10 = 0;
    if (*(char *)(DAT_0002a384 + 1) != '\0') {
      *(undefined1 *)(DAT_0002a384 + 1) = 0;
      iVar8 = DAT_0002a388;
      iVar7 = 0;
      *(undefined1 *)(iVar24 + 3) = 0;
      do {
        iVar25 = iVar8 + iVar7 * 2;
        if (*(byte *)(iVar25 + 5) >> 3 != 0) {
          bVar1 = *(byte *)(iVar24 + 3);
          for (iVar20 = 0; iVar20 < (int)(uint)bVar1; iVar20 = iVar20 + 1) {
            if (*(char *)(iVar25 + 4) == *(char *)((int)puVar6 + iVar20 + 0x4b0)) goto LAB_0002a118;
          }
          *(char *)((int)puVar6 + bVar1 + 0x4b0) = (char)iVar7;
          *(byte *)(iVar24 + 3) = bVar1 + 1;
        }
LAB_0002a118:
        iVar7 = iVar7 + 1;
      } while (iVar7 < 0xf7);
    }
    iVar8 = DAT_0002a38c;
    if (*(char *)(iVar24 + 4) != '\0') {
      *(undefined1 *)(iVar24 + 4) = 0;
      iVar7 = 0;
      do {
        if (*(int *)(iVar8 + 0xc4 + iVar7 * 4) != 0) {
          iVar25 = 0;
          do {
            iVar20 = iVar7 * 0xe + iVar25;
            sVar4 = *(short *)(iVar8 + iVar20 * 2);
            if (sVar4 != 0) {
              *(short *)(iVar8 + iVar20 * 2) = sVar4 + -1;
              if (sVar4 == 1) {
                bVar5 = true;
              }
              else {
                uVar10 = 1;
              }
            }
            iVar25 = iVar25 + 1;
          } while (iVar25 < 0xe);
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < 7);
      *(undefined1 *)(iVar24 + 4) = uVar10;
    }
    iVar8 = FUN_0001c604(DAT_0002a380 + 0x171,DAT_0002a380,0x1c);
    puVar6 = DAT_0002a380;
    if ((iVar8 == 0) && (!bVar5)) {
      return;
    }
    puVar9 = DAT_0002a380 + 0x16a;
    uVar13 = *DAT_0002a380;
    *puVar9 = uVar13;
    uVar14 = puVar6[1];
    puVar6[0x16b] = uVar14;
    uVar15 = puVar6[2];
    puVar6[0x16c] = uVar15;
    uVar16 = puVar6[3];
    puVar6[0x16d] = uVar16;
    uVar17 = puVar6[4];
    puVar6[0x16e] = uVar17;
    uVar18 = puVar6[5];
    puVar6[0x16f] = uVar18;
    uVar28 = puVar6[6];
    puVar6[0x170] = uVar28;
    iVar8 = DAT_0002a390;
    bVar1 = *(byte *)(iVar24 + 3);
    for (iVar24 = 0; iVar7 = DAT_0002a38c, iVar24 < (int)(uint)bVar1; iVar24 = iVar24 + 1) {
      uVar21 = (uint)*(byte *)(DAT_0002a394 + iVar24);
      if (uVar21 - 0xe0 < 8) {
        bVar2 = *(byte *)(uVar21 + iVar8);
      }
      else {
        bVar2 = *(byte *)(DAT_0002a390 + 0x70 + uVar21);
      }
      bVar2 = *(byte *)(DAT_0002a398 + (uint)bVar2);
      uVar19 = (uint)(bVar2 >> 4);
      uVar11 = 1 << (bVar2 & 0xf);
      iVar7 = DAT_0002a388 + uVar21 * 2;
      uVar21 = (uint)*(byte *)(iVar7 + 4);
      if (uVar21 - 0xe0 < 8) {
        bVar3 = *(byte *)(uVar21 + iVar8);
      }
      else {
        bVar3 = *(byte *)(DAT_0002a390 + 0x70 + uVar21);
      }
      bVar3 = *(byte *)(DAT_0002a398 + (uint)bVar3);
      uVar21 = (uint)(bVar3 >> 4);
      uVar26 = 1 << (bVar3 & 0xf);
      if (*(byte *)(iVar7 + 5) >> 3 == 1) {
        uVar22 = DAT_0002a380[uVar19];
        if (((uVar22 ^ DAT_0002a380[uVar19 + 0x171]) & uVar11) == 0) {
          uVar27 = DAT_0002a380[uVar21];
          if (((uVar27 ^ *(uint *)(DAT_0002a38c + -0x1c + uVar21 * 4)) & uVar26) == 0) {
            uVar23 = *(uint *)(DAT_0002a38c + 0xc4 + uVar19 * 4);
            if (((uVar23 & uVar11) == 0) || (*(short *)(DAT_0002a38c + (uint)bVar2 * 2) != 0)) {
              uVar23 = puVar9[uVar19] & ~uVar11;
              uVar22 = DAT_0002a380[uVar19 + 7];
            }
            else {
              *(uint *)(DAT_0002a38c + 0xc4 + uVar19 * 4) = uVar23 & ~uVar11;
              uVar23 = puVar9[uVar19] & ~uVar11;
            }
            puVar9[uVar19] = uVar23 | uVar22 & uVar11;
            uVar11 = *(uint *)(DAT_0002a38c + 0xc4 + uVar21 * 4);
            if (((uVar11 & uVar26) == 0) || (*(short *)(DAT_0002a38c + (uint)bVar3 * 2) != 0)) {
              uVar11 = puVar9[uVar21] & ~uVar26;
              uVar27 = DAT_0002a380[uVar21 + 7];
            }
            else {
              *(uint *)(DAT_0002a38c + 0xc4 + uVar21 * 4) = uVar11 & ~uVar26;
              uVar11 = puVar9[uVar21] & ~uVar26;
            }
            uVar11 = uVar11 | uVar27 & uVar26;
            goto LAB_0002a2c8;
          }
          if ((uVar27 & uVar26) != 0) {
            puVar9[uVar19] = puVar9[uVar19] & ~uVar11;
          }
        }
        else if ((uVar22 & uVar11) != 0) {
          uVar11 = puVar9[uVar21] & ~uVar26;
LAB_0002a2c8:
          puVar9[uVar21] = uVar11;
        }
      }
    }
    *(undefined4 *)(DAT_0002a38c + -0x1c) = uVar13;
    *(undefined4 *)(iVar7 + -0x18) = uVar14;
    *(undefined4 *)(iVar7 + -0x14) = uVar15;
    *(undefined4 *)(iVar7 + -0x10) = uVar16;
    *(undefined4 *)(iVar7 + -0xc) = uVar17;
    *(undefined4 *)(iVar7 + -8) = uVar18;
    *(undefined4 *)(iVar7 + -4) = uVar28;
    puVar12 = (undefined4 *)(iVar7 + -0x5c4);
    *puVar12 = *puVar9;
    *(undefined4 *)(iVar7 + -0x5c0) = puVar6[0x16b];
    *(undefined4 *)(iVar7 + -0x5bc) = puVar6[0x16c];
    *(undefined4 *)(iVar7 + -0x5b8) = puVar6[0x16d];
    *(undefined4 *)(iVar7 + -0x5b4) = puVar6[0x16e];
    *(undefined4 *)(iVar7 + -0x5b0) = puVar6[0x16f];
    uVar13 = puVar6[0x170];
  }
  else {
    puVar12 = DAT_0002a380 + 7;
    *puVar12 = *DAT_0002a380;
    puVar6[8] = puVar6[1];
    puVar6[9] = puVar6[2];
    puVar6[10] = puVar6[3];
    puVar6[0xb] = puVar6[4];
    puVar6[0xc] = puVar6[5];
    uVar13 = puVar6[6];
  }
  puVar12[6] = uVar13;
  return;
}

