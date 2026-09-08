// @0x3d8de  size=50

undefined8 FUN_0003d8de(int param_1,uint param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  int local_28;
  uint uStack_24;
  int iStack_20;
  int iStack_1c;
  
  local_28 = param_1;
  uStack_24 = param_2;
  iStack_20 = param_3;
  iStack_1c = param_4;
  iVar1 = FUN_0003dcd4(&local_28);
  *(uint *)(iVar1 + local_28 * 4 + 0x700) =
       param_2 | param_3 << 1 | param_4 << 2 | param_5 << 8 | param_6 << 0x10;
  return CONCAT44(uStack_24,local_28);
}

