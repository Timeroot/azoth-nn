// FUN_0002b318 @0002b318 size=88

void FUN_0002b318(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *DAT_0002b378;
  switch(param_1) {
  case 0xf0:
    uVar2 = 0;
    uVar1 = 0xf;
    break;
  default:
    return;
  case 0xf2:
    uVar2 = 0;
    uVar1 = 0x10;
    break;
  case 0xf3:
    uVar2 = 0;
    uVar1 = 0x11;
    break;
  case 0xf4:
    uVar2 = 0;
    uVar1 = 0x16;
    break;
  case 0xf5:
    *(undefined1 *)(DAT_0002b378 + 1) = 0;
    if (iVar3 != 0) {
      return;
    }
    uVar2 = 200;
    uVar1 = 0x14;
    break;
  case 0xf6:
    *(undefined1 *)(DAT_0002b378 + 1) = 1;
    if (iVar3 != 0) {
      return;
    }
    uVar2 = 200;
    uVar1 = 0x12;
  }
  FUN_0002d5cc(uVar1,1000,uVar2);
  return;
}

