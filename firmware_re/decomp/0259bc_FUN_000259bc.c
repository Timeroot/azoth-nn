// @0x259bc  size=178

void FUN_000259bc(void)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  
  *DAT_00025a74 = DAT_00025a70;
  FUN_0002994c(0);
  iVar2 = DAT_00025a7c;
  puVar1 = DAT_00025a78;
  uVar3 = 0;
  do {
    *puVar1 = (char)uVar3;
    *(char *)(iVar2 + uVar3 * 0x18) = (char)uVar3;
    FUN_00039ca4(uVar3 & 0xff,0);
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < 3);
  *puVar1 = 0;
  FUN_00029eac(DAT_00025a78,0);
  iVar2 = FUN_0003e38c();
  if (iVar2 != 0) {
    FUN_0003e2a0();
    do {
      iVar2 = FUN_0003e38c();
    } while (iVar2 != 0);
  }
  disableIRQinterrupts();
  FUN_0003df58(&DAT_000e7000);
  FUN_0003df58(&DAT_000e8000);
  FUN_0003df58(&DAT_000e9000);
  FUN_0003df58(&DAT_000ea000);
  FUN_0003df58(&DAT_000eb000);
  FUN_0003df58(&DAT_000ec000);
  FUN_0003df58(&DAT_000ed000);
  FUN_0003df58(&DAT_000ee000);
  FUN_0003df58(&DAT_000ef000);
  FUN_0003df58(0xf0000);
  FUN_0003df58(&DAT_000f1000);
  FUN_0003df58(&DAT_000f2000);
  enableIRQinterrupts();
  return;
}

