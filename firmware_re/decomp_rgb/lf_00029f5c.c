// FUN_00029f5c @00029f5c size=94

undefined4 FUN_00029f5c(char *param_1)

{
  char cVar1;
  
  if (((((*(char *)(DAT_00029fbc + 6) != -0x57) && (*(int *)(DAT_00029fc0 + 8) == 0)) &&
       (cVar1 = *param_1, cVar1 != -0xe)) &&
      (((cVar1 != -0xc && (cVar1 != -0xb)) && (*(char *)(DAT_00029fc0 + 3) == '\0')))) &&
     ((((*(char *)(*(int *)(DAT_00029fc8 + (uint)*(byte *)(DAT_00029fc4 + 5) * 4) + 1) == '\0' ||
        ((*DAT_00029fcc != 1 && ((int)((uint)*DAT_00029fd0 << 0x1d) < 0)))) || (cVar1 == -1)) ||
      ((((cVar1 == '\0' && (param_1[0x93] == '\0')) && (param_1[0x94] == '\0')) &&
       (param_1[0x95] == '\0')))))) {
    return 0;
  }
  return 1;
}

