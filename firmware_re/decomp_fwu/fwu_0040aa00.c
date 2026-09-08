// FUN_0040aa00 @0040aa00

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_0040aa00(int param_1,int *param_2)

{
  undefined8 uVar1;
  byte bVar2;
  char cVar3;
  byte ******ppppppbVar4;
  byte ******ppppppbVar5;
  byte ******ppppppbVar6;
  byte *pbVar7;
  undefined1 uVar8;
  int iVar9;
  byte *******pppppppbVar10;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar11;
  basic_ostream<char,std::char_traits<char>_> *pbVar12;
  undefined4 *puVar13;
  int *piVar14;
  undefined4 *******pppppppuVar15;
  byte *pbVar16;
  char **ppcVar17;
  char *******pppppppcVar18;
  byte *******pppppppbVar19;
  undefined4 ******ppppppuVar20;
  undefined4 uVar21;
  int iVar22;
  uint uVar23;
  uint uVar24;
  char *pcVar25;
  void *pvVar26;
  int iVar27;
  char **ppcVar28;
  bool bVar29;
  char *in_stack_fffffbe0;
  char *pcVar30;
  char local_3fc [16];
  undefined1 local_3ec [16];
  undefined1 local_3dc [16];
  undefined1 local_3cc [16];
  undefined1 local_3bc [16];
  undefined1 local_3ac [16];
  undefined1 local_39c [16];
  undefined1 local_38c [16];
  undefined1 local_37c [16];
  undefined1 local_36c [16];
  undefined1 local_35c [16];
  undefined1 local_34c [16];
  undefined1 local_33c [16];
  undefined1 local_32c [16];
  undefined1 local_31c [16];
  char local_30c [16];
  undefined1 local_2fc [16];
  undefined1 local_2ec [16];
  undefined1 local_2dc [16];
  undefined1 local_2cc [16];
  undefined1 local_2bc [16];
  uint local_2ac;
  undefined4 local_2a8;
  uint local_2a4;
  undefined4 local_2a0;
  uint local_29c;
  int local_298;
  uint local_294;
  undefined4 local_290;
  uint local_28c;
  int local_288;
  undefined4 ******local_284 [2];
  char acStack_27c [8];
  int local_274;
  uint uStack_270;
  uint local_26c;
  uint local_268;
  uint local_264;
  uint local_260;
  byte ******local_25c;
  uint local_258;
  byte *****local_254;
  undefined4 *****local_250;
  undefined4 *****pppppuStack_24c;
  undefined4 *****pppppuStack_248;
  undefined4 *****pppppuStack_244;
  undefined8 local_240;
  int local_238;
  uint local_234;
  byte ******local_230;
  char *local_22c;
  undefined4 uStack_228;
  undefined *local_224 [4];
  undefined *local_214 [2];
  undefined **local_20c [2];
  basic_iostream<char,std::char_traits<char>_> local_204 [48];
  undefined4 local_1d4;
  undefined4 local_1d0;
  basic_ios<char,std::char_traits<char>_> local_1bc [68];
  int iStack_178;
  undefined *local_174 [4];
  undefined *local_164 [2];
  undefined **local_15c [2];
  basic_iostream<char,std::char_traits<char>_> local_154 [48];
  undefined4 local_124;
  undefined4 local_120;
  basic_ios<char,std::char_traits<char>_> local_10c [72];
  char ******local_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  uint local_b4;
  uint local_b0;
  byte ******local_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  uint local_9c;
  uint local_98;
  byte ******local_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  uint local_84;
  uint local_80;
  int *local_7c;
  byte ******local_78;
  byte *****pppppbStack_74;
  byte *****pppppbStack_70;
  byte *****pppppbStack_6c;
  byte *****local_68;
  byte *****pppppbStack_64;
  byte ******local_60;
  byte *****pppppbStack_5c;
  byte *****pppppbStack_58;
  byte *****pppppbStack_54;
  undefined8 local_50;
  void *local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  uint local_34;
  byte *local_30;
  byte *local_2c;
  int local_28;
  char local_24;
  undefined8 local_20;
  int local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0041d933;
  local_10 = ExceptionList;
  local_14 = DAT_00442010 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_268 = 0;
  uStack_c0 = 0;
  uStack_bc = 0;
  uStack_b8 = 0;
  local_22c = (char *)0x0;
  local_b4 = 0;
  local_b0 = 0xf;
  local_c4 = (char ******)0x0;
  uStack_90 = 0;
  uStack_8c = 0;
  uStack_88 = 0;
  local_84 = 0;
  local_80 = 0xf;
  local_94 = (byte ******)0x0;
  pppppbStack_5c = (byte *****)0x0;
  pppppbStack_58 = (byte *****)0x0;
  pppppbStack_54 = (byte *****)0x0;
  local_258 = 0xf;
  local_50 = 0xf00000000;
  local_60 = (byte ******)0x0;
  pppppbStack_74 = (byte *****)0x0;
  pppppbStack_70 = (byte *****)0x0;
  pppppbStack_6c = (byte *****)0x0;
  local_68 = (byte *****)0x0;
  local_254 = (byte *****)0xf;
  pppppbStack_64 = (byte *****)0xf;
  local_78 = (byte ******)0x0;
  local_8._0_1_ = 3;
  local_8._1_3_ = 0;
  local_48 = (void *)0x0;
  uStack_44 = 0;
  uStack_40 = 0;
  uStack_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_238 = param_1;
  local_7c = param_2;
  FUN_00404c20(&local_48,&DAT_0043d114,0);
  local_8._0_1_ = 4;
  memset(local_224,0,0xb0);
  local_224[0] = &DAT_0043ed68;
  local_214[0] = &DAT_0043e64c;
  std::basic_ios<char,std::char_traits<char>_>::basic_ios<char,std::char_traits<char>_>(local_1bc);
  local_8 = CONCAT31(local_8._1_3_,5);
  local_264 = 8;
  local_268 = 8;
  std::basic_iostream<char,std::char_traits<char>_>::basic_iostream<char,std::char_traits<char>_>
            ((basic_iostream<char,std::char_traits<char>_> *)local_224,
             (basic_streambuf<char,std::char_traits<char>_> *)local_20c);
  local_8 = 6;
  *(undefined ***)((int)local_224 + *(int *)(local_224[0] + 4)) =
       std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)((int)&uStack_228 + *(int *)(local_224[0] + 4)) = *(int *)(local_224[0] + 4) + -0x68;
  std::basic_streambuf<char,std::char_traits<char>_>::basic_streambuf<char,std::char_traits<char>_>
            ((basic_streambuf<char,std::char_traits<char>_> *)local_20c);
  uVar23 = DAT_00442034;
  local_20c[0] = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  local_1d4 = 0;
  local_1d0 = 0;
  local_8._0_1_ = 7;
  local_20 = 0;
  local_18 = 0;
  if (DAT_00442034 != 0) {
    if (0x7fffffff < DAT_00442034) {
                    /* WARNING: Subroutine does not return */
      FUN_00401ee0();
    }
    FUN_00401450(&local_20,DAT_00442034);
    pvVar26 = (byte *)local_20;
    memset((byte *)local_20,0,uVar23);
    local_20 = CONCAT44((int)pvVar26 + uVar23,(byte *)local_20);
    param_1 = local_238;
  }
  local_24 = '\0';
  local_8._0_1_ = 9;
  if (DAT_004428ec != '\0') {
    local_26c = 500;
    local_268 = 0;
    FUN_00402280(&local_26c);
  }
  if (DAT_0044202a == '\0') {
    pcVar30 = (char *)0x0;
    FUN_00404c20(&stack0xfffffbe0,"FW Update Complete!",0x13);
    FUN_00405410(pcVar30);
    uVar21 = 0;
  }
  else {
    iVar27 = 0;
    if (0 < DAT_00442038) {
      iVar22 = param_1 * 0x5c;
      local_260 = 1000;
      local_25c = (byte ******)0x0;
      local_238 = iVar22;
      do {
        FUN_00402280(&local_260);
        iVar9 = FUN_004017f0((void *)(iVar22 + DAT_00442938),local_7c);
        if ((iVar9 != 0) && (iVar9 = FUN_00401a60((void *)(iVar22 + DAT_00442938)), iVar9 != 0)) {
          if (DAT_004428ed != '\0') {
            uStack_228._3_1_ = '\0';
            FUN_0040f4b0(&local_20,DAT_00442034,(byte *)((int)&uStack_228 + 3));
            if (DAT_004428ed != '\0') {
              if (((local_20._4_4_ == (byte *)local_20) ||
                  (*(byte *)local_20 = 0x12, (uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 2
                  )) || (((byte *)local_20)[1] = 0,
                        (uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 3)) {
LAB_0040cb96:
                    /* WARNING: Subroutine does not return */
                FUN_0040fef0();
              }
              ((byte *)local_20)[2] = 2;
            }
            pppppppbVar10 =
                 (byte *******)FUN_00401b30((void *)(iVar22 + DAT_00442938),(int *)&local_20);
            if (pppppppbVar10 != (byte *******)0x0) {
              FUN_0040ff00(&local_48,"Write Data Fail !!!",0x13);
              FUN_0040fc30(&stack0xfffffbe0,&local_48);
              FUN_00405270(in_stack_fffffbe0);
              uVar21 = 0xe;
              goto LAB_0040aebc;
            }
            local_234 = 500;
            local_230 = (byte ******)pppppppbVar10;
            FUN_00402280(&local_234);
            FUN_00405980((int *)&local_30,(void *)(iVar22 + DAT_00442938));
            if (local_24 == '\0') {
              FUN_0040ff00(&local_48,"Read Data Fail !!!",0x12);
              FUN_0040fc30(&stack0xfffffbe0,&local_48);
              FUN_00405270(in_stack_fffffbe0);
              uVar21 = 0xd;
              goto LAB_0040aebc;
            }
            if (DAT_004428ee != '\0') {
              FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"[DBG] ");
              uVar23 = 0;
              if (0 < *(int *)(local_238 + 0x18 + DAT_00442938)) {
                do {
                  pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                      ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                       FUN_00401310);
                  if ((uint)((int)local_2c - (int)local_30) <= uVar23) goto LAB_0040cb96;
                  pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                      ((basic_ostream<char,std::char_traits<char>_> *)pbVar11,
                                       (uint)local_30[uVar23]);
                  FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,",");
                  uVar23 = uVar23 + 1;
                } while ((int)uVar23 < *(int *)(local_238 + 0x18 + DAT_00442938));
              }
              std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00402220);
              iVar22 = local_238;
            }
            if ((uint)((int)local_2c - (int)local_30) < 5) goto LAB_0040cb96;
            if (local_30[4] == 0) {
              FUN_0040ff00(&local_48,"[S] Master is disconnect",0x18);
              FUN_0040fc30(&stack0xfffffbe0,&local_48);
              FUN_00405340(in_stack_fffffbe0);
              goto LAB_0040ae85;
            }
          }
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                 "Device in Application Mode!");
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,FUN_00402220);
          local_230 = local_60;
          local_25c = local_78;
          goto LAB_0040b170;
        }
        FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,".");
