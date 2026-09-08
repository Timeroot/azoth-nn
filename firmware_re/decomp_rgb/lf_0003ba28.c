// FUN_0003ba28 @0003ba28 size=88

void FUN_0003ba28(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  pcVar3 = DAT_0003ba84;
  iVar5 = *(int *)(DAT_0003ba84 + 4);
  iVar6 = (int)*(char *)(DAT_0003ba80 + iVar5) + *(int *)(DAT_0003ba84 + 8);
  uVar4 = iVar6 / 0x1e;
  cVar1 = (char)uVar4;
  *DAT_0003ba84 = cVar1;
  *(uint *)(pcVar3 + 8) = iVar6 + (uVar4 & 0xff) * -0x1e;
  iVar6 = (int)*(char *)(DAT_0003ba88 + iVar5) + *(int *)(pcVar3 + 0xc);
  uVar4 = iVar6 / 0x1e;
  cVar2 = (char)uVar4;
  pcVar3[1] = cVar2;
  *(uint *)(pcVar3 + 0xc) = iVar6 + (uVar4 & 0xff) * -0x1e;
  *(int *)(pcVar3 + 4) = iVar5 + 1;
  if (999 < iVar5 + 1) {
    pcVar3[4] = '\0';
    pcVar3[5] = '\0';
    pcVar3[6] = '\0';
    pcVar3[7] = '\0';
  }
  *param_1 = *param_1 + cVar1;
  *param_2 = *param_2 + cVar2;
  return;
}

