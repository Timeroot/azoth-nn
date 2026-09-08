// FUN_00032b44 @00032b44 size=376

void FUN_00032b44(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  byte bVar8;
  undefined1 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 local_38 [3];
  undefined4 local_2c [3];
  
  iVar2 = DAT_00032cd0;
  local_2c[2] = DAT_00032ccc[2];
  local_2c[0] = *DAT_00032ccc;
  local_2c[1] = DAT_00032ccc[1];
  local_38[2] = DAT_00032ccc[5];
  local_38[0] = DAT_00032ccc[3];
  local_38[1] = DAT_00032ccc[4];
  puVar7 = *(undefined1 **)(DAT_00032cd0 + 0x68);
  iVar11 = DAT_00032cd0 + 0x78;
  *puVar7 = 4;
  puVar7[1] = 4;
  puVar7[0x26] = *(undefined1 *)(param_1 + 0x2b);
  bVar8 = *(byte *)(param_1 + 0x2c) & 0xf;
  puVar7[0x10] = bVar8;
  puVar7[6] = *(undefined1 *)(param_1 + 0x2a);
  uVar3 = 0;
  puVar7[0x3c] = 0;
  if (bVar8 == 1) {
    puVar7[0x1b] = 0;
    puVar7[0x31] = 0x15;
    iVar5 = DAT_00032cd4;
    puVar7[0x47] = 0;
    iVar10 = iVar5 + 7;
    iVar6 = 0;
    do {
      *(undefined1 *)(iVar11 + iVar6) = *(undefined1 *)(iVar5 + iVar6);
      iVar12 = iVar6 * 3 + iVar10;
      puVar7[iVar6 * 4 + 0x43b] =
           (char)((uint)((int)(short)(ushort)*(byte *)(iVar10 + iVar6 * 3) *
                        (int)(short)(ushort)*(byte *)(param_1 + 0x2b)) / 100);
      puVar7[iVar6 * 4 + 0x43c] =
           (char)((uint)((int)(short)(ushort)*(byte *)(iVar12 + 1) *
                        (int)(short)(ushort)*(byte *)(param_1 + 0x2b)) / 100);
      iVar4 = iVar6 + 1;
      puVar7[iVar6 * 4 + 0x43d] =
           (char)((uint)((int)(short)(ushort)*(byte *)(iVar12 + 2) *
                        (int)(short)(ushort)*(byte *)(param_1 + 0x2b)) / 100);
      iVar6 = iVar4;
    } while (iVar4 < 7);
    goto LAB_00032c74;
  }
  uVar1 = *(undefined1 *)(param_1 + 0x2d);
  puVar7[0x1b] = uVar1;
  uVar9 = (undefined1)local_2c[2];
  switch(uVar1) {
  case 0:
  case 1:
  case 3:
  case 4:
  case 5:
  case 7:
    if (*(byte *)(param_1 + 0x2e) < 3) {
      uVar9 = *(undefined1 *)(local_2c + *(byte *)(param_1 + 0x2e));
    }
    break;
  case 2:
  case 6:
    if (*(byte *)(param_1 + 0x2e) < 3) {
      uVar9 = *(undefined1 *)(local_38 + *(byte *)(param_1 + 0x2e));
    }
    else {
      uVar9 = (undefined1)local_38[2];
    }
    break;
  case 8:
    if (*(byte *)(param_1 + 0x2e) < 3) {
      uVar9 = *(undefined1 *)(local_2c + *(byte *)(param_1 + 0x2e));
    }
    puVar7[0x31] = uVar9;
    uVar3 = 10;
    goto LAB_00032c20;
  default:
    goto switchD_00032b98_default;
  }
  puVar7[0x31] = uVar9;
LAB_00032c20:
  puVar7[0x47] = uVar3;
switchD_00032b98_default:
  iVar5 = 0;
  do {
    iVar10 = param_1 + iVar5 * 4;
    *(undefined1 *)(iVar11 + iVar5) = *(undefined1 *)(iVar10 + 0x30);
    puVar7[iVar5 * 4 + 0x43b] =
         (char)((uint)((int)(short)(ushort)*(byte *)(iVar10 + 0x31) *
                      (int)(short)(ushort)*(byte *)(param_1 + 0x2b)) / 100);
    puVar7[iVar5 * 4 + 0x43c] =
         (char)((uint)((int)(short)(ushort)*(byte *)(iVar10 + 0x32) *
                      (int)(short)(ushort)*(byte *)(param_1 + 0x2b)) / 100);
    iVar6 = iVar5 + 1;
    puVar7[iVar5 * 4 + 0x43d] =
         (char)((uint)((int)(short)(ushort)*(byte *)(iVar10 + 0x33) *
                      (int)(short)(ushort)*(byte *)(param_1 + 0x2b)) / 100);
    iVar5 = iVar6;
  } while (iVar6 < 7);
LAB_00032c74:
  FUN_00025f40(DAT_00032cd0 + 0x78,*(undefined1 *)(*(int *)(iVar2 + 0x68) + 0x31));
  FUN_0002609c(*(undefined1 *)(*(int *)(iVar2 + 0x68) + 0x31));
  return;
}

