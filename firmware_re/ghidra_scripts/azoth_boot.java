// Decompile bootloader functions that read P1.IN (candidate hardware DFU-entry)
// + the software "enter bootloader" path. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_boot extends GhidraScript {
    public void run() throws Exception {
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_boot\\";
        new File(outdir).mkdirs();
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        // instruction addrs that read P1.IN in the bootloader, + bootloader reset,
        // + app 'enter bootloader' string @0x2a074 (find its xref caller)
        long[] addrs = {0xf36ecL, 0xf3f20L, 0xf34a4L, 0xf3ce4L};
        Set<Function> done = new LinkedHashSet<>();
        for (long a : addrs) {
            Function f = getFunctionContaining(toAddr(a));
            if (f == null) { println("no func @0x" + Long.toHexString(a)); continue; }
            if (!done.add(f)) continue;
            DecompileResults r = dec.decompileFunction(f, 120, mon);
            String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
            FileWriter w = new FileWriter(String.format("%s%06x.c", outdir, f.getEntryPoint().getOffset()));
            w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + " (hit via 0x"
                    + Long.toHexString(a) + ")\n" + c); w.close();
            println("dumped 0x" + Long.toHexString(f.getEntryPoint().getOffset()));
        }
        // xrefs to app "enter bootloader" string @0x2a074
        for (Reference r : getReferencesTo(toAddr(0x2a074L))) {
            Function f = getFunctionContaining(r.getFromAddress());
            println("app 'enter bootloader' xref from 0x" + Long.toHexString(r.getFromAddress().getOffset())
                    + " in " + (f != null ? f.getName() : "?"));
            if (f != null && done.add(f)) {
                DecompileResults rr = dec.decompileFunction(f, 120, mon);
                String c = (rr != null && rr.getDecompiledFunction() != null) ? rr.getDecompiledFunction().getC() : "// fail";
                FileWriter w = new FileWriter(String.format("%s%06x_appboot.c", outdir, f.getEntryPoint().getOffset()));
                w.write(c); w.close();
            }
        }
        println("DONE");
    }
}
