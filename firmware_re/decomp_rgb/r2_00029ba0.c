// FUN_00029ba0 @00029ba0 size=36

void FUN_00029ba0(void)

{
  undefined1 *puVar1;
  
  puVar1 = DAT_00029bc4;
  *(undefined1 **)(DAT_00029bc8 + 0x68) = DAT_00029bc4;
  *(undefined1 **)(puVar1 + 0xe0) = puVar1 + -0x360;
  *puVar1 = 0xff;
  *(undefined4 *)(puVar1 + 0x43) = 0;
  *(undefined4 *)(puVar1 + 0x47) = 0;
  *(undefined2 *)(puVar1 + 0x4b) = 0;
  puVar1[0x4d] = 0;
  FUN_000271c0();
  return;
}

