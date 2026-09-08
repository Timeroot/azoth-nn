// @0x2325c  size=16

void FUN_0002325c(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    *(short *)(param_1 + iVar1 * 2) = (short)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0xf7);
  return;
}

