// FUN_0002fd7c @0002fd7c size=148

void FUN_0002fd7c(uint param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  char *pcVar3;
  
  iVar1 = DAT_0002fe10;
  if ((param_1 & 1) != 0) {
    *(undefined4 *)(DAT_0002fe10 + 0x4c) = 2;
    FUN_0003362c(0x81,2,0);
  }
  puVar2 = DAT_0002fe14;
  if ((int)(param_1 << 0x1e) < 0) {
    if (param_2 == 0) {
      *DAT_0002fe14 = *DAT_0002fe14 | 1;
      FUN_00027838(2,DAT_0002fe18);
    }
    else {
      *DAT_0002fe14 = *DAT_0002fe14 | 3;
    }
  }
  pcVar3 = DAT_0002fe18;
  if (((*puVar2 & 1) != 0) && (DAT_0002fe14[4] == 1)) {
    *puVar2 = *puVar2 & 0xfffffffe;
    FUN_0003362c(0x81,2,1,*pcVar3);
  }
  if ((((int)((uint)(byte)*puVar2 << 0x1e) < 0) && (*(char *)(DAT_0002fe1c + 1) == '\0')) &&
     (*DAT_0002fe20 == '\0')) {
    FUN_00027838(2,DAT_0002fe18);
    *puVar2 = *puVar2 & 0xfffffffd;
  }
  if ((*pcVar3 == '\0') && (*(int *)(iVar1 + 0x18) == 0)) {
    *(undefined4 *)(iVar1 + 0x2c) = 1;
  }
  return;
}

