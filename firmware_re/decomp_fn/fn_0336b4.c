// @0x336b4 size=256

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000336b4(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 unaff_r4;
  uint uVar5;
  undefined4 unaff_lr;
  
  iVar1 = DAT_000337b4;
  if (param_3 != 0) {
    uVar5 = (*(ushort *)(DAT_000337b4 + 0xc) & 0x1ff) >> 6;
    if (-1 < (int)(uVar5 << 0x1e)) {
      FUN_0001c5e0(DAT_000337b4 + 0x68,0x15);
    }
    if ((int)(uVar5 << 0x1d) < 0) {
      return;
    }
    FUN_0001c5e0(DAT_000337b4 + 0x7d,0x15);
    return;
  }
  if (param_1 != 0) {
    FUN_0001c5e0(DAT_000337b4 + 0x53,0x15);
    iVar1 = DAT_000337b4;
    iVar4 = DAT_000337b4 + 0x53;
    pbVar3 = (byte *)(iVar4 + (uint)(*(byte *)(DAT_000337b8 + param_1) >> 3));
    uVar5 = *(byte *)(DAT_000337b8 + param_1) & 7;
    *pbVar3 = *pbVar3 | (byte)(1 << uVar5);
    *(undefined1 *)(iVar1 + 0x54) = 0x70;
    iVar1 = _DAT_00029cec;
    FUN_0001c590(*(int *)(_DAT_00029cec + 0x14) * 0x15 + _DAT_00029cf0,iVar4,0x15,uVar5,unaff_r4,
                 unaff_lr);
    iVar4 = *(int *)(iVar1 + 0x14) - *(int *)(iVar1 + 0x18);
    if (((iVar4 != -1) && (iVar4 < 2)) &&
       (iVar4 = *(int *)(iVar1 + 0x14) + 1, *(int *)(iVar1 + 0x14) = iVar4, 2 < iVar4)) {
      *(undefined4 *)(iVar1 + 0x14) = 0;
    }
    return;
  }
  uVar5 = *(uint *)(DAT_000337b4 + 8);
  if (0x7b < param_2 - 4) {
    if (param_2 - 0xe0 < 8 || param_2 == 0xe8) {
      param_2 = param_2 - 0x70;
    }
    else if (param_2 - 0xf0 < 7) {
      param_2 = param_2 - 0x77;
    }
    else if (param_2 - 0x87 < 5) {
      param_2 = param_2 - 0x1f;
    }
    else if (param_2 - 0x90 < 2) {
      param_2 = param_2 - 0x23;
    }
    else {
      uVar2 = param_2 - 0xd4;
      if (uVar2 < 3) {
        if (2 < uVar2) {
          return;
        }
        pbVar3 = (byte *)(DAT_000337b4 + (uint)(*(byte *)(DAT_000337bc + uVar2) >> 3) + 0x7b);
        *pbVar3 = *pbVar3 | (byte)(1 << (*(byte *)(DAT_000337bc + uVar2) & 7));
        uVar5 = uVar5 | 0x100;
        goto LAB_0003378c;
      }
    }
  }
  if (0x7f < param_2) {
    return;
  }
  pbVar3 = (byte *)(DAT_000337b4 + (uint)(*(byte *)(DAT_000337c0 + param_2) >> 3) + 0x66);
  *pbVar3 = *pbVar3 | (byte)(1 << (*(byte *)(DAT_000337c0 + param_2) & 7));
  uVar5 = uVar5 | 0x80;
LAB_0003378c:
  *(uint *)(iVar1 + 8) = uVar5;
  return;
}

