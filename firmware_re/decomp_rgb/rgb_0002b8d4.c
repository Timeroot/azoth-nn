// FUN_0002b8d4 @0002b8d4 size=214

void FUN_0002b8d4(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  iVar4 = DAT_0002b9bc;
  iVar3 = DAT_0002b9b8;
  iVar2 = DAT_0002b9b0;
  if (*DAT_0002b9ac != '\0') {
    return;
  }
  if (9 < *(byte *)(DAT_0002b9b0 + 5)) {
    return;
  }
  if (*(int *)(DAT_0002b9b4 + 0x48) != 0) {
    return;
  }
  if (param_1 == 1) {
    iVar7 = 0x1c;
    bVar1 = *(byte *)((uint)*(byte *)(DAT_0002b9b0 + 7) + DAT_0002b9b8);
  }
  else {
    iVar7 = 0x17;
    bVar1 = *(byte *)(*(int *)(DAT_0002b9bc + (uint)*(byte *)(DAT_0002b9b0 + 5) * 4) + 1);
  }
  uVar8 = (uint)bVar1;
  if (param_3 == 1) {
    bVar6 = 100;
    if (param_2 != 0) {
      bVar6 = 0;
    }
    if (uVar8 < 0x4c) {
      bVar6 = bVar1 + 0x19;
    }
  }
  else {
    if (param_3 != 0) {
      if (uVar8 == 0) {
        uVar9 = 100;
      }
      else {
        uVar9 = 0;
      }
      goto LAB_0002b93e;
    }
    bVar6 = 0;
    if (param_2 != 0) {
      bVar6 = 100;
    }
    if (0x18 < uVar8) {
      bVar6 = bVar1 - 0x19;
    }
  }
  uVar9 = (uint)bVar6;
LAB_0002b93e:
  iVar7 = uVar9 / 0x19 + iVar7;
  if (iVar7 - 0x17U < 10) {
    FUN_0002d5cc(iVar7,1000,0);
  }
  uVar5 = DAT_0002b9c0;
  if (uVar8 == uVar9) {
    return;
  }
  if (param_1 == 1) {
    *(char *)((uint)*(byte *)(iVar2 + 7) + iVar3) = (char)uVar9;
    FUN_00032550(uVar9);
    FUN_0002bfc8();
    FUN_0003362c(0x92,0,0,uVar9);
    return;
  }
  *(char *)(*(int *)(iVar4 + (uint)*(byte *)(iVar2 + 5) * 4) + 1) = (char)uVar9;
  FUN_00032010(uVar9,uVar5);
  FUN_0002bfc8();
  FUN_000336b4(4,0);
  return;
}

