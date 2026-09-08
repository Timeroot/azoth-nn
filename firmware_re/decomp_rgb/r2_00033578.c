// FUN_00033578 @00033578 size=876

void FUN_00033578(int param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined2 *puVar9;
  uint uVar10;
  uint uVar11;
  undefined1 uVar12;
  uint uVar13;
  uint uVar14;
  uint unaff_r7;
  undefined4 unaff_r11;
  undefined2 local_3c;
  undefined1 uStack_3a;
  undefined2 local_24;
  undefined1 uStack_22;
  
  bVar1 = *(byte *)(param_1 + 0x47);
  uVar10 = (uint)bVar1;
  cVar2 = *(char *)(param_1 + 0x3c);
  if (cVar2 == '\0') {
    uVar11 = 0;
  }
  else {
    uVar11 = *(int *)(DAT_00033628 + 0x10) + 1;
  }
  *(uint *)(DAT_00033628 + 0x10) = uVar11;
  *(char *)(param_1 + 0x3c) = cVar2 + '\x01';
  if ((byte)(cVar2 + 1U) < *(byte *)(param_1 + 6)) goto switchD_000335a6_default;
  *(undefined1 *)(param_1 + 0x3c) = 0;
  switch(*(undefined1 *)(param_1 + 0x1b)) {
  case 0:
  case 1:
  case 7:
  case 8:
    *(byte *)(param_1 + 0x47) = bVar1 - 1;
    if (uVar10 != 0) goto switchD_000335a6_default;
    uVar12 = 0x14;
    break;
  case 2:
    *(byte *)(param_1 + 0x47) = bVar1 - 1;
    if (uVar10 != 0) goto switchD_000335a6_default;
    uVar12 = 0x11;
    break;
  case 3:
  case 4:
  case 5:
    *(byte *)(param_1 + 0x47) = bVar1 + 1;
    if (uVar10 < 0x14) goto switchD_000335a6_default;
    goto LAB_000335d0;
  case 6:
    *(byte *)(param_1 + 0x47) = bVar1 + 1;
    if (uVar10 < 0x11) goto switchD_000335a6_default;
LAB_000335d0:
    *(undefined1 *)(param_1 + 0x47) = 0;
  default:
    goto switchD_000335a6_default;
  }
  *(undefined1 *)(param_1 + 0x47) = uVar12;
switchD_000335a6_default:
  iVar3 = DAT_00027f84;
  iVar6 = DAT_00027eec;
  iVar7 = DAT_00027e48;
  switch(*(undefined1 *)(param_1 + 0x1b)) {
  case 0:
  case 4:
    uVar13 = 0;
    break;
  case 1:
  case 3:
  case 5:
  case 7:
    uVar11 = uVar11 & 0xff;
    iVar7 = 1;
LAB_00027cba:
    iVar3 = 0;
    iVar6 = iVar7;
    do {
      iVar7 = FUN_0003ba16(iVar6,0x10 - iVar3,6);
      iVar4 = param_1 + uVar10 * 4;
      cVar2 = *(char *)(param_1 + 0x1b);
      if (cVar2 == '\x01') {
LAB_00027cec:
        if (uVar10 != 0) {
          unaff_r11 = *(undefined4 *)(iVar4 + 0x45a);
          goto LAB_00027d06;
        }
        unaff_r11 = *(undefined4 *)(param_1 + 0x4ae);
        uVar10 = 1;
      }
      else {
        if ((cVar2 == '\x03') || (cVar2 == '\x05')) {
          if (uVar10 != 0x14) {
            unaff_r11 = *(undefined4 *)(iVar4 + 0x462);
            goto LAB_00027d06;
          }
          unaff_r11 = *(undefined4 *)(param_1 + 0x45e);
        }
        else {
          if (cVar2 == '\a') goto LAB_00027cec;
LAB_00027d06:
          uVar10 = uVar10 + 1;
          if ((int)uVar10 < 0x15) goto LAB_00027d0e;
        }
        uVar10 = 0;
      }
LAB_00027d0e:
      uVar8 = FUN_000271e8(unaff_r11,*(undefined4 *)(iVar4 + 0x45e),uVar11);
      for (iVar4 = 0; iVar4 < iVar7; iVar4 = iVar4 + 1) {
        cVar2 = *(char *)(param_1 + 0x1b);
        if (cVar2 == '\x01') {
LAB_00027d36:
          iVar5 = FUN_0003ba0e(6,iVar6);
          uVar13 = (iVar5 - iVar4) - 1;
LAB_00027d52:
          uVar13 = uVar13 & 0xff;
        }
        else {
          if (cVar2 == '\x03') {
LAB_00027d44:
            iVar5 = FUN_0003ba0e(6,iVar6);
            uVar13 = 6 - (iVar5 - iVar4);
            goto LAB_00027d52;
          }
          if (cVar2 == '\x05') goto LAB_00027d36;
          uVar13 = unaff_r7;
          if (cVar2 == '\a') goto LAB_00027d44;
        }
        uVar14 = iVar3 + iVar4 & 0xff;
        unaff_r7 = uVar13 & 0xffff00ff;
        iVar5 = FUN_0002b5e0(param_1,*(undefined4 *)(DAT_00027db0 + 0x6c),4,uVar13 & 0xff,uVar14);
        if (iVar5 == 0) {
          puVar9 = (undefined2 *)(uVar14 * 3 + (uVar13 & 0xff) * 0x30 + *(int *)(param_1 + 0xe0));
          local_3c = (undefined2)uVar8;
          *puVar9 = local_3c;
          uStack_3a = (undefined1)((uint)uVar8 >> 0x10);
          *(undefined1 *)(puVar9 + 1) = uStack_3a;
        }
      }
      iVar7 = iVar6 + 1;
      if (0x15 < iVar7) {
        return;
      }
      if (iVar6 + -5 < 0) goto LAB_00027cba;
      iVar3 = iVar6 + -5;
      iVar6 = iVar7;
    } while( true );
  case 2:
  case 6:
    uVar13 = 0;
    do {
      iVar7 = param_1 + uVar10 * 4;
      if (*(char *)(param_1 + 0x1b) == '\x02') {
        if (uVar10 != 0) {
          uVar8 = *(undefined4 *)(iVar7 + 0x45a);
          goto LAB_00027f16;
        }
        uVar8 = *(undefined4 *)(param_1 + 0x4a2);
        uVar10 = 1;
      }
      else {
        if (uVar10 == 0x11) {
          uVar8 = *(undefined4 *)(param_1 + 0x45e);
        }
        else {
          uVar8 = *(undefined4 *)(iVar7 + 0x462);
LAB_00027f16:
          uVar10 = uVar10 + 1;
          if ((int)uVar10 < 0x12) goto LAB_00027f1e;
        }
        uVar10 = 0;
      }
LAB_00027f1e:
      uVar8 = FUN_000271e8(uVar8,*(undefined4 *)(iVar7 + 0x45e),uVar11 & 0xff);
      uVar14 = 0;
      do {
        iVar7 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar3 + 0x6c),4,uVar13 & 0xff,uVar14 & 0xff);
        if (iVar7 == 0) {
          puVar9 = (undefined2 *)(uVar14 * 3 + uVar13 * 0x30 + *(int *)(param_1 + 0xe0));
          local_24 = (undefined2)uVar8;
          *puVar9 = local_24;
          uStack_22 = (undefined1)((uint)uVar8 >> 0x10);
          *(undefined1 *)(puVar9 + 1) = uStack_22;
        }
        uVar14 = uVar14 + 1;
      } while ((int)uVar14 < 0x10);
      uVar13 = uVar13 + 1;
      if (5 < (int)uVar13) {
        return;
      }
    } while( true );
  case 8:
    uVar13 = 0;
    do {
      iVar7 = param_1 + uVar10 * 4;
      if (uVar10 == 0) {
        uVar8 = *(undefined4 *)(param_1 + 0x4ae);
        uVar10 = 1;
      }
      else {
        uVar8 = *(undefined4 *)(iVar7 + 0x45a);
        uVar10 = uVar10 + 1;
        if (0x14 < (int)uVar10) {
          uVar10 = 0;
        }
      }
      uVar8 = FUN_000271e8(uVar8,*(undefined4 *)(iVar7 + 0x45e),uVar11 & 0xff);
      uVar14 = 0;
      do {
        iVar7 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar6 + 0x6c),4,uVar14 & 0xff,uVar13 & 0xff);
        if (iVar7 == 0) {
          puVar9 = (undefined2 *)(uVar13 * 3 + 0x18 + *(int *)(param_1 + 0xe0) + uVar14 * 0x30);
          local_24 = (undefined2)uVar8;
          *puVar9 = local_24;
          uStack_22 = (undefined1)((uint)uVar8 >> 0x10);
          *(undefined1 *)(puVar9 + 1) = uStack_22;
          puVar9 = (undefined2 *)((7 - uVar13) * 3 + uVar14 * 0x30 + *(int *)(param_1 + 0xe0));
          *puVar9 = local_24;
          *(undefined1 *)(puVar9 + 1) = uStack_22;
        }
        uVar14 = uVar14 + 1;
      } while ((int)uVar14 < 6);
      uVar13 = uVar13 + 1;
    } while ((int)uVar13 < 8);
    return;
  default:
    FUN_000271c0();
    return;
  }
  do {
    iVar6 = param_1 + uVar10 * 4;
    if (*(char *)(param_1 + 0x1b) == '\0') {
      if (uVar10 != 0) {
        uVar8 = *(undefined4 *)(iVar6 + 0x45a);
        goto LAB_00027dd8;
      }
      uVar8 = *(undefined4 *)(param_1 + 0x4ae);
      uVar10 = 1;
    }
    else {
      if (uVar10 == 0x14) {
        uVar8 = *(undefined4 *)(param_1 + 0x45e);
      }
      else {
        uVar8 = *(undefined4 *)(iVar6 + 0x462);
LAB_00027dd8:
        uVar10 = uVar10 + 1;
        if ((int)uVar10 < 0x15) goto LAB_00027de0;
      }
      uVar10 = 0;
    }
LAB_00027de0:
    uVar8 = FUN_000271e8(uVar8,*(undefined4 *)(iVar6 + 0x45e),uVar11 & 0xff);
    uVar14 = 0;
    do {
      iVar6 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar7 + 0x6c),4,uVar14 & 0xff,uVar13 & 0xff);
      if (iVar6 == 0) {
        puVar9 = (undefined2 *)(uVar13 * 3 + uVar14 * 0x30 + *(int *)(param_1 + 0xe0));
        *puVar9 = (short)uVar8;
        *(char *)(puVar9 + 1) = (char)((uint)uVar8 >> 0x10);
      }
      uVar14 = uVar14 + 1;
    } while ((int)uVar14 < 6);
    uVar13 = uVar13 + 1;
    if (0xf < (int)uVar13) {
      return;
    }
  } while( true );
}

