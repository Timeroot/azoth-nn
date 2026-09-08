// @0x22f60  size=618

void FUN_00022f60(int param_1,uint param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined1 local_28;
  undefined1 uStack_27;
  
  iVar4 = DAT_000231dc;
  puVar3 = (undefined2 *)(param_1 * 3 + DAT_000231d8);
  uVar2 = *puVar3;
  uVar1 = *(undefined1 *)(puVar3 + 1);
  *(ushort *)(DAT_000231dc + 2) = *(ushort *)(DAT_000231dc + 2) & ~(ushort)(1 << (param_2 & 0xff));
  local_28 = (undefined1)uVar2;
  uStack_27 = (undefined1)((ushort)uVar2 >> 8);
  switch(param_2) {
  case 0:
    *(undefined1 *)(iVar4 + 4) = 0x1e;
    *(undefined1 *)(iVar4 + 5) = 0x32;
    *(undefined1 *)(iVar4 + 6) = 0;
    *(undefined1 *)(iVar4 + 7) = 0xff;
    *(undefined1 *)(iVar4 + 8) = 0xff;
    *(undefined1 *)(iVar4 + 9) = local_28;
    *(undefined1 *)(iVar4 + 10) = uStack_27;
    *(undefined1 *)(iVar4 + 0xb) = uVar1;
    *(undefined1 *)(iVar4 + 0xc) = 0;
    *(undefined1 *)(iVar4 + 0xd) = 0;
    *(undefined1 *)(iVar4 + 0xe) = 0;
    *(undefined1 *)(iVar4 + 0xf) = 0;
    *(undefined1 *)(iVar4 + 0x10) = 0;
    *(undefined1 *)(iVar4 + 0x11) = 0;
    break;
  case 1:
    *(undefined1 *)(iVar4 + 0x12) = 0x1e;
    *(undefined1 *)(iVar4 + 0x13) = 0x32;
    *(undefined1 *)(iVar4 + 0x14) = 0;
    *(undefined1 *)(iVar4 + 0x15) = 0xff;
    *(undefined1 *)(iVar4 + 0x16) = 0xff;
    *(undefined1 *)(iVar4 + 0x17) = local_28;
    *(undefined1 *)(iVar4 + 0x18) = uStack_27;
    *(undefined1 *)(iVar4 + 0x19) = uVar1;
    *(undefined1 *)(iVar4 + 0x1a) = 0;
    *(undefined1 *)(iVar4 + 0x1b) = 0;
    *(undefined1 *)(iVar4 + 0x1c) = 0;
    *(undefined1 *)(iVar4 + 0x1d) = 0;
    *(undefined1 *)(iVar4 + 0x1e) = 0;
    *(undefined1 *)(iVar4 + 0x1f) = 0;
    break;
  case 2:
    *(undefined1 *)(iVar4 + 0x20) = 0x1f;
    *(undefined1 *)(iVar4 + 0x21) = 0x32;
    *(undefined1 *)(iVar4 + 0x22) = 0;
    *(undefined1 *)(iVar4 + 0x23) = 0xff;
    *(undefined1 *)(iVar4 + 0x24) = 0xff;
    *(undefined1 *)(iVar4 + 0x25) = 0;
    *(undefined1 *)(iVar4 + 0x26) = 0;
    *(undefined1 *)(iVar4 + 0x27) = 0;
    *(undefined1 *)(iVar4 + 0x28) = 0;
    *(undefined1 *)(iVar4 + 0x29) = 0;
    *(undefined1 *)(iVar4 + 0x2a) = 0;
    *(undefined1 *)(iVar4 + 0x2b) = 0;
    *(undefined1 *)(iVar4 + 0x2c) = 0;
    *(undefined1 *)(iVar4 + 0x2d) = 0;
    break;
  case 3:
    *(undefined1 *)(iVar4 + 0x78) = 0xf;
    *(undefined1 *)(iVar4 + 0x79) = 0x32;
    iVar4 = iVar4 + 0x7a;
    *(bool *)iVar4 = param_1 == 0;
    goto LAB_000231b4;
  case 4:
    *(undefined1 *)(iVar4 + 0x2e) = 0x3c;
    *(undefined1 *)(iVar4 + 0x2f) = 0x32;
    *(undefined1 *)(iVar4 + 0x30) = 0;
    *(undefined1 *)(iVar4 + 0x31) = 0;
    *(undefined1 *)(iVar4 + 0x32) = 2;
    *(undefined1 *)(iVar4 + 0x33) = 7;
    *(undefined1 *)(iVar4 + 0x34) = 8;
    *(undefined1 *)(iVar4 + 0x35) = 0xff;
    *(undefined1 *)(iVar4 + 0x36) = 0;
    *(undefined1 *)(iVar4 + 0x37) = 0x10;
    *(undefined1 *)(iVar4 + 0x38) = 0x17;
    *(undefined1 *)(iVar4 + 0x39) = 0xe8;
    *(undefined1 *)(iVar4 + 0x3a) = 0;
    *(undefined1 *)(iVar4 + 0x3b) = 0xff;
    *(undefined1 *)(iVar4 + 0x3c) = 0x27;
    *(undefined1 *)(iVar4 + 0x3d) = 8;
    *(undefined1 *)(iVar4 + 0x3e) = 8;
    *(undefined1 *)(iVar4 + 0x3f) = 0xff;
    *(undefined1 *)(iVar4 + 0x40) = 0x36;
    *(undefined1 *)(iVar4 + 0x41) = 0;
    *(undefined1 *)(iVar4 + 0x42) = 0xff;
    *(undefined1 *)(iVar4 + 0x43) = 0xf9;
    *(undefined1 *)(iVar4 + 0x44) = 0x46;
    *(undefined1 *)(iVar4 + 0x45) = 0;
    *(undefined1 *)(iVar4 + 0x46) = 0xff;
    *(undefined1 *)(iVar4 + 0x47) = 8;
    *(undefined1 *)(iVar4 + 0x48) = 0x56;
    *(undefined1 *)(iVar4 + 0x49) = 0xe9;
    *(undefined1 *)(iVar4 + 0x4a) = 0xff;
    *(undefined1 *)(iVar4 + 0x4b) = 0;
    *(undefined1 *)(iVar4 + 0x4c) = 100;
    *(undefined1 *)(iVar4 + 0x4d) = 0xff;
    *(undefined1 *)(iVar4 + 0x4e) = 0x14;
    *(undefined1 *)(iVar4 + 0x4f) = 0;
    *(undefined1 *)(iVar4 + 0x50) = 0;
    *(undefined1 *)(iVar4 + 0x51) = 0;
    *(undefined1 *)(iVar4 + 0x52) = 0;
    break;
  case 5:
    *(undefined1 *)(iVar4 + 0x53) = 100;
    *(undefined1 *)(iVar4 + 0x54) = 0x32;
    *(bool *)(iVar4 + 0x55) = param_1 == 0;
    *(undefined1 *)(iVar4 + 0x56) = 0xff;
    *(undefined1 *)(iVar4 + 0x57) = 1;
    *(undefined1 *)(iVar4 + 0x58) = 1;
    *(undefined1 *)(iVar4 + 0x59) = 100;
    *(undefined1 *)(iVar4 + 0x5a) = local_28;
    *(undefined1 *)(iVar4 + 0x5b) = uStack_27;
    *(undefined1 *)(iVar4 + 0x5c) = uVar1;
    *(undefined1 *)(iVar4 + 0x5d) = 0;
    *(undefined1 *)(iVar4 + 0x5e) = 0;
    *(undefined1 *)(iVar4 + 0x5f) = 0;
    *(undefined1 *)(iVar4 + 0x60) = 0;
    *(undefined1 *)(iVar4 + 0x61) = 0;
    *(undefined1 *)(iVar4 + 0x62) = 0;
    *(undefined1 *)(iVar4 + 99) = 0;
    *(undefined1 *)(iVar4 + 100) = 0;
    *(undefined1 *)(iVar4 + 0x65) = 0;
    *(undefined1 *)(iVar4 + 0x66) = 0;
    *(undefined1 *)(iVar4 + 0x67) = 0;
    *(undefined1 *)(iVar4 + 0x68) = 0;
    *(undefined1 *)(iVar4 + 0x69) = 0;
    *(undefined1 *)(iVar4 + 0x6a) = 0;
    *(undefined1 *)(iVar4 + 0x6b) = 0;
    *(undefined1 *)(iVar4 + 0x6c) = 0;
    *(undefined1 *)(iVar4 + 0x6d) = 0;
    *(undefined1 *)(iVar4 + 0x6e) = 0;
    *(undefined1 *)(iVar4 + 0x6f) = 0;
    *(undefined1 *)(iVar4 + 0x70) = 0;
    *(undefined1 *)(iVar4 + 0x71) = 0;
    *(undefined1 *)(iVar4 + 0x72) = 0;
    *(undefined1 *)(iVar4 + 0x73) = 0;
    *(undefined1 *)(iVar4 + 0x74) = 0;
    *(undefined1 *)(iVar4 + 0x75) = 0;
    *(undefined1 *)(iVar4 + 0x76) = 0;
    *(undefined1 *)(iVar4 + 0x77) = 0;
    break;
  case 6:
    *(undefined1 *)(iVar4 + 0x86) = 0xf;
    *(undefined1 *)(iVar4 + 0x87) = 0x32;
    iVar4 = iVar4 + 0x88;
    *(bool *)iVar4 = param_1 == 0;
    goto LAB_000231b4;
  case 7:
    *(undefined1 *)(iVar4 + 0x94) = 0xf;
    *(undefined1 *)(iVar4 + 0x95) = 0x32;
    *(bool *)(iVar4 + 0x96) = param_1 == 0;
    *(undefined1 *)(iVar4 + 0x97) = 2;
    *(undefined1 *)(iVar4 + 0x98) = 0xff;
    *(undefined1 *)(iVar4 + 0x99) = local_28;
    *(undefined1 *)(iVar4 + 0x9a) = uStack_27;
    *(undefined1 *)(iVar4 + 0x9b) = uVar1;
    *(undefined1 *)(iVar4 + 0x9c) = local_28;
    *(undefined1 *)(iVar4 + 0x9d) = uStack_27;
    *(undefined1 *)(iVar4 + 0x9e) = uVar1;
    *(undefined1 *)(iVar4 + 0x9f) = local_28;
    *(undefined1 *)(iVar4 + 0xa0) = uStack_27;
    *(undefined1 *)(iVar4 + 0xa1) = uVar1;
    *(undefined1 *)(iVar4 + 0xa2) = local_28;
    *(undefined1 *)(iVar4 + 0xa3) = uStack_27;
    *(undefined1 *)(iVar4 + 0xa4) = uVar1;
    *(undefined1 *)(iVar4 + 0xa5) = local_28;
    *(undefined1 *)(iVar4 + 0xa6) = uStack_27;
    *(undefined1 *)(iVar4 + 0xa7) = uVar1;
    *(undefined1 *)(iVar4 + 0xa8) = local_28;
    *(undefined1 *)(iVar4 + 0xa9) = uStack_27;
    *(undefined1 *)(iVar4 + 0xaa) = uVar1;
    *(undefined1 *)(iVar4 + 0xab) = 0;
    *(undefined1 *)(iVar4 + 0xac) = 0;
    *(undefined1 *)(iVar4 + 0xad) = 0;
    break;
  case 8:
    *(undefined1 *)(iVar4 + 0xae) = 10;
    *(undefined1 *)(iVar4 + 0xaf) = 0x32;
    iVar4 = iVar4 + 0xb0;
    *(bool *)iVar4 = param_1 == 0;
    goto LAB_000231b4;
  case 9:
    *(undefined1 *)(iVar4 + 0xbc) = 0x14;
    *(undefined1 *)(iVar4 + 0xbd) = 0x32;
    iVar4 = iVar4 + 0xbe;
    *(bool *)iVar4 = param_1 == 0;
LAB_000231b4:
    *(undefined1 *)(iVar4 + 1) = 0xff;
    *(undefined1 *)(iVar4 + 2) = 0xff;
    *(undefined1 *)(iVar4 + 3) = local_28;
    *(undefined1 *)(iVar4 + 4) = uStack_27;
    *(undefined1 *)(iVar4 + 5) = uVar1;
    *(undefined1 *)(iVar4 + 6) = 0;
    *(undefined1 *)(iVar4 + 7) = 0;
    *(undefined1 *)(iVar4 + 8) = 0;
    *(undefined1 *)(iVar4 + 9) = 0;
    *(undefined1 *)(iVar4 + 10) = 0;
    *(undefined1 *)(iVar4 + 0xb) = 0;
  }
  return;
}

