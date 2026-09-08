// FUN_00031f1c @00031f1c size=234

void FUN_00031f1c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  FUN_0001c580(*DAT_00032008);
  puVar1 = DAT_0003200c;
  iVar2 = 0;
  iVar4 = *(int *)(DAT_0003200c + 0x68);
  do {
    iVar3 = iVar4 + iVar2;
    iVar2 = iVar2 + 1;
    *(undefined1 *)(iVar3 + 0x38) = 0;
    *(undefined1 *)(iVar3 + 0x43) = 0;
    *(undefined1 *)(iVar3 + 0xd2) = 0;
  } while (iVar2 < 0xb);
  FUN_0002716c();
  *puVar1 = 1;
  FUN_000271c0();
  *(undefined4 *)(puVar1 + 0x6c) = param_2;
  *(undefined4 *)(puVar1 + 0x70) = param_4;
  FUN_00031d44(param_3);
  FUN_00031dec(param_3);
  FUN_00032b44(param_3);
  FUN_000327b4(param_3);
  FUN_0003283c(param_3);
  FUN_00032a6c(param_3);
  FUN_0003263c(param_3);
  FUN_00031e28(param_3);
  FUN_00032730(param_3);
  uVar6 = 0;
  **(undefined1 **)(puVar1 + 0x68) = 0xf0;
  do {
    uVar5 = 0;
    do {
      iVar2 = FUN_0002b5e0(*(undefined4 *)(puVar1 + 0x68),*(undefined4 *)(puVar1 + 0x6c),0,
                           uVar6 & 0xff,uVar5 & 0xff);
      if (iVar2 == 0) {
        iVar4 = uVar6 * 0x3f + param_1;
        iVar2 = uVar5 * 3;
        *(undefined1 *)(*(int *)(*(int *)(puVar1 + 0x68) + 0xe0) + iVar2 + uVar6 * 0x30) =
             *(undefined1 *)(iVar4 + iVar2);
        iVar4 = iVar4 + iVar2;
        *(undefined1 *)(*(int *)(*(int *)(puVar1 + 0x68) + 0xe0) + uVar6 * 0x30 + iVar2 + 1) =
             *(undefined1 *)(iVar4 + 1);
        *(undefined1 *)(*(int *)(*(int *)(puVar1 + 0x68) + 0xe0) + uVar6 * 0x30 + iVar2 + 2) =
             *(undefined1 *)(iVar4 + 2);
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 0x10);
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 6);
  *puVar1 = 0;
  return;
}

