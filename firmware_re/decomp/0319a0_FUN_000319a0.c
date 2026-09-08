// @0x319a0  size=236

undefined1 FUN_000319a0(uint param_1,undefined4 param_2,uint param_3,char param_4)

{
  uint *puVar1;
  uint *puVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  
  puVar1 = DAT_00031b04;
  if ((*DAT_00031a04 != DAT_00031a08) && ((int)((uint)*DAT_00031a0c << 0x1d) < 0)) {
    if (*DAT_00031a10 != '\0') {
      uVar3 = FUN_00031a18(param_1,param_2);
      return uVar3;
    }
    iVar4 = FUN_0003499c();
    if ((iVar4 == 5) && (*DAT_00031a14 == 1)) {
      iVar4 = FUN_00033474(param_1 & 0xff,param_2,param_3);
      if (iVar4 == 0) {
        return 0;
      }
      if (iVar4 != 0x11) {
        FUN_000340ec();
      }
    }
    return 2;
  }
  param_1 = param_1 & 0xf;
  uVar5 = param_1 - 1;
  *DAT_00031b04 = uVar5;
  iVar4 = DAT_00031b14;
  puVar2 = DAT_00031b04;
  if (uVar5 < 4) {
    if (((int)(*DAT_00031b08 << 0x1e) < 0) || (*DAT_00031b0c == DAT_00031b10)) {
      if ((*(byte *)((int)DAT_00031b04 + param_1 + 0x17) & param_4 - 1U) == 0) {
        if (param_3 <= *(byte *)(DAT_00031b14 + uVar5)) {
          *(undefined1 *)((int)DAT_00031b04 + param_1 + 0x17) = 1;
          FUN_0001c590(puVar2[param_1 + 0x10],param_2,param_3);
          FUN_0001c5e0(puVar2[*puVar1 + 0x11] + param_3,*(byte *)(iVar4 + *puVar1) - param_3);
          return 0;
        }
        FUN_0002778c(uVar5 & 0xff);
        FUN_0002778c(param_3 & 0xff);
        FUN_000277cc(s__EPwrong_size_00031b18);
        goto LAB_00031a8c;
      }
    }
    else if ((*DAT_00031b08 & 1) != 0) {
      FUN_0002ffd8(uVar5,param_2,param_3);
      return 0;
    }
    uVar3 = 2;
  }
  else {
LAB_00031a8c:
    uVar3 = 1;
  }
  return uVar3;
}

