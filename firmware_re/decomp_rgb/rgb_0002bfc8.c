// FUN_0002bfc8 @0002bfc8 size=24

void FUN_0002bfc8(void)

{
  undefined1 *puVar1;
  
  puVar1 = DAT_0002bfe0;
  *DAT_0002bfe0 = 4;
  puVar1[8] = 0;
  puVar1[9] = puVar1[9] & 0xf1 | 1;
  return;
}

