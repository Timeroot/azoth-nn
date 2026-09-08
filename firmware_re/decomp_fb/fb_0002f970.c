
void FUN_0002f970(void)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  
  piVar8 = DAT_0002fb20;
  iVar10 = DAT_0002fb1c;
  iVar3 = DAT_0002fb18;
  iVar5 = *(int *)(DAT_0002fb18 + 0x44);
  if (iVar5 == 0) {
    if (*(int *)(DAT_0002fb18 + 0xec) == 0) {
      return;
    }
    *(undefined4 *)(DAT_0002fb18 + 0x44) = 1;
    *(undefined4 *)(iVar3 + 0x88) = 0;
    *(undefined4 *)(iVar3 + 0x8c) = 0;
    FUN_0002d760();
    return;
  }
  if (iVar5 == 1) {
    iVar5 = 0;
    do {
      FUN_0001c5e0(iVar10 + (*(int *)(iVar3 + 0x8c) + iVar5) * 0x80 + 0xc,0x68);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10);
    iVar10 = *(int *)(iVar3 + 0x8c) + 0x10;
    *(int *)(iVar3 + 0x8c) = iVar10;
    if (iVar10 < 0x40) {
      return;
    }
  }
  else {
    if (iVar5 == 2) {
      if (*(char *)(DAT_0002fb18 + 3) == '\0') {
        return;
      }
      iVar10 = FUN_00029fd4();
      if (iVar10 != 0) {
        return;
      }
      if ((int)(*(uint *)(iVar3 + 0xec) << 0x1e) < 0) {
        uVar6 = 800;
        iVar10 = DAT_0002fb24 + *piVar8 * 0x322;
        piVar8 = DAT_0002fb20 + 3;
LAB_0002fa7a:
        FUN_000283e0(iVar10 + 2,piVar8,uVar6);
      }
      else if ((*(uint *)(iVar3 + 0xec) & 1) != 0) {
        uVar6 = 0x60;
        iVar10 = DAT_0002fb28 + (uint)*(byte *)((int)piVar8 + *(int *)(iVar3 + 0x88) + -0x8c) * 0x62
        ;
        piVar8 = DAT_0002fb20 + -0x1b;
        goto LAB_0002fa7a;
      }
      *(undefined1 *)(iVar3 + 3) = 0;
      uVar6 = 3;
      goto LAB_0002fa86;
    }
    if (iVar5 != 3) {
      return;
    }
    iVar5 = FUN_00029fd4();
    piVar4 = DAT_0002fb20;
    if (iVar5 != 0) {
      return;
    }
    uVar13 = *(uint *)(iVar3 + 0xec);
    if ((int)(uVar13 << 0x1e) < 0) {
      iVar5 = piVar8[1];
      iVar14 = piVar8[2];
      iVar9 = 0;
      do {
        iVar7 = 0;
        do {
          pbVar11 = (byte *)((int)piVar8 + iVar7 + iVar9 * 0x14 + 0xc);
          bVar2 = *pbVar11;
          bVar2 = (bVar2 >> 5) << 4 | (byte)(((uint)bVar2 << 0x1c) >> 0x1d);
          *pbVar11 = bVar2;
          iVar12 = iVar7 + (iVar14 + iVar9) * 0x80;
          iVar7 = iVar7 + 1;
          *(byte *)(iVar12 + iVar10 + iVar5 + 0xc) = bVar2;
        } while (iVar7 < 0x14);
        iVar9 = iVar9 + 1;
      } while (iVar9 < 0x28);
      uVar1 = 0xfffffffd;
LAB_0002fafe:
      *(uint *)(iVar3 + 0xec) = uVar13 & uVar1;
    }
    else if ((uVar13 & 1) != 0) {
      iVar9 = *(int *)(iVar3 + 0x88);
      iVar5 = piVar8[-0x1d];
      iVar14 = 0;
      do {
        iVar7 = 0;
        do {
          pbVar11 = (byte *)((int)piVar4 + iVar7 + iVar14 * 6 + -0x6c);
          bVar2 = *pbVar11;
          bVar2 = (bVar2 >> 5) << 4 | (byte)(((uint)bVar2 << 0x1c) >> 0x1d);
          *pbVar11 = bVar2;
          iVar12 = iVar5 + iVar9 * 6 + (piVar8[-0x1c] + iVar14) * 0x80 + iVar7;
          iVar7 = iVar7 + 1;
          *(byte *)(iVar12 + iVar10 + 0xc) = bVar2;
        } while (iVar7 < 6);
        iVar14 = iVar14 + 1;
      } while (iVar14 < 0x10);
      iVar9 = iVar9 + 1;
      iVar10 = piVar8[-0x1e];
      *(int *)(iVar3 + 0x88) = iVar9;
      if (iVar10 == iVar9) {
        uVar1 = 0xfffffffe;
        goto LAB_0002fafe;
      }
    }
    if (*(int *)(iVar3 + 0xec) == 0) {
      *(undefined4 *)(iVar3 + 0x44) = 0;
      *(undefined1 *)(iVar3 + 2) = 1;
      return;
    }
  }
  uVar6 = 2;
LAB_0002fa86:
  *(undefined4 *)(iVar3 + 0x44) = uVar6;
  return;
}

