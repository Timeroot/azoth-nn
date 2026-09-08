
void FUN_00031590(void)

{
  int iVar1;
  undefined4 in_r3;
  int iVar2;
  undefined1 local_10;
  undefined3 uStack_f;
  
  _local_10 = CONCAT31((int3)((uint)in_r3 >> 8),0xaf);
  FUN_00033558();
  iVar2 = 0;
  do {
    iVar1 = FUN_00031624(&local_10,1);
    if (iVar1 == 0) {
      return;
    }
    FUN_0002cbd0(10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  return;
}

