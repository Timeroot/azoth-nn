// @0x305be  size=48

undefined4 FUN_000305be(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
  }
  uVar1 = FUN_00044cd8(param_1,param_2 + -4);
  *(undefined2 *)(param_1 + 0x2c) = uVar1;
  FUN_0002cc20(&DAT_000d5000);
  FUN_0002cc3c(&DAT_000d5000,param_1,param_2);
  return 1;
}

