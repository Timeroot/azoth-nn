
void FUN_00040d0c(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 local_18;
  
  iVar2 = param_2 + 0x12;
  local_18 = param_4;
  if (*(short *)(param_2 + 6) == *(short *)((int)param_1 + 0xe)) {
    if (*(int *)(DAT_00040d80 + 0x58) == 0) {
      FUN_00024e98(iVar2,*(undefined1 *)(param_2 + 0x10));
    }
    else {
      iVar1 = FUN_00022f4c(iVar2);
      if (iVar1 == 0) {
        FUN_00024f7c(0);
      }
      else {
        FUN_00024e98(iVar2,*(undefined1 *)(param_2 + 0x10));
        FUN_0002330c();
        FUN_00026d18();
      }
    }
  }
  if (((*(short *)(param_2 + 6) == *(short *)((int)param_1 + 0x1a)) &&
      (*(short *)(param_2 + 0x10) == 2)) && (*param_1 != 0)) {
    iVar2 = FUN_00036e9c(iVar2);
    local_18 = CONCAT31(local_18._1_3_,iVar2 == 0);
    (*(code *)*param_1)(param_1,&local_18);
  }
  return;
}

