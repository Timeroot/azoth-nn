
void FUN_0002d2e0(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  
  iVar2 = DAT_0002d498;
  puVar6 = (ushort *)(DAT_0002d498 + -0x62);
  iVar8 = *(int *)(DAT_0002d498 + 0x28) + 1;
  *(int *)(DAT_0002d498 + 0x28) = iVar8;
  iVar3 = DAT_0002d49c;
  uVar1 = *puVar6;
  uVar5 = (uint)uVar1;
  if (9999 < iVar8) {
    *(undefined4 *)(iVar2 + 0x28) = 0;
    *(undefined1 *)(iVar2 + -0x6a) = 1;
    if ((uVar5 & 1) != (uint)*(byte *)(iVar2 + -0x75)) {
      *(char *)(iVar2 + -0x75) = (char)(uVar5 & 1);
    }
    if (*(char *)(iVar3 + 9) != *(char *)(iVar2 + -0x74)) {
      *(bool *)(iVar2 + -0x74) = *(char *)(iVar3 + 9) != '\0';
    }
    if (*(uint *)(iVar2 + 0x38) != (uint)(uVar1 >> 3)) {
      *(uint *)(iVar2 + 0x38) = (uint)(uVar1 >> 3);
    }
  }
  iVar4 = DAT_0002d4a4;
  iVar8 = DAT_0002d4a0;
  if ((uVar1 & 1) != 0) {
    if (*(char *)(iVar2 + -0x72) == '\0') {
      if ((int)(uVar5 << 0x1d) < 0) {
        FUN_00031710();
      }
      else if (-1 < (int)(uVar5 << 0x1e)) {
        if (*DAT_0002d4a8 == '\0') {
          iVar8 = *(int *)(iVar2 + 0x24) + 1;
          *(int *)(iVar2 + 0x24) = iVar8;
          if (9 < iVar8) {
            *(undefined1 *)(iVar2 + -0x7d) = 1;
            goto LAB_0002d38c;
          }
        }
        else {
LAB_0002d38c:
          *(undefined4 *)(iVar2 + 0x24) = 0;
        }
        if ((*(byte *)(iVar2 + -0x48) & 0x3f) == 0) {
          if ((*(byte *)(iVar2 + -0x44) & 7) == 0) {
            if ((uVar1 >> 3 == 0) || ((*(byte *)(DAT_0002d498 + -0x7f) & 0x18) != 0)) {
              FUN_0002e810();
              FUN_0002e9e8();
              if (*(char *)(iVar2 + -0x6a) != '\0') {
                if (*(int *)(iVar2 + 0x2c) != *(int *)(iVar2 + -0x34)) {
                  *(int *)(iVar2 + 0x2c) = *(int *)(iVar2 + -0x34);
                }
                if (*(uint *)(iVar2 + 0x30) != (uint)*(ushort *)(iVar2 + -0x68)) {
                  *(uint *)(iVar2 + 0x30) = (uint)*(ushort *)(iVar2 + -0x68);
                }
                if (*(int *)(iVar2 + 0x34) != *(int *)(iVar2 + -0x54)) {
                  *(int *)(iVar2 + 0x34) = *(int *)(iVar2 + -0x54);
                }
              }
            }
            else if (uVar1 >> 3 == 1) {
              FUN_0002f238();
            }
            else if ((uVar1 >> 3 == 2) && (*(char *)(iVar2 + -0x6e) != '\0')) {
              FUN_0002f5b0();
            }
          }
          else {
            FUN_0002f0fc();
          }
        }
        else {
          FUN_0002e664();
        }
      }
    }
    else if (*(char *)(iVar2 + -0x71) != '\0') {
      iVar7 = 0;
      do {
        *(byte *)(iVar4 + iVar7) =
             (*(byte *)(iVar8 + iVar7) >> 5) << 4 |
             (byte)(((uint)*(byte *)(iVar8 + iVar7) << 0x1c) >> 0x1d);
        iVar7 = iVar7 + 1;
      } while (iVar7 < 0x2000);
      *(undefined1 *)(iVar2 + -0x7e) = 1;
      *(undefined1 *)(iVar2 + -0x71) = 0;
    }
    if ((*(byte *)(iVar2 + -0x7e) & ~*(byte *)(iVar2 + -0x6f)) != 0) {
      *(undefined1 *)(iVar2 + -0x6f) = 1;
      *(undefined1 *)(iVar2 + -0x7e) = 0;
      *(undefined4 *)(iVar2 + 0x70) = 0;
    }
    FUN_0002e5e4();
  }
  if ((*(byte *)(iVar3 + 9) == (*(byte *)puVar6 & 1)) || (iVar8 = FUN_00029fd4(), iVar8 != 0))
  goto LAB_0002d482;
  iVar8 = *(int *)(iVar2 + -0x30);
  if (iVar8 < 500) {
    if (iVar8 == 300) {
      FUN_0002e544();
      goto LAB_0002d47a;
    }
    if (iVar8 == 0) {
      if (*(char *)(iVar3 + 9) == '\0') {
        FUN_0002e544();
      }
      else {
        FUN_0002e584();
        *(undefined4 *)(iVar2 + -0x44) = 7;
        FUN_0002e274(0x3f);
        if (*(char *)(iVar3 + 9) == -1) {
          *(undefined1 *)(iVar3 + 9) = 1;
        }
      }
      *puVar6 = *puVar6 & 0xfffe | *(byte *)(iVar3 + 9) & 1;
      goto LAB_0002d47a;
    }
  }
  else {
    FUN_0002d254();
LAB_0002d47a:
    iVar8 = *(int *)(iVar2 + -0x30);
    if (iVar8 == 0) goto LAB_0002d482;
  }
  *(int *)(iVar2 + -0x30) = iVar8 + -1;
LAB_0002d482:
  if (*DAT_0002d4ac != 0) {
    *DAT_0002d4ac = *DAT_0002d4ac + -1;
  }
  if (*(char *)(iVar2 + -0x6a) != '\0') {
    *(undefined1 *)(iVar2 + -0x6a) = 0;
  }
  return;
}

