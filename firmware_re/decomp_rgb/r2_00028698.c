// FUN_00028698 @00028698 size=206

void FUN_00028698(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iVar8;
  
  if (*(int *)(DAT_00028768 + 0x30) != 0) {
    if (param_1 != 2) {
      FUN_00038614();
    }
    FUN_00031320(1);
    FUN_000396c8(100);
    FUN_000395b0(1);
    pcVar2 = DAT_0002876c;
    cVar1 = *DAT_0002876c;
    if (cVar1 != '\0') {
      uVar6 = (uint)*(ushort *)(DAT_00028770 + param_1 * 2);
      iVar8 = 0x1000;
      if (cVar1 == '\x01') {
        iVar3 = 0;
      }
      else {
        iVar3 = 0x1000;
      }
      uVar4 = iVar3 + (uint)*(ushort *)(DAT_0002876c + param_1 * 2 + 2) *
                      (uint)*(ushort *)(DAT_0002876c + param_1 * 2 + 8) + uVar6;
      if (cVar1 == '\x01') {
        iVar8 = 0;
      }
      if (((uVar6 + (*(ushort *)(DAT_00028770 + param_1 * 2 + 2) - uVar6 & 0xffff) + iVar8) -
          (uint)*(ushort *)(DAT_0002876c + param_1 * 2 + 8)) - 1 < uVar4) {
        uVar5 = FUN_00028de8();
        puVar7 = (undefined1 *)(DAT_00028774 + -8);
        *(undefined4 *)(DAT_00028774 + -4) = uVar5;
        FUN_00028698(param_1,param_2,0);
        *puVar7 = 1;
      }
      else {
        FUN_0003974c(uVar4,param_2);
        FUN_0001c590(*(undefined4 *)(DAT_00028774 + param_1 * 4),param_2,
                     *(undefined2 *)(pcVar2 + param_1 * 2 + 8));
        *(short *)(pcVar2 + param_1 * 2 + 2) = *(short *)(pcVar2 + param_1 * 2 + 2) + 1;
      }
    }
    if ((param_3 != 0) && (iVar8 = FUN_00029fd4(), iVar8 == 0)) {
      FUN_00039540(1);
      FUN_00031320(0);
      return;
    }
  }
  return;
}

