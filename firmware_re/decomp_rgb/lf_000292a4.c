// FUN_000292a4 @000292a4 size=50

uint FUN_000292a4(void)

{
  int iVar1;
  uint uVar2;
  uint unaff_r4;
  
  iVar1 = FUN_0001c56c();
  uVar2 = FUN_0003b640(unaff_r4 & 0xff000000 | iVar1 % 0xff & 0xffU | 0xffff00);
  return uVar2 & 0xffffff;
}

