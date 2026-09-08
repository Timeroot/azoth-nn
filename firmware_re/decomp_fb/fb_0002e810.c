
void FUN_0002e810(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  undefined4 uVar6;
  byte bVar7;
  int iVar8;
  byte *pbVar9;
  uint uVar10;
  byte bVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  iVar1 = DAT_0002e9d0;
  if (*(short *)(DAT_0002e9d0 + 0x18) != 0) {
    *(short *)(DAT_0002e9d0 + 0x18) = *(short *)(DAT_0002e9d0 + 0x18) + -1;
  }
  iVar3 = DAT_0002e9d4;
  pbVar4 = (byte *)(DAT_0002e9d0 + 1);
  iVar8 = *(int *)(DAT_0002e9d0 + 0x24);
  switch(*(undefined4 *)(iVar1 + 0x4c)) {
  case 0:
    *(undefined4 *)(iVar1 + 0x4c) = 1;
    *(undefined4 *)(iVar1 + 0x68) = 0;
    break;
  case 1:
    if ((*(int *)(iVar1 + 0x20) != iVar8) && (*(char *)(iVar1 + 0x11) == '\0')) {
      iVar8 = 0;
      do {
        iVar2 = DAT_0002e9e0;
        if ((*pbVar4 & 0x18) == 0) {
          if (*(char *)(iVar3 + (uint)*(byte *)(DAT_0002e9e0 + 7)) == '\0') {
            FUN_0001c5e0(DAT_0002e9dc + (iVar8 + *(int *)(iVar1 + 0x68)) * 0x80 + 0xc,0x68);
          }
          else {
            iVar5 = 0;
            iVar14 = DAT_0002e9d8 + *(int *)(iVar1 + 0x24) * 0x1a00;
            iVar13 = iVar8 + *(int *)(iVar1 + 0x68);
            do {
              pbVar9 = (byte *)(iVar5 + iVar13 * 0x68 + iVar14);
              bVar11 = *pbVar9;
              uVar10 = bVar11 & 0xffffff0f |
                       ((uint)((int)(short)(ushort)(bVar11 >> 4) *
                              (int)(short)(ushort)*(byte *)(iVar3 + (uint)*(byte *)(iVar2 + 7))) >>
                        7 & 0xf) << 4;
              bVar11 = (byte)uVar10 & 0xf0 |
                       (byte)((uint)((int)(short)((ushort)uVar10 & 0xf) *
                                    (int)(short)(ushort)*(byte *)(iVar3 + (uint)*(byte *)(iVar2 + 7)
                                                                 )) >> 7) & 0xf;
              *pbVar9 = bVar11;
              iVar12 = iVar5 + iVar13 * 0x80;
              iVar5 = iVar5 + 1;
              *(byte *)(DAT_0002e9dc + iVar12 + 0xc) = bVar11;
            } while (iVar5 < 0x68);
          }
        }
        else {
          iVar2 = *(int *)(iVar1 + 0x68) + iVar8;
          FUN_0001c590(DAT_0002e9dc + iVar2 * 0x80 + 0xc,
                       DAT_0002e9d8 + *(int *)(iVar1 + 0x24) * 0x1a00 + iVar2 * 0x68,0x68);
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 8);
      iVar3 = *(int *)(iVar1 + 0x68) + 8;
      *(int *)(iVar1 + 0x68) = iVar3;
      if (0x3f < iVar3) {
        *(undefined4 *)(iVar1 + 0x4c) = 2;
      }
    }
    break;
  case 2:
    if (*(short *)(iVar1 + 0x18) != 0) {
      return;
    }
    uVar6 = 3;
    goto LAB_0002e9c0;
  case 3:
    *(undefined2 *)(iVar1 + 0x18) = *(undefined2 *)(DAT_0002e9e4 + iVar8 * 2);
    *(int *)(iVar1 + 0x24) = iVar8 + 1;
    if (9 < iVar8 + 1) {
      *(undefined4 *)(iVar1 + 0x24) = 0;
    }
    iVar3 = DAT_0002e9d0;
    bVar11 = *pbVar4;
    uVar10 = (uint)bVar11;
    if ((int)(uVar10 << 0x1b) < 0) {
      uVar10 = *(int *)(DAT_0002e9d0 + 200) + 1;
      *(uint *)(DAT_0002e9d0 + 200) = uVar10;
      if (*(uint *)(iVar3 + 0xc4) < uVar10) {
        bVar7 = bVar11 & 3;
        bVar11 = bVar11 >> 2 & 0x3b | 1;
LAB_0002e9b6:
        *pbVar4 = bVar7 & 3 | bVar11 << 2;
      }
    }
    else if (((int)(uVar10 << 0x1c) < 0) &&
            (-1 < (int)((uint)*(ushort *)(DAT_0002e9d0 + 0x1c) << 0x12))) {
      if ((-1 < (int)(uVar10 << 0x1e)) && (*(uint *)(DAT_0002e9d0 + 0xd0) < *(uint *)(iVar1 + 0x24))
         ) {
        *pbVar4 = bVar11 | 2;
      }
      if (*(int *)(iVar3 + 0xd0) + 1U < *(uint *)(iVar1 + 0x24)) {
        bVar7 = *pbVar4;
        bVar11 = bVar7 >> 2 & 0x3d;
        goto LAB_0002e9b6;
      }
    }
    *(undefined1 *)(iVar1 + 2) = 1;
    uVar6 = 4;
LAB_0002e9c0:
    *(undefined4 *)(iVar1 + 0x4c) = uVar6;
    break;
  case 4:
    if (*(ushort *)(iVar1 + 0x18) < 0x15) {
      *(undefined4 *)(iVar1 + 0x4c) = 0;
    }
  }
  return;
}

