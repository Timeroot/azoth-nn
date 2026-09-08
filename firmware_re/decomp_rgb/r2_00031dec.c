// FUN_00031dec @00031dec size=56

void FUN_00031dec(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(DAT_00031e24 + 0x68);
  *puVar1 = 2;
  puVar1[1] = 3;
  puVar1[0x25] = *(undefined1 *)(param_1 + 0x1d);
  puVar1[4] = *(undefined1 *)(param_1 + 0x1c);
  puVar1[0x3b] = 0;
  puVar1[0x6a] = 0;
  puVar1[0x6b] = 0xff;
  puVar1[0x6c] = (char)(((uint)*(byte *)(param_1 + 0x1d) * 0xff) / 100);
  return;
}

