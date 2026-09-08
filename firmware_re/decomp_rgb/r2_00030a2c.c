// FUN_00030a2c @00030a2c size=144

void FUN_00030a2c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined1 uVar7;
  
  iVar1 = DAT_00030abc;
  uVar6 = 0;
  do {
    uVar5 = 0;
    do {
      iVar2 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar1 + 0x6c),3,uVar6 & 0xff,uVar5 & 0xff);
      if (iVar2 == 0) {
        iVar2 = param_1 + uVar6 * 0x58 + uVar5 * 4;
        if ((*(char *)(iVar2 + 0x4ba) == '\0' && *(char *)(iVar2 + 0x4bb) == '\0') &&
            *(char *)(iVar2 + 0x4bc) == '\0') {
          puVar4 = (undefined2 *)(uVar5 * 3 + uVar6 * 0x30 + *(int *)(param_1 + 0xe0));
          uVar7 = 0;
          *puVar4 = 0;
        }
        else {
          uVar3 = FUN_00027c50(iVar2 + 0x4ba,*(undefined1 *)(param_1 + 0x28));
          puVar4 = (undefined2 *)(uVar5 * 3 + uVar6 * 0x30 + *(int *)(param_1 + 0xe0));
          *puVar4 = (short)uVar3;
          uVar7 = (undefined1)((uint)uVar3 >> 0x10);
        }
        *(undefined1 *)(puVar4 + 1) = uVar7;
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 0x10);
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 6);
  return;
}

