// FUN_00030b24 @00030b24 size=302

void FUN_00030b24(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  
  iVar2 = DAT_00030c54;
  iVar7 = 0;
  iVar11 = param_1;
  do {
    if (*(char *)(iVar2 + iVar7) != '\0') {
      uVar9 = 0;
      do {
        if (((uint)*(byte *)(iVar2 + iVar7) & 1 << (uVar9 & 0xff)) != 0) {
          iVar5 = uVar9 + iVar7 * 8;
          uVar8 = (uint)*(byte *)(DAT_00030c58 + iVar5 * 2);
          uVar10 = (uint)*(byte *)(DAT_00030c58 + iVar5 * 2 + 1);
          iVar5 = FUN_0002b5e0(param_1,*(undefined4 *)(DAT_00030c5c + 0x6c),3,uVar8,uVar10,iVar11);
          if (iVar5 != 0) {
            return;
          }
          iVar5 = param_1 + uVar8 * 0x58 + uVar10 * 4;
          if ((*(char *)(iVar5 + 0x4ba) == '\0' && *(char *)(iVar5 + 0x4bb) == '\0') &&
              *(char *)(iVar5 + 0x4bc) == '\0') {
            if (*(char *)(param_1 + 0x12) == '\0') {
              iVar3 = (uint)*(byte *)(param_1 + 0xd8) * 0x21 + param_1;
              *(undefined2 *)(iVar5 + 0x4ba) = *(undefined2 *)(iVar3 + 0xa2);
              *(undefined1 *)(iVar5 + 0x4bc) = *(undefined1 *)(iVar3 + 0xa4);
              goto LAB_00030c48;
            }
LAB_00030bf8:
            uVar4 = FUN_000292a4();
            *(short *)(iVar5 + 0x4ba) = (short)uVar4;
            *(char *)(iVar5 + 0x4bc) = (char)((uint)uVar4 >> 0x10);
          }
          else if ((1 < *(byte *)(iVar5 + 0x4bd)) || (param_2 != 0)) {
            if (*(char *)(param_1 + 0x12) != '\0') goto LAB_00030bf8;
            iVar3 = (uint)*(byte *)(param_1 + 0xd8) * 0x21 + param_1;
            uVar1 = *(undefined2 *)(iVar3 + 0xa2);
            *(undefined2 *)(iVar5 + 0x4ba) = uVar1;
            *(undefined1 *)(iVar5 + 0x4bc) = *(undefined1 *)(iVar3 + 0xa4);
            puVar6 = (undefined2 *)(*(int *)(param_1 + 0xe0) + uVar10 * 3 + uVar8 * 0x30);
            *puVar6 = uVar1;
            *(undefined1 *)(puVar6 + 1) = *(undefined1 *)(iVar5 + 0x4bc);
LAB_00030c48:
            *(bool *)(param_1 + 0xd8) = *(char *)(param_1 + 0xd8) == '\0';
          }
          *(undefined1 *)(iVar5 + 0x4bd) = 0;
        }
        uVar9 = uVar9 + 1;
      } while ((int)uVar9 < 8);
      *(undefined1 *)(iVar2 + iVar7) = 0;
    }
    iVar7 = iVar7 + 1;
    if (0x11 < iVar7) {
      return;
    }
  } while( true );
}

