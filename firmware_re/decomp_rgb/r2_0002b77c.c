// FUN_0002b77c @0002b77c size=334

void FUN_0002b77c(int param_1)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  byte bVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  
  pbVar3 = DAT_0002b8cc;
  iVar2 = DAT_0002b8c8;
  iVar1 = DAT_0002b8c0;
  uVar6 = *DAT_0002b8c4;
  if (*(int *)(DAT_0002b8c0 + 0x60) != 0) {
    if ((int)(uVar6 << 0x1e) < 0) {
      return;
    }
    if (param_1 == 0xb011) {
      return;
    }
    if (param_1 < 0xb012) {
      if (param_1 == 0xb000) {
        return;
      }
      if (param_1 == 0xb001) {
        return;
      }
      if (param_1 == 0xb002) {
        return;
      }
      if (param_1 == 0xb010) {
        return;
      }
    }
    else {
      if (param_1 == 0xb012) {
        return;
      }
      if (param_1 == 0xb020) {
        return;
      }
      if (param_1 == 0xb021) {
        return;
      }
    }
  }
  iVar8 = param_1 + -0xb012;
  if (param_1 == 0xb012) {
    uVar7 = 2;
LAB_0002b846:
    uVar5 = 1;
  }
  else {
    if (0xb012 < param_1) {
      bVar4 = *DAT_0002b8cc;
      if (iVar8 == 0x1e) {
        if ((uVar6 & 1) == 0) {
          return;
        }
        *DAT_0002b8cc = bVar4 + 1;
        if ((byte)(bVar4 + 1) < 3) goto LAB_0002b86e;
        bVar4 = 2;
      }
      else {
        if (iVar8 < 0x1f) {
          if (iVar8 == 0xe) {
            FUN_0002ba38(1);
            return;
          }
          if (iVar8 != 0xf) {
            return;
          }
          FUN_0002b9c4(1);
          return;
        }
        if (iVar8 != 0x1f) {
          if (iVar8 != 0x20) {
            return;
          }
          if ((int)(uVar6 << 0x1d) < 0) {
            return;
          }
          *(undefined4 *)(DAT_0002b8c8 + 0x14) = 0;
          if (*(int *)(iVar1 + 0x60) != 0) {
            *DAT_0002b8d0 = 1;
            return;
          }
          if ((uVar6 & 7) != 1) {
            if ((uVar6 & 7) != 2) {
              return;
            }
            FUN_0002fb4c();
            FUN_00030450();
            return;
          }
          *DAT_00025b9c = DAT_00025b98;
          FUN_0002cd9c();
          return;
        }
        if ((uVar6 & 1) == 0) {
          return;
        }
        if (bVar4 == 0) goto LAB_0002b86e;
        bVar4 = bVar4 - 1;
      }
      *pbVar3 = bVar4;
LAB_0002b86e:
      FUN_00029eac(DAT_0002b8cc,0);
      FUN_0002e274(8);
      FUN_0002d5cc(*pbVar3 + 3,0xffffffff,0);
      *(undefined1 *)(iVar2 + 2) = 1;
      *(undefined4 *)(iVar2 + 8) = 300;
      return;
    }
    if (param_1 == 0xb002) {
      uVar7 = 2;
    }
    else {
      if (0xb002 < param_1) {
        if (param_1 == 0xb010) {
          uVar7 = 1;
        }
        else {
          if (param_1 != 0xb011) {
            return;
          }
          uVar7 = 0;
        }
        goto LAB_0002b846;
      }
      if (param_1 == 0xb000) {
        uVar7 = 1;
      }
      else {
        if (param_1 != 0xb001) {
          return;
        }
        uVar7 = 0;
      }
    }
    uVar5 = 0;
  }
  FUN_0002b8d4(uVar5,0,uVar7);
  return;
}

