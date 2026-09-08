// @0x388b4 size=118

undefined4 FUN_000388b4(int *param_1,ushort *param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = DAT_0003892c;
  *(undefined4 *)(DAT_0003892c + (uint)*(byte *)((int)param_1 + 5) * 4) = param_3;
  iVar3 = iVar3 + 4;
  if (*(char *)(iVar3 + (uint)*(byte *)((int)param_1 + 5) * 8 + 4) != '\0') {
    return 8;
  }
  *(uint *)(*param_1 + 0x508) = (uint)*param_2;
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
  *(undefined1 *)(iVar3 + (uint)*(byte *)((int)param_1 + 5) * 8 + 4) = 1;
  *(int **)(iVar3 + (uint)*(byte *)((int)param_1 + 5) * 8) = param_1;
  return 0;
}

