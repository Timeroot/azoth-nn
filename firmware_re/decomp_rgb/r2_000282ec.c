// FUN_000282ec @000282ec size=92

void FUN_000282ec(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined2 local_c;
  undefined1 local_a;
  
  FUN_000271c0();
  iVar1 = DAT_0002834c;
  iVar3 = DAT_00028348;
  if (param_1 == 0xf6) {
    iVar2 = 0;
    do {
      iVar4 = iVar3 + iVar2 * 2;
      iVar2 = iVar2 + 1;
      puVar5 = (undefined2 *)
               ((uint)*(byte *)(iVar4 + 0x3d) * 3 + (uint)*(byte *)(iVar4 + 0x3c) * 0x30 +
               *(int *)(*(int *)(iVar1 + 0x68) + 0xe0));
      local_c = (undefined2)param_2;
      *puVar5 = local_c;
      local_a = (undefined1)((uint)param_2 >> 0x10);
      *(undefined1 *)(puVar5 + 1) = local_a;
      iVar4 = DAT_00028348;
    } while (iVar2 < 10);
    iVar3 = *(int *)(*(int *)(iVar1 + 0x68) + 0xe0);
    *(undefined2 *)(iVar3 + 0x51) = *(undefined2 *)(DAT_00028348 + -0x22);
    *(undefined1 *)(iVar3 + 0x53) = *(undefined1 *)(iVar4 + -0x20);
  }
  return;
}

