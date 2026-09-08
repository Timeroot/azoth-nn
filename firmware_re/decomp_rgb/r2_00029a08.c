// FUN_00029a08 @00029a08 size=60

void FUN_00029a08(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  FUN_000293e0();
  iVar3 = FUN_0002613c();
  iVar2 = DAT_00029a48;
  iVar1 = DAT_00029a44;
  if (iVar3 == 0) {
    *(undefined4 *)(DAT_00029a44 + 0x34) = 0;
    *(undefined1 *)(iVar2 + 1) = 0;
    FUN_00029534(DAT_00029a4c);
  }
  else {
    *(undefined4 *)(DAT_00029a44 + 0x34) = 1;
    *(undefined1 *)(iVar2 + 1) = 1;
  }
  FUN_0002778c(*(uint *)(iVar1 + 0x34) & 0xff);
  FUN_0002778c(*(undefined1 *)(iVar2 + 1));
  FUN_000277cc(s__CHG_Init_00029a50);
  return;
}

