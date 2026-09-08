// Decompile functions that reference the framebuffer 0x2000dd60, plus their callers,
// to find the display tick / flush and the pixel layout. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_fb extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec=new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
        String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_fb\\";
        new File(outdir).mkdirs();
        long[] litoffs={0x247fcL,0x2d4a4L,0x2e660L,0x2e80cL,0x2e9dcL,0x2f234L,0x2f598L,0x2f960L,0x2fb1cL,0x31560L,0x31620L};
        Set<Function> fns=new LinkedHashSet<>();
        for(long lo:litoffs){
            for(Reference r:getReferencesTo(toAddr(lo))){
                Function f=getFunctionContaining(r.getFromAddress());
                if(f!=null) fns.add(f);
            }
        }
        // add callers of each (to find the display tick / main loop)
        Set<Function> callers=new LinkedHashSet<>();
        for(Function f:fns){
            println("FB-fn "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
            for(Reference r:getReferencesTo(f.getEntryPoint())){
                Function c=getFunctionContaining(r.getFromAddress());
                if(c!=null && !fns.contains(c)){ callers.add(c); println("   <- called by "+c.getName()+" @"+c.getEntryPoint()); }
            }
        }
        Set<Function> all=new LinkedHashSet<>(fns); all.addAll(callers);
        for(Function f:all){
            DecompileResults r=dec.decompileFunction(f,150,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%sfb_%s.c",outdir,f.getEntryPoint())); w.write(c); w.close();
        }
        println("DONE dumped="+all.size());
    }
}
