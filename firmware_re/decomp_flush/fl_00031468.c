
void FUN_00031468(int param_1,undefined1 param_2)

{
  if (DAT_00031480 == param_1) {
    *(undefined1 *)(DAT_00031484 + 2) = param_2;
  }
  else if (DAT_00031480 + 0x10 == param_1) {
    *(undefined1 *)(DAT_00031484 + 3) = param_2;
    return;
  }
  return;
}

