// @0x2cf80 size=494

void FUN_0002cf80(void)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int extraout_r2;
  int iVar4;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  undefined4 extraout_r3_01;
  undefined4 uVar5;
  byte bVar6;
  undefined4 unaff_r4;
  int iVar7;
  undefined4 unaff_r5;
  int iVar8;
  undefined4 unaff_r6;
  int iVar9;
  int iVar10;
  int iVar11;
  
  pbVar2 = DAT_0002cfbc;
  bVar6 = 0;
  do {
    iVar1 = FUN_0003f994(pbVar2 + 4);
    uVar5 = extraout_r3;
    if (iVar1 == 0) break;
    FUN_0002cbd0(1);
    bVar6 = bVar6 + 1;
    uVar5 = extraout_r3_00;
  } while (bVar6 < 10);
  iVar1 = DAT_0002cfc0;
  if (*(char *)(DAT_0002cfc0 + (uint)*DAT_0002cfbc) != '\0') {
    pbVar2 = DAT_0002cfbc + 4;
    iVar8 = DAT_0003fab0 + (uint)DAT_0002cfbc[8] * 0x24;
    iVar7 = *(int *)pbVar2;
    if (*(int *)(iVar8 + 4) != 0) {
      *(undefined4 *)(iVar7 + 0x308) = DAT_0003fab4;
      uVar3 = (*(int *)pbVar2 << 0xc) >> 0x18;
      if (-1 < (int)uVar3) {
        *(int *)(&DAT_e000e180 + (uVar3 >> 5) * 4) = 1 << (uVar3 & 0x1f);
        DataSynchronizationBarrier(0xf);
        InstructionSynchronizationBarrier(0xf);
      }
    }
    *(uint *)(iVar7 + 0x200) = *(uint *)(iVar7 + 0x200) & 0xffffffdf;
    if (*(int *)(iVar8 + 0x18) != 0) {
      FUN_0003e4fe(iVar7,0x144,iVar1,uVar5,unaff_r4,unaff_r5,unaff_r6);
      *(undefined4 *)(iVar7 + 4) = 1;
      iVar1 = extraout_r2;
      uVar5 = extraout_r3_01;
    }
    FUN_0003e4fe(iVar7,0x158,iVar1,uVar5,unaff_r4,unaff_r5,unaff_r6);
    *(undefined4 *)(iVar7 + 0xc) = 1;
    do {
      do {
        iVar1 = FUN_0003e4f4(iVar7,0x158);
      } while (iVar1 == 0);
    } while ((*(int *)(iVar8 + 0x18) != 0) && (iVar1 = FUN_0003e4f4(iVar7,0x144), iVar1 == 0));
    *(undefined4 *)(iVar7 + 0x500) = 0;
    iVar1 = *(int *)pbVar2;
    iVar4 = *(int *)(iVar1 + 0x50c);
    iVar11 = *(int *)(iVar1 + 0x514);
    iVar10 = *(int *)(iVar1 + 0x508);
    iVar9 = *(int *)(iVar1 + 0x510);
    *(undefined4 *)(iVar1 + 0x50c) = 0xffffffff;
    *(undefined4 *)(iVar1 + 0x514) = 0xffffffff;
    iVar1 = *(int *)pbVar2;
    *(undefined4 *)(iVar1 + 0x508) = 0xffffffff;
    *(undefined4 *)(iVar1 + 0x510) = 0xffffffff;
    if (iVar4 != -1) {
      FUN_0003da88(iVar4);
    }
    if (iVar11 != -1) {
      FUN_0003da88(iVar11);
    }
    if (iVar9 != -1) {
      FUN_0003da88(iVar9);
    }
    if (iVar10 != -1) {
      FUN_0003da88(iVar10);
    }
    FUN_0003ec96(iVar7);
    *(undefined1 *)(iVar8 + 0x20) = 0;
    *(undefined4 *)(iVar8 + 4) = 0;
    return;
  }
  pbVar2 = DAT_0002cfbc + 0xc;
  iVar1 = DAT_0003f864 + (uint)DAT_0002cfbc[0x10] * 0x2c;
  *(undefined4 *)(*(int *)pbVar2 + 0x500) = 0;
  if (*(int *)(iVar1 + 4) != 0) {
    *(undefined4 *)(*(int *)pbVar2 + 0x308) = DAT_0003f868;
    uVar3 = (*(int *)pbVar2 << 0xc) >> 0x18;
    if (-1 < (int)uVar3) {
      *(int *)(&DAT_e000e180 + (uVar3 >> 5) * 4) = 1 << (uVar3 & 0x1f);
      DataSynchronizationBarrier(0xf);
      InstructionSynchronizationBarrier(0xf);
    }
  }
  iVar7 = *(int *)pbVar2;
  iVar8 = *(int *)(iVar7 + 0x50c);
  iVar10 = *(int *)(iVar7 + 0x514);
  iVar9 = *(int *)(iVar7 + 0x508);
  iVar4 = *(int *)(iVar7 + 0x510);
  *(undefined4 *)(iVar7 + 0x514) = 0xffffffff;
  *(undefined4 *)(iVar7 + 0x50c) = 0xffffffff;
  iVar7 = *(int *)pbVar2;
  *(undefined4 *)(iVar7 + 0x508) = 0xffffffff;
  *(undefined4 *)(iVar7 + 0x510) = 0xffffffff;
  if (iVar8 != -1) {
    FUN_0003da76(iVar8);
  }
  if (iVar10 != -1) {
    FUN_0003da76(iVar10);
  }
  if (iVar4 != -1) {
    FUN_0003da76(iVar4);
  }
  if (iVar9 != -1) {
    FUN_0003da76(iVar9);
  }
  FUN_0003ec96(*(undefined4 *)pbVar2);
  *(undefined1 *)(iVar1 + 0x2a) = 0;
  *(undefined4 *)(iVar1 + 4) = 0;
  return;
}

