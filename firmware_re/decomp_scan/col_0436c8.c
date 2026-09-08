// @0x436c8 size=32

void FUN_000436c8(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_000436e8;
  DAT_000436e8[1] = 1;
  *(undefined4 *)(*DAT_000436ec + 8) = 1;
  FUN_0003e8b4(0x40);
  puVar1[0x142] = 0xccd;
  *puVar1 = 1;
  return;
}

