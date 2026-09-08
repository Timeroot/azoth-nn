// FUN_00032dac @00032dac size=218

/* WARNING: Removing unreachable block (ram,0x00027b58) */
/* WARNING: Removing unreachable block (ram,0x00027b5e) */
/* WARNING: Removing unreachable block (ram,0x00027b86) */

void FUN_00032dac(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  uint uVar7;
  undefined4 unaff_r7;
  
  iVar5 = DAT_00032e88;
  bVar1 = *(byte *)(param_1 + 0x3f);
  *(byte *)(param_1 + 0x3f) = bVar1 + 1;
  if (*(uint *)(iVar5 + 0x14) <= (uint)bVar1) {
    *(undefined1 *)(param_1 + 0x3f) = 0;
    uVar4 = FUN_0001c56c();
    *(uint *)(iVar5 + 0x14) = uVar4 & 10;
    uVar7 = uVar4 % 6;
    uVar4 = (uVar4 >> (uVar4 & 10) ^ uVar4) & 0xf;
    iVar5 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar5 + 0x6c),6,uVar7,uVar4);
    if (iVar5 == 0) {
      if (*(char *)(param_1 + 0x13) == '\0') {
        iVar2 = (uint)*(byte *)(param_1 + 0xd9) * 0x21 + param_1;
        iVar5 = param_1 + uVar7 * 0x58 + uVar4 * 4;
        *(undefined2 *)(iVar5 + 0x4ba) = *(undefined2 *)(iVar2 + 0xa5);
        *(undefined1 *)(iVar5 + 0x4bc) = *(undefined1 *)(iVar2 + 0xa7);
        *(bool *)(param_1 + 0xd9) = *(char *)(param_1 + 0xd9) == '\0';
      }
      else {
        uVar6 = FUN_000292a4();
        iVar5 = param_1 + uVar7 * 0x58 + uVar4 * 4;
        *(short *)(iVar5 + 0x4ba) = (short)uVar6;
        *(char *)(iVar5 + 0x4bc) = (char)((uint)uVar6 >> 0x10);
      }
      *(undefined1 *)(param_1 + uVar7 * 0x58 + uVar4 * 4 + 0x4bd) = 0;
    }
  }
  iVar5 = DAT_00027c4c;
  uVar4 = 0;
  do {
    uVar7 = 0;
    do {
      iVar2 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar5 + 0x6c),6,uVar4 & 0xff,uVar7 & 0xff,
                           unaff_r4,unaff_r5,unaff_r6,unaff_r7);
      if (iVar2 == 0) {
        iVar2 = param_1 + uVar4 * 0x58 + uVar7 * 4;
        if ((*(char *)(iVar2 + 0x4ba) == '\0' && *(char *)(iVar2 + 0x4bb) == '\0') &&
            *(char *)(iVar2 + 0x4bc) == '\0') {
          iVar2 = uVar7 * 3;
          *(char *)(*(int *)(param_1 + 0xe0) + iVar2 + uVar4 * 0x30) =
               (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x6d) *
                            (int)(short)(ushort)*(byte *)(param_1 + 0x29)) >> 7);
          *(char *)(*(int *)(param_1 + 0xe0) + uVar4 * 0x30 + iVar2 + 1) =
               (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x6e) *
                            (int)(short)(ushort)*(byte *)(param_1 + 0x29)) >> 7);
          *(char *)(*(int *)(param_1 + 0xe0) + uVar4 * 0x30 + iVar2 + 2) =
               (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x6f) *
                            (int)(short)(ushort)*(byte *)(param_1 + 0x29)) >> 7);
        }
        else {
          uVar6 = FUN_00027c50(iVar2 + 0x4ba,*(undefined1 *)(param_1 + 0x29));
          puVar3 = (undefined2 *)(uVar7 * 3 + uVar4 * 0x30 + *(int *)(param_1 + 0xe0));
          *puVar3 = (short)uVar6;
          *(char *)(puVar3 + 1) = (char)((uint)uVar6 >> 0x10);
        }
      }
      uVar7 = uVar7 + 1;
    } while ((int)uVar7 < 0x10);
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 6);
  return;
}

