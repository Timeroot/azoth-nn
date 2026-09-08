// FUN_0002fc80 @0002fc80 size=216

void FUN_0002fc80(void)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  
  iVar5 = DAT_0002fd18;
  iVar4 = DAT_0002fd14;
  iVar3 = DAT_0002fd10;
  if (*(int *)(DAT_0002fd0c + 0x18) != 0) {
    return;
  }
  uVar8 = (*(byte *)(DAT_0002fd10 + 0x2b9) & 0x1f) >> 3;
  bVar1 = *(byte *)(DAT_0002fd14 + 5);
  iVar7 = DAT_0002fd10 + 0x2ba;
  if (uVar8 == 0) {
    if (*(int *)(DAT_0002fd0c + 0x48) == 0) {
      return;
    }
    *(undefined4 *)(DAT_0002fd0c + 0x48) = 0;
    uVar2 = *(undefined1 *)(*(int *)(iVar5 + (uint)bVar1 * 4) + 1);
  }
  else {
    if ((uVar8 != 1) && (uVar8 != 2)) {
      return;
    }
    if (*(uint *)(DAT_0002fd0c + 0x48) == uVar8) {
      if (*DAT_0002fd1c <= *(byte *)(DAT_0002fd10 + 0x2b8)) {
        return;
      }
    }
    else if (*DAT_0002fd1c <= *(byte *)(DAT_0002fd10 + 0x2b8)) {
      *(uint *)(DAT_0002fd0c + 0x48) = uVar8;
      iVar3 = DAT_0002fd74;
      if (*(int *)(DAT_0002fd6c + 0x18) != 0) {
        return;
      }
      if (*(int *)(DAT_0002fd6c + 0x48) == 1) {
        FUN_00032010(0,DAT_0002fd70 + 4);
        uVar2 = *(undefined1 *)(iVar3 + 7);
        uVar6 = 0;
      }
      else {
        if (*(int *)(DAT_0002fd6c + 0x48) != 2) {
          return;
        }
        if (*(byte *)(*(int *)(DAT_0002fd78 + (uint)*(byte *)(DAT_0002fd74 + 5) * 4) + 1) < 0x19) {
          return;
        }
        FUN_00032010(0x19,DAT_0002fd70 + 4);
        uVar2 = *(undefined1 *)(iVar3 + 7);
        uVar6 = 0x19;
      }
      FUN_00032550(uVar6,uVar2);
      return;
    }
    *(undefined4 *)(DAT_0002fd0c + 0x48) = 0;
    uVar2 = *(undefined1 *)(*(int *)(iVar5 + (uint)bVar1 * 4) + 1);
  }
  FUN_00032010(uVar2,iVar3 + 4);
  FUN_00032550(*(undefined1 *)((uint)*(byte *)(iVar4 + 7) + iVar7));
  return;
}

