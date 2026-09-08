// @0x396c8  size=58

undefined4 FUN_000396c8(short param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  char *pcVar1;
  int iVar2;
  uint local_18;
  
  pcVar1 = DAT_00039704;
  local_18 = param_4;
  while (((*pcVar1 != '\0' || (iVar2 = FUN_0003963a(&local_18), iVar2 != 0)) ||
         ((local_18 & 1) != 0))) {
    thunk_FUN_0003e8c4(1000);
    FUN_000403a4();
    param_1 = param_1 + -1;
    if (param_1 == 0) {
      return 0;
    }
  }
  return 1;
}

