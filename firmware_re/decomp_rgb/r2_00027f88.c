// FUN_00027f88 @00027f88 size=764

void FUN_00027f88(byte *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  puVar2 = DAT_00028294;
  if ((-1 < (int)((uint)*DAT_0002828c << 0x1d)) && (*(int *)(DAT_00028290 + 0x60) != 0)) {
    return;
  }
  uVar3 = *(int *)(DAT_00028294 + 4) + 1;
  *(uint *)(DAT_00028294 + 4) = uVar3;
  bVar1 = *param_1;
  uStack_18 = param_3;
  uStack_14 = param_4;
  if (bVar1 == 8) {
    if (uVar3 < param_1[10]) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00027430(param_1);
    goto LAB_00028274;
  }
  if (8 < bVar1) {
    if (bVar1 == 0xf3) {
      if (uVar3 < 100) goto switchD_00027fb2_default;
      *(undefined4 *)(puVar2 + 4) = 0;
      *puVar2 = 1;
      FUN_00030c90(param_1);
    }
    else if (bVar1 < 0xf4) {
      if (bVar1 == 9) {
        if (uVar3 < param_1[0xb]) goto switchD_00027fb2_default;
        *(undefined4 *)(puVar2 + 4) = 0;
        *puVar2 = 1;
        FUN_00030958(param_1);
      }
      else {
        if (bVar1 == 0xf0) {
          *puVar2 = 1;
          iVar4 = *(int *)(puVar2 + 0x30);
          *(int *)(puVar2 + 0x30) = iVar4 + 1;
          if (((int)(uint)param_1[3] <= iVar4 + 1) &&
             ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x1e) < 0)) {
            *(undefined4 *)(puVar2 + 0x30) = 0;
            param_1[1] = 2;
            FUN_00025e50(param_1);
          }
          iVar4 = *(int *)(puVar2 + 0x34);
          *(int *)(puVar2 + 0x34) = iVar4 + 1;
          bVar1 = param_1[4];
          if (((int)(uint)bVar1 <= iVar4 + 1) &&
             ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x1d) < 0)) {
            *(undefined4 *)(puVar2 + 0x34) = 0;
            param_1[1] = 3;
            iVar4 = *(int *)(puVar2 + 0x54);
            *(int *)(puVar2 + 0x54) = iVar4 + 1;
            if (iVar4 + 1 == 4) {
              *(uint *)(puVar2 + 0x34) = (uint)bVar1;
            }
            else {
              FUN_000272cc(param_1);
              if (4 < *(int *)(puVar2 + 0x54)) {
                *(undefined4 *)(puVar2 + 0x54) = 0;
              }
            }
          }
          iVar4 = *(int *)(puVar2 + 0x38);
          *(int *)(puVar2 + 0x38) = iVar4 + 1;
          if ((4 < iVar4 + 1) && ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x1b) < 0)) {
            *(undefined4 *)(puVar2 + 0x38) = 0;
            param_1[1] = 4;
            FUN_00033578(param_1);
          }
          FUN_00030fa0(&uStack_18,param_1);
          iVar4 = *(int *)(puVar2 + 0x3c);
          *(int *)(puVar2 + 0x3c) = iVar4 + 1;
          if (((int)(uint)param_1[7] <= iVar4 + 1) &&
             ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x1a) < 0)) {
            *(undefined4 *)(puVar2 + 0x3c) = 0;
            param_1[1] = 5;
            FUN_00030e48(param_1);
          }
          FUN_00030b24(param_1,0);
          iVar4 = *(int *)(puVar2 + 0x40);
          *(int *)(puVar2 + 0x40) = iVar4 + 1;
          if (((int)(uint)param_1[5] <= iVar4 + 1) &&
             ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x1c) < 0)) {
            *(undefined4 *)(puVar2 + 0x40) = 0;
            param_1[1] = 6;
            FUN_00030a2c(param_1);
          }
          iVar4 = *(int *)(puVar2 + 0x44);
          *(int *)(puVar2 + 0x44) = iVar4 + 1;
          if (((int)(uint)param_1[8] <= iVar4 + 1) &&
             ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x19) < 0)) {
            *(undefined4 *)(puVar2 + 0x44) = 0;
            param_1[1] = 7;
            FUN_00032dac(param_1);
          }
          iVar4 = *(int *)(puVar2 + 0x48);
          *(int *)(puVar2 + 0x48) = iVar4 + 1;
          if (((int)(uint)param_1[9] <= iVar4 + 1) &&
             ((int)((uint)**(byte **)(puVar2 + 0x70) << 0x18) < 0)) {
            *(undefined4 *)(puVar2 + 0x48) = 0;
            param_1[1] = 8;
            FUN_000301c8(param_1);
          }
          iVar4 = *(int *)(puVar2 + 0x4c);
          *(int *)(puVar2 + 0x4c) = iVar4 + 1;
          if (((int)(uint)param_1[10] <= iVar4 + 1) &&
             ((int)((uint)**(ushort **)(puVar2 + 0x70) << 0x17) < 0)) {
            *(undefined4 *)(puVar2 + 0x4c) = 0;
            param_1[1] = 9;
            FUN_00027430(param_1);
          }
          iVar4 = *(int *)(puVar2 + 0x50);
          *(int *)(puVar2 + 0x50) = iVar4 + 1;
          if (((int)(uint)param_1[0xb] <= iVar4 + 1) &&
             ((int)((uint)**(ushort **)(puVar2 + 0x70) << 0x16) < 0)) {
            *(undefined4 *)(puVar2 + 0x50) = 0;
            param_1[1] = 10;
            FUN_00030958(param_1);
          }
          *puVar2 = 0;
          goto switchD_00027fb2_default;
        }
        if (bVar1 == 0xf1) goto switchD_00027fb2_default;
        bVar6 = bVar1 == 0xf2;
