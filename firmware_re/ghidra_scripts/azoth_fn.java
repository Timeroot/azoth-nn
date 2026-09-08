// Dump the Fn-handling functions and anything referencing the Fn-held flag, to
// recover how Fn remaps keys (profiles on 1-6, F12, PrtSc/Home/End, arrows). @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_fn extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_fn\\";
        new File(outdir).mkdirs();
        // Fn handler + key-processing callees seen in FUN_0002a498
        long[] addrs = {0x2b6c4L, 0x2ba90L, 0x2bad4L, 0x3b354L, 0x30ac0L, 0x30f3cL, 0x336b4L, 0x2326cL};
        Set<Function> done = new LinkedHashSet<>();
        for (long a : addrs) {
            Function f = getFunctionContaining(toAddr(a));
            if (f != null && done.add(f)) {
                DecompileResults r = dec.decompileFunction(f, 120, mon);
                String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
                FileWriter w = new FileWriter(String.format("%sfn_%06x.c", outdir, f.getEntryPoint().getOffset()));
                w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + " size="
                        + f.getBody().getNumAddresses() + "\n" + c); w.close();
                println("dumped fn_" + Long.toHexString(f.getEntryPoint().getOffset()) + " size=" + f.getBody().getNumAddresses());
            }
        }
        println("DONE");
    }
}
