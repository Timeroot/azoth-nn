// @0xf37c0

byte FUN_000f37c0(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = DAT_000f3814;
  iVar1 = DAT_000f3810;
  *(undefined4 *)(DAT_000f3814 + 0x700) = 0xc;
  *(undefined4 *)(iVar2 + 0x704) = 0xc;
  (*DAT_000f3818)(0x3c0);
  uVar3 = *(uint *)(iVar1 + 0x510);
  uVar4 = *(uint *)(iVar1 + 0x510);
  *(undefined4 *)(iVar2 + 0x704) = 4;
  *(undefined4 *)(iVar2 + 0x700) = 4;
  return (uVar3 >> 0xe & 1) == 0 | ((uVar4 >> 0xf & 1) == 0) << 1;
}

