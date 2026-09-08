// FUN_0002aa10 @0002aa10 size=1582

void FUN_0002aa10(void)

{
  ushort uVar1;
  byte bVar2;
  byte bVar3;
  char *pcVar4;
  char *pcVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  uint *puVar12;
  uint *puVar13;
  int *piVar14;
  int iVar15;
  uint uVar16;
  byte *pbVar17;
  uint uVar18;
  byte *pbVar19;
  uint *puVar20;
  bool bVar21;
  int local_30;
  
  pcVar4 = DAT_0002ae14;
  local_30 = 0;
  if (*(int *)(DAT_0002ae14 + 0xc) != 0) {
    FUN_0001c5e0(DAT_0002ae18,*(int *)(DAT_0002ae14 + 0xc) << 1);
    pcVar4[0xc] = '\0';
    pcVar4[0xd] = '\0';
    pcVar4[0xe] = '\0';
    pcVar4[0xf] = '\0';
  }
  if ((*DAT_0002ae1c & 0xc) != 0) {
    FUN_00024f90(0,1);
  }
  if (*(int *)(DAT_0002ae20 + 0x30) == 2) {
    FUN_0002bad4(0,1);
  }
  FUN_0002a0c0();
  puVar6 = DAT_0002ae24;
  *DAT_0002ae24 = 0;
  uVar8 = FUN_0002a498();
  *puVar6 = *puVar6 & 0xfffffffc | uVar8 & 3;
  iVar9 = *(int *)(pcVar4 + 0x3c);
  if ((iVar9 == *(int *)(pcVar4 + 0x28)) || (*(int *)(pcVar4 + 0x28) = iVar9, iVar9 == 0)) {
    iVar9 = 0;
  }
  else {
    FUN_0003b354(iVar9,pcVar4[5]);
    iVar9 = 3;
    pcVar4[0x3c] = '\0';
    pcVar4[0x3d] = '\0';
    pcVar4[0x3e] = '\0';
    pcVar4[0x3f] = '\0';
  }
  *puVar6 = *puVar6 & 0xfffffff3 | iVar9 << 2;
  uVar8 = FUN_0002a40c();
  *puVar6 = *puVar6 & 0xffffffcf | (uVar8 & 3) << 4;
  uVar8 = FUN_0002a39c();
  uVar16 = *puVar6;
  *puVar6 = uVar16 & 0xfffffcff | (uVar8 & 3) << 8;
  FUN_000385f4(uVar16 & 3);
  if (pcVar4[9] != '\0') {
    uVar10 = FUN_0002a7e8();
    *(undefined4 *)(pcVar4 + 0x5c) = uVar10;
  }
  puVar7 = DAT_0002ae24;
  pcVar4 = DAT_0002ae14;
  pbVar19 = (byte *)((int)DAT_0002ae24 + -0x9d);
  bVar21 = (*puVar6 & 0x155) == 0 && *(int *)(DAT_0002ae14 + 0x5c) == 0;
  do {
    if (bVar21) goto LAB_0002ae0e;
  } while ((*(int *)(DAT_0002ae20 + 0x30) == 2) &&
          (bVar21 = true, *(int *)(DAT_0002ae20 + 0x38) == 3));
  if (*(char *)(DAT_0002ae28 + 3) == '\0') {
    puVar20 = DAT_0002ae24 + -5;
    DAT_0002ae24[-0x23] = 0;
    pcVar5 = DAT_0002ae14;
    *puVar20 = 0;
    pcVar5[0x70] = '\0';
    pcVar5[0x71] = '\0';
    pcVar5[0x72] = '\0';
    pcVar5[0x73] = '\0';
    pcVar4[0x2c] = '\0';
    pcVar4[0x2d] = '\0';
    pcVar4[0x2e] = '\0';
    pcVar4[0x2f] = '\0';
    pcVar4[0x30] = '\0';
    pcVar4[0x31] = '\0';
    pcVar4[0x32] = '\0';
    pcVar4[0x33] = '\0';
    FUN_0002bbb0();
    *pcVar4 = '\0';
    uVar8 = 0;
    while( true ) {
      pcVar4 = DAT_0002ae14;
      bVar21 = false;
      if (*(uint *)(DAT_0002ae14 + 0xc) <= uVar8) break;
      uVar1 = *(ushort *)(DAT_0002ae18 + uVar8 * 2);
      uVar16 = (uint)uVar1;
      bVar3 = (byte)uVar1;
      if (uVar16 - 4 < 0x8e) {
        uVar18 = *(uint *)(DAT_0002ae18 + 500);
        if (uVar18 != 0) {
          for (uVar11 = 0; uVar11 < uVar18; uVar11 = uVar11 + 1) {
            if (*(byte *)(DAT_0002ae18 + 500 + uVar11 + 4) == uVar16) {
              bVar21 = true;
              goto LAB_0002ab7a;
            }
          }
        }
        if (6 < *(uint *)(DAT_0002ae14 + 0xc)) {
          puVar12 = (uint *)(DAT_0002ae28 + -0x8c);
          bVar21 = true;
          uVar11 = *puVar12;
          for (uVar18 = 0; uVar18 < uVar11; uVar18 = uVar18 + 1) {
            if (*(byte *)((int)puVar12 + uVar18 + 4) == uVar16) {
              bVar21 = false;
              break;
            }
          }
          if ((uVar11 < 6) && (bVar21)) {
            *(byte *)(uVar11 + DAT_0002ae28 + -0x88) = bVar3;
            *puVar12 = *puVar12 + 1;
            bVar21 = false;
          }
        }
LAB_0002ab7a:
        if ((5 < local_30) || (bVar21)) {
          if (uVar16 - 4 < 0x7c) {
            pbVar17 = (byte *)((int)DAT_0002ae24 + ((int)uVar16 >> 3) + -0xac);
            *pbVar17 = *pbVar17 | (byte)(1 << (uVar16 & 7));
            puVar12 = DAT_0002ae24;
            puVar13 = DAT_0002ae24 + -0x23;
            puVar6[1] = (puVar6[1] & 0xfffffff3) + 8;
            *(byte *)((int)puVar12 + (*puVar13 - 0x88)) = bVar3;
            *puVar13 = *puVar13 + 1;
          }
        }
        else {
          DAT_0002ae14[local_30 + 0x6a] = bVar3;
          local_30 = local_30 + 1;
          puVar6[1] = (puVar6[1] & 0xfffffffc) + 2;
          *(byte *)((int)puVar7 + (*puVar20 - 0x10)) = bVar3;
          *puVar20 = *puVar20 + 1;
        }
      }
      else if (uVar16 - 0xe0 < 8) {
        pbVar17 = (byte *)(DAT_0002ae14 + 0x68);
        bVar2 = *pbVar17 | (byte)(1 << (uVar16 & 7));
        *pbVar17 = bVar2;
        iVar9 = DAT_0002ae2c;
        *(byte *)((int)puVar7 + (*puVar20 - 0x10)) = bVar3;
        *puVar20 = *puVar20 + 1;
        if (((int)((uint)*(byte *)(DAT_0002ae30 + (uint)*(byte *)(iVar9 + 6)) << 0x1d) < 0) &&
           (*(int *)(DAT_0002ae20 + 0x30) != 1)) {
          *pbVar17 = bVar2 & 0x77;
        }
        puVar6[1] = (puVar6[1] & 0xfffffffc) + 2;
      }
      else if (uVar16 - 0xd0 < 7) {
        piVar14 = (int *)(DAT_0002ae14 + 0x70);
        DAT_0002ae14[*piVar14 + 0x74] = bVar3;
        *piVar14 = *piVar14 + 1;
        for (uVar18 = 0; uVar18 < *(uint *)(DAT_0002ae14 + 0x60); uVar18 = uVar18 + 1) {
          if (*(byte *)((int)(DAT_0002ae14 + 0x60) + uVar18 + 4) == uVar16) goto LAB_0002ad74;
        }
        FUN_0002b318(uVar16);
      }
      else if (uVar16 - 0xb000 < 0x1000) {
        FUN_0002b77c(uVar16);
      }
      else if (uVar16 - 0xa000 < 0x1000) {
        if (((*puVar6 & 1) == 0) && ((*puVar6 >> 2 & 1) == 0)) {
          if (*(char *)(DAT_0002ae34 + 1) != '\x04') goto LAB_0002acc4;
          FUN_0002bbc0(uVar16 & 0xff);
        }
        else {
          FUN_0002bb20(uVar16 & 0xff);
        }
      }
      else {
LAB_0002acc4:
        uVar18 = uVar16 - 0xec;
        if (uVar18 < 0x12) {
          FUN_0002b318(uVar16);
          pbVar19[((int)uVar18 >> 3) + 1] =
               pbVar19[((int)uVar18 >> 3) + 1] | (byte)(1 << (uVar18 & 7));
          *(int *)(pcVar4 + 0x2c) = *(int *)(pcVar4 + 0x2c) + 1;
          uVar16 = (puVar6[2] & 0xfffffffc) + 2;
LAB_0002ad70:
          puVar6[2] = uVar16;
        }
        else if (uVar16 - 0x1e0 < 0x1f) {
          if (*(uint *)(DAT_0002ae14 + 0x1c) != uVar16) {
            FUN_0002a964(uVar16,puVar7 + -0x26);
            puVar6[2] = (puVar6[2] & 0xffffffcf) + 0x20;
          }
          if ((uVar16 == 0x1e8) || (uVar16 == 0x1e9)) {
            if (*(uint *)(pcVar4 + 0x1c) != uVar16) {
              pcVar4[0x20] = -0x38;
              pcVar4[0x21] = '\0';
              pcVar4[0x22] = '\0';
              pcVar4[0x23] = '\0';
            }
            *pcVar4 = '\x01';
            *(uint *)(pcVar4 + 0x1c) = uVar16;
          }
          *(int *)(pcVar4 + 0x30) = *(int *)(pcVar4 + 0x30) + 1;
        }
        else if (uVar16 - 0xe9 < 3) {
          *(byte *)((int)puVar7 + -0x92) = bVar3 + 0x18;
          uVar16 = (puVar6[2] & 0xfffffff3) + 8;
          goto LAB_0002ad70;
        }
      }
LAB_0002ad74:
      uVar8 = uVar8 + 1;
    }
    if ((*(int *)(DAT_0002ae28 + -0x8c) != 0) || (*puVar20 != 0)) {
      FUN_0001c590(DAT_0002ae24 + -0x15c,DAT_0002ae24 + -5,*puVar20 + 4);
    }
    if ((*(int *)(DAT_0002ae28 + -0x78) != 0) || (DAT_0002ae24[-0x23] != 0)) {
      FUN_0001c590(DAT_0002ae24 + -0x157,DAT_0002ae24 + -0x23,DAT_0002ae24[-0x23] + 4);
    }
    if ((*(int *)(DAT_0002ae14 + 0x60) != 0) || (*(int *)(DAT_0002ae14 + 0x70) != 0)) {
      FUN_0001c590(DAT_0002ae14 + 0x60,DAT_0002ae14 + 0x70,*(int *)(DAT_0002ae14 + 0x70) + 4);
    }
    pcVar4 = DAT_0002ae14;
    *(undefined4 *)(DAT_0002ae14 + 0x44) = *(undefined4 *)(DAT_0002ae14 + 0x2c);
    *(undefined4 *)(pcVar4 + 0x48) = *(undefined4 *)(pcVar4 + 0x30);
    if ((puVar6[2] & 0x1c0) != 0) {
      puVar6[3] = puVar6[3] | 0x40;
    }
    FUN_0002e4c8();
  }
LAB_0002ae0e:
  pcVar4 = DAT_0002ae14;
  if (*DAT_0002ae14 == '\0') {
    if (*(int *)(DAT_0002ae14 + 0x1c) != 0) {
      pcVar4[0x1c] = '\0';
      pcVar4[0x1d] = '\0';
      pcVar4[0x1e] = '\0';
      pcVar4[0x1f] = '\0';
    }
  }
  else {
    iVar9 = *(int *)(DAT_0002ae14 + 0x20);
    *(int *)(DAT_0002ae14 + 0x20) = iVar9 + -1;
    if (iVar9 + -1 == 0) {
      pcVar4[0x20] = -0x6a;
      pcVar4[0x21] = '\0';
      pcVar4[0x22] = '\0';
      pcVar4[0x23] = '\0';
      FUN_0002a964(*(undefined2 *)(pcVar4 + 0x1c),puVar7 + -0x26);
      puVar6[2] = (puVar6[2] & 0xffffffcf) + 0x20;
    }
  }
  *(undefined1 *)(DAT_0002b064 + 3) = 0;
  if ((*puVar6 & 1) != 0) {
    uVar8 = ((ushort)puVar6[2] & 0x1ff) >> 6;
    if ((int)(uVar8 << 0x1e) < 0) {
      puVar6[3] = puVar6[3] | 0x80;
    }
    if ((int)(uVar8 << 0x1d) < 0) {
      puVar6[3] = puVar6[3] | 0x100;
    }
  }
  if (*DAT_0002b068 != '\0') {
    FUN_0003ba28((byte *)((int)puVar7 + -0x96),DAT_0002b06c);
    puVar6[2] = (puVar6[2] & 0xffffffcf) + 0x20;
  }
  if ((puVar6[1] & 3) != 0) {
    if ((puVar6[1] & 3) == 2) {
      iVar9 = FUN_000319a0(0x81,DAT_0002b070,8,1);
      if (iVar9 == 0) {
        pcVar4[0x68] = '\0';
        pcVar4[0x69] = '\0';
        pcVar4[0x6a] = '\0';
        pcVar4[0x6b] = '\0';
        pcVar4[0x6c] = '\0';
        pcVar4[0x6d] = '\0';
        pcVar4[0x6e] = '\0';
        pcVar4[0x6f] = '\0';
        goto LAB_0002aeea;
      }
    }
    else if ((*(int *)(DAT_0002b064 + -0x8c) == 0) &&
            (iVar9 = FUN_000319a0(0x81,DAT_0002b070,8,0), iVar9 == 0)) {
LAB_0002aeea:
      uVar8 = puVar6[1] >> 2;
      puVar6[1] = (uVar8 | puVar6[1] << 0x1e) + 0xc0000000 >> 0x1e | uVar8 << 2;
      puVar6[3] = puVar6[3] & 0xfffffffd;
    }
  }
  if ((puVar6[1] & 0xc) != 0) {
    if ((puVar6[1] & 0xf) >> 2 == 2) {
      iVar9 = FUN_000319a0(0x84,DAT_0002b06c + -0x17,0xf,1);
      if (iVar9 != 0) goto LAB_0002af6a;
      FUN_0001c5e0(DAT_0002b06c + -0x17,0xf);
    }
    else if ((*(int *)(DAT_0002b064 + -0x78) != 0) ||
            (iVar9 = FUN_000319a0(0x84,DAT_0002b06c + -0x17,0xf,0), iVar9 != 0)) goto LAB_0002af6a;
    uVar8 = puVar6[1] >> 4;
    puVar6[1] = (uVar8 | puVar6[1] << 0x1c) + 0xc0000000 >> 0x1c | uVar8 << 4;
    puVar6[3] = puVar6[3] & 0xfffffffb;
  }
LAB_0002af6a:
  iVar9 = DAT_0002b06c;
  uVar8 = puVar6[2];
  if ((uVar8 & 3) == 0) {
    if ((uVar8 & 0x30) == 0) {
      if ((uVar8 & 0xf) >> 2 != 2) {
        return;
      }
      *(byte *)((int)puVar7 + -0x93) = (byte)((uVar8 << 0x1c) >> 0x1e);
      iVar15 = FUN_000319a0(0x83,iVar9 + 2,2,0);
      if (iVar15 != 0) {
        return;
      }
      *(undefined4 *)(iVar9 + 2) = 0;
      *(undefined1 *)(iVar9 + 6) = 0;
      uVar8 = puVar6[2] >> 4;
      puVar6[2] = (uVar8 | puVar6[2] << 0x1c) + 0xc0000000 >> 0x1c | uVar8 << 4;
      puVar6[3] = puVar6[3] & 0xffffffef;
      return;
    }
    *(byte *)(puVar7 + -0x26) = 4;
    if ((uVar8 & 0x3f) >> 4 == 2) {
      iVar15 = FUN_000319a0(0x83,puVar7 + -0x26,5,0);
      if (iVar15 != 0) {
        return;
      }
      *(undefined4 *)(iVar9 + -3) = 0;
      *(undefined1 *)(iVar9 + 1) = 0;
    }
    else {
      if (*(int *)(pcVar4 + 0x48) != 0) {
        return;
      }
      iVar9 = FUN_000319a0(0x83,puVar7 + -0x26,5,0);
      if (iVar9 != 0) {
        return;
      }
    }
    uVar8 = puVar6[2] >> 6;
    uVar8 = (uVar8 | puVar6[2] << 0x1a) + 0xc0000000 >> 0x1a | uVar8 << 6;
  }
  else {
    *pbVar19 = 1;
    if ((uVar8 & 3) == 2) {
      iVar15 = FUN_000319a0(0x83,DAT_0002b06c + -8,4,0);
      if (iVar15 != 0) {
        return;
      }
      *(undefined4 *)(iVar9 + -8) = 0;
      *(undefined1 *)(iVar9 + -4) = 0;
    }
    else {
      if (*(int *)(pcVar4 + 0x44) != 0) {
        return;
      }
      iVar9 = FUN_000319a0(0x83,iVar9 + -8,4,0);
      if (iVar9 != 0) {
        return;
      }
    }
    uVar8 = puVar6[2] >> 2;
    uVar8 = (uVar8 | puVar6[2] << 0x1e) + 0xc0000000 >> 0x1e | uVar8 << 2;
  }
  puVar6[2] = uVar8;
  return;
}

