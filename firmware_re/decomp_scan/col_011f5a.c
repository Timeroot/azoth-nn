// @0x11f5a size=44

void FUN_00011f5a(uint param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  if (param_3 == 0) {
    piVar3 = DAT_00012100 + 1;
  }
  else {
    uVar1 = FUN_00011f54();
    iVar2 = DAT_000120fc + param_1 * 8;
    *(undefined4 *)(iVar2 + 0x510) = uVar1;
    *(undefined4 *)(iVar2 + 0x514) = param_2;
    piVar3 = DAT_00012100;
  }
  *piVar3 = 1 << (param_1 & 0xff);
  return;
}

