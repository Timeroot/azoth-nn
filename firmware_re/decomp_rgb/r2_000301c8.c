// FUN_000301c8 @000301c8 size=344

void FUN_000301c8(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  
  iVar1 = DAT_00030320;
  if (*(char *)(param_1 + 0x1f) == '\x02') {
    uVar2 = 1;
    *(undefined4 *)(DAT_00030320 + 0x20) = 0;
  }
  else {
    uVar2 = 0xffffffff;
    *(undefined4 *)(DAT_00030320 + 0x20) = 5;
  }
  *(undefined4 *)(iVar1 + 0x18) = uVar2;
  uVar7 = (uint)*(byte *)(param_1 + 0x40);
  *(char *)(param_1 + 0x40) = (char)(uVar7 + 1);
  if ((0x95 < (uVar7 + 1 & 0xff)) &&
     (*(undefined1 *)(param_1 + 0x40) = 0, *(char *)(param_1 + 0x14) == '\x01')) {
    iVar3 = 0;
    do {
      uVar2 = FUN_000292a4();
      iVar8 = param_1 + iVar3 * 4;
      *(short *)(iVar8 + 0x4e) = (short)uVar2;
      iVar3 = iVar3 + 1;
      *(char *)(iVar8 + 0x50) = (char)((uint)uVar2 >> 0x10);
    } while (iVar3 < 6);
  }
  if (uVar7 == (uVar7 / 5) * 5) {
    *(uint *)(iVar1 + 0x1c) = uVar7 / 5;
    iVar9 = *(int *)(iVar1 + 0x18);
    iVar8 = *(int *)(iVar1 + 0x20);
    iVar3 = 0;
    do {
      iVar5 = uVar7 / 5 - iVar3;
      if ((-1 < iVar5) && (iVar6 = iVar9 * iVar3 + iVar8, iVar5 < 8)) {
        iVar11 = param_1 + iVar6 * 0x58;
        iVar6 = param_1 + iVar6 * 4;
        *(undefined4 *)(iVar11 + iVar5 * 4 + 0x4da) = *(undefined4 *)(iVar6 + 0x4e);
        *(undefined4 *)(iVar11 + (7 - iVar5) * 4 + 0x4ba) = *(undefined4 *)(iVar6 + 0x4e);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 6);
  }
  iVar5 = *(int *)(iVar1 + 0x1c);
  iVar8 = *(int *)(iVar1 + 0x20);
  iVar3 = *(int *)(iVar1 + 0x18);
  iVar9 = 0;
  do {
    iVar6 = iVar5 - iVar9;
    if (-1 < iVar6) {
      uVar10 = iVar3 * iVar9 + iVar8;
      uVar7 = 0;
      do {
        iVar11 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar1 + 0x6c),7,uVar10 & 0xff,uVar7 & 0xff);
        if ((iVar11 == 0) &&
           (iVar11 = param_1 + uVar10 * 0x58 + uVar7 * 4,
           (*(char *)(iVar11 + 0x4ba) != '\0' || *(char *)(iVar11 + 0x4bb) != '\0') ||
           *(char *)(iVar11 + 0x4bc) != '\0')) {
          if (iVar6 < 8) {
            *(undefined1 *)(iVar11 + 0x4bd) = 0;
          }
          uVar2 = FUN_00027c50(iVar11 + 0x4ba,*(undefined1 *)(param_1 + 0x2a));
          puVar4 = (undefined2 *)(uVar7 * 3 + uVar10 * 0x30 + *(int *)(param_1 + 0xe0));
          *puVar4 = (short)uVar2;
          *(char *)(puVar4 + 1) = (char)((uint)uVar2 >> 0x10);
        }
        uVar7 = uVar7 + 1;
      } while ((int)uVar7 < 0x10);
    }
    iVar9 = iVar9 + 1;
  } while (iVar9 < 6);
  return;
}

