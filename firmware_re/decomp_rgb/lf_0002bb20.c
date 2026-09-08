// FUN_0002bb20 @0002bb20 size=124

void FUN_0002bb20(uint param_1)

{
  int iVar1;
  undefined4 *puVar2;
  byte *pbVar3;
  
  puVar2 = DAT_0002bba0;
  iVar1 = DAT_0002bb9c;
  if (((*(int *)(DAT_0002bb9c + 0x30) == 1) && (*(uint *)(DAT_0002bb9c + 0x34) == param_1)) &&
     (*(char *)((int)DAT_0002bba0 + 1) == '\x03')) {
    *(undefined4 *)(DAT_0002bb9c + 0x38) = 5;
    return;
  }
  if (param_1 < 0xbd) {
    *(uint *)(DAT_0002bb9c + 0x34) = param_1;
    *(undefined4 *)(iVar1 + 0x38) = 0;
  }
  else {
    if (*DAT_0002bba4 == param_1) {
      FUN_0001c590(DAT_0002bba0,DAT_0002bba4,0x1c);
    }
    else {
      pbVar3 = DAT_0002bba8;
      if ((*DAT_0002bba8 != param_1) && (pbVar3 = DAT_0002bbac, *DAT_0002bbac != param_1)) {
        return;
      }
      *DAT_0002bba0 = *(undefined4 *)pbVar3;
      puVar2[1] = *(undefined4 *)(pbVar3 + 4);
      puVar2[2] = *(undefined4 *)(pbVar3 + 8);
    }
    *(undefined4 *)(iVar1 + 0x38) = 2;
  }
  FUN_0001c5e0(DAT_0002bb9c,0x18);
  FUN_0001c5e0(DAT_0002bb9c + 0x18,0x18);
  *(undefined4 *)(iVar1 + 0x3c) = 0;
  *(undefined4 *)(iVar1 + 0x30) = 1;
  *(undefined1 *)(iVar1 + 0x48) = 1;
  return;
}

