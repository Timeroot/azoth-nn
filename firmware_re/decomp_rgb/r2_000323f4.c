// FUN_000323f4 @000323f4 size=160

void FUN_000323f4(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  uint uVar5;
  undefined2 *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 local_28;
  undefined4 uStack_24;
  
  local_28 = DAT_00032494;
  uStack_24 = DAT_00032498;
  FUN_000271c0();
  iVar2 = DAT_000324a0;
  iVar1 = DAT_0003249c;
  puVar4 = *(undefined1 **)(DAT_0003249c + 0x68);
  *puVar4 = 0xf5;
  puVar4[0xde] = 0;
  *(undefined2 *)(puVar4 + 0x4b8) = 0;
  uVar5 = 0;
  do {
    uVar3 = 0;
    do {
      iVar8 = uVar3 * 3 + uVar5 * 0x30;
      puVar6 = (undefined2 *)(*(int *)(*(int *)(iVar1 + 0x68) + 0xe0) + iVar8);
      *puVar6 = *(undefined2 *)(iVar2 + -0x1f);
      *(undefined1 *)(puVar6 + 1) = *(undefined1 *)(iVar2 + -0x1d);
      uVar7 = 0;
      do {
        if ((*(byte *)(iVar2 + (uint)*(byte *)((int)&local_28 + uVar7) * 2) == uVar5) &&
           (*(byte *)(iVar2 + (uint)*(byte *)((int)&local_28 + uVar7) * 2 + 1) == uVar3)) {
          puVar6 = (undefined2 *)(*(int *)(*(int *)(iVar1 + 0x68) + 0xe0) + iVar8);
          *puVar6 = *(undefined2 *)(iVar2 + -0x28);
          *(undefined1 *)(puVar6 + 1) = *(undefined1 *)(iVar2 + -0x26);
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < 5);
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < 0x10);
    uVar5 = uVar5 + 1;
  } while ((int)uVar5 < 6);
  return;
}

