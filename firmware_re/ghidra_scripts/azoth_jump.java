// Find callers of FUN_0002a058 (GPREGRET+reset "enter bootloader") and decompile them
// to recover the HID command that triggers a software jump-to-bootloader. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_jump extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_jump\\";
        new File(outdir).mkdirs();
        Set<Function> fns = new LinkedHashSet<>();
        for (long t : new long[]{0x2a058L, 0x292f8L}) {
            Function tgt = getFunctionContaining(toAddr(t));
            if (tgt!=null) fns.add(tgt);
            Reference[] refs = getReferencesTo(toAddr(t));
            println("refs to 0x"+Long.toHexString(t)+": "+refs.length);
            for (Reference r: refs){
                Function f=getFunctionContaining(r.getFromAddress());
                if (f!=null){ fns.add(f); println("  called from "+f.getName()+" @"+f.getEntryPoint()); }
            }
        }
        for (Function f: fns){
            DecompileResults r=dec.decompileFunction(f,150,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%sjmp_%s.c",outdir,f.getEntryPoint()));
            w.write("// "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses()+"\n"+c); w.close();
            println("dumped "+f.getEntryPoint());
        }
        println("DONE");
    }
}
