// @0x1a404 size=76

void FUN_0001a404(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  *(undefined4 *)(DAT_0001a464 + 8) = DAT_0001a46c;
  iVar1 = DAT_0001a468;
  uVar2 = 0x11;
  do {
    iVar3 = iVar1 + uVar2 * 8;
    *(undefined4 *)(iVar3 + 0x510) = 0;
    *(undefined4 *)(iVar3 + 0x514) = 0;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x14);
  uVar2 = 0;
  do {
    iVar3 = iVar1 + uVar2 * 4;
    *(uint *)(iVar3 + 0x800) = *(uint *)(iVar3 + 0x800) & 0x1ffff;
    while( true ) {
      uVar2 = uVar2 + 1;
      if (5 < uVar2) {
        return;
      }
      if (uVar2 < 4) break;
      *(undefined4 *)(iVar1 + uVar2 * 4 + 0x800) = 0;
    }
  } while( true );
}

