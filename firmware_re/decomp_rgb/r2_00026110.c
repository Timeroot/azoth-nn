// FUN_00026110 @00026110 size=36

void FUN_00026110(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = DAT_00026138;
  if ((*(int *)(DAT_00026134 + 0x18) != 0) && (*(int *)(DAT_00026134 + 0x34) != 0)) {
    iVar2 = *(int *)(DAT_00026138 + 8);
    *(int *)(DAT_00026138 + 8) = iVar2 + 1;
    if (4 < iVar2 + 1) {
      *(undefined4 *)(puVar1 + 8) = 0;
      *puVar1 = 1;
    }
  }
  return;
}

