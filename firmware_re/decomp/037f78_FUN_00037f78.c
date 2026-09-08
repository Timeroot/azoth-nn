// @0x37f78  size=46

void FUN_00037f78(void)

{
  int iVar1;
  uint uVar2;
  uint in_r3;
  uint local_10;
  
  iVar1 = DAT_00037fa8;
  if (*(int *)(DAT_00037fa8 + 0x30) != 0) {
    local_10 = in_r3;
    FUN_00027a68(0,&local_10,1);
    uVar2 = FUN_00029358();
    if (((local_10 & 0xff) < uVar2) &&
       (uVar2 = (uint)*(byte *)(DAT_00037fac + (local_10 & 0xff)), uVar2 != *(uint *)(iVar1 + 8))) {
      *(uint *)(iVar1 + 8) = uVar2;
    }
  }
  return;
}

