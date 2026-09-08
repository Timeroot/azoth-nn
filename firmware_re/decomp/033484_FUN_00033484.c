// @0x33484  size=78

void FUN_00033484(undefined1 param_1,undefined1 param_2,undefined2 param_3,undefined4 param_4,
                 uint param_5)

{
  undefined1 local_58;
  undefined1 local_57;
  undefined2 local_56;
  undefined1 auStack_54 [60];
  
  FUN_0001c5e0(&local_58,0x40);
  if (0x3c < param_5) {
    param_5 = 0x3c;
  }
  local_58 = param_1;
  local_57 = param_2;
  local_56 = param_3;
  FUN_0001c590(auStack_54,param_4,param_5);
  if ((int)((uint)*DAT_000334d4 << 0x1d) < 0) {
    FUN_000319a0(0x82,&local_58,0x40,1);
  }
  return;
}

