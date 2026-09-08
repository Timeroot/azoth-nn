// FUN_00027430 @00027430 size=672

void FUN_00027430(int param_1)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined2 *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined2 local_2c;
  
  iVar2 = DAT_000276d0;
  bVar3 = *(char *)(param_1 + 0x41) + 1;
  *(byte *)(param_1 + 0x41) = bVar3;
  if (*(int *)(iVar2 + 0x24) + 0x14U <= (uint)bVar3) {
    *(undefined1 *)(param_1 + 0x41) = 0;
    uVar4 = FUN_0001c56c();
    *(uint *)(iVar2 + 0x24) = uVar4 & 0xf;
    iVar12 = param_1 + (uint)*(byte *)(param_1 + 0x4c) * 0x18;
    if ((*(char *)(iVar12 + 0xe4) == -1) && (*(char *)(iVar12 + 0xe5) == -1)) {
      uVar13 = uVar4 % 6;
      uVar9 = uVar4 >> (uVar4 & 0xf);
      uVar4 = (uVar4 ^ uVar9) & 0xf;
      uVar9 = uVar9 & 1;
      if (uVar9 == 0) {
        if (0xd < uVar4) goto LAB_00027582;
      }
      else if ((uVar9 != 0) && (uVar4 < 2)) goto LAB_00027582;
      if (uVar13 == 3) {
        if (uVar4 - 0xc < 5) goto LAB_00027582;
      }
      else {
        iVar5 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar2 + 0x6c),8,uVar13,uVar4);
        if (iVar5 != 0) goto LAB_00027582;
      }
      iVar5 = 0;
      do {
        iVar11 = param_1 + iVar5 * 0x18;
        if (*(byte *)(iVar11 + 0xe4) == uVar13) {
          uVar10 = uVar4 - *(byte *)(iVar11 + 0xe5);
          if ((int)uVar10 < 0) {
            uVar10 = -uVar10;
          }
          uVar10 = uVar10 & 0xffff;
          if (*(byte *)(iVar11 + 0xe7) == uVar9) {
            if (uVar10 < 6) goto LAB_00027582;
          }
          else if (uVar10 < 9) goto LAB_00027582;
          if (0xf < uVar10) goto LAB_00027582;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 5);
      *(char *)(iVar12 + 0xe7) = (char)uVar9;
      *(char *)(iVar12 + 0xe4) = (char)uVar13;
      *(char *)(iVar12 + 0xe5) = (char)uVar4;
      if (*(char *)(param_1 + 0x15) == '\0') {
        iVar5 = (uint)*(byte *)(param_1 + 0xdb) * 0x21 + param_1;
        *(undefined2 *)(iVar12 + 0xe8) = *(undefined2 *)(iVar5 + 0xab);
        *(undefined1 *)(iVar12 + 0xea) = *(undefined1 *)(iVar5 + 0xad);
        *(bool *)(param_1 + 0xdb) = *(char *)(param_1 + 0xdb) == '\0';
      }
      else {
        uVar6 = FUN_000292a4();
        *(short *)(iVar12 + 0xe8) = (short)uVar6;
        *(char *)(iVar12 + 0xea) = (char)((uint)uVar6 >> 0x10);
      }
      *(undefined1 *)(iVar12 + 0xef) = 0;
      *(undefined1 *)(iVar12 + 0xf3) = 0;
      *(undefined1 *)(iVar12 + 0xf7) = 0;
      *(undefined1 *)(iVar12 + 0xfb) = 0;
      bVar3 = *(char *)(param_1 + 0x4c) + 1;
      *(byte *)(param_1 + 0x4c) = bVar3;
      if (3 < bVar3) {
        *(undefined1 *)(param_1 + 0x4c) = 0;
      }
    }
  }
LAB_00027582:
  uVar4 = 0;
  do {
    iVar12 = param_1 + uVar4 * 0x18;
    if ((*(char *)(iVar12 + 0xe4) != -1) && (*(char *)(iVar12 + 0xe5) != -1)) {
      FUN_000276d8(param_1,uVar4 & 0xff);
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 5);
  bVar3 = *(byte *)(param_1 + 0x2b);
  local_2c = CONCAT11((char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x72) *
                                   (int)(short)(ushort)bVar3) >> 7),
                      (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x71) *
                                   (int)(short)(ushort)bVar3) >> 7));
  bVar1 = *(byte *)(param_1 + 0x73);
  uVar4 = 0;
  do {
    uVar9 = 0;
    do {
      iVar12 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar2 + 0x6c),8,uVar4 & 0xff,uVar9 & 0xff);
      if (iVar12 == 0) {
        puVar7 = (undefined2 *)(uVar9 * 3 + uVar4 * 0x30 + *(int *)(param_1 + 0xe0));
        *puVar7 = local_2c;
        *(char *)(puVar7 + 1) =
             (char)((uint)((int)(short)(ushort)bVar1 * (int)(short)(ushort)bVar3) >> 7);
      }
      uVar9 = uVar9 + 1;
    } while ((int)uVar9 < 0x10);
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 6);
  iVar12 = 0;
  do {
    iVar5 = param_1 + iVar12 * 0x18;
    uVar4 = (uint)*(byte *)(iVar5 + 0xe4);
    if ((uVar4 != 0xff) && (uVar9 = (uint)*(byte *)(iVar5 + 0xe5), uVar9 != 0xff)) {
      iVar11 = 0;
      do {
        iVar14 = iVar5 + iVar11 * 4;
        iVar8 = FUN_0001c604(iVar14 + 0xec,DAT_000276d4,3);
        if (iVar8 != 0) {
          if (*(char *)(iVar5 + 0xe7) == '\0') {
            uVar13 = uVar9 + iVar11;
            if ((int)uVar13 < 0x10) goto LAB_0002766a;
          }
          else {
            uVar13 = uVar9 - iVar11;
            if (-1 < (int)uVar13) {
LAB_0002766a:
              iVar8 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar2 + 0x6c),8,uVar4,uVar13 & 0xff);
              if (iVar8 == 0) {
                puVar7 = (undefined2 *)(*(int *)(param_1 + 0xe0) + uVar13 * 3 + uVar4 * 0x30);
                *puVar7 = *(undefined2 *)(iVar14 + 0xec);
                *(undefined1 *)(puVar7 + 1) = *(undefined1 *)(iVar14 + 0xee);
              }
            }
          }
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 4);
      if (*(char *)(iVar5 + 0xe6) != '\0') {
        *(undefined1 *)(iVar5 + 0xe6) = 0;
        *(undefined1 *)(iVar5 + 0xe4) = 0xff;
        *(undefined1 *)(iVar5 + 0xe5) = 0xff;
      }
    }
    iVar12 = iVar12 + 1;
    if (4 < iVar12) {
      return;
    }
  } while( true );
}

