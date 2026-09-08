// FUN_00029ff8 @00029ff8 size=34

undefined4 FUN_00029ff8(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if (((DAT_0002a01c == param_1) && (*DAT_0002a020 == '\0')) ||
     ((DAT_0002a01c + 0x10 == param_1 && (DAT_0002a020[1] == '\0')))) {
    uVar1 = 0;
  }
  return uVar1;
}

