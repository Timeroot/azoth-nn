// FUN_00032ce8 @00032ce8 size=178

void FUN_00032ce8(int param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint local_28;
  
  iVar1 = DAT_00032d9c;
  if (param_2 == 0) {
    if (*(char *)(DAT_00032d9c + 3) == '\0') {
      return;
    }
  }
  else {
    *(undefined4 *)(DAT_00032d9c + 100) = 0;
    *(undefined1 *)(iVar1 + 3) = 1;
  }
  puVar2 = DAT_00032da0;
  uVar4 = *(int *)(iVar1 + 100) + 1;
  *(uint *)(iVar1 + 100) = uVar4;
  uVar3 = 0;
  if (uVar4 < 500) {
    do {
      if (*(byte *)(param_1 + uVar3 * 2 + 5) >> 3 == 1) {
        if (uVar4 < 500) {
          if ((int)((uint)*(byte *)(DAT_00032da8 + (uint)*(byte *)(DAT_00032da4 + 6)) << 0x19) < 0)
          {
            local_28 = (uint)*(uint3 *)((int)puVar2 + 3);
          }
          else {
            local_28 = *(uint *)((int)puVar2 + 6);
          }
        }
        else {
          local_28 = *puVar2;
        }
        FUN_000324a4(local_28,uVar3 & 0xff);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0xf7);
  }
  else {
    do {
      if ((*(byte *)(param_1 + uVar3 * 2 + 5) >> 3 == 1) && (499 < uVar4)) {
        FUN_000324a4(*puVar2,uVar3 & 0xff);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0xf7);
    *(undefined4 *)(iVar1 + 100) = 0;
    *(undefined1 *)(iVar1 + 3) = 0;
  }
  return;
}

