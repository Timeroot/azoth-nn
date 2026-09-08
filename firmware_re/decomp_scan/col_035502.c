// @0x35502 size=118

void FUN_00035502(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  if (*param_2 != -1) {
    FUN_0003ded4();
    FUN_0003db08(*param_2);
  }
  if (param_2[1] != -1) {
    FUN_0003dae2(param_2[1],0);
  }
  *(int *)(*param_1 + 0x524) = param_2[6];
  *(uint *)(*param_1 + 0x56c) = (uint)(*(byte *)((int)param_2 + 0x15) | *(byte *)(param_2 + 5));
  iVar2 = param_2[1];
  iVar1 = *param_1;
  *(int *)(iVar1 + 0x50c) = *param_2;
  *(int *)(iVar1 + 0x514) = iVar2;
  if ((char)param_2[5] == '\x01') {
    if (param_2[2] != -1) {
      FUN_0003dae2(param_2[2],0);
    }
    if (param_2[3] != -1) {
      FUN_0003ded4();
      FUN_0003db08(param_2[3]);
    }
    iVar2 = param_2[2];
    iVar1 = *param_1;
    *(int *)(iVar1 + 0x508) = param_2[3];
    *(int *)(iVar1 + 0x510) = iVar2;
  }
  return;
}

