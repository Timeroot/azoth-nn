// Decompile the app key-scan function (reads P1.IN @0x042500) + its callees, to
// recover the column/row GPIO pin mapping. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_scan extends GhidraScript {
    DecompInterface dec; ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
    String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_scan\\";
    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec = new DecompInterface(); dec.openProgram(currentProgram);
        Set<Function> done = new LinkedHashSet<>();
        for (long a : new long[]{0x042500L, 0x0292a0L, 0x02b300L}) {
            Function f = getFunctionContaining(toAddr(a));
            if (f != null && done.add(f)) dump(f, done, 1, a);
        }
        println("DONE " + done.size());
    }
    void dump(Function f, Set<Function> done, int depth, long via) throws Exception {
        DecompileResults r = dec.decompileFunction(f, 120, mon);
        String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
        FileWriter w = new FileWriter(String.format("%ssc_%06x.c", outdir, f.getEntryPoint().getOffset()));
        w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + " via 0x" + Long.toHexString(via)
                + " size=" + f.getBody().getNumAddresses() + "\n" + c); w.close();
        println("  dumped sc_" + Long.toHexString(f.getEntryPoint().getOffset()) + " size=" + f.getBody().getNumAddresses());
        if (depth > 0) for (Function cal : f.getCalledFunctions(mon)) if (done.add(cal)) dump(cal, done, depth - 1, 0);
    }
}
