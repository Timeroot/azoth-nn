// FUN_00031b28 @00031b28 size=340

void FUN_00031b28(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 local_28;
  undefined4 local_24;
  
  puVar1 = DAT_00031c7c;
  iVar4 = 0;
  iVar5 = 0;
  iVar6 = 0;
  iVar3 = 0;
  *DAT_00031c7c = 0;
  local_28 = param_3;
  local_24 = param_4;
  if (param_2 == 0) {
    if (param_1 == 0) {
      do {
        local_24 = CONCAT13(local_24._3_1_,*(undefined3 *)(iVar4 * 3 + param_3));
        FUN_0002829c(local_24,&local_28);
        puVar1[iVar3 + 1] = local_28._2_1_;
        puVar1[iVar3 + 2] = local_28._1_1_;
        iVar5 = iVar5 + 1;
        puVar1[iVar3 + 3] = (undefined1)local_28;
        if (iVar5 < 6) {
          iVar3 = iVar3 + 0x1e;
        }
        else {
          iVar3 = iVar6 + 3;
          iVar5 = 0;
          iVar6 = iVar3;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x3c);
      return;
    }
    if (param_1 == 1) goto LAB_00031bc0;
    if (param_1 == 2) {
      uVar2 = 0;
      goto LAB_00031c76;
    }
    if (param_1 != 3) {
      return;
    }
    uVar2 = 0xb5;
  }
  else {
    if (param_2 != 1) {
      return;
    }
    if (param_1 == 0) {
      do {
        local_24 = CONCAT13(local_24._3_1_,*(undefined3 *)(iVar4 * 3 + param_3));
        FUN_0002829c(local_24,&local_28);
        puVar1[iVar3 + 1] = local_28._2_1_;
        puVar1[iVar3 + 2] = local_28._1_1_;
        iVar5 = iVar5 + 1;
        puVar1[iVar3 + 3] = (undefined1)local_28;
        if (iVar5 < 3) {
          iVar3 = iVar3 + 0x1e;
        }
        else {
          iVar3 = iVar6 + 3;
          iVar5 = 0;
          iVar6 = iVar3;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x1e);
      iVar5 = 0;
      iVar3 = 0x5a;
      iVar6 = 0x5a;
      iVar4 = 0;
      do {
        local_24 = CONCAT13(local_24._3_1_,*(undefined3 *)(iVar4 * 3 + param_3 + 0x5a));
        FUN_0002829c(local_24,&local_28);
        puVar1[iVar3 + 1] = local_28._2_1_;
        puVar1[iVar3 + 2] = local_28._1_1_;
        iVar5 = iVar5 + 1;
        puVar1[iVar3 + 3] = (undefined1)local_28;
        if (iVar5 < 9) {
          iVar3 = iVar3 + 9;
        }
        else {
          iVar3 = iVar6 + 3;
          iVar5 = 0;
          iVar6 = iVar3;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x1b);
      return;
    }
    if (param_1 == 1) {
LAB_00031bc0:
      FUN_0002987c();
      return;
    }
    if (param_1 == 2) {
      uVar2 = 1;
LAB_00031c76:
      FUN_00029864(uVar2,0);
      return;
    }
    if (param_1 != 3) {
      return;
    }
    uVar2 = 0xac;
  }
  FUN_00029704(DAT_00031c7c,uVar2,0x30);
  return;
}

