// FUN_000276d8 @000276d8 size=176

void FUN_000276d8(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  undefined1 uVar6;
  int iVar7;
  int extraout_r2;
  uint extraout_r3;
  int iVar8;
  undefined4 local_1c;
  
  iVar8 = param_1 + param_2 * 0x18;
  bVar2 = *(byte *)(param_1 + 0x2b);
  bVar3 = *(byte *)(iVar8 + 0xe8);
  bVar4 = *(byte *)(iVar8 + 0xe9);
  bVar5 = *(byte *)(iVar8 + 0xea);
  iVar7 = 0;
  do {
    iVar1 = iVar7 * 4;
    iVar7 = FUN_0003b73c();
    if (iVar7 == 0) {
      local_1c._0_2_ = *DAT_00027788;
      uVar6 = *(undefined1 *)(DAT_00027788 + 1);
    }
    else {
      local_1c._0_2_ =
           CONCAT11((char)((((int)(short)(ushort)bVar4 * (int)(short)(ushort)bVar2 & 0x7fffU) >> 7)
                           * iVar7 >> 8),
                    (char)((((int)(short)(ushort)bVar3 * (int)(short)(ushort)bVar2 & 0x7fffU) >> 7)
                           * iVar7 >> 8));
      uVar6 = (undefined1)
              ((((int)(short)(ushort)bVar5 * (int)(short)(ushort)bVar2 & 0x7fffU) >> 7) * iVar7 >> 8
              );
    }
    local_1c._0_3_ = CONCAT12(uVar6,(undefined2)local_1c);
    if (extraout_r3 < 0x80) {
      local_1c = CONCAT13((char)extraout_r3 + '\x01',(undefined3)local_1c);
    }
    else {
      local_1c = CONCAT13(0x80,(undefined3)local_1c);
      if (extraout_r2 == 3) {
        *(undefined1 *)(iVar8 + 0xe6) = 1;
      }
    }
    iVar7 = extraout_r2 + 1;
    *(undefined4 *)(iVar8 + iVar1 + 0xec) = local_1c;
  } while ((iVar7 < 4) && ((iVar7 == 0 || (0x13 < *(byte *)(iVar8 + iVar7 * 4 + 0xeb)))));
  return;
}

