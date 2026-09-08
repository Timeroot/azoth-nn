// @0x14648 size=298

void FUN_00014648(int param_1,undefined4 param_2)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  *(undefined4 *)(DAT_00014a34 + 0x200) = 3;
  iVar5 = DAT_00014a38;
  puVar6 = DAT_00014a30;
  uVar7 = DAT_00014a3c;
  if (*(char *)(DAT_00014a38 + 0x21) != '\0') {
    uVar7 = 0x60000;
  }
  *DAT_00014a30 = uVar7;
  FUN_0001a720(param_2);
  if (param_1 == 0) {
    iVar10 = FUN_00013624();
    if (iVar10 != 0) {
      FUN_00014e1e(param_2);
    }
    *(undefined1 *)(iVar5 + 10) = 1;
    *(uint *)(iVar5 + 0x38) = *(uint *)(iVar5 + 0x38) | 0x100000;
    uVar7 = 0x100000;
  }
  else {
    if (param_1 != 1) goto LAB_00014546;
    *(undefined1 *)(iVar5 + 10) = 2;
    *(uint *)(iVar5 + 0x38) = *(uint *)(iVar5 + 0x38) | 0x200000;
    uVar7 = 0x200000;
  }
  *puVar6 = uVar7;
LAB_00014546:
  iVar8 = FUN_0000a900();
  iVar10 = DAT_0001460c;
  iVar5 = DAT_000145ec;
  cVar1 = *(char *)(DAT_000145ec + 10);
  if (cVar1 == '\x01') {
    cVar2 = *(char *)(DAT_000145ec + 0x18);
  }
  else {
    if (cVar1 != '\x02') {
      return;
    }
    cVar2 = *(char *)(DAT_000145ec + 0x19);
  }
  if (cVar2 != '\0') {
    if (cVar1 == '\x01') {
      bVar3 = *(byte *)(DAT_000145ec + 0x1c);
      cVar1 = *(char *)(DAT_000145ec + 0x1a);
      iVar9 = 0x11;
    }
    else {
      bVar3 = *(byte *)(DAT_000145ec + 0x1d);
      cVar1 = *(char *)(DAT_000145ec + 0x1b);
      iVar9 = 0x24;
    }
    *(undefined4 *)(DAT_0001460c + 8) = 1;
    puVar6 = DAT_0001461c;
    if ((uint)(iVar8 + iVar9) <= *DAT_0001461c) {
      software_interrupt(0xff);
    }
    *(undefined4 *)(iVar10 + 0x108) = 0;
    *puVar6 = iVar8 + iVar9;
    iVar10 = DAT_00014618;
    bVar4 = *(byte *)(iVar5 + 0x20);
    *(uint *)(DAT_00014618 + (uint)bVar4 * 4 + 0x510) =
         (uint)bVar3 << 8 | (cVar1 != '\0' ^ 1) << 0x14 | 0x30003;
    iVar8 = DAT_00014620;
    iVar10 = iVar10 + (uint)bVar4 * 4;
    bVar3 = *(byte *)(iVar5 + 0x1e);
    iVar9 = DAT_00014620 + (uint)bVar3 * 8;
    *(int *)(iVar9 + 0x514) = iVar10;
    *(undefined4 *)(iVar9 + 0x510) = DAT_00014624;
    bVar4 = *(byte *)(iVar5 + 0x1f);
    iVar8 = iVar8 + (uint)bVar4 * 8;
    *(int *)(iVar8 + 0x514) = iVar10;
    *(undefined4 *)(iVar8 + 0x510) = DAT_00014a2c;
    *DAT_00014a30 = 1 << (uint)bVar3 | 1 << (uint)bVar4;
  }
  return;
}

