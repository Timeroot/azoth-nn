// FUN_0002e500 @0002e500 size=16

void FUN_0002e500(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_0002e514;
  if (*(int *)(DAT_0002e510 + 0x58) != 0) {
    *DAT_0002e514 = param_1;
    puVar1[1] = param_2;
    puVar1[2] = param_3;
  }
  return;
}

