// @0xdb660  size=332

int FUN_000db660(undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  uVar6 = param_4[1];
  iVar8 = param_4[2];
  iVar11 = 0;
  iVar10 = -1;
  do {
    iVar9 = iVar10;
    iVar10 = iVar9 + 1;
    iVar1 = (*(code *)param_4[6])(param_2);
    iVar2 = (*(code *)param_4[8])();
  } while (iVar2 != 0);
  if (iVar1 == -1) {
    return -1;
  }
  uVar7 = uVar6 & 0xfffff9ff;
  iVar2 = iVar8;
  iVar3 = iVar10;
  if (0 < iVar8) {
    if ((int)(uVar6 << 0x19) < 0) {
      if (iVar1 != 0x2b) {
        if (iVar1 != 0x2d) goto LAB_000db6c4;
        uVar7 = uVar7 | 0x400;
      }
      iVar10 = iVar9 + 2;
      iVar1 = (*(code *)param_4[6])(param_2);
      iVar8 = iVar8 + -1;
      iVar2 = iVar8;
      iVar3 = iVar10;
      if (iVar8 < 1) goto LAB_000db6ca;
    }
LAB_000db6c4:
    iVar2 = iVar8;
    iVar3 = iVar10;
    if (iVar1 == 0x30) {
      iVar2 = iVar8 + -1;
      uVar6 = uVar7 | 0x200;
      iVar3 = iVar10 + 1;
      iVar1 = (*(code *)param_4[6])(param_2);
      if ((iVar2 < 1) || ((iVar1 != 0x78 && (iVar1 != 0x58)))) {
        if (param_3 == 0) {
          param_3 = 8;
        }
      }
      else if ((param_3 == 0) || (param_3 == 0x10)) {
        iVar2 = iVar8 + -2;
        iVar3 = iVar10 + 2;
        iVar1 = (*(code *)param_4[6])(param_2);
        param_3 = 0x10;
        uVar6 = uVar7;
      }
      goto LAB_000db738;
    }
  }
LAB_000db6ca:
  uVar6 = uVar7;
  if (param_3 == 0) {
    param_3 = 10;
  }
LAB_000db738:
  while ((0 < iVar2 && (iVar10 = FUN_000db7cc(iVar1,param_3), -1 < iVar10))) {
    iVar11 = iVar11 * param_3 + iVar10;
    iVar2 = iVar2 + -1;
    iVar3 = iVar3 + 1;
    iVar1 = (*(code *)param_4[6])(param_2);
    uVar6 = uVar6 | 0x200;
  }
  (*(code *)param_4[7])(param_2);
  if ((int)(uVar6 << 0x16) < 0) {
    if ((uVar6 & 1) == 0) {
      if ((int)(uVar6 << 0x19) < 0) {
        if ((int)(uVar6 << 0x15) < 0) {
          iVar11 = -iVar11;
        }
        puVar4 = (undefined4 *)*param_4;
        *param_4 = puVar4 + 1;
        piVar5 = (int *)*puVar4;
        if ((int)(uVar6 << 0x14) < 0) {
          *(char *)piVar5 = (char)iVar11;
        }
        else if ((int)(uVar6 << 0x1c) < 0) {
          *(short *)piVar5 = (short)iVar11;
        }
        else {
          *piVar5 = iVar11;
        }
      }
      else {
        puVar4 = (undefined4 *)*param_4;
        *param_4 = puVar4 + 1;
        piVar5 = (int *)*puVar4;
        if ((int)(uVar6 << 0x14) < 0) {
          *(char *)piVar5 = (char)iVar11;
        }
        else if ((int)(uVar6 << 0x1c) < 0) {
          *(short *)piVar5 = (short)iVar11;
        }
        else {
          *piVar5 = iVar11;
        }
      }
    }
  }
  else {
    iVar3 = -2;
  }
  return iVar3;
}

