// FUN_004098c0 @004098c0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_004098c0(void)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  basic_ostream<char,std::char_traits<char>_> *pbVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  undefined4 *puVar6;
  HANDLE hConsoleOutput;
  char *pcVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  char *in_stack_fffffed8;
  undefined1 local_104 [16];
  undefined1 local_f4 [16];
  undefined1 local_e4 [16];
  undefined1 local_d4 [16];
  undefined1 local_c4 [16];
  uint local_b4;
  int local_b0;
  uint local_ac;
  int local_a8;
  uint local_a4;
  int local_a0;
  uint local_9c;
  int local_98;
  uint local_94;
  int local_90;
  uint local_8c;
  int local_88;
  uint local_84 [5];
  int local_70;
  int local_6c;
  int local_68;
  uint local_64;
  int local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  int local_50;
  byte local_4a;
  byte local_49;
  void *local_48;
  int local_44;
  int local_40;
  char local_3c;
  void *local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  uint local_24;
  undefined8 local_20;
  int local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0041d7cd;
  local_10 = ExceptionList;
  local_14 = DAT_00442010 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_28 = 0;
  local_24 = 0;
  local_38 = (void *)0x0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  FUN_00404c20(&local_38,&DAT_0043d114,0);
  uVar9 = DAT_00442034;
  local_8 = 0;
  local_20 = 0;
  local_18 = 0;
  if (DAT_00442034 != 0) {
    if (0x7fffffff < DAT_00442034) {
                    /* WARNING: Subroutine does not return */
      FUN_00401ee0();
    }
    FUN_00401450(&local_20,DAT_00442034);
    pvVar3 = (undefined1 *)local_20;
    memset((undefined1 *)local_20,0,uVar9);
    local_20 = CONCAT44((int)pvVar3 + uVar9,(undefined1 *)local_20);
  }
  local_3c = '\0';
  local_8 = CONCAT31(local_8._1_3_,2);
  if (DAT_004428ec != '\0') {
    local_84[2] = 500;
    local_84[3] = 0;
    FUN_00402280(local_84 + 2);
  }
  iVar10 = local_50 * 0x5c;
  local_5c = 0;
  local_70 = iVar10;
