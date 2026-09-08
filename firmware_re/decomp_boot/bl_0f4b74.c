// @0xf4b74

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000f4b74(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = _DAT_10000134;
  iVar2 = _DAT_10000130;
  if (_DAT_10000130 == 8) {
    _DAT_4000010c = 0;
    _DAT_40000110 = 0;
    *DAT_000f4d58 = 0;
    puVar1 = DAT_000f4d60;
    *DAT_000f4d60 = *DAT_000f4d5c;
    puVar1[1] = *DAT_000f4d64;
    puVar1[2] = *DAT_000f4d68;
    puVar1[3] = *DAT_000f4d6c;
    puVar1[4] = *DAT_000f4d70;
    puVar1[5] = *DAT_000f4d74;
    puVar1 = DAT_000f4d7c;
    *DAT_000f4d7c = *DAT_000f4d78;
    puVar1[1] = *DAT_000f4d80;
    puVar1[2] = *DAT_000f4d84;
    puVar1[3] = *DAT_000f4d88;
    puVar1[4] = *DAT_000f4d8c;
    puVar1[5] = *DAT_000f4d90;
    puVar1 = DAT_000f4d98;
    *DAT_000f4d98 = *DAT_000f4d94;
    puVar1[1] = *DAT_000f4d9c;
    puVar1[2] = *DAT_000f4da0;
    puVar1[3] = *DAT_000f4da4;
    puVar1[4] = *DAT_000f4da8;
  }
  if (iVar2 == 8 && uVar3 == 0) {
    *DAT_000f4db0 = DAT_000f4dac;
    *DAT_000f4db4 = 0xfb;
    *DAT_000f4db8 = *DAT_000f4db8 & 0xfffffff0 | DAT_10000258 & 0xf;
    *DAT_000f4dbc = 0x200;
  }
  if ((iVar2 == 8) && ((*DAT_000f4dc0 & 1) != 0)) {
    *DAT_000f4dc0 = 0xfffffffe;
  }
  *DAT_000f4dc4 = *DAT_000f4dc4 | 0xf00000;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  if ((_DAT_10000130 == 8) && (4 < _DAT_10000134)) {
    *DAT_000f4dc8 = _DAT_10001208;
  }
  if ((_DAT_1000120c & 1) != 0) {
    *DAT_000f4dcc = 1;
    do {
    } while (*DAT_000f4dd0 == 0);
    do {
    } while (*DAT_000f4dd0 == 0);
    *DAT_000f4dcc = 0;
    do {
    } while (*DAT_000f4dd0 == 0);
    DataSynchronizationBarrier(0xf);
    *DAT_000f4dd4 = *DAT_000f4dd4 & 0x700 | DAT_000f4dd8;
    DataSynchronizationBarrier(0xf);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *DAT_000f4de0 = DAT_000f4ddc;
  return;
}

