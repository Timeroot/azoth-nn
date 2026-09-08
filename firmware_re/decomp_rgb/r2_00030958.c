// FUN_00030958 @00030958 size=462

/* WARNING: Removing unreachable block (ram,0x00027b5e) */
/* WARNING: Removing unreachable block (ram,0x00027b82) */

void FUN_00030958(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_r7;
  
  iVar2 = DAT_00030a28;
  bVar1 = *(byte *)(param_1 + 0x42);
  *(byte *)(param_1 + 0x42) = bVar1 + 1;
  if (*(int *)(iVar2 + 0x2c) + 0x18 <= (int)(uint)bVar1) {
    *(undefined1 *)(param_1 + 0x42) = 0;
    uVar4 = FUN_0001c56c();
    *(uint *)(iVar2 + 0x2c) = uVar4 & 6;
    if (6 < *(byte *)(param_1 + 0x4d)) {
      *(undefined1 *)(param_1 + 0x4d) = 0;
      if (*(uint *)(iVar2 + 0x28) != (uVar4 & 0xf)) {
        *(uint *)(iVar2 + 0x28) = uVar4 & 0xf;
        if (*(char *)(param_1 + 0x16) == '\0') {
          iVar6 = (uint)*(byte *)(param_1 + 0xdc) * 0x21 + param_1;
          *(undefined2 *)(param_1 + 0x84) = *(undefined2 *)(iVar6 + 0xae);
          *(undefined1 *)(param_1 + 0x86) = *(undefined1 *)(iVar6 + 0xb0);
          *(bool *)(param_1 + 0xdc) = *(byte *)(param_1 + 0xdc) == 0;
        }
        else {
          uVar5 = FUN_000292a4();
          *(short *)(param_1 + 0x84) = (short)uVar5;
          *(char *)(param_1 + 0x86) = (char)((uint)uVar5 >> 0x10);
        }
      }
    }
  }
  bVar1 = *(byte *)(param_1 + 0x4d);
  if (bVar1 >> 2 < 6) {
    *(byte *)(param_1 + 0x4d) = bVar1 + 1;
    iVar6 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar2 + 0x6c),9,(uint)(bVar1 >> 2),
                         *(undefined1 *)(iVar2 + 0x28));
    if (iVar6 == 0) {
      *(undefined4 *)(param_1 + (uint)(bVar1 >> 2) * 0x58 + *(int *)(iVar2 + 0x28) * 4 + 0x4ba) =
           *(undefined4 *)(param_1 + 0x84);
    }
  }
  iVar2 = DAT_00027c4c;
  uVar4 = 0;
  do {
    uVar7 = 0;
    do {
      iVar6 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar2 + 0x6c),9,uVar4 & 0xff,uVar7 & 0xff,
                           unaff_r4,unaff_r5,unaff_r6,unaff_r7);
      if (iVar6 == 0) {
        iVar6 = param_1 + uVar4 * 0x58 + uVar7 * 4;
        if ((*(char *)(iVar6 + 0x4ba) == '\0' && *(char *)(iVar6 + 0x4bb) == '\0') &&
            *(char *)(iVar6 + 0x4bc) == '\0') {
          iVar6 = uVar7 * 3;
          *(char *)(*(int *)(param_1 + 0xe0) + iVar6 + uVar4 * 0x30) =
               (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x75) *
                            (int)(short)(ushort)*(byte *)(param_1 + 0x2c)) >> 7);
          *(char *)(*(int *)(param_1 + 0xe0) + uVar4 * 0x30 + iVar6 + 1) =
               (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x76) *
                            (int)(short)(ushort)*(byte *)(param_1 + 0x2c)) >> 7);
          *(char *)(*(int *)(param_1 + 0xe0) + uVar4 * 0x30 + iVar6 + 2) =
               (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 0x77) *
                            (int)(short)(ushort)*(byte *)(param_1 + 0x2c)) >> 7);
        }
        else {
          uVar5 = FUN_00027c50(iVar6 + 0x4ba,*(undefined1 *)(param_1 + 0x2c));
          puVar3 = (undefined2 *)(uVar7 * 3 + uVar4 * 0x30 + *(int *)(param_1 + 0xe0));
          *puVar3 = (short)uVar5;
          *(char *)(puVar3 + 1) = (char)((uint)uVar5 >> 0x10);
        }
      }
      uVar7 = uVar7 + 1;
    } while ((int)uVar7 < 0x10);
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 6);
  return;
}

