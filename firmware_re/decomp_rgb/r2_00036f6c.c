// FUN_00036f6c @00036f6c size=242

uint FUN_00036f6c(int param_1)

{
  byte *pbVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  
  pbVar1 = DAT_00037060;
  uVar8 = 0;
  iVar4 = *(int *)(DAT_00037060 + 8);
  *(int *)(DAT_00037060 + 8) = param_1 + iVar4;
  if ((uint)(param_1 + iVar4) < 5) {
    return 0;
  }
  pbVar1[8] = 0;
  pbVar1[9] = 0;
  pbVar1[10] = 0;
  pbVar1[0xb] = 0;
  uVar7 = (uint)*pbVar1;
  if (100 < uVar7) {
    uVar7 = 100;
  }
  uVar3 = FUN_00037f50();
  iVar4 = DAT_00037064;
  *(short *)(DAT_00037060 + 2) = (short)uVar3;
  if (*(int *)(iVar4 + 0x18) == 0) {
    if (uVar7 == 0) {
      if (((*(int *)(iVar4 + 0x10) == 0) && (uVar3 < 0xd48)) &&
         (iVar5 = *(int *)(pbVar1 + 0xc), *(uint *)(pbVar1 + 0xc) = iVar5 + 1U,
         puVar2 = DAT_00037070, 5 < iVar5 + 1U)) {
        *pbVar1 = 0;
        *puVar2 = DAT_0003706c;
        FUN_0002cd9c();
      }
      goto LAB_00037040;
    }
    if (*(ushort *)(DAT_00037068 + uVar7 * 2 + 0xc6) < uVar3) {
LAB_0003703e:
      pbVar1[0xc] = 0;
      pbVar1[0xd] = 0;
      pbVar1[0xe] = 0;
      pbVar1[0xf] = 0;
      goto LAB_00037040;
    }
    iVar5 = *(int *)(pbVar1 + 0xc);
    *(uint *)(pbVar1 + 0xc) = iVar5 + 1U;
    if (iVar5 + 1U < 6) goto LAB_00037040;
    bVar6 = (char)uVar7 - 1;
    pbVar1[0xc] = 0;
    pbVar1[0xd] = 0;
    pbVar1[0xe] = 0;
    pbVar1[0xf] = 0;
  }
  else {
    if (99 < uVar7) goto LAB_00037040;
    if (0x45 < uVar7) {
      if (*(int *)(iVar4 + 0x14) == 0) {
        uVar3 = 0x3c;
      }
      else {
        uVar3 = 0x30;
      }
      iVar5 = *(int *)(pbVar1 + 0xc);
      *(uint *)(pbVar1 + 0xc) = iVar5 + 1U;
      if (uVar3 <= iVar5 + 1U) {
        uVar7 = uVar7 + 1 & 0xff;
        pbVar1[0xc] = 0;
        pbVar1[0xd] = 0;
        pbVar1[0xe] = 0;
        pbVar1[0xf] = 0;
        if (99 < uVar7) {
          uVar8 = 1;
          uVar7 = 100;
          FUN_0002d5cc(6,1000,0);
        }
      }
      goto LAB_00037040;
    }
    if (uVar3 < *(ushort *)(DAT_00037068 + uVar7 * 2)) goto LAB_0003703e;
    iVar5 = *(int *)(pbVar1 + 0xc);
    *(uint *)(pbVar1 + 0xc) = iVar5 + 1U;
    if (iVar5 + 1U < 6) goto LAB_00037040;
    bVar6 = (char)uVar7 + 1;
    pbVar1[0xc] = 0;
    pbVar1[0xd] = 0;
    pbVar1[0xe] = 0;
    pbVar1[0xf] = 0;
  }
  uVar7 = (uint)bVar6;
LAB_00037040:
  if (uVar7 != *pbVar1) {
    if (*(int *)(iVar4 + 0x44) == 0) {
      FUN_0002e274(0x10);
    }
    *pbVar1 = (byte)uVar7;
    uVar8 = uVar8 | 2;
  }
  return uVar8;
}

