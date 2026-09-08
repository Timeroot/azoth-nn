// @0x39584  size=44

void FUN_00039584(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined2 local_8;
  undefined1 local_6;
  undefined1 local_5;
  
  if (param_3 < 0x2001) {
    _local_8 = CONCAT13((char)param_1,CONCAT12((char)((uint)param_1 >> 8),3));
    local_8 = CONCAT11((char)((uint)param_1 >> 0x10),3);
    FUN_00031330(&local_8,4,param_2,param_3);
  }
  return;
}

