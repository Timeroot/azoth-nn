// @0x28f20 size=156

void FUN_00028f20(void)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = DAT_00028fbc;
  uVar5 = 0;
  local_20 = 0;
  sVar6 = 0x100;
  uVar4 = 1;
  uVar7 = 0;
  local_1c = 0;
  do {
    iVar2 = FUN_0003df48(sVar6);
    if ((iVar2 != 0) && ((*(uint *)(iVar1 + 0x304) & uVar4) != 0)) {
      FUN_0003df34(sVar6);
      uVar5 = uVar5 | uVar4;
    }
    sVar6 = sVar6 + 4;
    uVar4 = uVar4 << 1;
    uVar7 = uVar7 + 1;
  } while (uVar7 < 8);
  iVar2 = FUN_0003df48(0x17c);
  if (iVar2 != 0) {
    FUN_0003df34(0x17c);
    uVar5 = uVar5 | 0x80000000;
    FUN_0003db60(0,2,&local_20);
  }
  if ((uVar5 & 0xff) != 0) {
    uVar7 = 1;
    uVar4 = 0;
    do {
      if ((uVar7 & uVar5) != 0) {
        iVar2 = iVar1 + uVar4 * 4;
        pcVar3 = *(code **)(DAT_00028fc0 + uVar4 * 4);
        if (pcVar3 != (code *)0x0) {
          (*pcVar3)((*(uint *)(iVar2 + 0x510) & 0x3fff) >> 8,
                    (*(uint *)(iVar2 + 0x510) & 0x3ffff) >> 0x10);
        }
      }
      uVar7 = uVar7 << 1;
      uVar4 = uVar4 + 1;
    } while (uVar4 < 8);
  }
  if ((int)uVar5 < 0) {
    FUN_00042154(&local_20);
  }
  return;
}

