// FUN_00032f90 @00032f90 size=38

void FUN_00032f90(void)

{
  if (*(int *)(DAT_00032fb8 + 0x18) == 0) {
    if (*(char *)(DAT_00032fbc + 1) != *DAT_00032fc0) {
      *(char *)(DAT_00032fbc + 1) = *DAT_00032fc0;
      FUN_0002fc80();
      FUN_0002b45c();
      return;
    }
  }
  return;
}

