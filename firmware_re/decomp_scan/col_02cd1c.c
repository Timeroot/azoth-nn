// @0x2cd1c size=116

void FUN_0002cd1c(int param_1,int param_2,int param_3,uint param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  iVar2 = DAT_0002cd94;
  for (uVar5 = 0; uVar5 < param_4; uVar5 = uVar5 + 1) {
    iVar6 = param_2 + uVar5;
    cVar1 = *(char *)(iVar6 + iVar2 + 0x5c);
    if (-1 < cVar1) {
      if (cVar1 < '\b') {
        iVar3 = FUN_000417c8(iVar6);
        if (iVar3 != 0) {
          uVar4 = FUN_00037ac8(iVar6);
          iVar6 = DAT_0002cd98;
          iVar3 = DAT_0002cd98 + uVar4 * 4;
          *(uint *)(iVar3 + 0x510) = *(uint *)(iVar3 + 0x510) & 0xfffffffe;
          *(int *)(iVar6 + 0x308) = 1 << (uVar4 & 0xff);
        }
      }
      else {
        iVar6 = param_1 + (param_3 + uVar5) * 4;
        *(uint *)(iVar6 + 0x700) = *(uint *)(iVar6 + 0x700) & 0xfffcffff;
        *(undefined4 *)(iVar6 + 0x700) = *(undefined4 *)(iVar6 + 0x700);
      }
    }
  }
  return;
}

