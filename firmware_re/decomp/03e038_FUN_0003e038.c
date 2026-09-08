// @0x3e038  size=64

void FUN_0003e038(void)

{
  int iVar1;
  uint in_r3;
  uint local_8;
  
  local_8 = in_r3 & 0xffffff00;
  FUN_00035410(&local_8);
  DataMemoryBarrier(0x1f);
  *(undefined4 *)(DAT_0003e078 + 0x280) = 0x40;
  FUN_00035458(local_8 & 0xff);
  iVar1 = FUN_0003e38c();
  if (iVar1 != 0) {
    software_interrupt(0x41);
    return;
  }
  WaitForEvent();
  WaitForEvent();
  return;
}

