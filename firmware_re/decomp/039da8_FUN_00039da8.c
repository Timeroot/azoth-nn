// @0x39da8  size=18

undefined1 FUN_00039da8(void)

{
  int iVar1;
  
  iVar1 = DAT_00039dbc;
  if (*(char *)(DAT_00039dbc + 9) < '\0') {
    *(char *)(DAT_00039dbc + 9) = -*(char *)(DAT_00039dbc + 9);
  }
  return *(undefined1 *)(iVar1 + 9);
}

