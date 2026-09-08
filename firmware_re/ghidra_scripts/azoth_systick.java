// Decompile the SysTick handler (0x1c4c0) + a couple timer helpers to find a
// free-running ms counter (a global incremented each tick). @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*; import java.util.*;
public class azoth_systick extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec=new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
        String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_tick\\"; new File(outdir).mkdirs();
        long[] a={0x1c4c0L, 0x2cbd0L, 0x402280L};  // systick, delay, timer-set (may be OOB)
        Set<Function> done=new LinkedHashSet<>();
        for(long x:a){ Function f=getFunctionContaining(toAddr(x)); if(f!=null&&done.add(f)){
            for(Function c:f.getCalledFunctions(mon)) done.add(c);
        }}
        for(Function f:done){
            if(f==null) continue;
            DecompileResults r=dec.decompileFunction(f,120,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%sst_%s.c",outdir,f.getEntryPoint())); w.write(c); w.close();
            println("dumped "+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
        }
        println("DONE");
    }
}
