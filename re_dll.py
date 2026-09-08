import sys, re
try:
    import pefile
except ImportError:
    import subprocess
    subprocess.run([sys.executable, "-m", "pip", "install", "pefile", "-q"])
    import pefile

path = sys.argv[1]
pe = pefile.PE(path, fast_load=True)
pe.parse_data_directories()
print("machine:", hex(pe.FILE_HEADER.Machine), "(0x8664=x64)")

print("\n=== EXPORTS ===")
if hasattr(pe, "DIRECTORY_ENTRY_EXPORT"):
    for e in pe.DIRECTORY_ENTRY_EXPORT.symbols[:120]:
        if e.name:
            print(f"  {e.name.decode(errors='replace')}")
else:
    print("  (none)")

print("\n=== IMPORTS of interest (hid/kernel32 write/read/sleep) ===")
if hasattr(pe, "DIRECTORY_ENTRY_IMPORT"):
    for mod in pe.DIRECTORY_ENTRY_IMPORT:
        mn = mod.dll.decode(errors="replace").lower()
        if any(k in mn for k in ("hid", "kernel32", "setupapi", "winusb")):
            for imp in mod.imports:
                if imp.name:
                    n = imp.name.decode(errors="replace")
                    if any(k in n for k in ("Write", "Read", "Sleep", "Hid", "Feature", "Report",
                                            "CreateFile", "DeviceIoControl", "Event", "Overlap")):
                        print(f"  {mn}: {n}")

data = open(path, "rb").read()
print("\n=== ASCII strings with keywords ===")
for m in re.finditer(rb"[\x20-\x7e]{4,}", data):
    s = m.group().decode("ascii")
    if re.search(r"(?i)oled|\bgif\b|anim|banner|music|frame|image|delay|retry|ack|packet|upload|azoth|batter|bright", s):
        print(f"  0x{m.start():06x}  {s}")

print("\n=== UTF-16 strings with keywords ===")
for m in re.finditer(rb"(?:[\x20-\x7e]\x00){4,}", data):
    s = m.group().decode("utf-16le", "replace")
    if re.search(r"(?i)oled|\bgif\b|anim|banner|music|frame|image|delay|retry|ack|packet|upload|azoth|batter|bright", s):
        print(f"  0x{m.start():06x}  {s}")
