// Locate + decompile the Azoth HID command handler via the RX-log string @0xde440.
// @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.util.*;

public class azoth_query extends GhidraScript {
    DecompInterface dec;
    ConsoleTaskMonitor mon = new ConsoleTaskMonitor();

    public void run() throws Exception {
        AddressSpace sp = currentProgram.getAddressFactory().getDefaultAddressSpace();
        FunctionManager fm = currentProgram.getFunctionManager();
        println("FUNCTION_COUNT " + fm.getFunctionCount());
        dec = new DecompInterface();
        dec.openProgram(currentProgram);

        long[] anchors = {0xde440L, 0xde458L, 0xde430L};
        Set<Function> handlers = new LinkedHashSet<>();
        for (long t : anchors) {
            Address a = sp.getAddress(t);
            Reference[] refs = getReferencesTo(a);
            println("\n=== xrefs to 0x" + Long.toHexString(t) + ": " + refs.length + " ===");
            for (Reference r : refs) {
                Address fa = r.getFromAddress();
                Function f = getFunctionContaining(fa);
                println("  from 0x" + Long.toHexString(fa.getOffset()) + " func=" + (f != null ? f.getName() : "?"));
                if (f != null) handlers.add(f);
            }
        }
        for (Function f : handlers) decomp(f, "HANDLER");

        println("\n=== functions in 0xd0000-0xf3000 (biggest 25) ===");
        List<Function> fns = new ArrayList<>();
        FunctionIterator it = fm.getFunctions(true);
        while (it.hasNext()) {
            Function f = it.next();
            long ep = f.getEntryPoint().getOffset();
            if (ep >= 0xd0000L && ep < 0xf3000L) fns.add(f);
        }
        fns.sort((x, y) -> Long.compare(y.getBody().getNumAddresses(), x.getBody().getNumAddresses()));
        for (int i = 0; i < Math.min(25, fns.size()); i++) {
            Function f = fns.get(i);
            println(String.format("  0x%06x size=%-5d %s", f.getEntryPoint().getOffset(),
                    f.getBody().getNumAddresses(), f.getName()));
        }
    }

    void decomp(Function f, String tag) {
        if (f == null) { println("(no func)"); return; }
        DecompileResults r = dec.decompileFunction(f, 90, mon);
        println("\n==== " + tag + " " + f.getName() + " @0x" + Long.toHexString(f.getEntryPoint().getOffset())
                + " (size " + f.getBody().getNumAddresses() + ") ====");
        if (r != null && r.getDecompiledFunction() != null) println(r.getDecompiledFunction().getC());
        else println("  decomp failed");
    }
}
