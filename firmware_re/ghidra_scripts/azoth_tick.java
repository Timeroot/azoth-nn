// Trace callers of the display tick FUN_0002e518 up to the main loop, and dump the
// flush FUN_00031658 + init, to find a periodic animation hook. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_tick extends GhidraScript {
    DecompInterface dec; ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
    String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_tick\\";
    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec=new DecompInterface(); dec.openProgram(currentProgram);
        Set<Function> want=new LinkedHashSet<>();
        // walk callers up to 3 levels from the display tick
        long[] seeds={0x2e518L, 0x31658L, 0x314e4L};
        Set<Long> visited=new HashSet<>();
        Deque<long[]> q=new ArrayDeque<>();
        for(long s:seeds) q.add(new long[]{s,0});
        while(!q.isEmpty()){
            long[] cur=q.poll(); Function f=getFunctionContaining(toAddr(cur[0]));
            if(f==null) continue; long ep=f.getEntryPoint().getOffset();
            if(!visited.add(ep)) continue; want.add(f);
            println("L"+cur[1]+" "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
            if(cur[1]<3){
                for(Reference r:getReferencesTo(f.getEntryPoint())){
                    Function c=getFunctionContaining(r.getFromAddress());
                    if(c!=null){ println("     <- "+c.getName()+" @"+c.getEntryPoint()); q.add(new long[]{c.getEntryPoint().getOffset(),cur[1]+1}); }
                }
            }
        }
        for(Function f:want){
            DecompileResults r=dec.decompileFunction(f,150,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%stk_%s.c",outdir,f.getEntryPoint())); w.write(c); w.close();
        }
        println("DONE "+want.size());
    }
}
