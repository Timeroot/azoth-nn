// Dump decompilation of the OLED dispatcher + its direct callees (per-command
// handlers) to .c files. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_dump extends GhidraScript {
    DecompInterface dec;
    ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
    String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp\\";

    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec = new DecompInterface();
        dec.openProgram(currentProgram);
        Set<Function> done = new HashSet<>();
        long[] roots = {0xdb850L, 0x2330cL};
        for (long r : roots) {
            Function f = getFunctionAt(toAddr(r));
            if (f != null) dump(f, done, 1);
        }
        println("DONE dumped " + done.size() + " functions to " + outdir);
    }

    void dump(Function f, Set<Function> done, int depth) throws Exception {
        if (f == null || done.contains(f)) return;
        done.add(f);
        DecompileResults r = dec.decompileFunction(f, 120, mon);
        String c = (r != null && r.getDecompiledFunction() != null)
                ? r.getDecompiledFunction().getC() : "// decomp failed";
        String fn = String.format("%s%06x_%s.c", outdir, f.getEntryPoint().getOffset(), f.getName());
        FileWriter w = new FileWriter(fn);
        w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + "  size="
                + f.getBody().getNumAddresses() + "\n" + c);
        w.close();
        if (depth > 0)
            for (Function callee : f.getCalledFunctions(mon)) dump(callee, done, depth - 1);
    }
}
