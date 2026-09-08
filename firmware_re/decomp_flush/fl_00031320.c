
undefined8 FUN_00031320(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined2 uStack_12;
  undefined4 local_10;
  undefined2 local_c;
  undefined2 uStack_a;
  
  if (param_1 != 0) {
    local_14 = (undefined1)param_2;
    local_13 = (undefined1)((uint)param_2 >> 8);
    uStack_12 = (undefined2)((uint)param_2 >> 0x10);
    local_18 = (undefined1)param_1;
    local_17 = (undefined1)((uint)param_1 >> 8);
    local_16 = (undefined1)((uint)param_1 >> 0x10);
    local_15 = (undefined1)((uint)param_1 >> 0x18);
    if (*DAT_000311c8 == 0) {
      local_14 = 6;
      local_13 = 0xff;
      local_15 = 0xff;
      local_10 = 0x80000000;
      local_16 = 0x17;
      local_17 = 0x18;
      _local_c = CONCAT22((short)((uint)param_4 >> 0x10),3);
      local_18 = 0x16;
      iVar1 = FUN_0003ce08(DAT_000311d0,&local_18,DAT_000311cc,0);
      if (iVar1 != 0) {
        FUN_000340ec();
      }
      if (*DAT_000311d4 == '\0') {
        FUN_0001c5d2(DAT_000311d4,0x2000,0xff);
      }
    }
    return CONCAT26(uStack_12,
                    CONCAT15(local_13,CONCAT14(local_14,CONCAT13(local_15,CONCAT12(local_16,CONCAT11
                                                  (local_17,local_18))))));
  }
  uVar2 = FUN_000312ec(DAT_0003132c);
  return uVar2;
}