LAB_0040ae85:
        iVar27 = iVar27 + 1;
      } while (iVar27 < DAT_00442038);
    }
    FUN_0040ff00(&local_48,"Device connect fail !!",0x16);
    FUN_0040fc30(&stack0xfffffbe0,&local_48);
    FUN_00405270(in_stack_fffffbe0);
    uVar21 = 10;
  }
LAB_0040aebc:
  local_25c = local_78;
  pppppppbVar10 = (byte *******)local_60;
LAB_0040aec8:
  if ((local_24 != '\0') && (local_30 != (byte *)0x0)) {
    pbVar16 = local_30;
    if ((0xfff < (uint)(local_28 - (int)local_30)) &&
       (pbVar16 = *(byte **)(local_30 + -4), (byte *)0x1f < local_30 + (-4 - (int)pbVar16)))
    goto LAB_0040b0e2;
    FUN_0041c647(pbVar16);
    local_30 = (byte *)0x0;
    local_2c = (byte *)0x0;
    local_28 = 0;
  }
  if ((byte *)local_20 != (void *)0x0) {
    pvVar26 = (byte *)local_20;
    if ((0xfff < (uint)(local_18 - (int)(byte *)local_20)) &&
       (pvVar26 = *(void **)((int)(byte *)local_20 + -4),
       0x1f < (uint)((int)(byte *)local_20 + (-4 - (int)pvVar26)))) goto LAB_0040b0e2;
    FUN_0041c647(pvVar26);
    local_20 = 0;
    local_18 = 0;
  }
  *(undefined ***)((int)local_224 + *(int *)(local_224[0] + 4)) =
       std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)((int)&uStack_228 + *(int *)(local_224[0] + 4)) = *(int *)(local_224[0] + 4) + -0x68;
  local_20c[0] = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  FUN_0040fe50((int)local_20c);
  std::basic_streambuf<char,std::char_traits<char>_>::~basic_streambuf<char,std::char_traits<char>_>
            ((basic_streambuf<char,std::char_traits<char>_> *)local_20c);
  std::basic_iostream<char,std::char_traits<char>_>::~basic_iostream<char,std::char_traits<char>_>
            (local_204);
  std::basic_ios<char,std::char_traits<char>_>::~basic_ios<char,std::char_traits<char>_>(local_1bc);
  if (0xf < local_34) {
    pvVar26 = local_48;
    if ((0xfff < local_34 + 1) &&
       (pvVar26 = *(void **)((int)local_48 + -4), 0x1f < (uint)((int)local_48 + (-4 - (int)pvVar26))
       )) goto LAB_0040b0e2;
    FUN_0041c647(pvVar26);
  }
  if ((byte ******)0xf < local_254) {
    pppppppbVar19 = (byte *******)local_25c;
    if ((0xfff < (int)local_254 + 1U) &&
       (pppppppbVar19 = (byte *******)local_25c[-1],
       (byte *)0x1f < (byte *)((int)local_25c + (-4 - (int)pppppppbVar19)))) goto LAB_0040b0e2;
    FUN_0041c647(pppppppbVar19);
  }
  if (0xf < local_258) {
    pppppppbVar19 = pppppppbVar10;
    if ((0xfff < local_258 + 1) &&
       (pppppppbVar19 = (byte *******)pppppppbVar10[-1],
       (byte *)0x1f < (byte *)((int)pppppppbVar10 + (-4 - (int)pppppppbVar19)))) goto LAB_0040b0e2;
    FUN_0041c647(pppppppbVar19);
  }
  if (0xf < local_80) {
    pppppppbVar10 = (byte *******)local_94;
    if ((0xfff < local_80 + 1) &&
       (pppppppbVar10 = (byte *******)local_94[-1],
       (byte *)0x1f < (byte *)((int)local_94 + (-4 - (int)pppppppbVar10)))) goto LAB_0040b0e2;
    FUN_0041c647(pppppppbVar10);
  }
  local_84 = 0;
  local_80 = 0xf;
  local_94 = (byte ******)((uint)local_94 & 0xffffff00);
  if (0xf < local_b0) {
    pppppppcVar18 = (char *******)local_c4;
    if ((0xfff < local_b0 + 1) &&
       (pppppppcVar18 = (char *******)local_c4[-1],
       (char *)0x1f < (char *)((int)local_c4 + (-4 - (int)pppppppcVar18)))) {
LAB_0040b0e2:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_0041c647(pppppppcVar18);
  }
  ExceptionList = local_10;
  return uVar21;
LAB_0040b170:
  if ((DAT_004428ec != '\0') && (DAT_00442028 != '\0')) {
    iVar27 = 0;
    do {
      uStack_228._3_1_ = '\0';
      FUN_0040f4b0(&local_20,DAT_00442034,(byte *)((int)&uStack_228 + 3));
      if ((DAT_004428ed == '\0') &&
         ((uVar23 = FUN_0040f960(&DAT_0044203c,(byte *)&DAT_00442054), uVar23 == 0 ||
          (uVar23 = FUN_0040f960(&DAT_00442084,(byte *)&DAT_0044206c), uVar23 == 0)))) {
        if (local_20._4_4_ == (byte *)local_20) goto LAB_0040cb96;
        *(byte *)local_20 = 0xa1;
      }
      else {
        if ((local_20._4_4_ == (byte *)local_20) ||
           ((*(byte *)local_20 = 0x12, (uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 2 ||
            (((byte *)local_20)[1] = 0x12, (uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 3))
           )) goto LAB_0040cb96;
        ((byte *)local_20)[2] = 2;
      }
      pppppuStack_24c = (undefined4 ******)0x0;
      pppppuStack_248 = (undefined4 ******)0x0;
      pppppuStack_244 = (undefined4 ******)0x0;
      local_240 = 0xf00000000;
      local_250 = (undefined4 ******)0x0;
      local_8._0_1_ = 10;
      FUN_0040f0a0(local_224,&local_250);
      local_8._0_1_ = 9;
      uVar8 = (undefined1)local_8;
      local_8._0_1_ = 9;
      if (0xf < local_240._4_4_) {
        ppppppuVar20 = (undefined4 ******)local_250;
        if ((0xfff < local_240._4_4_ + 1) &&
           (ppppppuVar20 = (undefined4 ******)local_250[-1],
           0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
        FUN_0041c647(ppppppuVar20);
      }
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)local_214,FUN_00401310);
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_3cc));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if (local_20._4_4_ == (byte *)local_20) goto LAB_0040cb96;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar12,(uint)*(byte *)local_20);
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_3bc));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if ((uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 2) goto LAB_0040cb96;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar12,(uint)*(byte *)((int)(byte *)local_20 + 1));
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_3ac));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if ((uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 3) goto LAB_0040cb96;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar12,(uint)*(byte *)((int)(byte *)local_20 + 2));
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_38c));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if ((uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 4) goto LAB_0040cb96;
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                (pbVar12,(uint)*(byte *)((int)(byte *)local_20 + 3));
      pppppppbVar10 = (byte *******)FUN_0040f1a0(local_224,&local_250);
      if (&local_60 != pppppppbVar10) {
        if (0xf < local_258) {
          pppppppbVar19 = (byte *******)local_230;
          if ((0xfff < local_258 + 1) &&
             (pppppppbVar19 = (byte *******)local_230[-1], uVar8 = (undefined1)local_8,
             (byte *)0x1f < (byte *)((int)local_230 + (-4 - (int)pppppppbVar19))))
          goto LAB_0040ca8e;
          FUN_0041c647(pppppppbVar19);
        }
        local_230 = *pppppppbVar10;
        pppppbStack_5c = (byte *****)pppppppbVar10[1];
        pppppbStack_58 = (byte *****)pppppppbVar10[2];
        pppppbStack_54 = (byte *****)pppppppbVar10[3];
        uVar1 = *(undefined8 *)(pppppppbVar10 + 4);
        local_50._4_4_ = (uint)((ulonglong)uVar1 >> 0x20);
        local_258 = local_50._4_4_;
        pppppppbVar10[4] = (byte ******)0x0;
        pppppppbVar10[5] = (byte ******)0xf;
        *(undefined1 *)pppppppbVar10 = 0;
        local_60 = local_230;
        local_50 = uVar1;
      }
      if (0xf < local_240._4_4_) {
        ppppppuVar20 = (undefined4 ******)local_250;
        if ((0xfff < local_240._4_4_ + 1) &&
           (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
           0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
        FUN_0041c647(ppppppuVar20);
      }
      iVar22 = local_238;
      iVar9 = FUN_00401b30((void *)(local_238 + DAT_00442938),(int *)&local_20);
      if (iVar9 != 0) goto LAB_0040cb35;
      local_28c = 500;
      local_288 = iVar9;
      FUN_00402280(&local_28c);
      FUN_00405980((int *)&local_30,(void *)(iVar22 + DAT_00442938));
      if (local_24 == '\0') goto LAB_0040cb00;
      pppppuStack_24c = (undefined4 ******)0x0;
      pppppuStack_248 = (undefined4 ******)0x0;
      pppppuStack_244 = (undefined4 ******)0x0;
      local_240 = 0xf00000000;
      local_250 = (undefined4 ******)0x0;
      local_8._0_1_ = 0xb;
      FUN_0040f0a0(local_224,&local_250);
      local_8._0_1_ = 9;
      if (0xf < local_240._4_4_) {
        ppppppuVar20 = (undefined4 ******)local_250;
        if ((0xfff < local_240._4_4_ + 1) &&
           (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
           0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
        FUN_0041c647(ppppppuVar20);
      }
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)local_214,FUN_00401310);
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_37c));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if (local_2c == local_30) goto LAB_0040cb96;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar12,(uint)*local_30);
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_33c));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if ((uint)((int)local_2c - (int)local_30) < 2) goto LAB_0040cb96;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar12,(uint)local_30[1]);
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_39c));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if ((uint)((int)local_2c - (int)local_30) < 3) goto LAB_0040cb96;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          (pbVar12,(uint)local_30[2]);
      puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_36c));
      pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
      pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
           (basic_ostream<char,std::char_traits<char>_>)0x30;
      if ((uint)((int)local_2c - (int)local_30) < 4) goto LAB_0040cb96;
      std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,(uint)local_30[3]);
      pppppppbVar10 = (byte *******)FUN_0040f1a0(local_224,&local_250);
      if (&local_78 != pppppppbVar10) {
        if ((byte ******)0xf < local_254) {
          pppppppbVar19 = (byte *******)local_25c;
          if ((0xfff < (int)local_254 + 1U) &&
             (pppppppbVar19 = (byte *******)local_25c[-1], uVar8 = (undefined1)local_8,
             (byte *)0x1f < (byte *)((int)local_25c + (-4 - (int)pppppppbVar19))))
          goto LAB_0040ca8e;
          FUN_0041c647(pppppppbVar19);
        }
        local_78 = *pppppppbVar10;
        pppppbStack_74 = (byte *****)pppppppbVar10[1];
        pppppbStack_70 = (byte *****)pppppppbVar10[2];
        pppppbStack_6c = (byte *****)pppppppbVar10[3];
        local_68 = (byte *****)pppppppbVar10[4];
        pppppbStack_64 = (byte *****)pppppppbVar10[5];
        local_254 = (byte *****)pppppppbVar10[5];
        pppppppbVar10[4] = (byte ******)0x0;
        pppppppbVar10[5] = (byte ******)0xf;
        *(undefined1 *)pppppppbVar10 = 0;
        local_25c = local_78;
      }
      if (0xf < local_240._4_4_) {
        ppppppuVar20 = (undefined4 ******)local_250;
        if ((0xfff < local_240._4_4_ + 1) &&
           (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
           0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
        FUN_0041c647(ppppppuVar20);
      }
      ppppppbVar6 = local_230;
      iVar27 = iVar27 + 1;
      uStack_228._3_1_ = 0xf < local_258;
      pppppppbVar10 = &local_60;
      if (0xf < local_258) {
        pppppppbVar10 = (byte *******)local_230;
      }
      pppppppbVar19 = &local_78;
      if ((byte ******)0xf < local_254) {
        pppppppbVar19 = (byte *******)local_25c;
      }
      uStack_228._2_1_ = (byte ******)0xf < local_254;
      ppppppbVar5 = (byte ******)local_68;
      if ((byte ******)local_68 == (byte ******)local_50) {
        while (ppppppbVar4 = ppppppbVar5 + -1, (byte ******)0x3 < ppppppbVar5) {
          if (*pppppppbVar19 != *pppppppbVar10) goto LAB_0040b7b6;
          pppppppbVar19 = pppppppbVar19 + 1;
          pppppppbVar10 = pppppppbVar10 + 1;
          ppppppbVar5 = ppppppbVar4;
        }
        if (ppppppbVar4 == (byte ******)0xfffffffc) {
LAB_0040b7ea:
          uVar23 = 0;
        }
        else {
LAB_0040b7b6:
          bVar29 = *(byte *)pppppppbVar19 < *(byte *)pppppppbVar10;
          if ((*(byte *)pppppppbVar19 == *(byte *)pppppppbVar10) &&
             ((ppppppbVar4 == (byte ******)0xfffffffd ||
              ((bVar29 = *(byte *)((int)pppppppbVar19 + 1) < *(byte *)((int)pppppppbVar10 + 1),
               *(byte *)((int)pppppppbVar19 + 1) == *(byte *)((int)pppppppbVar10 + 1) &&
               ((ppppppbVar4 == (byte ******)0xfffffffe ||
                ((bVar29 = *(byte *)((int)pppppppbVar19 + 2) < *(byte *)((int)pppppppbVar10 + 2),
                 *(byte *)((int)pppppppbVar19 + 2) == *(byte *)((int)pppppppbVar10 + 2) &&
                 ((ppppppbVar4 == (byte ******)0xffffffff ||
                  (bVar29 = *(byte *)((int)pppppppbVar19 + 3) < *(byte *)((int)pppppppbVar10 + 3),
                  *(byte *)((int)pppppppbVar19 + 3) == *(byte *)((int)pppppppbVar10 + 3)))))))))))))
          goto LAB_0040b7ea;
          uVar23 = -(uint)bVar29 | 1;
        }
        if (uVar23 == 0) {
          memset(local_174,0,0xb0);
          local_174[0] = &DAT_0043ed68;
          local_164[0] = &DAT_0043e64c;
          std::basic_ios<char,std::char_traits<char>_>::basic_ios<char,std::char_traits<char>_>
                    (local_10c);
          local_8 = CONCAT31(local_8._1_3_,0xc);
          local_268 = local_264 | 0x20;
          local_264 = local_268;
          std::basic_iostream<char,std::char_traits<char>_>::
          basic_iostream<char,std::char_traits<char>_>
                    ((basic_iostream<char,std::char_traits<char>_> *)local_174,
                     (basic_streambuf<char,std::char_traits<char>_> *)local_15c);
          local_8 = 0xd;
          *(undefined ***)((int)local_174 + *(int *)(local_174[0] + 4)) =
               std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
          *(int *)((int)&iStack_178 + *(int *)(local_174[0] + 4)) =
               *(int *)(local_174[0] + 4) + -0x68;
          std::basic_streambuf<char,std::char_traits<char>_>::
          basic_streambuf<char,std::char_traits<char>_>
                    ((basic_streambuf<char,std::char_traits<char>_> *)local_15c);
          local_15c[0] = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::
                         vftable;
          local_124 = 0;
          local_120 = 0;
          local_8._0_1_ = 0xe;
          uVar23 = 4;
          goto LAB_0040b980;
        }
      }
      if (iVar27 == 1) {
        local_294 = 3000;
        local_290 = 0;
        FUN_00402280(&local_294);
      }
      else if (iVar27 == 10) goto LAB_0040cb00;
      pppppppbVar10 = &local_60;
      if (uStack_228._3_1_ != '\0') {
        pppppppbVar10 = (byte *******)ppppppbVar6;
      }
      pppppppbVar19 = &local_78;
      if (uStack_228._2_1_ != '\0') {
        pppppppbVar19 = (byte *******)local_25c;
      }
      ppppppbVar6 = (byte ******)local_68;
      if ((byte ******)local_68 == (byte ******)local_50) {
        while (ppppppbVar5 = ppppppbVar6 + -1, (byte ******)0x3 < ppppppbVar6) {
          if (*pppppppbVar19 != *pppppppbVar10) goto LAB_0040b86c;
          pppppppbVar19 = pppppppbVar19 + 1;
          pppppppbVar10 = pppppppbVar10 + 1;
          ppppppbVar6 = ppppppbVar5;
        }
        if (ppppppbVar5 == (byte ******)0xfffffffc) {
LAB_0040b8a0:
          uVar23 = 0;
        }
        else {
LAB_0040b86c:
          bVar29 = *(byte *)pppppppbVar19 < *(byte *)pppppppbVar10;
          if ((*(byte *)pppppppbVar19 == *(byte *)pppppppbVar10) &&
             ((ppppppbVar5 == (byte ******)0xfffffffd ||
              ((bVar29 = *(byte *)((int)pppppppbVar19 + 1) < *(byte *)((int)pppppppbVar10 + 1),
               *(byte *)((int)pppppppbVar19 + 1) == *(byte *)((int)pppppppbVar10 + 1) &&
               ((ppppppbVar5 == (byte ******)0xfffffffe ||
                ((bVar29 = *(byte *)((int)pppppppbVar19 + 2) < *(byte *)((int)pppppppbVar10 + 2),
                 *(byte *)((int)pppppppbVar19 + 2) == *(byte *)((int)pppppppbVar10 + 2) &&
                 ((ppppppbVar5 == (byte ******)0xffffffff ||
                  (bVar29 = *(byte *)((int)pppppppbVar19 + 3) < *(byte *)((int)pppppppbVar10 + 3),
                  *(byte *)((int)pppppppbVar19 + 3) == *(byte *)((int)pppppppbVar10 + 3)))))))))))))
          goto LAB_0040b8a0;
          uVar23 = -(uint)bVar29 | 1;
        }
        if (uVar23 == 0) break;
      }
    } while (iVar27 < 10);
  }
  goto LAB_0040ba63;
