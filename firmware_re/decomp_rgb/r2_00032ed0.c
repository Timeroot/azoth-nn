// FUN_00032ed0 @00032ed0 size=154

void FUN_00032ed0(void)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar2 = DAT_00032f84;
  uVar3 = *DAT_00032f6c;
  if (-1 < (int)(uVar3 << 0x1d)) {
    pcVar1 = DAT_00032f74;
    if (*(int *)(DAT_00032f70 + 0x30) == 0) {
      uVar4 = *(uint *)(DAT_00032f74 + 0x14);
      uVar5 = *(byte *)(DAT_00032f78 + 0x2b9) & 7;
      if (uVar4 == 0) {
        uVar4 = (uint)*(ushort *)(DAT_00032f7c + uVar5 * 2);
      }
      if (((*(char *)(DAT_00032f80 + 6) != -0x57) && (*(int *)(DAT_00032f84 + 0x10) == 0)) &&
         (uVar5 < 5)) {
        uVar5 = *(int *)(DAT_00032f74 + 0x10) + 1;
        *(uint *)(DAT_00032f74 + 0x10) = uVar5;
        if (uVar4 <= uVar5) {
          pcVar1[0x10] = '\0';
          pcVar1[0x11] = '\0';
          pcVar1[0x12] = '\0';
          pcVar1[0x13] = '\0';
          *(undefined4 *)(iVar2 + 0x5c) = 1;
          FUN_0002cf24();
          FUN_000277cc(s_E_I_M_00032f88);
          return;
        }
        if ((uVar3 & 1) != 0) {
          if (uVar5 < uVar4 - 1) {
            if ((char)(*DAT_00032f74 * -0x80) == '\0') {
              uVar3 = 5;
              goto LAB_00032f58;
            }
          }
          else if ((char)(*DAT_00032f74 * -0x80) != '\0') {
            uVar3 = 0;
LAB_00032f58:
            *DAT_00032f74 = (char)uVar3;
            FUN_0003362c(0x81,3,0,uVar3 >> 1);
            return;
          }
        }
      }
    }
    else {
      pcVar1[0x10] = '\0';
      pcVar1[0x11] = '\0';
      pcVar1[0x12] = '\0';
      pcVar1[0x13] = '\0';
    }
  }
  return;
}

