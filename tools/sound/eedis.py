"""Tiny EE (R5900) linear disassembler on top of rdis.dis (own code, CC0).
usage: eedis.py START_HEX END_HEX"""
import struct, sys
from rdis import dis, R, sx
from eeread import rd
EXTRA_OP = {0x14: "beql", 0x15: "bnel", 0x16: "blezl", 0x17: "bgtzl", 0x37: "ld", 0x3f: "sd", 0x1e: "lq", 0x1f: "sq",
            0x18: "daddi", 0x19: "daddiu", 0x31: "lwc1", 0x39: "swc1", 0x27: "lwu"}
EXTRA_FN = {0x2d: "daddu", 0x2f: "dsubu", 0x14: "dsllv", 0x38: "dsll", 0x3a: "dsrl", 0x3b: "dsra", 0x3c: "dsll32",
            0x3e: "dsrl32", 0x3f: "dsra32", 0x0f: "sync", 0x0a: "movz", 0x0b: "movn"}
a, e = int(sys.argv[1], 16), int(sys.argv[2], 16)
d = rd(a, e - a)
for i in range(0, e - a, 4):
    w, pc = struct.unpack_from("<I", d, i)[0], a + i
    op, rs, rt, rd_, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 63
    if op in EXTRA_OP:
        n = EXTRA_OP[op]
        if op in (0x14, 0x15, 0x16, 0x17):
            s = f"{n} {R[rs]},{R[rt]},{(pc+4+(sx(w&0xFFFF)<<2)):x}"
        elif op in (0x18, 0x19):
            s = f"{n} {R[rt]},{R[rs]},{sx(w&0xFFFF)}"
        else:
            s = f"{n} {'$f%d'%rt if op in (0x31,0x39) else R[rt]},{sx(w&0xFFFF)}({R[rs]})"
    elif op == 0 and fn in EXTRA_FN:
        s = f"{EXTRA_FN[fn]} {R[rd_]},{R[rs]},{R[rt]}" + (f",{(w>>6)&31}" if fn >= 0x38 else "")
    else:
        s, _ = dis(w, pc)
    print(f"{pc:08x}: {w:08x}  {s}")
