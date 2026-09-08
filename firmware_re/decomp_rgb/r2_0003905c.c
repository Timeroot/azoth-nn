// FUN_0003905c @0003905c size=110

void FUN_0003905c(void)

{
  int iVar1;
  undefined4 in_r3;
  int iVar2;
  undefined4 local_20;
  
  iVar1 = DAT_000390cc;
  iVar2 = 0;
  *(undefined4 *)(DAT_000390cc + 0x30) = 0;
  local_20 = in_r3;
  FUN_00031320(1);
  do {
    FUN_000395b0(1);
    FUN_0002cbd0(1);
    local_20 = CONCAT31(local_20._1_3_,0x9f);
    FUN_00031330(&local_20,1,(int)&local_20 + 1,3);
    if (((local_20._1_1_ == -0x11) && (local_20._2_1_ == '`')) && (local_20._3_1_ == '\x18')) {
      *(undefined4 *)(iVar1 + 0x30) = 1;
    }
    iVar2 = iVar2 + 1;
  } while ((iVar2 < 3) && (*(int *)(iVar1 + 0x30) == 0));
  FUN_00039540(1);
  FUN_00031320(0);
  return;
}

