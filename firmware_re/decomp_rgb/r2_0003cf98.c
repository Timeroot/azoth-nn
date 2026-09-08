// FUN_0003cf98 @0003cf98 size=916

void FUN_0003cf98(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  byte bVar5;
  undefined2 uVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  int iVar10;
  char *pcVar11;
  uint uVar12;
  undefined8 uVar13;
  undefined4 local_28;
  undefined4 local_24;
  
  pcVar11 = DAT_0003d1e8;
  pcVar4 = DAT_0003d1e4;
  iVar3 = DAT_0003d1e0;
  iVar8 = DAT_0003d1dc;
  iVar10 = DAT_0003d1d8;
  cVar1 = *param_1;
  local_28 = param_3;
  local_24 = param_4;
  if (cVar1 == '\0') {
    *(undefined4 *)(DAT_0003d1e0 + 0x38) = 0;
    if (*pcVar11 == '\0') {
      if (*(int *)(iVar10 + 0x60) == 0) {
        *(undefined4 *)(iVar3 + 0x30) = 1000;
      }
      else {
        *(undefined4 *)(iVar3 + 0x30) = 100;
      }
    }
    *(undefined4 *)(iVar3 + 0x10) = 0;
    *(undefined1 *)(iVar3 + 7) = 1;
    if (*(char *)(iVar3 + 8) != '\0') {
      return;
    }
    uVar13 = FUN_00039ebc();
    if ((int)uVar13 == 0) {
      FUN_0003d47c(2,(int)((ulonglong)uVar13 >> 0x20),local_28,local_24);
      return;
    }
    if ((*(byte *)(iVar3 + 2) & ~*(byte *)(iVar3 + 0xb)) == 0) {
      return;
    }
    iVar10 = *(int *)(iVar3 + 0x44) + 1;
    *(int *)(iVar3 + 0x44) = iVar10;
    if (iVar10 != 1) {
      return;
    }
    *(undefined4 *)(iVar8 + 0x44) = 1;
    if (400 - *DAT_0003d1ec < 0x5b) {
      return;
    }
    uVar6 = 0;
  }
  else {
    if (cVar1 != '\x01') {
      if (cVar1 != '\x02') {
        return;
      }
      iVar8 = FUN_0003d364(DAT_0003d1e4 + -0x5a);
      if (iVar8 != 0) {
        return;
      }
      pbVar9 = (byte *)(pcVar4 + -0x5a);
      *(char *)(iVar3 + 9) = pcVar4[-0x58];
      iVar8 = DAT_00030800;
      if (*(int *)(iVar10 + 0x60) == 0) {
        if ((pcVar4[-0x55] == 'A') && (pcVar4[-0x54] == 'M')) {
          uVar12 = FUN_00044cd8(pcVar4 + -0x55,*pbVar9 - 2);
          uVar7 = (uint)*pbVar9;
          if ((uint)(byte)DAT_0003d1e4[uVar7 - 0x57] != (uVar12 & 0xff)) {
            return;
          }
          if ((uint)(byte)DAT_0003d1e4[uVar7 - 0x56] != uVar12 >> 8) {
            return;
          }
          if (uVar7 < 9) {
            local_28 = 0;
            local_24 = 0;
            FUN_0001c590(&local_28,pcVar4 + -0x53,*pbVar9 - 4);
            FUN_00024e98(&local_28,5);
            return;
          }
          FUN_00024e98(pcVar4 + -0x53,uVar7 - 4 & 0xff,local_28,local_24);
          return;
        }
        pcVar11 = pcVar4 + -0x55;
        uVar12 = (uint)*pbVar9;
        if (*pcVar11 == 'I') {
          if (pcVar4[-0x54] != 'N') {
            return;
          }
          if ((byte)pcVar4[-0x53] != uVar12) {
            return;
          }
          uVar7 = FUN_00044e0c(pcVar11,uVar12 - 1,local_28,local_24);
          puVar2 = DAT_00030804;
          if (uVar7 == (byte)pcVar11[uVar12 - 1]) {
            bVar5 = pcVar4[-0x52];
            if (bVar5 == 0xd2) {
              *(undefined1 *)(iVar8 + 1) = 0;
              FUN_0002ce7c(*puVar2);
              return;
            }
            if (0xd2 < bVar5) {
              if (bVar5 == 0xd5) {
                if (pcVar4[-0x51] != '\x01') {
                  return;
                }
                FUN_000298b8(pcVar4[-0x50]);
                return;
              }
              if (bVar5 != 0xfd) {
                return;
              }
              *(undefined1 *)(iVar8 + 1) = 1;
              return;
            }
            if (bVar5 == 0xc0) {
              if (*(char *)(iVar8 + 6) != '\0') {
                return;
              }
              *(undefined1 *)(iVar8 + 6) = 1;
              return;
            }
            if (bVar5 != 0xc1) {
              if (bVar5 != 0xd1) {
                return;
              }
              FUN_0002cf24(*DAT_00030804);
              if (*(int *)(DAT_00030808 + 0x5c) == 0) {
                return;
              }
              *DAT_0003080c = 1;
              return;
            }
            if (*(char *)(iVar8 + 6) == '\0') {
              return;
            }
            *(undefined1 *)(iVar8 + 6) = 0;
            return;
          }
        }
        if ((((*pcVar11 == 'U') && (pcVar4[-0x54] == -0x2b)) && (pcVar4[-0x53] == '\x02')) &&
           (uVar7 = FUN_00044e0c(pcVar11,uVar12 - 1), uVar7 == (byte)pcVar11[uVar12 - 1])) {
          if (pcVar4[-0x52] == -1) {
            FUN_00043748(0);
            *(undefined1 *)(iVar8 + 3) = 0;
            FUN_00044508();
            *(undefined1 *)(iVar8 + 2) = 0;
          }
          else {
            FUN_00043748(1);
            if ((uint)(byte)pcVar4[-0x52] != *(uint *)(iVar8 + 0x34)) {
              *(uint *)(iVar8 + 0x34) = (uint)(byte)pcVar4[-0x52];
            }
            *(undefined1 *)(iVar8 + 3) = 1;
            if (*(uint *)(iVar8 + 0x34) < 2) {
              *(undefined4 *)(iVar8 + 0x14) = 0;
              *(undefined4 *)(iVar8 + 0x18) = 2;
            }
            else {
              *(undefined4 *)(iVar8 + 0x14) = 2;
              *(undefined4 *)(iVar8 + 0x18) = 4;
            }
            if (*(char *)(iVar8 + 10) == '\0') {
              if (*DAT_00030814 != '\0') {
                FUN_0003d498(*(undefined4 *)
                              (DAT_00030818 + (*(int *)(iVar8 + 0x2c) + *(uint *)(iVar8 + 0x34)) * 4
                              ));
                return;
              }
              *(undefined1 *)(iVar8 + 2) = 0;
              *(undefined4 *)(iVar8 + 0x40) = 0x46;
              FUN_000443a0(0x1c2);
              return;
            }
            iVar10 = -(((uint)(byte)pcVar4[-0x51] * 10 - *(int *)(iVar8 + 0x48)) + -0x10);
            *(int *)(iVar8 + 0x3c) = iVar10;
            *(undefined4 *)(iVar8 + 0x40) = 0;
            *DAT_00030810 = iVar10 + 1000;
            *(undefined1 *)(iVar8 + 2) = 1;
          }
        }
        return;
      }
      if (*(char *)(iVar3 + 4) == '\0') {
        return;
      }
      if (pcVar4[-0x55] != 'H') {
        return;
      }
      if (pcVar4[-0x54] != 'K') {
        return;
      }
      if (pcVar4[-0x53] != 'P') {
        return;
      }
      if (pcVar4[-0x52] != 'R') {
        return;
      }
      cVar1 = *(char *)(iVar3 + 5);
      if (pcVar4[-0x51] != cVar1) {
        return;
      }
      *(char *)(iVar3 + 5) = cVar1 + '\x01';
      if (cVar1 == -1) {
        *(undefined1 *)(iVar3 + 4) = 2;
        return;
      }
      if (cVar1 != '\0') {
        return;
      }
      *(undefined1 *)(iVar3 + 4) = 4;
      FUN_0001c590(pcVar4,pcVar4 + -0x50,0x30);
      bVar5 = pcVar4[10] + 1U | 0x80;
      pcVar4[10] = bVar5;
      if (bVar5 != pcVar4[0xb]) {
        return;
      }
      pcVar4[10] = bVar5 + 1;
      return;
    }
    if (*DAT_0003d1e4 != '\x01') {
      return;
    }
    if (*(int *)(DAT_0003d1d8 + 0x60) != 0) {
      uVar12 = (uint)*(byte *)(DAT_0003d1e0 + 4);
      if ((uVar12 != 6) && (uVar12 != 0)) {
        return;
      }
      goto LAB_0003d154;
    }
    iVar10 = FUN_00039ebc();
    if (iVar10 == 0) {
      if ((*(char *)(iVar3 + 3) == '\0') &&
         (uVar12 = *(int *)(iVar3 + 0x34) + 1, *(uint *)(iVar3 + 0x34) = uVar12, 3 < uVar12)) {
        *(undefined4 *)(iVar3 + 0x34) = 0;
      }
    }
    else if ((*(char *)(iVar3 + 0xc) == '\0') &&
            (uVar12 = *(int *)(iVar3 + 0x34) + 1, *(uint *)(iVar3 + 0x34) = uVar12,
            *(uint *)(iVar3 + 0x18) <= uVar12)) {
      *(undefined4 *)(iVar3 + 0x34) = *(undefined4 *)(iVar3 + 0x14);
    }
    iVar10 = FUN_0003d498(*(undefined4 *)
                           (DAT_0003d1f0 + (*(int *)(iVar3 + 0x34) + *(int *)(iVar3 + 0x2c)) * 4));
    if (iVar10 != 0) {
      return;
    }
    if (*(char *)(iVar3 + 8) != '\0') {
      FUN_00030380();
      iVar10 = FUN_00039ebc();
      if (iVar10 == 0) {
        return;
      }
      if (*(uint *)(iVar3 + 0x38) < 5000) {
        return;
      }
      *(undefined4 *)(iVar3 + 0x38) = 0;
      *(undefined1 *)(iVar3 + 3) = 0;
      FUN_00043748(0);
      *(undefined1 *)(iVar3 + 2) = 0;
      return;
    }
    iVar10 = FUN_00039ebc();
    uVar12 = *(uint *)(iVar3 + 0x38);
    if (iVar10 == 0) {
      if (199 < uVar12) {
        *(undefined4 *)(iVar3 + 0x38) = 0;
      }
      uVar6 = *(undefined2 *)(iVar3 + 0xe);
    }
    else {
      if (uVar12 < 1000) {
        if ((uVar12 < 0x1e) && (*(char *)(iVar3 + 2) != '\0')) {
          return;
        }
        *(undefined1 *)(iVar3 + 2) = 0;
        *(undefined4 *)(iVar3 + 0x40) = 0x46;
        uVar13 = FUN_0003d47c(0);
        param_2 = (undefined4)((ulonglong)uVar13 >> 0x20);
        uVar12 = (uint)uVar13;
        *(undefined4 *)(iVar8 + 0xc) = 1;
        goto LAB_0003d154;
      }
      *(undefined4 *)(iVar3 + 0x38) = 0;
      *(undefined1 *)(iVar3 + 3) = 0;
      FUN_00043748(0);
      FUN_00044508();
      uVar6 = 2;
    }
  }
  uVar13 = FUN_0003d47c(uVar6);
  param_2 = (undefined4)((ulonglong)uVar13 >> 0x20);
  uVar12 = (uint)uVar13;
LAB_0003d154:
  FUN_0003d500(uVar12,param_2,local_28,local_24);
  return;
}

