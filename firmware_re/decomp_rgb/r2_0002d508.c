// FUN_0002d508 @0002d508 size=124

void FUN_0002d508(void)

{
  ushort uVar1;
  ushort *puVar2;
  
  puVar2 = DAT_0002d584;
  if ((*DAT_0002d584 & 1) == 0) {
    FUN_0002e544();
  }
  else {
    FUN_000311fc();
    if (*(int *)(DAT_0002d588 + 0x18) == 0) {
      *puVar2 = *puVar2 & 0xfffe;
      puVar2[0x19] = 500;
      puVar2[0x1a] = 0;
    }
    else {
      FUN_00031590();
    }
    FUN_000312ec(DAT_0002d58c);
    if ((*puVar2 & 1) != 0) {
      puVar2[0xf] = 7;
      puVar2[0x10] = 0;
      FUN_0002e274(0x3f);
    }
    uVar1 = *puVar2;
    if (uVar1 >> 3 == 1) {
      FUN_0002e1d4(0);
    }
    else if (uVar1 >> 3 == 2) {
      FUN_0002e1b4();
    }
    else if (uVar1 >> 3 == 0) {
      puVar2[-3] = 0;
      puVar2[0x17] = 0;
      puVar2[0x18] = 0;
    }
  }
  puVar2 = DAT_0002d584;
  puVar2[0x69] = 0;
  puVar2[0x6a] = 0;
  return;
}

