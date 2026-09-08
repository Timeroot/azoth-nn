// FUN_00032550 @00032550 size=58

void FUN_00032550(uint param_1,uint param_2)

{
  if (*(int *)(DAT_0003258c + 0x48) == 1) {
    param_1 = 0;
  }
  else if (*(int *)(DAT_0003258c + 0x48) == 2) {
    if (0x19 < param_1) {
      param_1 = 0x19;
    }
  }
  else if ((*(char *)(DAT_00032590 + 8) == '\0') && (0x28 < param_1)) {
    param_1 = 0x28;
  }
  if (param_2 < 8) {
    *(char *)(DAT_00032594 + param_2) = (char)((param_1 << 7) / 100);
  }
  return;
}

