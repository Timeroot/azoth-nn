// FUN_00028d6c @00028d6c size=94

void FUN_00028d6c(void)

{
  int iVar1;
  uint uVar2;
  
  if ((*(uint *)(DAT_00028dcc + 0x30) & -(uint)*DAT_00028dd0) != 0) {
    FUN_00031320(1);
    FUN_000396c8(100);
    FUN_000395b0(1);
    uVar2 = 0;
    do {
      iVar1 = FUN_00028ea8(uVar2);
      if ((iVar1 != 0) && (iVar1 = FUN_0003979c(), iVar1 == 0)) {
        FUN_00028efa(uVar2);
      }
      uVar2 = uVar2 + 0x1000;
    } while (uVar2 < 0x380000);
    iVar1 = FUN_00029fd4();
    if (iVar1 == 0) {
      FUN_00039540(1);
      FUN_00031320(0);
      return;
    }
  }
  return;
}

