// @0x44cd8  size=24

short FUN_00044cd8(int param_1,uint param_2)

{
  short sVar1;
  uint uVar2;
  
  sVar1 = 0;
  for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
    sVar1 = sVar1 + (ushort)*(byte *)(param_1 + uVar2);
  }
  return sVar1;
}