LAB_004099b0:
  uVar9 = local_5c;
  iVar2 = FUN_004017f0((void *)(iVar10 + DAT_0044292c),(int *)0x1);
  uVar1 = local_5c;
  if ((iVar2 == 0) ||
     (iVar2 = FUN_00401a60((void *)(iVar10 + DAT_0044292c)), uVar9 = uVar1, iVar2 == 0))
  goto LAB_004099dd;
  std::basic_ostream<char,std::char_traits<char>_>::operator<<
            ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00402220);
  local_60 = 0;
  if (0 < DAT_00442030) {
    do {
      local_50 = 0;
      DAT_004428fc = *(int *)(DAT_0044295c + local_60 * 4) << 10;
      DAT_00442910 = *(int *)(DAT_00442944 + local_60 * 4) << 10;
      DAT_0044290c = *(int *)(DAT_00442968 + local_60 * 4) << 10;
      if (local_60 < DAT_00442030) {
        local_84[0] = 0x32;
        local_84[1] = 0;
        do {
          FUN_00402280(local_84);
          local_49 = 0;
          FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
          if (local_20._4_4_ == (undefined1 *)local_20) goto LAB_0040a9f3;
          *(undefined1 *)local_20 = 0x82;
          iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
          if (iVar2 != 0) goto LAB_0040a943;
          local_8c = 0x32;
          local_88 = iVar2;
          FUN_00402280(&local_8c);
          FUN_00405980((int *)&local_48,(void *)(iVar10 + DAT_0044292c));
          if (local_3c == '\0') {
LAB_0040a99b:
            FUN_0040ff00(&local_38,"Read Data Fail !!!",0x12);
            FUN_0040fc30(&stack0xfffffed8,&local_38);
            FUN_00405270(in_stack_fffffed8);
            uVar8 = 0xd;
            goto LAB_00409a47;
          }
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                "Bootloader Version = V");
          pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00401310)
          ;
          puVar6 = (undefined4 *)std::setw(CONCAT44(2,local_c4));
          pbVar4 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar5,puVar6)
          ;
          pbVar4[*(int *)(*(int *)pbVar4 + 4) + 0x40] =
               (basic_ostream<char,std::char_traits<char>_>)0x30;
          if ((uint)(local_44 - (int)local_48) < 4) goto LAB_0040a9f3;
          pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                             (pbVar4,(uint)*(byte *)((int)local_48 + 3));
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,"_");
          puVar6 = (undefined4 *)std::setw(CONCAT44(2,local_d4));
          pbVar4 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar4,puVar6)
          ;
          pbVar4[*(int *)(*(int *)pbVar4 + 4) + 0x40] =
               (basic_ostream<char,std::char_traits<char>_>)0x30;
          if ((uint)(local_44 - (int)local_48) < 3) goto LAB_0040a9f3;
          pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                             (pbVar4,(uint)*(byte *)((int)local_48 + 2));
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,"_");
          puVar6 = (undefined4 *)std::setw(CONCAT44(2,local_e4));
          pbVar4 = (basic_ostream<char,std::char_traits<char>_> *)FUN_00402250((int *)pbVar4,puVar6)
          ;
          pbVar4[*(int *)(*(int *)pbVar4 + 4) + 0x40] =
               (basic_ostream<char,std::char_traits<char>_>)0x30;
          if ((uint)(local_44 - (int)local_48) < 2) goto LAB_0040a9f3;
          pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                             (pbVar4,(uint)*(byte *)((int)local_48 + 1));
          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                    ((basic_ostream<char,std::char_traits<char>_> *)pbVar5,FUN_00402220);
          local_49 = 0;
          FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
          if (((((local_20._4_4_ == (undefined1 *)local_20) ||
                (*(undefined1 *)local_20 = 0x10,
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) ||
               (((undefined1 *)local_20)[1] = 0x41,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 3)) ||
              ((((undefined1 *)local_20)[2] = 0x53,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 4 ||
               (((undefined1 *)local_20)[3] = 0x55,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 5)))) ||
             ((((((undefined1 *)local_20)[4] = 0x53,
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 6 ||
                ((((undefined1 *)local_20)[5] = 0x48,
                 (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 7 ||
                 (((undefined1 *)local_20)[6] = 0x49,
                 (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 8)))) ||
               (((undefined1 *)local_20)[7] = 0x44,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 9)) ||
              ((((undefined1 *)local_20)[8] = 0x46,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 10 ||
               (((undefined1 *)local_20)[9] = 0x57,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 0xb))))))
          goto LAB_0040a9f3;
          ((undefined1 *)local_20)[10] = 0x55;
          iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
          if (iVar2 != 0) {
LAB_0040a943:
            FUN_0040ff00(&local_38,"Write Data Fail !!!",0x13);
            FUN_0040fc30(&stack0xfffffed8,&local_38);
            FUN_00405270(in_stack_fffffed8);
            uVar8 = 0xe;
            goto LAB_00409a47;
          }
          local_49 = 0;
          FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
          if (local_20._4_4_ == (undefined1 *)local_20) goto LAB_0040a9f3;
          *(undefined1 *)local_20 = 0x8f;
          do {
            iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
            if (iVar2 != 0) goto LAB_0040a943;
            local_94 = 0x32;
            local_90 = iVar2;
            FUN_00402280(&local_94);
            FUN_00405980((int *)&local_48,(void *)(iVar10 + DAT_0044292c));
            if (local_3c == '\0') goto LAB_0040a99b;
            if (((uint)(local_44 - (int)local_48) < 2) ||
               (local_49 = *(byte *)((int)local_48 + 1), (uint)(local_44 - (int)local_48) < 3))
            goto LAB_0040a9f3;
            pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                  "Status Flags = ");
            pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                               (pbVar4,(uint)local_49);
            std::basic_ostream<char,std::char_traits<char>_>::operator<<
                      ((basic_ostream<char,std::char_traits<char>_> *)pbVar5,FUN_00402220);
          } while (-1 < (char)local_49);
          if (DAT_004428ee != '\0') {
            local_49 = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
            if ((local_20._4_4_ == (undefined1 *)local_20) ||
               (*(undefined1 *)local_20 = 0x7f,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) goto LAB_0040a9f3;
            ((undefined1 *)local_20)[1] = 0xff;
            iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
            if (iVar2 != 0) goto LAB_0040a943;
          }
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                "Start Erase...");
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00402220);
          uVar9 = DAT_004428fc;
          do {
            local_49 = 0;
            local_5c = uVar9;
            local_58 = uVar9;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
            if ((((local_20._4_4_ == (undefined1 *)local_20) ||
                 (*(undefined1 *)local_20 = 0x20,
                 (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) ||
                (((undefined1 *)local_20)[1] = (char)uVar9,
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 3)) ||
               ((((undefined1 *)local_20)[2] = (char)(local_5c >> 8),
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 4 ||
                (((undefined1 *)local_20)[3] = (char)(local_5c >> 0x10),
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 5)))) goto LAB_0040a9f3;
            ((undefined1 *)local_20)[4] = (char)(local_5c >> 0x18);
            iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
            if (iVar2 != 0) goto LAB_0040a943;
            local_9c = 2;
            local_98 = iVar2;
            FUN_00402280(&local_9c);
            local_49 = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
            if ((local_20._4_4_ == (undefined1 *)local_20) ||
               (*(undefined1 *)local_20 = 0x1f,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) goto LAB_0040a9f3;
            ((undefined1 *)local_20)[1] = 1;
            iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
            if (iVar2 != 0) goto LAB_0040a943;
            local_a4 = 0x32;
            local_a0 = iVar2;
            FUN_00402280(&local_a4);
            local_49 = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_49);
            if (local_20._4_4_ == (undefined1 *)local_20) goto LAB_0040a9f3;
            *(undefined1 *)local_20 = 0x8f;
            do {
              iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
              if (iVar2 != 0) goto LAB_0040a943;
              FUN_00405980((int *)&local_48,(void *)(iVar10 + DAT_0044292c));
              if (local_3c == '\0') goto LAB_0040a99b;
              if (((uint)(local_44 - (int)local_48) < 2) ||
                 (local_49 = *(byte *)((int)local_48 + 1), (uint)(local_44 - (int)local_48) < 3))
              goto LAB_0040a9f3;
              local_4a = *(byte *)((int)local_48 + 2);
              if (DAT_004428ee != '\0') {
                pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                      "[DBG] Erase Address = ");
                pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,uVar9);
                pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,
                                      ", Status = ");
                pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                   (pbVar4,(uint)local_49);
                pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,
                                      ", Error = ");
                pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                   (pbVar4,(uint)local_4a);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)pbVar5,FUN_00402220);
              }
            } while ((local_49 & 1) != 0);
            std::basic_ostream<char,std::char_traits<char>_>::operator<<
                      ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00401310);
            pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"0x");
            pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                               (pbVar4,FUN_00401310);
            puVar6 = (undefined4 *)std::setw(CONCAT44(8,local_f4));
            pbVar4 = (basic_ostream<char,std::char_traits<char>_> *)
                     FUN_00402250((int *)pbVar5,puVar6);
            std::basic_ios<char,std::char_traits<char>_>::fill
                      ((basic_ios<char,std::char_traits<char>_> *)
                       (pbVar4 + *(int *)(*(int *)pbVar4 + 4)),'0');
            pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,local_58);
            pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,
                                  " Erase Done...");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00402220);
            uVar9 = local_58 + DAT_0044290c;
          } while ((int)uVar9 < DAT_00442910 + DAT_004428fc);
          local_5c = uVar9;
          local_58 = uVar9;
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                "Start Programming...");
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00402220);
          local_58 = DAT_004428fc;
          local_5c = DAT_004428fc;
          do {
            uVar9 = DAT_0044290c;
            local_68 = 0;
            local_84[4] = uVar9;
            if (0 < (int)DAT_0044290c) {
              local_64 = 0;
              do {
                if ((uint)(DAT_00442924 - DAT_00442920) <= local_64) goto LAB_0040a9f3;
                *(undefined1 *)(DAT_00442920 + local_64) =
                     *(undefined1 *)(DAT_00442900 + local_64 + local_5c);
                local_64 = local_64 + 1;
                iVar10 = local_70;
              } while ((int)local_64 < (int)uVar9);
            }
            local_4a = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
            if ((((local_20._4_4_ == (undefined1 *)local_20) ||
                 (*(undefined1 *)local_20 = 0x20,
                 (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) ||
                (((undefined1 *)local_20)[1] = (char)local_58,
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 3)) ||
               ((((undefined1 *)local_20)[2] = (char)(local_58 >> 8),
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 4 ||
                (((undefined1 *)local_20)[3] = (char)(local_58 >> 0x10),
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 5)))) goto LAB_0040a9f3;
            ((undefined1 *)local_20)[4] = (char)(local_58 >> 0x18);
            iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
            if (iVar2 != 0) goto LAB_0040a943;
            local_ac = 2;
            local_a8 = iVar2;
            FUN_00402280(&local_ac);
            local_4a = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
            uVar1 = DAT_0044290c;
            if (((local_20._4_4_ == (undefined1 *)local_20) ||
                (*(undefined1 *)local_20 = 0x21,
                (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) ||
               (((undefined1 *)local_20)[1] = (char)uVar1,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 3)) goto LAB_0040a9f3;
            ((undefined1 *)local_20)[2] = (char)(uVar1 >> 8);
            iVar10 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
            if (iVar10 != 0) goto LAB_0040a943;
            local_b4 = 2;
            local_b0 = iVar10;
            FUN_00402280(&local_b4);
            iVar10 = (DAT_004428ef != '\0') + 4;
            local_6c = iVar10;
            do {
              local_4a = 0;
              local_64 = DAT_0044202c - iVar10;
              if ((int)uVar9 <= (int)(DAT_0044202c - iVar10)) {
                local_64 = uVar9;
              }
              if (DAT_004428ef == '\0') {
                FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
                if ((((local_20._4_4_ == (undefined1 *)local_20) ||
                     (*(undefined1 *)local_20 = 0x22,
                     (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) ||
                    (((undefined1 *)local_20)[1] = (char)local_64,
                    (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 3)) ||
                   (((undefined1 *)local_20)[2] = (char)local_68,
                   (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 4))
                goto LAB_0040a9f3;
                ((undefined1 *)local_20)[3] = (char)((uint)local_68 >> 8);
              }
              else {
                FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
                if (((local_20._4_4_ == (undefined1 *)local_20) ||
                    (*(undefined1 *)local_20 = 0x22,
                    (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) ||
                   ((((undefined1 *)local_20)[1] = (char)local_64,
                    (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 3 ||
                    ((((undefined1 *)local_20)[2] = (char)(local_64 >> 8),
                     (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 4 ||
                     (((undefined1 *)local_20)[3] = (char)local_68,
                     (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 5))))))
                goto LAB_0040a9f3;
                ((undefined1 *)local_20)[4] = (char)((uint)local_68 >> 8);
              }
              if (0 < (int)local_64) {
                local_84[3] = 0;
                do {
                  if ((uint)(DAT_00442924 - DAT_00442920) <= local_68 + local_84[3])
                  goto LAB_0040a9f3;
                  if ((uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) <=
                      local_84[3] + local_6c) goto LAB_0040a9f3;
                  *(undefined1 *)(local_84[3] + local_6c + (int)(undefined1 *)local_20) =
                       *(undefined1 *)(local_68 + local_84[3] + DAT_00442920);
                  local_84[3] = local_84[3] + 1;
                  iVar10 = local_6c;
                } while ((int)local_84[3] < (int)local_64);
              }
              iVar2 = FUN_00401b30((void *)(local_70 + DAT_0044292c),(int *)&local_20);
              if (iVar2 != 0) goto LAB_0040a943;
              uVar9 = local_84[4] - local_64;
              local_68 = local_68 + local_64;
              local_84[4] = uVar9;
            } while (0 < (int)uVar9);
            local_4a = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
            iVar10 = local_70;
            if ((local_20._4_4_ == (undefined1 *)local_20) ||
               (*(undefined1 *)local_20 = 0x1f,
               (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) goto LAB_0040a9f3;
            ((undefined1 *)local_20)[1] = 0x51;
            iVar2 = FUN_00401b30((void *)(local_70 + DAT_0044292c),(int *)&local_20);
            if (iVar2 != 0) goto LAB_0040a943;
            local_4a = 0;
            FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
            uVar9 = local_58;
            if (local_20._4_4_ == (undefined1 *)local_20) goto LAB_0040a9f3;
            *(undefined1 *)local_20 = 0x8f;
            do {
              iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
              if (iVar2 != 0) goto LAB_0040a943;
              FUN_00405980((int *)&local_48,(void *)(iVar10 + DAT_0044292c));
              if (local_3c == '\0') goto LAB_0040a99b;
              if (((uint)(local_44 - (int)local_48) < 2) ||
                 (local_49 = *(byte *)((int)local_48 + 1), (uint)(local_44 - (int)local_48) < 3))
              goto LAB_0040a9f3;
              local_4a = *(byte *)((int)local_48 + 2);
              if (DAT_004428ee != '\0') {
                pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                      "[DBG] Program Address = ");
                pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,uVar9);
                pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,
                                      ", Status = ");
                pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                   (pbVar4,(uint)local_49);
                pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,
                                      ", Error = ");
                pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                   (pbVar4,(uint)local_4a);
                std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)pbVar5,FUN_00402220);
              }
            } while ((local_49 & 1) != 0);
            pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"0x");
            pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                               (pbVar4,FUN_00401310);
            puVar6 = (undefined4 *)std::setw(CONCAT44(8,local_104));
            pbVar4 = (basic_ostream<char,std::char_traits<char>_> *)
                     FUN_00402250((int *)pbVar5,puVar6);
            pbVar4[*(int *)(*(int *)pbVar4 + 4) + 0x40] =
                 (basic_ostream<char,std::char_traits<char>_>)0x30;
            pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,local_58);
            pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)pbVar5,
                                  " Programming Done...");
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00402220);
            local_58 = local_58 + DAT_0044290c;
            local_5c = local_5c + DAT_0044290c;
            local_84[4] = DAT_0044290c;
          } while ((int)local_58 < DAT_00442910 + DAT_004428fc);
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                "Read checksum...");
          std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00402220);
          local_4a = 0;
          FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
          if (local_20._4_4_ == (undefined1 *)local_20) goto LAB_0040a9f3;
          *(undefined1 *)local_20 = 0x8e;
          iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
          if (iVar2 != 0) goto LAB_0040a943;
          FUN_00405980((int *)&local_48,(void *)(iVar10 + DAT_0044292c));
          if (local_3c == '\0') goto LAB_0040a99b;
          if ((uint)(local_44 - (int)local_48) < 2) goto LAB_0040a9f3;
          if (*(char *)((int)local_48 + 1) == -6) {
            std::basic_ostream<char,std::char_traits<char>_>::operator<<
                      ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00402220);
            pcVar7 = "Programming Success!";
LAB_0040a8a7:
            pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,pcVar7);
            std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,FUN_00402220);
            if ((DAT_00442029 != '\0') && (local_60 == DAT_00442030 + -1)) {
              local_4a = 0;
              FUN_0040f4b0(&local_20,DAT_0044202c,&local_4a);
              if ((local_20._4_4_ == (undefined1 *)local_20) ||
                 (*(undefined1 *)local_20 = 0x11,
                 (uint)((int)local_20._4_4_ - (int)(undefined1 *)local_20) < 2)) {
LAB_0040a9f3:
                    /* WARNING: Subroutine does not return */
                FUN_0040fef0();
              }
              ((undefined1 *)local_20)[1] = 0xff;
              iVar2 = FUN_00401b30((void *)(iVar10 + DAT_0044292c),(int *)&local_20);
              if (iVar2 != 0) goto LAB_0040a943;
            }
            break;
          }
          if (*(char *)((int)local_48 + 1) != -2) {
            pcVar7 = "Programming Success! (no check checksum)";
            goto LAB_0040a8a7;
          }
          hConsoleOutput = GetStdHandle(0xfffffff5);
          SetConsoleTextAttribute(hConsoleOutput,0xe);
          pbVar4 = FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                "Programming Fail, retry..");
          iVar2 = local_50;
          pbVar5 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar4,local_50);
          std::basic_ostream<char,std::char_traits<char>_>::operator<<
                    ((basic_ostream<char,std::char_traits<char>_> *)pbVar5,FUN_00402220);
          local_50 = iVar2 + 1;
          if (2 < local_50) {
            FUN_0040ff00(&local_38,"FW Update Fail !!!",0x12);
            FUN_0040fc30(&stack0xfffffed8,&local_38);
            FUN_00405270(in_stack_fffffed8);
            uVar8 = 9;
            goto LAB_00409a47;
          }
        } while (local_60 < DAT_00442030);
      }
      local_60 = local_60 + 1;
    } while (local_60 < DAT_00442030);
  }
  uVar8 = 0;
  goto LAB_00409a47;
