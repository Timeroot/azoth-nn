// Decompile peripheral_fwu_pro checksum + version logic: find funcs referencing the
// key strings and dump them. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class fwu_checksum extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon = new ConsoleTaskMonitor();
        String outdir = "C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_fwu\\";
        new File(outdir).mkdirs();
        String[] needles = {"Read checksum", "is different", "has wrong", "Programming Success",
                            "Application Version", "Skip Update", "checksum"};
        Set<Function> fns = new LinkedHashSet<>();
        // scan defined strings
        DataIterator di = currentProgram.getListing().getDefinedData(true);
        Listing lst = currentProgram.getListing();
        for (Data d : (Iterable<Data>)() -> currentProgram.getListing().getDefinedData(true)) {
            Object v = d.getValue();
            if (!(v instanceof String)) continue;
            String s = (String) v;
            boolean hit=false; for (String n:needles) if (s.contains(n)) hit=true;
            if (!hit) continue;
            for (Reference r : getReferencesTo(d.getAddress())) {
                Function f = getFunctionContaining(r.getFromAddress());
                if (f != null) { if (fns.add(f)) println("string \""+s.substring(0,Math.min(30,s.length()))
                        +"\" used by "+f.getName()+" @"+f.getEntryPoint()); }
            }
        }
        for (Function f : fns) {
            DecompileResults r = dec.decompileFunction(f, 180, mon);
            String c = (r!=null && r.getDecompiledFunction()!=null)? r.getDecompiledFunction().getC():"// fail";
            FileWriter w = new FileWriter(String.format("%sfwu_%s.c", outdir, f.getEntryPoint()));
            w.write("// "+f.getName()+" @"+f.getEntryPoint()+"\n"+c); w.close();
        }
        println("DONE funcs="+fns.size());
    }
}
