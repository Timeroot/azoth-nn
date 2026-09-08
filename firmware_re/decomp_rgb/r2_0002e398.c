// FUN_0002e398 @0002e398 size=198

void FUN_0002e398(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int *piVar7;
  undefined4 local_44 [2];
  undefined1 auStack_3c [28];
  
  iVar3 = DAT_0002e468;
  iVar2 = DAT_0002e464;
  iVar1 = DAT_0002e460;
  if (*(int *)(DAT_0002e460 + 0x58) != 0) {
    *(undefined4 *)(DAT_0002e464 + 0x14) = 0;
    *(uint *)(iVar3 + 0x6c) = *(uint *)(iVar3 + 0x6c) & 0xfffffffe;
  }
  piVar7 = (int *)(DAT_0002e464 + 0x8c);
  if (*(int *)(iVar1 + 0x58) != 0) {
    *piVar7 = 0xff;
    *(uint *)(iVar3 + 0x6c) = *(uint *)(iVar3 + 0x6c) & 0xfffffffd;
  }
  FUN_0002d1e4();
  iVar4 = FUN_0002cbea(*DAT_0002e46c,local_44);
  FUN_0002cbb4(local_44[0],iVar4,auStack_3c);
  auStack_3c[iVar4] = 0x25;
  uVar6 = iVar4 + 1;
  if (*(int *)(iVar1 + 0x14) == 0) {
    uVar5 = 0xe;
  }
  else {
    uVar5 = 0xd;
  }
  FUN_0002e500(uVar5,0x1e,0xc);
  if (((*(int *)(iVar1 + 0x58) != 0) && (uVar6 < 0x12)) &&
     (*(uint *)(iVar2 + 0x14) = uVar6, uVar6 != 0)) {
    FUN_0001c590(DAT_0002e464,auStack_3c);
    *(undefined4 *)(iVar2 + 0x18) = 0x32;
    *(undefined4 *)(iVar2 + 0x1c) = 0x18;
  }
  if (*(int *)(iVar1 + 0x58) != 0) {
    if (*piVar7 != 0xff) {
      *(uint *)(iVar3 + 0x6c) = *(uint *)(iVar3 + 0x6c) | 2;
    }
    if (*(int *)(iVar2 + 0x14) != 0) {
      *(uint *)(iVar3 + 0x6c) = *(uint *)(iVar3 + 0x6c) | 1;
    }
    *(undefined4 *)(DAT_0002e468 + -0x3c) = 0;
  }
  return;
}

