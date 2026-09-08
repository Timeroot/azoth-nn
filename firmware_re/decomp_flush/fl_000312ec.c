
void FUN_000312ec(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  undefined4 unaff_r4;
  byte bVar5;
  undefined4 unaff_r5;
  int *piVar6;
  undefined4 unaff_r6;
  
  bVar5 = 0;
  if (*(int *)(*(int *)(param_1 + 4) + 0x500) != 7) {
    return;
  }
  do {
    iVar1 = FUN_0002a034(param_1);
    if (iVar1 == 0) break;
    FUN_0002cbd0(1);
    bVar5 = bVar5 + 1;
  } while (bVar5 < 10);
  piVar2 = (int *)(param_1 + 4);
  piVar6 = (int *)(DAT_0003f34c + (uint)*(byte *)(param_1 + 8) * 0x24);
  if ((*piVar6 != 0) && (uVar3 = (*piVar2 << 0xc) >> 0x18, -1 < (int)uVar3)) {
    *(int *)(&DAT_e000e180 + (uVar3 >> 5) * 4) = 1 << (uVar3 & 0x1f);
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
  }
  iVar1 = *piVar2;
  if ((*piVar6 != 0) &&
     (*(undefined4 *)(iVar1 + 0x308) = DAT_0003f350, *(char *)((int)piVar6 + 0x1d) != '\0')) {
    *(undefined4 *)(iVar1 + 0x14) = 1;
    do {
      iVar4 = FUN_0003e492(iVar1,0x104);
    } while (iVar4 == 0);
    *(undefined1 *)((int)piVar6 + 0x1d) = 0;
  }
  if ((char)piVar6[8] != -1) {
    FUN_0003d9d8((char)piVar6[8],0,1,0,0,0,unaff_r4,unaff_r5,unaff_r6);
  }
  *(undefined4 *)(iVar1 + 0x500) = 0;
  if (iVar1 == DAT_0003f354) {
    *(undefined4 *)(DAT_0003f354 + 4) = 1;
  }
  FUN_0003ec96(*piVar2);
  *(undefined1 *)(piVar6 + 7) = 0;
  return;
}

