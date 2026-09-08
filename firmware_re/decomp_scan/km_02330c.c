// @0x2330c size=6538

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0002330c(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  char *pcVar4;
  undefined **ppuVar5;
  int *piVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  ushort *puVar12;
  int iVar13;
  undefined1 *puVar14;
  int iVar15;
  undefined4 *puVar16;
  undefined2 *puVar17;
  byte bVar18;
  byte bVar19;
  undefined2 uVar20;
  undefined *puVar21;
  undefined4 uVar22;
  char *pcVar23;
  int iVar24;
  byte *pbVar25;
  int iVar26;
  undefined1 uVar27;
  uint uVar28;
  int iVar29;
  int iVar30;
  ushort uVar31;
  undefined **ppuVar32;
  undefined **ppuVar33;
  undefined **ppuVar34;
  undefined4 *puVar35;
  undefined *puVar36;
  uint unaff_r10;
  uint uVar37;
  bool bVar38;
  bool bVar39;
  bool bVar40;
  uint uVar41;
  undefined **local_70;
  uint local_6c;
  byte local_68 [8];
  undefined4 uStack_60;
  
  ppuVar5 = DAT_00023704;
  pcVar4 = DAT_00023700;
  if (DAT_00023700[1] == '\0') {
    if (*(byte *)DAT_00023704 == 0) {
      return;
    }
    FUN_000385c8();
    piVar6 = DAT_00023708;
    uVar37 = (uint)*(byte *)ppuVar5;
    if (uVar37 == 0x12) {
      bVar18 = *(byte *)((int)ppuVar5 + 1);
      if (((bVar18 != 0) && (bVar18 != 1)) && (bVar18 != 3)) goto LAB_00023366;
    }
    else if (uVar37 == 0xc0) {
      if (*(byte *)((int)ppuVar5 + 1) != 0x81) goto LAB_00023366;
    }
    else if ((((uVar37 != 0xfd) && (uVar37 != 0x65)) &&
             ((uVar37 != 0x66 && ((uVar37 != 0x67 && (uVar37 != 99)))))) && (uVar37 != 100)) {
LAB_00023366:
      *DAT_00023708 = 0;
    }
    puVar16 = DAT_00024c0c;
    iVar15 = DAT_000247f8;
    puVar14 = DAT_000247f0;
    iVar13 = DAT_000247e0;
    puVar35 = DAT_000243e0;
    puVar12 = DAT_000243dc;
    pbVar11 = DAT_000243c8;
    pbVar10 = DAT_000243c4;
    iVar9 = DAT_000243c0;
    iVar24 = DAT_00023f68;
    puVar8 = DAT_00023b3c;
    pcVar23 = DAT_00023b34;
    ppuVar33 = DAT_00023b30;
    iVar26 = DAT_00023b28;
    iVar30 = DAT_00023b24;
    iVar29 = DAT_00023728;
    pbVar7 = DAT_00023724;
    puVar21 = DAT_00023718;
    pbVar25 = DAT_0002370c;
    ppuVar32 = (undefined **)((int)&MemManage + 3);
    ppuVar34 = &SysTick;
    puVar36 = &DAT_000d3000;
    bVar40 = SBORROW4(uVar37,100);
    bVar38 = (int)(uVar37 - 100) < 0;
    bVar39 = uVar37 == 100;
LAB_0002337e:
    while( true ) {
      if (bVar39) goto LAB_00024226;
      if (bVar38 == bVar40) break;
      if (uVar37 == 0x50) {
        bVar18 = *(byte *)((int)ppuVar5 + 1);
        if (bVar18 == 0x55) {
          if (*DAT_00023b34 != '\x04') {
            *DAT_00023b34 = '\x04';
            pcVar23[8] = '\0';
            bVar18 = pcVar23[9] & 0xf3;
            goto LAB_000238e0;
          }
        }
        else {
          if (0x55 < bVar18) {
            if (bVar18 == 0x60) {
              FUN_0002325c(DAT_00023b28 + 0xca);
              uVar31 = *(ushort *)((int)ppuVar5 + 2);
              uVar28 = 0x60;
            }
            else {
              bVar39 = bVar18 == 0x61;
              if (!bVar39) {
LAB_000237ea:
                if (bVar39) {
                  *(undefined1 *)ppuVar34 = 1;
                  FUN_0001c5e0((undefined1 *)((int)ppuVar34 + 1),0x80);
                  uVar28 = 1;
                  goto LAB_0002389c;
                }
                goto switchD_00024374_caseD_5;
              }
              *(undefined1 *)(DAT_00023b24 + 5) =
                   *(undefined1 *)(DAT_00023b38 + (uint)*(byte *)(DAT_00023b24 + 6));
              FUN_00022f60();
              *(undefined2 *)(DAT_00023b28 + 2) = 0;
              FUN_000231e0(*(undefined1 *)(iVar30 + 5));
              uVar31 = *(ushort *)((int)ppuVar5 + 2);
              uVar28 = 0x61;
            }
            uVar41 = 0x3c;
            ppuVar33 = ppuVar5 + 1;
            uVar37 = (uint)uVar31;
            bVar18 = 0x50;
            goto LAB_00024cf6;
          }
          if (bVar18 != 0x30) {
            bVar39 = bVar18 == 0x40;
            goto LAB_000238ae;
          }
          if (*DAT_00023b34 == '\x03') goto LAB_000239a8;
          *DAT_00023b34 = '\x03';
LAB_000238dc:
          pcVar23[8] = '\0';
          bVar18 = pcVar23[9];
LAB_000238e0:
          pcVar23[9] = bVar18 | 1;
        }
LAB_000239a8:
        pcVar23[9] = pcVar23[9] | 2;
        goto switchD_00024374_caseD_0;
      }
      if (uVar37 < 0x51) {
        if (uVar37 != 0x25) {
          if (uVar37 < 0x26) {
            if (uVar37 != 0x12) {
              if (uVar37 != 0x21) {
                bVar39 = uVar37 == 0x22;
                goto LAB_000233a2;
              }
              bVar39 = *(byte *)((int)ppuVar5 + 1) == 0;
              if (!bVar39) goto LAB_00023624;
              uVar28 = 0;
              ppuVar33 = ppuVar5 + 1;
              *(char *)(ppuVar5 + 1) = DAT_00023700[0x33];
              uVar41 = 1;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              bVar18 = 0x21;
              goto LAB_00024cf6;
            }
            switch(*(byte *)((int)ppuVar5 + 1)) {
            case 0:
              if (*(short *)((int)ppuVar5 + 2) == 0) {
                puVar36 = *(undefined **)(pcVar4 + 0x30);
                puVar21 = *(undefined **)(pcVar4 + 0x34);
                ppuVar5[1] = *(undefined **)(pcVar4 + 0x2c);
                ppuVar5[2] = puVar36;
                ppuVar5[3] = puVar21;
                bVar18 = *(byte *)((int)ppuVar5 + 10);
                if (bVar18 == 0) {
                  bVar18 = 6;
                }
                *(byte *)((int)ppuVar5 + 10) = bVar18;
                uVar41 = 0xc;
                uVar37 = 0;
              }
              else {
                if (*(short *)((int)ppuVar5 + 2) != 2) goto LAB_00024d90;
                if ((*DAT_0002371c & 1) == 0) goto switchD_0002346a_default;
                *(bool *)(ppuVar5 + 1) = *(int *)(DAT_00023720 + 0x5c) == 0;
                uVar37 = 2;
                uVar41 = 1;
              }
              ppuVar33 = ppuVar5 + 1;
              uVar28 = 0;
              break;
            case 1:
              *(byte *)(ppuVar5 + 1) = 0;
              iVar29 = DAT_00023728;
              bVar18 = *pbVar7;
              *(byte *)((int)ppuVar5 + 5) = bVar18;
              uVar28 = (uint)*(byte *)(iVar29 + 0x2b9);
              uVar37 = uVar28 & 7;
              bVar19 = (byte)uVar37;
              if (4 < uVar37) {
                bVar19 = 0xff;
              }
              *(byte *)((int)ppuVar5 + 6) = bVar19;
              *(byte *)((int)ppuVar5 + 7) = (byte)((uVar28 << 0x1b) >> 0x1e);
              *(byte *)(ppuVar5 + 2) = (byte)*(undefined4 *)(DAT_00023720 + 0x18);
              *(byte *)((int)ppuVar5 + 9) = *(byte *)(iVar29 + 0x2b8);
              *(byte *)((int)ppuVar5 + 10) = bVar18;
              *(byte *)((int)ppuVar5 + 0xb) = *pbVar25;
              *(byte *)(ppuVar5 + 3) = pbVar25[1];
              uVar41 = 9;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              ppuVar33 = ppuVar5 + 1;
              uVar28 = 1;
              break;
            case 2:
              *(byte *)(ppuVar5 + 1) = 0;
              *(byte *)((int)ppuVar5 + 5) =
                   (byte)(((uint)*(byte *)(iVar29 + 0x2b9) << 0x1a) >> 0x1f);
              uVar41 = 2;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              ppuVar33 = ppuVar5 + 1;
              uVar28 = 2;
              break;
            case 3:
              uVar37 = *DAT_0002371c;
              if ((int)(uVar37 << 0x1d) < 0) {
                *(byte *)(ppuVar5 + 1) = 0;
              }
              else if ((int)(uVar37 << 0x1e) < 0) {
                *(byte *)(ppuVar5 + 1) = 1;
              }
              else {
                if ((((uVar37 & 1) == 0) || (*(int *)(DAT_00023720 + 0x5c) != 0)) ||
                   (*(int *)(DAT_00023720 + 0x58) != 0)) {
                  bVar18 = 0xff;
                }
                else {
                  bVar18 = 2;
                }
                *(byte *)(ppuVar5 + 1) = bVar18;
              }
              uVar41 = 1;
              ppuVar33 = ppuVar5 + 1;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              uVar28 = 3;
              break;
            case 4:
            case 8:
            case 9:
            case 10:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
              goto switchD_0002346a_caseD_4;
            case 5:
              *(byte *)(ppuVar5 + 1) = (byte)*(undefined4 *)(DAT_00023720 + 0xc);
              *(byte *)((int)ppuVar5 + 5) = 0xff;
              ppuVar33 = ppuVar5 + 1;
              uVar37 = 0;
              uVar28 = 5;
              uVar41 = 2;
              break;
            case 6:
              ppuVar33 = ppuVar5 + 1;
              uVar28 = 6;
              *(byte *)(ppuVar5 + 1) =
                   (byte)(((uint)*(byte *)(DAT_0002372c + (uint)(byte)DAT_00023700[0x32]) << 0x1b)
                         >> 0x1f);
              uVar41 = 1;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              break;
            case 7:
              uVar41 = 4;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              uVar28 = 7;
              ppuVar33 = DAT_00023730;
              break;
            case 0x12:
              local_6c = 0;
              FUN_00027a68(0,&local_6c,1);
              if (0x19 < local_6c) {
                local_6c = 0;
              }
              *(byte *)(ppuVar5 + 1) = *(byte *)(DAT_00023734 + local_6c);
              *(byte *)((int)ppuVar5 + 5) = (byte)local_6c;
              uVar41 = 2;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              uVar28 = 0x12;
              ppuVar33 = ppuVar5 + 1;
              break;
            case 0x13:
              iVar29 = FUN_00027aa8(0,ppuVar5 + 1,1);
              if (iVar29 == 0) {
                ppuVar33 = (undefined **)0x0;
                uVar28 = 0xaa;
                uVar37 = 0;
                bVar18 = 0xff;
                uVar41 = 0;
                goto LAB_00024cf6;
              }
              FUN_00037f78();
              uVar41 = 0x3c;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              uVar28 = 0x13;
              ppuVar33 = ppuVar5 + 1;
              break;
            case 0x14:
              sVar3 = *(short *)((int)ppuVar5 + 2);
              if (sVar3 == 0) {
                uVar37 = 0;
                *(byte *)(ppuVar5 + 1) = *(byte *)(DAT_0002372c + 6);
                uVar41 = 1;
                goto LAB_00023686;
              }
              if (sVar3 == 1) {
                FUN_0002cc30(&DAT_000d7000,ppuVar5 + 1,0xc);
                iVar29 = 0;
                do {
                  if (*(byte *)((int)ppuVar5 + iVar29 + 4) == 0x20) {
                    *(byte *)((int)ppuVar5 + iVar29 + 4) = 0x30;
                  }
                  iVar29 = iVar29 + 1;
                } while (iVar29 < 0xc);
                uVar37 = 1;
                uVar41 = 0xc;
                goto LAB_00023686;
              }
              bVar39 = sVar3 == 2;
              goto LAB_00023624;
            case 0x15:
              if (((*DAT_00023710 == '\0') || (-1 < (int)((uint)(byte)*DAT_0002371c << 0x1e))) &&
                 ((*DAT_00023714 == '\0' || (-1 < (int)((uint)(byte)*DAT_0002371c << 0x1d))))) {
                *(byte *)(ppuVar5 + 1) = 0;
              }
              else {
                if (3 < (*(ushort *)(DAT_00023728 + 0x620) & 0xf)) {
                  *(ushort *)(DAT_00023728 + 0x620) =
                       (*(ushort *)(DAT_00023728 + 0x620) & 0xfff0) + 3;
                }
                *(byte *)(ppuVar5 + 1) = *(byte *)(iVar29 + 0x620) & 0xf;
              }
              uVar41 = 0x3c;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              uVar28 = 0x15;
              ppuVar33 = ppuVar5 + 1;
              break;
            default:
              goto switchD_0002346a_default;
            }
            goto LAB_00023688;
          }
          if (uVar37 == 0x41) {
            if (*(byte *)((int)ppuVar5 + 1) == 0) {
              *DAT_000243c4 = *DAT_000243c4 & 0xfc;
              uVar28 = 0;
            }
            else {
              if (*(byte *)((int)ppuVar5 + 1) != 1) goto switchD_00024374_caseD_5;
              *DAT_000243c4 = (*DAT_000243c4 & 0xfc) + 1;
              uVar28 = 1;
            }
            uVar41 = 0;
            ppuVar33 = (undefined **)0x0;
            uVar37 = 0;
            bVar18 = 0x41;
            goto LAB_00024cf6;
          }
          bVar39 = uVar37 == 0x43;
          if (!bVar39) goto LAB_000233a2;
          bVar18 = *(byte *)((int)ppuVar5 + 1);
          if (bVar18 == 0x80) {
            if ((*(byte *)((int)DAT_00023b30 + 0x81) & 1) == 0) {
              FUN_00024efc(0x43,0x80,0,(undefined1 *)((int)DAT_00023b30 + 1),0x38);
              bVar18 = *(byte *)((int)ppuVar33 + 0x81) | 1;
              goto LAB_00023862;
            }
            uVar28 = 0x80;
          }
          else if (bVar18 < 0x81) {
            if (bVar18 != 0) {
              bVar39 = bVar18 == 1;
              ppuVar34 = DAT_00023b30;
              goto LAB_000237ea;
            }
            *(undefined1 *)DAT_00023b30 = 0;
            uVar28 = 0;
          }
          else if (bVar18 == 0x81) {
            if (-1 < (int)((uint)*(byte *)((int)DAT_00023b30 + 0x81) << 0x1e)) {
              FUN_00024efc(0x43,0x81,0,(undefined1 *)((int)DAT_00023b30 + 0x39),0x38);
              bVar18 = *(byte *)((int)ppuVar33 + 0x81) | 2;
              goto LAB_00023862;
            }
            uVar28 = 0x81;
          }
          else {
            if (bVar18 != 0x82) goto switchD_00024374_caseD_5;
            if (-1 < (int)((uint)*(byte *)((int)DAT_00023b30 + 0x81) << 0x1d)) {
              FUN_00024efc(0x43,0x82,0,(undefined1 *)((int)DAT_00023b30 + 0x71),0x10);
              bVar18 = *(byte *)((int)ppuVar33 + 0x81) | 4;
LAB_00023862:
              *(byte *)((int)ppuVar33 + 0x81) = bVar18;
              goto switchD_00024374_caseD_0;
            }
            uVar28 = 0x82;
          }
LAB_0002389c:
          uVar41 = 0;
          ppuVar33 = (undefined **)0x0;
          uVar37 = 0;
          bVar18 = 0x43;
          goto LAB_00024cf6;
        }
        bVar38 = *(byte *)((int)ppuVar5 + 1) == 1;
        ppuVar32 = ppuVar5;
LAB_000237be:
        if (!bVar38) goto switchD_00024374_caseD_5;
        uVar28 = 1;
        *(byte *)(ppuVar32 + 1) =
             (byte)(((uint)*(byte *)(DAT_00023b2c + (uint)*(byte *)(DAT_00023b24 + 6)) << 0x19) >>
                   0x1f);
        uVar41 = 1;
        uVar37 = (uint)*(ushort *)((int)ppuVar32 + 2);
        ppuVar33 = ppuVar5 + 1;
        bVar18 = 0x25;
        goto LAB_00024cf6;
      }
      bVar40 = SBORROW4(uVar37,0x61);
      bVar38 = (int)(uVar37 - 0x61) < 0;
      bVar39 = uVar37 == 0x61;
      if (!bVar39) {
        if (0x61 < uVar37) goto LAB_000233ee;
        if (uVar37 == 0x51) {
          bVar18 = *(byte *)((int)ppuVar5 + 1);
          if (bVar18 == 0x38) {
            bVar18 = *(byte *)(ppuVar5 + 1);
            if (4 < bVar18) {
              bVar18 = 7;
            }
            *(byte *)(DAT_00023f7c + 0x2b9) = *(byte *)(DAT_00023f7c + 0x2b9) & 0xf8 | bVar18 & 7;
            *piVar6 = 0;
            ppuVar33 = ppuVar5 + 1;
            uVar37 = 0;
            uVar28 = 0x38;
            uVar41 = 1;
          }
          else if (bVar18 < 0x39) {
            if (bVar18 == 0x18) {
              if (*(int *)(DAT_00023f70 + 0x30) == 1) {
                *(undefined4 *)(DAT_00023f70 + 0x38) = 5;
              }
              iVar29 = DAT_00023f74;
              ppuVar33 = ppuVar5 + 1;
              *(byte *)(DAT_00023f74 + 1) = *(byte *)((int)ppuVar5 + 2);
              *(byte *)(iVar29 + 2) = *(byte *)(ppuVar5 + 1);
              uVar41 = 2;
              uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
              uVar28 = 0x18;
            }
            else if (bVar18 < 0x19) {
              if (bVar18 == 0) {
                local_6c = (uint)*(byte *)(ppuVar5 + 1);
                if (local_6c == 6) {
                  local_6c = 0;
                }
                if (local_6c < 6) {
                  if (*DAT_00023b34 != '\x02') {
                    *DAT_00023b34 = '\x02';
                    pcVar23[1] = (char)local_6c;
                    goto LAB_000238dc;
                  }
                  goto LAB_000239a8;
                }
                goto switchD_00024374_caseD_5;
              }
              if (bVar18 == 10) {
                ppuVar33 = ppuVar5 + 1;
                *(byte *)(DAT_00023f7c + 0x2b9) =
                     *(byte *)(DAT_00023f7c + 0x2b9) & 0xdf | (*(byte *)(ppuVar5 + 1) & 1) << 5;
                uVar37 = 0;
                uVar28 = 10;
                uVar41 = 1;
              }
              else {
                bVar39 = bVar18 == 0xc;
LAB_00023952:
                iVar29 = _DAT_00023f80;
                pbVar25 = DAT_00023f64;
                if (!bVar39) {
LAB_000238ae:
                  pcVar23 = DAT_00023b34;
                  bVar38 = false;
                  if (bVar39) {
                    if (*DAT_00023b34 == '\x05') goto LAB_000239a8;
                    *DAT_00023b34 = '\x05';
                    pcVar23[1] = *(byte *)(ppuVar5 + 1);
                    pcVar23[2] = '\0';
                    goto LAB_000238dc;
                  }
                  goto LAB_000237be;
                }
                if (*(short *)((int)ppuVar5 + 2) == 0) {
                  if (DAT_00023f64[0x2f] == 0) {
                    pbVar25[0x1f] = 0xe8;
                    pbVar25[0x20] = 3;
                    pbVar25[0x21] = 0;
                    pbVar25[0x22] = 0;
                    if ((pbVar25[0x23] != 1) && (ppuVar32 = local_70, pbVar25[0x23] == 0)) {
                      local_70 = (undefined **)((int)&BusFault + 1);
                      ppuVar32 = local_70;
                    }
                    local_70 = ppuVar32;
                    FUN_0002d6e0(*(byte *)(ppuVar5 + 1));
                    FUN_0002d5cc((uint)local_70 & 0xffff,1000,0,1);
                  }
                }
                else if (*(short *)((int)ppuVar5 + 2) == 1) {
                  *(undefined1 *)(_DAT_00023f80 + 1) = 1;
                  *(byte *)(iVar29 + 2) = *(byte *)(ppuVar5 + 1);
                }
                uVar41 = 1;
                ppuVar33 = ppuVar5 + 1;
                uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
                uVar28 = 0xc;
              }
            }
            else if (bVar18 == 0x20) {
              uVar37 = (uint)*(byte *)(ppuVar5 + 1);
              uVar28 = (uint)*(ushort *)(ppuVar5 + 1);
              uVar41 = (uint)*(byte *)((int)ppuVar5 + 2);
              if (0xbc < uVar41) goto switchD_00024374_caseD_5;
              bVar39 = *(byte *)((int)ppuVar5 + 3) == 0;
              ppuVar32 = ppuVar5;
LAB_000239d0:
              if (!bVar39) goto LAB_00023952;
              if (uVar28 < 0xbd) {
                uVar31 = (ushort)(byte)puVar21[uVar28];
LAB_00023a1e:
                *(ushort *)(DAT_00023b28 + (uint)(byte)puVar21[uVar41] * 2 + 0xca) = uVar31;
              }
              else {
                if (uVar37 != 0xff) {
                  if ((uVar37 == 199) || (uVar37 == 200)) {
                    uVar31 = (ushort)uVar37 | 0xa000;
                  }
                  else {
                    if (uVar37 != 0xd3) {
                      *(short *)(DAT_00023b28 + (uint)(byte)puVar21[uVar41] * 2 + 0xca) =
                           (short)uVar28;
                      goto LAB_00023a00;
                    }
                    uVar31 = 0xa0d3;
                  }
                  goto LAB_00023a1e;
                }
                *(ushort *)(DAT_00023b28 + (uint)(byte)puVar21[uVar41] * 2 + 0xca) =
                     (ushort)(byte)puVar21[uVar41];
              }
LAB_00023a00:
              uVar41 = 0x3c;
              uVar37 = (uint)*(ushort *)((int)ppuVar32 + 2);
              ppuVar33 = ppuVar5 + 1;
              uVar28 = 0x20;
            }
            else {
              if (bVar18 != 0x2c) {
                bVar39 = bVar18 == 0x31;
                if (!bVar39) goto LAB_000238ae;
                if (*(byte *)(ppuVar5 + 1) < 4) {
                  if (((*DAT_00023710 != '\0') && ((int)((uint)*DAT_00023f78 << 0x1e) < 0)) ||
                     ((*DAT_00023714 != '\0' && ((int)((uint)*DAT_00023f78 << 0x1d) < 0)))) {
                    *(ushort *)(DAT_00023f7c + 0x620) =
                         *(ushort *)(DAT_00023f7c + 0x620) & 0xfff0 | *(byte *)(ppuVar5 + 1) & 0xf;
                  }
                  ppuVar33 = ppuVar5 + 1;
                  uVar37 = 0;
                  uVar28 = 0x31;
                  uVar41 = 1;
                  goto LAB_00023d34;
                }
                goto switchD_00024374_caseD_5;
              }
              uVar28 = (uint)*(byte *)((int)ppuVar5 + 2);
              uVar41 = DAT_00023b38 + 0x6c;
              iVar29 = DAT_00023b24 + 0x20;
              if ((uVar28 == 4) || (uVar28 == 5)) {
                uVar37 = (uint)*(byte *)((int)ppuVar5 + 3);
                if (uVar37 == 0) {
                  uVar37 = (uint)(byte)pcVar4[4];
                  bVar39 = false;
                  if (uVar37 == 0x1e) {
                    iVar30 = *(int *)(iVar29 + uVar28 * 4);
                    ppuVar32 = (undefined **)ppuVar5[1];
                    uVar37 = iVar30 + 0x1e;
                    *(undefined ***)(iVar30 + 0x1e) = ppuVar32;
                    *(undefined2 *)(iVar30 + 0x22) = *(undefined2 *)(ppuVar5 + 2);
                    *(byte *)(iVar30 + 0x24) = *(byte *)((int)ppuVar5 + 10);
                    pcVar4[4] = '%';
                    bVar18 = *(byte *)((int)ppuVar5 + 2);
                    uVar28 = (uint)bVar18;
                    uVar41 = (uint)*(byte *)(uVar41 + uVar28);
                    bVar39 = false;
                    if (uVar41 == 0x25) {
                      pcVar4[4] = '\0';
                      goto LAB_00023b76;
                    }
                  }
                }
                else {
                  if (uVar37 == 1) {
                    if (pcVar4[4] != '\x0e') goto LAB_00023b4a;
                    FUN_0001c590(*(int *)(iVar29 + uVar28 * 4) + 0xe,ppuVar5 + 1,0x10);
                    pcVar4[4] = pcVar4[4] + '\x10';
                    goto LAB_00023b88;
                  }
                  bVar39 = uVar37 == 2;
                }
LAB_00023aa0:
                if (!bVar39) goto LAB_000239d0;
                iVar29 = *(int *)(iVar29 + uVar28 * 4);
LAB_00023b0c:
                FUN_0001c590((uint)(byte)pcVar4[4] + iVar29,ppuVar5 + 1,0xe);
                pcVar4[4] = '\x0e';
LAB_00023b88:
                uVar41 = 0x3c;
                uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
                ppuVar33 = ppuVar5 + 1;
              }
              else {
                if (uVar28 == 7) {
                  uVar28 = (uint)*(byte *)((int)ppuVar5 + 3);
                  if (uVar28 != 0) {
                    bVar39 = uVar28 == 1;
                    uVar37 = 0x2c;
                    if (!bVar39) goto LAB_00023aa0;
                    iVar29 = *(int *)(DAT_00023b24 + 0x3c);
                    goto LAB_00023b0c;
                  }
                  if (pcVar4[4] == '\x0e') {
                    iVar29 = *(int *)(DAT_00023b24 + 0x3c);
                    *(undefined **)(iVar29 + 0xe) = ppuVar5[1];
                    *(undefined **)(iVar29 + 0x12) = ppuVar5[2];
                    *(undefined **)(iVar29 + 0x16) = ppuVar5[3];
                    pcVar4[4] = '\x1a';
                    bVar18 = *(byte *)((int)ppuVar5 + 2);
                    if (*(char *)(uVar41 + bVar18) == '\x1a') {
                      pcVar4[4] = '\0';
LAB_00023b76:
                      pbVar25 = DAT_00023f64;
                      *DAT_00023f64 = *DAT_00023f64 & 0xf3;
                      pbVar25[0x2c] = bVar18;
                      FUN_000231e0();
                      goto LAB_00023b88;
                    }
                  }
                  else {
LAB_00023b4a:
                    pcVar4[4] = '\0';
                  }
                  goto switchD_00024374_caseD_5;
                }
                FUN_0001c590(*(undefined4 *)(iVar29 + (uint)*(ushort *)((int)ppuVar5 + 2) * 4),
                             ppuVar5 + 1,*(undefined1 *)(uVar41 + *(ushort *)((int)ppuVar5 + 2)));
                pbVar25 = (byte *)(iVar30 + -0x27);
                *pbVar25 = *pbVar25 & 0xf3;
                *(byte *)(DAT_00023b24 + 5) = *(byte *)((int)ppuVar5 + 2);
                FUN_000231e0();
                uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
                uVar41 = (uint)*(byte *)(uVar41 + uVar37);
                ppuVar33 = *(undefined ***)(iVar29 + uVar37 * 4);
              }
              uVar28 = 0x2c;
            }
          }
          else if (bVar18 == 0x55) {
            if (*(ushort *)(ppuVar5 + 1) < 0xbd) {
              local_6c = (uint)(byte)DAT_00023718[*(ushort *)(ppuVar5 + 1)];
            }
            if (*(ushort *)((int)ppuVar5 + 6) < 0xbd) {
              unaff_r10 = (uint)(byte)DAT_00023718[*(ushort *)((int)ppuVar5 + 6)];
            }
            if (((0x8d < local_6c - 4) && (7 < local_6c - 0xe0)) ||
               ((0x8d < unaff_r10 - 4 && (7 < unaff_r10 - 0xe0)))) goto switchD_00024374_caseD_5;
            if (*(byte *)(ppuVar5 + 2) == 1) {
              iVar29 = DAT_00023f68 + local_6c * 2;
              if ((*(byte *)(iVar29 + 5) >> 3 != 0) ||
                 (iVar30 = DAT_00023f68 + unaff_r10 * 2, *(byte *)(iVar30 + 5) >> 3 != 0))
              goto switchD_00024374_caseD_5;
              *(byte *)(iVar29 + 5) = (*(byte *)(iVar29 + 5) & 7) + 8 & 0xf8;
              *(char *)(iVar29 + 4) = (char)unaff_r10;
              *(byte *)(iVar30 + 5) = (*(byte *)(iVar30 + 5) & 7) + 8 & 0xf8;
              *(char *)(iVar30 + 4) = (char)local_6c;
            }
            else {
              if ((*(byte *)(ppuVar5 + 2) != 0) ||
                 (iVar29 = DAT_00023f68 + local_6c * 2, *(byte *)(iVar29 + 4) != unaff_r10))
              goto switchD_00024374_caseD_5;
              *(undefined1 *)(iVar29 + 5) = 0;
              iVar24 = iVar24 + unaff_r10 * 2;
              *(undefined1 *)(iVar29 + 4) = 0;
              *(undefined1 *)(iVar24 + 5) = 0;
              *(undefined1 *)(iVar24 + 4) = 0;
            }
            FUN_00032ce8(DAT_00023f68,1);
            *puVar8 = 1;
            pcVar4[6] = '\x01';
            uVar41 = 0x3c;
            ppuVar33 = ppuVar5 + 1;
            uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
            uVar28 = 0x55;
          }
          else if (bVar18 < 0x56) {
            if (bVar18 == 0x39) {
              *(byte *)(DAT_00023f7c + 0x2b9) =
                   *(byte *)(DAT_00023f7c + 0x2b9) & 0xe7 | (*(byte *)(ppuVar5 + 1) & 3) << 3;
              FUN_0002fc80();
              ppuVar33 = ppuVar5 + 1;
              uVar37 = 0;
              uVar28 = 0x39;
              uVar41 = 1;
            }
            else if (bVar18 == 0x3a) {
              *(byte *)(DAT_00023f7c + 0x2b8) = *(byte *)(ppuVar5 + 1);
              FUN_0002fc80();
              FUN_0002b45c();
              ppuVar33 = ppuVar5 + 1;
              uVar37 = 0;
              uVar28 = 0x3a;
              uVar41 = 1;
            }
            else {
              bVar39 = bVar18 == 0x41;
              if (!bVar39) goto LAB_000238ae;
              *(byte *)(DAT_00023f6c + (uint)DAT_00023f64[0x2d]) =
                   *(byte *)(DAT_00023f6c + (uint)DAT_00023f64[0x2d]) & 0xef |
                   (*(byte *)(ppuVar5 + 1) & 1) << 4;
              ppuVar33 = ppuVar5 + 1;
              uVar37 = 0;
              uVar28 = 0x41;
              uVar41 = 1;
            }
          }
          else if (bVar18 == 0x56) {
            FUN_00022f18(DAT_00023f68);
            FUN_00032ce8(DAT_00023f68,1);
            *puVar8 = 1;
            pcVar4[6] = '\x01';
            uVar41 = 0x3c;
            ppuVar33 = ppuVar5 + 1;
            uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
            uVar28 = 0x56;
          }
          else if (bVar18 == 0x57) {
            *(byte *)(DAT_00023f6c + (uint)DAT_00023f64[0x2d]) =
                 *(byte *)(DAT_00023f6c + (uint)DAT_00023f64[0x2d]) & 0xbf |
                 (*(byte *)(ppuVar5 + 1) & 1) << 6;
            FUN_00032ce8(DAT_00023f68,1);
            FUN_00027838(1,DAT_00023f6c);
            uVar41 = 0x3c;
            ppuVar33 = ppuVar5 + 1;
            uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
            uVar28 = 0x57;
          }
          else {
            bVar39 = bVar18 == 0x90;
            if (!bVar39) goto LAB_000238ae;
            if ((*DAT_00023f64 & 3) != 0) {
              FUN_00031d1c(*(byte *)(ppuVar5 + 1));
              FUN_00031d30(*(byte *)((int)ppuVar5 + 5));
            }
            ppuVar33 = ppuVar5 + 1;
            uVar37 = 0;
            uVar28 = 0x90;
            uVar41 = 0x3c;
          }
LAB_00023d34:
          bVar18 = 0x51;
        }
        else if (uVar37 == 0x52) {
          bVar39 = *(byte *)((int)ppuVar5 + 1) == 0x90;
LAB_00023e26:
          if (!bVar39) goto switchD_00024374_caseD_5;
          if ((*DAT_00023f64 & 3) != 0) {
            bVar18 = FUN_000292d8();
            *(byte *)(ppuVar5 + 1) = bVar18;
            bVar18 = FUN_000292e8();
            *(byte *)((int)ppuVar5 + 5) = bVar18;
          }
          ppuVar33 = ppuVar5 + 1;
          uVar37 = 0;
          uVar28 = 0x90;
          bVar18 = 0x52;
          uVar41 = 0x3c;
        }
        else {
          bVar39 = uVar37 == 0x53;
          puVar36 = DAT_00023718;
          if (!bVar39) goto LAB_000233a2;
          if (*(byte *)((int)ppuVar5 + 3) == 0) {
            bVar18 = *(byte *)((int)ppuVar5 + 1);
            if ((bVar18 < 0xbd) && (bVar19 = DAT_00023718[bVar18], bVar19 != 0xd0)) {
              if (bVar19 < 0xd1) {
                if ((bVar19 != 0x39) && ((bVar19 != 0x47 && (bVar19 != 0x53)))) {
LAB_00024166:
                  pbVar25 = DAT_000243c8 + 3;
                  *DAT_000243c8 = bVar18;
                  *pbVar25 = 0;
                  FUN_0001c5e0(pbVar11 + 4,400);
                  goto LAB_00024180;
                }
              }
              else if ((bVar19 != 0xe2) && (bVar19 != 0xe8)) goto LAB_00024166;
            }
            *DAT_000243c8 = 0;
            pbVar11[3] = 0;
          }
LAB_00024180:
          pbVar25 = DAT_000243c8;
          bVar18 = *(byte *)((int)ppuVar5 + 2);
          uVar28 = (uint)DAT_000243c8[3];
          uVar37 = uVar28 + bVar18;
          DAT_000243c8[3] = (byte)uVar37;
          if ((*pbVar25 == 0) || (0x65 < (uVar37 & 0xff))) {
            *pbVar25 = 0;
            pbVar25[3] = 0;
            goto switchD_00024374_caseD_5;
          }
          FUN_0001c590(pbVar25 + uVar28 * 4 + 4,ppuVar5 + 1,(uint)bVar18 << 2);
          if ((pbVar25[(uint)pbVar25[3] * 4] == 0xff) && (pbVar25[(uint)pbVar25[3] * 4 + 1] == 0)) {
            local_6c = (uint)(byte)puVar21[*pbVar25];
            if (*pbVar25 - 0xa4 < 3) {
              *pbVar25 = puVar21[*pbVar25] + 0x6e;
            }
            FUN_0002c144();
            if ((DAT_000243c4[0x2f] == 7) || (2 < local_6c - 0xd4)) {
              *(ushort *)(DAT_000243cc + local_6c * 2 + 0xca) = *pbVar25 | 0xa000;
            }
            pbVar25[3] = pbVar25[3] - 1;
          }
          uVar41 = 0x3c;
          ppuVar33 = (undefined **)(pbVar25 + uVar28 * 4 + 4);
          uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
          uVar28 = (uint)*pbVar25;
          bVar18 = 0x53;
        }
        goto LAB_00024cf6;
      }
    }
    if (uVar37 == 0x72) {
      FUN_0002d5cc(*(byte *)((int)ppuVar5 + 5) + 0x3f,1000,0);
      uVar41 = 2;
      ppuVar33 = ppuVar5 + 1;
      uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
      uVar28 = (uint)*(byte *)((int)ppuVar5 + 1);
      bVar18 = 0x72;
      goto LAB_00024cf6;
    }
    if (uVar37 < 0x73) {
      if (uVar37 == 0x68) {
        if (*(byte *)((int)ppuVar5 + 1) != 0) goto switchD_00024374_caseD_5;
        local_70 = (undefined **)0x0;
        goto LAB_00024258;
      }
      if (uVar37 < 0x69) {
        if (((uVar37 == 0x65) || (uVar37 == 0x66)) || (bVar39 = false, uVar37 == 0x67))
        goto LAB_00024226;
        goto LAB_000233a2;
      }
      if (uVar37 != 0x69) {
        bVar39 = uVar37 == 0x71;
        if (!bVar39) goto LAB_000233a2;
        if (*(byte *)((int)ppuVar5 + 1) == 0) {
          iVar30 = 0;
          iVar29 = 0;
          do {
            if (*(char *)(DAT_000243cc + iVar29 * 8 + 0x2c2) != '\0') {
              iVar30 = iVar30 + 1;
            }
            iVar29 = iVar29 + 1;
          } while (iVar29 < 8);
          if (iVar30 < 2) {
            if (*(byte *)((int)ppuVar5 + 5) != 0) goto LAB_000242da;
            goto switchD_00024374_caseD_5;
          }
          if (*(byte *)((int)ppuVar5 + 5) == 0) {
            uVar27 = 0;
          }
          else {
LAB_000242da:
            uVar27 = 1;
          }
          bVar18 = *(byte *)(ppuVar5 + 1);
          *(undefined1 *)(DAT_000243cc + (uint)bVar18 * 8 + 0x2c2) = uVar27;
          if ((uint)bVar18 == (uint)pbVar10[0x2f]) {
            FUN_0002bfe4();
            FUN_0003362c(0x91,0,0,pbVar10[0x2f]);
          }
          uVar31 = *(ushort *)((int)ppuVar5 + 2);
          uVar28 = 0;
        }
        else {
          if (*(byte *)((int)ppuVar5 + 1) != 1) goto switchD_00024374_caseD_5;
          local_70 = (undefined **)(uint)*(ushort *)((int)ppuVar5 + 5);
          local_6c = (uint)*(ushort *)((int)ppuVar5 + 7);
          FUN_0002c04c(*(byte *)(ppuVar5 + 1),local_70);
          uVar31 = *(ushort *)((int)ppuVar5 + 2);
          uVar28 = 1;
        }
        uVar41 = 0x3c;
        ppuVar33 = ppuVar5 + 1;
        uVar37 = (uint)uVar31;
        bVar18 = 0x71;
        goto LAB_00024cf6;
      }
      if ((*(byte *)((int)ppuVar5 + 1) == 0) &&
         (bVar18 = *(byte *)(ppuVar5 + 1), *(byte *)(DAT_000243d4 + 9) = bVar18, bVar18 != 0)) {
        *DAT_000243d8 = 500;
      }
      uVar41 = 0x3c;
      ppuVar33 = ppuVar5 + 1;
      uVar28 = 0;
      uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
      bVar18 = 0x69;
      goto LAB_00024cf6;
    }
    if (uVar37 != 0xfa) {
      if (0xfa < uVar37) {
        if (uVar37 == 0xfc) {
          bVar18 = *(byte *)((int)ppuVar5 + 1);
          if (bVar18 >> 6 == 0) {
            pcVar4[0x1c] = '\0';
            pcVar4[0x1d] = '\0';
            pcVar4[0x1e] = '\0';
            pcVar4[0x1f] = '\0';
            pcVar4[0x20] = '\0';
            pcVar4[0x21] = '\0';
            pcVar4[0x22] = '\0';
            pcVar4[0x23] = '\0';
          }
          if (*(uint *)(pcVar4 + 0x1c) == (uint)(bVar18 >> 6)) {
            uVar37 = *(uint *)(pcVar4 + 0x1c) + 1;
            *(uint *)(pcVar4 + 0x1c) = uVar37;
            if (3 < uVar37) {
              pcVar4[0x1c] = '\x01';
              pcVar4[0x1d] = '\0';
              pcVar4[0x1e] = '\0';
              pcVar4[0x1f] = '\0';
            }
            local_70 = (undefined **)(bVar18 & 0x3f);
            if (local_70 < (undefined **)((int)&Reserved2 + 1)) {
              if ((bVar18 & 0x3f) != 0) goto LAB_00024d4e;
              pbVar25 = *(byte **)(pcVar4 + 8);
            }
            else {
              local_70 = &Reserved2;
LAB_00024d4e:
              FUN_0001c590(DAT_00024e4c + *(int *)(pcVar4 + 8),(byte *)((int)ppuVar5 + 2),local_70);
              pbVar25 = (byte *)((int)local_70 + *(int *)(pcVar4 + 8));
              *(byte **)(pcVar4 + 8) = pbVar25;
            }
            if (((byte *)((int)&SysTick + 3) < pbVar25) || (local_70 < &Reserved2)) {
              *pcVar4 = '\x01';
            }
            FUN_00024efc(0xfc,((byte)pcVar4[0x20] & 3) << 6,0,0,0);
            iVar29 = *(int *)(pcVar4 + 0x20);
            *(uint *)(pcVar4 + 0x20) = iVar29 + 1U;
            if (3 < iVar29 + 1U) {
              pcVar4[0x20] = '\x01';
              pcVar4[0x21] = '\0';
              pcVar4[0x22] = '\0';
              pcVar4[0x23] = '\0';
            }
          }
          goto LAB_00024d90;
        }
        bVar39 = uVar37 == 0xfd;
        if (!bVar39) goto LAB_000233a2;
        bVar18 = *(byte *)((int)ppuVar5 + 1);
        if ((bVar18 != 0xa0) && (bVar18 != 0xa1)) {
          if (bVar18 != 0xa2) goto switchD_0002346a_default;
          bVar18 = *(byte *)(ppuVar5 + 1);
          if (bVar18 != *DAT_00024e48) {
            *DAT_00024e48 = bVar18;
            if (bVar18 == 1) {
              FUN_0002cfc4();
            }
            else {
              FUN_0002cf80();
            }
          }
          goto LAB_00024d90;
        }
        if ((int)((uint)*DAT_00024e44 << 0x1e) < 0) {
          uVar22 = 0x14;
        }
        else {
          uVar22 = 0x3c;
        }
        local_6c = FUN_000292f8(ppuVar5 + 1,uVar22);
        uVar41 = local_6c & 0xff;
        uVar28 = (uint)*(byte *)((int)ppuVar5 + 1);
        ppuVar33 = ppuVar5 + 1;
        uVar37 = 0;
        bVar18 = 0xfd;
        goto LAB_00024cf6;
      }
      if (uVar37 == 0x7d) {
        uVar28 = (uint)*(byte *)((int)ppuVar5 + 1);
        if (uVar28 == 2) {
          sVar3 = *(short *)((int)ppuVar5 + 2);
          if (sVar3 == 0) {
            *(byte *)(ppuVar5 + 1) = 0x83;
            *(byte *)((int)ppuVar5 + 5) = 0x1a;
            FUN_00024efc(0x7d,2,0,ppuVar5 + 1,2);
            goto LAB_00023f02;
          }
          if (sVar3 == 1) {
            local_68[0] = s_ROG_AZOTH_00023fa8[0];
            local_68[1] = s_ROG_AZOTH_00023fa8[1];
            local_68[2] = s_ROG_AZOTH_00023fa8[2];
            local_68[3] = s_ROG_AZOTH_00023fa8[3];
            local_68[4] = s_ROG_AZOTH_00023fa8[4];
            local_68[5] = s_ROG_AZOTH_00023fa8[5];
            local_68[6] = s_ROG_AZOTH_00023fa8[6];
            local_68[7] = s_ROG_AZOTH_00023fa8[7];
            uStack_60 = ram0x00023fb0;
            uVar37 = 0;
            goto LAB_00023ee0;
          }
          if (sVar3 == 2) {
            *(byte *)(ppuVar5 + 1) = 0x13;
            *(byte *)((int)ppuVar5 + 5) = 4;
            unaff_r10 = 2;
          }
          goto LAB_00023f02;
        }
        if (2 < uVar28) {
          if (uVar28 == 3) {
            *(byte *)(ppuVar5 + 1) = 0;
            uVar37 = 0;
          }
          else {
            bVar39 = uVar28 == 0x20;
            if (!bVar39) goto LAB_00023e26;
            if (*(short *)((int)ppuVar5 + 2) != 2) {
              bVar39 = *(short *)((int)ppuVar5 + 2) == 5;
              goto LAB_00023f24;
            }
            if (*DAT_00023710 == '\0' && *DAT_00023714 == '\0') {
              *(byte *)(ppuVar5 + 1) = 0;
            }
            else {
              *(byte *)(ppuVar5 + 1) = 1;
            }
            uVar37 = 2;
          }
          uVar41 = 1;
          goto LAB_00023fca;
        }
        if (uVar28 == 0) {
          bVar39 = *(byte *)(ppuVar5 + 1) == 0xaa;
          goto LAB_00023e66;
        }
        bVar39 = uVar28 == 1;
LAB_00023e54:
        if (!bVar39) goto LAB_00023e26;
        *(byte *)(ppuVar5 + 1) = 1;
        FUN_00024efc(0x7d,uVar28,0,ppuVar5 + 1,1);
        FUN_000277cc(s_GET_SUPPORT_00023f9b + 1);
        goto switchD_00024374_caseD_0;
      }
      bVar39 = uVar37 == 0xc0;
      if (!bVar39) goto LAB_000233a2;
      uVar28 = DAT_000243c0 + 0x3d;
      if (*(byte *)((int)ppuVar5 + 1) == 0x81) {
        if ((*DAT_000243c4 & 0xc) == 0) {
          FUN_000231e0(0xf1);
          *(undefined1 *)(iVar9 + 0x3c) = 0;
        }
        *pbVar10 = (*pbVar10 & 0xf3) + 4;
        FUN_0001c590(DAT_000243c0,ppuVar5 + 1,0x3c);
        if (*(ushort *)((int)ppuVar5 + 2) < 0x10) {
          uVar37 = (uint)*(byte *)((int)ppuVar5 + 2);
          pbVar25 = (byte *)(iVar9 + 0x3c);
          bVar18 = *pbVar25;
          *pbVar25 = (byte)(bVar18 + uVar37);
          FUN_00024efc(0xc0,0x82,bVar18 + uVar37 & 0xff,uVar28,0x17);
          *pbVar25 = 0;
        }
        else {
          uVar37 = 0xf;
          *(char *)(iVar9 + 0x3c) = *(char *)(iVar9 + 0x3c) + '\x0f';
        }
        FUN_00032384(1);
        for (iVar29 = 0; iVar29 < (int)uVar37; iVar29 = iVar29 + 1) {
          bVar18 = *(byte *)(iVar9 + iVar29 * 4);
          FUN_00032a08(bVar18 >> 3,bVar18 & 7,iVar9 + iVar29 * 4 + 1);
        }
      }
      else {
        bVar39 = *(byte *)((int)ppuVar5 + 1) == 0x83;
        if (!bVar39) {
LAB_00023f24:
          if (!bVar39) goto LAB_00023e54;
          if (((*(byte *)(ppuVar5 + 1) != 0xaa) || (*(byte *)((int)ppuVar5 + 5) != 0x43)) ||
             ((*(byte *)((int)ppuVar5 + 6) != 0x44 ||
              ((*(byte *)((int)ppuVar5 + 7) != 0x43 || (*(byte *)(ppuVar5 + 2) != 0xaa))))))
          goto switchD_00024374_caseD_0;
          FUN_000277cc(s_leave_CDC_mode_000243b0);
          FUN_000334d8(0x32);
          uVar41 = 5;
          uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
          uVar28 = (uint)*(byte *)((int)ppuVar5 + 1);
          goto LAB_00023fca;
        }
        uVar31 = *(ushort *)((int)ppuVar5 + 2);
        uVar37 = (uint)uVar31;
        if ((*DAT_000243c4 & 0xf) >> 2 != 1) {
          *DAT_000243c4 = (*DAT_000243c4 & 0xf3) + 4;
          *(undefined1 *)(iVar9 + 0x3c) = 0;
          FUN_000231e0(0xf1);
        }
        uVar41 = (uVar37 & 0xfff) >> 8;
        FUN_0001c590(DAT_000243c0,ppuVar5 + 1,uVar41 << 2);
        if ((uVar31 >> 0xc == 1) || (*(uint *)(pcVar4 + 0x18) < (uVar37 & 0xff))) {
          FUN_00024efc(0xc0,0x82,*(undefined1 *)(iVar9 + 0x3c),uVar28,0x17);
          *(undefined1 *)(iVar9 + 0x3c) = 0;
        }
        *(uint *)(pcVar4 + 0x18) = uVar37 & 0xff;
        *(char *)(iVar9 + 0x3c) = *(char *)(iVar9 + 0x3c) + (char)((uVar37 & 0xfff) >> 8);
        FUN_00032384(1);
        for (iVar29 = 0; iVar29 < (int)uVar41; iVar29 = iVar29 + 1) {
          bVar18 = *(byte *)(iVar9 + iVar29 * 4);
          FUN_00032a08(bVar18 >> 3,bVar18 & 7,iVar9 + iVar29 * 4 + 1);
        }
      }
      FUN_00032384(0);
      goto switchD_00024374_caseD_0;
    }
    bVar18 = *(byte *)((int)ppuVar5 + 1);
    if (bVar18 == 0) {
      if (*(short *)((int)ppuVar5 + 2) == -0x5a2d) {
        DAT_000243e0[4] = 1;
        if (puVar35[6] != 0) {
          *DAT_000247dc = 1;
        }
      }
      else {
        DAT_000243e0[4] = 0;
        *DAT_000243e4 = *DAT_000243e4 & 0xfe;
        uVar31 = *puVar12;
        if ((int)((uint)uVar31 << 0x1e) < 0) {
          *puVar12 = uVar31 & 0xfffd;
          FUN_0002e38c();
          FUN_0002e274(0x3f);
          FUN_00032598(0);
        }
      }
      if ((int)((uint)*DAT_000247d8 << 0x1d) < 0) {
        FUN_00029a88();
      }
      uVar41 = 0;
      ppuVar33 = (undefined **)0x0;
      uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
      uVar28 = 0;
      goto LAB_00024c72;
    }
    if (DAT_000243e0[4] == 0) goto switchD_00024374_caseD_5;
    if (bVar18 == 0xd) {
      bVar39 = false;
      if (*(short *)((int)ppuVar5 + 2) == 0) {
        bVar18 = *DAT_00024800;
        *(byte *)(ppuVar5 + 1) = bVar18;
        if ((bVar18 == 1) && (puVar35[6] != 0)) {
          FUN_000260e0(8,(byte *)((int)ppuVar5 + 5),3);
        }
        else {
          *(byte *)((int)ppuVar5 + 5) = 0;
          *(byte *)((int)ppuVar5 + 6) = 0;
          *(byte *)((int)ppuVar5 + 7) = 0;
        }
        uVar41 = 4;
        ppuVar33 = ppuVar5 + 1;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        uVar28 = 0xd;
        goto LAB_00024c72;
      }
LAB_00024672:
      if (!bVar39) goto switchD_00024822_caseD_1;
      FUN_0003167c(*(byte *)(ppuVar5 + 1));
      uVar41 = 1;
      goto LAB_000246c8;
    }
    if (bVar18 < 0xe) {
      switch(bVar18) {
      case 0:
        goto switchD_00024374_caseD_0;
      case 1:
        if (*(short *)((int)ppuVar5 + 2) != 0) {
          bVar39 = *(short *)((int)ppuVar5 + 2) == 1;
          goto LAB_0002443e;
        }
        *(undefined1 *)(DAT_000247e0 + 4) = 0x1e;
        *(undefined1 *)(iVar13 + 5) = 100;
        *(undefined1 *)(iVar13 + 6) = 0;
        *(undefined1 *)(iVar13 + 7) = 0xff;
        *(undefined1 *)(iVar13 + 8) = 0xff;
        *(byte *)(iVar13 + 9) = *(byte *)(ppuVar5 + 1);
        *(byte *)(iVar13 + 10) = *(byte *)((int)ppuVar5 + 5);
        *(byte *)(iVar13 + 0xb) = *(byte *)((int)ppuVar5 + 6);
        *(undefined1 *)(iVar13 + 0xc) = 0;
        *(undefined1 *)(iVar13 + 0xd) = 0;
        *(undefined1 *)(iVar13 + 0xe) = 0;
        *(undefined1 *)(iVar13 + 0xf) = 0;
        *(undefined1 *)(iVar13 + 0x10) = 0;
        *(undefined1 *)(iVar13 + 0x11) = 0;
        FUN_0003222c(0);
        uVar41 = 3;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        goto LAB_0002448a;
      case 2:
        bVar39 = false;
        if (*(short *)((int)ppuVar5 + 2) != 1) goto LAB_0002443e;
        uVar41 = FUN_00028dd4(ppuVar5 + 1);
        ppuVar33 = ppuVar5 + 1;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        uVar28 = 2;
        goto LAB_00024c72;
      case 3:
        bVar39 = false;
        if (*(short *)((int)ppuVar5 + 2) == 0) {
          *(byte *)(ppuVar5 + 1) = (byte)DAT_000243e0[0xc];
          *(byte *)((int)ppuVar5 + 5) = (byte)puVar35[0xd];
          ppuVar33 = ppuVar5 + 1;
          uVar28 = 3;
          uVar41 = 2;
          uVar37 = 0;
          goto LAB_00024c72;
        }
LAB_0002443e:
        if (!bVar39) goto switchD_00024374_caseD_0;
        uVar37 = 1;
        *DAT_000247e4 = *(byte *)(ppuVar5 + 1);
        uVar41 = 1;
LAB_0002448a:
        ppuVar33 = ppuVar5 + 1;
        uVar28 = 1;
        goto LAB_00024c72;
      case 4:
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        switch(uVar37) {
        case 0:
          puVar36 = *(undefined **)(pcVar4 + 0x30);
          puVar21 = *(undefined **)(pcVar4 + 0x34);
          ppuVar5[1] = *(undefined **)(pcVar4 + 0x2c);
          ppuVar5[2] = puVar36;
          ppuVar5[3] = puVar21;
          bVar18 = *(byte *)((int)ppuVar5 + 10);
          if (bVar18 == 0) {
            bVar18 = 6;
          }
          *(byte *)((int)ppuVar5 + 10) = bVar18;
          uVar41 = 0xc;
          break;
        case 1:
          FUN_0002992c();
          FUN_0002994c(0);
          iVar29 = 0;
          iVar30 = DAT_000247ec + (uint)*DAT_000247e8 * 0x18;
          do {
            *(byte *)((int)ppuVar5 + iVar29 + 4) = *(byte *)(iVar30 + iVar29 + 1);
            iVar29 = iVar29 + 1;
          } while (iVar29 < 6);
          uVar41 = 6;
          uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
          break;
        case 2:
          ppuVar5[1] = DAT_000f4000;
          uVar41 = 4;
          break;
        case 3:
          *(byte *)(ppuVar5 + 1) = 0xff;
          *(byte *)((int)ppuVar5 + 5) = 0xff;
          uVar41 = 2;
          break;
        case 4:
          if ((*DAT_000247d8 & 1) == 0) {
            uVar22 = 0x1b;
            goto LAB_00024cce;
          }
          FUN_00025c04(ppuVar5 + 1,0x10);
          uVar41 = 0x10;
          uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
          break;
        case 5:
          FUN_000270ac();
          FUN_0003de50(0x20);
          FUN_0003d8de(0x20,1,0,1,7,0);
          FUN_0003de50(0x21);
          FUN_0003d8de(0x21,1,0,1,7,0);
          FUN_0003de50(0x22);
          FUN_0003d8de(0x22,1,0,1,7,0);
          FUN_0003de50(0x23);
          FUN_0003d8de(0x23,1,0,1,7,0);
          FUN_0003de50(0x24);
          FUN_0003d8de(0x24,1,0,1,7,0);
          thunk_FUN_0002b37c();
          *(byte *)(ppuVar5 + 1) = (byte)puVar35[2];
          *(byte *)((int)ppuVar5 + 5) = (byte)puVar35[3];
          uVar41 = 2;
          ppuVar33 = ppuVar5 + 1;
          uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
          uVar28 = 5;
          goto LAB_00024c72;
        default:
          goto switchD_00024374_caseD_0;
        }
        ppuVar33 = ppuVar5 + 1;
        uVar28 = 4;
        goto LAB_00024c72;
      default:
        goto switchD_00024374_caseD_5;
      case 6:
        ppuVar33 = ppuVar5 + 1;
        *DAT_000247f0 = 6;
        puVar14[1] = 1;
        puVar14[2] = 0;
        puVar14[8] = 0;
        puVar14[9] = puVar14[9] & 0xfd | 1;
        uVar41 = 1;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        uVar28 = 6;
        goto LAB_00024c72;
      case 7:
        bVar18 = *(byte *)(ppuVar5 + 1);
        bVar19 = *(byte *)(DAT_000247f8 + (uint)*(byte *)(DAT_000247f4 + 6));
        if (bVar18 == 0) {
          bVar19 = bVar19 & 0xf7;
        }
        else {
          bVar19 = bVar19 | 8;
        }
        bVar1 = *(byte *)(DAT_000247f4 + 6);
        *(byte *)(DAT_000247f8 + (uint)bVar1) = bVar19;
        bVar2 = *(byte *)((int)ppuVar5 + 5);
        if (bVar2 == 0) {
          bVar19 = bVar19 & 0xfb;
        }
        else {
          bVar19 = bVar19 | 4;
        }
        *(byte *)(iVar15 + (uint)bVar1) = bVar19;
        local_6c = (uint)bVar18 | (uint)bVar2 << 1;
        FUN_000298c4(0,&local_6c);
        uVar41 = 2;
        ppuVar33 = ppuVar5 + 1;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        uVar28 = 7;
        goto LAB_00024c72;
      case 8:
        goto LAB_00024668;
      }
    }
    if (bVar18 == 0x23) {
      sVar3 = *(short *)((int)ppuVar5 + 2);
      if (sVar3 == 0) {
        ppuVar5[1] = DAT_000dc000;
        uVar37 = 0;
        uVar41 = 4;
      }
      else {
        if (sVar3 != 1) {
          if ((((sVar3 != 2) || (*(byte *)(ppuVar5 + 1) != 0x45)) ||
              (*(byte *)((int)ppuVar5 + 5) != 0x44)) ||
             ((*(byte *)((int)ppuVar5 + 6) != 0x54 || (*(byte *)((int)ppuVar5 + 7) != 0x4d))))
          goto switchD_0002346a_default;
          FUN_0002a090();
          goto LAB_00024d90;
        }
        bVar18 = FUN_00037d0c();
        *(byte *)(ppuVar5 + 1) = bVar18;
        uVar37 = 1;
        uVar41 = 1;
      }
      ppuVar33 = ppuVar5 + 1;
      uVar28 = 0x23;
      goto LAB_00024c72;
    }
    if (0x23 < bVar18) {
      if (bVar18 == 0x24) {
        bVar18 = FUN_00039da8();
        *(byte *)((int)ppuVar5 + 7) = bVar18;
        uVar41 = 4;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        ppuVar33 = ppuVar5 + 1;
        uVar28 = 0x24;
        goto LAB_00024c72;
      }
      if (bVar18 == 0x30) {
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        switch(uVar37) {
        case 0:
          FUN_000312ec(DAT_00024c1c);
          FUN_000312ec(DAT_00024c20);
          FUN_00029534(DAT_00024c24);
          FUN_00029534(DAT_00024c28);
          FUN_0003dbcc(7);
          FUN_0003dbcc(3);
          FUN_0003dbcc(4);
          FUN_00035330();
          iVar29 = FUN_0003e38c();
          if (iVar29 == 0) {
            uVar22 = 0x40000000;
            _DAT_4000007c = 1;
          }
          else {
            uVar22 = 1;
            software_interrupt(0x32);
          }
          do {
            FUN_0003e038(uVar22);
            uVar22 = FUN_000403a4();
          } while( true );
        case 1:
          *(byte *)(ppuVar5 + 1) = *DAT_00024c2c;
          *(byte *)((int)ppuVar5 + 5) = *pbVar25;
          *(byte *)((int)ppuVar5 + 6) = pbVar25[1];
          uVar41 = 3;
          break;
        case 2:
          *DAT_00024c2c = *(byte *)(ppuVar5 + 1);
          FUN_00027838(2);
          goto LAB_00024bdc;
        case 3:
          FUN_00026024(*(undefined2 *)(ppuVar5 + 1),ppuVar5 + 1);
          goto LAB_00024b90;
        case 4:
          if (DAT_000243e0[6] == 0) {
            uVar22 = 3;
          }
          else {
            uVar22 = 2;
          }
          iVar29 = FUN_00027aa8(uVar22,DAT_00024c30,2);
          if (iVar29 == 1) {
            *(byte *)(ppuVar5 + 1) = 1;
            *(byte *)((int)ppuVar5 + 5) = (byte)puVar35[6];
            puVar17 = DAT_00024c30;
            *(undefined2 *)((int)ppuVar5 + 6) = *DAT_00024c30;
            *DAT_00024c34 = *puVar17;
          }
          else {
            ppuVar5[1] = (undefined *)0x0;
          }
          goto LAB_00024b90;
        case 5:
          FUN_00027a68(2,ppuVar5 + 1);
          FUN_00027a68(3,(byte *)((int)ppuVar5 + 6),2);
LAB_00024b90:
          uVar41 = 4;
LAB_00024bde:
          uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
          break;
        case 6:
          local_70 = (undefined **)0x0;
          iVar29 = FUN_00027aa8(2,&local_70,4);
          if (iVar29 == 0) {
            *(byte *)(ppuVar5 + 1) = 0;
          }
          else {
            *(byte *)(ppuVar5 + 1) = 1;
            FUN_00032904();
          }
LAB_00024bdc:
          uVar41 = 1;
          goto LAB_00024bde;
        default:
          goto switchD_00024ae2_caseD_7;
        case 8:
          if (DAT_000243e0[6] == 0) {
            uVar28 = (*(byte *)(DAT_00024c38 + 0x2b9) & 0xfffffff8) + 2;
            *(char *)(DAT_00024c38 + 0x2b9) = (char)uVar28;
            *piVar6 = *(ushort *)(DAT_00024c3c + (uVar28 & 7) * 2) - 1;
          }
          uVar41 = 1;
          break;
        case 9:
          if ((*(byte *)(DAT_00024e38 + 0x2b9) & 7) < 5) {
            FUN_000329d4(*(byte *)(ppuVar5 + 1) != 0);
          }
          uVar37 = 9;
          uVar41 = 1;
        }
        ppuVar33 = ppuVar5 + 1;
        uVar28 = 0x30;
      }
      else {
        bVar39 = bVar18 == 0x40;
        if (!bVar39) goto LAB_00024426;
        sVar3 = *(short *)((int)ppuVar5 + 2);
        if (sVar3 == 0) {
          uVar37 = 0;
          *(bool *)DAT_00024e3c = *(byte *)(ppuVar5 + 1) != 0;
          uVar41 = 1;
        }
        else if (sVar3 == 1) {
          *(bool *)DAT_00024e40 = *(byte *)(ppuVar5 + 1) != 0;
          FUN_0002a7c0();
          uVar37 = 1;
          uVar41 = 1;
        }
        else {
          if (sVar3 != 2) goto LAB_00024d90;
          FUN_0002b074((byte *)((int)ppuVar5 + 5),*(byte *)(ppuVar5 + 1));
          uVar37 = 2;
          uVar41 = 0x3c;
        }
        ppuVar33 = ppuVar5 + 1;
        uVar28 = 0x40;
      }
      goto LAB_00024c72;
    }
    if (bVar18 == 0xe) {
      switch(*(undefined2 *)((int)ppuVar5 + 2)) {
      case 0:
        if (DAT_000243e0[0x15] == 0) goto LAB_00024790;
        FUN_0002cc20(&DAT_000d7000);
        uVar20 = FUN_00044cd8(ppuVar5 + 1,0xc);
        *(byte *)(ppuVar5 + 4) = (byte)uVar20;
        *(byte *)((int)ppuVar5 + 0x11) = (byte)((ushort)uVar20 >> 8);
        *(byte *)((int)ppuVar5 + 0x12) = 0;
        *(byte *)((int)ppuVar5 + 0x13) = 0;
        FUN_0002cc3c(&DAT_000d7000,ppuVar5 + 1,0x10);
        uVar37 = 0;
        uVar41 = 0xc;
        break;
      case 1:
      case 2:
        FUN_0002cc30(&DAT_000d7000,ppuVar5 + 1,0x10);
        uVar41 = 0xe;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        break;
      case 3:
        FUN_0002cc20(&DAT_000d3000);
        uVar20 = FUN_00044cd8(ppuVar5 + 1,0xc);
        *(byte *)(ppuVar5 + 4) = (byte)uVar20;
        *(byte *)((int)ppuVar5 + 0x11) = (byte)((ushort)uVar20 >> 8);
        *(byte *)((int)ppuVar5 + 0x12) = 0;
        *(byte *)((int)ppuVar5 + 0x13) = 0;
        FUN_0002cc3c(&DAT_000d3000,ppuVar5 + 1,0x10);
        uVar37 = 3;
        uVar41 = 0xc;
        break;
      case 4:
        FUN_0002cc30(&DAT_000d3000,ppuVar5 + 1,0x10);
        uVar37 = 4;
        uVar41 = 0xe;
        break;
      default:
        goto switchD_00024822_caseD_1;
      }
      ppuVar33 = ppuVar5 + 1;
      uVar28 = 0xe;
      goto LAB_00024c72;
    }
    if (bVar18 == 0xf) goto switchD_00024374_caseD_0;
    bVar39 = bVar18 == 0x20;
LAB_00024426:
    if (!bVar39) goto switchD_00024374_caseD_5;
    switch(*(undefined2 *)((int)ppuVar5 + 2)) {
    case 0:
      if (*(byte *)(ppuVar5 + 1) == 1) {
        bVar39 = DAT_000243e0[0x15] == 0;
        goto LAB_00024842;
      }
      if (*(byte *)(ppuVar5 + 1) == 2) {
        FUN_000259bc();
        uVar41 = 1;
        goto LAB_0002486e;
      }
      goto switchD_0002346a_default;
    default:
      goto switchD_00024822_caseD_1;
    case 2:
      if ((((*(byte *)(ppuVar5 + 1) != 0x52) || (*(byte *)((int)ppuVar5 + 5) != 0x45)) ||
          (*(byte *)((int)ppuVar5 + 6) != 0x41)) || (*(byte *)((int)ppuVar5 + 7) != 0x44)) {
        iVar29 = 2;
        do {
          iVar29 = iVar29 + 1;
        } while (iVar29 < 4);
        uVar22 = 0x16;
        break;
      }
      FUN_0003040c(ppuVar5 + 1,0x30);
      uVar37 = 2;
      uVar41 = 0x30;
      goto LAB_00024872;
    case 3:
      bVar39 = DAT_000243e0[0x15] == 0;
LAB_00024884:
      if (bVar39) goto LAB_00024790;
      if (((*(byte *)(ppuVar5 + 1) == 0x57) && (*(byte *)((int)ppuVar5 + 5) == 0x52)) &&
         ((*(byte *)((int)ppuVar5 + 6) == 0x49 &&
          ((*(byte *)((int)ppuVar5 + 7) == 0x54 && (*(byte *)(ppuVar5 + 2) == 0x45)))))) {
        FUN_0001c590(DAT_00024c10 + 0xac3,DAT_00024c10,0x30);
        FUN_000305be(DAT_00024c14,0x30);
        uVar37 = 3;
        uVar41 = 0x35;
        goto LAB_00024872;
      }
      iVar29 = 2;
      do {
        iVar29 = iVar29 + 1;
      } while (iVar29 < 5);
      uVar22 = 0x17;
      break;
    case 4:
      bVar39 = DAT_000243e0[0x15] == 0;
      puVar35 = DAT_00024c0c;
      goto LAB_0002490c;
    case 5:
      bVar39 = true;
      if (DAT_000243e0[0x15] == 0) goto LAB_00024884;
      if (((*(byte *)(ppuVar5 + 1) != 0x4c) || (*(byte *)((int)ppuVar5 + 5) != 0x56)) ||
         ((*(byte *)((int)ppuVar5 + 6) != 0x5f ||
          ((*(byte *)((int)ppuVar5 + 7) != 0x52 || (*(byte *)(ppuVar5 + 2) != 0x46))))))
      goto LAB_00024978;
      FUN_0002cbd0(10);
      FUN_00033484(0xfa,0x20,5,ppuVar5 + 1,5);
      FUN_0002cbd0(10);
      *puVar16 = 0;
      goto LAB_0002499a;
    case 6:
      bVar39 = DAT_000243e0[0x15] == 0;
      if (!bVar39) {
        if (((((*(byte *)(ppuVar5 + 1) == 0x56) && (*(byte *)((int)ppuVar5 + 5) == 0x45)) &&
             (*(byte *)((int)ppuVar5 + 6) == 0x52)) &&
            ((*(byte *)((int)ppuVar5 + 7) == 0x49 && (*(byte *)(ppuVar5 + 2) == 0x46)))) &&
           (*(byte *)((int)ppuVar5 + 9) == 0x59)) {
          FUN_0003040c(ppuVar5 + 1,0x30);
          FUN_0002cc30(&DAT_000d7000,DAT_00024c10 + 7,0x10);
          *(byte *)(ppuVar5 + 8) = 0;
          *(byte *)((int)ppuVar5 + 0x21) = 0x85;
          *(byte *)((int)ppuVar5 + 0x22) = 0x1a;
          *(byte *)((int)ppuVar5 + 0x23) = (byte)puVar35[2];
          uVar37 = 6;
          uVar41 = 0x20;
          goto LAB_00024872;
        }
        uVar22 = 0x1a;
        break;
      }
LAB_0002490c:
      if (!bVar39) {
        if ((((*(byte *)(ppuVar5 + 1) != 0x45) || (*(byte *)((int)ppuVar5 + 5) != 0x4e)) ||
            (*(byte *)((int)ppuVar5 + 6) != 0x5f)) ||
           ((*(byte *)((int)ppuVar5 + 7) != 0x52 || (*(byte *)(ppuVar5 + 2) != 0x46)))) {
LAB_00024978:
          uVar22 = 0x18;
          break;
        }
        FUN_0002cbd0(10);
        FUN_00033484(0xfa,0x20,4,ppuVar5 + 1,5);
        FUN_0002cbd0(10);
        *puVar35 = DAT_00024c18;
        goto LAB_0002499a;
      }
LAB_00024842:
      if (bVar39) goto LAB_00024790;
      if (((*(byte *)((int)ppuVar5 + 5) != 0x43) || (*(byte *)((int)ppuVar5 + 6) != 0x4c)) ||
         ((*(byte *)((int)ppuVar5 + 7) != 0x45 ||
          ((*(byte *)(ppuVar5 + 2) != 0x41 || (*(byte *)((int)ppuVar5 + 9) != 0x52)))))) {
        uVar22 = 0x15;
        break;
      }
      FUN_0003039c();
      uVar41 = 6;
LAB_0002486e:
      uVar37 = 0;
      goto LAB_00024872;
    case 7:
      if (((*(byte *)(ppuVar5 + 1) != 0x45) || (*(byte *)((int)ppuVar5 + 5) != 0x4e)) ||
         ((((*(byte *)((int)ppuVar5 + 6) != 0x5f ||
            ((*(byte *)((int)ppuVar5 + 7) != 0x50 || (*(byte *)(ppuVar5 + 2) != 0x41)))) ||
           (*(byte *)((int)ppuVar5 + 9) != 0x49)) || (*(byte *)((int)ppuVar5 + 10) != 0x52))))
      goto switchD_0002346a_default;
      DAT_000243e0[0x15] = 1;
      uVar37 = 7;
      uVar41 = 7;
      goto LAB_00024872;
    case 8:
      bVar39 = *(byte *)(ppuVar5 + 1) == 0x44;
      goto LAB_00024a50;
    }
    goto LAB_00024cce;
  }
  goto LAB_00024dba;
  while (local_70 = (undefined **)((int)local_70 + 0x19), local_70 < (undefined **)0x64) {
LAB_00024258:
    if ((undefined **)(uint)*(byte *)(ppuVar5 + 1) <= local_70) break;
  }
  *(char *)((uint)DAT_000243c4[0x2e] + DAT_000243d0) = (char)local_70;
  FUN_00032550((uint)local_70 & 0xffff);
  FUN_0002e4c8();
  FUN_0002e250();
  uVar41 = 0x3c;
  ppuVar33 = ppuVar5 + 1;
  uVar28 = 0;
  uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
  bVar18 = 0x68;
  goto LAB_00024cf6;
  while( true ) {
    unaff_r10 = uVar37 + 1;
    *(byte *)((int)ppuVar5 + uVar37 + 4) = local_68[uVar37];
    uVar37 = unaff_r10;
    if (0x1f < (int)unaff_r10) break;
LAB_00023ee0:
    unaff_r10 = uVar37;
    if (local_68[uVar37] == 0) break;
  }
LAB_00023f02:
  uVar41 = unaff_r10 & 0xff;
  uVar28 = (uint)*(byte *)((int)ppuVar5 + 1);
  uVar37 = 0;
LAB_00023fca:
  ppuVar33 = ppuVar5 + 1;
  bVar18 = 0x7d;
  goto LAB_00024cf6;
  while ((((bVar39 = *(byte *)((int)ppuVar5 + 5) == 0x43, !bVar39 ||
           (bVar39 = *(byte *)((int)ppuVar5 + 6) == 0x44, !bVar39)) ||
          (bVar39 = *(byte *)((int)ppuVar5 + 7) == 0x43, !bVar39)) ||
         (bVar39 = *(byte *)(ppuVar5 + 2) == 0xaa, !bVar39))) {
LAB_00023e66:
    if (!bVar39) goto switchD_00024374_caseD_0;
  }
  FUN_000277cc(s_enter_CDC_mode_00023f83 + 1);
  *_DAT_00023f98 = DAT_00023f94;
LAB_0002499a:
  FUN_0002cd9c();
  goto LAB_00024d90;
LAB_00024668:
  sVar3 = *(short *)((int)ppuVar5 + 2);
  if (sVar3 != 0) {
    if (sVar3 != 1) {
      bVar39 = sVar3 == 2;
      goto LAB_00024672;
    }
    FUN_00031320(1);
    FUN_000396c8(100);
    FUN_000395b0(1);
    FUN_00039584(0x380000,ppuVar5 + 1,4);
    iVar29 = FUN_00029fd4();
    if (iVar29 == 0) {
      FUN_00039540(1);
      FUN_00031320(0);
    }
    uVar41 = 4;
    uVar31 = *(ushort *)((int)ppuVar5 + 2);
    goto LAB_00024702;
  }
  if (-1 < (int)((uint)*DAT_000243dc << 0x1e)) {
    *DAT_000243dc = *DAT_000243dc | 2;
  }
  FUN_00032598(0);
  iVar29 = DAT_000247fc;
  if (*(byte *)(ppuVar5 + 1) == 0) {
    local_6c = 0;
  }
  else {
    local_6c = 0xff;
  }
  uVar27 = 0;
  if (*(byte *)((int)ppuVar5 + 5) != 0) {
    uVar27 = 0xff;
  }
  iVar30 = 0;
  do {
    iVar26 = iVar29 + iVar30 * 0x80;
    FUN_0001c5d2(iVar26,0x40,local_6c);
    FUN_0001c5d2(iVar26 + 0x40,0x40,uVar27);
    iVar30 = iVar30 + 1;
  } while (iVar30 < 0x40);
  uVar41 = 2;
LAB_000246c8:
  uVar31 = *(ushort *)((int)ppuVar5 + 2);
LAB_00024702:
  uVar37 = (uint)uVar31;
  ppuVar33 = ppuVar5 + 1;
  uVar28 = 8;
  goto LAB_00024c72;
LAB_00024790:
  uVar22 = 0x10;
LAB_00024cce:
  FUN_00024f7c(uVar22);
  goto LAB_00024d90;
LAB_000233ee:
  bVar40 = SBORROW4(uVar37,0x62);
  bVar38 = (int)(uVar37 - 0x62) < 0;
  bVar39 = uVar37 == 0x62;
  if (!bVar39) goto code_r0x000233f4;
  goto LAB_0002337e;
code_r0x000233f4:
  bVar39 = uVar37 == 99;
  if (!bVar39) {
LAB_000233a2:
    if (bVar39) {
      if (*(byte *)((int)ppuVar5 + 1) == 1) {
        uVar28 = 1;
        *(byte *)(ppuVar5 + 1) = *(byte *)(DAT_00023b24 + 8);
        uVar41 = 1;
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        ppuVar33 = ppuVar5 + 1;
        bVar18 = 0x22;
        goto LAB_00024cf6;
      }
      bVar39 = *(byte *)((int)ppuVar5 + 1) == 2;
      if (bVar39) {
        uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
        if (uVar37 < 9) {
          iVar29 = DAT_00023b28 + uVar37 * 8;
          *(byte *)(ppuVar5 + 1) = *(byte *)(iVar29 + 0x2c2);
          uVar20 = *(undefined2 *)(iVar29 + 0x2c6);
          *(byte *)((int)ppuVar5 + 5) = (byte)uVar20;
          *(byte *)((int)ppuVar5 + 6) = (byte)((ushort)uVar20 >> 8);
          uVar20 = *(undefined2 *)(iVar29 + 0x2c4);
          *(byte *)((int)ppuVar5 + 7) = (byte)uVar20;
          *(byte *)(ppuVar5 + 2) = (byte)((ushort)uVar20 >> 8);
          uVar20 = *(undefined2 *)(iVar29 + 0x2c8);
          *(byte *)((int)ppuVar5 + 9) = (byte)uVar20;
          *(byte *)((int)ppuVar5 + 10) = (byte)((ushort)uVar20 >> 8);
          uVar22 = 7;
        }
        else {
          uVar20 = *(undefined2 *)(DAT_00023b28 + 0x270);
          *(byte *)(ppuVar5 + 1) = (byte)uVar20;
          *(byte *)((int)ppuVar5 + 5) = (byte)((ushort)uVar20 >> 8);
          uVar20 = *(undefined2 *)(iVar26 + 0x272);
          *(byte *)((int)ppuVar5 + 6) = (byte)uVar20;
          *(byte *)((int)ppuVar5 + 7) = (byte)((ushort)uVar20 >> 8);
          uVar20 = *(undefined2 *)(iVar26 + 0x274);
          *(byte *)(ppuVar5 + 2) = (byte)uVar20;
          *(byte *)((int)ppuVar5 + 9) = (byte)((ushort)uVar20 >> 8);
          uVar20 = *(undefined2 *)(iVar26 + 0x276);
          *(byte *)((int)ppuVar5 + 10) = (byte)uVar20;
          *(byte *)((int)ppuVar5 + 0xb) = (byte)((ushort)uVar20 >> 8);
          uVar22 = 8;
        }
        FUN_00024efc(0x22,1,uVar37,ppuVar5 + 1,uVar22);
      }
      else {
LAB_00023624:
        if (bVar39) {
          FUN_0002cc30(puVar36,ppuVar5 + 1,0xc);
          iVar29 = 0;
          do {
            if (*(byte *)((int)ppuVar5 + iVar29 + 4) == 0x20) {
              *(byte *)((int)ppuVar5 + iVar29 + 4) = 0x30;
            }
            iVar29 = iVar29 + 1;
          } while (iVar29 < 0xc);
          uVar37 = 2;
          uVar41 = 0xc;
LAB_00023686:
          uVar28 = 0x14;
          ppuVar33 = ppuVar5 + 1;
LAB_00023688:
          bVar18 = 0x12;
          goto LAB_00024cf6;
        }
switchD_0002346a_caseD_4:
      }
switchD_00024374_caseD_5:
    }
switchD_0002346a_default:
    uVar22 = 0;
    goto LAB_00024cce;
  }
LAB_00024226:
  local_70 = (undefined **)
             FUN_0002d7a0(uVar37,*(byte *)((int)ppuVar5 + 1),*(undefined2 *)((int)ppuVar5 + 2),
                          ppuVar5 + 1,*(undefined4 *)(pcVar4 + 0x14));
  if (local_70 == (undefined **)0x2) {
    uVar41 = 0;
    uVar37 = (uint)*(ushort *)((int)ppuVar5 + 2);
    uVar28 = (uint)*(byte *)((int)ppuVar5 + 1);
    bVar18 = *(byte *)ppuVar5;
    ppuVar33 = (undefined **)0x0;
    goto LAB_00024cf6;
  }
  if (local_70 == (undefined **)0x1) goto switchD_00024374_caseD_5;
switchD_00024374_caseD_0:
switchD_00024822_caseD_1:
switchD_00024ae2_caseD_7:
  goto LAB_00024d90;
  while ((((bVar39 = *(byte *)((int)ppuVar5 + 5) == 0x49, !bVar39 ||
           (bVar39 = *(byte *)((int)ppuVar5 + 6) == 0x53, !bVar39)) ||
          ((bVar39 = *(byte *)((int)ppuVar5 + 7) == 0x5f, !bVar39 ||
           (((bVar39 = *(byte *)(ppuVar5 + 2) == 0x50, !bVar39 ||
             (bVar39 = *(byte *)((int)ppuVar5 + 9) == 0x41, !bVar39)) ||
            (bVar39 = *(byte *)((int)ppuVar5 + 10) == 0x49, !bVar39)))))) ||
         (bVar39 = *(byte *)((int)ppuVar5 + 0xb) == 0x52, !bVar39))) {
LAB_00024a50:
    if (!bVar39) goto LAB_00024790;
  }
  DAT_000243e0[0x15] = 0;
  uVar37 = 8;
  uVar41 = 8;
LAB_00024872:
  ppuVar33 = ppuVar5 + 1;
  uVar28 = 0x20;
LAB_00024c72:
  bVar18 = 0xfa;
LAB_00024cf6:
  FUN_00024efc(bVar18,uVar28,uVar37,ppuVar33,uVar41);
LAB_00024d90:
  if (*pcVar4 == '\0') {
    pcVar4[2] = '\0';
    *(byte *)ppuVar5 = 0;
  }
  else {
    FUN_0001c590(DAT_00024e4c + -0xafc,DAT_00024e4c,*(undefined4 *)(pcVar4 + 8));
    pcVar4[8] = '\0';
    pcVar4[9] = '\0';
    pcVar4[10] = '\0';
    pcVar4[0xb] = '\0';
    *pcVar4 = '\0';
    pcVar4[2] = '\x01';
  }
  if (pcVar4[1] != '\0') {
LAB_00024dba:
    local_70 = *(undefined ***)(pcVar4 + 0x10);
    if ((undefined **)0x20 < local_70) {
      local_70 = (undefined **)0x20;
    }
    iVar30 = *(int *)(pcVar4 + 0xc);
    iVar29 = DAT_00024e4c + 0x40;
    uVar37 = (uint)local_70 & 0xff;
    FUN_0001c5e0(local_68,0x40);
    if (0x3c < uVar37) {
      uVar37 = 0x3c;
    }
    local_68[1] = (byte)uVar37 | pcVar4[0x20] << 6;
    local_68[0] = 0xfc;
    FUN_0001c590(local_68 + 2,iVar29 + iVar30,uVar37);
    iVar29 = FUN_000319a0(0x82,local_68,uVar37 + 2,0);
    if (iVar29 == 0) {
      iVar29 = *(int *)(pcVar4 + 0x20);
      *(uint *)(pcVar4 + 0x20) = iVar29 + 1U;
      if (3 < iVar29 + 1U) {
        pcVar4[0x20] = '\x01';
        pcVar4[0x21] = '\0';
        pcVar4[0x22] = '\0';
        pcVar4[0x23] = '\0';
      }
      iVar29 = *(int *)(pcVar4 + 0x10);
      *(int *)(pcVar4 + 0x10) = iVar29 - (int)local_70;
      *(int *)(pcVar4 + 0xc) = (int)local_70 + *(int *)(pcVar4 + 0xc);
      if (iVar29 - (int)local_70 == 0) {
        pcVar4[1] = '\0';
      }
    }
  }
  return;
}

