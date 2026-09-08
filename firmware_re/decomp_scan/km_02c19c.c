// @0x2c19c size=2336

void FUN_0002c19c(undefined4 param_1,uint param_2,int param_3,char *param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined2 *puVar9;
  short sVar10;
  undefined2 uVar11;
  int iVar12;
  char cVar13;
  ushort uVar14;
  int iVar15;
  byte *pbVar16;
  undefined1 *puVar17;
  undefined4 uVar18;
  uint uVar19;
  uint uVar20;
  byte bVar21;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  int iVar22;
  bool bVar23;
  uint local_30;
  int local_2c;
  char *local_28;
  
  iVar15 = DAT_0002c5b0;
  iVar5 = DAT_0002c5ac;
  iVar12 = DAT_0002c5a8;
  pcVar3 = DAT_0002c5a0;
  iVar4 = DAT_0002c59c;
  local_30 = param_2;
  local_2c = param_3;
  local_28 = param_4;
  if (*(char *)(DAT_0002c59c + 2) != '\0') goto switchD_0002c5d4_caseD_0;
  local_30 = (uint)*DAT_0002c5a4;
  iVar22 = *(int *)(DAT_0002c59c + 0x14);
  if ((*DAT_0002c5a0 != '\x01') || (*(int *)(DAT_0002c5a8 + 0x60) != 0)) {
    cVar13 = DAT_0002c5a0[0x20];
    if (*(char *)(DAT_0002c59c + 1) == '\0') {
      if (cVar13 != '\0') {
        if ((cVar13 == '\v') && (*(ushort *)(DAT_0002c5a0 + 0x22) < 3000)) {
          if (iVar22 != 0) {
            *(undefined4 *)(DAT_0002c59c + 0x14) = 0;
            FUN_0002d710();
          }
          iVar15 = DAT_0002cb04;
          if (*(int *)(iVar12 + 0x60) == 0) {
            iVar12 = 0;
            do {
              bVar21 = *(char *)(iVar5 + 8) + 1;
              *(byte *)(iVar5 + 8) = bVar21;
              if (7 < bVar21) {
                *(undefined1 *)(iVar5 + 8) = 0;
              }
            } while ((*(char *)(iVar15 + (uint)*(byte *)(iVar5 + 8) * 8 + 0x2c2) == '\0') &&
                    (iVar12 = iVar12 + 1, iVar12 < 8));
            uVar18 = 1000;
            iVar12 = *(byte *)(iVar5 + 8) + 0x32;
LAB_0002ca5c:
            FUN_0002d5cc(iVar12,uVar18,0);
          }
          else {
            if ((*DAT_0002cb00 & 1) != 0) {
              uVar18 = 0xffffffff;
              iVar12 = 0x3d;
              goto LAB_0002ca5c;
            }
            if ((int)(*DAT_0002cb00 << 0x1e) < 0) {
              *DAT_0002cb08 = 1;
            }
          }
          FUN_0002c100();
        }
        pcVar3[0x20] = '\0';
        pcVar3[0x22] = '\0';
        pcVar3[0x23] = '\0';
      }
    }
    else {
      if (cVar13 == '\0') {
        cVar13 = '\0';
        iVar12 = 0;
        do {
          uVar2 = *(ushort *)(pcVar3 + iVar12 * 2 + 2);
          if (uVar2 != 0) {
            uVar20 = 0;
            uVar14 = 1;
            do {
              if ((uVar2 & uVar14) != 0) {
                cVar13 = *(char *)(DAT_0002ca24 + (uVar20 | iVar12 << 4));
                *(ushort *)(pcVar3 + iVar12 * 2 + 2) = uVar2 & ~uVar14;
                if (cVar13 != '\0') goto LAB_0002c99c;
                break;
              }
              uVar20 = uVar20 + 1;
              uVar14 = uVar14 << 1;
            } while ((int)uVar20 < 0x10);
          }
          iVar12 = iVar12 + 1;
        } while (iVar12 < 0xc);
LAB_0002c99c:
        if (local_30 != 0) {
          if (cVar13 == -0x2d) {
            return;
          }
          goto LAB_0002c9b2;
        }
        if ((cVar13 != -0x2d) || (pcVar3[0x20] != '\0')) goto LAB_0002c9b2;
        if (*(int *)(pcVar3 + 0x54) != 0) goto LAB_0002cae4;
        pcVar3[0x20] = '\v';
        pcVar3[0x22] = '\0';
        pcVar3[0x23] = '\0';
      }
      else {
LAB_0002c9b2:
        if (pcVar3[0x20] != '\v') goto LAB_0002cae4;
      }
      if (*(short *)(pcVar3 + 0x22) == 3000) {
        if ((*DAT_0002cb00 & 1) == 0) {
          if ((int)(*DAT_0002cb00 << 0x1e) < 0) {
            FUN_0002b0ac(0xb032,0);
          }
        }
        else {
          *(undefined4 *)(iVar4 + 0x14) = 60000;
          *(undefined1 *)(iVar5 + 8) = 8;
          FUN_0002d5cc(0x3a,0xffffffff,0);
          FUN_0002c100();
        }
      }
      *(short *)(pcVar3 + 0x22) = *(short *)(pcVar3 + 0x22) + 1;
    }
LAB_0002cae4:
    *(undefined1 *)(iVar4 + 1) = 0;
    goto LAB_0002cae6;
  }
  local_2c = DAT_0002c5b0;
  if (-1 < (int)((uint)*(ushort *)(DAT_0002c5a0 + 0x14) << 0x10)) {
    *DAT_0002c5a0 = '\x02';
    if (pcVar3[1] != '\0') {
      pcVar3[1] = '\0';
      local_30 = 0;
      FUN_00031de8(0,0,0);
    }
    if (pcVar3[0x1a] != '\0') {
      if (pcVar3[0x1a] == '\x06') {
        FUN_0002b684(*(undefined1 *)(iVar5 + 5));
        FUN_00032550(*(undefined1 *)((uint)*(byte *)(iVar5 + 7) + iVar15));
        FUN_0002d710();
        *DAT_0002c5c8 = 2;
      }
      pcVar3[0x1a] = '\0';
      pcVar3[0x1e] = '\0';
      pcVar3[0x1f] = '\0';
    }
    goto LAB_0002c594;
  }
  *(ushort *)(DAT_0002c5a0 + 0x14) = *(ushort *)(DAT_0002c5a0 + 0x14) & 0x7fff;
  if (pcVar3[0x1a] != '\0') goto switchD_0002c370_caseD_4a;
  uVar20 = 0;
  iVar12 = 0;
  do {
    local_28 = pcVar3 + iVar12 * 2;
    uVar2 = *(ushort *)(local_28 + 2);
    if (uVar2 != 0) {
      uVar19 = 0;
      uVar14 = 1;
      do {
        if ((uVar2 & uVar14) != 0) {
          uVar20 = (uint)*(byte *)(DAT_0002c5b4 + (uVar19 | iVar12 << 4));
          *(ushort *)(local_28 + 2) = uVar2 & ~uVar14;
          if (uVar20 != 0) goto LAB_0002c240;
          break;
        }
        uVar19 = uVar19 + 1;
        uVar14 = uVar14 << 1;
      } while ((int)uVar19 < 0x10);
    }
    iVar12 = iVar12 + 1;
  } while (iVar12 < 0xc);
LAB_0002c240:
  if (local_30 != 0) {
    if (uVar20 == 0x49) {
      return;
    }
    if (uVar20 < 0x4a) {
      if (uVar20 == 0x22) {
        return;
      }
      if (uVar20 < 0x23) {
        if (uVar20 == 0x1f) {
          return;
        }
        if (uVar20 < 0x20) {
          if (uVar20 == 0x13) {
            return;
          }
          if (uVar20 == 0x1e) {
            return;
          }
        }
        else {
          if (uVar20 == 0x20) {
            return;
          }
          if (uVar20 == 0x21) {
            return;
          }
        }
      }
      else {
        if (uVar20 == 0x29) {
          return;
        }
        if (uVar20 < 0x2a) {
          if (uVar20 == 0x23) {
            return;
          }
          if (uVar20 == 0x24) {
            return;
          }
        }
        else {
          if (uVar20 == 0x2b) {
            return;
          }
          if (uVar20 == 0x39) {
            return;
          }
        }
      }
    }
    else {
      if (uVar20 == 0x50) {
        return;
      }
      if (uVar20 < 0x51) {
        if (uVar20 - 0x4b < 5) {
          return;
        }
      }
      else {
        if (uVar20 == 0x51) {
          return;
        }
        if (uVar20 == 0x52) {
          return;
        }
        if (uVar20 == 0xe3) {
          return;
        }
        if (uVar20 == 0xe4) {
          return;
        }
      }
    }
  }
  if (iVar22 == 0) goto LAB_0002c322;
  if (uVar20 == 0x49) {
LAB_0002c318:
    *(undefined4 *)(iVar4 + 0x14) = 0;
    FUN_0002d710();
    FUN_0002bfe4();
  }
  else {
    if (uVar20 < 0x4a) {
      if (uVar20 != 0x22) {
        if (uVar20 < 0x23) {
          if (uVar20 != 0x1f) {
            if (uVar20 < 0x20) {
              if ((uVar20 == 0x13) || (uVar20 == 0x1e)) goto LAB_0002c318;
            }
            else if ((uVar20 == 0x20) || (uVar20 == 0x21)) goto LAB_0002c318;
            goto LAB_0002c322;
          }
        }
        else if (uVar20 != 0x29) {
          if (uVar20 < 0x2a) {
            if ((uVar20 == 0x23) || (uVar20 == 0x24)) goto LAB_0002c318;
          }
          else if ((uVar20 == 0x2b) || (uVar20 == 0x39)) goto LAB_0002c318;
          goto LAB_0002c322;
        }
      }
      goto LAB_0002c318;
    }
    if (uVar20 == 0x50) goto LAB_0002c318;
    if (uVar20 < 0x51) {
      if (uVar20 - 0x4b < 5) goto LAB_0002c318;
    }
    else if ((((uVar20 == 0x51) || (uVar20 == 0x52)) || (uVar20 == 0xe3)) || (uVar20 == 0xe4))
    goto LAB_0002c318;
  }
LAB_0002c322:
  if (uVar20 == 0x45) {
    uVar11 = *(undefined2 *)(DAT_0002c5c4 + 0xe);
    goto LAB_0002c4e2;
  }
  if (uVar20 < 0x46) {
    if (uVar20 != 0x22) {
      if (0x22 < uVar20) {
        if (uVar20 == 0x29) {
          if ((pcVar3[0x1a] == '\0') && (*(int *)(pcVar3 + 0x54) == 0)) {
            cVar13 = '\x06';
LAB_0002c54a:
            pcVar3[0x1a] = cVar13;
            goto LAB_0002c422;
          }
        }
        else if (uVar20 < 0x2a) {
          if (uVar20 == 0x23) goto LAB_0002c3c0;
          if (uVar20 != 0x24) goto switchD_0002c370_caseD_4a;
          if (((-1 < (int)((uint)*DAT_0002c5c0 << 0x1d)) && (pcVar3[0x1a] == '\0')) &&
             (*(int *)(pcVar3 + 0x54) == 0)) {
            cVar13 = '\b';
            goto LAB_0002c54a;
          }
        }
        else {
          if (uVar20 != 0x2b) {
            if (uVar20 == 0x39) {
              DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] =
                   DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] & 0xbfU |
                   (byte)((((int)(uint)(byte)DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] >> 6) + 1U &
                          1) << 6);
              FUN_00032ce8(DAT_0002c5b8,1);
              FUN_00027838(1,DAT_0002c5a0 + 0x70);
              FUN_0002c17c();
            }
            goto switchD_0002c370_caseD_4a;
          }
          uVar20 = (byte)DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] & 0xffffffdf |
                   (((int)(uint)(byte)DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] >> 5) + 1U & 1) << 5
          ;
          DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] = (char)uVar20;
          if ((int)(uVar20 << 0x1a) < 0) {
            uVar18 = 0x3b;
          }
          else {
            uVar18 = 0x3c;
          }
          FUN_0002d5cc(uVar18,1000,0);
          FUN_00027838(1,DAT_0002c5a0 + 0x70);
          FUN_0002e274(0x20);
        }
        goto LAB_0002c594;
      }
      if (uVar20 != 0x1f) {
        if (uVar20 < 0x20) {
          if (uVar20 == 0x13) {
            uVar11 = 0x46;
            goto LAB_0002c4e2;
          }
          if (uVar20 != 0x1e) goto switchD_0002c370_caseD_4a;
        }
        else if ((uVar20 != 0x20) && (uVar20 != 0x21)) {
switchD_0002c370_caseD_4a:
          goto LAB_0002c594;
        }
      }
    }