LAB_004099dd:
  local_54 = 1000;
  local_50 = 0;
  FUN_00402280(&local_54);
  FUN_00402000((basic_ostream<char,std::char_traits<char>_> *)cout_exref,".");
  local_5c = uVar9 + 1;
  if (4 < (int)local_5c) goto code_r0x00409a0c;
  goto LAB_004099b0;
code_r0x00409a0c:
  std::basic_ostream<char,std::char_traits<char>_>::operator<<
            ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_00402220);
  FUN_0040ff00(&local_38,"Device Connect Fail !!!",0x17);
  FUN_0040fc30(&stack0xfffffed8,&local_38);
  FUN_00405270(in_stack_fffffed8);
  uVar8 = 10;
LAB_00409a47:
  if ((local_3c != '\0') && (local_48 != (void *)0x0)) {
    pvVar3 = local_48;
    if ((0xfff < (uint)(local_40 - (int)local_48)) &&
       (pvVar3 = *(void **)((int)local_48 + -4), 0x1f < (uint)((int)local_48 + (-4 - (int)pvVar3))))
    goto LAB_00409b0d;
    FUN_0041c647(pvVar3);
    local_48 = (void *)0x0;
    local_44 = 0;
    local_40 = 0;
  }
  if ((undefined1 *)local_20 != (void *)0x0) {
    pvVar3 = (undefined1 *)local_20;
    if ((0xfff < (uint)(local_18 - (int)(undefined1 *)local_20)) &&
       (pvVar3 = *(void **)((int)(undefined1 *)local_20 + -4),
       0x1f < (uint)((int)(undefined1 *)local_20 + (-4 - (int)pvVar3)))) goto LAB_00409b0d;
    FUN_0041c647(pvVar3);
    local_20 = 0;
    local_18 = 0;
  }
  if (0xf < local_24) {
    pvVar3 = local_38;
    if ((0xfff < local_24 + 1) &&
       (pvVar3 = *(void **)((int)local_38 + -4), 0x1f < (uint)((int)local_38 + (-4 - (int)pvVar3))))
    {
LAB_00409b0d:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_0041c647(pvVar3);
  }
  ExceptionList = local_10;
  return uVar8;
}

