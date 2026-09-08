// @0xd430 size=22

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000d430(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 1 << (param_1 & 0xff);
  if (param_2 != 0) {
    _DAT_5000050c = iVar1;
    return;
  }
  _DAT_50000508 = iVar1;
  return;
}

