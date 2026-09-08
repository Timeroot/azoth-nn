// FUN_0002622c @0002622c size=70

void FUN_0002622c(void)

{
  int iVar1;
  int in_r3;
  int local_8;
  
  if (*(int *)(DAT_00026274 + 0x30) != 0) {
    local_8 = in_r3;
    FUN_00031320(1);
    FUN_000396c8(100);
    FUN_000395b0(1);
    iVar1 = FUN_00039624(&local_8);
    if ((iVar1 == 0) && (local_8 << 0x1d < 0)) {
      *DAT_00026278 = 1;
    }
    iVar1 = FUN_00029fd4();
    if (iVar1 == 0) {
      FUN_00039540(1);
      FUN_00031320(0);
    }
  }
  return;
}

