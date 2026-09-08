// @0x2994c  size=178

void FUN_0002994c(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar3 = FUN_00044d74(DAT_00029a00,0x48);
  iVar1 = DAT_00029a00;
  if (iVar3 == 0) {
    uVar5 = 0;
    do {
      *(char *)(iVar1 + uVar5 * 0x18) = (char)uVar5;
      FUN_00039ca4(uVar5 & 0xff,0);
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 3);
    if (param_1 != 0) {
      FUN_0002cd9c();
    }
  }
  pcVar2 = DAT_00029a04;
  DAT_00029a04[8] = *(char *)(iVar1 + (uint)(byte)DAT_00029a04[7] * 0x18);
  if (*pcVar2 != '\0') {
    FUN_00039cf8();
    FUN_00025c34(pcVar2[7]);
  }
  iVar3 = 0;
  do {
    iVar4 = iVar1 + (uint)(byte)pcVar2[7] * 0x18;
    if (*(char *)(iVar4 + 1) == -1) {
      if ((((*(char *)(iVar4 + 2) == -1) && (*(char *)(iVar4 + 3) == -1)) &&
          (*(char *)(iVar4 + 4) == -1)) &&
         ((*(char *)(iVar4 + 5) == -1 && (*(char *)(iVar4 + 6) == -1)))) goto LAB_000299e6;
    }
    else if ((((*(char *)(iVar4 + 1) == '\0') &&
              ((*(char *)(iVar4 + 2) == '\0' && (*(char *)(iVar4 + 3) == '\0')))) &&
             (*(char *)(iVar4 + 4) == '\0')) &&
            ((*(char *)(iVar4 + 5) == '\0' &&
             ((*(char *)(iVar4 + 6) == '\0' || (*(char *)(iVar4 + 6) == -0x40)))))) {
LAB_000299e6:
      FUN_00039ca4((uint)(byte)pcVar2[7],param_1 != 0);
    }
    iVar3 = iVar3 + 1;
    if (5 < iVar3) {
      return;
    }
  } while( true );
}

