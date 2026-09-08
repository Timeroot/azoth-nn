// @0x3e99c size=196

undefined4 FUN_0003e99c(uint param_1,byte *param_2,uint param_3,undefined4 param_4)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint local_20;
  undefined4 local_1c;
  
  iVar5 = DAT_0003ea60;
  uVar6 = 0;
  if (*(char *)(DAT_0003ea60 + param_1 + 0x5c) < '\0') {
    local_20 = param_3;
    local_1c = param_4;
    iVar3 = FUN_00037a80(param_1,param_3,(param_2[2] & 3) >> 1);
    if (iVar3 == -1) {
      uVar6 = 4;
    }
    else {
      if (-1 < (int)((uint)param_2[2] << 0x1d)) {
        if ((param_2[2] & 1) == 0) {
          local_20 = 0;
          local_1c = 0;
          FUN_0003d942(param_1,0,0,param_2[1]);
        }
        else {
          local_20 = param_1;
          iVar4 = FUN_0003dd44(&local_20);
          iVar4 = iVar4 + local_20 * 4;
          *(uint *)(iVar4 + 0x700) = *(uint *)(iVar4 + 0x700) & 0xfffffffd;
        }
        FUN_00041794(param_1);
      }
      if ((int)((uint)param_2[2] << 0x1e) < 0) {
        bVar2 = *param_2;
        iVar5 = DAT_0003ea64 + iVar3 * 4;
        *(uint *)(iVar5 + 0x510) = *(uint *)(iVar5 + 0x510) & DAT_0003ea68;
        *(uint *)(iVar5 + 0x510) =
             (param_1 & 0x3f) << 8 | (bVar2 & 3) << 0x10 | *(uint *)(iVar5 + 0x510);
      }
      else {
        pbVar1 = (byte *)(iVar5 + iVar3 + 0x84);
        *pbVar1 = *pbVar1 | *param_2 << 6;
      }
    }
  }
  else {
    uVar6 = 8;
  }
  return uVar6;
}

