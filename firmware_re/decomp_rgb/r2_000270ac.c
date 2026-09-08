// FUN_000270ac @000270ac size=172

void FUN_000270ac(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_0003dabe(0x20,3);
  FUN_0003dabe(0x21,3);
  FUN_0003dabe(0x22,3);
  FUN_0003dabe(0x23,3);
  FUN_0003dabe(0x24,3);
  FUN_0003e8c4(0xf);
  iVar2 = FUN_0003ddfc(0x20);
  iVar3 = FUN_0003ddfc(0x21);
  iVar4 = FUN_0003ddfc(0x22);
  iVar1 = DAT_00027158;
  *(uint *)(DAT_00027158 + 8) =
       (uint)(iVar2 == 0) | (uint)(iVar3 == 0) << 1 | (uint)(iVar4 == 0) << 2;
  iVar2 = FUN_0003ddfc(0x23);
  iVar3 = FUN_0003ddfc(0x24);
  *(uint *)(iVar1 + 0xc) = (uint)(iVar2 == 0) | (uint)(iVar3 == 0) << 1;
  FUN_0003da40(0x20);
  FUN_0003da40(0x21);
  FUN_0003da40(0x22);
  FUN_0003da40(0x23);
  FUN_0003da40(0x24);
  return;
}

