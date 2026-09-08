// Find code that references the keymap table @0x476a4 (the scan→HID lookup) and
// decompile it, to recover the exact matrix indexing. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_kmref extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_scan\\";
        new File(outdir).mkdirs();
        Set<Function> fns = new LinkedHashSet<>();
        // check a few keymap-table addresses + the layer stride
        for (long t : new long[]{0x476a4L, 0x47706L, 0x476a6L, 0x476a8L, 0x46d2aL, 0x46d28L}) {
            Reference[] refs = getReferencesTo(toAddr(t));
            println("refs to 0x" + Long.toHexString(t) + ": " + refs.length);
            for (Reference r : refs) {
                Function f = getFunctionContaining(r.getFromAddress());
                println("  from 0x" + Long.toHexString(r.getFromAddress().getOffset())
                        + " in " + (f != null ? f.getName() : "?"));
                if (f != null) fns.add(f);
            }
        }
        for (Function f : fns) {
            DecompileResults r = dec.decompileFunction(f, 120, mon);
            String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
            FileWriter w = new FileWriter(String.format("%skm_%06x.c", outdir, f.getEntryPoint().getOffset()));
            w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + " size="
                    + f.getBody().getNumAddresses() + "\n" + c); w.close();
            println("  dumped km_" + Long.toHexString(f.getEntryPoint().getOffset()));
        }
        println("DONE");
    }
}
