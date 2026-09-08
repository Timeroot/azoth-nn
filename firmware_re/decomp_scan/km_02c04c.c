// @0x2c04c size=164

void FUN_0002c04c(uint param_1,uint param_2,uint param_3)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = DAT_0002c0f4;
  if (param_2 < 0xbd) {
    uVar3 = (uint)*(byte *)(DAT_0002c0f0 + param_2);
  }
  else {
    uVar3 = 0;
  }
  if (param_3 < 0xbd) {
    param_3 = (uint)*(byte *)(DAT_0002c0f0 + param_3);
  }
  else if (0x1e < param_3 - 0x1e0) {
    if (param_3 == 0xd3) {
      param_3 = 0xa0d3;
    }
    else if (param_3 == 0xff) {
      iVar4 = DAT_0002c0f8 + param_1 * 8;
      if (uVar3 == 0xd4) {
        param_3 = (uint)*(ushort *)(iVar4 + 4);
      }
      else if (uVar3 == 0xd5) {
        param_3 = (uint)*(ushort *)(iVar4 + 2);
      }
      else if (uVar3 == 0xd6) {
        param_3 = (uint)*(ushort *)(iVar4 + 6);
      }
    }
    else {
      param_3 = 0;
    }
  }
  if ((param_1 < 8) && (uVar3 - 0xd4 < 3)) {
    iVar4 = DAT_0002c0f4 + param_1 * 8;
    uVar1 = (undefined2)param_3;
    if (uVar3 == 0xd4) {
      *(undefined2 *)(iVar4 + 0x2c6) = uVar1;
    }
    else if (uVar3 == 0xd5) {
      *(undefined2 *)(iVar4 + 0x2c4) = uVar1;
    }
    else if (uVar3 == 0xd6) {
      *(undefined2 *)(iVar4 + 0x2c8) = uVar1;
    }
    if (*(byte *)(DAT_0002c0fc + 8) == param_1) {
      iVar4 = iVar2 + (uint)*(byte *)(DAT_0002c0fc + 8) * 8;
      *(undefined2 *)(iVar2 + 0x272) = *(undefined2 *)(iVar4 + 0x2c6);
      *(undefined2 *)(iVar2 + 0x274) = *(undefined2 *)(iVar4 + 0x2c4);
      *(undefined2 *)(iVar2 + 0x276) = *(undefined2 *)(iVar4 + 0x2c8);
    }
  }
  return;
}

