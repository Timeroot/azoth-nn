// @0x2b6c4 size=162

void FUN_0002b6c4(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = DAT_0002b768;
  if (*DAT_0002b768 == '\0') {
    if (param_1 == 0) {
      return;
    }
    *DAT_0002b768 = '\x01';
    pcVar2[1] = '\0';
    FUN_0001c5e0(pcVar2 + 2,0x18,param_3,param_4,param_4);
  }
  else {
    if (param_1 != 0) goto LAB_0002b734;
    *DAT_0002b768 = '\0';
    if (pcVar2[1] != '\0') {
      pcVar2[1] = '\0';
      FUN_00031de8(0,0,0,0,0);
    }
    iVar3 = DAT_0002b76c;
    if (pcVar2[0x1a] != '\0') {
      if (pcVar2[0x1a] == '\x06') {
        FUN_0002b684(*(undefined1 *)(DAT_0002b76c + 5));
        FUN_00032550(*(undefined1 *)((uint)*(byte *)(iVar3 + 7) + DAT_0002b770));
        FUN_0002d710();
        *DAT_0002b774 = 2;
      }
      pcVar2[0x1a] = '\0';
      pcVar2[0x1e] = '\0';
      pcVar2[0x1f] = '\0';
    }
  }
  if (*pcVar2 == '\0') {
    return;
  }
LAB_0002b734:
  if ((param_2 - 0xe0U < 8) || (param_2 == 0xe8)) {
    param_2 = param_2 + -0x70;
  }
  else if (0x8d < param_2 - 4U) {
    param_2 = 0;
  }
  bVar1 = *(byte *)(DAT_0002b778 + param_2) >> 4;
  *(ushort *)(pcVar2 + (uint)bVar1 * 2 + 2) =
       *(ushort *)(pcVar2 + (uint)bVar1 * 2 + 2) |
       (ushort)(1 << (*(byte *)(DAT_0002b778 + param_2) & 0xf));
  return;
}

