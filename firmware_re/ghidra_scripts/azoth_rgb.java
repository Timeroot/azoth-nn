// RGB backlight recon: dump the Fn light-control path (FUN_0002b8d4), brightness
// (FUN_00032550), and find the LED subsystem - per-key color buffer, the driver
// flush, mode renderers, and coordinate/key->LED tables. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.io.*; import java.util.*;

public class azoth_rgb extends GhidraScript {
    DecompInterface dec; ConsoleTaskMonitor mon=new ConsoleTaskMonitor();
    String outdir="C:\\Users\\Timeroot\\azoth\\firmware_re\\decomp_rgb\\";
    public void run() throws Exception {
        new File(outdir).mkdirs();
        dec=new DecompInterface(); dec.openProgram(currentProgram);
        Set<Function> want=new LinkedHashSet<>();
        // seeds: Fn light control, brightness setter, and their callees (depth 1)
        long[] seeds={0x2b8d4L, 0x32550L};
        for(long s:seeds){ Function f=getFunctionContaining(toAddr(s));
            if(f!=null){ want.add(f); for(Function c:f.getCalledFunctions(mon)) want.add(c); } }
        // scan app region for funcs touching the SECOND SPIM/TWIM base (LED driver) -
        // OLED uses one; the other likely drives the LED matrix IC.
        long[] periph={0x40003000L,0x40004000L,0x40023000L,0x4002b000L,0x40002000L};
        InstructionIterator it=currentProgram.getListing().getInstructions(true);
        Map<Long,Integer> perUse=new HashMap<>();
        while(it.hasNext()){ Instruction ins=it.next(); long a=ins.getAddress().getOffset();
            if(a>=0xd0000L) continue;
            for(int op=0;op<ins.getNumOperands();op++) for(Object o:ins.getOpObjects(op)) if(o instanceof Scalar){
                long v=((Scalar)o).getUnsignedValue();
                for(long p:periph) if(v==p){ Function f=getFunctionContaining(ins.getAddress());
                    if(f!=null){ want.add(f); perUse.merge(p,1,Integer::sum);} }
            }
        }
        for(Map.Entry<Long,Integer> e:perUse.entrySet())
            println("periph 0x"+Long.toHexString(e.getKey())+" used in "+e.getValue()+" insns");
        for(Function f:want){ if(f==null) continue;
            DecompileResults r=dec.decompileFunction(f,120,mon);
            String c=(r!=null&&r.getDecompiledFunction()!=null)?r.getDecompiledFunction().getC():"// fail";
            FileWriter w=new FileWriter(String.format("%srgb_%s.c",outdir,f.getEntryPoint()));
            w.write("// "+f.getName()+" @"+f.getEntryPoint()+" size="+f.getBody().getNumAddresses()+"\n"+c); w.close();
            println("dumped "+f.getEntryPoint()+" size="+f.getBody().getNumAddresses());
        }
        println("DONE "+want.size());
    }
}
