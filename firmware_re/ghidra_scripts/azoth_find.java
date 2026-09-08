// Find OLED handler functions via distinctive constants (framebuffer size 6656,
// meta 1000, NAK 0xaa, dims 208). @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.util.*;

public class azoth_find extends GhidraScript {
    public void run() throws Exception {
        long[] consts = {0x1a00, 0x3e8, 0xaa, 0xd0, 0x2000, 0x67};   // 6656,1000,NAK,208,8192,cmd
        Map<Long, Map<Function, Integer>> byConst = new HashMap<>();
        for (long c : consts) byConst.put(c, new HashMap<>());
        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        while (it.hasNext()) {
            Instruction insn = it.next();
            for (int oi = 0; oi < insn.getNumOperands(); oi++) {
                Scalar s = insn.getScalar(oi);
                if (s == null) continue;
                long v = s.getUnsignedValue();
                if (byConst.containsKey(v)) {
                    Function f = getFunctionContaining(insn.getAddress());
                    if (f != null) byConst.get(v).merge(f, 1, Integer::sum);
                }
            }
        }
        for (long c : consts) {
            println(String.format("\n=== functions using constant 0x%x (%d) ===", c, c));
            List<Map.Entry<Function,Integer>> es = new ArrayList<>(byConst.get(c).entrySet());
            es.sort((a,b)->b.getValue()-a.getValue());
            for (int i=0;i<Math.min(10,es.size());i++)
                println(String.format("  0x%06x  x%d  %s", es.get(i).getKey().getEntryPoint().getOffset(),
                        es.get(i).getValue(), es.get(i).getKey().getName()));
        }
    }
}
