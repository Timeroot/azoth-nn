// FUN_000272cc @000272cc size=100

void FUN_000272cc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined2 local_1c;
  undefined1 uStack_1a;
  
  *(char *)(param_1 + 0x6a) = *(char *)(param_1 + 0x6a) + '\x01';
  uVar2 = FUN_0003b640(*(undefined4 *)(param_1 + 0x6a));
  iVar1 = DAT_00027330;
  uVar6 = 0;
  do {
    uVar5 = 0;
    do {
      iVar3 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar1 + 0x6c),2,uVar6 & 0xff,uVar5 & 0xff);
      if (iVar3 == 0) {
        puVar4 = (undefined2 *)(uVar5 * 3 + uVar6 * 0x30 + *(int *)(param_1 + 0xe0));
        local_1c = (undefined2)uVar2;
        *puVar4 = local_1c;
        uStack_1a = (undefined1)((uint)uVar2 >> 0x10);
        *(undefined1 *)(puVar4 + 1) = uStack_1a;
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 0x10);
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 6);
  return;
}

