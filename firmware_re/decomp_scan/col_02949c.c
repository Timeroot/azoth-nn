// @0x2949c size=152

void FUN_0002949c(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r1;
  byte bVar2;
  uint local_20;
  undefined4 uStack_1c;
  
  bVar2 = 0;
  local_20 = param_3;
  uStack_1c = param_4;
  FUN_0003de3c();
  FUN_0003de3c(param_2);
  local_20 = 6;
  uStack_1c = 0;
  FUN_0003d8ac(param_1,1,0,0);
  local_20 = 6;
  uStack_1c = 0;
  FUN_0003d8ac(param_2,1,1,0);
  do {
    local_20 = param_1;
    iVar1 = FUN_0003dcb8(&local_20);
    if ((*(uint *)(iVar1 + 0x510) >> (local_20 & 0xff) & 1) != 0) break;
    thunk_FUN_0003e8c4(2);
    FUN_0003dbb8(param_2);
    thunk_FUN_0003e8c4(2);
    FUN_0003de3c(param_2);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 9);
  thunk_FUN_0003e8c4(2);
  FUN_0003dbb8(param_1);
  thunk_FUN_0003e8c4(2);
  FUN_0003de3c(param_1);
  FUN_0003da52(param_1);
  FUN_0003da52(param_2,extraout_r1,local_20,uStack_1c);
  return;
}

