// FUN_00029a5c @00029a5c size=94

void FUN_00029a5c(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(DAT_00029a84 + 0x18) == 0) {
    uVar1 = 0;
    *(undefined4 *)(DAT_00029a84 + 0x4c) = 0;
  }
  else {
    if (param_1 == 100) {
      *(undefined4 *)(DAT_00029a84 + 0x4c) = 2;
      return;
    }
    *(undefined4 *)(DAT_00029a84 + 0x4c) = 1;
    uVar1 = 1;
  }
  FUN_0003362c(0x81,2,0,uVar1);
  return;
}

