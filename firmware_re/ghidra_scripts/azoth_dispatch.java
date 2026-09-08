// Find the OLED HID command dispatcher: the function(s) that compare an incoming
// byte against the most distinct OLED command opcodes. @category Azoth
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.app.decompiler.*;
import ghidra.util.task.ConsoleTaskMonitor;
import java.util.*;

public class azoth_dispatch extends GhidraScript {
    public void run() throws Exception {
        Set<Long> cmds = new HashSet<>(Arrays.asList(
            0x61L,0x62L,0x63L,0x64L,0x66L,0x67L,0x12L,0x22L,0x50L,0x7dL));
        Map<Function, Set<Long>> hits = new HashMap<>();
        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        while (it.hasNext()) {
            Instruction insn = it.next();
            String m = insn.getMnemonicString().toLowerCase();
            if (!(m.startsWith("cmp") || m.startsWith("sub"))) continue;
            for (int oi = 0; oi < insn.getNumOperands(); oi++) {
                Scalar s = insn.getScalar(oi);
                if (s != null && cmds.contains(s.getUnsignedValue())) {
                    Function f = getFunctionContaining(insn.getAddress());
                    if (f != null) hits.computeIfAbsent(f, k -> new TreeSet<>()).add(s.getUnsignedValue());
                }
            }
        }
        List<Function> ranked = new ArrayList<>(hits.keySet());
        ranked.sort((a, b) -> Integer.compare(hits.get(b).size(), hits.get(a).size()));
        println("=== functions comparing OLED cmd bytes (ranked by #distinct) ===");
        for (int i = 0; i < Math.min(15, ranked.size()); i++) {
            Function f = ranked.get(i);
            List<String> hex = new ArrayList<>();
            for (Long v : hits.get(f)) hex.add(String.format("%02x", v));
            println(String.format("  0x%06x  %2d distinct [%s]  %s",
                f.getEntryPoint().getOffset(), hits.get(f).size(), String.join(",", hex), f.getName()));
        }
        if (!ranked.isEmpty()) {
            DecompInterface dec = new DecompInterface(); dec.openProgram(currentProgram);
            for (int i = 0; i < Math.min(2, ranked.size()); i++) {
                Function f = ranked.get(i);
                DecompileResults r = dec.decompileFunction(f, 120, new ConsoleTaskMonitor());
                println("\n==== DISPATCHER#" + i + " " + f.getName() + " @0x"
                    + Long.toHexString(f.getEntryPoint().getOffset()) + " ====");
                if (r != null && r.getDecompiledFunction() != null) println(r.getDecompiledFunction().getC());
            }
        }
    }
}
