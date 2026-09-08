
undefined4 FUN_0002cec0(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = param_1;
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  iVar1 = FUN_0002a034();
  if (iVar1 == 0) {
    if (DAT_0002cf14 == param_1) {
      *DAT_0002cf18 = 1;
    }
    else if (DAT_0002cf14 + 0x10 == param_1) {
      DAT_0002cf18[1] = 1;
    }
    if (param_2 == 0) {
      local_20 = DAT_0002cf20;
      local_18 = param_3;
    }
    else {
      local_18 = DAT_0002cf1c;
      local_20 = param_2;
    }
    iVar1 = FUN_0003f358(param_1 + 4,&local_20,0);
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

