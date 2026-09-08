// FUN_00025004 @00025004 size=2350

void FUN_00025004(void)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int *piVar3;
  ushort *puVar4;
  char *pcVar5;
  char *pcVar6;
  undefined2 *puVar7;
  undefined2 uVar8;
  ushort uVar9;
  undefined1 *puVar10;
  int iVar11;
  int iVar12;
  byte bVar13;
  char cVar14;
  undefined4 extraout_r1;
  int extraout_r2;
  undefined4 uVar15;
  ushort *puVar16;
  uint uVar17;
  undefined1 *puVar18;
  bool bVar19;
  int local_58;
  char local_54;
  char local_34 [4];
  undefined1 *local_30;
  undefined1 *local_2c;
  undefined1 *local_28;
  
  if ((DAT_00025404[9] & 1) == 0) {
switchD_00025052_caseD_0:
    return;
  }
  FUN_000385a4(*DAT_00025404);
  pcVar5 = DAT_00025840;
  piVar3 = DAT_00025408;
  puVar2 = DAT_00025404;
  puVar16 = (ushort *)(DAT_00025404 + -0x83a);
  local_28 = DAT_00025404 + -0x52e;
  puVar10 = DAT_00025404 + -0x770;
  local_30 = DAT_00025404 + -0x578;
  local_2c = DAT_00025404 + -0x582;
  puVar18 = DAT_00025404 + -0x580;
  switch(*DAT_00025404) {
  default:
    goto switchD_00025052_caseD_0;
  case 1:
    switch(DAT_00025404[8]) {
    case 0:
      iVar11 = FUN_00029f4c();
      if (iVar11 != 0) {
        return;
      }
      *DAT_0002540c = 0;
      FUN_000285ec(0,&local_58);
      if (local_58 == *piVar3) {
        FUN_0001c590(DAT_00025408,&local_58,0x20);
        uVar17 = (uint)*(byte *)((int)piVar3 + 6);
        *(undefined1 *)((int)piVar3 + 5) = *(undefined1 *)((int)piVar3 + uVar17 + 0xc);
        *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)((int)piVar3 + uVar17 + 0x12);
        *(undefined1 *)(piVar3 + 2) = *(undefined1 *)((int)piVar3 + uVar17 + 0x18);
        FUN_000285ec(1,DAT_00025410);
      }
      else {
        if (local_54 == (char)piVar3[1]) {
          local_58 = *piVar3;
          FUN_0001c590(DAT_00025408,&local_58,0x20);
        }
        uVar17 = (uint)*(byte *)((int)piVar3 + 6);
        *(undefined1 *)((int)piVar3 + 5) = *(undefined1 *)((int)piVar3 + uVar17 + 0xc);
        *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)((int)piVar3 + uVar17 + 0x12);
        *(undefined1 *)(piVar3 + 2) = *(undefined1 *)((int)piVar3 + uVar17 + 0x18);
        FUN_00027838(0,DAT_00025408);
        FUN_00027838(1,DAT_00025410);
      }
LAB_000250ea:
      bVar13 = *(byte *)((int)piVar3 + 6);
      uVar15 = 2;
      break;
    case 1:
      if ((*DAT_00025414 != 1) && ((int)((uint)*DAT_00025418 << 0x1d) < 0)) {
        return;
      }
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      if (*puVar16 == 0xffff) goto LAB_0002551c;
LAB_000254ca:
      bVar13 = *(byte *)((int)piVar3 + 6);
