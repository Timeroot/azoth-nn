// FUN_00029818 @00029818 size=66

void FUN_00029818(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined2 local_18;
  undefined2 uStack_16;
  
  iVar2 = DAT_00029860;
  iVar1 = DAT_0002985c;
  if (*(byte *)(DAT_0002985c + param_2) != param_1) {
    uStack_16 = (undefined2)((uint)param_4 >> 0x10);
    local_18 = 0xc5fe;
    FUN_000296cc(&local_18,2,*(undefined2 *)(DAT_00029860 + param_2 * 2));
    local_18 = CONCAT11((char)param_1,0xfd);
    *(char *)(iVar1 + param_2) = (char)param_1;
    FUN_000296cc(&local_18,2,*(undefined2 *)(iVar2 + param_2 * 2));
  }
  return;
}

