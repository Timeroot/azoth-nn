// @0x3f148 size=356

undefined4 FUN_0003f148(int *param_1,byte *param_2,int param_3,int param_4)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  
  piVar8 = (int *)(DAT_0003f2ac + (uint)*(byte *)(param_1 + 1) * 0x24);
  if ((char)piVar8[7] == '\0') {
    iVar3 = *param_1;
    iVar4 = FUN_0003ec5c(iVar3,*(undefined4 *)(DAT_0003f2b0 + (uint)*(byte *)(param_1 + 1) * 4),
                         DAT_0003f2b0,param_4,param_3,param_4);
    if (iVar4 == 0) {
      *piVar8 = param_3;
      piVar8[1] = param_4;
      if (param_2[0xc] < 2) {
        FUN_0003dc28();
      }
      else {
        FUN_0003dee8(*param_2);
      }
      uVar2 = 0;
      FUN_0003d9d8(*param_2,1,0,0,0,0);
      uVar5 = (uint)param_2[1];
      if (uVar5 == 0xff) {
        uVar5 = 0xffffffff;
      }
      else {
        FUN_0003dc28();
        FUN_0003db1c(uVar5);
      }
      uVar6 = (uint)param_2[2];
      uVar7 = 0xffffffff;
      if (uVar6 != 0xff) {
        FUN_0003d9d8(uVar6,0,0,1,0,0);
        uVar7 = uVar6;
      }
      *(byte *)(piVar8 + 8) = param_2[2];
      *(byte *)((int)piVar8 + 0x1f) = param_2[3];
      if (param_2[3] != 0xff) {
        if (param_2[4] == 0) {
          FUN_0003dee8();
        }
        else {
          FUN_0003dc28();
        }
        FUN_0003db1c(param_2[3]);
        *(byte *)((int)piVar8 + 0x1e) = param_2[4];
      }
      *(uint *)(iVar3 + 0x508) = (uint)*param_2;
      *(uint *)(iVar3 + 0x50c) = uVar5;
      *(uint *)(iVar3 + 0x510) = uVar7;
      *(undefined4 *)(iVar3 + 0x524) = *(undefined4 *)(param_2 + 8);
      bVar1 = param_2[0xc];
      uVar5 = (uint)(param_2[0xd] != 0);
      if (bVar1 == 1) {
        uVar5 = uVar5 | 2;
      }
      else if (bVar1 == 2) {
        uVar5 = uVar5 | 4;
      }
      else if (bVar1 == 3) {
        uVar5 = uVar5 | 6;
      }
      *(uint *)(iVar3 + 0x554) = uVar5;
      *(uint *)(iVar3 + 0x5c0) = (uint)param_2[6];
      *(undefined4 *)(iVar3 + 0x500) = 7;
      if (*piVar8 != 0) {
        uVar5 = (*param_1 << 0xc) >> 0x18;
        if ((int)uVar5 < 0) {
          *(byte *)((uVar5 & 0xf) + 0xe000ed14) = param_2[5] << 5;
        }
        else {
          (&DAT_e000e400)[uVar5] = param_2[5] << 5;
        }
        uVar5 = (*param_1 << 0xc) >> 0x18;
        if (-1 < (int)uVar5) {
          *(int *)(&DAT_e000e100 + (uVar5 >> 5) * 4) = 1 << (uVar5 & 0x1f);
        }
      }
      *(undefined1 *)((int)piVar8 + 0x1d) = 0;
      *(undefined1 *)(piVar8 + 7) = 1;
    }
    else {
      uVar2 = 0x11;
    }
  }
  else {
    uVar2 = 8;
  }
  return uVar2;
}

