// FUN_0003263c @0003263c size=164

void FUN_0003263c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined1 uVar6;
  int iVar7;
  undefined2 local_18;
  undefined1 uStack_16;
  
  iVar4 = DAT_000326e0;
  puVar3 = *(undefined1 **)(DAT_000326e0 + 0x68);
  *puVar3 = 7;
  puVar3[1] = 8;
  puVar3[0x1f] = *(undefined1 *)(param_1 + 0x93);
  puVar3[0x2a] = (char)(((ulonglong)*(byte *)(param_1 + 0x91) << 7) / 100);
  puVar3[0x14] = *(byte *)(param_1 + 0x92) & 0xf;
  puVar3[9] = *(undefined1 *)(param_1 + 0x90);
  puVar3[0x40] = 0;
  if ((*(byte *)(param_1 + 0x92) & 0xf) == 1) {
    iVar7 = 0;
    do {
      uVar1 = FUN_000292a4();
      local_18 = (undefined2)uVar1;
      iVar2 = *(int *)(iVar4 + 0x68) + iVar7 * 4;
      iVar7 = iVar7 + 1;
      *(undefined2 *)(iVar2 + 0x4e) = local_18;
      uStack_16 = (undefined1)((uint)uVar1 >> 0x10);
      *(undefined1 *)(iVar2 + 0x50) = uStack_16;
      *(undefined1 *)(iVar2 + 0x51) = 0;
    } while (iVar7 < 6);
    return;
  }
  iVar4 = 0;
  do {
    iVar7 = iVar4 * 3 + param_1;
    puVar5 = (undefined2 *)(puVar3 + iVar4 * 4 + 0x4e);
    *puVar5 = *(undefined2 *)(iVar7 + 0x95);
    uVar6 = *(undefined1 *)(iVar7 + 0x97);
    while( true ) {
      *(undefined1 *)(puVar5 + 1) = uVar6;
      iVar4 = iVar4 + 1;
      *(undefined1 *)((int)puVar5 + 3) = 0;
      if (5 < iVar4) {
        return;
      }
      if (iVar4 < 6) break;
      puVar5 = (undefined2 *)(puVar3 + iVar4 * 4 + 0x4e);
      *puVar5 = *(undefined2 *)(param_1 + 0xa4);
      uVar6 = *(undefined1 *)(param_1 + 0xa6);
    }
  } while( true );
}

