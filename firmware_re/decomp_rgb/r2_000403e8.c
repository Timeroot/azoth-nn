// FUN_000403e8 @000403e8 size=178

/* WARNING: Removing unreachable block (ram,0x00032638) */

void FUN_000403e8(undefined4 param_1)

{
  int iVar1;
  undefined4 local_c8;
  undefined1 auStack_c4 [13];
  undefined1 auStack_b7 [115];
  undefined1 auStack_44 [56];
  undefined4 local_c;
  undefined4 local_8;
  
  switch(param_1) {
  default:
    goto switchD_000403f0_caseD_0;
  case 3:
    FUN_00025ad8(1);
    FUN_0002fb4c();
    FUN_0002d5cc(0x3d,0xffffffff,0);
    return;
  case 5:
    if (*(int *)(DAT_00040494 + 0x58) == 0) {
      return;
    }
    FUN_00025b3c(2);
    return;
  case 7:
    local_c = 8;
    local_8 = 8;
    iVar1 = FUN_000420a0(auStack_44,&local_c,auStack_c4,&local_8);
    if (iVar1 != 0) {
      FUN_000340ec();
    }
    FUN_0003a9bc(2);
    local_c8 = local_8;
    iVar1 = FUN_00035fc0(DAT_00040498,auStack_44,local_c,auStack_c4);
    break;
  case 8:
    if (*(short *)(DAT_0004049c + 0xc) == -1) {
      return;
    }
    iVar1 = FUN_00041cfc(*(short *)(DAT_0004049c + 0xc),&local_c8);
    if (iVar1 == 5) {
      return;
    }
    if (iVar1 != 0) {
      FUN_000340ec();
    }
    FUN_0003a9bc(6);
    iVar1 = FUN_00035d98(DAT_00040498,auStack_b7);
  }
  if (iVar1 != 0) {
    FUN_000340ec();
  }
switchD_000403f0_caseD_0:
  return;
}

