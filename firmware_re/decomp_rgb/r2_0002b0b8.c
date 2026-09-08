// FUN_0002b0b8 @0002b0b8 size=576

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0002b0b8(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  undefined4 local_30;
  
  iVar2 = DAT_0002b2f8;
  local_30 = 0;
  if (*(char *)(DAT_0002b2f8 + 8) == '\0') {
    if (*(char *)(DAT_0002b2f8 + 7) != '\0') goto LAB_0002b15e;
    if (*(int *)(DAT_0002b2f8 + 0x40) == 0) {
      _DAT_50000508 = 0xfe00;
      if (param_2 == 0) {
        *(int *)(DAT_0002b2f8 + 0x50) = *(int *)(DAT_0002b2f8 + 0x50) + 1;
      }
      iVar3 = FUN_000424f4();
      if (iVar3 == 0) {
        if (6 < *(uint *)(iVar2 + 0x50)) {
          *(undefined4 *)(iVar2 + 0x4c) = 0;
          FUN_0002b3c4();
        }
        iVar3 = *(int *)(iVar2 + 0x4c);
        if ((iVar3 != 0) && (*(undefined4 *)(DAT_0002b304 + 4) = 1, param_2 == 0)) {
          *(int *)(iVar2 + 0x4c) = iVar3 + -1;
        }
        goto LAB_0002b15e;
      }
      _DAT_5000050c = 0xfe00;
    }
    else {
      *(undefined4 *)(DAT_0002b2f8 + 0x50) = 0;
    }
  }
  else {
    *(undefined1 *)(DAT_0002b2f8 + 8) = 0;
    *(undefined4 *)(iVar2 + 0x50) = 0;
    *(undefined1 *)(iVar2 + 2) = 1;
  }
  *(undefined4 *)(iVar2 + 0x40) = 0;
  iVar3 = DAT_0002b2fc;
  uVar9 = 0;
  do {
    if (*(char *)(iVar2 + 2) == '\0') {
      if (*(int *)(DAT_0002b308 + 0xc) != 0) {
        FUN_000432a4(uVar9);
        uVar5 = 0xf;
        goto LAB_0002b172;
      }
      FUN_000432a4(uVar9);
      thunk_FUN_0003e8c4(7);
      puVar8 = DAT_0002b30c;
      *DAT_0002b30c = 0x701;
      puVar8[1] = 0x701;
      puVar8[2] = 0x701;
      puVar8[3] = 0x701;
      puVar8[4] = 0x701;
      puVar8[5] = 0x701;
      puVar8[6] = 0x701;
      puVar8[7] = 0x701;
      puVar8[8] = 0x701;
      puVar8[9] = 0x701;
      puVar8[10] = 0x701;
      puVar8[0xb] = 0x701;
      puVar8[0xc] = 0x701;
      puVar8[0xd] = 0x701;
      thunk_FUN_0003e8c4(3);
      uVar10 = FUN_000424f4();
      *puVar8 = 0x705;
      puVar8[1] = 0x705;
      puVar8[2] = 0x705;
      puVar8[3] = 0x705;
      puVar8[4] = 0x705;
      puVar8[5] = 0x705;
      puVar8[6] = 0x705;
      puVar8[7] = 0x705;
      puVar8[8] = 0x705;
      puVar8[9] = 0x705;
      puVar8[10] = 0x705;
      puVar8[0xb] = 0x705;
      puVar8[0xc] = 0x705;
      puVar8[0xd] = 0x705;
    }
    else {
      iVar4 = FUN_000424f4();
      if (iVar4 != 0) {
        *(undefined4 *)(DAT_0002b300 + 0x50c) = 0x3fff;
        uVar10 = 0;
        do {
          iVar4 = FUN_000424f4();
          if (iVar4 == 0) break;
          uVar10 = uVar10 + 1;
        } while (uVar10 < 0xff);
        *(undefined4 *)(DAT_0002b300 + 0x508) = 0x3fff;
      }
      FUN_000432a4(uVar9);
      uVar5 = 1;
LAB_0002b172:
      thunk_FUN_0003e8c4(uVar5);
      uVar10 = FUN_000424f4();
    }
    iVar4 = DAT_0002b310;
    _DAT_5000050c = 0xfe00;
    uVar6 = *(uint *)(iVar3 + uVar9 * 4);
    uVar7 = (uVar6 ^ uVar10) & ~*(uint *)(DAT_0002b310 + uVar9 * 4);
    if (uVar7 != 0) {
      *(uint *)(iVar3 + uVar9 * 4) = uVar6 & ~uVar7 | uVar7 & uVar10;
      local_30 = 1;
    }
    iVar12 = DAT_0002b310;
    uVar11 = *(uint *)(DAT_0002b310 + -0x1c + uVar9 * 4);
    *(uint *)(DAT_0002b310 + -0x1c + uVar9 * 4) = uVar10;
    uVar6 = 0;
    uVar7 = 1;
    puVar8 = (undefined4 *)(iVar12 + 0x1c + uVar9 * 0x38);
    do {
      if (((uVar11 ^ uVar10) & uVar7) == 0) {
        if ((puVar8[uVar6] != 0) &&
           (iVar12 = puVar8[uVar6] + -1, puVar8[uVar6] = iVar12, iVar12 == 0)) {
          *(uint *)(iVar4 + uVar9 * 4) = *(uint *)(iVar4 + uVar9 * 4) & ~uVar7;
        }
      }
      else {
        *(uint *)(iVar4 + uVar9 * 4) = *(uint *)(iVar4 + uVar9 * 4) | uVar7;
        if (((*(int *)(DAT_0002b308 + 0xc) == 0) && (*(int *)(DAT_0002b308 + 8) == 1)) &&
           (uVar6 == 0)) {
          *puVar8 = 0x1e;
        }
        else {
          puVar8[uVar6] = param_1;
        }
      }
      uVar7 = uVar7 << 1;
      uVar6 = uVar6 + 1;
    } while (uVar6 < 0xe);
    iVar12 = uVar9 * 4;
    iVar1 = uVar9 * 4;
    uVar9 = uVar9 + 1;
    uVar10 = *(uint *)(iVar3 + iVar12) | *(uint *)(iVar4 + iVar1) | *(uint *)(iVar2 + 0x40);
    *(uint *)(iVar2 + 0x40) = uVar10;
  } while (uVar9 < 7);
  if (uVar10 != 0) {
    *DAT_0002b314 = 0;
    *(undefined1 *)(iVar2 + 2) = 0;
  }
  if (*(int *)(iVar2 + 0x4c) != 0) {
    if (uVar10 == 0) {
      *(undefined4 *)(DAT_0002b304 + 4) = 1;
    }
    else {
      *(undefined4 *)(iVar2 + 0x4c) = 0;
    }
  }
LAB_0002b15e:
  return CONCAT44(local_30,local_30);
}

