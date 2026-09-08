// @0x29a88  size=54

void FUN_00029a88(void)

{
  int iVar1;
  
  iVar1 = DAT_00029ac4;
  if ((*DAT_00029ac0 & 1) != 0) {
    if (2 < *(byte *)(DAT_00029ac4 + 7)) {
      *(undefined1 *)(DAT_00029ac4 + 7) = 0;
      FUN_00027838(1,iVar1);
    }
    FUN_0002778c(*(undefined1 *)(iVar1 + 7));
    FUN_000277cc(&DAT_00029ac8);
  }
  FUN_0003e8c4(1000);
  return;
}