LAB_00027fd2:
        if ((!bVar6) || (uVar3 < 100)) goto switchD_00027fb2_default;
        *(undefined4 *)(puVar2 + 4) = 0;
        *puVar2 = 1;
        FUN_00030d08(param_1);
      }
    }
    else if (bVar1 == 0xf4) {
      if (uVar3 < 2) goto switchD_00027fb2_default;
      *(undefined4 *)(puVar2 + 4) = 0;
      *puVar2 = 1;
      FUN_0002b520(param_1);
    }
    else {
      bVar6 = bVar1 == 0xf5;
      if (!bVar6) goto LAB_00027fd2;
      if (uVar3 < 2) goto switchD_00027fb2_default;
      *(undefined4 *)(puVar2 + 4) = 0;
      *puVar2 = 1;
      FUN_0002b4cc(param_1);
    }
    goto LAB_00028274;
  }
  switch(bVar1) {
  case 0:
    bVar7 = uVar3 <= param_1[2];
    bVar6 = param_1[2] == uVar3;
    goto LAB_00027fe4;
  case 1:
    bVar7 = uVar3 <= param_1[3];
    bVar6 = param_1[3] == uVar3;
    if (bVar7 && !bVar6) goto LAB_00027fe4;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00025e50(param_1);
    break;
  case 2:
    uVar5 = (uint)param_1[4];
    bVar7 = uVar3 <= uVar5;
    bVar6 = uVar5 == uVar3;
    if (!bVar7 || bVar6) {
      *(undefined4 *)(puVar2 + 4) = 0;
      iVar4 = *(int *)(puVar2 + 0x54);
      *(int *)(puVar2 + 0x54) = iVar4 + 1;
      if (iVar4 + 1 == 4) {
        *(uint *)(puVar2 + 4) = uVar5;
      }
      else {
        *puVar2 = 1;
        FUN_000272cc(param_1);
        *puVar2 = 0;
        if (4 < *(int *)(puVar2 + 0x54)) {
          *(undefined4 *)(puVar2 + 0x54) = 0;
        }
      }
      goto switchD_00027fb2_default;
    }
LAB_00027fe4:
    if (bVar7 && !bVar6) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00032e8c(param_1);
    break;
  case 3:
    FUN_00030b24(param_1,0);
    if (*(uint *)(puVar2 + 4) < (uint)param_1[5]) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00030a2c(param_1);
    break;
  case 4:
    if (uVar3 < 5) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00033578(param_1);
    break;
  case 5:
    FUN_00030fa0(&uStack_18,param_1);
    if (*(uint *)(puVar2 + 4) < (uint)param_1[7]) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00030e48(param_1);
    break;
  case 6:
    if (uVar3 < param_1[8]) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_00032dac(param_1);
    break;
  case 7:
    if (uVar3 < param_1[9]) goto switchD_00027fb2_default;
    *(undefined4 *)(puVar2 + 4) = 0;
    *puVar2 = 1;
    FUN_000301c8(param_1);
    break;
  default:
    goto switchD_00027fb2_default;
  }
LAB_00028274:
  *puVar2 = 0;
switchD_00027fb2_default:
  FUN_000298c4(0);
  FUN_00032ce8(DAT_00028298,0,uStack_18,uStack_14);
  return;
}