LAB_0002c3c0:
    if ((1 << (uVar20 - 0x1e & 0xff) & 0x3fU) != 0) {
      uVar20 = (uVar20 - 0x1e & 0xffff) + 1;
      *(uint *)(iVar4 + 0x10) = uVar20;
      if (5 < uVar20) {
        *(undefined4 *)(iVar4 + 0x10) = 0;
      }
      if ((*DAT_0002c5bc == '\0') &&
         (uVar20 = *(uint *)(iVar4 + 0x10), *(byte *)(iVar5 + 6) != uVar20)) {
        pcVar3[0x1a] = '\x01';
        pcVar3[0x1b] = (char)uVar20;
        goto LAB_0002c422;
      }
    }
  }
  else if (uVar20 == 0x50) {
    pcVar3[0x1a] = '\x02';
    pcVar3[0x1b] = '\x02';
LAB_0002c422:
    pcVar3[0x1e] = '\0';
    pcVar3[0x1f] = '\0';
  }
  else {
    if (uVar20 < 0x51) {
      switch(uVar20) {
      case 0x49:
        uVar11 = 0x48;
        break;
      default:
        goto switchD_0002c370_caseD_4a;
      case 0x4b:
        uVar11 = 0x4a;
        break;
      case 0x4c:
        uVar11 = 0x47;
        break;
      case 0x4e:
        uVar11 = 0x4d;
        break;
      case 0x4f:
        pcVar3[0x1a] = '\x02';
        pcVar3[0x1b] = '\x01';
        goto LAB_0002c422;
      }
LAB_0002c4e2:
      FUN_0002b0ac(uVar11,0);
      goto LAB_0002c594;
    }
    if (uVar20 == 0xe2) {
      if (*(int *)(pcVar3 + 0x54) == 2) {
        *(int *)(pcVar3 + 0x5c) = *(int *)(pcVar3 + 0x5c) + 1;
        if (*(int *)(pcVar3 + 0x60) == 0) {
          uVar18 = 0x31;
        }
        else {
          uVar18 = 0x30;
        }
LAB_0002c508:
        FUN_0002d5cc(uVar18,0xffffffff,0);
      }
      else {
        if (*(int *)(pcVar3 + 0x54) != 1) {
          pcVar3[0x54] = '\x02';
          pcVar3[0x55] = '\0';
          pcVar3[0x56] = '\0';
          pcVar3[0x57] = '\0';
          uVar18 = 0x2f;
          pcVar3[0x5c] = '\0';
          pcVar3[0x5d] = '\0';
          pcVar3[0x5e] = '\0';
          pcVar3[0x5f] = '\0';
          goto LAB_0002c508;
        }
        pcVar3[0x5c] = '\x05';
        pcVar3[0x5d] = '\0';
        pcVar3[0x5e] = '\0';
        pcVar3[0x5f] = '\0';
      }
      uVar18 = 3;
    }
    else {
      if (uVar20 < 0xe3) {
        if (uVar20 == 0x51) {
          uVar18 = 0;
        }
        else {
          if (uVar20 != 0x52) goto switchD_0002c370_caseD_4a;
          uVar18 = 1;
        }
        FUN_0002b8d4(0,0,uVar18);
        goto LAB_0002c594;
      }
      if (uVar20 != 0xe3) {
        if (uVar20 == 0xe4) {
          uVar11 = 0x65;
          goto LAB_0002c4e2;
        }
        goto switchD_0002c370_caseD_4a;
      }
      uVar20 = (byte)DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] & 0xfffffffb |
               (((int)(uint)(byte)DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] >> 2) + 1U & 1) << 2;
      DAT_0002c5a0[*(byte *)(iVar5 + 6) + 0x70] = (char)uVar20;
      if ((int)(uVar20 << 0x1d) < 0) {
        uVar18 = 0x2d;
      }
      else {
        uVar18 = 0x2e;
      }
      FUN_0002d5cc(uVar18,1000,0);
      FUN_00030c60();
      FUN_00027838(1,DAT_0002c5a0 + 0x70);
      uVar18 = 1;
    }
    FUN_000336b4(uVar18,0);
  }
