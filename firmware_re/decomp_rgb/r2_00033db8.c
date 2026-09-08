// FUN_00033db8 @00033db8 size=296

int FUN_00033db8(byte param_1,byte *param_2)

{
  int iVar1;
  char *pcVar2;
  undefined2 uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  
  iVar1 = DAT_00033ee4;
  if (((*(int *)(DAT_00033ee0 + 0x60) != 0) && (*(byte *)(DAT_00033ee4 + 4) < 6)) ||
     (*DAT_00033ee8 != '\x01')) {
    return 8;
  }
  iVar4 = FUN_0003cf40();
  if (iVar4 != 0) {
    return iVar4;
  }
  pbVar7 = (byte *)(DAT_00033ee8 + -0xb4);
  DAT_00033ee8[-0xb3] = '\x02';
  if ((*param_2 & 3) == 0) {
    iVar4 = FUN_0003d224();
    pcVar2 = DAT_00033ee8;
    if (iVar4 != 0) {
      return 0;
    }
    *pbVar7 = 1;
    pbVar5 = (byte *)(pcVar2 + -0xaf);
    *(byte **)(iVar1 + 0x4c) = pbVar5;
    *pbVar5 = *pbVar5 & 4 | pcVar2[0x30] << 3;
    iVar4 = FUN_00039ebc();
    if (iVar4 == 0) {
      uVar3 = 2;
    }
    else {
      uVar3 = 0;
    }
    *(undefined2 *)(iVar1 + 0xe) = uVar3;
    FUN_0003d47c();
    iVar4 = FUN_00039ebc();
    if (iVar4 == 0) {
      pbVar5 = (byte *)0x0;
      goto LAB_00033e80;
    }
    disableIRQinterrupts();
    pbVar5 = (byte *)0x0;
  }
  else {
    *pbVar7 = param_1;
    iVar4 = FUN_00039ebc();
    if (iVar4 == 0) {
      if (*pbVar7 < 0x1a) {
        uVar3 = 2;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      uVar3 = 0;
    }
    *(undefined2 *)(iVar1 + 0xe) = uVar3;
    FUN_0003d47c();
    iVar4 = FUN_00039ebc();
    pbVar5 = param_2;
    if (iVar4 == 0) {
LAB_00033e80:
      iVar4 = FUN_0003d528(DAT_00033ee8 + -0xb4,pbVar5);
      goto LAB_00033e8a;
    }
    disableIRQinterrupts();
  }
  iVar4 = FUN_0003d528(DAT_00033ee8 + -0xb4,pbVar5);
  enableIRQinterrupts();
LAB_00033e8a:
  if (iVar4 == 0) {
    iVar6 = FUN_00039ebc();
    if (iVar6 == 0) {
      if ((*(int *)(iVar1 + 0x10) == 0) && (iVar4 = FUN_0003d350(), iVar4 != 0)) {
        iVar4 = FUN_0003d500();
        if (iVar4 == 0) {
          *(undefined4 *)(iVar1 + 0x10) = 1;
        }
      }
      else {
        iVar4 = 0x11;
      }
    }
    else if ((((*param_2 & 3) != 0) && (*(char *)(iVar1 + 2) != '\0')) &&
            ((*(int *)(iVar1 + 0x44) != 0 &&
             ((iVar6 = FUN_0003d350(), iVar6 != 0 && (iVar6 = FUN_0003b2f4(*pbVar7), iVar6 != 0)))))
            ) {
      FUN_0003d47c(0);
      iVar4 = FUN_0003d500();
      if (iVar4 == 0) {
        *(undefined1 *)(iVar1 + 0xc) = 1;
      }
    }
  }
  return iVar4;
}

