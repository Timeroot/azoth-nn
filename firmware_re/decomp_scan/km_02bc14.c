// @0x2bc14 size=894

void FUN_0002bc14(void)

{
  char cVar1;
  undefined1 uVar2;
  short sVar3;
  ushort uVar4;
  undefined1 *puVar5;
  undefined3 *puVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  ushort uVar11;
  undefined4 in_r3;
  int iVar12;
  int extraout_r3;
  int iVar13;
  uint uVar14;
  
  iVar9 = DAT_0002bfac;
  puVar5 = DAT_0002bfa8;
  iVar12 = DAT_0002bfa4;
  iVar13 = DAT_0002bfa0;
  iVar8 = *(int *)(DAT_0002bfa0 + 0x30);
  if (iVar8 == 0) {
    return;
  }
  if (iVar8 != 1) {
    if (iVar8 != 2) {
      return;
    }
    cVar1 = *(char *)(DAT_0002bfa0 + -0x24);
    iVar8 = *(int *)(DAT_0002bfa0 + 0x44) + 1;
    switch(*(int *)(DAT_0002bfa0 + 0x38)) {
    case 0:
      *(undefined4 *)(DAT_0002bfa0 + 0x34) = 0;
      FUN_0001c5e0(iVar13,0x18,cVar1,in_r3,in_r3);
      FUN_0001c5e0(DAT_0002bfa0 + 0x18,0x18);
      FUN_0001c5e0(DAT_0002bfa8,0x196);
      *(undefined4 *)(iVar13 + 0x44) = 0;
      *(undefined4 *)(iVar13 + 0x3c) = 0;
      FUN_000323d4();
      break;
    case 1:
      *(int *)(DAT_0002bfa0 + 0x44) = iVar8;
      if (cVar1 == '\0') {
        iVar13 = 0;
        do {
          iVar12 = DAT_0002bfa0 + iVar13 * 2;
          uVar11 = *(ushort *)(DAT_0002bfa0 + iVar13 * 2);
          uVar4 = uVar11 ^ *(ushort *)(iVar12 + 0x18);
          if (uVar4 != 0) {
            uVar14 = 0;
            *(ushort *)(iVar12 + 0x18) = uVar11;
            uVar11 = 1;
            do {
              iVar12 = DAT_0002bfa0;
              if ((uVar4 & uVar11) != 0) {
                uVar7 = uVar14 | iVar13 << 4;
                iVar9 = *(int *)(DAT_0002bfa0 + 0x3c);
                if (iVar9 < 100) {
                  if (iVar9 != 0) {
                    *(undefined2 *)(puVar5 + iVar9 * 4 + 2) = *(undefined2 *)(DAT_0002bfa0 + 0x44);
                  }
                  *(undefined4 *)(iVar12 + 0x44) = 0;
                  puVar5[iVar9 * 4 + 4] = (char)uVar7;
                  if ((*(ushort *)(iVar12 + iVar13 * 2) & uVar11) == 0) {
                    puVar5[iVar9 * 4 + 5] = 1;
                  }
                  else {
                    puVar5[iVar9 * 4 + 5] = 2;
                  }
                  *(int *)(iVar12 + 0x3c) = iVar9 + 1;
                  uVar2 = *(undefined1 *)(DAT_0002bfb8 + uVar7);
                  puVar6 = DAT_0002bfbc;
                }
                else {
                  uVar2 = *(undefined1 *)(DAT_0002bfb8 + uVar7);
                  puVar6 = DAT_0002bfc0;
                }
                FUN_000324a4(*puVar6,uVar2);
              }
              uVar11 = uVar11 << 1;
              uVar14 = uVar14 + 1;
            } while ((int)uVar14 < 0x10);
          }
          iVar13 = iVar13 + 1;
        } while (iVar13 < 0xc);
      }
      if (*(int *)(DAT_0002bfa0 + 0x44) < 0x4e21) {
        return;
      }
      *(undefined4 *)(DAT_0002bfa0 + 0x38) = 4;
      return;
    case 2:
      iVar12 = *(int *)(DAT_0002bfa0 + 0x3c);
      *(undefined2 *)(DAT_0002bfa8 + iVar12 * 4 + 2) = 0;
      puVar5[3] = (char)iVar12;
      FUN_000323f4();
      uVar14 = 0;
      do {
        uVar7 = (uint)*(ushort *)(iVar9 + uVar14 * 2 + 0xca);
        puVar6 = DAT_0002bfc0;
        if (uVar7 == 0xa0d3) {
          uVar7 = uVar14 & 0xff;
LAB_0002bec6:
          FUN_000324a4(*puVar6,uVar7);
        }
        else {
          if (uVar7 - 0xa000 < 0x1000) {
            uVar7 = (uint)*(byte *)(DAT_0002bfb8 + (uVar7 & 0xff));
            goto LAB_0002bec6;
          }
          if (uVar7 != uVar14) {
            uVar7 = uVar14 & 0xff;
            puVar6 = DAT_0002bfc4;
            goto LAB_0002bec6;
          }
        }
        uVar14 = uVar14 + 1;
      } while ((int)uVar14 < 0xf7);
      *(undefined4 *)(iVar13 + 0x44) = 0;
      break;
    case 3:
      *(int *)(DAT_0002bfa0 + 0x44) = iVar8;
      if (cVar1 == '\0') {
        iVar12 = 0;
        do {
          iVar8 = iVar13 + iVar12 * 2;
          sVar3 = *(short *)(iVar13 + iVar12 * 2);
          if (sVar3 != *(short *)(iVar8 + 0x18)) {
            uVar14 = 0;
            *(short *)(iVar8 + 0x18) = sVar3;
            uVar11 = 1;
            do {
              if (((((*(ushort *)(iVar13 + iVar12 * 2) & uVar11) != 0) &&
                   (uVar7 = uVar14 | iVar12 << 4, uVar7 != 0x5a)) &&
                  ((uVar7 != 0x1e && (((uVar7 != 0x7d && (uVar7 != 0x3b)) && (uVar7 != 0x3c)))))) &&
                 (uVar7 != 0x9f)) {
                uVar10 = uVar7 & 0xff;
                *puVar5 = (char)uVar7;
                if (*(int *)(iVar13 + 0x3c) == 0) {
                  uVar7 = (uint)*(byte *)(DAT_0002bfb8 + uVar10);
                  iVar12 = iVar9 + uVar7 * 2;
                  if ((*(ushort *)(iVar12 + 0xca) & 0xa000) != 0) goto LAB_0002bf54;
                }
                else {
                  puVar5[1] = 1;
                  iVar12 = DAT_0002bfb8;
                  puVar5[2] = 0;
                  uVar7 = uVar10 | 0xa000;
                  iVar12 = iVar9 + (uint)*(byte *)(iVar12 + uVar10) * 2;
LAB_0002bf54:
                  *(short *)(iVar12 + 0xca) = (short)uVar7;
                }
                FUN_0002bfc8();
                *(undefined4 *)(iVar13 + 0x38) = 4;
                *(undefined4 *)(iVar13 + 0x44) = 0;
                iVar12 = extraout_r3;
              }
              uVar11 = uVar11 << 1;
              uVar14 = uVar14 + 1;
            } while ((int)uVar14 < 0x10);
          }
          iVar12 = iVar12 + 1;
        } while (iVar12 < 10);
      }
      if (*(int *)(iVar13 + 0x44) < 0x4e21) {
        return;
      }
      goto LAB_0002bd88;
    case 4:
      *(undefined4 *)(DAT_0002bfa0 + 0x30) = 0;
      *(undefined4 *)(iVar13 + 0x38) = 0;
      FUN_000271c0();
      FUN_0002b684(*(undefined1 *)(iVar12 + 5));
      FUN_0002d710();
      return;
    default:
      goto switchD_0002bc50_default;
    }
    goto LAB_0002bcc6;
  }
  if (((DAT_0002bfa8[1] == '\x04') && (*(char *)(DAT_0002bfa0 + 0x48) == '\0')) &&
     (*(int *)(DAT_0002bfa0 + 0x38) < 4)) {
    *(undefined4 *)(DAT_0002bfa0 + 0x38) = 5;
    FUN_000277cc(s_MR_SD_M_0002bfb0);
  }
  switch(*(undefined4 *)(iVar13 + 0x38)) {
  case 0:
    iVar9 = FUN_00029fd4();
    if (iVar9 != 0) {
      return;
    }
    FUN_000283e0((uint)*(byte *)(iVar12 + 6) * 0x80000 + *(int *)(iVar13 + 0x34) * 0x1000 + 0x20000,
                 DAT_0002bfa8,0x196);
    break;
  case 1:
    iVar12 = FUN_00029fd4();
    if (iVar12 != 0) {
      return;
    }
    uVar14 = FUN_00044cd8(puVar5 + 4,puVar5[3]);
    if (*(ushort *)(puVar5 + 0x194) != uVar14) {
      *(undefined4 *)(iVar13 + 0x30) = 0;
      goto LAB_0002bcd6;
    }
    *(undefined4 *)(iVar13 + 0x3c) = 0;
    break;
  case 2:
    uVar14 = (uint)(byte)puVar5[*(int *)(iVar13 + 0x3c) * 4 + 4];
    if (0xbc < uVar14) {
      if (uVar14 < 0xea) {
        uVar14 = uVar14 - 0x40;
      }
      else {
        uVar14 = uVar14 - 0x46;
      }
    }
    if ((puVar5[*(int *)(iVar13 + 0x3c) * 4 + 5] & 0xf) == 1) {
      uVar11 = *(ushort *)(iVar13 + (uVar14 >> 4) * 2) & ~(ushort)(1 << (uVar14 & 0xf));
    }
    else {
      if ((puVar5[*(int *)(iVar13 + 0x3c) * 4 + 5] & 0xf) != 2) goto LAB_0002bd28;
      uVar11 = *(ushort *)(iVar13 + (uVar14 >> 4) * 2) | (ushort)(1 << (uVar14 & 0xf));
    }
    *(ushort *)(iVar13 + (uVar14 >> 4) * 2) = uVar11;
LAB_0002bd28:
    iVar12 = *(int *)(iVar13 + 0x3c);
    uVar11 = *(ushort *)(puVar5 + iVar12 * 4 + 6);
    *(int *)(iVar13 + 0x3c) = iVar12 + 1;
    *(uint *)(iVar13 + 0x40) = (uint)uVar11;
    *(undefined4 *)(iVar13 + 0x44) = 0;
    *(int *)(iVar13 + 0x38) = *(int *)(iVar13 + 0x38) + 1;
    return;
  case 3:
    iVar12 = *(int *)(iVar13 + 0x44) + 1;
    *(int *)(iVar13 + 0x44) = iVar12;
    if (iVar12 < *(int *)(iVar13 + 0x40)) {
      return;
    }
    if (*(int *)(iVar13 + 0x3c) < (int)(uint)(byte)puVar5[3]) {
      *(undefined4 *)(iVar13 + 0x38) = 2;
      return;
    }
    FUN_0001c5e0(DAT_0002bfa0,0x18);
    cVar1 = puVar5[1];
    if (cVar1 == '\x02') {
      cVar1 = puVar5[2];
      puVar5[2] = cVar1 + -1;
      if (cVar1 != '\x01') goto LAB_0002bd82;
    }
    else if ((cVar1 == '\x03') || (cVar1 == '\x04')) {
LAB_0002bd82:
      *(undefined4 *)(iVar13 + 0x38) = 2;
      *(undefined4 *)(iVar13 + 0x3c) = 0;
      return;
    }
    goto LAB_0002bd88;
  case 4:
    *(undefined4 *)(iVar13 + 0x30) = 0;
    *(undefined4 *)(iVar13 + 0x34) = 0;
LAB_0002bcd6:
    *(undefined4 *)(iVar13 + 0x38) = 0;
    *puVar5 = 0;
    puVar5[3] = 0;
    return;
  case 5:
    FUN_0001c5e0(DAT_0002bfa0,0x18);
LAB_0002bd88:
    *(undefined4 *)(iVar13 + 0x38) = 4;
    return;
  default:
    goto switchD_0002bc50_default;
  }
LAB_0002bcc6:
  *(int *)(iVar13 + 0x38) = *(int *)(iVar13 + 0x38) + 1;
switchD_0002bc50_default:
  return;
}

