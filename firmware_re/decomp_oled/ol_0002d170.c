// FUN_0002d170 @0002d170 size=28

void FUN_0002d170(void)

{
  int iVar1;
  byte *pbVar2;
  
  FUN_0002d760();
  iVar1 = DAT_0002d18c;
  *(undefined4 *)(DAT_0002d18c + 0x28) = 0;
  *(undefined4 *)(iVar1 + 0x2c) = 2;
  pbVar2 = (byte *)(iVar1 + 1);
  *pbVar2 = *pbVar2 | 1;
  return;
}

