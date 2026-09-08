// FUN_00028778 @00028778 size=1434

void FUN_00028778(void)

{
  ushort uVar1;
  byte *pbVar2;
  char *pcVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint in_r3;
  bool bVar9;
  uint local_28;
  
  iVar6 = DAT_00028b68;
  pbVar2 = DAT_00028b64;
  if (*DAT_00028b64 == 0) {
    return;
  }
  local_28 = in_r3;
  if ((*(int *)(DAT_00028b68 + 0x30) == 0) && (FUN_0003905c(), *(int *)(iVar6 + 0x30) == 0)) {
    if (*pbVar2 == 3) {
      FUN_0001c5d2(*(undefined4 *)(pbVar2 + 4),*(undefined4 *)(pbVar2 + 0x10),0xff);
    }
    *pbVar2 = 0;
    pbVar2[0x18] = 2;
    return;
  }
  pcVar3 = DAT_00028b6c;
  bVar4 = *pbVar2;
  if (bVar4 != 0x36) {
    if (0x36 < bVar4) {
      if (bVar4 != 0x52) {
        if (bVar4 == 199) {
          switch(pbVar2[8]) {
          case 0:
            goto switchD_000287c6_caseD_0;
          case 1:
            goto switchD_000287c6_caseD_1;
          case 2:
            goto switchD_000287c6_caseD_2;
          case 3:
switchD_000288f0_caseD_3:
            goto switchD_00028c36_caseD_3;
          case 4:
            if (*DAT_00028b6c != '\0') {
              return;
            }
            FUN_000395f0();
            goto LAB_00028cac;
          case 5:
switchD_000288f0_caseD_5:
            if (*DAT_00028b6c != '\0') {
switchD_000287c6_caseD_0:
              return;
            }
            iVar6 = FUN_0003963a(&local_28);
            if (iVar6 != 0) {
              return;
            }
            iVar6 = local_28 << 0x1f;
LAB_0002896e:
            if (iVar6 != 0) {
              return;
            }
            goto LAB_00028c5c;
          case 6:
            goto switchD_00028816_caseD_6;
          case 7:
            goto switchD_000287c6_caseD_b;
          default:
            return;
          }
        }
        if (bVar4 != 0xd8) {
          return;
        }
      }
      switch(pbVar2[8]) {
      case 0:
switchD_000287c6_caseD_0:
        return;
      case 1:
        goto switchD_000287c6_caseD_1;
      case 2:
        goto switchD_000287c6_caseD_2;
      case 3:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        iVar6 = FUN_0003963a(&local_28);
        if (iVar6 != 0) {
          return;
        }
        if ((int)(local_28 << 0x1e) < 0) {
          pbVar2[0x19] = 0;
          if (*pbVar2 == 0x52) {
LAB_00028d62:
            pbVar2[8] = 4;
            return;
          }
          goto LAB_00028c5c;
        }
        bVar4 = pbVar2[0x19];
        bVar9 = 2 < bVar4;
LAB_0002889e:
        if (!bVar9) goto LAB_00028840;
        break;
      case 4:
      case 6:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        if (bVar4 == 0x52) {
          FUN_00039602(*(undefined4 *)(pbVar2 + 0xc));
          goto LAB_00028cac;
        }
        FUN_000395ce();
LAB_000288b4:
        bVar4 = 7;
        goto LAB_00028c2c;
      case 5:
      case 7:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        iVar6 = FUN_0003963a(&local_28);
        if (iVar6 != 0) {
          return;
        }
        if ((local_28 & 1) != 0) {
          return;
        }
        break;
      case 8:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        FUN_00039540();
        goto LAB_00028a08;
      case 9:
        goto switchD_000287c6_caseD_b;
      default:
        goto switchD_000287c6_caseD_0;
      }
LAB_000288d8:
      bVar4 = 8;
      goto LAB_00028c2c;
    }
    if (bVar4 == 2) {
      switch(pbVar2[8]) {
      case 0:
        return;
      case 1:
        goto switchD_00028c36_caseD_1;
      case 2:
        if (*(int *)(pbVar2 + 0x10) == 0) goto LAB_00028c5c;
LAB_00028c4c:
        iVar6 = FUN_0003979c();
        if (iVar6 != 0) {
          return;
        }
LAB_00028c54:
        pbVar2[8] = 3;
        return;
      case 3:
switchD_00028c36_caseD_3:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        iVar6 = FUN_0003963a(&local_28);
        if (iVar6 != 0) {
          return;
        }
        if (-1 < (int)(local_28 << 0x1e)) {
          bVar4 = pbVar2[0x19];
          if (2 < bVar4) goto LAB_00028c5c;
          goto LAB_00028840;
        }
LAB_0002883c:
        pbVar2[0x19] = 0;
        goto LAB_00028d62;
      case 4:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        uVar5 = *(uint *)(pbVar2 + 0xc);
        uVar8 = 0x100 - (uVar5 & 0xff);
        if (uVar8 < *(uint *)(pbVar2 + 0x10)) {
          *(short *)(DAT_00028b6c + 2) = (short)uVar8;
        }
        else {
          *(short *)(DAT_00028b6c + 2) = (short)*(uint *)(pbVar2 + 0x10);
        }
        FUN_00039708(uVar5,*(int *)(pbVar2 + 4) + *(int *)(pbVar2 + 0x14),
                     *(undefined2 *)(pcVar3 + 2));
        goto LAB_00028cac;
      case 5:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        iVar6 = FUN_0003963a(&local_28);
        if (iVar6 != 0) {
          return;
        }
        if ((local_28 & 1) != 0) {
          return;
        }
        *(uint *)(pbVar2 + 0xc) = (*(uint *)(pbVar2 + 0xc) & 0xffffff00) + 0x100;
        uVar1 = *(ushort *)(pcVar3 + 2);
        *(uint *)(pbVar2 + 0x14) = *(int *)(pbVar2 + 0x14) + (uint)uVar1;
        *(uint *)(pbVar2 + 0x10) = *(int *)(pbVar2 + 0x10) - (uint)uVar1;
        goto LAB_00028ce8;
      case 6:
switchD_00028816_caseD_6:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        FUN_00039540();
        goto LAB_000288b4;
      case 7:
        goto switchD_00028c36_caseD_7;
      default:
        return;
      }
    }
    if (bVar4 == 3) {
      bVar4 = pbVar2[8];
      if (bVar4 != 1) {
        if (bVar4 == 2) {
          if (*DAT_00028b6c != '\0') {
            return;
          }
          uVar5 = 0x2000;
          if (*(uint *)(pbVar2 + 0x10) < 0x2001) {
            uVar5 = *(uint *)(pbVar2 + 0x10);
          }
          *(short *)(DAT_00028b6c + 2) = (short)uVar5;
          FUN_0003955e(*(undefined4 *)(pbVar2 + 0xc),*(int *)(pbVar2 + 0x14) + *(int *)(pbVar2 + 4))
          ;
          goto LAB_00028c54;
        }
        if (bVar4 == 3) {
          if (*DAT_00028b6c != '\0') {
            return;
          }
          uVar8 = *(uint *)(pbVar2 + 0x10);
          uVar5 = 0x2000;
          if (uVar8 < 0x2001) {
            uVar5 = uVar8;
          }
          uVar7 = uVar5 & 0xffff;
          *(short *)(DAT_00028b6c + 2) = (short)uVar5;
          *(uint *)(pbVar2 + 0xc) = *(int *)(pbVar2 + 0xc) + uVar7;
          *(uint *)(pbVar2 + 0x10) = uVar8 - uVar7;
          *(uint *)(pbVar2 + 0x14) = *(int *)(pbVar2 + 0x14) + uVar7;
          pbVar2[8] = 2;
          if (uVar8 - uVar7 != 0) {
            return;
          }
          FUN_00039540();
          goto LAB_00028d62;
        }
        if (bVar4 != 4) {
          return;
        }
        goto switchD_00028c36_caseD_7;
      }
switchD_00028c36_caseD_1:
    }
    else {
      if (bVar4 != 0x20) {
        if (bVar4 != 0x22) {
          return;
        }
        switch(pbVar2[8]) {
        default:
          return;
        case 1:
          goto switchD_000287c6_caseD_1;
        case 2:
          goto switchD_000287c6_caseD_2;
        case 3:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          iVar6 = FUN_0003963a(&local_28);
          if (iVar6 != 0) {
            return;
          }
          if ((int)(local_28 << 0x1e) < 0) goto LAB_0002883c;
          bVar4 = pbVar2[0x19];
          bVar9 = false;
          if (bVar4 < 3) goto LAB_0002889e;
          break;
        case 4:
          goto switchD_000287c6_caseD_4;
        case 5:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          iVar6 = FUN_0003963a(&local_28);
          if (iVar6 != 0) {
            return;
          }
          if ((local_28 & 1) != 0) {
            return;
          }
          if (*(int *)(pbVar2 + 0x10) != 0) {
            iVar6 = FUN_0003979c();
            goto LAB_0002896e;
          }
          break;
        case 6:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          iVar6 = FUN_0003963a(&local_28);
          if (iVar6 != 0) {
            return;
          }
          if ((int)(local_28 << 0x1e) < 0) {
            pbVar2[0x19] = 0;
            goto LAB_000288b4;
          }
          if (pbVar2[0x19] < 3) {
            pbVar2[0x19] = pbVar2[0x19] + 1;
            goto LAB_00028cac;
          }
          break;
        case 7:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          uVar5 = *(uint *)(pbVar2 + 0x10);
          if (0x100 < uVar5) {
            uVar5 = 0x100;
          }
          *(short *)(DAT_00028b6c + 2) = (short)uVar5;
          FUN_00039708(*(undefined4 *)(pbVar2 + 0xc),*(int *)(pbVar2 + 0x14) + *(int *)(pbVar2 + 4))
          ;
          goto LAB_000288d8;
        case 8:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          iVar6 = FUN_0003963a(&local_28);
          if (iVar6 != 0) {
            return;
          }
          if ((local_28 & 1) != 0) {
            return;
          }
          uVar5 = *(uint *)(pbVar2 + 0x10);
          if (0x100 < uVar5) {
            uVar5 = 0x100;
          }
          *(short *)(pcVar3 + 2) = (short)uVar5;
          FUN_0003955e(*(undefined4 *)(pbVar2 + 0xc),DAT_00028b70);
          goto LAB_00028a08;
        case 9:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          uVar5 = *(uint *)(pbVar2 + 0x10);
          if (0x100 < uVar5) {
            uVar5 = 0x100;
          }
          *(short *)(DAT_00028b6c + 2) = (short)uVar5;
          iVar6 = FUN_0001c604(*(int *)(pbVar2 + 4) + *(int *)(pbVar2 + 0x14),DAT_00028b70);
          if (iVar6 == 0) {
            uVar5 = (uint)*(ushort *)(pcVar3 + 2);
            *(uint *)(pbVar2 + 0xc) = *(int *)(pbVar2 + 0xc) + uVar5;
            *(uint *)(pbVar2 + 0x14) = *(int *)(pbVar2 + 0x14) + uVar5;
            *(uint *)(pbVar2 + 0x10) = *(int *)(pbVar2 + 0x10) - uVar5;
            goto LAB_00028cac;
          }
          break;
        case 10:
          if (*DAT_00028b6c != '\0') {
            return;
          }
          FUN_00039540();
          goto LAB_00028bda;
        case 0xb:
          goto switchD_000287c6_caseD_b;
        }
LAB_00028a4e:
        bVar4 = 10;
        goto LAB_00028c2c;
      }
      switch(pbVar2[8]) {
      case 0:
        return;
      case 1:
        break;
      case 2:
switchD_000287c6_caseD_2:
        goto LAB_00028c4c;
      case 3:
        goto switchD_000288f0_caseD_3;
      case 4:
switchD_000287c6_caseD_4:
        if (*DAT_00028b6c != '\0') {
          return;
        }
        FUN_00039650(*(undefined4 *)(pbVar2 + 0xc));
LAB_00028cac:
        pbVar2[8] = 5;
        return;
      case 5:
        goto switchD_000288f0_caseD_5;
      case 6:
        goto switchD_00028816_caseD_6;
      case 7:
switchD_000287c6_caseD_b:
        goto switchD_00028a68_caseD_d;
      default:
        goto switchD_000287c6_caseD_0;
      }
    }
switchD_000287c6_caseD_1:
    FUN_00031320(1);
    FUN_000395b0(0);
LAB_00028ce8:
    pbVar2[8] = 2;
    return;
  }
  switch(pbVar2[8]) {
  case 0:
    break;
  case 1:
    goto switchD_000287c6_caseD_1;
  case 2:
    if (*DAT_00028b6c == '\0') {
      if ((*DAT_00028b74 == '\0') ||
         (iVar6 = FUN_00028ea8(*(undefined4 *)(pbVar2 + 0xc)), iVar6 == 0)) goto LAB_00028c54;
      iVar6 = FUN_0003979c();
      if (iVar6 == 0) {
        FUN_00028efa(*(undefined4 *)(pbVar2 + 0xc));
        return;
      }
    }
    break;
  case 3:
    iVar6 = FUN_0003979c();
    if (iVar6 != 0) {
      return;
    }
    goto LAB_00028d62;
  case 4:
    if ((*DAT_00028b6c == '\0') && (iVar6 = FUN_0003963a(&local_28), iVar6 == 0)) {
      if ((int)(local_28 << 0x1e) < 0) {
        pbVar2[0x19] = 0;
        goto LAB_00028cac;
      }
      bVar4 = pbVar2[0x19];
      if (2 < bVar4) goto LAB_00028c0a;
LAB_00028840:
      pbVar2[0x19] = bVar4 + 1;
      bVar4 = 1;
      goto LAB_00028c2c;
    }
    break;
  case 5:
    if (*DAT_00028b6c == '\0') {
      FUN_00039650(*(undefined4 *)(pbVar2 + 0xc));
      goto LAB_00028c5c;
    }
    break;
  case 6:
    if (((*DAT_00028b6c == '\0') && (iVar6 = FUN_0003963a(&local_28), iVar6 == 0)) &&
       ((local_28 & 1) == 0)) {
      if (*(int *)(pbVar2 + 0x10) != 0) {
        iVar6 = FUN_0003979c();
        if (iVar6 != 0) {
          return;
        }
        goto LAB_000288b4;
      }
      goto LAB_00028c0a;
    }
    break;
  case 7:
    if (*DAT_00028b6c == '\0') {
      iVar6 = FUN_0003963a(&local_28);
      bVar9 = iVar6 == 0;
LAB_00028b22:
      if (bVar9) {
        if ((int)(local_28 << 0x1e) < 0) {
          pbVar2[0x19] = 0;
          goto LAB_000288d8;
        }
        if (pbVar2[0x19] < 3) {
          pbVar2[0x19] = pbVar2[0x19] + 1;
LAB_00028c5c:
          pbVar2[8] = 6;
          return;
        }
        goto LAB_00028c0a;
      }
    }
    break;
  case 8:
    if (*DAT_00028b6c == '\0') {
      uVar5 = *(uint *)(pbVar2 + 0x10);
      if (0x100 < uVar5) {
        uVar5 = 0x100;
      }
      *(short *)(DAT_00028b6c + 2) = (short)uVar5;
      FUN_00039708(*(undefined4 *)(pbVar2 + 0xc),*(int *)(pbVar2 + 0x14) + *(int *)(pbVar2 + 4));
LAB_00028a08:
      bVar4 = 9;
      goto LAB_00028c2c;
    }
    break;
  case 9:
    if (*DAT_00028b6c != '\0') {
      return;
    }
    iVar6 = FUN_0003963a(&local_28);
    if (iVar6 != 0) {
      return;
    }
    if ((local_28 & 1) != 0) {
      return;
    }
    uVar5 = 0x100;
    if (*(uint *)(pbVar2 + 0x10) < 0x101) {
      uVar5 = *(uint *)(pbVar2 + 0x10);
    }
    *(short *)(pcVar3 + 2) = (short)uVar5;
    FUN_0003955e(*(undefined4 *)(pbVar2 + 0xc),DAT_00028d68);
    goto LAB_00028a4e;
  case 10:
    if (*DAT_00028b6c != '\0') {
      return;
    }
    uVar5 = *(uint *)(pbVar2 + 0x10);
    if (0x100 < uVar5) {
      uVar5 = 0x100;
    }
    *(short *)(DAT_00028b6c + 2) = (short)uVar5;
    iVar6 = FUN_0001c604(*(int *)(pbVar2 + 4) + *(int *)(pbVar2 + 0x14),DAT_00028d68);
    if (iVar6 == 0) {
      uVar5 = (uint)*(ushort *)(pcVar3 + 2);
      *(uint *)(pbVar2 + 0xc) = *(int *)(pbVar2 + 0xc) + uVar5;
      *(uint *)(pbVar2 + 0x14) = *(int *)(pbVar2 + 0x14) + uVar5;
      *(uint *)(pbVar2 + 0x10) = *(int *)(pbVar2 + 0x10) - uVar5;
      goto LAB_00028c5c;
    }
LAB_00028bda:
    bVar4 = 0xb;
    goto LAB_00028c2c;
  case 0xb:
    if (*DAT_00028b6c != '\0') {
      return;
    }
    if ((*DAT_00028b74 != '\0') && (iVar6 = FUN_00028ea8(*(undefined4 *)(pbVar2 + 0xc)), iVar6 == 0)
       ) {
      iVar6 = FUN_0003979c();
      bVar9 = false;
      if (iVar6 == 0) {
        FUN_00028ed8(*(undefined4 *)(pbVar2 + 0xc));
        return;
      }
      goto LAB_00028b22;
    }
LAB_00028c0a:
    bVar4 = 0xc;
LAB_00028c2c:
    pbVar2[8] = bVar4;
    return;
  case 0xc:
    if (*DAT_00028b6c != '\0') {
      return;
    }
    FUN_00039540();
    bVar4 = 0xd;
    goto LAB_00028c2c;
  case 0xd:
switchD_00028a68_caseD_d:
switchD_00028c36_caseD_7:
    *pbVar2 = 0;
    pbVar2[8] = 0;
    pbVar2[0x18] = 0;
    FUN_00031320(0);
    return;
  default:
    goto switchD_000287c6_caseD_0;
  }
switchD_000287c6_caseD_0:
  return;
}

