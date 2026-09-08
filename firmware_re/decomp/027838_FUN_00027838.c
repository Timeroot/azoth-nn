// @0x27838  size=86

void FUN_00027838(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_00027894;
  if (2 < (int)param_1) {
    return;
  }
  if (*(int *)(DAT_00027890 + 0x30) == 0) {
    return;
  }
  if (param_1 != 2) {
    FUN_00038614();
    iVar2 = DAT_00027898;
    if (param_1 == 0) {
      FUN_0001c590(DAT_00027898,param_2,0x20);
      goto LAB_0002785e;
    }
    if (param_1 == 1) {
      *(undefined4 *)(DAT_00027898 + 0x20) = *param_2;
      *(undefined4 *)(iVar2 + 0x24) = param_2[1];
      *(undefined2 *)(iVar2 + 0x28) = *(undefined2 *)(param_2 + 2);
      *(undefined1 *)(iVar2 + 0x2a) = *(undefined1 *)((int)param_2 + 10);
      goto LAB_0002785e;
    }
  }
  *(undefined1 *)(iVar1 + 1) = *(undefined1 *)param_2;
LAB_0002785e:
  *(uint *)(iVar1 + 0xc) = 1 << (param_1 & 0xff) | *(uint *)(iVar1 + 0xc);
  return;
}

