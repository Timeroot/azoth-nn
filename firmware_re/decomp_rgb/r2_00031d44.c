// FUN_00031d44 @00031d44 size=160

void FUN_00031d44(int param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined2 local_10;
  undefined1 uStack_e;
  
  iVar5 = DAT_00031de4;
  puVar4 = *(undefined1 **)(DAT_00031de4 + 0x68);
  *puVar4 = 1;
  puVar4[1] = 2;
  puVar4[0xe] = *(byte *)(param_1 + 0x10) & 0xf;
  puVar4[0x24] = (char)(((ulonglong)*(byte *)(param_1 + 0xf) << 7) / 100);
  puVar4[0x7b] = *(byte *)(param_1 + 0x10) >> 4;
  puVar4[3] = *(undefined1 *)(param_1 + 0xe);
  puVar4[0x3a] = 0;
  if ((*(byte *)(param_1 + 0x10) & 0xf) == 1) {
    uVar3 = FUN_000292a4();
    iVar5 = *(int *)(iVar5 + 0x68);
    local_10 = (undefined2)uVar3;
    *(undefined2 *)(iVar5 + 0x8c) = local_10;
    uStack_e = (undefined1)((uint)uVar3 >> 0x10);
    *(undefined1 *)(iVar5 + 0x8e) = uStack_e;
    return;
  }
  iVar5 = *(int *)(iVar5 + 0x68);
  if (*(byte *)(param_1 + 0x10) >> 4 != 0) {
    uVar2 = *(undefined2 *)(param_1 + 0x13);
    *(undefined2 *)(puVar4 + 0x96) = uVar2;
    uVar1 = *(undefined1 *)(param_1 + 0x15);
    puVar4[0x98] = uVar1;
    *(undefined2 *)(iVar5 + 0xb7) = *(undefined2 *)(param_1 + 0x16);
    *(undefined1 *)(iVar5 + 0xb9) = *(undefined1 *)(param_1 + 0x18);
    *(undefined2 *)(iVar5 + 0x8c) = uVar2;
    *(undefined1 *)(iVar5 + 0x8e) = uVar1;
    return;
  }
  uVar2 = *(undefined2 *)(param_1 + 0x13);
  *(undefined2 *)(puVar4 + 0x96) = uVar2;
  uVar1 = *(undefined1 *)(param_1 + 0x15);
  puVar4[0x98] = uVar1;
  *(undefined2 *)(iVar5 + 0xb7) = *(undefined2 *)(param_1 + 0x13);
  *(undefined1 *)(iVar5 + 0xb9) = *(undefined1 *)(param_1 + 0x15);
  *(undefined2 *)(iVar5 + 0x8c) = uVar2;
  *(undefined1 *)(iVar5 + 0x8e) = uVar1;
  return;
}

