// FUN_000285ec @000285ec size=154

void FUN_000285ec(int param_1,undefined4 param_2)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = DAT_0002868c;
  if ((*(int *)(DAT_00028688 + 0x30) == 0) || (*(short *)(DAT_0002868c + param_1 * 2 + 2) == 0)) {
    if (param_1 != 1) {
      FUN_0001c5d2(param_2,*(undefined2 *)(DAT_0002868c + param_1 * 2 + 8),0xff);
      return;
    }
    FUN_0001c5e0(param_2,*(undefined2 *)(DAT_0002868c + 10));
    return;
  }
  FUN_00031320(1);
  FUN_000396c8(100);
  FUN_000395b0(1);
  if (*pcVar1 == '\x01') {
    iVar2 = 0;
  }
  else {
    iVar2 = 0x1000;
  }
  FUN_00039584((*(ushort *)(pcVar1 + param_1 * 2 + 2) - 1) *
               (uint)*(ushort *)(pcVar1 + param_1 * 2 + 8) +
               (uint)*(ushort *)(DAT_00028690 + param_1 * 2) + iVar2,param_2);
  FUN_0001c590(*(undefined4 *)(DAT_00028694 + param_1 * 4),param_2,
               *(undefined2 *)(pcVar1 + param_1 * 2 + 8));
  iVar2 = FUN_00029fd4();
  if (iVar2 == 0) {
    FUN_00039540(1);
    FUN_00031320(0);
    return;
  }
  return;
}

