// FUN_0003b760 @0003b760 size=476

void FUN_0003b760(void)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  iVar4 = FUN_0003423c();
  if (iVar4 != 0) {
    FUN_000340ec();
  }
  iVar4 = FUN_00042f40();
  if (iVar4 != 0) {
    FUN_000340ec();
  }
  iVar4 = FUN_00035760();
  if (iVar4 != 0) {
    FUN_000340ec();
  }
  iVar4 = FUN_000293cc();
  if (iVar4 != 0) {
    FUN_000340ec();
  }
  FUN_0003a0d4();
  FUN_00044e58();
  FUN_000270ac();
  FUN_00028fe8();
  FUN_0002949c(0x1a,0x1b);
  FUN_0002cb78();
  iVar4 = FUN_0003e010();
  if (iVar4 != 0) {
    FUN_000340ec();
  }
  iVar4 = FUN_000341e4(0x20,0x20,DAT_0003b93c);
  if (iVar4 != 0) {
    FUN_000340ec();
  }
  FUN_00029ad0();
  iVar2 = DAT_0003b948;
  piVar1 = DAT_0003b944;
  iVar4 = DAT_0003b940;
  if ((*(int *)(DAT_0003b940 + 0x10) == 0) && (*(int *)(DAT_0003b940 + 0x18) == 0)) {
    iVar5 = FUN_00037ddc();
    if (iVar5 != 0) {
      if (*piVar1 != iVar2) goto LAB_0003b7d4;
      uVar7 = 0;
      goto LAB_0003b7e6;
    }
    uVar7 = 0;
  }
  else {
LAB_0003b7d4:
    uVar7 = 1;
LAB_0003b7e6:
    *piVar1 = 0;
  }
  *(undefined4 *)(DAT_0003b950 + 4) = DAT_0003b94c;
  iVar5 = FUN_0003cbc0();
  if (iVar5 != 0) {
    FUN_000340ec();
  }
  FUN_0003e864();
  puVar3 = DAT_0003b954;
  iVar5 = DAT_0003b950;
  if ((*DAT_0003b954 & 1) != 0) {
    iVar5 = 0;
  }
  FUN_0003cc58(iVar5);
  if ((int)((uint)(byte)*puVar3 << 0x1d) < 0) {
    FUN_00026ce8();
  }
  if (*(int *)(iVar4 + 0x18) != 0) {
    FUN_000261c8();
    FUN_00029a08();
  }
  if (uVar7 != 0) {
    FUN_0003905c();
    FUN_0002622c();
    FUN_00028d6c();
    FUN_00028430(0);
    FUN_00029cf4();
    FUN_000403b0();
    FUN_000427ec();
    FUN_00029a5c();
    FUN_00037e10();
    FUN_00029ba0();
    FUN_00024e84();
    FUN_00022f18(DAT_0003b958);
    FUN_0003863c();
    FUN_0002fc34();
    FUN_0002627c();
  }
  iVar5 = FUN_0003e38c();
  if (((iVar5 == 0) && (iVar5 = FUN_0003ccac(0), iVar5 != 0)) && (iVar5 != 0x85)) {
    FUN_000340ec();
  }
  FUN_00037fb0();
  FUN_000277a0(DAT_0003b95c);
  if (*DAT_0003b960 == DAT_0003b964) {
    FUN_000277cc(&DAT_0003b968);
    *(undefined4 *)(iVar4 + 0x54) = 1;
    *(undefined4 *)(iVar4 + 0x10) = 1;
    FUN_00045428();
    FUN_000454f0();
  }
  else {
    uVar6 = *puVar3;
    if ((int)(uVar6 << 0x1d) < 0) {
      if (*DAT_0003b970 == iVar2) {
        *DAT_0003b970 = 0;
        *(undefined4 *)(iVar4 + 0x10) = 1;
        FUN_000277cc(s__SiFM_0003b974);
      }
      FUN_000277cc(&DAT_0003b97c);
      FUN_00045428();
      FUN_000454f0();
      goto LAB_0003b914;
    }
    if ((uVar6 & uVar7) != 0) {
      FUN_000277cc(&DAT_0003b984);
      FUN_00025ca4();
      goto LAB_0003b914;
    }
    if ((-1 < (int)(uVar6 << 0x1e)) || (uVar7 == 0)) {
      FUN_000277cc(&DAT_0003b990);
      FUN_0002e544();
      FUN_000308e0(1,0xccd);
      FUN_00042204();
      goto LAB_0003b914;
    }
    FUN_000277cc(&DAT_0003b98c);
  }
  FUN_000305f0();
LAB_0003b914:
  FUN_0003082c();
  FUN_000308e0(0,0x20);
  do {
    FUN_0002d0b8();
    FUN_00045a64();
    if ((*puVar3 & 1) != 0) {
      FUN_00025c90();
    }
    FUN_000341a4();
    FUN_0003e038();
  } while( true );
}

