// FUN_00027c50 @00027c50 size=84

uint FUN_00027c50(byte *param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  
  bVar1 = param_1[3];
  if (bVar1 < 0x40) {
    sVar2 = (ushort)bVar1 * -4 + 0x100;
  }
  else {
    sVar2 = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  param_1[3] = bVar1 + 1;
  return (uint)param_1 & 0xff000000 |
         param_2 * ((uint)((int)(short)(ushort)*param_1 * (int)sVar2) >> 8) >> 7 & 0xff |
         (param_2 * ((uint)((int)(short)(ushort)param_1[1] * (int)sVar2) >> 8) >> 7 & 0xff) << 8 |
         (param_2 * ((uint)((int)(short)(ushort)param_1[2] * (int)sVar2) >> 8) >> 7 & 0xff) << 0x10;
}

