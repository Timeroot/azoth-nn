
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000332f4(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  undefined4 uVar12;
  uint local_28;
  
  FUN_000336b4(0,0,1);
  if ((*DAT_00033364 == 1) || (-1 < (int)((uint)*DAT_00033368 << 0x1d))) {
    FUN_0002b0b8(0xf,0);
    FUN_0002aa10();
  }
  FUN_000269c4();
  FUN_0002c19c();
  FUN_0002bc14();
  FUN_00029bcc();
  FUN_00025004();
  FUN_00026c40();
  FUN_0002330c();
  FUN_00028778();
  FUN_00028588();
  FUN_0002789c();
  FUN_00026d18();
  FUN_00027f88(*DAT_0003336c);
  FUN_00031798(1);
  FUN_0002d2e0();
  piVar4 = DAT_000266e8;
  iVar3 = DAT_000266e4;
  iVar2 = DAT_000266e0;
  iVar9 = DAT_000266dc;
  puVar1 = DAT_000266d8;
  uVar8 = *DAT_000266d8;
  if ((int)(uVar8 << 0x1e) < 0) {
    if (*(int *)(DAT_000266e0 + 0x60) != 0) {
      return;
    }
    FUN_00033856(1);
    *DAT_000266ec = *DAT_000266ec + 1;
    FUN_0003389a(1);
    if ((*DAT_000266f0 & ~*DAT_000266f4) == 0) {
      if (*(int *)(iVar3 + 0x24) < 5000) {
        iVar9 = *(int *)(iVar3 + 0x24) + 1;
        *(int *)(iVar3 + 0x24) = iVar9;
        if (iVar9 < 5000) {
          return;
        }
        FUN_000277cc(s_RF_5s_DC_000266f8);
        FUN_0002cf24(*puVar1);
        return;
      }
    }
    else {
      *(undefined4 *)(iVar3 + 0x24) = 0;
    }
  }
  else if ((uVar8 & 1) == 0) {
    if (-1 < (int)(uVar8 << 0x1d)) {
      return;
    }
    if (*(int *)(DAT_000266e0 + 4) == 0) {
      if (*(char *)(DAT_000266dc + 6) == -0x57) {
        *(undefined4 *)(DAT_000266e0 + 4) = 1;
        *(undefined4 *)(iVar3 + 0x18) = 1;
        pcVar11 = s_USB_Demo_Mode_00026704;
        *(undefined4 *)(iVar3 + 0x1c) = 1;
      }
      else {
        iVar10 = FUN_0003499c();
        if (((iVar10 != 5) || (*piVar4 == 0)) || (*piVar4 == *(int *)(iVar3 + 0x20)))
        goto LAB_000263a6;
        *(undefined4 *)(iVar2 + 4) = 1;
        if (*(int *)(iVar3 + 0x18) != 1) {
          *(undefined4 *)(iVar3 + 0x18) = 1;
          *(undefined4 *)(iVar3 + 0x1c) = 0x32;
        }
        pcVar11 = s_USB_PM_Ct_00026714;
      }
      FUN_000277cc(pcVar11);
    }
  }
LAB_000263a6:
  if (*(int *)(iVar3 + 0x1c) != 0) {
    disableIRQinterrupts();
    *(int *)(iVar3 + 0x1c) = *(int *)(iVar3 + 0x1c) + -1;
    enableIRQinterrupts();
    uVar8 = *puVar1;
    if (((-1 < (int)(uVar8 << 0x1e)) && ((uVar8 & 1) == 0)) &&
       (((int)(uVar8 << 0x1d) < 0 && ((*piVar4 != 0 && (*piVar4 != *(int *)(iVar3 + 0x20))))))) {
      *(undefined4 *)(iVar3 + 0x18) = 1;
      *(undefined4 *)(iVar3 + 0x1c) = 0;
      FUN_000277cc(s_USB_PM_Rs_00026720);
    }
    if (*(int *)(iVar3 + 0x1c) == 0) {
      switch(*(undefined4 *)(iVar3 + 0x18)) {
      case 0:
      case 2:
      case 5:
        if (*(char *)(iVar9 + 6) != -0x57) {
          FUN_000277cc(s_Enter_sleep_00026734);
          if (((int)((uint)(byte)*puVar1 << 0x1e) < 0) &&
             (FUN_00042a84(), *(int *)(iVar2 + 0x18) == 0)) {
            *DAT_00026740 = 1;
          }
          *(undefined4 *)(iVar2 + 0x58) = 1;
          local_28 = 0;
          iVar9 = 0;
          FUN_0001c5e0(DAT_00026744,0x18);
          FUN_0002b3c4();
          FUN_00042c70(*(int *)(iVar2 + 0x18) != 0);
          piVar5 = DAT_00026744;
          if (*(int *)(iVar2 + 0x18) == 0) {
            DAT_00026744[4] = 100;
          }
          else {
            DAT_00026744[4] = 1;
          }
          puVar6 = DAT_00026748;
          if ((int)(*puVar1 << 0x1e) < 0) {
            *(undefined1 *)(iVar3 + 4) = 0;
            *puVar6 = 1;
            FUN_00044508();
            iVar10 = FUN_00039ebc();
            puVar7 = DAT_00026750;
            if (iVar10 != 0) {
              *DAT_0002674c = 0;
              *puVar7 = 0x46;
            }
            FUN_00030d04();
          }
          else if ((*puVar1 & 1) != 0) {
            FUN_00025b3c(2);
          }
          if ((*DAT_00026754 & 1) != 0) {
            FUN_000311fc();
            if (*(int *)(iVar2 + 0x18) == 0) {
              FUN_0002e544();
            }
            else {
              FUN_00031564();
            }
            FUN_000312ec(DAT_00026758);
          }
          *(undefined1 *)(iVar3 + 2) = 1;
          FUN_00033510();
          FUN_00031798(0);
          *(undefined1 *)(iVar3 + 5) = 1;
          pcVar11 = DAT_0002675c;
LAB_000264c0:
          do {
            if (*pcVar11 == '\0') {
              FUN_00045a64();
              FUN_000341a4();
              FUN_0003e038();
              FUN_00045a64();
              FUN_000341a4();
              if (*DAT_00026760 == '\0') goto LAB_000264c0;
LAB_000264ca:
              iVar10 = piVar5[4];
              if (iVar10 == 1) {
                *piVar5 = *piVar5 + 1;
              }
              piVar5[1] = piVar5[1] + iVar10;
              piVar5[5] = iVar10 + piVar5[5];
              disableIRQinterrupts();
              *DAT_00026760 = '\0';
              enableIRQinterrupts();
            }
            else if (*DAT_00026760 != '\0') goto LAB_000264ca;
            if ((int)(*puVar1 << 0x1e) < 0) {
              if (piVar5[5] == 500) {
                if (*(int *)(iVar2 + 0x18) == 0) {
                  FUN_0003a0d4();
                  FUN_000436f0();
                  piVar5[4] = 1;
                }
                *DAT_00026764 = '\0';
                FUN_00030380();
LAB_00026572:
                iVar10 = FUN_00039ebc();
                uVar12 = 0;
                if (iVar10 != 0) {
                  uVar12 = 2;
                }
                FUN_0003d47c(uVar12);
                if (*(int *)(iVar2 + 0x5c) == 0) {
                  uVar12 = 0xff;
                }
                else {
                  uVar12 = 0xfe;
                }
                FUN_000432e8(uVar12);
              }
              else if (500 < piVar5[5]) {
                FUN_00030380();
                if ((*DAT_00026764 == '\0') && (piVar5[5] < 0x208)) goto LAB_00026572;
                piVar5[5] = 0;
                if (*(int *)(iVar2 + 0x18) == 0) {
                  FUN_0002d024();
                  FUN_000436c8();
                  piVar5[4] = 100;
                }
              }
LAB_000265b2:
              if ((*(int *)(iVar3 + 0x18) == 3) || (*(int *)(iVar3 + 0x18) == 1)) goto LAB_000265c6;
LAB_000265be:
              if ((*(int *)(iVar2 + 0x18) == 1) && (*_DAT_00026768 == '\0')) {
                if (*(char *)(iVar3 + 2) == '\0') {
                  FUN_0002e518();
                }
                else {
                  FUN_0002d4b0();
                  *(undefined1 *)(iVar3 + 2) = 0;
                }
              }
              FUN_00028778();
              FUN_0002789c();
              if (99 < piVar5[1]) {
                piVar5[1] = 0;
                FUN_00033856(1);
                *DAT_000266ec = *DAT_000266ec + 100;
                FUN_0003389a(1);
                FUN_000403a4();
                FUN_00037cc8();
                FUN_00037fd0();
                FUN_00026920();
                if ((*puVar1 & 1) != 0) {
                  FUN_00026d18();
                }
                if (*(char *)(iVar3 + 4) != '\0') {
                  *(undefined1 *)(iVar3 + 4) = 0;
                  *(undefined4 *)(iVar2 + 0x5c) = 0;
                }
                iVar10 = piVar5[2];
                piVar5[2] = iVar10 + 100;
                if (999 < iVar10 + 100) {
                  piVar5[2] = 0;
                  if ((*(int *)(iVar2 + 0x18) == 1) && (*_DAT_00026768 == '\0')) {
                    FUN_0002e398();
                  }
                  FUN_00026110();
                }
                iVar10 = piVar5[3];
                piVar5[3] = iVar10 + 100;
                if (4999 < iVar10 + 100) {
                  piVar5[3] = 0;
                  uVar12 = FUN_00036f6c(5);
                  FUN_0002fd7c(uVar12,0);
                }
              }
              if (*pcVar11 != '\0' || iVar9 != 0) {
                if (*(int *)(iVar2 + 0x18) == 0) {
                  iVar10 = FUN_0003cb00();
                  if (iVar10 == 0) {
                    FUN_0003a0d4();
                  }
                  if (piVar5[4] == 100) {
                    FUN_000436f0();
                    piVar5[4] = 1;
                  }
                }
                if (*pcVar11 != '\0') {
                  iVar9 = 7;
                }
                iVar10 = FUN_0002b0b8(1,0);
                if (iVar10 == 0) {
                  FUN_000277cc(s_S_K_Fake_00026888);
                  if ((iVar9 != 0) && (iVar9 = iVar9 + -1, iVar9 == 0)) {
                    FUN_0002b3c4();
                  }
                }
                else if ((-1 < (int)((uint)(byte)*puVar1 << 0x1d)) ||
                        (iVar10 = FUN_0003499c(), iVar10 == 5)) {
                  FUN_000277cc(s_S_K_True_0002676b + 1);
                  if ((*puVar1 & 6) == 0) {
                    FUN_0002ce7c();
                  }
                  else {
                    *DAT_00026748 = 0;
                    FUN_0002cdfc();
                  }
                  FUN_0002aa10();
                  FUN_00029bcc();
                  FUN_00026d18();
                  local_28 = local_28 | 2;
                }
              }
            }
            else {
              if (-1 < (int)(*puVar1 << 0x1d)) goto LAB_000265b2;
              if ((*piVar4 == 0) || (*piVar4 == *(int *)(iVar3 + 0x20))) {
                *(undefined4 *)(iVar3 + 0x18) = 2;
                goto LAB_000265be;
              }
              *(undefined4 *)(iVar3 + 0x18) = 3;
              *(undefined4 *)(iVar3 + 0x1c) = 0x32;
LAB_000265c6:
              local_28 = local_28 | 1;
            }
          } while (local_28 == 0);
          *(undefined1 *)(iVar3 + 5) = 0;
          if ((((int)((uint)(byte)*puVar1 << 0x1e) < 0) &&
              (*DAT_00026894 = 0, *(int *)(iVar2 + 0x18) == 0)) &&
             (iVar9 = FUN_0003cb00(), iVar9 == 0)) {
            FUN_0003a0d4();
          }
          FUN_00042d14();
          if ((int)(*puVar1 << 0x1e) < 0) {
            if (*(int *)(iVar2 + 0x18) == 0) {
              FUN_0002d13c();
            }
            iVar9 = FUN_00039ebc();
            if (iVar9 != 0) {
              FUN_000443a0(0x1c2);
            }
          }
          else if ((*puVar1 & 1) != 0) {
            FUN_00025b3c(1);
          }
          *(undefined4 *)(iVar2 + 0x5c) = 0;
          *(undefined4 *)(iVar3 + 0x10) = 0;
          *(undefined4 *)(iVar3 + 0x24) = 0;
          if ((*puVar1 & 1) != 0) {
            *_DAT_00026898 = 5;
            FUN_0003362c(0x81,3,0,2);
          }
          FUN_0002d508();
          FUN_0002e4c8();
          thunk_FUN_0002b37c();
          pcVar11 = s_Wake_up_0002689b + 1;
          goto LAB_0002687a;
        }
        break;
      case 1:
        *(undefined4 *)(iVar2 + 0x58) = 0;
        thunk_FUN_00032cd8();
        pcVar11 = s_PM_Rn_0002672c;
LAB_0002687a:
        FUN_000277cc(pcVar11);
        return;
      case 3:
      case 4:
        uVar8 = *puVar1;
        if (((-1 < (int)(uVar8 << 0x1e)) && ((uVar8 & 1) == 0)) && ((int)(uVar8 << 0x1d) < 0)) {
          if ((*piVar4 == 0) || (*piVar4 == *(int *)(iVar3 + 0x20))) {
            *(undefined4 *)(iVar3 + 0x18) = 2;
            *(undefined4 *)(iVar3 + 0x1c) = 0x32;
            *(int *)(iVar3 + 0x20) = *piVar4;
            pcVar11 = s_PM_nRs_000268ac;
          }
          else {
            *(undefined4 *)(iVar3 + 0x18) = 3;
            *(undefined4 *)(iVar3 + 0x1c) = 5000;
            *(int *)(iVar3 + 0x20) = *piVar4;
            pcVar11 = s_PM_nNRs_000268a4;
          }
          goto LAB_0002687a;
        }
      }
    }
  }
  return;
}

