// Decompile the LED transfer FUN_000319a0 + callees (the hardware push), and the
// remaining LED composers, to recover the framebuffer + driver protocol. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*; import java.util.*;
public class azoth_ledflush extends GhidraScript {
    DecompInterface dec; ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
    String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_rgb\\";
    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec=new DecompInterface(); dec.openProgram(currentProgram);
        Set<Function> done=new LinkedHashSet<>();
        long[] seeds={0x319a0L,0x27430L,0x30958L,0x2aa10L,0x30f3cL,0x30ac0L,0x31798L};
        for(long s:seeds){ Function f=getFunctionContaining(toAddr(s));
            if(f!=null&&done.add(f)){ for(Function c:f.getCalledFunctions(mon)) done.add(c); } }
        for(Function f:done){ if(f==null) continue;
            DecompileResults r=dec.decompileFunction(f,150,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%slf_%s.c",outdir,f.getEntryPoint()));
            w.write("// "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses()+"\n"+c); w.close();
            println("dumped "+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
        }
        println("DONE "+done.size());
    }
}