LAB_000252fc:
      uVar15 = 0x622;
      break;
    case 2:
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      uVar9 = FUN_00044cd8(puVar2 + -0x838,0x2b8);
      if (*puVar16 == (uVar9 & (*(byte *)((int)piVar3 + 6) | 0xfff0))) {
        if (((int)((uint)*(ushort *)(puVar2 + -0x838) << 0x10) < 0) &&
           (uVar17 = FUN_00044cd8(local_28,0x2c0), uVar17 != *(ushort *)(puVar2 + -0x530))) {
          *(ushort *)(puVar2 + -0x838) = *(ushort *)(puVar2 + -0x838) & 0x7fff;
        }
      }
      else {
        FUN_0002325c(puVar10);
        iVar11 = DAT_00025410;
        uVar17 = (uint)*(byte *)((int)piVar3 + 6);
        uVar1 = *(undefined1 *)(DAT_0002541c + uVar17);
        *(undefined1 *)((int)piVar3 + 5) = uVar1;
        *(undefined1 *)(iVar11 + 9) = 1;
        *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)(DAT_0002541c + 6 + uVar17);
        FUN_0001c5d2(puVar18,8,100);
        iVar11 = DAT_0002541c;
        *(undefined1 *)(piVar3 + 2) = *(undefined1 *)(DAT_0002541c + 0xc + uVar17);
        FUN_0001c590(local_30,iVar11 + 0x12,0x48);
        FUN_00022f60(uVar17,uVar1);
        *(undefined2 *)(puVar2 + -0x838) = 0;
        FUN_00024e50(local_2c,extraout_r1,puVar16);
        *(undefined2 *)(extraout_r2 + 0x620) = *(undefined2 *)(DAT_0002541c + -2);
      }
      FUN_000231e0(*(undefined1 *)((int)piVar3 + 5));
      FUN_00032550(puVar18[*(byte *)((int)piVar3 + 7)]);
      FUN_0002fc80();
      FUN_0002b45c();
      FUN_0002bfe4();
      FUN_0002e274(0x20);
      if (*(char *)(DAT_00025410 + 9) != '\0') {
        FUN_0002d2b4();
      }
      goto LAB_000251ec;
    case 3:
switchD_00025066_caseD_3:
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      if (*DAT_00025420 == 0xffff) goto LAB_0002551c;
      bVar13 = *(byte *)((int)piVar3 + 6);
      uVar15 = 0x1f2;
      goto LAB_00025218;
    case 4:
