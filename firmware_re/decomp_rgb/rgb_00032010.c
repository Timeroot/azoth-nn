// FUN_00032010 @00032010 size=520

void FUN_00032010(uint param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  int iVar12;
  
  if (*(int *)(DAT_00032220 + 0x48) == 1) {
    param_1 = 0;
  }
  else {
    if ((*(int *)(DAT_00032220 + 0x48) == 2) && (0x19 < param_1)) {
      param_1 = 0x19;
      goto LAB_0003203a;
    }
    if (param_1 != 0) goto LAB_0003203a;
  }
  FUN_000271c0();
LAB_0003203a:
  iVar6 = DAT_00032224;
  pbVar10 = *(byte **)(DAT_00032224 + 0x68);
  bVar1 = *pbVar10;
  if (bVar1 == 6) {
    pbVar10[0x29] = (byte)((param_1 << 7) / 100);
  }
  else if (bVar1 < 7) {
    switch(bVar1) {
    case 0:
      uVar4 = (param_1 << 7) / 100;
      uVar2 = (ushort)uVar4 & 0xff;
      pbVar10[0x23] = (byte)uVar4;
      pbVar10[0x93] =
           (byte)((uint)((int)(short)(ushort)*(byte *)(param_2 + 5) * (int)(short)uVar2) >> 7);
      pbVar10[0x94] =
           (byte)((uint)((int)(short)(ushort)*(byte *)(param_2 + 6) * (int)(short)uVar2) >> 7);
      bVar1 = (byte)((uint)((int)(short)(ushort)*(byte *)(param_2 + 7) * (int)(short)uVar2) >> 7);
      pbVar10[0x95] = bVar1;
      *(undefined2 *)(pbVar10 + 0x88) = *(undefined2 *)(pbVar10 + 0x93);
      pbVar10[0x8a] = bVar1;
      break;
    case 1:
      pbVar10[0x24] = (byte)((param_1 << 7) / 100);
      break;
    case 2:
      pbVar10[0x25] = (byte)param_1;
      pbVar10[0x6c] = (byte)((param_1 * 0xff) / 100);
      break;
    case 3:
      pbVar10[0x28] = (byte)((param_1 << 7) / 100);
      break;
    case 4:
      pbVar10[0x26] = (byte)param_1;
      iVar7 = DAT_00032228;
      iVar11 = DAT_00032224 + 0x78;
      sVar3 = (short)param_1;
      iVar9 = 0;
      if (pbVar10[0x10] == 1) {
        iVar8 = DAT_00032228 + 7;
        do {
          *(undefined1 *)(iVar11 + iVar9) = *(undefined1 *)(iVar7 + iVar9);
          iVar12 = iVar9 * 3 + iVar8;
          pbVar10[iVar9 * 4 + 0x43b] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar8 + iVar9 * 3) * (int)sVar3) / 100);
          pbVar10[iVar9 * 4 + 0x43c] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar12 + 1) * (int)sVar3) / 100);
          iVar5 = iVar9 + 1;
          pbVar10[iVar9 * 4 + 0x43d] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar12 + 2) * (int)sVar3) / 100);
          iVar9 = iVar5;
        } while (iVar5 < 7);
      }
      else {
        do {
          iVar8 = param_2 + iVar9 * 4;
          *(undefined1 *)(iVar11 + iVar9) = *(undefined1 *)(iVar8 + 0x30);
          pbVar10[iVar9 * 4 + 0x43b] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar8 + 0x31) * (int)sVar3) / 100);
          pbVar10[iVar9 * 4 + 0x43c] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar8 + 0x32) * (int)sVar3) / 100);
          iVar7 = iVar9 + 1;
          pbVar10[iVar9 * 4 + 0x43d] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar8 + 0x33) * (int)sVar3) / 100);
          iVar9 = iVar7;
        } while (iVar7 < 7);
      }
      FUN_00025f40(DAT_00032224 + 0x78,*(undefined1 *)(*(int *)(iVar6 + 0x68) + 0x31));
      FUN_0002609c(*(undefined1 *)(*(int *)(iVar6 + 0x68) + 0x31));
      return;
    case 5:
      pbVar10[0x27] = (byte)((param_1 << 7) / 100);
      iVar6 = 0;
      if ((*(byte *)(param_2 + 0x51) & 0xf) == 0) {
        do {
          iVar9 = param_2 + iVar6 * 4;
          pbVar10[iVar6 * 4 + 0x43b] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar9 + 0x56) *
                            (int)(short)(ushort)pbVar10[0x27]) >> 7);
          pbVar10[iVar6 * 4 + 0x43c] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar9 + 0x57) *
                            (int)(short)(ushort)pbVar10[0x27]) >> 7);
          iVar7 = iVar6 + 1;
          pbVar10[iVar6 * 4 + 0x43d] =
               (byte)((uint)((int)(short)(ushort)*(byte *)(iVar9 + 0x58) *
                            (int)(short)(ushort)pbVar10[0x27]) >> 7);
          iVar6 = iVar7;
        } while (iVar7 < 7);
      }
    }
  }
  else if (bVar1 < 0xf0) {
    if (bVar1 == 7) {
      pbVar10[0x2a] = (byte)((param_1 << 7) / 100);
    }
    else if (bVar1 == 8) {
      pbVar10[0x2b] = (byte)((param_1 << 7) / 100);
    }
    else if (bVar1 == 9) {
      pbVar10[0x2c] = (byte)((param_1 << 7) / 100);
    }
  }
  return;
}

