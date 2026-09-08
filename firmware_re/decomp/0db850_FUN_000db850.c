// @0xdb850  size=846

/* WARNING: Switch with 1 destination removed at 0x000dbb84 */

void FUN_000db850(void)

{
  bool bVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined **ppuVar7;
  uint extraout_r1;
  uint uVar8;
  uint extraout_r1_00;
  undefined **extraout_r2;
  undefined **extraout_r2_00;
  undefined **extraout_r2_01;
  undefined **extraout_r2_02;
  undefined **extraout_r2_03;
  undefined **extraout_r2_04;
  undefined **extraout_r2_05;
  undefined **extraout_r2_06;
  undefined **ppuVar9;
  undefined **extraout_r2_07;
  undefined **extraout_r2_08;
  undefined **extraout_r2_09;
  undefined **extraout_r2_10;
  undefined4 *puVar10;
  undefined *puVar11;
  undefined **unaff_r6;
  int iVar12;
  undefined *puVar13;
  uint uVar14;
  int iVar15;
  undefined4 uVar16;
  bool bVar17;
  undefined1 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined *local_58;
  undefined **local_54;
  uint local_50 [9];
  undefined8 local_2c;
  undefined4 *puStack_24;
  undefined4 *puStack_20;
  undefined **ppuStack_1c;
  undefined4 uStack_4;
  
  puVar5 = puRam000db870;
  for (puVar10 = puRam000db86c; uVar18 = puVar5 <= puVar10, !(bool)uVar18; puVar10 = puVar10 + 4) {
    (*(code *)puVar10[3])(*puVar10,puVar10[1],puVar10[2]);
  }
  uVar16 = 0xdb86d;
  uVar19 = thunk_FUN_000df0f8();
  ppuVar9 = extraout_r2;
  puStack_24 = puVar10;
  puStack_20 = puVar5;
  do {
    ppuVar7 = (undefined **)((ulonglong)uVar19 >> 0x20);
    uVar8 = (uint)unaff_r6 & 0xff;
    puStack_24 = (undefined4 *)
                 ((int)ppuVar9 +
                 (uint)(uVar8 == 0 && (bool)uVar18 ||
                       uVar8 != 0 && ((int)puStack_24 >> uVar8 - 1 & 1U) != 0) +
                 ((int)puStack_24 >> uVar8));
    iVar15 = 0;
    local_54 = ppuVar7 + 3;
    bVar1 = true;
    iVar12 = 0;
    ppuStack_1c = ppuVar7;
    uStack_4 = uVar16;
    while( true ) {
      uVar16 = 0xdb899;
      local_2c = uVar19;
      uVar19 = (*(code *)ppuVar7[5])(local_54,1);
      uVar8 = (uint)((ulonglong)uVar19 >> 0x20);
      uVar14 = (uint)uVar19;
      uVar18 = 1;
      ppuVar9 = extraout_r2_00;
      if (uVar14 == 0) break;
      if (uVar14 == 0x25) {
        puVar13 = (undefined *)0x0;
        iVar3 = (*(code *)ppuVar7[5])(local_54,0);
        if (iVar3 == 0x2a) {
          (*(code *)ppuVar7[5])(local_54,1);
        }
        puVar2 = DAT_000dbba0;
        puVar11 = (undefined *)(uint)(iVar3 == 0x2a);
        while( true ) {
          uVar16 = 0xdb921;
          iVar3 = (*(code *)ppuVar7[5])(local_54,1);
          uVar8 = iVar3 - 0x30;
          ppuVar9 = extraout_r2_02;
          if ((int)&NMI + 1U < uVar8) break;
          uVar18 = puVar2 <= puVar13;
          if ((int)puVar2 < (int)puVar13) goto LAB_000dbb82;
          uVar8 = (int)puVar13 * 5;
          uVar14 = iVar3 + (int)puVar13 * 10;
          uVar18 = 0x2f < uVar14;
          puVar13 = (undefined *)(uVar14 - 0x30);
          if ((int)puVar13 < 0) goto LAB_000dbb82;
          puVar11 = (undefined *)((uint)puVar11 | 0x10);
        }
        uVar20 = CONCAT44((int)puVar11 << 0x1b,iVar3);
        if (-1 < (int)puVar11 << 0x1b) {
          puVar13 = (undefined *)0x7fffffff;
        }
        if (iVar3 == 0x6c) {
          uVar16 = 0xdb969;
          uVar20 = (*(code *)ppuVar7[5])(local_54,1);
          if ((int)uVar20 != 0x6c) {
            puVar11 = (undefined *)((uint)puVar11 | 4);
            ppuVar9 = extraout_r2_03;
            uVar19 = local_2c;
            goto LAB_000db99c;
          }
LAB_000db972:
          puVar11 = (undefined *)((uint)puVar11 | 2);
LAB_000db994:
          uVar16 = 0xdb99d;
          uVar20 = (*(code *)ppuVar7[5])(local_54,1);
          ppuVar9 = extraout_r2_05;
          uVar19 = local_2c;
        }
        else {
          if (iVar3 == 0x4c) {
            puVar11 = (undefined *)((uint)puVar11 | 0x20);
            goto LAB_000db994;
          }
          if (iVar3 == 0x68) {
            uVar16 = 0xdb987;
            uVar20 = (*(code *)ppuVar7[5])(local_54,1);
            if ((int)uVar20 == 0x68) {
              puVar11 = (undefined *)((uint)puVar11 | 0x800);
              goto LAB_000db994;
            }
            puVar11 = (undefined *)((uint)puVar11 | 8);
            ppuVar9 = extraout_r2_04;
            uVar19 = local_2c;
          }
          else {
            if (iVar3 == 0x6a) goto LAB_000db972;
            if ((iVar3 == 0x74) || (uVar19 = local_2c, iVar3 == 0x7a)) goto LAB_000db994;
          }
        }
LAB_000db99c:
        local_2c._4_4_ = (undefined4)((ulonglong)uVar19 >> 0x20);
        local_2c._0_4_ = (undefined4)uVar19;
        uVar8 = (uint)((ulonglong)uVar20 >> 0x20);
        uVar14 = (uint)uVar20;
        ppuVar7[1] = puVar11;
        ppuVar7[2] = puVar13;
        if (uVar14 == 0x65) goto LAB_000dba20;
        if ((int)uVar14 < 0x66) {
          if (uVar14 == 0x58) {
LAB_000dbaa0:
            ppuVar7[1] = (undefined *)((uint)puVar11 | 0x40);
            if ((int)puVar11 << 0x1e < 0) {
              ppuVar9 = &MemManage;
              goto LAB_000dbaae;
            }
LAB_000dbabc:
            ppuVar9 = &MemManage;
LAB_000dbac0:
            uVar16 = 0xdbacb;
            uVar19 = FUN_000db660(0xfffffffe,(undefined4)local_2c,ppuVar9,ppuVar7);
            ppuVar9 = extraout_r2_07;
          }
          else if ((int)uVar14 < 0x59) {
            if (uVar14 != 0x45) {
              if ((int)uVar14 < 0x46) {
                if (uVar14 == 0x25) {
                  uVar4 = (*(code *)ppuVar7[6])((undefined4)local_2c);
                  local_2c = uVar19;
                  if (uVar4 != 0x25) {
                    uVar16 = 0xdba19;
                    (*(code *)ppuVar7[7])((undefined4)local_2c);
                    uVar8 = extraout_r1_00;
                    ppuVar9 = extraout_r2_06;
                    goto joined_r0x000dba1a;
                  }
                  goto LAB_000db8e4;
                }
                uVar18 = 0x40 < uVar14;
                if (uVar14 != 0x41) break;
              }
              else if ((uVar14 != 0x46) && (uVar18 = 0x46 < uVar14, uVar14 != 0x47)) break;
            }
LAB_000dba20:
            uVar19 = CONCAT44((undefined4)local_2c,0xfffffffe);
            ppuVar9 = &local_58;
          }
          else {
            if (uVar14 != 0x5b) {
              if (uVar14 == 0x61) goto LAB_000dba20;
              if (uVar14 != 99) {
                uVar18 = 99 < uVar14;
                if (uVar14 == 100) {
LAB_000dba8e:
                  ppuVar7[1] = (undefined *)((uint)puVar11 | 0x40);
                  ppuVar9 = (undefined **)((int)&NMI + 2);
                  goto joined_r0x000dba7e;
                }
                break;
              }
            }
LAB_000dbacc:
            puVar13 = (undefined *)0x0;
            if (uVar14 == 99) {
              if (-1 < (int)((uint)*(byte *)(ppuVar7 + 1) << 0x1b)) {
                ppuVar7[2] = (undefined *)0x1;
              }
              puVar13 = (undefined *)0x1;
            }
            else if (uVar14 == 0x5b) {
              uVar16 = 0xdbaf5;
              uVar8 = (*(code *)ppuVar7[5])(local_54,1,ppuVar7[5],0);
              uVar18 = 0x5d < uVar8;
              bVar17 = uVar8 == 0x5e;
              ppuVar9 = extraout_r2_08;
              if (bVar17) {
                uVar16 = 0xdbb05;
                uVar8 = (*(code *)ppuVar7[5])(local_54,1);
                ppuVar9 = extraout_r2_09;
              }
              uVar19 = CONCAT44(ppuVar7[4],uVar8);
              if (ppuVar7[4] == (undefined *)0x0) {
                uVar14 = 0;
                ppuVar9 = (undefined **)0x0;
                do {
                  local_50[uVar14] = 0;
                  uVar14 = uVar14 + 1;
                  uVar19 = CONCAT44(uVar14,uVar8);
                  uVar18 = (int)&Reset + 3U < uVar14;
                } while ((int)uVar14 < 8);
              }
              do {
                uVar8 = (uint)((ulonglong)uVar19 >> 0x20);
                iVar3 = (int)uVar19;
                if (iVar3 == 0) goto LAB_000dbb82;
                if (ppuVar7[4] == (undefined *)0x0) {
                  local_50[(int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1b)) >> 5] =
                       local_50[(int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1b)) >> 5] |
                       1 << (iVar3 % 0x20 & 0xffU);
                }
                uVar16 = 0xdbb43;
                uVar19 = (*(code *)ppuVar7[5])(local_54,1);
                uVar18 = 0x5c < (uint)uVar19;
                ppuVar9 = extraout_r2_10;
              } while ((uint)uVar19 != 0x5d);
              if (bVar17) {
                iVar3 = 0;
                do {
                  local_50[iVar3] = ~local_50[iVar3];
                  iVar3 = iVar3 + 1;
                } while (iVar3 < 8);
              }
            }
            uVar19 = CONCAT44((undefined4)local_2c,0xfffffffe);
            ppuVar9 = ppuVar7;
            local_58 = puVar13;
          }
LAB_000dbb70:
          uVar8 = (uint)((ulonglong)uVar19 >> 0x20);
          uVar14 = (uint)uVar19;
          if ((int)uVar14 < 0) {
            uVar18 = 0xfffffffe < uVar14;
            if ((uVar14 == 0xffffffff) && (uVar18 = 1, bVar1)) goto LAB_000dbb7e;
            break;
          }
          if (((uint)puVar11 & 1) == 0) {
            iVar15 = iVar15 + 1;
          }
          iVar12 = iVar12 + uVar14;
          bVar1 = false;
          uVar19 = CONCAT44(local_2c._4_4_,(undefined4)local_2c);
        }
        else {
          if (uVar14 == 0x6f) {
            ppuVar7[1] = (undefined *)((uint)puVar11 | 0x40);
            ppuVar9 = &NMI;
joined_r0x000dba7e:
            if (-1 < (int)puVar11 << 0x1e) goto LAB_000dbac0;
LAB_000dbaae:
            uVar19 = CONCAT44((undefined4)local_2c,0xfffffffe);
            goto LAB_000dbb70;
          }
          if (0x6f < (int)uVar14) {
            if (uVar14 == 0x70) {
              ppuVar7[1] = (undefined *)((uint)puVar11 & 0xfffff7f1);
              goto LAB_000dbabc;
            }
            if (uVar14 == 0x73) goto LAB_000dbacc;
            if (uVar14 == 0x75) goto LAB_000dba8e;
            uVar18 = 0x77 < uVar14;
            if (uVar14 == 0x78) goto LAB_000dbaa0;
            break;
          }
          if ((uVar14 == 0x66) || (uVar14 == 0x67)) goto LAB_000dba20;
          if (uVar14 == 0x69) {
            ppuVar7[1] = (undefined *)((uint)puVar11 | 0x40);
            ppuVar9 = (undefined **)0x0;
            if ((int)puVar11 << 0x1e < 0) goto LAB_000dbaae;
            goto LAB_000dbac0;
          }
          uVar18 = 0x6d < uVar14;
          if (uVar14 != 0x6e) break;
          if (((uint)puVar11 & 1) == 0) {
            puVar5 = (undefined4 *)*ppuVar7;
            *ppuVar7 = (undefined *)(puVar5 + 1);
            piVar6 = (int *)*puVar5;
            if ((int)puVar11 << 0x14 < 0) {
              *(char *)piVar6 = (char)iVar12;
            }
            else if ((int)puVar11 << 0x1c < 0) {
              *(short *)piVar6 = (short)iVar12;
            }
            else if ((int)puVar11 << 0x1e < 0) {
              *piVar6 = iVar12;
              piVar6[1] = iVar12 >> 0x1f;
            }
            else {
              *piVar6 = iVar12;
            }
          }
        }
      }
      else {
        iVar3 = (*(code *)ppuVar7[8])();
        if (iVar3 == 0) {
          uVar4 = (*(code *)ppuVar7[6])((undefined4)local_2c);
          if (uVar4 != uVar14) {
            uVar16 = 0xdb8ef;
            (*(code *)ppuVar7[7])((undefined4)local_2c);
            uVar8 = extraout_r1;
            ppuVar9 = extraout_r2_01;
joined_r0x000dba1a:
            uVar18 = 0xfffffffe < uVar4;
            if ((uVar4 == 0xffffffff) && (uVar18 = 1, iVar15 == 0)) {
LAB_000dbb7e:
              uVar18 = 1;
              iVar15 = -1;
            }
            break;
          }
LAB_000db8e4:
          iVar12 = iVar12 + 1;
          uVar19 = local_2c;
        }
        else {
          do {
            (*(code *)ppuVar7[5])(local_54,1);
            iVar3 = (*(code *)ppuVar7[8])();
          } while (iVar3 != 0);
          (*(code *)ppuVar7[5])(local_54,0xffffffff);
          while( true ) {
            (*(code *)ppuVar7[6])((undefined4)local_2c);
            iVar3 = (*(code *)ppuVar7[8])();
            if (iVar3 == 0) break;
            iVar12 = iVar12 + 1;
          }
          (*(code *)ppuVar7[7])((undefined4)local_2c);
          uVar19 = local_2c;
        }
      }
    }
LAB_000dbb82:
    uVar19 = CONCAT44(uVar8,iVar15);
    unaff_r6 = ppuStack_1c;
  } while( true );
}

