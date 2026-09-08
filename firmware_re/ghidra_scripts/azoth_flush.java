// Decompile the full OLED refresh sequence: setup(311fc), flush(31658->cec0),
// finalize(312ec/2a034), + command prims + the state machine 2e5e4. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*; import java.util.*;
public class azoth_flush extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec=new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
        String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_flush\\"; new File(outdir).mkdirs();
        long[] a={0x2e5e4L,0x311fcL,0x312ecL,0x2a034L,0x31658L,0x2cec0L,0x31468L,
                  0x3de84L,0x3dc00L,0x3ca98L,0x311b0L,0x31590L,0x31624L};
        Set<Function> done=new LinkedHashSet<>();
        for(long x:a){ Function f=getFunctionContaining(toAddr(x)); if(f!=null&&done.add(f)){
            DecompileResults r=dec.decompileFunction(f,120,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%sfl_%s.c",outdir,f.getEntryPoint())); w.write(c); w.close();
            println("dumped "+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
        }}
        println("DONE");
    }
}
