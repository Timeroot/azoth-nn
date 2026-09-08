// FUN_0002fb70 @0002fb70 size=70

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0002fb70(void)

{
  short sVar1;
  int iVar2;
  
  iVar2 = DAT_0002fbb8;
  if (*(int *)(DAT_0002fbb8 + 0x60) != 0) {
    sVar1 = *(short *)(DAT_0002fbbc + 6);
    if ((sVar1 != 0) && (*(short *)(DAT_0002fbbc + 6) = sVar1 + -1, sVar1 == 1)) {
      if ((int)(*_DAT_0002fbc0 << 0x1e) < 0) {
        FUN_000305a4();
      }
      else if ((*_DAT_0002fbc0 & 1) != 0) {
        FUN_00025a80();
      }
      *(undefined4 *)(iVar2 + 0x60) = 0;
      FUN_00032718();
      FUN_000277cc(s_Pair_Timeout_0002fbc3 + 1);
      return;
    }
  }
  return;
}

