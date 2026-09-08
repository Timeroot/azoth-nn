
void FUN_000315b8(void)

{
  int iVar1;
  int iVar2;
  
  FUN_0003dc00(0x15);
  FUN_0003ca98(1);
  FUN_0003de84(0x15);
  FUN_0003ca98(1);
  FUN_0003de84(4);
  FUN_0003ca98(10);
  iVar2 = 0;
  do {
    iVar1 = FUN_00031624(DAT_0003161c,0x1e);
    if (iVar1 == 0) break;
    FUN_0002cbd0(10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  iVar2 = 0;
  do {
    iVar1 = FUN_00031658(DAT_00031620,0x2000);
    if (iVar1 == 0) break;
    FUN_0002cbd0(10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  FUN_00031590();
  return;
}

