// @0x2d6e0  size=44

void FUN_0002d6e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  uVar2 = FUN_0002cbea(param_1,&local_10);
  iVar1 = DAT_0002d70c;
  *(undefined4 *)(DAT_0002d70c + 0x14) = uVar2;
  FUN_0002cbb4(local_10,uVar2,iVar1);
  *(undefined1 *)(iVar1 + *(int *)(iVar1 + 0x14)) = 0x25;
  *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 1;
  *(undefined4 *)(iVar1 + 0x18) = 0x28;
  *(undefined4 *)(iVar1 + 0x1c) = 0x18;
  return;
}

