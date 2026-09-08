// @0x27a68  size=52

void FUN_00027a68(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
    *param_2 = *(undefined1 *)(DAT_00027aa4 + 0xe);
    return;
  case 1:
    iVar1 = DAT_00027aa4 + 0x14;
    break;
  case 2:
    iVar1 = DAT_00027aa4 + 0x10;
    break;
  case 3:
    iVar1 = DAT_00027aa4 + 0x12;
    break;
  default:
    return;
  case 5:
    iVar1 = DAT_00027aa4 + 0x24;
  }
  FUN_0001c590(param_2,iVar1);
  return;
}

