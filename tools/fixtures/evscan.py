#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Find which SB2 scripts (.stb: event / map / NPC scripts) call given native commands.

    python tools/fixtures/evscan.py find ID[,ID..] [--glob RX]      # files + entry points calling them
    python tools/fixtures/evscan.py dis FILE [MEMBER] [--around ID]  # disassemble one script
    python tools/fixtures/evscan.py natives                          # id -> handler (event command table)

SB2 format (ScriptVmInit_176af0, ScriptVmRunEntry_176940, ScriptVmExec_173b00):
header "SB2\0", +0x04 default entry offset, +0x08 code offset, +0x0C label table offset
({s32 id, s32 entry offset} pairs), +0x10 label count; code = 12-byte {op, a, b}
records; a native call is `PUSHIMM 1, ID` (op 3) + the arguments + `NATIVE argc+1` (op 21),
ID = the event command number of the table at D_0044D6F0 ({handler, id} pairs; e.g.
1574 EvCmdMenuInsectEntryOpen_25c3f0, 1587 EvCmdInvCountInsects_25c280, 1553 state var set).
Handler names come from game/src/main_data/data2c_0044D6F0.c.
Scripts are found in archive files ending .stb and in .pac members ending .stb.
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gamedata  # noqa: E402

PORT = Path(__file__).resolve().parents[2]
OPS = {1: "PUSHVAR", 2: "PUSHREF", 3: "PUSHIMM", 4: "DROP", 5: "STORE", 6: "ADD", 7: "SUB", 8: "MUL",
       9: "DIV", 10: "MOD", 11: "INVT", 12: "ITOF", 13: "FTOI", 14: "CMP", 15: "RET", 16: "JMP",
       17: "AND", 18: "OR", 19: "CALL", 20: "TRACE", 21: "NATIVE", 22: "LABEL", 23: "YIELD", 24: "BITAND",
       25: "BITOR", 26: "NOT", 27: "STOP", 28: "WAIT", 29: "SIN", 30: "COS"}
CMP = {0x28: "==", 0x29: "!=", 0x2A: "<", 0x2B: "<=", 0x2C: ">", 0x2D: ">="}


def natives():
    t = (PORT / "game/src/main_data/data2c_0044D6F0.c").read_text()
    return {int(i, 16): n for n, i in re.findall(r"\(u32\)&(\w+), 0x([0-9A-F]+)u", t)}


def scripts(glob=None):
    """Yield (archive name, member or None, bytes) for every SB2 script."""
    a = gamedata.Archive()
    rx = re.compile(glob, re.I) if glob else None
    for name in sorted(a.files):
        low = name.lower()
        if rx and not rx.search(name):
            continue
        if low.endswith(".stb"):
            b = a.get(name)
            if b[:3] == b"SB2":
                yield name, None, b
        elif low.endswith(".pac"):
            b = a.get(name)
            for nm, off, size in gamedata.pac_members(b):
                if nm.lower().endswith(".stb") and b[off:off + 3] == b"SB2":
                    yield name, nm, b[off:off + size]


def header(b):
    dflt, code, labels, nlab = struct.unpack_from("<iiii", b, 4)
    labs = [struct.unpack_from("<ii", b, labels + 8 * i) for i in range(nlab)]
    return dflt, code, labs


def instrs(b):
    _, code, _ = header(b)
    for off in range(0, len(b) - code - 11, 4):
        yield off, struct.unpack_from("<iii", b, code + off)


def native_sites(b, ids):
    _, code, _ = header(b)
    out = []
    for i in ids:
        pat = struct.pack("<iii", 3, 1, i)
        p = b.find(pat, code)
        while p >= 0:
            if (p - code) % 4 == 0:
                out.append((i, p - code))
            p = b.find(pat, p + 4)
    return out


def cmd_find(a):
    ids = [int(x, 0) for x in a.ids.split(",")]
    nat = natives()
    n = 0
    for name, mem, b in scripts(a.glob):
        s = native_sites(b, ids)
        if s:
            n += 1
            print(f"{name}{' :: ' + mem if mem else ''}: " + ", ".join(f"{nat.get(i, i)}@{o:#x}" for i, o in s))
    print(f"evscan: {n} scripts")
    return 0


