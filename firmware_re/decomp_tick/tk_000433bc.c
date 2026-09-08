
void FUN_000433bc(void)

{
  ushort uVar1;
  ushort *puVar2;
  undefined4 uVar3;
  int iVar4;
  
  FUN_000332f4();
  puVar2 = DAT_0004341c;
  uVar1 = *DAT_0004341c;
  *DAT_0004341c = uVar1 + 1;
  if (4 < (ushort)(uVar1 + 1)) {
    *puVar2 = 0;
    FUN_00033370();
    uVar1 = puVar2[1];
    puVar2[1] = uVar1 + 1;
    if ((uVar1 + 1 & 1) != 0) {
      disableIRQinterrupts();
      *DAT_000332bc = *DAT_000332bc + 10;
      enableIRQinterrupts();
      FUN_00026920();
      FUN_00037fd0();
      FUN_00030494();
      FUN_00029588();
      if (*(char *)(DAT_0002b624 + 2) != '\0') {
        iVar4 = *(int *)(DAT_0002b624 + 8) + -1;
        *(int *)(DAT_0002b624 + 8) = iVar4;
        if (iVar4 == 0) {
          FUN_0002cd9c();
          return;
        }
      }
      return;
    }
    puVar2[1] = 0;
    thunk_FUN_000333f8();
    uVar1 = puVar2[2];
    puVar2[2] = uVar1 + 1;
    if (9 < (ushort)(uVar1 + 1)) {
      puVar2[2] = 0;
      FUN_0003327c();
      uVar1 = puVar2[3];
      puVar2[3] = uVar1 + 1;
      if (9 < (ushort)(uVar1 + 1)) {
        puVar2[3] = 0;
        FUN_00026110();
        uVar3 = FUN_00036f6c(1);
        FUN_0002fd7c(uVar3,1);
        FUN_00032f90();
        FUN_000403a4();
        thunk_FUN_00044f9c(0x54);
        FUN_00038530();
        FUN_0002d590();
        puVar2 = DAT_0002d79c;
        uVar1 = *DAT_0002d79c;
        if (((uVar1 >> 3 == 2) && (*(char *)((int)DAT_0002d79c + -0x15) == '\0')) &&
           (iVar4 = *(int *)(DAT_0002d79c + 0x1d), *(int *)(DAT_0002d79c + 0x1d) = iVar4 + -1,
           iVar4 + -1 == 0)) {
          *puVar2 = uVar1 & 7;
          *(undefined1 *)((int)puVar2 + -0x15) = 1;
        }
        return;
      }
    }
  }
  return;
}

