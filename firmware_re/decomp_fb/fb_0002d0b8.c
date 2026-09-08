
void FUN_0002d0b8(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  byte *pbVar4;
  int iVar5;
  
  pbVar4 = DAT_0002d138;
  piVar3 = DAT_0002d134;
  piVar2 = DAT_0002d130;
  piVar1 = DAT_0002d12c;
  while( true ) {
    if (*piVar2 == 0 && piVar2[1] == 0) break;
    disableIRQinterrupts();
    *piVar1 = *piVar2;
    piVar1[1] = piVar2[1];
    *piVar2 = 0;
    piVar2[1] = 0;
    enableIRQinterrupts();
    if (*piVar1 == 0) {
      if ((piVar1[1] != 0) &&
         (((*piVar3 == 1 || (-1 < (int)((uint)*pbVar4 << 0x1d))) &&
          (iVar5 = FUN_0002b0b8(0xf,1), iVar5 != 0)))) {
        FUN_000336b4(0,0,1);
        FUN_0002aa10();
        FUN_00029bcc();
        FUN_00026d18();
        FUN_000269c4();
      }
    }
    else {
      FUN_000433bc();
    }
  }
  FUN_0002330c();
  return;
}

