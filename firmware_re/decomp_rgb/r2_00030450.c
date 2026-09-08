// FUN_00030450 @00030450 size=54

undefined4 FUN_00030450(void)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(DAT_00030488 + 0x60) != 0) {
    FUN_0003040c(DAT_0003048c,0x30);
    FUN_00030380();
    iVar2 = FUN_00039ebc();
    iVar1 = DAT_00030490;
    if (iVar2 != 0) {
      *(undefined1 *)(DAT_00030490 + 3) = 0;
      FUN_00043748(0);
      *(undefined1 *)(iVar1 + 2) = 0;
    }
    *(undefined1 *)(iVar1 + 4) = 1;
    *(undefined1 *)(iVar1 + 5) = 0;
    FUN_000326e4();
  }
  return 0;
}

