// @0x24efc  size=118

void FUN_00024efc(undefined1 param_1,undefined1 param_2,undefined2 param_3,undefined4 param_4,
                 uint param_5)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 local_60;
  undefined1 local_5f;
  undefined2 local_5e;
  undefined1 auStack_5c [64];
  
  FUN_0001c5e0(&local_60,0x40);
  puVar2 = DAT_00024f78;
  iVar1 = DAT_00024f74;
  if (0x3c < param_5) {
    param_5 = 0x3c;
  }
  if (*(char *)(DAT_00024f74 + 2) == '\0') {
    local_60 = param_1;
    local_5f = param_2;
    local_5e = param_3;
    FUN_0001c590(auStack_5c,param_4,param_5);
    FUN_000319a0(0x82,&local_60,0x40,1);
  }
  else {
    puVar3 = DAT_00024f78 + 1;
    *DAT_00024f78 = param_1;
    *puVar3 = param_2;
    *(undefined2 *)(puVar2 + 2) = param_3;
    FUN_0001c590(puVar2 + 4,param_4,param_5);
    *(undefined4 *)(iVar1 + 0xc) = 0;
    *(uint *)(iVar1 + 0x10) = param_5 + 4;
    *(undefined1 *)(iVar1 + 1) = 1;
  }
  return;
}

