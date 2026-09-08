// Find the APP matrix column-drive routine: functions that write GPIO OUTSET
// (base+0x508) or OUTCLR (+0x50c) in the app region (<0xd0000), to recover the
// column->pin order and compare to the bootloader's pin=col+9. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.lang.OperandType;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_colscan extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_scan\\";
        new File(outdir).mkdirs();
        // Scan app region instructions for immediate scalars 0x508/0x50c/0x510 used as
        // register offsets, collect containing functions.
        Set<Function> fns = new LinkedHashSet<>();
        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        while (it.hasNext()) {
            Instruction ins = it.next();
            long a = ins.getAddress().getOffset();
            if (a >= 0xd0000L) continue;           // app region only
            for (int op = 0; op < ins.getNumOperands(); op++) {
                for (Object o : ins.getOpObjects(op)) {
                    if (o instanceof Scalar) {
                        long v = ((Scalar) o).getUnsignedValue();
                        if (v == 0x508 || v == 0x50c || v == 0x510) {
                            Function f = getFunctionContaining(ins.getAddress());
                            if (f != null) fns.add(f);
                        }
                    }
                }
            }
        }
        println("app funcs touching GPIO OUTSET/OUTCLR/IN offsets: " + fns.size());
        for (Function f : fns) {
            println("  " + f.getName() + " @0x" + Long.toHexString(f.getEntryPoint().getOffset())
                    + " size=" + f.getBody().getNumAddresses());
            DecompileResults r = dec.decompileFunction(f, 120, mon);
            String c = (r != null && r.getDecompiledFunction() != null) ? r.getDecompiledFunction().getC() : "// fail";
            FileWriter w = new FileWriter(String.format("%scol_%06x.c", outdir, f.getEntryPoint().getOffset()));
            w.write("// @0x" + Long.toHexString(f.getEntryPoint().getOffset()) + " size="
                    + f.getBody().getNumAddresses() + "\n" + c); w.close();
        }
        println("DONE");
    }
}
