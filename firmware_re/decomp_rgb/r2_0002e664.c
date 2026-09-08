// FUN_0002e664 @0002e664 size=378

void FUN_0002e664(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  iVar2 = DAT_0002e7e4;
  iVar3 = *(int *)(DAT_0002e7e4 + 0x34);
  if (iVar3 != 0) {
    if (iVar3 != 1) {
      if (iVar3 != 6) {
        return;
      }
      uVar5 = *(uint *)(DAT_0002e7e4 + 0x38);
      if ((uVar5 & 0x3f) == 0) {
        return;
      }
      *(undefined4 *)(DAT_0002e7e4 + 0x6c) = 0;
      do {
        if ((1 << (*(uint *)(iVar2 + 0x6c) & 0xff) & uVar5) != 0) {
          *(undefined4 *)(iVar2 + 0x34) = 0;
          return;
        }
        iVar3 = *(uint *)(iVar2 + 0x6c) + 1;
        *(int *)(iVar2 + 0x6c) = iVar3;
      } while (iVar3 < 6);
      return;
    }
    iVar4 = FUN_00029fd4();
    iVar6 = DAT_0002e80c;
    iVar3 = DAT_0002e808;
    if (iVar4 != 0) {
      return;
    }
    uVar5 = *(uint *)(iVar2 + 0x6c);
    iVar4 = 0;
    do {
      puVar8 = (undefined4 *)(iVar6 + (iVar4 + uVar5 * 10) * 0x80);
      puVar7 = (undefined4 *)(iVar3 + iVar4 * 0xc);
      iVar4 = iVar4 + 1;
      *puVar8 = *puVar7;
      puVar8[1] = puVar7[1];
      puVar8[2] = puVar7[2];
    } while (iVar4 < 10);
    *(undefined4 *)(iVar2 + 0x34) = 6;
    uVar5 = *(uint *)(iVar2 + 0x38) & ~(1 << (uVar5 & 0xff));
    *(uint *)(iVar2 + 0x38) = uVar5;
    if ((uVar5 & 0x3f) != 0) {
      return;
    }
    *(undefined1 *)(iVar2 + 2) = 1;
    return;
  }
  if (*(char *)(DAT_0002e7e4 + 3) == '\0') {
    return;
  }
  iVar3 = FUN_00029fd4();
  if (iVar3 != 0) {
    return;
  }
  iVar6 = *(int *)(iVar2 + 0x6c);
  iVar3 = 0xff;
  switch(iVar6) {
  case 0:
  case 1:
    if ((1 << (iVar6 + 1U & 0xff) & (uint)*DAT_0002e7ec) == 0) {
      if (iVar6 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = 3;
      }
    }
    else if (iVar6 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = 2;
    }
    break;
  case 2:
    if (*(byte *)(DAT_0002e7e8 + 6) != 0) {
      iVar3 = *(byte *)(DAT_0002e7e8 + 6) + 3;
      goto switchD_0002e6b6_default;
    }
    iVar3 = 9;
    break;
  case 3:
    if ((*DAT_0002e7f0 & 1) != 0) {
      iVar3 = *DAT_0002e7f4 + 0xc;
      goto switchD_0002e6b6_default;
    }
    if ((int)(*DAT_0002e7f0 << 0x1e) < 0) {
      iVar3 = 0xb;
    }
    else {
      iVar3 = 10;
    }
    break;
  case 4:
    if (*(int *)(DAT_0002e7f8 + 0x18) == 0) {
      if (*(int *)(DAT_0002e7f8 + 0x44) == 0) {
        bVar1 = *DAT_0002e7fc;
        if (bVar1 < 0x5f) {
          if (bVar1 < 0x4b) {
            if (bVar1 < 0x32) {
              if (bVar1 < 0x19) {
                if (bVar1 < 6) {
                  iVar3 = 0x12;
                }
                else {
                  iVar3 = 0x13;
                }
              }
              else {
                iVar3 = 0x14;
              }
            }
            else {
              iVar3 = 0x15;
            }
          }
          else {
            iVar3 = 0x16;
          }
        }
        else {
          iVar3 = 0x17;
        }
      }
      else {
        iVar3 = 0xf;
      }
    }
    else if (*(int *)(DAT_0002e7f8 + 0x14) == 0) {
      iVar3 = 0x10;
    }
    else {
      iVar3 = 0x11;
    }
    break;
  case 5:
    if ((int)((uint)*(byte *)(DAT_0002e800 + (uint)*(byte *)(DAT_0002e7e8 + 6)) << 0x1a) < 0) {
      iVar3 = 0x18;
    }
    else {
      iVar3 = 0x19;
    }
    break;
  default:
switchD_0002e6b6_default:
    *(undefined1 *)(iVar2 + 3) = 0;
    if (iVar3 == 0xff) {
      *(undefined4 *)(iVar2 + 0x34) = 6;
      return;
    }
    goto LAB_0002e76c;
  }
  *(undefined1 *)(iVar2 + 3) = 0;
LAB_0002e76c:
  FUN_000283e0(DAT_0002e804 + iVar3 * 0x7a + 2,DAT_0002e808,0x78);
  *(int *)(iVar2 + 0x34) = *(int *)(iVar2 + 0x34) + 1;
  return;
}

