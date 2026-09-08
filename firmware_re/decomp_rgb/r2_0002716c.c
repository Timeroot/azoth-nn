// FUN_0002716c @0002716c size=74

void FUN_0002716c(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  puVar1 = DAT_000271bc;
  iVar3 = DAT_000271b8;
  iVar2 = 0;
  iVar4 = *(int *)(DAT_000271b8 + 0x68);
  do {
    iVar5 = iVar2 * 3 + iVar4;
    *(undefined2 *)(iVar5 + 0x90) = *puVar1;
    *(undefined1 *)(iVar5 + 0x92) = *(undefined1 *)(puVar1 + 1);
    *(undefined2 *)(iVar5 + 0xb1) = *puVar1;
    iVar2 = iVar2 + 1;
    *(undefined1 *)(iVar5 + 0xb3) = *(undefined1 *)(puVar1 + 1);
  } while (iVar2 < 10);
  iVar2 = *(int *)(iVar3 + 0x68);
  iVar3 = 0;
  do {
    iVar4 = iVar2 + iVar3 * 4;
    *(undefined2 *)(iVar4 + 0x84) = *puVar1;
    iVar3 = iVar3 + 1;
    *(undefined1 *)(iVar4 + 0x86) = *(undefined1 *)(puVar1 + 1);
  } while (iVar3 < 3);
  return;
}

