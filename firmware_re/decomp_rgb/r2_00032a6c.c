// FUN_00032a6c @00032a6c size=130

void FUN_00032a6c(int param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  undefined1 uVar3;
  
  puVar2 = *(undefined1 **)(DAT_00032af0 + 0x68);
  *puVar2 = 6;
  puVar2[1] = 7;
  puVar2[0x29] = (char)(((ulonglong)*(byte *)(param_1 + 0x83) << 7) / 100);
  puVar2[0x13] = *(byte *)(param_1 + 0x84) & 0xf;
  puVar2[0x80] = *(byte *)(param_1 + 0x84) >> 4;
  puVar2[8] = *(undefined1 *)(param_1 + 0x82);
  puVar2[0x3f] = 0;
  bVar1 = *(byte *)(param_1 + 0x84);
  *(undefined2 *)(puVar2 + 0xa5) = *(undefined2 *)(param_1 + 0x87);
  puVar2[0xa7] = *(undefined1 *)(param_1 + 0x89);
  if (bVar1 >> 4 == 0) {
    *(undefined2 *)(puVar2 + 0xc6) = *(undefined2 *)(param_1 + 0x87);
    uVar3 = *(undefined1 *)(param_1 + 0x89);
  }
  else {
    *(undefined2 *)(puVar2 + 0xc6) = *(undefined2 *)(param_1 + 0x8a);
    uVar3 = *(undefined1 *)(param_1 + 0x8c);
  }
  puVar2[200] = uVar3;
  *(undefined2 *)(puVar2 + 0x6d) = *(undefined2 *)(param_1 + 0x8d);
  puVar2[0x6f] = *(undefined1 *)(param_1 + 0x8f);
  return;
}

