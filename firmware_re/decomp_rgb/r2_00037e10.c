// FUN_00037e10 @00037e10 size=246

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00037e10(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  
  iVar2 = _DAT_00037f08;
  uVar5 = 0;
  do {
    FUN_000285ec(1,_DAT_00037f08);
    if ((*(char *)(iVar2 + 6) == -0x57) || (*(char *)(iVar2 + 6) == '\0')) goto LAB_00037e44;
    uVar5 = uVar5 + 1;
  } while (uVar5 < 3);
  FUN_0002778c();
  FUN_000277cc(s_ForcedLeave_DemoMode_00037f0b + 1);
  *(undefined1 *)(iVar2 + 6) = 0;
  FUN_0002778c(0);
LAB_00037e44:
  piVar3 = DAT_00037f28;
  cVar1 = *(char *)(iVar2 + 6);
  if (*(int *)(DAT_00037f24 + 0x18) != 0) {
    iVar6 = 0;
    uVar5 = 0;
    do {
      FUN_0002b0b8(0xf,2);
      if (((((*piVar3 == 0) && (piVar3[1] == 0)) && (piVar3[2] == 0x400)) &&
          ((piVar3[3] == 0 && (piVar3[4] == 0)))) && ((piVar3[5] == 0x400 && (piVar3[6] == 0)))) {
        iVar6 = iVar6 + 1;
        if (iVar6 == 3000) {
          if (*(char *)(iVar2 + 6) == -0x57) {
            *(undefined1 *)(iVar2 + 6) = 0;
          }
          else {
            *(undefined1 *)(iVar2 + 6) = 0xa9;
          }
          FUN_00028698(1,_DAT_00037f08);
          break;
        }
      }
      else {
        iVar6 = 0;
        if (99 < uVar5) break;
      }
      FUN_0002cbd0(1);
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0xc1c);
  }
  if (*(char *)(iVar2 + 6) == -0x57) {
    FUN_0002d5cc(0,1000,0);
  }
  if ((cVar1 != '\0') && (*(char *)(iVar2 + 6) != -0x57)) {
    *DAT_00037f2c = 1;
    FUN_000277cc(s_D_2_N_00037f30);
  }
  FUN_0002778c(*(undefined1 *)(iVar2 + 6));
  if (*(char *)(iVar2 + 6) == -0x57) {
    pcVar4 = s_Demo_Mode_00037f44;
  }
  else {
    pcVar4 = s_Normal_Mode_00037f38;
  }
  FUN_000277cc(pcVar4);
  return;
}

