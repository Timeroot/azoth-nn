// FUN_0002d5cc @0002d5cc size=214

void FUN_0002d5cc(uint param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  ushort *puVar4;
  byte *pbVar5;
  
  iVar2 = DAT_0002d6a4;
  if (*(char *)(DAT_0002d6a4 + 0xe) == '\0') {
    puVar4 = (ushort *)(DAT_0002d6a4 + 0x1c);
    uVar1 = *puVar4;
    if (param_1 == 0) {
      *puVar4 = uVar1 | 0x8000;
    }
    else if (((-1 < (int)((uint)*(ushort *)(DAT_0002d6a4 + 0x1e) << 0x1e)) &&
             (-1 < (int)((uint)*(ushort *)(DAT_0002d6a4 + 0x1e) << 0x1d))) &&
            ((-1 < (int)((uint)uVar1 << 0x11) || (param_2 == -1)))) {
      pbVar5 = (byte *)(DAT_0002d6a4 + 1);
      uVar3 = (uint)*pbVar5;
      if ((((uVar1 & 0x1fff) == param_1) && ((int)(uVar3 << 0x1c) < 0)) && (param_4 == 0)) {
        if (((int)(uVar3 << 0x1e) < 0) && (param_2 != -1)) {
          *(short *)(DAT_0002d6a4 + 0x18) = (short)param_2;
        }
      }
      else {
        *(undefined1 *)(DAT_0002d6a4 + 3) = 0;
        *puVar4 = uVar1 | 0x2000;
        if (param_2 == -1) {
          *puVar4 = uVar1 | 0x6000;
          *(undefined4 *)(iVar2 + 0x30) = 1000;
        }
        else {
          *(int *)(iVar2 + 0x30) = param_2;
        }
        if (-1 < (int)(uVar3 << 0x1b)) {
          *(undefined4 *)(iVar2 + 0x28) = 0;
          FUN_0002d760();
          *(undefined2 *)(iVar2 + 0x18) = 0;
          *(undefined4 *)(iVar2 + 0x4c) = 0;
          *(undefined4 *)(iVar2 + 0x2c) = 0;
        }
        iVar2 = DAT_0002d6a4;
        *(undefined4 *)(DAT_0002d6a4 + 0xd0) = 0;
        if (param_3 != 0) {
          *pbVar5 = *pbVar5 & 0xfd | 1;
          *(undefined4 *)(iVar2 + 0xd0) = 1;
          *(int *)(iVar2 + 0xd4) = param_3;
        }
        *pbVar5 = *pbVar5 & 3 | (*pbVar5 >> 2 | 2) << 2;
        *puVar4 = *puVar4 & 0xe000 | (ushort)param_1 & 0x1fff;
      }
      FUN_0002e250();
      return;
    }
  }
  return;
}

