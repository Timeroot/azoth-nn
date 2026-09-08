// FUN_00032af4 @00032af4 size=76

void FUN_00032af4(int param_1)

{
  ushort uVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined1 *puVar4;
  
  puVar4 = *(undefined1 **)(DAT_00032b40 + 0x68);
  *puVar4 = 0;
  puVar4[1] = 1;
  bVar3 = (byte)(((ulonglong)*(byte *)(param_1 + 1) << 7) / 100);
  puVar4[0x23] = bVar3;
  uVar1 = (ushort)bVar3;
  puVar4[0x93] = (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 5) * (int)(short)uVar1) >> 7)
  ;
  puVar4[0x94] = (char)((uint)((int)(short)(ushort)*(byte *)(param_1 + 6) * (int)(short)uVar1) >> 7)
  ;
  uVar2 = (undefined1)((uint)((int)(short)(ushort)*(byte *)(param_1 + 7) * (int)(short)uVar1) >> 7);
  puVar4[0x95] = uVar2;
  *(undefined2 *)(puVar4 + 0x88) = *(undefined2 *)(puVar4 + 0x93);
  puVar4[0x8a] = uVar2;
  return;
}

