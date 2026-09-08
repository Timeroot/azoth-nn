// @0x37d0c  size=82

undefined4 FUN_00037d0c(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  piVar4 = &DAT_000db000;
  iVar5 = 0;
  if ((((DAT_000db000 == 0) || (DAT_000db000 == -1)) || (DAT_000db000 == -2)) ||
     (DAT_000db000 == -3)) {
    pcVar2 = s_Header_is_zero_00037d6c;
  }
  else {
    iVar1 = 0;
    do {
      iVar3 = *piVar4;
      piVar4 = piVar4 + 1;
      iVar1 = iVar1 + 1;
      iVar5 = iVar5 + iVar3;
    } while (iVar1 < 0x2fff);
    FUN_000277a0(iVar5);
    FUN_000277a0(*piVar4);
    if (*piVar4 == iVar5) {
      FUN_000277cc(s__DTM_CKP_00037d7c);
      return 1;
    }
    pcVar2 = s__DTM_CKF_00037d60;
  }
  FUN_000277cc(pcVar2);
  return 0;
}

