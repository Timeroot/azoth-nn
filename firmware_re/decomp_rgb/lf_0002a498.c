// FUN_0002a498 @0002a498 size=768

uint FUN_0002a498(void)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  uint uVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  
  puVar4 = DAT_0002a7a0;
  bVar3 = true;
  uVar16 = 0;
  iVar14 = 0;
  if ((*DAT_0002a798 != 1) && (*(int *)(DAT_0002a79c + 0x5c) == 0)) {
    bVar3 = false;
  }
  uVar13 = 0;
  *DAT_0002a7a0 = 0;
  do {
    uVar9 = *(uint *)(puVar4 + uVar13 * 4 + -0x288);
    uVar12 = *(uint *)(DAT_0002a7a4 + uVar13 * 4) ^ uVar9;
    if (uVar12 != 0) {
      *(uint *)(DAT_0002a7a4 + uVar13 * 4) = uVar9;
      uVar16 = uVar16 | 1;
    }
    if (uVar9 != 0) {
      uVar9 = 0;
      uVar15 = 1;
      do {
        if ((*(uint *)(puVar4 + uVar13 * 4 + -0x288) & uVar15) != 0) {
          iVar14 = iVar14 + 1;
          cVar2 = *(char *)(DAT_0002a7a8 + *(int *)(DAT_0002a79c + 8) * 0x62 + uVar13 * 0xe + uVar9)
          ;
          if (bVar3) {
            if ((*(uint *)(DAT_0002a7a4 + 0xd4) & 1) == 0) {
              iVar11 = FUN_0002ba90(cVar2);
              if (iVar11 == 0) {
                if (*(int *)(DAT_0002a7b0 + 0x30) != 2) goto LAB_0002a5c4;
                FUN_0003b354(cVar2,0);
                FUN_0002bad4(cVar2,0);
                uVar16 = uVar16 | 2;
              }
            }
            else if (((cVar2 == -0x18) || (cVar2 == ')')) || (cVar2 == '$')) {
              FUN_0002b6c4(*(uint *)(DAT_0002a7a4 + 0xd4) & 1,cVar2);
            }
            else if ((((cVar2 == -0x1f) || (cVar2 == -0x1b)) ||
                     ((cVar2 == -0x20 || (cVar2 == -0x1a)))) ||
                    ((((cVar2 == -0x1e || (cVar2 == -0x1c)) || (cVar2 == -0x1d)) &&
                     ((int)((uint)*(byte *)(DAT_0002a7a4 + 0xd8) << 0x1e) < 0)))) {
LAB_0002a5c4:
              FUN_0003b354(cVar2,1);
              uVar16 = uVar16 | 2;
            }
            puVar5 = DAT_0002a7a0;
            if (DAT_0002a7a0[1] != '\0') {
              DAT_0002a7a0[1] = 0;
              *(uint *)(puVar5 + 4) = uVar13;
              *(uint *)(puVar5 + 8) = uVar9;
            }
            FUN_000336b4(0,cVar2);
            FUN_00030ac0(cVar2);
            if ((*DAT_0002a7b4 & 0xc) != 0) {
              FUN_00024f90(cVar2,0);
            }
            if ((uVar12 & uVar15) != 0) {
              FUN_00030f3c(cVar2);
              if (*DAT_0002a7b8 != '\0') {
                FUN_0002326c(cVar2);
              }
              uVar7 = *(uint *)(DAT_0002a7a4 + 0xd4);
              if ((uVar7 & 1) != 0) {
                if ((cVar2 == -0x1e) || (cVar2 == -0x1d)) {
                  if (((*(uint *)(puVar4 + -0x278) & 0x2001) == 0) &&
                     ((uVar10 = *(uint *)(puVar4 + -0x274), (uVar10 & 1) == 0 &&
                      (-1 < (int)(uVar10 << 0x13))))) {
                    iVar11 = uVar10 << 0x16;
LAB_0002a6ee:
                    if (-1 < iVar11) goto LAB_0002a69a;
                  }
                }
                else {
                  if (cVar2 != -0x1c) goto LAB_0002a69a;
                  if (((((*(uint *)(puVar4 + -0x278) & 0x2001) == 0) &&
                       (uVar10 = *(uint *)(puVar4 + -0x274), (uVar10 & 1) == 0)) &&
                      (-1 < (int)(uVar10 << 0x1d))) && (-1 < (int)(uVar10 << 0x16))) {
                    iVar11 = uVar10 << 0x1e;
                    goto LAB_0002a6ee;
                  }
                }
              }
            }
          }
          else {
            uVar16 = uVar16 | 2;
            FUN_0003b354(cVar2,0);
            FUN_00030ac0(cVar2);
            if ((uVar12 & uVar15) != 0) {
              FUN_00030f3c(cVar2);
            }
            *DAT_0002a7ac = 0;
            uVar7 = *(uint *)(DAT_0002a7a4 + 0xd4);
            cVar8 = '\0';
            if (((uVar7 & 1) == 0) || ((cVar2 != -0x18 && (cVar8 = cVar2, cVar2 != '$')))) {
              if (cVar2 == -0x2d) {
                FUN_0002ba90(0xd3,cVar8);
              }
            }
            else {
LAB_0002a69a:
              FUN_0002b6c4(uVar7 & 1,cVar2);
            }
          }
        }
        uVar15 = uVar15 << 1;
        uVar9 = uVar9 + 1;
      } while (uVar9 < 0xe);
    }
    iVar6 = DAT_0002a7bc;
    iVar11 = DAT_0002a7a4;
    uVar13 = uVar13 + 1;
  } while (uVar13 < 7);
  uVar13 = *(uint *)(puVar4 + -0x274);
  if ((int)(uVar13 << 0x15) < 0) {
    if (iVar14 == 1) {
      *(uint *)(DAT_0002a7a4 + 0xd4) = *(uint *)(DAT_0002a7a4 + 0xd4) | 1;
      *(undefined4 *)(iVar11 + 0xd8) = 1;
      goto LAB_0002a756;
    }
    if (iVar14 != 2) goto LAB_0002a756;
    piVar1 = (int *)(DAT_0002a7a4 + 0xd8);
    if (*piVar1 << 0x1e < 0) {
      *(uint *)(DAT_0002a7a4 + 0xd4) = *(uint *)(DAT_0002a7a4 + 0xd4) | 1;
      goto LAB_0002a756;
    }
    if (((((*(uint *)(puVar4 + -0x278) & 0x2001) != 0) || ((uVar13 & 1) != 0)) ||
        (((int)(uVar13 << 0x13) < 0 || (((int)(uVar13 << 0x1d) < 0 || ((int)(uVar13 << 0x16) < 0))))
        )) || ((int)(uVar13 << 0x1e) < 0)) {
      *(uint *)(DAT_0002a7a4 + 0xd4) = *(uint *)(DAT_0002a7a4 + 0xd4) | 1;
      if ((2 < *(uint *)(iVar6 + 0x24)) && (*piVar1 == 0)) {
        *(undefined4 *)(iVar11 + 0xd8) = 2;
      }
      goto LAB_0002a756;
    }
  }
  else {
    if ((*(uint *)(DAT_0002a7a4 + 0xd4) & 1) != 0) {
      *(uint *)(DAT_0002a7a4 + 0xd4) = *(uint *)(DAT_0002a7a4 + 0xd4) & 0xfffffffe;
      *(uint *)(iVar11 + 0xd8) = *(uint *)(iVar11 + 0xd8) & 0xfffffffe;
      FUN_0002b6c4(0,0);
    }
LAB_0002a756:
    if (((((*(uint *)(puVar4 + -0x278) & 0x2001) != 0) ||
         (uVar13 = *(uint *)(puVar4 + -0x274), (uVar13 & 1) != 0)) || ((int)(uVar13 << 0x13) < 0))
       || ((((int)(uVar13 << 0x1d) < 0 || ((int)(uVar13 << 0x16) < 0)) ||
           ((int)(uVar13 << 0x1e) < 0)))) {
      if (iVar14 == 1) {
        *(undefined4 *)(DAT_0002a7a4 + 0xd8) = 2;
      }
      goto LAB_0002a790;
    }
  }
  *(uint *)(DAT_0002a7a4 + 0xd8) = *(uint *)(DAT_0002a7a4 + 0xd8) & 0xfffffffd;
LAB_0002a790:
  *(int *)(iVar6 + 0x24) = iVar14;
  return uVar16;
}

