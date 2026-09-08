// FUN_0003283c @0003283c size=192

void FUN_0003283c(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = DAT_000328fc;
  puVar2 = *(undefined1 **)(DAT_000328fc + 0x68);
  *puVar2 = 5;
  puVar2[1] = 5;
  puVar2[0x11] = *(byte *)(param_1 + 0x51) & 0xf;
  puVar2[0x27] = (char)(((ulonglong)*(byte *)(param_1 + 0x50) << 7) / 100);
  puVar2[0x32] = *(undefined1 *)(param_1 + 0x53);
  puVar2[7] = *(undefined1 *)(param_1 + 0x4f);
  puVar2[0x3d] = 0;
  if ((*(byte *)(param_1 + 0x51) & 0xf) == 0) {
    iVar1 = 0;
    do {
      iVar4 = param_1 + iVar1 * 4;
      *(undefined1 *)(iVar5 + 0x78 + iVar1) = *(undefined1 *)(iVar4 + 0x55);
      puVar2[iVar1 * 4 + 0x43b] =
           (char)((uint)((int)(short)(ushort)*(byte *)(iVar4 + 0x56) *
                        (int)(short)(ushort)(byte)puVar2[0x27]) >> 7);
      puVar2[iVar1 * 4 + 0x43c] =
           (char)((uint)((int)(short)(ushort)*(byte *)(iVar4 + 0x57) *
                        (int)(short)(ushort)(byte)puVar2[0x27]) >> 7);
      iVar3 = iVar1 + 1;
      puVar2[iVar1 * 4 + 0x43d] =
           (char)((uint)((int)(short)(ushort)*(byte *)(iVar4 + 0x58) *
                        (int)(short)(ushort)(byte)puVar2[0x27]) >> 7);
      iVar1 = iVar3;
    } while (iVar3 < 7);
    FUN_00025f40(DAT_000328fc + 0x78,0x10);
  }
  iVar1 = 0;
  iVar5 = *(int *)(iVar5 + 0x68);
  do {
    iVar3 = iVar1 * 7 + iVar5;
    iVar1 = iVar1 + 1;
    *(undefined1 *)(iVar3 + 0x15c) = 0xff;
    *(undefined1 *)(iVar3 + 0x15d) = 0xff;
    *(undefined1 *)(iVar3 + 0x15e) = 0xff;
  } while (iVar1 < 0x69);
  FUN_0001c5e0(DAT_00032900,0x12);
  return;
}

