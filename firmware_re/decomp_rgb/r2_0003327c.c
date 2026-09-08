// FUN_0003327c @0003327c size=92

void FUN_0003327c(void)

{
  char *pcVar1;
  int iVar2;
  
  FUN_00037cc8();
  FUN_0002fb70();
  FUN_00032ed0();
  pcVar1 = DAT_00037dd4;
  if ((*(int *)(DAT_00037dd0 + 0x60) == 0) || (5 < (byte)DAT_00037dd4[4])) {
    if (*(int *)(DAT_00037dd4 + 0x30) != 0) {
      disableIRQinterrupts();
      if (*DAT_00037dd4 == '\0') {
        *DAT_00037dd4 = '\x01';
        FUN_0002ce7c(*DAT_00037dd8);
        FUN_000432e8(0xfd);
      }
      else {
        iVar2 = *(int *)(DAT_00037dd4 + 0x30) + -10;
        *(int *)(DAT_00037dd4 + 0x30) = iVar2;
        if (iVar2 == 0) {
          *pcVar1 = '\0';
        }
      }
      enableIRQinterrupts();
      return;
    }
  }
  else {
    pcVar1[0x30] = '\0';
    pcVar1[0x31] = '\0';
    pcVar1[0x32] = '\0';
    pcVar1[0x33] = '\0';
    *pcVar1 = '\0';
  }
  return;
}