switchD_00025490_caseD_4:
      iVar11 = FUN_00029fd4();
      puVar16 = DAT_00025420;
      if (iVar11 == 0) {
        uVar17 = FUN_00044cd8(DAT_00025420 + 1,0x1f0);
        if (*puVar16 != uVar17) {
          FUN_00022f18(puVar16);
        }
        *DAT_00025424 = 1;
        puVar2 = DAT_00025404;
        *DAT_00025404 = 0;
        puVar2[8] = 0;
        puVar2[9] = puVar2[9] & 0xfe;
        return;
      }
      return;
    default:
      goto switchD_00025052_caseD_0;
    }
    iVar11 = (uint)bVar13 * 0x1000 + 0x2000;
    puVar16 = DAT_00025428;
    goto LAB_0002521c;
  case 2:
    switch(DAT_00025404[8]) {
    case 0:
      iVar11 = FUN_00029fd4();
      puVar2 = DAT_00025404;
      if (iVar11 == 0) {
        *(undefined1 *)((int)piVar3 + *(byte *)((int)piVar3 + 6) + 0xc) =
             *(undefined1 *)((int)piVar3 + 5);
        *(undefined1 *)((int)piVar3 + *(byte *)((int)piVar3 + 6) + 0x12) =
             *(undefined1 *)((int)piVar3 + 7);
        *(char *)((int)piVar3 + *(byte *)((int)piVar3 + 6) + 0x18) = (char)piVar3[2];
        uVar17 = (uint)(byte)puVar2[1];
        *(undefined1 *)((int)piVar3 + 6) = puVar2[1];
        *(undefined1 *)((int)piVar3 + 5) = *(undefined1 *)((int)piVar3 + uVar17 + 0xc);
        *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)((int)piVar3 + uVar17 + 0x12);
        *(undefined1 *)(piVar3 + 2) = *(undefined1 *)((int)piVar3 + uVar17 + 0x18);
        FUN_00027838(0,DAT_00025408);
        FUN_00027838(1,DAT_00025410);
        FUN_000283e0((uint)*(byte *)((int)piVar3 + 6) * 0x1000 + 0x2000,puVar2 + -0x83a,2);
        puVar2[8] = puVar2[8] + '\x01';
        FUN_0002e274(4);
        return;
      }
      return;
    case 1:
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      if (*puVar16 != 0xffff) {
        bVar13 = *(byte *)((int)piVar3 + 6);
        goto LAB_000252fc;
      }
      FUN_0002325c(puVar10);
      uVar17 = (uint)*(byte *)((int)piVar3 + 6);
      uVar1 = *(undefined1 *)(DAT_0002541c + uVar17);
      iVar11 = DAT_0002541c + 6;
      *(undefined1 *)((int)piVar3 + 5) = uVar1;
      *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)(iVar11 + uVar17);
      FUN_0001c5d2(puVar18,8,100);
      iVar11 = DAT_0002541c;
      *(undefined1 *)(piVar3 + 2) = *(undefined1 *)(DAT_0002541c + 0xc + uVar17);
      FUN_0001c590(local_30,iVar11 + 0x12,0x48);
      FUN_00022f60(uVar17,uVar1);
      *(undefined2 *)(puVar2 + -0x21a) = *(undefined2 *)(DAT_0002541c + -2);
      *(undefined2 *)(puVar2 + -0x838) = 0;
      goto LAB_0002551c;
    case 2:
      iVar11 = FUN_00029fd4();
      bVar19 = iVar11 == 0;
      break;
    case 3:
      goto switchD_00025066_caseD_3;
    case 4:
      iVar11 = FUN_00029fd4();
      puVar4 = DAT_00025838;
      bVar19 = false;
      if (iVar11 == 0) {
        uVar17 = FUN_00044cd8(DAT_00025838 + 1,0x1f0);
        if (*puVar4 != uVar17) {
          FUN_00022f18(puVar4);
        }
        pcVar5 = DAT_00025840;
        *DAT_0002583c = 1;
        if ((int)((uint)(byte)pcVar5[9] << 0x1e) < 0) {
          local_34[0] = *(char *)((int)piVar3 + 6);
          if (local_34[0] == '\0') {
            local_34[0] = '\x06';
          }
          FUN_00024efc(0x51,0,0,local_34,1);
        }
        *pcVar5 = '\0';
        pcVar5[8] = '\0';
        pcVar5[9] = pcVar5[9] & 0xfe;
        return;
      }
      break;
    default:
      return;
    }
    if (!bVar19) {
      return;
    }
    uVar9 = FUN_00044cd8(puVar2 + -0x838,0x2b8);
    if (*puVar16 == (uVar9 & (*(byte *)((int)piVar3 + 6) | 0xfff0))) {
      if (((int)((uint)*(ushort *)(puVar2 + -0x838) << 0x10) < 0) &&
         (uVar17 = FUN_00044cd8(local_28,0x2c0), uVar17 != *(ushort *)(puVar2 + -0x530))) {
        *(ushort *)(puVar2 + -0x838) = *(ushort *)(puVar2 + -0x838) & 0x7fff;
      }
    }
    else {
      FUN_0002325c(puVar10);
      uVar17 = (uint)*(byte *)((int)piVar3 + 6);
      uVar1 = *(undefined1 *)(DAT_0002541c + uVar17);
      iVar11 = DAT_0002541c + 6;
      *(undefined1 *)((int)piVar3 + 5) = uVar1;
      *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)(iVar11 + uVar17);
      FUN_0001c5d2(puVar18,8,100);
      iVar11 = DAT_0002541c;
      *(undefined1 *)(piVar3 + 2) = *(undefined1 *)(DAT_0002541c + 0xc + uVar17);
      FUN_0001c590(local_30,iVar11 + 0x12,0x48);
      FUN_00022f60(uVar17,uVar1);
      *(undefined2 *)(puVar2 + -0x21a) = *(undefined2 *)(DAT_0002541c + -2);
      *(undefined2 *)(puVar2 + -0x838) = 0;
      FUN_00024e50(local_2c);
    }
    FUN_000231e0(*(undefined1 *)((int)piVar3 + 5));
    FUN_00032550(puVar18[*(byte *)((int)piVar3 + 7)]);
    FUN_0002fc80();
    FUN_0002b45c();
    FUN_0002bfe4();
    FUN_0002e274(0x20);
    break;
  case 3:
    switch(DAT_00025840[8]) {
    case '\0':
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      uVar17 = (uint)*(byte *)((int)piVar3 + 6);
      *(undefined1 *)((int)piVar3 + 5) = *(undefined1 *)((int)piVar3 + uVar17 + 0xc);
      *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)((int)piVar3 + uVar17 + 0x12);
      *(char *)((int)piVar3 + uVar17 + 0x18) = (char)piVar3[2];
      goto LAB_000250ea;
    case '\x01':
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      if (*puVar16 != 0xffff) goto LAB_000254ca;
      FUN_0002325c(puVar10);
      *(undefined1 *)((int)piVar3 + 5) =
           *(undefined1 *)(DAT_00025844 + (uint)*(byte *)((int)piVar3 + 6));
      FUN_00022f60();
      bVar13 = *(byte *)((int)piVar3 + 6);
      *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)(DAT_00025844 + 6 + (uint)bVar13);
      FUN_0001c5d2(puVar18,8,100);
      iVar11 = DAT_00025844;
      *(undefined1 *)(piVar3 + 2) = *(undefined1 *)(DAT_00025844 + 0xc + (uint)bVar13);
      FUN_0001c590(local_30,iVar11 + 0x12,0x48);
      *(undefined2 *)(puVar2 + -0x21a) = *(undefined2 *)(DAT_00025844 + -2);
      *(undefined2 *)(puVar2 + -0x838) = 0;
      goto LAB_0002551c;
    case '\x02':
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      uVar9 = FUN_00044cd8(puVar2 + -0x838,0x2b8);
      if (*puVar16 == (uVar9 & (*(byte *)((int)piVar3 + 6) | 0xfff0))) {
        if (((int)((uint)*(ushort *)(puVar2 + -0x838) << 0x10) < 0) &&
           (uVar17 = FUN_00044cd8(local_28,0x2c0), uVar17 != *(ushort *)(puVar2 + -0x530))) {
          *(ushort *)(puVar2 + -0x838) = *(ushort *)(puVar2 + -0x838) & 0x7fff;
        }
      }
      else {
        FUN_0002325c(puVar10);
        *(undefined1 *)((int)piVar3 + 5) =
             *(undefined1 *)(DAT_00025844 + (uint)*(byte *)((int)piVar3 + 6));
        FUN_00022f60();
        bVar13 = *(byte *)((int)piVar3 + 6);
        *(undefined1 *)((int)piVar3 + 7) = *(undefined1 *)(DAT_00025844 + 6 + (uint)bVar13);
        FUN_0001c5d2(puVar18,8,100);
        iVar11 = DAT_00025844;
        *(undefined1 *)(piVar3 + 2) = *(undefined1 *)(DAT_00025844 + 0xc + (uint)bVar13);
        FUN_0001c590(local_30,iVar11 + 0x12,0x48);
        *(undefined2 *)(puVar2 + -0x21a) = *(undefined2 *)(DAT_00025844 + -2);
        *(undefined2 *)(puVar2 + -0x838) = 0;
        FUN_00024e50(local_2c);
      }
      FUN_000231e0(*(undefined1 *)((int)piVar3 + 5));
      FUN_00032550(puVar18[*(byte *)((int)piVar3 + 7)]);
      FUN_0002fc80();
      FUN_0002b45c();
      FUN_0002bfe4();
      FUN_0002e274(0x20);
      FUN_00024efc(0x50,0x30,0,0,0);
      break;
    case '\x03':
      goto switchD_00025066_caseD_3;
    case '\x04':
      goto switchD_00025490_caseD_4;
    default:
      goto switchD_00025604_default;
    }
    break;
  case 4:
    switch(DAT_00025840[8]) {
    case '\0':
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      *(undefined1 *)((int)piVar3 + *(byte *)((int)piVar3 + 6) + 0xc) =
           *(undefined1 *)((int)piVar3 + 5);
      *(undefined1 *)((int)piVar3 + *(byte *)((int)piVar3 + 6) + 0x12) =
           *(undefined1 *)((int)piVar3 + 7);
      *(char *)((int)piVar3 + *(byte *)((int)piVar3 + 6) + 0x18) = (char)piVar3[2];
      FUN_00027838(0,DAT_00025848);
      FUN_00027838(1,DAT_0002584c);
      if (*(byte *)((int)piVar3 + 5) < 10) {
        uVar9 = (ushort)(1 << (uint)*(byte *)((int)piVar3 + 5));
      }
      else {
        uVar9 = 0x8000;
      }
      *(ushort *)(puVar2 + -0x838) = *(ushort *)(puVar2 + -0x838) | uVar9;
      uVar9 = FUN_00044cd8(puVar2 + -0x838,0x2b8);
      *puVar16 = uVar9 & (*(byte *)((int)piVar3 + 6) | 0xfff0);
      if ((int)((uint)*(ushort *)(puVar2 + -0x838) << 0x10) < 0) {
        uVar8 = FUN_00044cd8(local_28,0x2c0);
        *(undefined2 *)(puVar2 + -0x530) = uVar8;
      }
      FUN_00028390((uint)*(byte *)((int)piVar3 + 6) * 0x1000 + 0x2000,DAT_00025850,0x622);
      goto LAB_0002574c;
    case '\x01':
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      iVar11 = FUN_00029fe4();
      if (iVar11 == 0) goto LAB_000257b6;
      pcVar5[9] = pcVar5[9] & 0xf3;
      pcVar5[8] = pcVar5[8] + '\x01';
    case '\x02':
      goto switchD_00025604_caseD_2;
    case '\x03':
      goto switchD_00025604_caseD_3;
    case '\x04':
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      iVar11 = FUN_00029fe4();
      if (iVar11 != 0) {
        if (*(char *)(DAT_00025848 + -0x26) != '\0') {
          *(undefined1 *)(DAT_00025848 + -0x26) = 0;
        }
        if ((int)((uint)(byte)pcVar5[9] << 0x1e) < 0) {
          FUN_00024efc(0x50,0x55,0,0,0);
        }
        *pcVar5 = '\0';
        pcVar5[8] = '\0';
        pcVar5[9] = pcVar5[9] & 0xfe;
        return;
      }
LAB_000257b6:
      bVar13 = pcVar5[9];
      if ((bVar13 & 0xf) >> 2 < 3) {
        pcVar5[9] = (byte)(((uint)(bVar13 >> 4) | (uint)bVar13 << 0x1c) + 0x40000000 >> 0x1c) |
                    (bVar13 >> 4) << 4;
        pcVar5[8] = '\0';
        return;
      }
      goto LAB_000256d4;
    default:
      goto switchD_00025604_default;
    }
  case 5:
  case 6:
    cVar14 = DAT_00025840[8];
    if (cVar14 == '\0') {
      iVar12 = FUN_00029fd4();
      iVar11 = DAT_000259a8;
      if (iVar12 != 0) {
        return;
      }
      if (pcVar5[1] == '\x01') {
        bVar13 = pcVar5[2];
        *(undefined1 *)(DAT_000259a8 + (uint)bVar13) = 0x10;
        FUN_00028370((uint)bVar13 * 0x1000 + 0x2000);
        bVar13 = pcVar5[2];
        pcVar5[2] = bVar13 + 1;
        if (bVar13 < 5) {
          return;
        }
        if ((*(int *)(DAT_000259ac + 0x10) != 0) && (*pcVar5 == '\x06')) {
          *(undefined1 *)(iVar11 + 6) = 0;
          *(undefined1 *)(iVar11 + 7) = 0;
          *(undefined1 *)(iVar11 + 8) = 0;
        }
        puVar7 = DAT_000259b4;
        iVar11 = DAT_000259b0;
        *(undefined1 *)((int)piVar3 + 6) = 0;
        *(undefined4 *)(iVar11 + 0x38) = *(undefined4 *)(puVar7 + 1);
        *(undefined2 *)(iVar11 + 0x3c) = puVar7[3];
        *(undefined4 *)(iVar11 + 0x3e) = *(undefined4 *)(puVar7 + 4);
        *(undefined2 *)(iVar11 + 0x42) = puVar7[6];
        *(undefined4 *)(iVar11 + 0x44) = *(undefined4 *)(puVar7 + 7);
        *(undefined2 *)(iVar11 + 0x48) = puVar7[9];
        cVar14 = pcVar5[8] + '\x01';
      }
      else {
        bVar13 = *(byte *)((int)piVar3 + 6);
        *(undefined1 *)(DAT_000259a8 + (uint)bVar13) = 0x10;
        FUN_00028370((uint)bVar13 * 0x1000 + 0x2000);
        cVar14 = '\x02';
      }
      pcVar5[8] = cVar14;
      uVar17 = (uint)*(byte *)((int)piVar3 + 6);
      *(undefined1 *)((int)piVar3 + 5) = *(undefined1 *)((int)DAT_000259b4 + uVar17 + 2);
      FUN_0001c5e0(DAT_000259b8,0x622);
      bVar13 = *(byte *)((int)DAT_000259b4 + uVar17 + 8);
      *(byte *)((int)piVar3 + 7) = bVar13;
      FUN_0001c5d2(puVar18,8,100);
      puVar7 = DAT_000259b4;
      *(undefined1 *)(piVar3 + 2) = *(undefined1 *)((int)DAT_000259b4 + uVar17 + 0xe);
      FUN_0001c590(local_30,puVar7 + 10,0x48);
      FUN_00032550(puVar18[bVar13],(uint)bVar13);
      *(undefined2 *)(puVar2 + -0x21a) = *DAT_000259b4;
      FUN_00022f60(*(undefined1 *)((int)piVar3 + 6),*(undefined1 *)((int)piVar3 + 5));
      FUN_000231e0(*(undefined1 *)((int)piVar3 + 5));
      FUN_00024e50(local_2c);
      FUN_0002fc80();
      FUN_0002b45c();
      FUN_0002e274(0x3f);
      FUN_0002d190();
      return;
    }
    if (cVar14 == '\x01') {
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      FUN_00028350(0x320000);
      cVar14 = '\x03';
    }
    else {
      if (cVar14 != '\x02') {
        if (cVar14 != '\x03') {
          return;
        }
        iVar11 = FUN_00029fd4();
        if (iVar11 == 0) {
          *(undefined1 *)(DAT_00025848 + -0x26) = 0;
          *DAT_0002583c = 1;
          FUN_00022f18(DAT_00025838);
          FUN_0002325c(puVar10);
          FUN_00028430(1);
          FUN_00027838(2,DAT_0002585c);
          FUN_00027838(0,DAT_00025848);
          FUN_00027838(1,DAT_0002584c);
          if ((int)((uint)(byte)pcVar5[9] << 0x1e) < 0) {
            FUN_00024efc(0x50,0x40,0,pcVar5 + 1,1);
          }
          iVar11 = FUN_00029f00();
          if (iVar11 == 0) {
            *pcVar5 = '\0';
            pcVar5[8] = '\0';
            pcVar5[9] = pcVar5[9] & 0xfe;
          }
          else {
            FUN_00024e84();
          }
          FUN_0002bfe4();
          FUN_0002e38c();
          return;
        }
        return;
      }
      iVar11 = FUN_00029fd4();
      if (iVar11 != 0) {
        return;
      }
      FUN_00028370((uint)*(byte *)((int)piVar3 + 6) * 0x1000 + 0x320000);
      cVar14 = pcVar5[8] + '\x01';
    }
    pcVar5[8] = cVar14;
    return;
  }
  FUN_0002d190();
