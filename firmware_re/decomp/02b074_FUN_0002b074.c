// @0x2b074  size=48

void FUN_0002b074(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar2 = DAT_0002b0a8;
  iVar1 = DAT_0002b0a4;
  iVar4 = 0;
  for (iVar3 = *(int *)(DAT_0002b0a4 + 0x54); (iVar4 < param_2 && (iVar3 < 0x14)); iVar3 = iVar3 + 1
      ) {
    puVar5 = (undefined4 *)(iVar2 + iVar3 * 8);
    puVar6 = (undefined4 *)(param_1 + iVar4 * 8);
    *puVar5 = *puVar6;
    puVar5[1] = puVar6[1];
    iVar4 = iVar4 + 1;
  }
  *(int *)(iVar1 + 0x54) = iVar3;
  return;
}

