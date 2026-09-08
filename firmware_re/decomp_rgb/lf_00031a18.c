// FUN_00031a18 @00031a18 size=88

undefined4 FUN_00031a18(uint param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = DAT_00031a70;
  if (*(char *)(DAT_00031a70 + 3) == '\0') {
LAB_00031a38:
    uVar4 = 0x11;
  }
  else {
    uVar3 = (param_1 & 0xf) - 1;
    *(uint *)(DAT_00031a70 + 0x10) = uVar3;
    iVar2 = DAT_00031a74;
    iVar1 = DAT_00031a70;
    if (uVar3 < 4) {
      iVar6 = iVar5 + 0x18;
      if (*(char *)(iVar6 + uVar3) != '\0') goto LAB_00031a38;
      if (param_3 <= *(byte *)(DAT_00031a74 + uVar3)) {
        *(undefined1 *)(iVar6 + uVar3) = 1;
        FUN_0001c590(*(undefined4 *)(iVar1 + 0x34 + uVar3 * 4),param_2,param_3);
        iVar5 = *(int *)(iVar5 + 0x10);
        FUN_0001c5e0(*(int *)(iVar1 + 0x34 + iVar5 * 4) + param_3,*(byte *)(iVar2 + iVar5) - param_3
                    );
        return 0;
      }
    }
    uVar4 = 7;
  }
  return uVar4;
}

