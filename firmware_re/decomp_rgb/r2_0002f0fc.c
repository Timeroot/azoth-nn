// FUN_0002f0fc @0002f0fc size=288

void FUN_0002f0fc(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  
  iVar1 = DAT_0002f21c;
  iVar3 = *(int *)(DAT_0002f21c + 0x74);
  if (iVar3 != 0) {
    if (iVar3 == 1) {
      iVar4 = FUN_00029fd4();
      iVar2 = DAT_0002f234;
      iVar3 = DAT_0002f22c;
      if (iVar4 != 0) {
        return;
      }
      uVar5 = *(uint *)(iVar1 + 0x70);
      iVar4 = 0;
      do {
        iVar7 = iVar2 + (iVar4 + uVar5 * 0x18) * 0x80;
        puVar6 = (undefined4 *)(iVar3 + iVar4 * 0xc);
        iVar4 = iVar4 + 1;
        *(undefined4 *)(iVar7 + 0x74) = *puVar6;
        *(undefined4 *)(iVar7 + 0x78) = puVar6[1];
        *(undefined4 *)(iVar7 + 0x7c) = puVar6[2];
      } while (iVar4 < 0x10);
      *(undefined4 *)(iVar1 + 0x74) = 6;
      uVar5 = *(uint *)(iVar1 + 0x3c) & ~(1 << (uVar5 & 0xff));
      *(uint *)(iVar1 + 0x3c) = uVar5;
      if ((uVar5 & 7) != 0) {
        return;
      }
      *(undefined1 *)(iVar1 + 2) = 1;
      return;
    }
    if (iVar3 != 6) {
      return;
    }
    uVar5 = *(uint *)(DAT_0002f21c + 0x3c);
    if ((uVar5 & 7) == 0) {
      return;
    }
    *(undefined4 *)(DAT_0002f21c + 0x70) = 0;
    do {
      if ((1 << (*(uint *)(iVar1 + 0x70) & 0xff) & uVar5) != 0) {
        *(undefined4 *)(iVar1 + 0x74) = 0;
        return;
      }
      iVar3 = *(uint *)(iVar1 + 0x70) + 1;
      *(int *)(iVar1 + 0x70) = iVar3;
    } while (iVar3 < 3);
    return;
  }
  if (*(char *)(DAT_0002f21c + 3) == '\0') {
    return;
  }
  iVar3 = FUN_00029fd4();
  if (iVar3 != 0) {
    return;
  }
  iVar3 = *(int *)(iVar1 + 0x70);
  uVar5 = 0xff;
  if (iVar3 == 0) {
    if (*(byte *)(DAT_0002f220 + 8) == 1) {
      uVar5 = 0xb;
    }
    else if (*(byte *)(DAT_0002f220 + 8) < 4) {
      uVar5 = 9;
    }
    else {
      uVar5 = 0xd;
    }
LAB_0002f18a:
    *(undefined1 *)(iVar1 + 3) = 0;
  }
  else {
    if (iVar3 == 1) {
      uVar5 = (uint)*(byte *)(DAT_0002f220 + 8);
    }
    else if (iVar3 == 2) {
      if (*(byte *)(DAT_0002f220 + 8) == 1) {
        uVar5 = 0xc;
      }
      else if (*(byte *)(DAT_0002f220 + 8) < 4) {
        uVar5 = 10;
      }
      else {
        uVar5 = 0xe;
      }
      goto LAB_0002f18a;
    }
    *(undefined1 *)(iVar1 + 3) = 0;
    if (uVar5 == 0xff) {
      *(undefined4 *)(iVar1 + 0x74) = 6;
      return;
    }
  }
  if ((*(int *)(DAT_0002f224 + 0x60) == 0) || (-1 < (int)((uint)*DAT_0002f228 << 0x1e))) {
    FUN_000283e0(DAT_0002f230 + uVar5 * 0xc2 + 2,DAT_0002f22c,0xc0);
  }
  else {
    FUN_0001c5e0(DAT_0002f22c,0xc0);
  }
  *(int *)(iVar1 + 0x74) = *(int *)(iVar1 + 0x74) + 1;
  return;
}

