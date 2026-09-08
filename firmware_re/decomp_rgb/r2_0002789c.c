// FUN_0002789c @0002789c size=434

void FUN_0002789c(void)

{
  ushort uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  char cVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  
  pcVar2 = DAT_00027a60;
  iVar6 = DAT_00027a5c;
  iVar3 = DAT_00027a58;
  if (*(int *)(DAT_00027a54 + 0x30) == 0) {
    return;
  }
  uVar9 = *(undefined4 *)(DAT_00027a58 + 4);
  switch(uVar9) {
  case 0:
    if (*(uint *)(DAT_00027a58 + 0xc) != 0) {
      for (uVar10 = *(uint *)(DAT_00027a58 + 8); (int)uVar10 < 3; uVar10 = uVar10 + 1) {
        if ((1 << (uVar10 & 0xff) & *(uint *)(DAT_00027a58 + 0xc)) != 0) {
          uVar9 = 1;
          break;
        }
      }
      *(undefined4 *)(DAT_00027a58 + 4) = uVar9;
      *(uint *)(iVar3 + 8) = uVar10;
      if (2 < (int)uVar10) {
        *(undefined4 *)(iVar3 + 8) = 0;
      }
    }
    break;
  case 1:
    iVar4 = FUN_00029fd4();
    if (iVar4 != 0) {
      return;
    }
    cVar8 = *pcVar2;
    if (cVar8 != '\0') {
      iVar4 = *(int *)(iVar3 + 8);
      uVar10 = (uint)*(ushort *)(pcVar2 + iVar4 * 2 + 8);
      if (cVar8 == '\x01') {
        iVar5 = 0;
      }
      else {
        iVar5 = 0x1000;
      }
      uVar11 = *(ushort *)(pcVar2 + iVar4 * 2 + 2) * uVar10 + (uint)*(ushort *)(iVar6 + iVar4 * 2) +
               iVar5;
      if (cVar8 == '\x01') {
        iVar5 = 0;
      }
      else {
        iVar5 = 0x1000;
      }
      if ((((uint)*(ushort *)(iVar6 + iVar4 * 2 + 2) + iVar5) - uVar10) - 1 < uVar11) {
        *(undefined4 *)(iVar3 + 0xc) = 7;
        uVar9 = 3;
        goto LAB_00027a04;
      }
      if (uVar10 < 0x101) {
        FUN_0001c590(DAT_00027a64,*(undefined4 *)(DAT_00027a58 + 0x18 + iVar4 * 4));
        FUN_00028408(uVar11,DAT_00027a64,*(undefined2 *)(pcVar2 + *(int *)(iVar3 + 8) * 2 + 8));
        *(uint *)(iVar3 + 0xc) = *(uint *)(iVar3 + 0xc) & ~(1 << *(sbyte *)(iVar3 + 8));
        *(undefined4 *)(iVar3 + 4) = 2;
        return;
      }
    }
    *(undefined4 *)(iVar3 + 4) = 5;
    break;
  case 2:
    iVar6 = FUN_00029fd4();
    if (iVar6 != 0) {
      return;
    }
    *(short *)(pcVar2 + *(int *)(iVar3 + 8) * 2 + 2) =
         *(short *)(pcVar2 + *(int *)(iVar3 + 8) * 2 + 2) + 1;
    goto LAB_00027a48;
  case 3:
    iVar4 = FUN_00029fd4();
    if (iVar4 != 0) {
      return;
    }
    if (*pcVar2 == '\x01') {
      iVar4 = 0x1000;
    }
    else {
      iVar4 = 0;
    }
    iVar5 = *(int *)(iVar3 + 8);
    uVar1 = *(ushort *)(iVar6 + iVar5 * 2);
    if (*(ushort *)(pcVar2 + iVar5 * 2 + 8) < 0x101) {
      FUN_0001c590(DAT_00027a64,*(undefined4 *)(DAT_00027a58 + 0x18 + iVar5 * 4));
      FUN_00028408(iVar4 + (uint)uVar1,DAT_00027a64,
                   *(undefined2 *)(pcVar2 + *(int *)(iVar3 + 8) * 2 + 8));
      *(uint *)(iVar3 + 0xc) = *(uint *)(iVar3 + 0xc) & ~(1 << *(sbyte *)(iVar3 + 8));
    }
    iVar6 = *(int *)(iVar3 + 8) + 1;
    *(int *)(iVar3 + 8) = iVar6;
    if (iVar6 < 3) {
      return;
    }
    uVar9 = 4;
LAB_00027a04:
    *(undefined4 *)(iVar3 + 4) = uVar9;
    *(undefined4 *)(iVar3 + 8) = 0;
    break;
  case 4:
    iVar6 = FUN_00029fd4();
    puVar7 = DAT_00027a64;
    if (iVar6 != 0) {
      return;
    }
    if (*pcVar2 == '\x01') {
      uVar9 = 0;
    }
    else {
      uVar9 = 0x1000;
    }
    *DAT_00027a64 = 0;
    FUN_00028408(uVar9,puVar7,1);
    puVar7 = (undefined1 *)(DAT_00027a58 + 0x10);
    *(undefined4 *)(DAT_00027a58 + 0x14) = uVar9;
    *puVar7 = 1;
    if (*pcVar2 == '\x01') {
      cVar8 = '\x02';
    }
    else {
      cVar8 = '\x01';
    }
    *pcVar2 = cVar8;
    pcVar2[2] = '\x01';
    pcVar2[3] = '\0';
    pcVar2[4] = '\x01';
    pcVar2[5] = '\0';
    pcVar2[6] = '\x01';
    pcVar2[7] = '\0';
LAB_00027a48:
    *(undefined4 *)(iVar3 + 4) = 0;
  }
  return;
}

