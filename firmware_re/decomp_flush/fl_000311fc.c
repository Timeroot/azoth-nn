
void FUN_000311fc(void)

{
  int iVar1;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined4 local_18;
  undefined1 local_14;
  undefined1 local_13;
  
  if (*DAT_00031284 == 0) {
    local_1c = 6;
    local_1d = 0xff;
    local_1b = 0xff;
    local_1e = 0xff;
    local_1f = 0x12;
    local_18 = 0x80000000;
    local_14 = 3;
    local_20 = 0x11;
    local_13 = 0;
    iVar1 = FUN_0003ce08(DAT_0003128c,&local_20,DAT_00031288,0);
    if (iVar1 != 0) {
      FUN_000340ec();
    }
    FUN_0003d848(0x11,1,0,0,3,0);
    FUN_0003d848(0x12,1,1,0,3,0);
    if (*DAT_00031290 == '\0') {
      FUN_0001c5d2(DAT_00031290,0x2000,0xff);
    }
  }
  return;
}

