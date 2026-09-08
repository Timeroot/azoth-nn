// FUN_000323d4 @000323d4 size=26

void FUN_000323d4(void)

{
  undefined1 *puVar1;
  
  FUN_000271c0();
  puVar1 = *(undefined1 **)(DAT_000323f0 + 0x68);
  *puVar1 = 0xf4;
  puVar1[0xde] = 0;
  *(undefined2 *)(puVar1 + 0x4b8) = 0;
  return;
}

