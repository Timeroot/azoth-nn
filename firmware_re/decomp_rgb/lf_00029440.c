// FUN_00029440 @00029440 size=66

undefined8 FUN_00029440(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_20;
  uint local_1c;
  undefined4 uStack_18;
  undefined1 local_14;
  byte local_13;
  byte local_12;
  undefined1 uStack_11;
  
  iVar2 = DAT_00029484;
  bVar1 = *(byte *)(DAT_00029484 + 3);
  local_1c = (uint)bVar1;
  local_20 = param_1;
  uVar3 = param_2;
  if (local_1c == 0) {
    local_20 = 1;
    uStack_18 = 0x6680000;
    uStack_11 = (undefined1)((uint)param_4 >> 0x18);
    _local_14 = CONCAT12(bVar1,CONCAT11(bVar1,6));
    iVar4 = FUN_0003ce78(DAT_0002948c,&local_20,DAT_00029488,0);
    if (iVar4 != 0) {
      FUN_000340ec();
    }
    FUN_0003f3f8(DAT_0002948c + 4);
    *(undefined1 *)(iVar2 + 3) = 1;
    uVar3 = local_1c;
  }
  local_1c = uVar3;
  return CONCAT44(local_1c,local_20);
}

