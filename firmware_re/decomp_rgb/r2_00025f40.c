// FUN_00025f40 @00025f40 size=166

void FUN_00025f40(byte *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  short sStack_36;
  short local_34 [8];
  ushort local_24 [8];
  
  if (*param_1 != 0xff) {
    local_24[0] = (ushort)*param_1;
    iVar2 = 1;
    do {
      if (param_1[iVar2] == 0xff) {
        local_24[iVar2] = 0xff;
      }
      else {
        local_24[iVar2] = (ushort)param_1[iVar2] - (ushort)param_1[iVar2 + -1];
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 7);
    uVar6 = 0;
    iVar2 = 0;
    do {
      if (local_24[iVar2] == 0xff) {
        local_34[iVar2] = 0xff;
      }
      else {
        uVar5 = (param_2 * (uint)local_24[iVar2]) / 10 & 0xffff;
        uVar4 = (uVar5 + 5) / 10;
        sVar3 = (short)uVar4;
        if ((uVar4 * 10 < uVar5) && (uVar6 = uVar5 + uVar4 * -10 + uVar6 & 0xffff, 9 < uVar6)) {
          uVar6 = 0;
          sVar3 = sVar3 + 1;
        }
        local_34[iVar2] = sVar3;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);
    local_34[iVar2] = (short)param_2 - (&sStack_36)[iVar2];
    iVar1 = *(int *)(DAT_00026010 + 0x68);
    *(undefined1 *)(iVar1 + 0x457) = (undefined1)local_34[0];
    iVar2 = 1;
    do {
      if (local_34[iVar2] == 0xff) {
        *(undefined1 *)(iVar1 + iVar2 + 0x457) = 0xff;
      }
      else {
        *(char *)(iVar1 + iVar2 + 0x457) = (char)local_34[iVar2] + *(char *)(iVar1 + iVar2 + 0x456);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 7);
  }
  return;
}

