// @0x292f8  size=86

uint FUN_000292f8(undefined4 param_1,uint param_2)

{
  ushort uVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  pcVar2 = DAT_00029350;
  uVar5 = 0;
  if (*DAT_00029350 == '\x01') {
    *DAT_00029350 = '\0';
    FUN_0002cf80();
  }
  uVar4 = (uint)*(ushort *)(pcVar2 + 2);
  uVar3 = (uint)*(ushort *)(pcVar2 + 4);
  if (uVar4 != uVar3) {
    if (uVar3 < uVar4) {
      uVar5 = uVar4 - uVar3;
    }
    else {
      uVar5 = 0x1000 - uVar3;
    }
    if ((int)param_2 < (int)uVar5) {
      uVar5 = param_2;
    }
    FUN_0001c590(param_1,DAT_00029354 + uVar3,uVar5);
    uVar1 = *(ushort *)(pcVar2 + 4);
    *(short *)(pcVar2 + 4) = (short)(uVar1 + uVar5);
    if (0xfff < (uVar1 + uVar5 & 0xffff)) {
      pcVar2[4] = '\0';
      pcVar2[5] = '\0';
    }
  }
  return uVar5 & 0xff;
}

