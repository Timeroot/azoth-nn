// FUN_00030494 @00030494 size=244

int FUN_00030494(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined1 local_18;
  undefined3 uStack_17;
  undefined4 local_14;
  
  pcVar1 = DAT_00030598;
  iVar3 = DAT_00030590;
  if (*(int *)(DAT_00030590 + 0x60) == 0) {
    return 8;
  }
  _local_18 = CONCAT31((int3)((uint)param_3 >> 8),0xa1);
  local_14 = DAT_00030594;
  switch(DAT_00030598[4]) {
  case '\x01':
    iVar3 = FUN_0003d350();
    if (iVar3 == 0) {
      return 0;
    }
    iVar3 = FUN_0003d498(0x50);
    if (iVar3 != 0) {
      return iVar3;
    }
    iVar3 = FUN_0003d3ec(&local_14);
    if (iVar3 != 0) {
      return iVar3;
    }
    iVar3 = FUN_0003d434(&local_18,1);
    if (iVar3 != 0) {
      return iVar3;
    }
    pcVar1[5] = '\0';
    cVar2 = '\x02';
    goto LAB_00030508;
  case '\x02':
    iVar3 = FUN_0003d350();
    if (iVar3 == 0) {
      return 0;
    }
    cVar2 = '\x03';
    pcVar1[0x1c] = '\0';
    pcVar1[0x1d] = '\0';
    pcVar1[0x1e] = '\0';
    pcVar1[0x1f] = '\0';
    goto LAB_00030516;
  case '\x03':
    iVar3 = *(int *)(DAT_00030598 + 0x1c);
    *(int *)(DAT_00030598 + 0x1c) = iVar3 + 1;
    if (iVar3 + 1 < 200) {
      return 0;
    }
    cVar2 = '\x01';
    goto LAB_00030508;
  case '\x04':
    iVar3 = FUN_0003d350();
    if (iVar3 == 0) {
      return 0;
    }
    cVar2 = '\x05';
    pcVar1[0x1c] = '\0';
    pcVar1[0x1d] = '\0';
    pcVar1[0x1e] = '\0';
    pcVar1[0x1f] = '\0';
LAB_00030516:
    pcVar1[4] = cVar2;
    FUN_000303a4();
    break;
  case '\x05':
    FUN_00039df4(0);
    FUN_000303a4();
    pcVar1[0x30] = '\0';
    pcVar1[0x31] = '\0';
    pcVar1[0x32] = '\0';
    pcVar1[0x33] = '\0';
    *pcVar1 = '\0';
    cVar2 = '\x06';
LAB_00030508:
    pcVar1[4] = cVar2;
    break;
  case '\x06':
    if (*DAT_00030598 == '\0') {
      iVar3 = *(int *)(DAT_00030598 + 0x20);
      *(uint *)(DAT_00030598 + 0x20) = iVar3 + 1U;
      if (0x13 < iVar3 + 1U) {
        FUN_00030450();
        pcVar1[0x20] = '\0';
        pcVar1[0x21] = '\0';
        pcVar1[0x22] = '\0';
        pcVar1[0x23] = '\0';
      }
      pcVar1[0x24] = '\0';
      pcVar1[0x25] = '\0';
      pcVar1[0x26] = '\0';
      pcVar1[0x27] = '\0';
    }
    else {
      iVar3 = *(int *)(DAT_00030598 + 0x24);
      *(uint *)(DAT_00030598 + 0x24) = iVar3 + 1U;
      if (4 < iVar3 + 1U) {
        pcVar1[0x24] = '\0';
        pcVar1[0x25] = '\0';
        pcVar1[0x26] = '\0';
        pcVar1[0x27] = '\0';
        pcVar1[4] = '\a';
      }
      pcVar1[0x20] = '\0';
      pcVar1[0x21] = '\0';
      pcVar1[0x22] = '\0';
      pcVar1[0x23] = '\0';
    }
    break;
  case '\a':
    iVar4 = FUN_0003d350();
    if (iVar4 != 0) {
      FUN_000305be(DAT_0003059c,0x30);
      FUN_00039df4(1);
      FUN_0003d500();
      if (*(char *)(DAT_0003059c + 0x20) == '\x01') {
        *DAT_000305a0 = 0x3b;
      }
      *(undefined4 *)(iVar3 + 0x60) = 0;
      pcVar1[4] = '\0';
      FUN_000325c0();
    }
  }
  return 0;
}

