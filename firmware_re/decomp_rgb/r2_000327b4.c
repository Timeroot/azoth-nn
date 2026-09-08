// FUN_000327b4 @000327b4 size=126

void FUN_000327b4(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  puVar3 = *(undefined1 **)(DAT_00032834 + 0x68);
  *puVar3 = 3;
  puVar3[1] = 6;
  puVar3[0x12] = *(byte *)(param_1 + 0x76) & 0xf;
  puVar3[0x7f] = *(byte *)(param_1 + 0x76) >> 4;
  puVar3[0x28] = (char)(((ulonglong)*(byte *)(param_1 + 0x75) << 7) / 100);
  puVar3[5] = *(undefined1 *)(param_1 + 0x74);
  puVar3[0x3e] = 0;
  bVar1 = *(byte *)(param_1 + 0x76);
  if ((bVar1 & 0xf) != 1) {
    iVar4 = *(int *)(DAT_00032834 + 0x68);
    *(undefined2 *)(puVar3 + 0xa2) = *(undefined2 *)(param_1 + 0x79);
    puVar3[0xa4] = *(undefined1 *)(param_1 + 0x7b);
    if (bVar1 >> 4 == 0) {
      *(undefined2 *)(iVar4 + 0xc3) = *(undefined2 *)(param_1 + 0x79);
      uVar2 = *(undefined1 *)(param_1 + 0x7b);
    }
    else {
      *(undefined2 *)(iVar4 + 0xc3) = *(undefined2 *)(param_1 + 0x7c);
      uVar2 = *(undefined1 *)(param_1 + 0x7e);
    }
    *(undefined1 *)(iVar4 + 0xc5) = uVar2;
  }
  FUN_0001c5e0(DAT_00032838,0x12);
  return;
}

