// @0x3ed5c size=138

undefined4 FUN_0003ed5c(int *param_1,ushort *param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = DAT_0003ede8;
  *(undefined4 *)(DAT_0003ede8 + (uint)*(byte *)((int)param_1 + 5) * 4) = param_3;
  iVar3 = iVar3 + -8;
  if (*(char *)(iVar3 + (uint)*(byte *)((int)param_1 + 5) * 3) != '\0') {
    return 8;
  }
  uVar2 = (uint)(char)param_1[1];
  cVar1 = (char)param_2[1] << 5;
  if ((int)uVar2 < 0) {
    *(char *)((uVar2 & 0xf) + 0xe000ed14) = cVar1;
  }
  else {
    (&DAT_e000e400)[uVar2] = cVar1;
  }
  uVar2 = (uint)(char)param_1[1];
  if (-1 < (int)uVar2) {
    *(int *)(&DAT_e000e100 + (uVar2 >> 5) * 4) = 1 << (uVar2 & 0x1f);
  }
  *(uint *)(*param_1 + 0x508) = (uint)*param_2;
  *(char *)((uint)*(byte *)((int)param_1 + 5) * 3 + iVar3 + 1) = (char)param_2[2];
  *(undefined1 *)((uint)*(byte *)((int)param_1 + 5) * 3 + iVar3 + 2) =
       *(undefined1 *)((int)param_2 + 3);
  *(undefined1 *)(iVar3 + (uint)*(byte *)((int)param_1 + 5) * 3) = 1;
  return 0;
}

