// Find the OLED panel-flush: app-region funcs referencing SPIM/TWIM peripheral bases
// or TXD.PTR offsets, plus the 0x32xxx OLED driver cluster + callees. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*;
import java.util.*;

public class azoth_oled extends GhidraScript {
    DecompInterface dec; ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
    String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_oled\\";
    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec=new DecompInterface(); dec.openProgram(currentProgram);
        Set<Function> fns=new LinkedHashSet<>();
        // peripheral bases: SPIM0..3 / TWIM0..1
        long[] periph={0x40003000L,0x40004000L,0x40023000L,0x4002b000L};
        InstructionIterator it=currentProgram.getListing().getInstructions(true);
        while(it.hasNext()){
            Instruction ins=it.next(); long a=ins.getAddress().getOffset();
            if(a<0x1c000L||a>=0x4e000L) continue;
            for(int op=0;op<ins.getNumOperands();op++) for(Object o:ins.getOpObjects(op)) if(o instanceof Scalar){
                long v=((Scalar)o).getUnsignedValue();
                for(long p:periph) if(v==p){ Function f=getFunctionContaining(ins.getAddress()); if(f!=null) fns.add(f); }
            }
        }
        println("app funcs touching SPIM/TWIM bases: "+fns.size());
        // also seed the OLED driver cluster
        for(long s:new long[]{0x32550L,0x32598L,0x32910L,0x32598L,0x2d170L}){
            Function f=getFunctionContaining(toAddr(s)); if(f!=null) fns.add(f);
        }
        // dump each + immediate callees
        Set<Function> all=new LinkedHashSet<>(fns);
        for(Function f:fns) for(Function c:f.getCalledFunctions(mon)){ long a=c.getEntryPoint().getOffset(); if(a>=0x1c000&&a<0x4e000) all.add(c); }
        for(Function f:all){
            DecompileResults r=dec.decompileFunction(f,120,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%sol_%s.c",outdir,f.getEntryPoint()));
            w.write("// "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses()+"\n"+c); w.close();
            println("  dumped "+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
        }
        println("DONE total="+all.size());
    }
}
