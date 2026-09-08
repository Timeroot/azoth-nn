// Follow bootloader entry pointers, disassemble reachable code, create functions,
// decompile the bootloader main + its callees (incl the P1.IN button check).
// @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_bootasm2 extends GhidraScript {
    DecompInterface dec; ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
    String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_boot\\";

    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec = new DecompInterface(); dec.openProgram(currentProgram);
        long p0 = getInt(toAddr(0xf34c0L)) & 0xffffffffL;
        long p1 = getInt(toAddr(0xf34c4L)) & 0xffffffffL;
        println("entry ptrs: 0x" + Long.toHexString(p0) + " 0x" + Long.toHexString(p1));
        // aggressive: disassemble every even addr in the region not yet code (flow-follows)
        for (long a = 0xf3000L; a < 0xff000L; a += 2) {
            Address ad = toAddr(a);
            if (getInstructionAt(ad) == null && getUndefinedDataAt(ad) != null) {
                try { disassemble(ad); } catch (Exception e) {}
            }
        }
        // create functions at the entry pointers + P1.IN sites (walk back to prologue)
        long[] seeds = {p0 & ~1L, p1 & ~1L, 0xf36ecL, 0xf3f20L};
        Set<Function> done = new LinkedHashSet<>();
        for (long s : seeds) {
            Function f = getFunctionContaining(toAddr(s));
            if (f == null) {
                Address start = findFuncStart(toAddr(s));
                if (start != null) try { f = createFunction(start, null); } catch (Exception e) {}
            }
            if (f != null && done.add(f)) dumpWithCallees(f, done, 1);
            else println("  no func for seed 0x" + Long.toHexString(s));
        }
        println("DONE dumped " + done.size());
    }

    Address findFuncStart(Address a) {
        // walk back up to 0x400 bytes for a 'push {...,lr}' (b5xx) prologue
        for (int i = 0; i < 0x400; i += 2) {
            Address t = a.subtract(i);
            Instruction ins = getInstructionAt(t);
            if (ins != null && ins.getMnemonicString().toLowerCase().startsWith("push")
                    && ins.toString().contains("lr")) return t;
        }
        return null;
    }

    void dumpWithCallees(Function f, Set<Function> done, int depth) throws Exception {
        DecompileResults r = dec.decompileFunction(f, 120, mon);
        String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
        FileWriter w = new FileWriter(String.format("%sbl_%06x.c", outdir, f.getEntryPoint().getOffset()));
        w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + "\n" + c); w.close();
        println("  dumped bl_" + Long.toHexString(f.getEntryPoint().getOffset()) + " (size "
                + f.getBody().getNumAddresses() + ")");
        if (depth > 0) for (Function cal : f.getCalledFunctions(mon)) {
            if (cal.getEntryPoint().getOffset() >= 0xf3000L && done.add(cal)) dumpWithCallees(cal, done, depth - 1);
        }
    }
}
