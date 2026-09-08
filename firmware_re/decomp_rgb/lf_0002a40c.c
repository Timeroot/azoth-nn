// FUN_0002a40c @0002a40c size=126

uint FUN_0002a40c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort uVar10;
  
  iVar2 = DAT_0002a48c;
  if (*(int *)(DAT_0002a48c + 0x30) == 1) {
    uVar5 = 0;
    uVar8 = 0;
    do {
      iVar7 = iVar2 + uVar8 * 2;
      sVar1 = *(short *)(iVar2 + uVar8 * 2);
      if (sVar1 != *(short *)(iVar7 + 0x18)) {
        *(short *)(iVar7 + 0x18) = sVar1;
        uVar5 = uVar5 | 1;
      }
      iVar3 = DAT_0002a494;
      iVar7 = DAT_0002a490;
      if (sVar1 != 0) {
        uVar9 = 0;
        uVar10 = 1;
        do {
          if ((*(ushort *)(iVar2 + uVar8 * 2) & uVar10) != 0) {
            uVar6 = uVar9 | uVar8 << 4;
            if (uVar6 - 0xa0 < 0x14) {
              uVar4 = *(ushort *)(iVar3 + uVar6 * 2 + -0x140);
            }
            else {
              uVar4 = (ushort)*(byte *)(iVar7 + uVar6);
            }
            FUN_0003b354(uVar4,0);
            uVar5 = uVar5 | 2;
          }
          uVar10 = uVar10 << 1;
          uVar9 = uVar9 + 1;
        } while (uVar9 < 0x10);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < 0xc);
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