LAB_0040cb35:
  FUN_0040ff00(&local_48,"Write Data Fail !!!",0x13);
  FUN_0040fc30(&stack0xfffffbe0,&local_48);
  FUN_00405270(in_stack_fffffbe0);
  uVar21 = 0xe;
  pppppppbVar10 = (byte *******)local_230;
  goto LAB_0040aec8;
LAB_0040cb00:
  FUN_0040ff00(&local_48,"Read Data Fail !!!",0x12);
  FUN_0040fc30(&stack0xfffffbe0,&local_48);
  FUN_00405270(in_stack_fffffbe0);
  uVar21 = 0xd;
  pppppppbVar10 = (byte *******)local_230;
  goto LAB_0040aec8;
code_r0x0040c8ac:
  FUN_0040ff00(&local_48,"FW Update Fail !!!",0x12);
  FUN_0040fc30(&stack0xfffffbec,&local_48);
  FUN_00405270(pcVar30);
  uVar21 = 0xc;
  pppppppbVar10 = (byte *******)local_230;
  goto LAB_0040aec8;
  while( true ) {
    FUN_004115d0((basic_ostream<char,std::char_traits<char>_> *)local_164,local_30[uVar23]);
    uVar23 = uVar23 + 1;
    if (0xf < (int)uVar23) break;
LAB_0040b980:
    if ((uint)((int)local_2c - (int)local_30) <= uVar23) goto LAB_0040cb96;
  }
  FUN_00411870((basic_istream<char,std::char_traits<char>_> *)local_174,&local_c4);
  if (DAT_004428ee != '\0') {
    pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"[DBG] sn = ");
    pppppppcVar18 = &local_c4;
    if (0xf < local_b0) {
      pppppppcVar18 = (char *******)local_c4;
    }
    pbVar12 = FUN_004135e0(pbVar12,(char *)pppppppcVar18,local_b4);
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,FUN_00402220);
  }
  local_8._0_1_ = 9;
  *(undefined ***)((int)local_174 + *(int *)(local_174[0] + 4)) =
       std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  *(int *)((int)&iStack_178 + *(int *)(local_174[0] + 4)) = *(int *)(local_174[0] + 4) + -0x68;
  local_15c[0] = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::vftable;
  FUN_0040fe50((int)local_15c);
  std::basic_streambuf<char,std::char_traits<char>_>::~basic_streambuf<char,std::char_traits<char>_>
            ((basic_streambuf<char,std::char_traits<char>_> *)local_15c);
  std::basic_iostream<char,std::char_traits<char>_>::~basic_iostream<char,std::char_traits<char>_>
            (local_154);
  std::basic_ios<char,std::char_traits<char>_>::~basic_ios<char,std::char_traits<char>_>(local_10c);
