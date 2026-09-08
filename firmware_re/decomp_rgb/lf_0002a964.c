// FUN_0002a964 @0002a964 size=164

void FUN_0002a964(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = param_1 + -0x1e7;
  if (param_1 == 0x1e7) {
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 0xf6;
LAB_0002a9b6:
    *(undefined1 *)(param_2 + 3) = 0;
    goto LAB_0002a9b8;
  }
  if (0x1e7 < param_1) {
    if (iVar2 == 10) {
      uVar1 = 2;
LAB_0002aa04:
      *(undefined1 *)(param_2 + 1) = uVar1;
    }
    else {
      if (iVar2 < 0xb) {
        uVar1 = 1;
        if (iVar2 == 1) {
          *(undefined1 *)(param_2 + 1) = 0;
          *(undefined1 *)(param_2 + 2) = 0;
          *(undefined1 *)(param_2 + 3) = 0;
LAB_0002aa00:
          *(undefined1 *)(param_2 + 4) = uVar1;
          return;
        }
        if (iVar2 == 2) {
          *(undefined1 *)(param_2 + 1) = 0;
          *(undefined1 *)(param_2 + 2) = 0;
          *(undefined1 *)(param_2 + 3) = 0;
          uVar1 = 0xff;
          goto LAB_0002aa00;
        }
        if (iVar2 != 9) {
          return;
        }
        goto LAB_0002aa04;
      }
      if (iVar2 == 0xb) {
        uVar1 = 4;
        goto LAB_0002aa04;
      }
      if (iVar2 != 0x17) {
        return;
      }
      *(undefined1 *)(param_2 + 1) = 0;
    }
    *(undefined1 *)(param_2 + 2) = 0;
    goto LAB_0002a9b6;
  }
  switch(param_1) {
  case 0x1e0:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 0xf6;
    break;
  case 0x1e1:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 0;
    break;
  case 0x1e2:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 10;
    break;
  case 0x1e3:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 10;
    goto LAB_0002a9b6;
  case 0x1e4:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 10;
    goto LAB_0002a9e0;
  case 0x1e5:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 0;
    goto LAB_0002a9e0;
  case 0x1e6:
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)(param_2 + 2) = 0xf6;
LAB_0002a9e0:
    *(undefined1 *)(param_2 + 3) = 10;
    goto LAB_0002a9b8;
  default:
    goto switchD_0002a986_default;
  }
  *(undefined1 *)(param_2 + 3) = 0xf6;
LAB_0002a9b8:
  *(undefined1 *)(param_2 + 4) = 0;
switchD_0002a986_default:
  return;
}

