// @0x44774 size=164

void FUN_00044774(int *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  int iVar2;
  uint local_10;
  
  *(undefined4 *)(*param_1 * 4 + 0x50000700) = 0x60c;
  *(undefined4 *)(param_1[1] * 4 + 0x50000700) = 0x60c;
  local_10 = param_4;
  FUN_0003defc(*param_1);
  FUN_0003defc(param_1[1]);
  *(undefined4 *)(*param_1 * 4 + 0x50000700) = 0x60d;
  *(undefined4 *)(param_1[1] * 4 + 0x50000700) = 0x60d;
  FUN_0003e8e4(4);
  iVar2 = 0;
  do {
    local_10 = param_1[1];
    iVar1 = FUN_0003ddb4(&local_10);
    if ((*(uint *)(iVar1 + 0x510) >> (local_10 & 0xff) & 1) != 0) {
      if (iVar2 == 0) {
        return;
      }
      break;
    }
    FUN_0003dc3c(*param_1);
    FUN_0003e8e4(4);
    FUN_0003defc(*param_1);
    FUN_0003e8e4(4);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 9);
  FUN_0003dc3c(param_1[1]);
  FUN_0003e8e4(4);
  FUN_0003defc(param_1[1],extraout_r1,extraout_r2,local_10);
  return;
}