LAB_0002c594:
  iVar12 = DAT_0002c9e4;
  puVar17 = DAT_0002c9e0;
  pbVar16 = DAT_0002c9dc;
  switch(pcVar3[0x1a]) {
  case '\x01':
    bVar23 = *DAT_0002c9dc == 0;
    do {
      if (!bVar23) goto LAB_0002c938;
      bVar23 = *(int *)(pcVar3 + 0x54) == 0;
    } while (!bVar23);
    if (*(short *)(pcVar3 + 0x1e) == 0) {
      *DAT_0002c9e0 = 2;
      bVar21 = pcVar3[0x1b];
      puVar17[1] = bVar21;
      puVar17[8] = 0;
      puVar17[9] = puVar17[9] & 0xfd | 1;
      FUN_0002d5cc(bVar21 + 9,1000,0);
      uVar20 = (uint)(byte)pcVar3[0x1b];
      if (uVar20 == 0) {
        uVar20 = 6;
      }
      iVar12 = uVar20 + 7;
LAB_0002c8b0:
      FUN_000336b4(iVar12,0);
      goto LAB_0002c94a;
    }
    if ((*(short *)(pcVar3 + 0x1e) == 1) && ((DAT_0002c9e0[9] & 1) == 0)) goto LAB_0002c938;
  default:
switchD_0002c5d4_caseD_0:
    break;
  case '\x02':
    if ((*DAT_0002c9dc == 0) && (*(int *)(pcVar3 + 0x54) == 0)) {
      if (pcVar3[0x1b] == '\x01') {
        FUN_0002b9c4(0);
      }
      else if (pcVar3[0x1b] == '\x02') {
        FUN_0002ba38(0);
      }
      FUN_000336b4(2,0);
    }
    goto LAB_0002c66a;
  case '\x03':
    if (((*DAT_0002c9dc == 0) && (*(int *)(pcVar3 + 0x54) == 0)) && (pcVar3[1] == '\x01')) {
      if (*(byte *)(iVar5 + 5) == 5) {
        iVar15 = *(int *)(DAT_0002c9e4 + 0x14) + 7;
      }
      else {
        iVar15 = *(int *)(DAT_0002c9e4 + (uint)*(byte *)(iVar5 + 5) * 4) + 5;
      }
      *(int *)(iVar4 + 0xc) = iVar15;
      cVar13 = pcVar3[0x1b];
      if (cVar13 == '\x01') {
        pbVar16 = *(byte **)(iVar4 + 0xc);
        if (*pbVar16 < 0xe4) {
          bVar21 = *pbVar16 + 0x1c;
        }
        else {
          bVar21 = 0;
        }
        *pbVar16 = bVar21;
        if (0xfb < bVar21) {
          *pbVar16 = 0xff;
        }
      }
      else if (cVar13 == '\x02') {
        iVar15 = *(int *)(iVar4 + 0xc);
        if (*(byte *)(iVar15 + 1) < 0xe4) {
          bVar21 = *(byte *)(iVar15 + 1) + 0x1c;
        }
        else {
          bVar21 = 0;
        }
        *(byte *)(iVar15 + 1) = bVar21;
        if (0xfb < bVar21) {
          *(undefined1 *)(iVar15 + 1) = 0xff;
        }
      }
      else if (cVar13 == '\x03') {
        iVar15 = *(int *)(iVar4 + 0xc);
        if (*(byte *)(iVar15 + 2) < 0xe4) {
          bVar21 = *(byte *)(iVar15 + 2) + 0x1c;
        }
        else {
          bVar21 = 0;
        }
        *(byte *)(iVar15 + 2) = bVar21;
        if (0xfb < bVar21) {
          *(undefined1 *)(iVar15 + 2) = 0xff;
        }
      }
      puVar17 = *(undefined1 **)(iVar4 + 0xc);
      if (*(byte *)(iVar5 + 5) == 5) {
        *(undefined1 *)(*(int *)(iVar12 + 0x14) + 7) = *puVar17;
        *(undefined1 *)(*(int *)(iVar12 + (uint)*(byte *)(iVar5 + 5) * 4) + 8) = puVar17[1];
        *(undefined1 *)(*(int *)(iVar12 + (uint)*(byte *)(iVar5 + 5) * 4) + 9) = puVar17[2];
      }
      else {
        *(undefined1 *)(*(int *)(iVar12 + (uint)*(byte *)(iVar5 + 5) * 4) + 5) = *puVar17;
        *(undefined1 *)(*(int *)(iVar12 + (uint)*(byte *)(iVar5 + 5) * 4) + 6) = puVar17[1];
        *(undefined1 *)(*(int *)(iVar12 + (uint)*(byte *)(iVar5 + 5) * 4) + 7) = puVar17[2];
      }
      FUN_0002bfc8();
    }
LAB_0002c66a:
    pcVar3[0x1a] = '\0';
    pcVar3[0x1e] = '\0';
    pcVar3[0x1f] = '\0';
    break;
  case '\x06':
    uVar2 = *(ushort *)(pcVar3 + 0x1e);
    if (uVar2 == 0) {
      FUN_0003222c(0xf2,DAT_0002c9e8 + 4);
      FUN_0002d5cc(0x2b,0xffffffff,0);
      *(short *)(pcVar3 + 0x1e) = *(short *)(pcVar3 + 0x1e) + 1;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      break;
    }
    if (uVar2 != 3000) {
      if (uVar2 != 0xbb9) {
        if ((int)((uint)*(ushort *)(pcVar3 + 0xe) << 0x11) < 0) {
          *(ushort *)(pcVar3 + 0xe) = *(ushort *)(pcVar3 + 0xe) & 0xbfff;
          if (uVar2 < 0xbb9) {
            *(ushort *)(pcVar3 + 0x1e) = uVar2 + 1;
            uVar18 = 0xf2;
          }
          else {
            uVar18 = 0xf3;
          }
          FUN_0003222c(uVar18,DAT_0002c9e8 + 4);
          break;
        }
        FUN_0002b684(*(undefined1 *)(iVar5 + 5));
        FUN_00032550(*(undefined1 *)((uint)*(byte *)(iVar5 + 7) + iVar15));
        FUN_0002d710();
        *DAT_0002ca18 = 2;
        pcVar3[0x1a] = '\0';
        pcVar3[0x1e] = '\0';
        pcVar3[0x1f] = '\0';
        goto LAB_0002c958;
      }
      iVar12 = FUN_00029fd4();
      if (iVar12 != 0) break;
      FUN_00028430(1);
      FUN_00027838(2,DAT_0002ca0c);
      FUN_00027838(0,DAT_0002ca10);
      FUN_00027838(1,DAT_0002c9ec);
      FUN_0003222c(0xf3,DAT_0002c9e8 + 4);
      if (*(int *)(DAT_0002ca14 + 0x18) == 0) {
        FUN_0002fc80();
        FUN_0002b45c();
      }
      FUN_0002d5cc(0x2c,0xffffffff,0);
      iVar12 = 5;
      goto LAB_0002c8b0;
    }
    iVar22 = FUN_00029fd4();
    iVar12 = DAT_0002c9ec;
    if (iVar22 != 0) break;
    iVar22 = *(int *)(iVar4 + 0x10);
    *(undefined1 *)(DAT_0002c9ec + iVar22) = 0x10;
    FUN_00028370(iVar22 * 0x1000 + 0x2000);
    iVar22 = *(int *)(iVar4 + 0x10);
    *(int *)(iVar4 + 0x10) = iVar22 + 1;
    if (iVar22 < 5) break;
    *(undefined1 *)(iVar5 + 6) = 0;
    puVar6 = DAT_0002c9f0;
    *(undefined4 *)(iVar5 + 0xc) = *DAT_0002c9f0;
    *(undefined2 *)(iVar5 + 0x10) = *(undefined2 *)(puVar6 + 1);
    FUN_0001c5e0(DAT_0002c9e8,0x622);
    puVar7 = DAT_0002c9f4;
    *(undefined4 *)(iVar5 + 0x12) = *DAT_0002c9f4;
    *(undefined2 *)(iVar5 + 0x16) = *(undefined2 *)(puVar7 + 1);
    puVar8 = DAT_0002c9f8;
    *(undefined4 *)(iVar5 + 0x18) = *DAT_0002c9f8;
    *(undefined2 *)(iVar5 + 0x1c) = *(undefined2 *)(puVar8 + 1);
    *pbVar16 = *pbVar16 & 0xf3;
    uVar1 = *(undefined1 *)puVar6;
    *(undefined1 *)(iVar5 + 5) = uVar1;
    *(undefined1 *)(iVar5 + 7) = *(undefined1 *)puVar7;
    FUN_0001c5d2(iVar15,8,100);
    FUN_00022f60(0,uVar1);
    FUN_0002325c(DAT_0002c9e8 + 0xca);
    FUN_00022f18(DAT_0002c9fc);
    FUN_00024e50(DAT_0002ca00);
    *(undefined1 *)(iVar5 + 8) = *(undefined1 *)((int)DAT_0002c9f8 + (uint)*(byte *)(iVar5 + 6));
    FUN_0001c590(DAT_0002ca00 + 10,DAT_0002ca04,0x48);
    FUN_0002bfe4();
    FUN_0002e274(0x20);
    puVar9 = DAT_0002ca08;
    *(undefined1 *)(iVar12 + 9) = 1;
    *(undefined2 *)(DAT_0002c9e8 + 0x620) = *puVar9;
LAB_0002c94a:
    *(short *)(pcVar3 + 0x1e) = *(short *)(pcVar3 + 0x1e) + 1;
    break;
  case '\a':
    if (*(short *)(pcVar3 + 0x1e) == 0) {
LAB_0002c932:
      pcVar3[0x1e] = '\x01';
      pcVar3[0x1f] = '\0';
      break;
    }
    if (*(short *)(pcVar3 + 0x1e) != 1) break;
    goto LAB_0002c938;
  case '\b':
    if (*(short *)(pcVar3 + 0x1e) != 0) {
      if (*(short *)(pcVar3 + 0x1e) != 3000) {
        bVar21 = *(byte *)(DAT_0002ca1c + 0x24) >> 4;
        uVar20 = 1 << (*(byte *)(DAT_0002ca1c + 0x24) & 0xf);
        if ((*(ushort *)(pcVar3 + (uint)bVar21 * 2 + 2) & uVar20) != 0) {
          *(ushort *)(pcVar3 + (uint)bVar21 * 2 + 2) =
               *(ushort *)(pcVar3 + (uint)bVar21 * 2 + 2) & ~(ushort)uVar20;
          if (*(ushort *)(pcVar3 + 0x1e) < 0xbb9) {
            *(ushort *)(pcVar3 + 0x1e) = *(ushort *)(pcVar3 + 0x1e) + 1;
          }
          break;
        }
        pcVar3[0x1a] = '\0';
        pcVar3[0x1e] = '\0';
        pcVar3[0x1f] = '\0';
LAB_0002c958:
        pcVar3[0x54] = '\0';
        pcVar3[0x55] = '\0';
        pcVar3[0x56] = '\0';
        pcVar3[0x57] = '\0';
        pcVar3[0x5c] = '\0';
        pcVar3[0x5d] = '\0';
        pcVar3[0x5e] = '\0';
        pcVar3[0x5f] = '\0';
        break;
      }
      FUN_0002b0ac(0xb032,0);
      goto LAB_0002c94a;
    }
    if (-1 < (int)((uint)*DAT_0002ca20 << 0x1d)) goto LAB_0002c932;
LAB_0002c938:
    pcVar3[0x1a] = '\0';
    pcVar3[0x1e] = '\0';
    pcVar3[0x1f] = '\0';
  }
