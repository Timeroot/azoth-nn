// FUN_00025e50 @00025e50 size=236

void FUN_00025e50(int param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined2 local_1c;
  
  cVar1 = *(char *)(param_1 + 0x3a);
  *(char *)(param_1 + 0x3a) = cVar1 + '\x01';
  if (0xbb < (byte)(cVar1 + 1U)) {
    *(undefined1 *)(param_1 + 0x3a) = 0;
  }
  if (cVar1 == '@') {
    if (*(char *)(param_1 + 0xe) == '\x01') {
      uVar5 = FUN_000292a4();
      *(short *)(param_1 + 0x8c) = (short)uVar5;
      *(char *)(param_1 + 0x8e) = (char)((uint)uVar5 >> 0x10);
    }
    else {
      iVar7 = (uint)*(byte *)(param_1 + 0xd4) * 0x21 + param_1;
      *(undefined2 *)(param_1 + 0x8c) = *(undefined2 *)(iVar7 + 0x96);
      *(undefined1 *)(param_1 + 0x8e) = *(undefined1 *)(iVar7 + 0x98);
      *(bool *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) == 0;
    }
  }
  iVar3 = FUN_0003b708(cVar1);
  iVar7 = DAT_00025f3c;
  uVar8 = (uint)*(byte *)(param_1 + 0x24);
  local_1c = CONCAT11((char)(uVar8 * (iVar3 * (uint)*(byte *)(param_1 + 0x8d) >> 8) >> 7),
                      (char)(uVar8 * (iVar3 * (uint)*(byte *)(param_1 + 0x8c) >> 8) >> 7));
  bVar2 = *(byte *)(param_1 + 0x8e);
  uVar10 = 0;
  do {
    uVar9 = 0;
    do {
      iVar4 = FUN_0002b5e0(param_1,*(undefined4 *)(iVar7 + 0x6c),1,uVar10 & 0xff,uVar9 & 0xff);
      if (iVar4 == 0) {
        puVar6 = (undefined2 *)(uVar9 * 3 + uVar10 * 0x30 + *(int *)(param_1 + 0xe0));
        *puVar6 = local_1c;
        *(char *)(puVar6 + 1) = (char)(uVar8 * (iVar3 * (uint)bVar2 >> 8) >> 7);
      }
      uVar9 = uVar9 + 1;
    } while ((int)uVar9 < 0x10);
    uVar10 = uVar10 + 1;
  } while ((int)uVar10 < 6);
  return;
}

