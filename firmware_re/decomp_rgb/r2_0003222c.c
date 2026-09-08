// FUN_0003222c @0003222c size=306

void FUN_0003222c(uint param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  
  puVar1 = DAT_00032378;
  if (((param_1 == 0xf2) || (param_1 == 0xf3)) && (**(byte **)(DAT_00032378 + 0x68) == param_1)) {
    return;
  }
  FUN_0001c580(*DAT_0003237c);
  iVar2 = 0;
  iVar6 = *(int *)(puVar1 + 0x68);
  do {
    iVar5 = iVar6 + iVar2;
    iVar2 = iVar2 + 1;
    *(undefined1 *)(iVar5 + 0x38) = 0;
    *(undefined1 *)(iVar5 + 0x43) = 0;
    *(undefined1 *)(iVar5 + 0xd2) = 0;
  } while (iVar2 < 0xb);
  *puVar1 = 1;
  if (param_1 == 9) {
    FUN_000271c0();
    FUN_0002716c();
    FUN_00032730(param_2);
    goto switchD_00032272_default;
  }
  if ((int)param_1 < 10) {
    switch(param_1) {
    case 0:
      FUN_0002716c();
      FUN_00032af4(param_2);
      break;
    case 1:
      FUN_0002716c();
      FUN_00031d44(param_2);
      break;
    case 2:
      FUN_0002716c();
      FUN_00031dec(param_2);
      break;
    case 3:
      FUN_000271c0();
      FUN_0002716c();
      FUN_000327b4(param_2);
      break;
    case 4:
      FUN_0002716c();
      FUN_00032b44(param_2);
      break;
    case 5:
      FUN_000271c0();
      FUN_0002716c();
      FUN_0003283c(param_2);
      break;
    case 6:
      FUN_000271c0();
      FUN_0002716c();
      FUN_00032a6c(param_2);
      break;
    case 7:
      FUN_000271c0();
      FUN_0002716c();
      FUN_0003263c(param_2);
      break;
    case 8:
      FUN_000271c0();
      FUN_0002716c();
      FUN_00031e28(param_2);
    }
    goto switchD_00032272_default;
  }
  switch(param_1) {
  case 0xf1:
    **(undefined1 **)(puVar1 + 0x68) = 0xf1;
    break;
  case 0xf2:
    uVar4 = 0xf2;
    goto LAB_00032348;
  case 0xf3:
    uVar4 = 0xf3;
LAB_00032348:
    puVar3 = *(undefined1 **)(puVar1 + 0x68);
    *puVar3 = uVar4;
    puVar3[0xdd] = 0;
    break;
  case 0xf6:
    **(undefined1 **)(puVar1 + 0x68) = 0xf6;
    FUN_000282ec(0xf6,*(undefined3 *)(DAT_00032380 + 9));
    *puVar1 = 0;
    break;
  case 0xff:
    FUN_000271c0();
    FUN_0002716c();
    FUN_0003253c();
  }
switchD_00032272_default:
  *(undefined4 *)(puVar1 + 4) = 0;
  return;
}

