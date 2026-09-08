FW = r"C:\Users\Timeroot\azoth\M701_fw\M701_FirmwareAutoUpdate_1.0.0.14\FirmwareAutoUpdate_1.0.0.14\Firmware\M701_KEYBOARD_V04_00_13.bin"
d = open(FW, "rb").read()
K = {0: ".", 0x28: "Enter", 0x29: "Esc", 0x2a: "BkSp", 0x2b: "Tab", 0x2c: "Space",
     0x2d: "-", 0x2e: "=", 0x2f: "[", 0x30: "]", 0x31: "Bslash", 0x33: ";", 0x34: "Quote",
     0x35: "Grave", 0x36: ",", 0x37: ".", 0x38: "/", 0x39: "Caps",
     0x46: "PrtSc", 0x47: "ScrLk", 0x48: "Pause", 0x49: "Ins", 0x4a: "Home", 0x4b: "PgUp",
     0x4c: "Del", 0x4d: "End", 0x4e: "PgDn", 0x4f: "Right", 0x50: "Left", 0x51: "Down", 0x52: "Up",
     0xe0: "LCtrl", 0xe1: "LShift", 0xe2: "LAlt", 0xe3: "LGUI", 0xe4: "RCtrl", 0xe5: "RShift",
     0xe6: "RAlt", 0xe7: "Fn"}
for c, n in zip(range(0x04, 0x1e), "ABCDEFGHIJKLMNOPQRSTUVWXYZ"):
    K[c] = n
for c, n in zip(range(0x1e, 0x28), "1234567890"):
    K[c] = n
for c in range(0x3a, 0x46):
    K[c] = "F%d" % (c - 0x39)

def nm(b):
    return K.get(b, "%02x" % b)

def show(base, label):
    t = d[base:base + 98]
    print("\n===== %s  table @0x%x =====" % (label, base))
    for col in range(7):
        print(" col%d:" % col, " ".join("%5s" % nm(t[col * 14 + r]) for r in range(14)))
    print(" combo (col*14+row): ", end="")
    for c, r in [(3, 9), (4, 6), (5, 10)]:
        print("(c%d,r%d)=%s  " % (c, r, nm(t[c * 14 + r])), end="")
    print()

# CORRECT base is 0x476a3 (proven: DAT_0002a7a8 literal @0x2a7a8 = 0x000476a3, the
# ONLY occurrence; 0x476a4 never appears as a literal). Base 0x476a3 puts Esc at
# (col0,row0) and every column becomes a clean physical row (leftmost key at row0).
show(0x0476a3, "APP keymap layer0")
show(0x0fa4d8, "BOOTLOADER keymap")
# Bootloader DFU combo cells (col3 bit9)+(col4 bit6)+(col5 bit10) => Fn + L + B
