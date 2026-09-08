import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;

public class azoth_ledsend extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String o = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_rgb\\"; new File(o).mkdirs();
        long[] addrs = {0x31b28L, 0x29704L, 0x29818L, 0x29440L, 0x2ffd8L};
        for (long a : addrs) {
            Function f = getFunctionContaining(toAddr(a));
            if (f == null) { println("no fn @" + Long.toHexString(a)); continue; }
            DecompileResults r = dec.decompileFunction(f, 150, mon);
            String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
            FileWriter w = new FileWriter(String.format("%sls_%s.c", o, f.getEntryPoint()));
            w.write("// " + f.getName() + " @" + f.getEntryPoint() + " size=" + f.getBody().getNumAddresses() + "\n" + c);
            w.close();
            println("dumped " + f.getEntryPoint());
        }
        println("DONE");
    }
}