LAB_0040ba63:
  iVar27 = 0;
  do {
    uStack_228._2_1_ = '\0';
    FUN_0040f4b0(&local_20,DAT_00442034,(byte *)((int)&uStack_228 + 2));
    if (local_20._4_4_ == (byte *)local_20) goto LAB_0040cb96;
    *(byte *)local_20 = 0x12;
    pppppuStack_24c = (undefined4 ******)0x0;
    pppppuStack_248 = (undefined4 ******)0x0;
    pppppuStack_244 = (undefined4 ******)0x0;
    local_240 = 0xf00000000;
    local_250 = (undefined4 ******)0x0;
    local_8._0_1_ = 0xf;
    FUN_0040f0a0(local_224,&local_250);
    local_8._0_1_ = 9;
    if (0xf < local_240._4_4_) {
      ppppppuVar20 = (undefined4 ******)local_250;
      if ((0xfff < local_240._4_4_ + 1) &&
         (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
         0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
      FUN_0041c647(ppppppuVar20);
    }
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)local_214,FUN_00401310);
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_3dc));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if (local_20._4_4_ == (byte *)local_20) goto LAB_0040cb96;
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        (pbVar12,(uint)*(byte *)local_20);
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_3ec));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if ((uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 2) goto LAB_0040cb96;
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        (pbVar12,(uint)*(byte *)((int)(byte *)local_20 + 1));
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_2bc));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if ((uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 3) goto LAB_0040cb96;
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        (pbVar12,(uint)*(byte *)((int)(byte *)local_20 + 2));
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_2cc));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if ((uint)((int)local_20._4_4_ - (int)(byte *)local_20) < 4) goto LAB_0040cb96;
    std::basic_ostream<char,std::char_traits<char>_>::operator<<
              (pbVar12,(uint)*(byte *)((int)(byte *)local_20 + 3));
    pppppppbVar10 = (byte *******)FUN_0040f1a0(local_224,&local_250);
    if (&local_60 != pppppppbVar10) {
      if (0xf < local_258) {
        pppppppbVar19 = (byte *******)local_230;
        if ((0xfff < local_258 + 1) &&
           (pppppppbVar19 = (byte *******)local_230[-1], uVar8 = (undefined1)local_8,
           (byte *)0x1f < (byte *)((int)local_230 + (-4 - (int)pppppppbVar19)))) goto LAB_0040ca8e;
        FUN_0041c647(pppppppbVar19);
      }
      local_230 = *pppppppbVar10;
      pppppbStack_5c = (byte *****)pppppppbVar10[1];
      pppppbStack_58 = (byte *****)pppppppbVar10[2];
      pppppbStack_54 = (byte *****)pppppppbVar10[3];
      uVar1 = *(undefined8 *)(pppppppbVar10 + 4);
      local_50._4_4_ = (uint)((ulonglong)uVar1 >> 0x20);
      local_258 = local_50._4_4_;
      pppppppbVar10[4] = (byte ******)0x0;
      pppppppbVar10[5] = (byte ******)0xf;
      *(undefined1 *)pppppppbVar10 = 0;
      local_60 = local_230;
      local_50 = uVar1;
    }
    if (0xf < local_240._4_4_) {
      ppppppuVar20 = (undefined4 ******)local_250;
      if ((0xfff < local_240._4_4_ + 1) &&
         (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
         0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
      FUN_0041c647(ppppppuVar20);
    }
    iVar22 = local_238;
    iVar9 = FUN_00401b30((void *)(local_238 + DAT_00442938),(int *)&local_20);
    if (iVar9 != 0) goto LAB_0040cb35;
    local_29c = 500;
    local_298 = iVar9;
    FUN_00402280(&local_29c);
    FUN_00405980((int *)&local_30,(void *)(iVar22 + DAT_00442938));
    if (local_24 == '\0') goto LAB_0040cb00;
    pppppuStack_24c = (undefined4 ******)0x0;
    pppppuStack_248 = (undefined4 ******)0x0;
    pppppuStack_244 = (undefined4 ******)0x0;
    local_240 = 0xf00000000;
    local_250 = (undefined4 ******)0x0;
    local_8._0_1_ = 0x10;
    FUN_0040f0a0(local_224,&local_250);
    local_8._0_1_ = 9;
    if (0xf < local_240._4_4_) {
      ppppppuVar20 = (undefined4 ******)local_250;
      if ((0xfff < local_240._4_4_ + 1) &&
         (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
         0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
      FUN_0041c647(ppppppuVar20);
    }
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)local_214,FUN_00401310);
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_2dc));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if (local_2c == local_30) goto LAB_0040cb96;
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,(uint)*local_30);
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_2ec));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if ((uint)((int)local_2c - (int)local_30) < 2) goto LAB_0040cb96;
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        (pbVar12,(uint)local_30[1]);
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_2fc));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if ((uint)((int)local_2c - (int)local_30) < 3) goto LAB_0040cb96;
    pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        (pbVar12,(uint)local_30[2]);
    pcVar30 = local_30c;
    puVar13 = (undefined4 *)std::setw(CONCAT44(2,pcVar30));
    pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar11,puVar13);
    pbVar12[*(int *)(*(int *)pbVar12 + 4) + 0x40] =
         (basic_ostream<char,std::char_traits<char>_>)0x30;
    if ((uint)((int)local_2c - (int)local_30) < 4) goto LAB_0040cb96;
    std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,(uint)local_30[3]);
    pppppppbVar10 = (byte *******)FUN_0040f1a0(local_224,&local_250);
    if (&local_78 != pppppppbVar10) {
      if ((byte ******)0xf < local_254) {
        pppppppbVar19 = (byte *******)local_25c;
        if ((0xfff < (int)local_254 + 1U) &&
           (pppppppbVar19 = (byte *******)local_25c[-1], uVar8 = (undefined1)local_8,
           (byte *)0x1f < (byte *)((int)local_25c + (-4 - (int)pppppppbVar19)))) goto LAB_0040ca8e;
        pcVar30 = (char *)0x40bf60;
        FUN_0041c647(pppppppbVar19);
      }
      local_78 = *pppppppbVar10;
      pppppbStack_74 = (byte *****)pppppppbVar10[1];
      pppppbStack_70 = (byte *****)pppppppbVar10[2];
      pppppbStack_6c = (byte *****)pppppppbVar10[3];
      local_68 = (byte *****)pppppppbVar10[4];
      pppppbStack_64 = (byte *****)pppppppbVar10[5];
      local_254 = (byte *****)pppppppbVar10[5];
      pppppppbVar10[4] = (byte ******)0x0;
      pppppppbVar10[5] = (byte ******)0xf;
      *(undefined1 *)pppppppbVar10 = 0;
      local_25c = local_78;
    }
    if (0xf < local_240._4_4_) {
      ppppppuVar20 = (undefined4 ******)local_250;
      if ((0xfff < local_240._4_4_ + 1) &&
         (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
         0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
      pcVar30 = (char *)0x40bfce;
      FUN_0041c647(ppppppuVar20);
    }
    ppppppbVar6 = local_230;
    iVar27 = iVar27 + 1;
    uStack_228._2_1_ = 0xf < local_258;
    pppppppbVar10 = &local_60;
    if (0xf < local_258) {
      pppppppbVar10 = (byte *******)local_230;
    }
    pppppppbVar19 = &local_78;
    if ((byte ******)0xf < local_254) {
      pppppppbVar19 = (byte *******)local_25c;
    }
    uStack_228._3_1_ = (byte ******)0xf < local_254;
    ppppppbVar5 = (byte ******)local_68;
    if ((byte ******)local_68 == (byte ******)local_50) {
      while (ppppppbVar4 = ppppppbVar5 + -1, (byte ******)0x3 < ppppppbVar5) {
        if (*pppppppbVar19 != *pppppppbVar10) goto LAB_0040c029;
        pppppppbVar19 = pppppppbVar19 + 1;
        pppppppbVar10 = pppppppbVar10 + 1;
        ppppppbVar5 = ppppppbVar4;
      }
      if (ppppppbVar4 == (byte ******)0xfffffffc) {
LAB_0040c05d:
        uVar23 = 0;
      }
      else {
LAB_0040c029:
        bVar29 = *(byte *)pppppppbVar19 < *(byte *)pppppppbVar10;
        if ((*(byte *)pppppppbVar19 == *(byte *)pppppppbVar10) &&
           ((ppppppbVar4 == (byte ******)0xfffffffd ||
            ((bVar29 = *(byte *)((int)pppppppbVar19 + 1) < *(byte *)((int)pppppppbVar10 + 1),
             *(byte *)((int)pppppppbVar19 + 1) == *(byte *)((int)pppppppbVar10 + 1) &&
             ((ppppppbVar4 == (byte ******)0xfffffffe ||
              ((bVar29 = *(byte *)((int)pppppppbVar19 + 2) < *(byte *)((int)pppppppbVar10 + 2),
               *(byte *)((int)pppppppbVar19 + 2) == *(byte *)((int)pppppppbVar10 + 2) &&
               ((ppppppbVar4 == (byte ******)0xffffffff ||
                (bVar29 = *(byte *)((int)pppppppbVar19 + 3) < *(byte *)((int)pppppppbVar10 + 3),
                *(byte *)((int)pppppppbVar19 + 3) == *(byte *)((int)pppppppbVar10 + 3)))))))))))))
        goto LAB_0040c05d;
        uVar23 = -(uint)bVar29 | 1;
      }
      if (uVar23 == 0) {
        memset(local_174,0,0xb0);
        local_174[0] = &DAT_0043ed68;
        local_164[0] = &DAT_0043e64c;
        std::basic_ios<char,std::char_traits<char>_>::basic_ios<char,std::char_traits<char>_>
                  (local_10c);
        local_8 = CONCAT31(local_8._1_3_,0x11);
        local_268 = local_264 | 0x10;
        local_264 = local_268;
        std::basic_iostream<char,std::char_traits<char>_>::
        basic_iostream<char,std::char_traits<char>_>
                  ((basic_iostream<char,std::char_traits<char>_> *)local_174,
                   (basic_streambuf<char,std::char_traits<char>_> *)local_15c);
        local_8 = 0x12;
        *(undefined ***)((int)local_174 + *(int *)(local_174[0] + 4)) =
             std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
        *(int *)((int)&iStack_178 + *(int *)(local_174[0] + 4)) = *(int *)(local_174[0] + 4) + -0x68
        ;
        std::basic_streambuf<char,std::char_traits<char>_>::
        basic_streambuf<char,std::char_traits<char>_>
                  ((basic_streambuf<char,std::char_traits<char>_> *)local_15c);
        local_15c[0] = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::
                       vftable;
        local_124 = 0;
        local_120 = 0;
        local_8._0_1_ = 0x13;
        if (DAT_004428ed == '\0') {
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              ((basic_ostream<char,std::char_traits<char>_> *)local_164,FUN_00401310
                              );
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,"V");
          puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_34c));
          pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_00402250((int *)pbVar12,puVar13);
          std::basic_ios<char,std::char_traits<char>_>::fill
                    ((basic_ios<char,std::char_traits<char>_> *)
                     (pbVar12 + *(int *)(*(int *)pbVar12 + 4)),'0');
          if ((uint)((int)local_2c - (int)local_30) < 7) goto LAB_0040cb96;
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar12,(uint)local_30[6]);
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,"_");
          puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_35c));
          pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_00402250((int *)pbVar12,puVar13);
          std::basic_ios<char,std::char_traits<char>_>::fill
                    ((basic_ios<char,std::char_traits<char>_> *)
                     (pbVar12 + *(int *)(*(int *)pbVar12 + 4)),'0');
          if ((uint)((int)local_2c - (int)local_30) < 6) goto LAB_0040cb96;
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar12,(uint)local_30[5]);
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,"_");
          pcVar30 = acStack_27c;
          puVar13 = (undefined4 *)std::setw(CONCAT44(2,pcVar30));
          pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_00402250((int *)pbVar12,puVar13);
          std::basic_ios<char,std::char_traits<char>_>::fill
                    ((basic_ios<char,std::char_traits<char>_> *)
                     (pbVar12 + *(int *)(*(int *)pbVar12 + 4)),'0');
          if ((uint)((int)local_2c - (int)local_30) < 5) goto LAB_0040cb96;
          bVar2 = local_30[4];
        }
        else {
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              ((basic_ostream<char,std::char_traits<char>_> *)local_164,FUN_00401310
                              );
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,"V");
          puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_31c));
          pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_00402250((int *)pbVar12,puVar13);
          std::basic_ios<char,std::char_traits<char>_>::fill
                    ((basic_ios<char,std::char_traits<char>_> *)
                     (pbVar12 + *(int *)(*(int *)pbVar12 + 4)),'0');
          if ((uint)((int)local_2c - (int)local_30) < 0x11) goto LAB_0040cb96;
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar12,(uint)local_30[0x10]);
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,"_");
          puVar13 = (undefined4 *)std::setw(CONCAT44(2,local_32c));
          pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_00402250((int *)pbVar12,puVar13);
          std::basic_ios<char,std::char_traits<char>_>::fill
                    ((basic_ios<char,std::char_traits<char>_> *)
                     (pbVar12 + *(int *)(*(int *)pbVar12 + 4)),'0');
          if ((uint)((int)local_2c - (int)local_30) < 0x10) goto LAB_0040cb96;
          pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              (pbVar12,(uint)local_30[0xf]);
          pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,"_");
          pcVar30 = local_3fc;
          puVar13 = (undefined4 *)std::setw(CONCAT44(2,pcVar30));
          pbVar12 = (basic_ostream<char,std::char_traits<char>_> *)
                    FUN_00402250((int *)pbVar12,puVar13);
          std::basic_ios<char,std::char_traits<char>_>::fill
                    ((basic_ios<char,std::char_traits<char>_> *)
                     (pbVar12 + *(int *)(*(int *)pbVar12 + 4)),'0');
          if ((uint)((int)local_2c - (int)local_30) < 0xf) goto LAB_0040cb96;
          bVar2 = local_30[0xe];
        }
        std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,(uint)bVar2);
        FUN_00411870((basic_istream<char,std::char_traits<char>_> *)local_174,&local_94);
        local_8._0_1_ = 9;
        *(undefined ***)((int)local_174 + *(int *)(local_174[0] + 4)) =
             std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>_>::vftable;
        *(int *)((int)&iStack_178 + *(int *)(local_174[0] + 4)) = *(int *)(local_174[0] + 4) + -0x68
        ;
        local_15c[0] = std::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>_>::
                       vftable;
        FUN_0040fe50((int)local_15c);
        std::basic_streambuf<char,std::char_traits<char>_>::
        ~basic_streambuf<char,std::char_traits<char>_>
                  ((basic_streambuf<char,std::char_traits<char>_> *)local_15c);
        std::basic_iostream<char,std::char_traits<char>_>::
        ~basic_iostream<char,std::char_traits<char>_>(local_154);
        std::basic_ios<char,std::char_traits<char>_>::~basic_ios<char,std::char_traits<char>_>
                  (local_10c);
        break;
      }
    }
    if (iVar27 == 1) {
      local_2a4 = 3000;
      local_2a0 = 0;
      FUN_00402280(&local_2a4);
    }
    else if (iVar27 == 10) goto LAB_0040cb00;
    pppppppbVar10 = &local_60;
    if (uStack_228._2_1_ != '\0') {
      pppppppbVar10 = (byte *******)ppppppbVar6;
    }
    pppppppbVar19 = &local_78;
    if (uStack_228._3_1_ != '\0') {
      pppppppbVar19 = (byte *******)local_25c;
    }
    ppppppbVar6 = (byte ******)local_68;
    if ((byte ******)local_68 == (byte ******)local_50) {
      while (ppppppbVar5 = ppppppbVar6 + -1, (byte ******)0x3 < ppppppbVar6) {
        if (*pppppppbVar19 != *pppppppbVar10) goto LAB_0040c0e6;
        pppppppbVar19 = pppppppbVar19 + 1;
        pppppppbVar10 = pppppppbVar10 + 1;
        ppppppbVar6 = ppppppbVar5;
      }
      if (ppppppbVar5 == (byte ******)0xfffffffc) {
LAB_0040c11a:
        uVar23 = 0;
      }
      else {
LAB_0040c0e6:
        bVar29 = *(byte *)pppppppbVar19 < *(byte *)pppppppbVar10;
        if ((*(byte *)pppppppbVar19 == *(byte *)pppppppbVar10) &&
           ((ppppppbVar5 == (byte ******)0xfffffffd ||
            ((bVar29 = *(byte *)((int)pppppppbVar19 + 1) < *(byte *)((int)pppppppbVar10 + 1),
             *(byte *)((int)pppppppbVar19 + 1) == *(byte *)((int)pppppppbVar10 + 1) &&
             ((ppppppbVar5 == (byte ******)0xfffffffe ||
              ((bVar29 = *(byte *)((int)pppppppbVar19 + 2) < *(byte *)((int)pppppppbVar10 + 2),
               *(byte *)((int)pppppppbVar19 + 2) == *(byte *)((int)pppppppbVar10 + 2) &&
               ((ppppppbVar5 == (byte ******)0xffffffff ||
                (bVar29 = *(byte *)((int)pppppppbVar19 + 3) < *(byte *)((int)pppppppbVar10 + 3),
                *(byte *)((int)pppppppbVar19 + 3) == *(byte *)((int)pppppppbVar10 + 3)))))))))))))
        goto LAB_0040c11a;
        uVar23 = -(uint)bVar29 | 1;
      }
      if (uVar23 == 0) break;
    }
  } while (iVar27 < 10);
  local_2ac = 500;
  local_2a8 = 0;
  FUN_00402280(&local_2ac);
  if (DAT_004428ee != '\0') {
    FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"[DBG] ");
    iVar27 = local_238;
    uVar23 = 0;
    if (0 < *(int *)(local_238 + 0x18 + DAT_00442938)) {
      do {
        pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00401310)
        ;
        if ((uint)((int)local_2c - (int)local_30) <= uVar23) goto LAB_0040cb96;
        pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                            ((basic_ostream<char,std::char_traits<char>_> *)pbVar11,
                             (uint)local_30[uVar23]);
        FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar11,",");
        uVar23 = uVar23 + 1;
      } while ((int)uVar23 < *(int *)(iVar27 + 0x18 + DAT_00442938));
    }
    std::basic_ostream<char,std::char_traits<char>_>::operator<<
              ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00402220);
  }
  pbVar16 = DAT_00442954;
  if ((DAT_004428ec != '\0') && (pbVar7 = DAT_00442950, piVar14 = local_7c, DAT_00442028 != '\0')) {
    for (; pbVar7 != pbVar16; pbVar7 = pbVar7 + 0x1c) {
      if ((*(int **)(pbVar7 + 0x18) == piVar14) &&
         (uVar23 = FUN_004117f0(pbVar7,(byte *)&local_c4), piVar14 = local_7c, (char)uVar23 == '\0')
         ) {
        FUN_0040ff00(&local_48,"Device Index Changed",0x14);
        FUN_0040fc30(&stack0xfffffbe0,&local_48);
        FUN_00405340(in_stack_fffffbe0);
        uVar21 = 0x12;
        pppppppbVar10 = (byte *******)local_230;
        goto LAB_0040aec8;
      }
    }
  }
  pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                         "Get New Version = ");
  pppppppbVar10 = &local_94;
  if (0xf < local_80) {
    pppppppbVar10 = (byte *******)local_94;
  }
  pbVar12 = FUN_004135e0(pbVar12,(char *)pppppppbVar10,local_84);
  std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,FUN_00402220);
  uStack_228._2_1_ = 0xf < DAT_004420c8;
  ppcVar17 = &DAT_004420b4;
  if ((bool)uStack_228._2_1_) {
    ppcVar17 = (char **)DAT_004420b4;
  }
  if (DAT_004420c4 == 0) {
LAB_0040c605:
    uVar23 = 0xffffffff;
  }
  else {
    iVar27 = -1;
    if (DAT_004420c4 - 1 != -1) {
      iVar27 = DAT_004420c4 - 1;
    }
    ppcVar28 = (char **)((int)ppcVar17 + iVar27);
    cVar3 = *(char *)ppcVar28;
    while (cVar3 != 'V') {
      if (ppcVar28 == ppcVar17) goto LAB_0040c605;
      ppcVar28 = (char **)((int)ppcVar28 + -1);
      cVar3 = *(char *)ppcVar28;
    }
    uVar23 = (int)ppcVar28 - (int)ppcVar17;
  }
  ppcVar17 = &DAT_004420b4;
  if ((bool)uStack_228._2_1_) {
    ppcVar17 = (char **)DAT_004420b4;
  }
  if (DAT_004420c4 == 0) {
LAB_0040c63e:
    iVar27 = -1;
  }
  else {
    iVar27 = -1;
    if (DAT_004420c4 - 1 != -1) {
      iVar27 = DAT_004420c4 - 1;
    }
    ppcVar28 = (char **)((int)ppcVar17 + iVar27);
    cVar3 = *(char *)ppcVar28;
    while (cVar3 != '.') {
      if (ppcVar28 == ppcVar17) goto LAB_0040c63e;
      ppcVar28 = (char **)((int)ppcVar28 + -1);
      cVar3 = *(char *)ppcVar28;
    }
    iVar27 = (int)ppcVar28 - (int)ppcVar17;
  }
  local_9c = 0;
  local_98 = 0;
  local_ac = (byte ******)0x0;
  uStack_a8 = 0;
  uStack_a4 = 0;
  uStack_a0 = 0;
  FUN_00404c20(&local_ac,&DAT_0043d114,0);
  uVar24 = iVar27 - uVar23;
  local_8._0_1_ = 0x14;
  if ((int)uVar24 < 1) {
    if (0x7fffffff - DAT_004420c4 < 0xb) goto LAB_0040cba0;
    ppcVar17 = &DAT_004420b4;
    if (0xf < DAT_004420c8) {
      ppcVar17 = (char **)DAT_004420b4;
    }
    pcVar30 = local_22c;
    FUN_004125f0(local_284,local_22c,DAT_004420c4,"FileName = ",0xb,ppcVar17,DAT_004420c4);
    local_8._0_1_ = 0x15;
    if (uStack_270 - local_274 < 0x1d) {
      pppppppuVar15 =
           (undefined4 *******)
           FUN_00411fa0(local_284,0x1d,local_22c,"has wrong. FW Update Fail !!!",0x1d);
    }
    else {
      pppppppuVar15 = local_284;
      if (0xf < uStack_270) {
        pppppppuVar15 = (undefined4 *******)local_284[0];
      }
      pvVar26 = (void *)((int)pppppppuVar15 + local_274);
      local_274 = local_274 + 0x1d;
      memmove(pvVar26,"has wrong. FW Update Fail !!!",0x1d);
      *(undefined1 *)((int)pvVar26 + 0x1d) = 0;
      pppppppuVar15 = local_284;
    }
    local_250 = *pppppppuVar15;
    pppppuStack_24c = pppppppuVar15[1];
    pppppuStack_248 = pppppppuVar15[2];
    pppppuStack_244 = pppppppuVar15[3];
    local_240 = *(undefined8 *)(pppppppuVar15 + 4);
    pppppppuVar15[4] = (undefined4 ******)0x0;
    pppppppuVar15[5] = (undefined4 ******)0xf;
    *(undefined1 *)pppppppuVar15 = 0;
    FUN_0040fbb0(&local_48,(int *)&local_250);
    if (0xf < local_240._4_4_) {
      ppppppuVar20 = (undefined4 ******)local_250;
      if ((0xfff < local_240._4_4_ + 1) &&
         (ppppppuVar20 = (undefined4 ******)local_250[-1], uVar8 = (undefined1)local_8,
         0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040ca8e;
      FUN_0041c647(ppppppuVar20);
    }
    local_8._0_1_ = 0x14;
    if (0xf < uStack_270) {
      pppppppuVar15 = (undefined4 *******)local_284[0];
      if ((0xfff < uStack_270 + 1) &&
         (pppppppuVar15 = (undefined4 *******)local_284[0][-1], uVar8 = (undefined1)local_8,
         0x1f < (uint)((int)local_284[0] + (-4 - (int)pppppppuVar15)))) {
LAB_0040ca8e:
        local_8._0_1_ = uVar8;
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_0041c647(pppppppuVar15);
    }
    FUN_0040fc30(&stack0xfffffbe4,&local_48);
    FUN_00405270(pcVar30);
    uVar21 = 6;
  }
  else {
    local_240 = 0;
    local_250 = (undefined4 ******)0x0;
    pppppuStack_24c = (undefined4 ******)0x0;
    pppppuStack_248 = (undefined4 ******)0x0;
    pppppuStack_244 = (undefined4 ******)0x0;
    if (DAT_004420c4 < uVar23) {
      FUN_00410040();
LAB_0040cba0:
                    /* WARNING: Subroutine does not return */
      FUN_00402530();
    }
    if (DAT_004420c4 - uVar23 < uVar24) {
      uVar24 = DAT_004420c4 - uVar23;
    }
    ppcVar17 = &DAT_004420b4;
    if (0xf < DAT_004420c8) {
      ppcVar17 = (char **)DAT_004420b4;
    }
    FUN_00404c20(&local_250,(char *)((int)ppcVar17 + uVar23),uVar24);
    local_264 = local_264 | 2;
    FUN_0040fbb0(&local_ac,(int *)&local_250);
    if (0xf < local_240._4_4_) {
      ppppppuVar20 = (undefined4 ******)local_250;
      if ((0xfff < local_240._4_4_ + 1) &&
         (ppppppuVar20 = (undefined4 ******)local_250[-1],
         0x1f < (uint)((int)local_250 + (-4 - (int)ppppppuVar20)))) goto LAB_0040cae5;
      FUN_0041c647(ppppppuVar20);
    }
    if (DAT_004428ee != '\0') {
      pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                             "[DBG] packet_ver_str = ");
      pppppppbVar10 = &local_ac;
      if (0xf < local_98) {
        pppppppbVar10 = (byte *******)local_ac;
      }
      pbVar12 = FUN_004135e0(pbVar12,(char *)pppppppbVar10,local_9c);
      std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,FUN_00402220);
    }
    pppppppbVar10 = &local_ac;
    if (0xf < local_98) {
      pppppppbVar10 = (byte *******)local_ac;
    }
    pppppppbVar19 = &local_94;
    if (0xf < local_80) {
      pppppppbVar19 = (byte *******)local_94;
    }
    uVar23 = local_84;
    if (local_9c < local_84) {
      uVar23 = local_9c;
    }
    while (uVar24 = uVar23 - 4, 3 < uVar23) {
      if (*pppppppbVar19 != *pppppppbVar10) goto LAB_0040c7be;
      pppppppbVar19 = pppppppbVar19 + 1;
      pppppppbVar10 = pppppppbVar10 + 1;
      uVar23 = uVar24;
    }
    if (uVar24 == 0xfffffffc) {
LAB_0040c7f2:
      uVar23 = 0;
    }
    else {
LAB_0040c7be:
      bVar29 = *(byte *)pppppppbVar19 < *(byte *)pppppppbVar10;
      if ((*(byte *)pppppppbVar19 == *(byte *)pppppppbVar10) &&
         ((uVar24 == 0xfffffffd ||
          ((bVar29 = *(byte *)((int)pppppppbVar19 + 1) < *(byte *)((int)pppppppbVar10 + 1),
           *(byte *)((int)pppppppbVar19 + 1) == *(byte *)((int)pppppppbVar10 + 1) &&
           ((uVar24 == 0xfffffffe ||
            ((bVar29 = *(byte *)((int)pppppppbVar19 + 2) < *(byte *)((int)pppppppbVar10 + 2),
             *(byte *)((int)pppppppbVar19 + 2) == *(byte *)((int)pppppppbVar10 + 2) &&
             ((uVar24 == 0xffffffff ||
              (bVar29 = *(byte *)((int)pppppppbVar19 + 3) < *(byte *)((int)pppppppbVar10 + 3),
              *(byte *)((int)pppppppbVar19 + 3) == *(byte *)((int)pppppppbVar10 + 3)))))))))))))
      goto LAB_0040c7f2;
      uVar23 = -(uint)bVar29 | 1;
    }
    if (((uVar23 != 0) || (local_84 < local_9c)) || (local_9c < local_84)) {
      pbVar12 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"FileName = "
                            );
      ppcVar17 = &DAT_004420b4;
      if (0xf < DAT_004420c8) {
        ppcVar17 = (char **)DAT_004420b4;
      }
      pbVar12 = FUN_004135e0(pbVar12,(char *)ppcVar17,DAT_004420c4);
      pbVar12 = FUN_00402000(pbVar12," is different, retry..");
      pcVar25 = local_22c;
      pbVar11 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar12,(int)local_22c)
      ;
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                ((basic_ostream<char,std::char_traits<char>_> *)pbVar11,FUN_00402220);
      pcVar25 = pcVar25 + 1;
      local_8._0_1_ = 9;
      local_22c = pcVar25;
      if (local_98 < 0x10) {
LAB_0040c8a3:
        if (3 < (int)pcVar25) goto code_r0x0040c8ac;
        goto LAB_0040b170;
      }
      pppppppbVar10 = (byte *******)local_ac;
      if ((local_98 + 1 < 0x1000) ||
         (pppppppbVar10 = (byte *******)local_ac[-1],
         (byte *)((int)local_ac + (-4 - (int)pppppppbVar10)) < (byte *)0x20)) {
        FUN_0041c647(pppppppbVar10);
        goto LAB_0040c8a3;
      }
      goto LAB_0040cae5;
    }
    pcVar30 = (char *)0x0;
    FUN_00404c20(&stack0xfffffbe8,"FW Update Complete!",0x13);
    FUN_00405410(pcVar30);
    uVar21 = 0;
  }
  pppppppbVar10 = (byte *******)local_230;
  if (local_98 < 0x10) goto LAB_0040aec8;
  pppppppbVar10 = (byte *******)local_ac;
  if ((local_98 + 1 < 0x1000) ||
     (pppppppbVar10 = (byte *******)local_ac[-1],
     (byte *)((int)local_ac + (-4 - (int)pppppppbVar10)) < (byte *)0x20)) {
    FUN_0041c647(pppppppbVar10);
    pppppppbVar10 = (byte *******)local_230;
    goto LAB_0040aec8;
  }
LAB_0040cae5:
                    /* WARNING: Subroutine does not return */
  _invalid_parameter_noinfo_noreturn();
}

