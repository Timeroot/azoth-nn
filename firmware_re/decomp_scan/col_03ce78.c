// @0x3ce78 size=274

undefined4 FUN_0003ce78(byte *param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  byte *pbVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_r4;
  uint uVar5;
  int *piVar6;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_r7;
  undefined4 unaff_r8;
  undefined4 unaff_lr;
  
  iVar4 = DAT_0003ceb0;
  uVar5 = (uint)*param_1;
  *(int *)(DAT_0003ceb0 + uVar5 * 4) = param_3;
  *(undefined4 *)(iVar4 + 8 + uVar5 * 4) = param_4;
  if (*(char *)((int)param_2 + 0xd) != '\0') {
    FUN_00044774(param_2);
  }
  iVar4 = DAT_0003ceb4;
  if (param_3 == 0) {
    iVar4 = 0;
  }
  pbVar1 = param_1 + 4;
  piVar6 = (int *)(DAT_0003f4f8 + (uint)param_1[8] * 0x34);
  if (*(char *)((int)piVar6 + 0x2d) == '\0') {
    iVar3 = FUN_0003ec5c(*(undefined4 *)pbVar1,*(undefined4 *)(DAT_0003f4fc + (uint)param_1[8] * 4),
                         DAT_0003f4f8,uVar5,iVar4,uVar5,unaff_r4,unaff_r5,unaff_r6,unaff_r7,unaff_r8
                         ,unaff_lr);
    if (iVar3 == 0) {
      *piVar6 = iVar4;
      piVar6[1] = uVar5;
      piVar6[2] = 0;
      *(undefined1 *)(piVar6 + 0xc) = 0;
      *(undefined1 *)((int)piVar6 + 0x2f) = 0;
      *(undefined1 *)((int)piVar6 + 0x32) = *(undefined1 *)((int)param_2 + 0xd);
      FUN_0003da0c(*param_2,0,0,3,6,0);
      FUN_0003da0c(param_2[1],0,0,3,6,0);
      uVar2 = param_2[1];
      iVar4 = *(int *)pbVar1;
      *(undefined4 *)(iVar4 + 0x508) = *param_2;
      *(undefined4 *)(iVar4 + 0x50c) = uVar2;
      *(undefined4 *)(iVar4 + 0x524) = param_2[2];
      if (*piVar6 != 0) {
        uVar5 = (*(int *)pbVar1 << 0xc) >> 0x18;
        if ((int)uVar5 < 0) {
          *(char *)((uVar5 & 0xf) + 0xe000ed14) = *(char *)(param_2 + 3) << 5;
        }
        else {
          (&DAT_e000e400)[uVar5] = *(char *)(param_2 + 3) << 5;
        }
        uVar5 = (*(int *)pbVar1 << 0xc) >> 0x18;
        if (-1 < (int)uVar5) {
          *(int *)(&DAT_e000e100 + (uVar5 >> 5) * 4) = 1 << (uVar5 & 0x1f);
        }
      }
      *(undefined1 *)((int)piVar6 + 0x2d) = 1;
      uVar2 = 0;
    }
    else {
      uVar2 = 0x11;
    }
  }
  else {
    uVar2 = 8;
  }
  return uVar2;
}

