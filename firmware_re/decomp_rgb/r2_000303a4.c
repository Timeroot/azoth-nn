// FUN_000303a4 @000303a4 size=92

void FUN_000303a4(void)

{
  undefined1 *puVar1;
  
  FUN_0003d1f4();
  puVar1 = DAT_00030400;
  DAT_00030400[1] = 0;
  *puVar1 = 0x36;
  puVar1[5] = 2;
  puVar1[6] = 0x48;
  puVar1[7] = 0x4b;
  puVar1[8] = 0x50;
  puVar1[9] = 0x52;
  puVar1[10] = *(undefined1 *)(DAT_00030404 + 5);
  puVar1[0xd4] = 1;
  puVar1[0xd7] = 0;
  *(undefined2 *)(puVar1 + 0xda) = 0x1a85;
  puVar1[0xd3] = (char)*(undefined4 *)(DAT_00030408 + 8);
  FUN_0001c590(puVar1 + 0xb,puVar1 + 0xb4,0x30);
  FUN_0003d528(DAT_00030400,0);
  FUN_0003d500();
  return;
}

