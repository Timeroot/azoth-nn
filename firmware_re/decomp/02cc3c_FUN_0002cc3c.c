// @0x2cc3c  size=210

void FUN_0002cc3c(undefined4 param_1,int param_2,uint param_3,undefined4 param_4)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  
  puVar1 = DAT_0002cd14;
  if (*DAT_0002cd10 == '\x01') {
    if (0x47fff < param_2 - 0x93000U) {
      if (0x10 < param_3) {
        if (((uint)(ushort)DAT_0002cd14[0x21] & 1 << (*(ushort *)((int)DAT_0002cd14 + 0x86) & 0xff))
            != 0) {
          return;
        }
        FUN_0001c590(DAT_0002cd14 + (uint)*(ushort *)((int)DAT_0002cd14 + 0x86) * 0x1c + 0x22,
                     param_2,param_3,(uint)(ushort)DAT_0002cd14[0x21],param_4);
        iVar2 = FUN_0003d7b0(DAT_0002cd18,param_1,
                             puVar1 + (uint)*(ushort *)((int)puVar1 + 0x86) * 0x1c + 0x22,param_3,0)
        ;
        if (iVar2 != 0) {
          return;
        }
        uVar3 = *(ushort *)((int)puVar1 + 0x86) + 1;
        *(ushort *)(puVar1 + 0x21) =
             (ushort)puVar1[0x21] | (ushort)(1 << (*(ushort *)((int)puVar1 + 0x86) & 0xff));
        *(short *)((int)puVar1 + 0x86) = (short)uVar3;
        if ((uVar3 & 0xffff) < 8) {
          return;
        }
        *(undefined2 *)((int)puVar1 + 0x86) = 0;
        return;
      }
      FUN_0001c590(DAT_0002cd14 + *DAT_0002cd14 * 4 + 1);
      iVar2 = FUN_0003d7b0(DAT_0002cd18,param_1,puVar1 + *puVar1 * 4 + 1,param_3,0);
      if (iVar2 != 0) {
        return;
      }
      uVar3 = *puVar1;
      *puVar1 = uVar3 + 1;
      if (uVar3 + 1 < 8) {
        return;
      }
      *puVar1 = 0;
      return;
    }
  }
  else if (*DAT_0002cd10 != '\x02') {
    return;
  }
  FUN_0003d7b0(DAT_0002cd18,param_1,param_2,param_3,0);
  return;
}

