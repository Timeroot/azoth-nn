// FUN_00033474 @00033474 size=12

undefined4 FUN_00033474(uint param_1,uint param_2,uint param_3)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint *puStack_28;
  
  puVar1 = DAT_00033480;
  *DAT_00033480 = param_2;
  puVar1[1] = param_3;
  puStack_28 = puVar1;
  uVar3 = FUN_00038a56();
  puStack_28 = (uint *)((uint)puStack_28 & 0xffffff00);
  FUN_00035410(&puStack_28);
  iVar2 = DAT_0003fe88;
  if (((param_1 & 0xf) == 0) && (param_1 != *(byte *)(DAT_0003fe88 + 2))) {
    uVar8 = 0x10;
  }
  else {
    uVar3 = 1 << (uVar3 & 0xff);
    if ((((uint)(ushort)~*(ushort *)(DAT_0003fe88 + 8) | *(uint *)(DAT_0003fe88 + 0xc)) & uVar3) ==
        0) {
      puVar4 = (undefined4 *)FUN_00038a64(param_1);
      if ((int)(param_1 << 0x18) < 0) {
        puVar5 = (uint *)(DAT_0003fe8c + (param_1 & 0xf) * 0xc);
        iVar6 = (uint)(byte)puVar1[2] << 0x1f;
        if (*puVar1 >> 0x1d == 1) {
          uVar8 = DAT_0003fe98;
          if (iVar6 != 0) {
            uVar8 = DAT_0003fe90;
          }
        }
        else {
          uVar8 = DAT_0003fe9c;
          if (iVar6 != 0) {
            uVar8 = DAT_0003fe94;
          }
        }
      }
      else {
        puVar5 = (uint *)(DAT_0003fe8c + 0x6c + (param_1 & 0xf) * 0xc);
        uVar8 = DAT_0003fea0;
      }
      *puVar4 = uVar8;
      uVar7 = puVar1[1];
      uVar9 = puVar1[2];
      *puVar5 = *puVar1;
      puVar5[1] = uVar7;
      puVar5[2] = uVar9;
      puVar4[1] = puVar5;
      puVar4[2] = 0;
      *(undefined1 *)((int)puVar4 + 0xe) = 0;
      *(uint *)(iVar2 + 0xc) = uVar3 | *(uint *)(iVar2 + 0xc);
      uVar8 = 0;
      FUN_00045a74();
    }
    else {
      uVar8 = 0x11;
    }
  }
  FUN_00035458((uint)puStack_28 & 0xff);
  return uVar8;
}

