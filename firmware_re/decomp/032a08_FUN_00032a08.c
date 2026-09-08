// @0x32a08  size=84

void FUN_00032a08(uint param_1,uint param_2,undefined2 *param_3)

{
  uint uVar1;
  undefined2 *puVar2;
  uint uVar3;
  int iVar4;
  
  if ((((*(int *)(DAT_00032a5c + 0x44) == 0) && (**(char **)(DAT_00032a60 + 0x68) == -0xf)) &&
      (param_2 < 6)) && (param_1 < 0x10)) {
    iVar4 = DAT_00032a64 + param_2 * 0x34;
    uVar3 = (uint)*(byte *)(iVar4 + param_1 * 2);
    uVar1 = (uint)*(byte *)(iVar4 + param_1 * 2 + 1);
    if ((uVar3 < 6) && (uVar1 < 0x10)) {
      puVar2 = (undefined2 *)(uVar1 * 3 + DAT_00032a68 + uVar3 * 0x30);
      *puVar2 = *param_3;
      *(undefined1 *)(puVar2 + 1) = *(undefined1 *)(param_3 + 1);
    }
  }
  return;
}

