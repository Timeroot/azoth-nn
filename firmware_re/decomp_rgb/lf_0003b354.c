// FUN_0003b354 @0003b354 size=188

void FUN_0003b354(uint param_1,int param_2)

{
  int iVar1;
  undefined1 *puVar2;
  undefined2 *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = DAT_0003b428;
  puVar2 = DAT_0003b424;
  iVar1 = DAT_0003b414;
  uVar5 = *(uint *)(DAT_0003b414 + 0xc);
  if (0x77 < uVar5) {
    return;
  }
  if ((((0x8d < param_1 - 4) && (7 < param_1 - 0xe0)) && (2 < param_1 - 0xd4)) || (param_2 == 0))
  goto LAB_0003b3b4;
  param_1 = (uint)*(ushort *)(DAT_0003b420 + param_1 * 2 + 0xca);
  if ((int)((uint)*(byte *)(DAT_0003b41c + (uint)*(byte *)(DAT_0003b418 + 6)) << 0x1a) < 0) {
    if (param_1 == 0xe3) {
      param_1 = 0xe2;
      goto LAB_0003b3b4;
    }
    if (param_1 == 0xe2) {
      param_1 = 0xe3;
      goto LAB_0003b3b4;
    }
    if (param_1 == 0xe6) {
      param_1 = 0xe7;
      goto LAB_0003b3b4;
    }
  }
  if (param_1 == 0xa0d3) {
    *DAT_0003b424 = 1;
    puVar2[1] = 1;
    *(undefined4 *)(puVar2 + 0xc) = 0;
    return;
  }
LAB_0003b3b4:
  for (uVar4 = 0; uVar4 < uVar5; uVar4 = uVar4 + 1) {
    if ((ushort)DAT_0003b428[uVar4] == param_1) {
      return;
    }
  }
  if (param_1 == 0) {
    return;
  }
  if ((*(byte *)(DAT_0003b41c + (uint)*(byte *)(DAT_0003b418 + 6)) & 3) == 0) {
    *(undefined1 *)(DAT_0003b414 + 6) = 0;
  }
  else if (param_1 - 4 < 0x8e) {
    for (uVar4 = 0; uVar4 < *(uint *)(DAT_0003b414 + 0x10); uVar4 = uVar4 + 1) {
      if ((ushort)DAT_0003b428[uVar4 + 0x78] == param_1) goto LAB_0003b3f8;
    }
    *(char *)(DAT_0003b414 + 6) = (char)param_1;
  }
LAB_0003b3f8:
  if (param_1 == *(byte *)(iVar1 + 6)) {
    puVar3[uVar5] = *puVar3;
    *puVar3 = (short)param_1;
  }
  else {
    puVar3[uVar5] = (short)param_1;
  }
  *(uint *)(iVar1 + 0xc) = uVar5 + 1;
  return;
}

