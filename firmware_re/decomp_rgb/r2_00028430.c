// FUN_00028430 @00028430 size=330

void FUN_00028430(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  ushort uVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 local_28;
  
  pcVar2 = DAT_0002857c;
  pcVar2[8] = ' ';
  pcVar2[9] = '\0';
  pcVar2[10] = '\v';
  iVar5 = DAT_00028580;
  pcVar2[0xb] = '\0';
  pcVar2[0xc] = '\x01';
  pcVar2[0xd] = '\0';
  if (*(int *)(iVar5 + 0x30) == 0) {
    return;
  }
  local_28 = param_4;
  FUN_00031320(1);
  FUN_000396c8(100);
  FUN_000395b0(1);
  FUN_00039584(0,&local_28,1);
  FUN_00039584(0x1000,(int)&local_28 + 1,1);
  uVar3 = local_28 & 0xff;
  if ((uVar3 == 0xff) || (uVar3 == 0)) {
    if ((local_28._1_1_ == -1) || (local_28._1_1_ == '\0')) {
      if (param_1 == 0) {
        FUN_0003979c();
        FUN_00039650(0);
        FUN_000396c8(400);
        FUN_0003979c();
        FUN_00039650(0x1000);
        FUN_000396c8(400);
      }
      uVar3 = 0;
      *pcVar2 = '\x01';
      do {
        iVar5 = uVar3 * 2;
        uVar3 = uVar3 + 1 & 0xffff;
        (pcVar2 + iVar5 + 2)[0] = '\0';
        (pcVar2 + iVar5 + 2)[1] = '\0';
      } while (uVar3 < 3);
      goto LAB_00028520;
    }
    *pcVar2 = '\x02';
    if (uVar3 != 0xff) {
      FUN_0003979c();
      uVar4 = 0;
      goto LAB_000284b0;
    }
  }
  else {
    *pcVar2 = '\x01';
    if (local_28._1_1_ != -1) {
      FUN_0003979c();
      uVar4 = 0x1000;
LAB_000284b0:
      FUN_00039650(uVar4);
      FUN_000396c8(400);
    }
  }
  iVar5 = DAT_00028584;
  uVar3 = 0;
  do {
    if (*pcVar2 == '\x01') {
      iVar7 = 0;
    }
    else {
      iVar7 = 0x1000;
    }
    uVar6 = (uint)*(ushort *)(iVar5 + uVar3 * 2);
    uVar1 = *(ushort *)(iVar5 + uVar3 * 2 + 2);
    iVar7 = iVar7 + uVar6;
    for (uVar8 = 0; uVar8 < uVar1 - uVar6; uVar8 = uVar8 + 1 & 0xffff) {
      FUN_00039584(iVar7,&local_28,1);
      if ((char)local_28 == -1) {
        *(short *)(pcVar2 + uVar3 * 2 + 2) = (short)uVar8;
        break;
      }
      iVar7 = iVar7 + (uint)*(ushort *)(pcVar2 + uVar3 * 2 + 8);
    }
    uVar3 = uVar3 + 1 & 0xffff;
  } while (uVar3 < 3);
  FUN_00039584(0x10000,DAT_0002857c + 0xe,0x18);
LAB_00028520:
  iVar5 = FUN_00029fd4();
  if (iVar5 == 0) {
    FUN_00039540(1);
    FUN_00031320(0);
  }
  return;
}

