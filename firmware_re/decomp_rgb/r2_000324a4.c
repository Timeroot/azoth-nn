// FUN_000324a4 @000324a4 size=144

void FUN_000324a4(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  undefined2 *puVar5;
  undefined2 local_10;
  undefined1 local_e;
  
  iVar2 = DAT_00032538;
  if (param_2 - 0xe0 < 8 || param_2 == 0xe8) {
    bVar3 = (char)param_2 + 0xa0;
  }
  else {
    if (4 < param_2 - 0x87) {
      if (0x7b < param_2 - 4) {
        param_2 = 0;
      }
      goto LAB_000324dc;
    }
    bVar3 = (char)param_2 - 0x17;
  }
  param_2 = (uint)bVar3;
LAB_000324dc:
  uVar1 = (uint)*(byte *)(DAT_00032534 + param_2 * 2);
  uVar4 = (uint)*(byte *)(DAT_00032534 + param_2 * 2 + 1);
  puVar5 = (undefined2 *)(uVar4 * 3 + uVar1 * 0x30 + *(int *)(*(int *)(DAT_00032538 + 0x68) + 0xe0))
  ;
  local_10 = (undefined2)param_1;
  *puVar5 = local_10;
  local_e = (undefined1)((uint)param_1 >> 0x10);
  *(undefined1 *)(puVar5 + 1) = local_e;
  iVar2 = *(int *)(iVar2 + 0x68) + uVar1 * 0x58 + uVar4 * 4;
  *(undefined2 *)(iVar2 + 0x4ba) = local_10;
  *(undefined1 *)(iVar2 + 0x4bc) = local_e;
  *(undefined1 *)(iVar2 + 0x4bd) = 0;
  return;
}

