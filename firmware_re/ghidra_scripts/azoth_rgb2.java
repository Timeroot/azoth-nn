// Find all functions referencing the LED state struct (0x20003200) and related RAM,
// plus the key-edge LED path, to locate the effect renderer + hardware flush. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*; import java.util.*;

public class azoth_rgb2 extends GhidraScript {
    public void run() throws Exception {
        DecompInterface dec=new DecompInterface(); dec.openProgram(currentProgram);
        ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
        String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_rgb\\"; new File(outdir).mkdirs();
        long[] targets={0x20003200L, 0x2000415cL, 0x2000be48L};
        Set<Function> fns=new LinkedHashSet<>();
        // scan all defined data words in text for these literals, follow refs to containing fn
        Listing lst=currentProgram.getListing();
        DataIterator di=lst.getDefinedData(true);
        for(Data dt: (Iterable<Data>)()->lst.getDefinedData(true)){
            Object v=dt.getValue(); if(!(v instanceof ghidra.program.model.scalar.Scalar)) continue;
            long val=((ghidra.program.model.scalar.Scalar)v).getUnsignedValue();
            boolean hit=false; for(long t:targets) if(val==t) hit=true;
            if(!hit) continue;
            for(Reference r:getReferencesTo(dt.getAddress())){
                Function f=getFunctionContaining(r.getFromAddress());
                if(f!=null && fns.add(f)) println("ref 0x"+Long.toHexString(val)+" <- "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
            }
        }
        // also seed known LED path fns
        for(long s:new long[]{0x30f3cL,0x271c0L,0x30ac0L}){
            Function f=getFunctionContaining(toAddr(s)); if(f!=null) fns.add(f);
        }
        for(Function f:fns){
            DecompileResults r=dec.decompileFunction(f,150,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%sr2_%s.c",outdir,f.getEntryPoint()));
            w.write("// "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses()+"\n"+c); w.close();
        }
        println("DONE "+fns.size());
    }
}
