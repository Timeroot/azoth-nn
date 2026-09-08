// FUN_0003a0f0 @0003a0f0 size=182

void FUN_0003a0f0(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_18;
  
  if ((param_2 == 0) || (param_2 == 1)) {
    return;
  }
  if (param_2 != 2) {
    if (param_2 != 3) {
      return;
    }
    local_18 = 0;
    FUN_00034fce(param_1,&local_18);
    return;
  }
  piVar2 = *(int **)(param_1 + 0x20);
  pcVar1 = (char *)*piVar2;
  local_18 = param_4;
  if (*pcVar1 == '{') {
    if (((((pcVar1[1] == -0x56) && (pcVar1[2] == 'A')) && (pcVar1[3] == 'S')) &&
        ((pcVar1[4] == 'U' && (pcVar1[5] == 'S')))) && (pcVar1[6] == -0x56)) {
      FUN_0002a058();
    }
    iVar3 = 1;
    do {
      FUN_0002778c(*(undefined1 *)(*piVar2 + iVar3));
      iVar3 = iVar3 + 1;
    } while (iVar3 < 7);
    pcVar1 = s__boot_0003a1a8;
  }
  else {
    if (*pcVar1 != '|') {
      FUN_00024e98(pcVar1,0x40);
      goto LAB_0003a124;
    }
    if (((pcVar1[1] == -0x56) && (pcVar1[2] == 'D')) &&
       ((pcVar1[3] == 'T' && ((pcVar1[4] == 'M' && (pcVar1[5] == -0x56)))))) {
      FUN_0002a090();
    }
    iVar3 = 1;
    do {
      FUN_0002778c(*(undefined1 *)(*piVar2 + iVar3));
      iVar3 = iVar3 + 1;
    } while (iVar3 < 6);
    pcVar1 = &LAB_0003a1b0;
  }
  FUN_000277cc(pcVar1);
LAB_0003a124:
  local_18 = 0;
  FUN_00034fda(param_1,&local_18);
  return;
}

