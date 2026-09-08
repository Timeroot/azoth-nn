// @0x27aa8  size=152

undefined4 FUN_00027aa8(undefined4 param_1,byte *param_2,uint param_3)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
    *(ushort *)(DAT_00027b48 + 0xe) = (ushort)*param_2;
    goto LAB_00027ad0;
  case 1:
    if (0x10 < param_3) {
      param_3 = 0x10;
    }
    iVar1 = DAT_00027b48 + 0x14;
    break;
  case 2:
    iVar1 = DAT_00027b48 + 0x10;
    break;
  case 3:
    iVar1 = DAT_00027b48 + 0x12;
    break;
  default:
    goto switchD_00027aae_caseD_4;
  case 5:
    iVar1 = DAT_00027b48 + 0x24;
  }
  FUN_0001c590(iVar1,param_2,param_3);
LAB_00027ad0:
  FUN_00031320(1);
  FUN_000396c8(100);
  FUN_000395b0(1);
  FUN_0003979c();
  FUN_00039650(0x10000);
  iVar1 = FUN_000396c8(400);
  if (iVar1 != 0) {
    FUN_0003974c(0x10000,DAT_00027b48 + 0xe,0x18);
    iVar1 = FUN_00029fd4();
    if (iVar1 == 0) {
      FUN_00039540(1);
      FUN_00031320(0);
    }
    return 1;
  }
  iVar1 = FUN_00029fd4();
  if (iVar1 == 0) {
    FUN_00039540(1);
    FUN_00031320(0);
  }
switchD_00027aae_caseD_4:
  return 0;
}

