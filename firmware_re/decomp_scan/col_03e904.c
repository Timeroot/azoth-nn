// @0x3e904 size=144

void FUN_0003e904(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_000417b0();
  if (iVar1 == 0) {
    iVar1 = FUN_000417c8(param_1);
    if (iVar1 != 0) {
      uVar2 = FUN_00037ac8(param_1);
      iVar1 = DAT_0003e994;
      iVar3 = DAT_0003e994 + uVar2 * 4;
      *(uint *)(iVar3 + 0x510) = *(uint *)(iVar3 + 0x510) | 1;
      FUN_0003df34(uVar2 * 4 + 0x100 & 0xffff);
      if ((param_2 != 0) && (iVar3 = FUN_00037ac8(param_1), *(int *)(DAT_0003e998 + iVar3 * 4) != 0)
         ) {
        *(int *)(iVar1 + 0x304) = 1 << (uVar2 & 0xff);
      }
    }
    return;
  }
  iVar1 = FUN_00037ac8();
  iVar1 = FUN_000421f4(iVar1 + -8);
  if (iVar1 == 3) {
    iVar1 = FUN_0003de12(param_1);
    if (iVar1 == 0) goto LAB_0003e93e;
  }
  else if (iVar1 == 1) {
LAB_0003e93e:
    uVar4 = 2;
    goto LAB_0003e934;
  }
  uVar4 = 3;
LAB_0003e934:
  FUN_0003db30(param_1,uVar4);
  return;
}

