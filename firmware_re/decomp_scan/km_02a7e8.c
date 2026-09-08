// @0x2a7e8 size=354

uint FUN_0002a7e8(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  ushort uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  
  iVar7 = DAT_0002a94c;
  uVar10 = 0;
  if ((*(int *)(DAT_0002a94c + 0xc) != 0) &&
     (iVar6 = *(int *)(DAT_0002a94c + 0x58) + 1, *(int *)(DAT_0002a94c + 0x58) = iVar6,
     iVar6 == 1000)) {
    *(byte *)(iVar7 + 10) = *(byte *)(iVar7 + 10) ^ 1;
    *(undefined4 *)(iVar7 + 0x58) = 0;
  }
  iVar3 = DAT_0002a954;
  iVar6 = DAT_0002a950;
  if (*(char *)(iVar7 + 10) != '\0') {
    iVar14 = DAT_0002a950 + 0xa2;
    iVar15 = DAT_0002a950 + 0xf2;
    iVar8 = DAT_0002a950 + 0x142;
    iVar11 = *(int *)(iVar7 + 0x54);
    for (iVar7 = 0; iVar9 = DAT_0002a958, iVar7 < iVar11; iVar7 = iVar7 + 1) {
      iVar9 = iVar6 + iVar7 * 8;
      sVar2 = *(short *)(iVar9 + 6);
      if (sVar2 != 0) {
        uVar12 = (uint)*(ushort *)(iVar6 + iVar7 * 8);
        if (uVar12 - 0xe0 < 8) {
          uVar12 = uVar12 - 0x70;
        }
        else if (0x8d < uVar12 - 4) {
          uVar12 = 0;
        }
        iVar16 = *(int *)(iVar14 + iVar7 * 4);
        if (iVar16 == 0) {
          iVar16 = *(int *)(iVar15 + iVar7 * 4);
          if ((iVar16 == 0) ||
             (iVar16 = iVar16 + -1, *(int *)(iVar15 + iVar7 * 4) = iVar16, iVar16 == 0)) {
            bVar1 = *(byte *)(iVar3 + uVar12);
            uVar12 = (uint)(bVar1 >> 4);
            *(ushort *)(iVar8 + uVar12 * 2) =
                 *(ushort *)(iVar8 + uVar12 * 2) | (ushort)(1 << (bVar1 & 0xf));
            *(uint *)(iVar14 + iVar7 * 4) = (uint)*(ushort *)(iVar9 + 2);
            *(uint *)(iVar15 + iVar7 * 4) = (uint)*(ushort *)(iVar9 + 4);
          }
        }
        else {
          iVar16 = iVar16 + -1;
          *(int *)(iVar14 + iVar7 * 4) = iVar16;
          if ((iVar16 == 0) &&
             (bVar1 = *(byte *)(iVar3 + uVar12), uVar12 = (uint)(bVar1 >> 4),
             *(ushort *)(iVar8 + uVar12 * 2) =
                  *(ushort *)(iVar8 + uVar12 * 2) & ~(ushort)(1 << (bVar1 & 0xf)), sVar2 != -1)) {
            *(short *)(iVar9 + 6) = sVar2 + -1;
          }
        }
      }
    }
    iVar7 = 0;
    do {
      sVar2 = *(short *)(iVar8 + iVar7 * 2);
      if (sVar2 != *(short *)(iVar9 + iVar7 * 2)) {
        *(short *)(iVar9 + iVar7 * 2) = sVar2;
        uVar10 = uVar10 | 1;
      }
      iVar3 = DAT_0002a960;
      iVar6 = DAT_0002a95c;
      if (sVar2 != 0) {
        uVar12 = 0;
        uVar13 = 1;
        do {
          if ((*(ushort *)(iVar8 + iVar7 * 2) & uVar13) != 0) {
            uVar5 = uVar12 | iVar7 << 4;
            if (uVar5 - 0xa0 < 0x14) {
              uVar4 = *(ushort *)(iVar3 + uVar5 * 2 + -0x140);
            }
            else {
              uVar4 = (ushort)*(byte *)(iVar6 + uVar5);
            }
            FUN_0003b354(uVar4,0);
            uVar10 = uVar10 | 2;
          }
          uVar13 = uVar13 << 1;
          uVar12 = uVar12 + 1;
        } while ((int)uVar12 < 0x10);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 0xc);
  }
  return uVar10;
}

