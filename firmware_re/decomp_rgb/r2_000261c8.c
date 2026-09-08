// FUN_000261c8 @000261c8 size=88

void FUN_000261c8(void)

{
  undefined *puVar1;
  uint in_r3;
  uint local_10;
  
  local_10 = in_r3 & 0xffff0000;
  FUN_0002cb20(3);
  FUN_0003e8c4(200);
  FUN_0002cb54(3,&local_10);
  FUN_000277ea(local_10 & 0xffff);
  if (((local_10 & 0xffff) - 0x71c < 0x473) || (*DAT_00026220 != 0)) {
    DAT_00026220[5] = 1;
    puVar1 = &DAT_00026224;
  }
  else {
    DAT_00026220[5] = 0;
    puVar1 = &DAT_00026228;
  }
  FUN_000277cc(puVar1);
  FUN_0002cb0c(3);
  FUN_0003e8c4(10);
  return;
}

