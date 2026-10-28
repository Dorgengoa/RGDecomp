"""Find jal sites to given EE targets in the retail ELF and recover $a0/$a1 constants (own code, CC0).
usage: eecalls.py TARGET_HEX [TARGET_HEX...]"""
import struct, sys
from eeread import b, segs
def sx(v): return v - 0x10000 if v & 0x8000 else v
tg = [int(x, 16) for x in sys.argv[1:]]
for ty, off, va, pa, fsz, msz, fl, al in segs:
    if ty != 1 or not (fl & 1): continue
    n = fsz // 4
    ws = struct.unpack_from(f"<{n}I", b, off)
    for i, w in enumerate(ws):
        if w >> 26 == 3 and ((w & 0x3FFFFFF) << 2) in tg:
            regs = {}
            for k in list(range(max(0, i - 10), i)) + [i + 1]:
                x = ws[k]; op, rs, rt = x >> 26, (x >> 21) & 31, (x >> 16) & 31
                if op in (2, 3) and k != i + 1: regs = {}; continue
                if op in (9, 0x19) and rs == 0: regs[rt] = sx(x & 0xFFFF)
                elif op == 13 and rs == 0: regs[rt] = x & 0xFFFF
                elif op == 0 and (x & 63) in (0x21, 0x25, 0x2d): regs.pop((x >> 11) & 31, None)
                elif op in (0x23, 0x20, 0x24, 0x21, 0x25, 0x37, 9, 13, 15): regs.pop(rt, None)
            print(f"{va+4*i:08x} -> {((w&0x3FFFFFF)<<2):x}  a0={regs.get(4)} a1={regs.get(5)} a2={regs.get(6)}")
