// @0x1450a size=60

void FUN_0001450a(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = DAT_000145ec;
  if (*(char *)(DAT_000145ec + 10) == '\x01') {
    cVar1 = *(char *)(DAT_000145ec + 0x18);
  }
  else {
    if (*(char *)(DAT_000145ec + 10) != '\x02') {
      return;
    }
    cVar1 = *(char *)(DAT_000145ec + 0x19);
  }
  if (cVar1 != '\0') {
    *(int *)(DAT_00014610 + -0x94) =
         1 << *(sbyte *)(DAT_000145ec + 0x1e) | 1 << *(sbyte *)(DAT_000145ec + 0x1f);
    *(undefined4 *)(DAT_00014618 + (uint)*(byte *)(iVar2 + 0x20) * 4 + 0x510) = 0;
  }
  return;
}

