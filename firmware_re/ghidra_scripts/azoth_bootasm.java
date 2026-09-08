// Force-disassemble the bootloader region (own vector table @0xf3000) as Thumb,
// create functions, decompile the P1.IN key-check. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.lang.*;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class azoth_bootasm extends GhidraScript {
    public void run() throws Exception {
        ProgramContext pc = currentProgram.getProgramContext();
        Register tmode = pc.getRegister("TMode");
        Address bstart = toAddr(0xf3000L), bend = toAddr(0xfefffL);
        clearListing(bstart, bend);                                            // remove stale code/data
        if (tmode != null) pc.setValue(tmode, bstart, bend, BigInteger.ONE);   // Thumb

        // disassemble from each bootloader vector-table handler entry
        List<Address> entries = new ArrayList<>();
        for (long off = 0xf3004L; off < 0xf3100L; off += 4) {
            long v = getInt(toAddr(off)) & 0xffffffffL;
            if (v >= 0xf3000L && v < 0xff000L) entries.add(toAddr(v & ~1L));
        }
        // plus the two P1.IN read sites
        entries.add(toAddr(0xf36e0L));
        entries.add(toAddr(0xf3f10L));
        for (Address a : entries) {
            try { disassemble(a); } catch (Exception e) {}
        }
        // create functions at vector entries
        for (Address a : entries) {
            try { if (getFunctionContaining(a) == null) createFunction(a, null); } catch (Exception e) {}
        }
        println("bootloader functions now: ");
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_boot\\";
        new File(outdir).mkdirs();
        Set<Function> done = new LinkedHashSet<>();
        for (long a : new long[]{0xf36ecL, 0xf3f20L, 0xf34a4L}) {
            Function f = getFunctionContaining(toAddr(a));
            if (f == null) { println("  still no func @0x" + Long.toHexString(a)); continue; }
            if (!done.add(f)) continue;
            DecompileResults r = dec.decompileFunction(f, 120, mon);
            String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
            FileWriter w = new FileWriter(String.format("%sbl_%06x.c", outdir, f.getEntryPoint().getOffset()));
            w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + " (via 0x"
                    + Long.toHexString(a) + ")\n" + c); w.close();
            println("  dumped bl_" + Long.toHexString(f.getEntryPoint().getOffset()));
        }
        println("DONE");
    }
}