LAB_000251ec:
  bVar13 = *(byte *)((int)piVar3 + 6);
  uVar15 = 2;
LAB_00025218:
  iVar11 = (uint)bVar13 * 0x1000 + 0x320000;
  puVar16 = DAT_00025420;
LAB_0002521c:
  FUN_000283e0(iVar11,puVar16,uVar15);
LAB_0002551c:
  DAT_00025840[8] = DAT_00025840[8] + '\x01';
switchD_00025604_default:
  return;
switchD_00025604_caseD_2:
  iVar11 = FUN_00029fd4();
  pcVar6 = DAT_00025854;
  if ((((iVar11 == 0) && (pcVar5[8] = pcVar5[8] + '\x01', *pcVar6 != '\0')) && (pcVar6[3] != '\0'))
     && (*(int *)(DAT_00025858 + 0x30) != 1)) {
    FUN_0002bbdc();
    return;
  }
switchD_00025604_caseD_3:
  iVar11 = FUN_00029fd4();
  if (iVar11 != 0) {
    return;
  }
  iVar11 = FUN_00029fe4();
  pcVar6 = DAT_00025854;
  if (iVar11 == 0) {
    bVar13 = pcVar5[9];
    if (2 < (bVar13 & 0xf) >> 2) {
LAB_000256d4:
      *pcVar5 = '\0';
      pcVar5[8] = '\0';
      pcVar5[9] = bVar13 & 0xfe;
      return;
    }
    pcVar5[9] = (byte)(((uint)(bVar13 >> 4) | (uint)bVar13 << 0x1c) + 0x40000000 >> 0x1c) |
                (bVar13 >> 4) << 4;
    cVar14 = '\x02';
  }
  else {
    *DAT_00025854 = '\0';
    pcVar6[3] = '\0';
    puVar16 = DAT_00025838;
    if (*(char *)(DAT_00025848 + -0x26) != '\0') {
      uVar9 = FUN_00044cd8(DAT_00025838 + 1,0x1f0);
      *puVar16 = uVar9;
      FUN_00028390((uint)*(byte *)((int)piVar3 + 6) * 0x1000 + 0x320000,puVar16,0x1f2);
      pcVar5[9] = pcVar5[9] & 0xf3;
    }
LAB_0002574c:
    cVar14 = pcVar5[8] + '\x01';
  }
  pcVar5[8] = cVar14;
  return;
}