def dis(b, nat, lo=0, hi=None):
    _, code, labs = header(b)
    end = len(b) - code
    hi = end if hi is None else min(hi, end)
    off = lo
    while off + 12 <= hi:
        op, x, y = struct.unpack_from("<iii", b, code + off)
        nm = OPS.get(op)
        if nm is None:
            print(f"  {off:#07x}  .word    {op:#x} {x:#x} {y:#x}")
            off += 12
            continue
        if op == 3 and x == 1:
            arg = f"int {y}" + (f"   ; {nat[y]}" if y in nat else "")
        elif op == 3 and x == 2:
            arg = f"float {struct.unpack('<f', struct.pack('<i', y))[0]:g}"
        elif op == 3 and x == 3:
            arg = f"code {y:#x}"
        elif op == 14:
            arg = CMP.get(x, hex(x))
        elif op in (16, 17, 18):
            arg = f"-> {x:#x}"
        elif op in (1, 2, 5):
            arg = f"slot {x} mode {y:#x}"
        else:
            arg = f"{x} {y}"
        print(f"  {off:#07x}  {nm:8s} {arg}")
        off += 12


def entries(b):
    """{code offset of the routine: (entry offset (code-relative), name or '', slots, args, label ids)}:
    every routine the label table or a CALL names (Entry = {code, name, slots, args})."""
    _, code, labs = header(b)
    ents = {}
    for lid, off in labs:
        ents.setdefault(off - code, []).append(lid)
    for off, (op, x, y) in instrs(b):
        if op == 19 and 0 <= y < len(b) - code:
            ents.setdefault(y, [])
    out = {}
    for e, lids in ents.items():
        if e + 16 > len(b) - code:
            continue
        c, nm, slots, args = struct.unpack_from("<iiii", b, code + e)
        out[c] = (e, slots, args, lids)
    return out


def routine_of(b, site):
    starts = sorted(entries(b))
    best = None
    for c in starts:
        if c <= site:
            best = c
    nxt = [c for c in starts if c > site]
    return best, (nxt[0] if nxt else None)


def callers(b, entry_off):
    return [off for off, (op, x, y) in instrs(b) if op == 19 and y == entry_off]


def cmd_dis(a):
    nat = natives()
    for name, mem, b in scripts(re.escape(a.file)):
        if a.member and (mem or "").lower() != a.member.lower():
            continue
        dflt, code, labs = header(b)
        print(f"== {name} {mem or ''}: default entry {dflt:#x}, code {code:#x}, {len(labs)} labels")
        if a.around and a.func:
            ents = entries(b)
            for i, o in native_sites(b, [int(a.around, 0)]):
                st, en = routine_of(b, o)
                e, slots, args, lids = ents[st]
                print(f"-- site {o:#x} in routine code {st:#x} (entry {e:#x}, {args} args / {slots} slots, "
                      f"labels {lids}, called from {[hex(c) for c in callers(b, e)]})")
                dis(b, nat, st, en)
        elif a.at:
            st = int(a.at, 0)
            ents = entries(b)
            en = min([c for c in ents if c > st] or [None]) if ents else None
            e = ents.get(st)
            if e:
                print(f"-- routine {st:#x} (entry {e[0]:#x}, {e[2]} args / {e[1]} slots, labels {e[3]}, "
                      f"called from {[hex(c) for c in callers(b, e[0])]})")
            dis(b, nat, st, en)
        elif a.around:
            for i, o in native_sites(b, [int(a.around, 0)]):
                print(f"-- site {o:#x}")
                dis(b, nat, max(0, o - a.before * 12), o + a.after * 12)
        else:
            dis(b, nat)
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    f = sp.add_parser("find")
    f.add_argument("ids")
    f.add_argument("--glob")
    f.set_defaults(fn=cmd_find)
    d = sp.add_parser("dis")
    d.add_argument("file")
    d.add_argument("member", nargs="?")
    d.add_argument("--around")
    d.add_argument("--before", type=int, default=40)
    d.add_argument("--after", type=int, default=40)
    d.add_argument("--func", action="store_true", help="with --around: the whole routine holding each site")
    d.add_argument("--at", help="disassemble the routine starting at this code offset")
    d.set_defaults(fn=cmd_dis)
    n = sp.add_parser("natives")
    n.set_defaults(fn=lambda a: [print(k, v) for k, v in sorted(natives().items())] and 0)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
