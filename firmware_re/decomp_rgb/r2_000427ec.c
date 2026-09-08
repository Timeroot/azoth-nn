// FUN_000427ec @000427ec size=52

void FUN_000427ec(void)

{
  uint in_r3;
  uint local_10;
  
  if (*(int *)(DAT_00042820 + 0x30) != 0) {
    local_10 = in_r3;
    FUN_000285ec(2,&local_10);
    if ((local_10 & 0xff) != 0xff) {
      if (100 < (local_10 & 0xff)) {
        local_10 = 100;
      }
      goto LAB_00042810;
    }
  }
  local_10 = 0x32;
LAB_00042810:
  *DAT_00042824 = (undefined1)local_10;
  return;
}

