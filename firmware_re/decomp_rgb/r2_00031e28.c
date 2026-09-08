// FUN_00031e28 @00031e28 size=234

void FUN_00031e28(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined2 local_20;
  undefined1 uStack_1e;
  
  iVar2 = DAT_00031f14;
  puVar7 = *(undefined1 **)(DAT_00031f14 + 0x68);
  *puVar7 = 8;
  puVar7[1] = 9;
  puVar7[0x2b] = (char)(((ulonglong)*(byte *)(param_1 + 0xab) << 7) / 100);
  puVar7[0x15] = *(byte *)(param_1 + 0xac) & 0xf;
  puVar7[0x82] = *(byte *)(param_1 + 0xac) >> 4;
  puVar7[10] = *(undefined1 *)(param_1 + 0xaa);
  puVar7[0x41] = 0;
  *(undefined2 *)(puVar7 + 0x71) = *(undefined2 *)(param_1 + 0xb5);
  puVar7[0x73] = *(undefined1 *)(param_1 + 0xb7);
  bVar1 = *(byte *)(param_1 + 0xac);
  if ((bVar1 & 0xf) != 1) {
    iVar9 = *(int *)(iVar2 + 0x68);
    *(undefined2 *)(puVar7 + 0xab) = *(undefined2 *)(param_1 + 0xaf);
    puVar7[0xad] = *(undefined1 *)(param_1 + 0xb1);
    if (bVar1 >> 4 == 0) {
      *(undefined2 *)(iVar9 + 0xcc) = *(undefined2 *)(param_1 + 0xaf);
      uVar4 = *(undefined1 *)(param_1 + 0xb1);
    }
    else {
      *(undefined2 *)(iVar9 + 0xcc) = *(undefined2 *)(param_1 + 0xb2);
      uVar4 = *(undefined1 *)(param_1 + 0xb4);
    }
    *(undefined1 *)(iVar9 + 0xce) = uVar4;
  }
  puVar3 = DAT_00031f18;
  iVar9 = 0;
  do {
    iVar5 = *(int *)(iVar2 + 0x68) + iVar9 * 0x18;
    *(undefined1 *)(iVar5 + 0xe4) = 0xff;
    *(undefined1 *)(iVar5 + 0xe5) = 0xff;
    uVar6 = FUN_000292a4();
    iVar8 = *(int *)(iVar2 + 0x68);
    local_20 = (undefined2)uVar6;
    iVar5 = iVar8 + iVar9 * 0x18;
    *(undefined2 *)(iVar5 + 0xe8) = local_20;
    uStack_1e = (undefined1)((uint)uVar6 >> 0x10);
    *(undefined1 *)(iVar5 + 0xea) = uStack_1e;
    iVar5 = 0;
    do {
      iVar10 = iVar8 + iVar9 * 0x18 + iVar5 * 4;
      *(undefined2 *)(iVar10 + 0xec) = *puVar3;
      iVar5 = iVar5 + 1;
      *(undefined1 *)(iVar10 + 0xee) = *(undefined1 *)(puVar3 + 1);
    } while (iVar5 < 4);
    iVar9 = iVar9 + 1;
  } while (iVar9 < 5);
  return;
}

