# Ghidra post-script (PyGhidra flat API): locate + decompile the HID command
# handler in the Azoth firmware, using the RX-log string @0xde440 as the anchor.
# @category Azoth
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

sp = currentProgram.getAddressFactory().getDefaultAddressSpace()
def A(x): return sp.getAddress(x)
fm = currentProgram.getFunctionManager()
print("=== FUNCTION_COUNT %d ===" % fm.getFunctionCount())

dec = DecompInterface(); dec.openProgram(currentProgram)
mon = ConsoleTaskMonitor()

def decomp(f, tag=""):
    if f is None:
        print("  (no function)"); return
    try:
        r = dec.decompileFunction(f, 90, mon)
        print("\n==== %s DECOMP %s @0x%x (size %d) ====" % (
            tag, f.getName(), f.getEntryPoint().getOffset(), f.getBody().getNumAddresses()))
        print(r.getDecompiledFunction().getC())
    except Exception as e:
        print("  decomp failed: %s" % e)

# --- anchor: strings of interest and their xrefs -> handler functions ---
anchors = {"RX-log 0xde440": 0xde440}
handler_funcs = set()
for name, addr in anchors.items():
    a = A(addr)
    refs = getReferencesTo(a)
    print("\n=== xrefs to %s (0x%x): %d ===" % (name, addr, len(refs)))
    for r in refs:
        fa = r.getFromAddress()
        f = getFunctionContaining(fa)
        print("  from 0x%x  func=%s" % (fa.getOffset(), f.getName() if f else "?"))
        if f: handler_funcs.add(f)

for f in handler_funcs:
    decomp(f, "HANDLER")

# --- fallback: functions in the 0xd0000-0xf3000 block, biggest first ---
print("\n=== functions in 0xd0000-0xf3000 (biggest 20) ===")
fns = []
it = fm.getFunctions(True)
for f in it:
    ep = f.getEntryPoint().getOffset()
    if 0xd0000 <= ep < 0xf3000:
        fns.append((f.getBody().getNumAddresses(), f))
fns.sort(reverse=True, key=lambda t: t[0])
for sz, f in fns[:20]:
    print("  0x%06x  size=%-5d  %s" % (f.getEntryPoint().getOffset(), sz, f.getName()))