LAB_0002cae6:
  if ((*(int *)(iVar4 + 0x14) != 0) &&
     (iVar12 = *(int *)(iVar4 + 0x14) + -1, *(int *)(iVar4 + 0x14) = iVar12, iVar12 == 0)) {
    FUN_0002d710();
    FUN_0002bfe4();
  }
  iVar4 = DAT_0002b680;
  pcVar3 = DAT_0002b674;
  if (*DAT_0002b674 != '\0') {
    sVar10 = *(short *)(DAT_0002b674 + 4);
    if (sVar10 == 1000) {
      FUN_0002b684(*(undefined1 *)(DAT_0002b678 + 5),local_30,local_2c,local_28,unaff_r4,unaff_lr);
      if ((int)((uint)*DAT_0002b67c << 0x1d) < 0) {
        FUN_0004540c();
      }
      sVar10 = *(short *)(pcVar3 + 4);
    }
    else if (sVar10 == 0x3e9) {
      *DAT_0002b674 = '\0';
      *(undefined1 *)(iVar4 + 0x1a) = 0;
      *(undefined2 *)(iVar4 + 0x1e) = 0;
      pcVar3[4] = '\0';
      pcVar3[5] = '\0';
      FUN_0002cd9c();
      return;
    }
    *(short *)(pcVar3 + 4) = sVar10 + 1;
  }
  return;
}

