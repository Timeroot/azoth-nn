// FUN_00031798 @00031798 size=710

void FUN_00031798(uint param_1)

{
  int iVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined2 *puVar12;
  int iVar13;
  int iVar14;
  undefined1 uVar15;
  uint uVar16;
  undefined2 *puVar17;
  
  pcVar2 = DAT_00031970;
  uVar8 = FUN_00029f5c(*(undefined4 *)(DAT_00031970 + 0x68));
  iVar13 = DAT_00031980;
  pcVar5 = DAT_0003197c;
  pcVar4 = DAT_00031978;
  puVar3 = DAT_00031974;
  puVar7 = DAT_000296c4;
  iVar9 = DAT_000296c0;
  if ((uVar8 & param_1) == 0) {
    if ((*DAT_00031978 != '\0') && (iVar9 = FUN_00029ff8(DAT_00031998), iVar9 == 0)) {
      FUN_00029534(DAT_00031998);
      FUN_0003dbe0(3);
      FUN_0003dbe0(7);
      puVar6 = DAT_0003199c;
      *pcVar4 = '\0';
      *puVar6 = 0;
      pcVar2[0x58] = '\0';
      pcVar2[0x59] = '\0';
      pcVar2[0x5a] = '\0';
      pcVar2[0x5b] = '\0';
      pcVar2[0x60] = '\0';
      pcVar2[0x61] = '\0';
      pcVar2[0x62] = '\0';
      pcVar2[99] = '\0';
      *puVar3 = 0;
      FUN_0001c5e0(DAT_00031980,0xb4);
      FUN_0001c5e0(DAT_00031980 + 0xb4,0xb4);
      return;
    }
    return;
  }
  if (*DAT_00031978 != '\0') {
    if (*DAT_0003197c != '\0') {
      *DAT_0003197c = '\0';
      *pcVar4 = '\0';
      pcVar2[0x60] = '\0';
      pcVar2[0x61] = '\0';
      pcVar2[0x62] = '\0';
      pcVar2[99] = '\0';
      return;
    }
    if (*pcVar2 == '\0') {
      iVar9 = *(int *)(pcVar2 + 0x60);
      *(int *)(pcVar2 + 0x60) = iVar9 + 1;
      pcVar4 = DAT_00031984;
      switch(iVar9) {
      case 0:
        if (*DAT_00031984 != '\0') {
          FUN_0002988c(*DAT_00031984,0);
          *pcVar4 = '\0';
        }
        break;
      case 1:
        iVar9 = 0;
        uVar8 = *(uint *)(pcVar2 + 0xc);
        iVar14 = DAT_00031980 + -0xb4;
        iVar13 = DAT_00031988 + *(int *)(pcVar2 + 0x5c) * 0x78;
        do {
          puVar17 = DAT_00031990;
          uVar11 = (uint)*(byte *)(iVar13 + iVar9 * 2);
          if ((uVar11 < 6) && (uVar16 = (uint)*(byte *)(iVar13 + iVar9 * 2 + 1), uVar16 < 0x10)) {
            puVar17 = (undefined2 *)(DAT_0003198c + uVar11 * 0x30 + uVar16 * 3);
            iVar1 = iVar9 * 3;
            puVar12 = (undefined2 *)(iVar1 + iVar14);
            *puVar12 = *puVar17;
            *(undefined1 *)(puVar12 + 1) = *(undefined1 *)(puVar17 + 1);
            *(char *)(iVar14 + iVar1) =
                 (char)(((uint)*(byte *)(iVar14 + iVar1) * 0xff >> (uVar8 & 0xff)) >> 8);
            *(char *)((int)puVar12 + 1) =
                 (char)(((uint)((short)(ushort)*(byte *)((int)puVar12 + 1) * 0xd2) >> (uVar8 & 0xff)
                        ) >> 8);
            uVar15 = (undefined1)
                     (((uint)((short)(ushort)*(byte *)(puVar12 + 1) * 0xbe) >> (uVar8 & 0xff)) >> 8)
            ;
          }
          else {
            puVar12 = (undefined2 *)(iVar9 * 3 + iVar14);
            *puVar12 = *DAT_00031990;
            uVar15 = *(undefined1 *)(puVar17 + 1);
          }
          iVar9 = iVar9 + 1;
          *(undefined1 *)(puVar12 + 1) = uVar15;
        } while (iVar9 < 0x3c);
        break;
      case 2:
        iVar9 = FUN_0001c604(iVar13 + *(int *)(pcVar2 + 0x5c) * 0xb4,DAT_00031980 + -0xb4,0xb4);
        if (iVar9 == 0) {
          pcVar2[1] = '\0';
        }
        else {
          FUN_0001c590(iVar13 + *(int *)(pcVar2 + 0x5c) * 0xb4,DAT_00031980 + -0xb4,0xb4);
          pcVar2[1] = '\x01';
        }
        break;
      case 3:
      case 4:
      case 5:
      case 6:
        if (pcVar2[1] != '\0') {
          FUN_00031b28(iVar9 + -3,*(int *)(pcVar2 + 0x5c),iVar13 + *(int *)(pcVar2 + 0x5c) * 0xb4);
        }
        break;
      case 0xb:
        iVar9 = *(int *)(pcVar2 + 0x5c);
        *(int *)(pcVar2 + 0x5c) = iVar9 + 1;
        if (1 < iVar9 + 1) {
          pcVar2[0x5c] = '\0';
          pcVar2[0x5d] = '\0';
          pcVar2[0x5e] = '\0';
          pcVar2[0x5f] = '\0';
        }
        iVar13 = *(int *)(pcVar2 + 0x58);
        *(int *)(pcVar2 + 0x58) = iVar13 + 1;
        iVar9 = DAT_00031994;
        if ((0x340 < iVar13 + 1) &&
           (pcVar2[0x58] = '\0', pcVar2[0x59] = '\0', pcVar2[0x5a] = '\0', pcVar2[0x5b] = '\0',
           *(int *)(iVar9 + 0x10) == 0)) {
          *pcVar5 = '\x01';
          *puVar3 = 1;
        }
        pcVar2[0x60] = '\0';
        pcVar2[0x61] = '\0';
        pcVar2[0x62] = '\0';
        pcVar2[99] = '\0';
      }
    }
    iVar9 = *(int *)(pcVar2 + 0xc);
    if (iVar9 == 0) {
      return;
    }
    iVar13 = *(int *)(pcVar2 + 0x74);
    *(int *)(pcVar2 + 0x74) = iVar13 + -1;
    if (iVar13 + -1 != 0) {
      return;
    }
    pcVar2[0x74] = '\x03';
    pcVar2[0x75] = '\0';
    pcVar2[0x76] = '\0';
    pcVar2[0x77] = '\0';
    *(int *)(pcVar2 + 0xc) = iVar9 + -1;
    return;
  }
  iVar13 = *(int *)(DAT_000296c0 + 0x10);
  switch(iVar13) {
  case 0:
    FUN_0003de64(3);
    FUN_00029440();
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    break;
  case 1:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    FUN_00029818(4,0);
    *puVar7 = 0;
    puVar7[1] = 1;
    puVar7[2] = 0x30;
    puVar7[3] = 0;
    uVar10 = 4;
    puVar7 = DAT_000296c4;
    goto LAB_000296a2;
  case 2:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    *puVar7 = 0x36;
    puVar7[1] = 3;
    FUN_00029704(DAT_000296c4,2,0x30);
    if (*(char *)(iVar9 + 2) != '\0') {
      iVar13 = 5;
      goto LAB_00029632;
    }
    break;
  case 3:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    FUN_00029818(0);
    uVar10 = 0xb5;
    goto LAB_0002966a;
  case 4:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    FUN_00029818(1,0);
    uVar10 = 0xac;
LAB_0002966a:
    puVar7 = DAT_000296c4 + 0xb5;
LAB_000296a2:
    FUN_00029704(puVar7,uVar10,0x30);
    break;
  case 5:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    FUN_00029818(2,0);
    uVar10 = 0xb5;
    goto LAB_0002969e;
  case 6:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    FUN_00029818(3,0);
    uVar10 = 0xac;
LAB_0002969e:
    puVar7 = (undefined1 *)(DAT_000296c0 + 0x14);
    goto LAB_000296a2;
  case 7:
    iVar13 = FUN_00029ff8(DAT_000296c8);
    if (iVar13 != 0) {
      return;
    }
    FUN_0003de64(7);
    *(undefined1 *)(iVar9 + 1) = 1;
    *(undefined4 *)(iVar9 + 0x10) = 0;
    return;
  default:
    goto switchD_000295ca_default;
  }
  iVar13 = *(int *)(iVar9 + 0x10);
switchD_000295ca_default:
  iVar13 = iVar13 + 1;
LAB_00029632:
  *(int *)(iVar9 + 0x10) = iVar13;
  return;
}

