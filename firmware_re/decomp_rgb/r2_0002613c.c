// FUN_0002613c @0002613c size=122

undefined4 FUN_0002613c(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 in_r3;
  int iVar4;
  undefined4 local_14;
  
  iVar4 = 0;
  local_14 = CONCAT22((short)((uint)in_r3 >> 0x10),0x1a01);
  do {
    iVar2 = FUN_000297a4(DAT_000261b8,0x6b,&local_14,2,0);
    if (iVar2 == 0) {
      local_14 = 0;
      iVar2 = FUN_000260e0(0xb,&local_14,1);
      puVar1 = DAT_000261c4;
      if (iVar2 == 0) {
        if ((local_14 & 0x7f) >> 3 != 9) {
          return 0;
        }
        if (*(int *)(DAT_000261bc + 0x18) != 0) {
          if (*DAT_000261c0 == '\0') {
            if (*(int *)(DAT_000261bc + 0x14) == 0) {
              puVar3 = DAT_000261c4 + 0x15;
            }
            else {
              puVar3 = DAT_000261c4 + 0xc;
            }
            *(undefined1 **)(DAT_000261c4 + 4) = puVar3;
          }
          else {
            **(undefined4 **)(DAT_000261c4 + 4) = *(undefined4 *)(DAT_000261c4 + 0x1e);
          }
          *puVar1 = 1;
          FUN_00037ce0(0);
        }
        return 1;
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 3);
  return 0;
}

