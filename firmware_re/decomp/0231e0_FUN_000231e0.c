// @0x231e0  size=106

void FUN_000231e0(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (*(int *)(DAT_0002324c + 0x30) == 2) {
    return;
  }
  if (((*DAT_00023250 & 0xc) == 0) && (param_1 != 0xf1)) {
    if (param_1 < 10) {
      FUN_0003222c(param_1,DAT_00023254 + 4);
    }
    else if (param_1 == 0xf0) {
      FUN_00031f1c(DAT_00023258 + 2,DAT_00023258 + 0x1bb);
    }
    param_4 = 7;
    iVar2 = FUN_0003dcd4(&stack0xfffffff8);
    if ((*(uint *)(iVar2 + 0x510) >> 7 & 1) != 0) {
      FUN_00030c60();
    }
  }
  else {
    FUN_0003222c(0xf1,DAT_00023254 + 4);
  }
  iVar2 = DAT_0002fd74;
  if (*(int *)(DAT_0002fd6c + 0x18) != 0) {
    return;
  }
  if (*(int *)(DAT_0002fd6c + 0x48) == 1) {
    FUN_00032010(0,DAT_0002fd70 + 4,1,param_4);
    uVar1 = *(undefined1 *)(iVar2 + 7);
    uVar3 = 0;
  }
  else {
    if (*(int *)(DAT_0002fd6c + 0x48) != 2) {
      return;
    }
    if (*(byte *)(*(int *)(DAT_0002fd78 + (uint)*(byte *)(DAT_0002fd74 + 5) * 4) + 1) < 0x19) {
      return;
    }
    FUN_00032010(0x19,DAT_0002fd70 + 4,DAT_0002fd78,param_4);
    uVar1 = *(undefined1 *)(iVar2 + 7);
    uVar3 = 0x19;
  }
  FUN_00032550(uVar3,uVar1);
  return;
}

