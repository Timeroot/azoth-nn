// FUN_00032730 @00032730 size=128

void FUN_00032730(int param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  
  puVar2 = *(undefined1 **)(DAT_000327b0 + 0x68);
  *puVar2 = 9;
  puVar2[1] = 10;
  puVar2[0x2c] = (char)(((ulonglong)*(byte *)(param_1 + 0xb9) << 7) / 100);
  puVar2[0x16] = *(byte *)(param_1 + 0xba) & 0xf;
  puVar2[0x83] = *(byte *)(param_1 + 0xba) >> 4;
  puVar2[0xb] = *(undefined1 *)(param_1 + 0xb8);
  puVar2[0x42] = 0;
  bVar1 = *(byte *)(param_1 + 0xba);
  *(undefined2 *)(puVar2 + 0xae) = *(undefined2 *)(param_1 + 0xbd);
  puVar2[0xb0] = *(undefined1 *)(param_1 + 0xbf);
  if (bVar1 >> 4 == 0) {
    puVar3 = (undefined2 *)(param_1 + 0xbd);
    uVar4 = *puVar3;
  }
  else {
    puVar3 = (undefined2 *)(param_1 + 0xc0);
    uVar4 = *puVar3;
  }
  *(undefined2 *)(puVar2 + 0xcf) = uVar4;
  puVar2[0xd1] = *(undefined1 *)(puVar3 + 1);
  *(undefined2 *)(puVar2 + 0x75) = *(undefined2 *)(param_1 + 0xc3);
  puVar2[0x77] = *(undefined1 *)(param_1 + 0xc5);
  return;
}

