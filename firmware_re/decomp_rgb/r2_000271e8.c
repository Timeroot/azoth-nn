// FUN_000271e8 @000271e8 size=222

uint FUN_000271e8(uint param_1,uint param_2,int param_3)

{
  char cVar1;
  uint uVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_10;
  
  uVar2 = (uint)*(byte *)(*(int *)(DAT_000272c8 + 0x68) + 6);
  local_10 = param_2;
  if (param_3 != 0) {
    uVar6 = param_1 & 0xff;
    uVar5 = param_2 & 0xff;
    if (uVar6 == uVar5) {
      cVar3 = (char)param_1;
    }
    else {
      if (uVar5 < uVar6) {
        cVar3 = (char)((((uVar6 - uVar5) * 0x10) / uVar2) * param_3 >> 4);
      }
      else {
        cVar3 = -(char)((((uVar5 - uVar6) * 0x10) / uVar2) * param_3 >> 4);
      }
      cVar3 = (char)param_2 + cVar3;
    }
    uVar6 = (param_1 & 0xffff) >> 8;
    uVar5 = (param_2 & 0xffff) >> 8;
    if (uVar6 == uVar5) {
      cVar4 = (char)(param_1 >> 8);
    }
    else {
      if (uVar5 < uVar6) {
        cVar4 = (char)((((uVar6 - uVar5) * 0x10) / uVar2) * param_3 >> 4);
      }
      else {
        cVar4 = -(char)((((uVar5 - uVar6) * 0x10) / uVar2) * param_3 >> 4);
      }
      cVar4 = (char)(param_2 >> 8) + cVar4;
    }
    uVar6 = (param_1 & 0xffffff) >> 0x10;
    uVar5 = (param_2 & 0xffffff) >> 0x10;
    if (uVar6 == uVar5) {
      local_10._0_3_ = CONCAT12((char)(param_1 >> 0x10),CONCAT11(cVar4,cVar3));
      local_10 = (uint)(uint3)local_10;
    }
    else {
      if (uVar5 < uVar6) {
        cVar1 = (char)((((uVar6 - uVar5) * 0x10) / uVar2) * param_3 >> 4);
      }
      else {
        cVar1 = -(char)((((uVar5 - uVar6) * 0x10) / uVar2) * param_3 >> 4);
      }
      local_10._0_3_ = CONCAT12((char)(param_2 >> 0x10) + cVar1,CONCAT11(cVar4,cVar3));
      local_10 = (uint)(uint3)local_10;
    }
  }
  return local_10 & 0xffffff;
}

