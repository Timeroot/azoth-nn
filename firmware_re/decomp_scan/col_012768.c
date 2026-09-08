// @0x12768 size=248

undefined8 FUN_00012768(char *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int extraout_r1;
  int extraout_r1_00;
  uint uVar8;
  uint uVar9;
  undefined8 uVar10;
  int local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  local_30 = param_2;
  uStack_2c = param_3;
  uStack_28 = param_4;
  uVar10 = FUN_00013108();
  iVar2 = DAT_000129ac;
  iVar6 = DAT_000129a8;
  iVar7 = (int)((ulonglong)uVar10 >> 0x20);
  bVar1 = (int)uVar10 != 0;
  if (*param_1 == '\0') {
    uVar4 = 0;
    do {
      if (iVar2 != 0) {
        iVar7 = 0;
        uVar4 = 0x4ff;
      }
      uVar9 = (uint)*(byte *)(iVar6 + 0xa9);
      *(undefined1 *)(iVar6 + 0x9f) = 0;
      uVar8 = 0;
      if (iVar2 != 0) {
        iVar7 = 0;
        uVar4 = 0x504;
      }
      uVar10 = CONCAT44(iVar7,uVar4);
      if (bVar1) {
        uVar10 = FUN_000125d4(uVar9,iVar7);
        uVar9 = (uint)uVar10;
      }
      if (iVar2 != 0) {
        uVar10 = 0x50c;
      }
      uVar3 = FUN_0000a7ca((int)uVar10,(int)((ulonglong)uVar10 >> 0x20));
      FUN_000126da(uVar3,param_1,&local_30,uVar9);
      iVar7 = extraout_r1;
      if (iVar2 != 0) {
        iVar7 = 0;
      }
      if ((*(char *)(iVar6 + 0xaa) != '\x1f') &&
         (iVar7 = *(int *)(iVar6 + 0x8c), iVar5 = (local_30 - iVar7) * 0x100,
         (int)(iVar5 + ((uint)(iVar5 >> 0x1f) >> 0x18)) >> 8 < 0)) {
        FUN_00013190(&local_30);
        uVar8 = 1;
        iVar7 = extraout_r1_00;
      }
      if (iVar2 != 0) {
        iVar7 = 0;
      }
      uVar4 = (uint)*(byte *)(iVar6 + 0x9f);
    } while (uVar4 != 0);
    uVar3 = 0;
    if (iVar2 != 0) {
      iVar7 = 0;
      uVar3 = 0x522;
    }
    uVar3 = FUN_0000a7ca(uVar3,iVar7);
    iVar6 = FUN_00013168(uVar3,0,DAT_000129b8,&local_30);
    uVar3 = 0;
    if (iVar6 != 0) {
      if (bVar1) {
        uVar4 = FUN_0001259e(&local_30,uVar9);
        uVar8 = uVar8 | uVar4;
      }
      if (uVar8 != 0) {
        uVar3 = FUN_00011dea(&local_30);
        *(undefined4 *)(param_1 + 8) = uVar3;
      }
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return CONCAT44(local_30,uVar3);
}

