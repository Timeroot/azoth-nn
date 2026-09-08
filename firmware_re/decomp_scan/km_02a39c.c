// @0x2a39c size=102

uint FUN_0002a39c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar8;
  
  FUN_00027334();
  iVar2 = DAT_0002a404;
  if (*(char *)(DAT_0002a404 + 2) == '\0') {
    uVar6 = 0;
  }
  else {
    uVar6 = 0;
    uVar5 = 0;
    do {
      iVar4 = iVar2 + uVar5 * 2;
      sVar1 = *(short *)(iVar4 + 0x1c);
      if (sVar1 != *(short *)(iVar4 + 0x34)) {
        *(short *)(iVar4 + 0x34) = sVar1;
        uVar6 = uVar6 | 1;
      }
      iVar3 = DAT_0002a408;
      if (sVar1 != 0) {
        uVar7 = 0;
        uVar8 = 1;
        do {
          if ((*(ushort *)(iVar4 + 0x1c) & uVar8) != 0) {
            FUN_0003b354(*(undefined1 *)(iVar3 + (uVar7 | uVar5 << 4)),0);
            uVar6 = uVar6 | 2;
          }
          uVar8 = uVar8 << 1;
          uVar7 = uVar7 + 1;
        } while (uVar7 < 0x10);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0xc);
  }
  return uVar6;
}

