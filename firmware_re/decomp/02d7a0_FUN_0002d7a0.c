// @0x2d7a0  size=2420

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0002d7a0(int param_1,uint param_2,uint param_3,byte *param_4,undefined4 param_5)

{
  byte bVar1;
  ushort uVar2;
  char cVar3;
  ushort uVar4;
  undefined1 *puVar5;
  ushort *puVar6;
  byte bVar7;
  uint uVar8;
  char *pcVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 uVar13;
  byte *pbVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  bool bVar19;
  bool bVar20;
  undefined4 uVar21;
  undefined4 local_d0 [2];
  int local_c8;
  undefined1 auStack_c4 [20];
  char local_b0 [4];
  char acStack_ac [4];
  undefined4 uStack_a8;
  undefined4 local_a0;
  char local_9c [4];
  char acStack_98 [4];
  undefined4 uStack_94;
  undefined4 local_90 [2];
  undefined4 local_88;
  undefined4 uStack_84;
  char local_80 [4];
  char acStack_7c [4];
  char local_78 [4];
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  char local_50 [4];
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34 [4];
  
  iVar18 = DAT_0002e1b0;
  iVar17 = DAT_0002dc1c;
  puVar6 = DAT_0002dc18;
  iVar16 = DAT_0002dc14;
  local_44 = DAT_0002dba4;
  local_40 = DAT_0002dba8;
  local_3c = DAT_0002dbac;
  local_88 = DAT_0002dbb0;
  uStack_84 = DAT_0002dbb4;
  local_80 = (char  [4])s_CHASSIS_0002dbb8._0_4_;
  acStack_7c = (char  [4])s_CHASSIS_0002dbb8._4_4_;
  local_78 = (char  [4])s_Usage_0002dbc0._0_4_;
  uStack_74 = ram0x0002dbc4;
  local_70 = DAT_0002dbc8;
  uStack_6c = DAT_0002dbcc;
  local_68 = DAT_0002dbd0;
  uStack_64 = DAT_0002dbd4;
  local_48 = DAT_0002dbd8;
  local_60 = DAT_0002dbdc;
  uStack_5c = DAT_0002dbe0;
  local_9c = (char  [4])s_Charging_0002dbe4._0_4_;
  acStack_98 = (char  [4])s_Charging_0002dbe4._4_4_;
  uStack_94 = ram0x0002dbec;
  local_58 = DAT_0002dbf0;
  uStack_54 = DAT_0002dbf4;
  local_50 = (char  [4])s_Alarm_0002dbf8._0_4_;
  uStack_4c = ram0x0002dbfc;
  local_b0 = (char  [4])s_Calendar_0002dc00._0_4_;
  acStack_ac = (char  [4])s_Calendar_0002dc00._4_4_;
  uStack_a8 = ram0x0002dc08;
  uVar12 = param_1 - 0x61;
  local_38 = DAT_0002dc0c;
  local_34[0] = DAT_0002dc10;
  uVar2 = *DAT_0002dc18;
  uVar8 = (uint)uVar2;
  iVar15 = 2;
  cVar3 = *(char *)(DAT_0002dc1c + 10);
  uVar4 = uVar2 & 7;
  switch(param_1) {
  case 0x61:
    if (param_2 == 0) {
      if (5 < *param_4) {
        return 1;
      }
      if (uVar2 >> 3 != 0) {
        *DAT_0002dc18 = uVar4;
      }
      pbVar14 = DAT_0002dc20;
      if (DAT_0002dc20[7] == *param_4) {
        return 2;
      }
      DAT_0002dc20[7] = *param_4;
      FUN_0002d170();
      bVar7 = pbVar14[7];
LAB_0002da6a:
      FUN_00032550(*(undefined1 *)((uint)bVar7 + iVar16));
      return 2;
    }
    if (param_2 == 1) {
      if (cVar3 == -1) {
        *(undefined1 *)(DAT_0002dc1c + 10) = 0;
      }
      *(byte *)(iVar17 + 10) = *(byte *)(iVar17 + 10) & 0xbf;
      FUN_00027838(1,DAT_0002dc1c);
      FUN_00032910(DAT_0002dc24);
      *puVar6 = *puVar6 | 4;
      FUN_00032598(0);
      bVar7 = *param_4;
      bVar1 = param_4[1];
      goto LAB_0002d9d0;
    }
    if (param_2 == 2) {
      uVar8 = uVar8 << 0x1d;
      bVar19 = (int)uVar8 < 0;
      goto LAB_0002d8d6;
    }
    bVar20 = param_2 == 3;
    goto LAB_0002d874;
  case 0x62:
    uVar12 = 1 << DAT_0002dc20[6];
    if (param_2 != 0) {
      if (param_2 == 1) {
        uVar8 = uVar8 << 0x1d;
        bVar20 = (int)uVar8 < 0;
        if (!bVar20) goto LAB_0002d916;
        param_2 = *(uint *)(DAT_0002dc18 + 0x61);
        bVar20 = param_2 == 0;
        goto LAB_0002d9ec;
      }
      bVar20 = param_2 == 2;
      do {
        if (!bVar20) goto LAB_0002d874;
        if (cVar3 == -1) {
          *(undefined1 *)(iVar17 + 10) = 0;
        }
        pbVar14 = DAT_0002dc20;
        param_2 = (uint)*(byte *)(iVar17 + 10);
        bVar20 = (param_2 & uVar12) == 0;
        param_4 = DAT_0002dc20;
        if (!bVar20) {
          if (uVar8 >> 3 != 0) {
            *puVar6 = uVar4;
          }
          bVar7 = 7;
          goto LAB_0002da62;
        }
LAB_0002d9ec:
        if (bVar20) {
          return 1;
        }
        param_2 = param_2 - 1;
        bVar20 = param_2 == param_3;
LAB_0002d9f2:
      } while (!bVar20);
      *(uint *)(puVar6 + 0x61) = param_2;
      if (param_2 != 0) goto LAB_0002d9fa;
      FUN_00032928(param_4,param_5,1);
      *(byte *)(iVar17 + 10) = *(byte *)(iVar17 + 10) | (byte)(1 << (uint)DAT_0002dc20[6]);
      goto LAB_0002da22;
    }
    uVar8 = (uint)*param_4;
    if (uVar8 < 5) {
      if (param_4[1] == 1) {
        uVar8 = (uint)*(ushort *)(param_4 + 4);
        bVar19 = uVar8 == 0x2e;
      }
      else {
LAB_0002d95e:
        uVar8 = (uint)*(ushort *)(param_4 + 2);
        bVar19 = uVar8 == 0xd0;
      }
      bVar20 = false;
      if (bVar19) {
LAB_0002d96c:
        if (0x9000 < (uint)*(ushort *)(param_4 + 4) * (uint)(*(ushort *)(param_4 + 2) >> 1) + 6) {
          return 1;
        }
        if (cVar3 == -1) {
          *(undefined1 *)(DAT_0002dc1c + 10) = 0;
        }
        *(byte *)(iVar17 + 10) = *(byte *)(iVar17 + 10) & ~(byte)uVar12;
        pbVar14 = DAT_0002dc20;
        FUN_00027838(1,DAT_0002dc1c);
        FUN_00032910(DAT_0002dc28 + (uint)pbVar14[6] * 0x9000);
        *puVar6 = *puVar6 | 4;
        FUN_00032598(0);
        FUN_00032928(param_4,6,0);
        bVar7 = param_4[6];
        bVar1 = param_4[7];
LAB_0002d9d0:
        *(uint *)(puVar6 + 0x61) = (uint)CONCAT11(bVar1,bVar7);
        puVar6[99] = 0;
        puVar6[100] = 0;
        puVar6[0x65] = 0;
        puVar6[0x66] = 0;
        return 2;
      }
    }
    else {
      bVar20 = false;
      if (uVar8 == 0xff) {
        if (param_4[1] != 1) goto LAB_0002d95e;
        uVar8 = (uint)*(ushort *)(param_4 + 4);
        bVar19 = uVar8 == 0x40;
        uVar11 = 0;
        if (!bVar19) goto LAB_0002d8e4;
        goto LAB_0002d96c;
      }
    }
LAB_0002d874:
    do {
      if (!bVar20) {
        return 1;
      }
      if (cVar3 == -1) {
        *(undefined1 *)(iVar17 + 10) = 0;
      }
      bVar20 = (int)((uint)*(byte *)(iVar17 + 10) << 0x19) < 0;
LAB_0002d916:
      bVar19 = false;
      if (bVar20) {
        if (uVar8 >> 3 != 0) {
          *puVar6 = uVar4;
        }
        bVar7 = 6;
        pbVar14 = DAT_0002dc20;
LAB_0002da62:
        pbVar14[7] = bVar7;
        FUN_0002d170();
        bVar7 = pbVar14[7];
        goto LAB_0002da6a;
      }
LAB_0002d8d6:
      if (!bVar19) {
        return 1;
      }
      if (*(int *)(puVar6 + 0x61) == 0) {
        return 1;
      }
      uVar11 = *(int *)(puVar6 + 0x61) - 1;
      bVar19 = uVar11 == param_3;
LAB_0002d8e4:
      bVar20 = false;
    } while (!bVar19);
    *(uint *)(puVar6 + 0x61) = uVar11;
    if (uVar11 != 0) {
LAB_0002d9fa:
      FUN_00032928(param_4,param_5,0);
      return 2;
    }
    FUN_00032928(param_4,param_5,1);
    *(byte *)(iVar17 + 10) = *(byte *)(iVar17 + 10) | 0x40;
LAB_0002da22:
    puVar6 = DAT_0002dc18;
    puVar6[0xf] = 7;
    puVar6[0x10] = 0;
    FUN_0002e274(0x3f);
    FUN_00027838(1,DAT_0002dc1c);
    return 2;
  case 99:
    bVar20 = param_2 == 0;
    if (!bVar20) goto LAB_0002d9f2;
    if (uVar2 >> 3 != 1) {
      *DAT_0002dc18 = uVar2 & 7 | 8;
    }
    FUN_0002d210();
    FUN_0002d238();
    FUN_0002d1e4();
    iVar16 = FUN_0002cbea(*(undefined2 *)(param_4 + 1),local_d0);
    FUN_0002cbb4(local_d0[0],iVar16,auStack_c4);
    auStack_c4[iVar16] = 0x2f;
    FUN_0002cbea(param_4[3],local_d0);
    FUN_0002cbb4(local_d0[0],2,auStack_c4 + iVar16 + 1);
    auStack_c4[iVar16 + 3] = 0x2f;
    FUN_0002cbea(param_4[4],local_d0);
    FUN_0002cbb4(local_d0[0],2,auStack_c4 + iVar16 + 4);
    FUN_0002e490(0,auStack_c4,iVar16 + 6,0x14,0xe);
    FUN_0002cbea(param_4[5],local_d0);
    FUN_0002cbb4(local_d0[0],2,auStack_c4);
    auStack_c4[2] = 0x3a;
    FUN_0002cbea(param_4[6],local_d0);
    FUN_0002cbb4(local_d0[0],2,auStack_c4 + 3);
    iVar16 = 5;
    if ((int)((uint)*param_4 << 0x18) < 0) {
      auStack_c4[5] = 0x3a;
      FUN_0002cbea(param_4[7],local_d0);
      FUN_0002cbb4(local_d0[0],2,auStack_c4 + 6);
      iVar16 = 8;
    }
    auStack_c4[iVar16] = 0x20;
    iVar17 = iVar16 + 1;
    if ((*param_4 & 0x7f) == 1) {
      uVar13 = FUN_0001c5f6(&local_38);
      FUN_0001c590(auStack_c4 + iVar16 + 1,&local_38,uVar13);
      puVar5 = &stack0x0000007c;
LAB_0002db88:
      iVar16 = FUN_0001c5f6(puVar5 + -0xb4);
      iVar17 = iVar17 + iVar16;
    }
    else if ((*param_4 & 0x7f) == 2) {
      uVar13 = FUN_0001c5f6(local_34);
      FUN_0001c590(auStack_c4 + iVar16 + 1,local_34,uVar13);
      puVar5 = &stack0x00000080;
      goto LAB_0002db88;
    }
    FUN_0002e490(1,auStack_c4,iVar17,0x14,0x22);
    uVar13 = 0xc;
    goto LAB_0002dc9e;
  case 100:
    break;
  case 0x65:
LAB_0002dca6:
    if (param_2 == 0) {
      FUN_0002d210();
      FUN_0002d238();
      FUN_0002d1e4();
      iVar16 = DAT_0002e0b8;
      bVar7 = *param_4;
      if (bVar7 == 0) {
        FUN_0002e4bc(8,0,0xc);
        uVar13 = FUN_0001c5f6(&local_58);
        FUN_0001c590(auStack_c4,&local_58,uVar13);
        pcVar9 = (char *)&local_58;
      }
      else if (bVar7 == 1) {
        FUN_0002e4bc(10,0,0xc);
        uVar13 = FUN_0001c5f6(local_50);
        FUN_0001c590(auStack_c4,local_50,uVar13);
        pcVar9 = local_50;
      }
      else {
        if (bVar7 != 2) {
          if (*(char *)(DAT_0002e0b8 + 0xd) == '\0') {
            return 2;
          }
          *(undefined1 *)(DAT_0002e0b8 + 0xd) = 0;
          if (*(int *)(puVar6 + 0x4f) == 2) {
            FUN_0002e1b4();
            *puVar6 = *puVar6 & 7 | 0x10;
            return 2;
          }
          if (*(int *)(puVar6 + 0x4f) == 0) {
            *(undefined2 *)(iVar16 + 0x18) = 0;
            *puVar6 = (byte)*puVar6 & 7;
            *(undefined4 *)(iVar16 + 0x4c) = 0;
            return 2;
          }
          return 2;
        }
        FUN_0002e4bc(9,0,0xc);
        uVar13 = FUN_0001c5f6(local_b0);
        FUN_0001c590(auStack_c4,local_b0,uVar13);
        pcVar9 = local_b0;
      }
      iVar16 = FUN_0001c5f6(pcVar9);
      iVar17 = DAT_0002e0b8;
      if (*(char *)(DAT_0002e0b8 + 0xd) == '\0') {
        *(uint *)(puVar6 + 0x4f) = (uint)(*puVar6 >> 3);
      }
      if (*puVar6 >> 3 != 1) {
        *puVar6 = *puVar6 & 7 | 8;
      }
      *(undefined1 *)(iVar17 + 0xd) = 1;
      uVar13 = 0x14;
      uVar21 = 0x18;
      uVar10 = 0;
      goto LAB_0002e0da;
    }
    break;
  case 0x66:
    if (param_2 != 0) goto LAB_0002dca6;
    if (1 < param_3) {
      return 1;
    }
    if (uVar2 >> 3 != 1) {
      *DAT_0002dc18 = uVar2 & 7 | 8;
    }
    FUN_0002d210();
    FUN_0002d238();
    FUN_0002d1e4();
    iVar16 = 0;
    FUN_0001c5d2(auStack_c4,0x11,0x20);
    iVar17 = 0;
    for (uVar8 = 0; uVar8 <= param_3; uVar8 = uVar8 + 1) {
      bVar7 = param_4[iVar17];
      if (bVar7 >> 4 == 0) {
        uVar13 = FUN_0001c5f6(&local_44);
        FUN_0001c590(auStack_c4 + iVar16,&local_44,uVar13);
        pcVar9 = (char *)&local_44;
LAB_0002de54:
        iVar18 = FUN_0001c5f6(pcVar9);
        iVar16 = iVar16 + iVar18;
      }
      else {
        if (bVar7 >> 4 == 1) {
          uVar13 = FUN_0001c5f6(&local_40);
          FUN_0001c590(auStack_c4 + iVar16,&local_40,uVar13);
          pcVar9 = (char *)&local_40;
          goto LAB_0002de54;
        }
        if (bVar7 >> 4 == 2) {
          uVar13 = FUN_0001c5f6(&local_3c);
          FUN_0001c590(auStack_c4 + iVar16,&local_3c,uVar13);
          pcVar9 = (char *)&local_3c;
          goto LAB_0002de54;
        }
        if (bVar7 >> 4 == 3) {
          uVar13 = FUN_0001c5f6(local_90 + 2);
          FUN_0001c590(auStack_c4 + iVar16,local_90 + 2,uVar13);
          pcVar9 = (char *)(local_90 + 2);
          goto LAB_0002de54;
        }
        if (bVar7 >> 4 == 4) {
          uVar13 = FUN_0001c5f6(local_80);
          FUN_0001c590(auStack_c4 + iVar16,local_80,uVar13);
          pcVar9 = local_80;
          goto LAB_0002de54;
        }
      }
      if (param_4[iVar17 + 1] != 0xff) {
        local_c8 = FUN_0002cbea(param_4[iVar17 + 1],local_d0);
        FUN_0002cbb4(local_d0[0],local_c8,auStack_c4 + iVar16);
        iVar16 = iVar16 + local_c8;
      }
      if (param_3 == 0) {
        auStack_c4[iVar16] = 0x20;
        iVar16 = iVar16 + 1;
      }
      else if ((param_3 == 1) && (uVar8 != 1)) {
        iVar16 = 9;
      }
      iVar17 = iVar17 + 4;
    }
    if (param_3 == 0) {
      uVar13 = 0x14;
      uVar21 = 0xe;
LAB_0002debc:
      FUN_0002e490(0,auStack_c4,iVar16,uVar13,uVar21);
    }
    else if (param_3 == 1) {
      uVar13 = 0;
      uVar21 = 4;
      goto LAB_0002debc;
    }
    FUN_0001c5d2(auStack_c4,0x11,0x20);
    iVar17 = 0;
    iVar18 = 0;
    for (uVar8 = 0; uVar8 <= param_3; uVar8 = uVar8 + 1) {
      if ((param_4[iVar18] & 0xf) == 0) {
        local_a0 = 6;
        uVar13 = FUN_0001c5f6(local_78);
        FUN_0001c590(auStack_c4 + iVar17,local_78,uVar13);
        iVar15 = FUN_0001c5f6(local_78);
        uVar13 = 0xff;
LAB_0002df66:
        iVar17 = iVar17 + iVar15;
        local_90[uVar8] = uVar13;
      }
      else {
        bVar7 = param_4[iVar18] & 0xf;
        if (bVar7 == 1) {
          local_a0 = 7;
          uVar13 = FUN_0001c5f6(&local_70);
          FUN_0001c590(auStack_c4 + iVar17,&local_70,uVar13);
          iVar15 = FUN_0001c5f6(&local_70);
          iVar17 = iVar17 + iVar15;
          local_90[uVar8] = 0;
        }
        else {
          if (bVar7 == 2) {
            local_a0 = 3;
            uVar13 = FUN_0001c5f6(&local_68);
            FUN_0001c590(auStack_c4 + iVar17,&local_68,uVar13);
            iVar15 = FUN_0001c5f6(&local_68);
            uVar13 = 5;
            goto LAB_0002df66;
          }
          if (bVar7 == 3) {
            local_a0 = 4;
            uVar13 = FUN_0001c5f6(&local_48);
            FUN_0001c590(auStack_c4 + iVar17,&local_48,uVar13);
            iVar15 = FUN_0001c5f6(&local_48);
LAB_0002dfac:
            uVar13 = 3;
          }
          else {
            if (bVar7 == 4) {
              local_a0 = 4;
              uVar13 = FUN_0001c5f6(&local_48);
              FUN_0001c590(auStack_c4 + iVar17,&local_48,uVar13);
              iVar15 = FUN_0001c5f6(&local_48);
              goto LAB_0002dfac;
            }
            if (bVar7 != 5) goto LAB_0002dfd8;
            local_a0 = 5;
            uVar13 = FUN_0001c5f6(&local_60);
            FUN_0001c590(auStack_c4 + iVar17,&local_60,uVar13);
            iVar15 = FUN_0001c5f6(&local_60);
            uVar13 = 6;
          }
          iVar17 = iVar17 + iVar15;
          local_90[uVar8] = uVar13;
        }
      }
LAB_0002dfd8:
      if ((param_3 == 1) && (uVar8 != 1)) {
        iVar17 = 9;
      }
      iVar18 = iVar18 + 4;
    }
    if (param_3 == 0) {
      uVar13 = 0xe;
      iVar16 = iVar16 * 6 + 0x14;
LAB_0002e00e:
      FUN_0002e490(1,auStack_c4,iVar17,iVar16,uVar13);
    }
    else if (param_3 == 1) {
      iVar16 = 0;
      uVar13 = 0x18;
      goto LAB_0002e00e;
    }
    iVar16 = 0;
    FUN_0001c5d2(auStack_c4,0x11,0x20);
    iVar17 = 0;
    for (uVar8 = 0; uVar8 <= param_3; uVar8 = uVar8 + 1) {
      iVar18 = FUN_0002cbea(*(undefined2 *)(param_4 + iVar17 + 2),local_d0);
      FUN_0002cbb4(local_d0[0],iVar18,auStack_c4 + iVar16);
      iVar16 = iVar16 + iVar18;
      if ((param_4[iVar17] & 0xf) == 0) {
        auStack_c4[iVar16] = 0x25;
        iVar16 = iVar16 + 1;
        if (param_3 == 1) {
LAB_0002e098:
          if (uVar8 != 1) {
            iVar16 = 9;
          }
        }
      }
      else if (param_3 == 0) {
        FUN_0002e470(uVar8,local_90[uVar8],iVar16 * 6 + 0x14,0x22);
      }
      else if (param_3 == 1) {
        FUN_0002e470(uVar8,local_90[uVar8],iVar16 * 6,0x2c);
        goto LAB_0002e098;
      }
      iVar17 = iVar17 + 4;
    }
    if (param_3 == 0) {
      FUN_0002e4bc(local_a0,0,0xc);
      uVar13 = 0x14;
      uVar21 = 0x22;
    }
    else {
      if (param_3 != 1) goto LAB_0002e0de;
      uVar13 = 0;
      uVar21 = 0x2c;
    }
    uVar10 = 2;
LAB_0002e0da:
    FUN_0002e490(uVar10,auStack_c4,iVar16,uVar13,uVar21);
    goto LAB_0002e0de;
  case 0x67:
    if (param_2 != 0) {
      if (param_2 != 1) {
        if (param_2 != 2) {
          return 1;
        }
        FUN_0002e304(param_4);
        return 0;
      }
      if (*(int *)(DAT_0002dc18 + 0x61) == 0) {
        return 1;
      }
      uVar8 = *(int *)(DAT_0002dc18 + 0x61) - 1;
      if (uVar8 != param_3) {
        return 1;
      }
      *(uint *)(DAT_0002dc18 + 0x61) = uVar8;
      FUN_0002e288(param_4,param_5);
      return 2;
    }
    *(undefined1 *)(DAT_0002e1b0 + 0x14) = 0;
    *(undefined1 *)(iVar18 + 0x13) = 0;
    *(undefined1 *)(iVar18 + 0x12) = 0;
    *(undefined4 *)(iVar18 + 0x48) = 0;
    uVar8 = (uint)*param_4;
    if (uVar8 == 1) goto LAB_0002e16a;
    puVar6[0x6f] = 0;
    puVar6[0x70] = 0;
    uVar2 = *(ushort *)(param_4 + 4);
    *(uint *)(iVar18 + 0x100) = (uint)(uVar2 >> 1);
    uVar12 = (uint)*(ushort *)(param_4 + 6);
    *(uint *)(iVar18 + 0x104) = uVar12;
    if (uVar8 == 0) {
      if (uVar12 != 0x40) goto LAB_0002e148;
    }
    else if (uVar12 != 0x20) {
LAB_0002e148:
      iVar15 = 1;
    }
    if (0x1a0 < (uVar2 >> 1) - 0x68) {
      iVar15 = 1;
    }
    *(uint *)(puVar6 + 0x61) = (uint)*(ushort *)(param_4 + 2);
    if (iVar15 == 1) {
      return 1;
    }
LAB_0002e16a:
    *(uint *)(puVar6 + 0x6b) = uVar8;
    *(uint *)(puVar6 + 0x6d) = (uint)param_4[1];
    *(undefined1 *)(iVar18 + 9) = 0;
    return iVar15;
  default:
    goto LAB_0002e1a6;
  }
  if (param_2 != 0) {
LAB_0002e1a6:
    return 1;
  }
  if (uVar2 >> 3 != 1) {
    *DAT_0002dc18 = uVar2 & 7 | 8;
  }
  FUN_0002d210();
  FUN_0002d238();
  FUN_0002d1e4();
  iVar16 = FUN_0002cbea(*param_4,local_d0);
  FUN_0002cbb4(local_d0[0],iVar16,auStack_c4);
  auStack_c4[iVar16] = 0x25;
  iVar17 = iVar16 + 1;
  if (param_4[1] != 0) {
    uVar13 = FUN_0001c5f6(local_9c);
    FUN_0001c590(auStack_c4 + iVar16 + 1,local_9c,uVar13);
    iVar16 = FUN_0001c5f6(local_9c);
    iVar17 = iVar17 + iVar16;
  }
  FUN_0002e490(0,auStack_c4,iVar17,0x14,0x18);
  uVar13 = 1;
LAB_0002dc9e:
  FUN_0002e4bc(uVar13,0,0xc);
LAB_0002e0de:
  FUN_0002e1d4(0);
  return 2;
}

