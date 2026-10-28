#!/usr/bin/env python3
"""Retail cross-check for the `devirt` stage (PLAN.md transform 3 "Check",
docs/DEVIRT.md).

For every C++ unit, compare the virtual-call sites of the COMPILED port
object against retail:

  retail  `lw $25,V($r) ; lw $25,S($25) ; jalr|jr $25`        -> (V, S)
          decoded from ../work/SCUS_974.90 and BIN/*.BIN over every
          symbol the unit defines (game/MANIFEST.tsv `symbols`; function
          bounds from the pinned snapshot's symbol tables, through
          tools/census/platform/common.py, read-only)
  port    `movl V(%r),%x ; calll|jmpl *S(%x)`, or `movl S(%x),%y ;
          calll *%y`, in the i686 object (every function the object defines:
          the inline thunks and member bodies are inlined into the unit as
          mwcc inlined them)

Both sides run a small forward must-dataflow over register definitions
(branches, MIPS delay slots and branch-likely, calls clobbering caller-saved
registers), with stack-slot spills tracked, so a vptr load hoisted above a
branch or kept in a spilled register is still found.  V is reported raw and
"normalised" (plus the constant `addiu`/`leal`/`addl` chain that formed the
base pointer); a port site matches a retail site when S is equal and the raw
or normalised V agree.  A port `calll *(%r,%idx)` (clang turned a switch of
virtual calls into a table of slot offsets) is a dynamic-slot site and
covers the retail sites of the same V left after matching.

Status per unit:
  match          equal multisets
  set-match      every site matches, only the COUNT of some (V,S) differs (a
                 call site duplicated or tail-merged by one compiler)
  dyn-slot       matches once clang's switch-to-slot-table sites are counted
  voff-fold      slots agree; some V differs only by how the object address
                 was formed (spill / fold the dataflow could not follow)
  port-fewer / port-more / mismatch    real disagreements (slot or call count)

    python tools/devirt_verify.py [--objdir build/i686-windows] [--only SUBSTR]
           [--fault slot+1|voff+4]   # deliberate-fault control

The fault control perturbs the PORT sites (every slot offset +4, or every V
+4) before comparing; every unit with virtual calls must then fail to match
(`ctest -L devirt`, test devirt.verify_control).

Exit 1 when a unit disagrees (port-fewer/port-more/mismatch) and is not
listed in tests/devirt/expected_mismatch.tsv.
"""
from __future__ import annotations

import argparse
import collections
import os
import re
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(PORT / "tools" / "census" / "platform"))
OBJDUMP = Path(os.environ.get("LLVM_ROOT", "../tools/llvm")) / "bin" / "llvm-objdump.exe"
EXPECTED = PORT / "tests" / "devirt" / "expected_mismatch.tsv"
DYN = -1      # slot offset of a dynamic-slot (table) call


# ------------------------------------------------------------------ dataflow
def dataflow(n: int, succ: list, transfer, full: bool = False):
    """Forward must-analysis.  in[i] = the defs every reached predecessor
    agrees on, recomputed from the predecessors' current outs each pass
    (address order) until nothing changes."""
    preds: list = [[] for _ in range(n)]
    for i, ss in enumerate(succ):
        for j in ss:
            if 0 <= j < n:
                preds[j].append(i)
    ins: list = [None] * n
    outs: list = [None] * n
    for _ in range(60):
        changed = False
        for i in range(n):
            if i == 0:
                new = {}
            else:
                ps = [outs[p] for p in preds[i] if outs[p] is not None]
                if not preds[i]:
                    new = {}           # no static predecessor: a jump-table target
                elif not ps:
                    new = None
                else:
                    new = dict(ps[0])
                    for o in ps[1:]:
                        new = {k: v for k, v in new.items() if o.get(k) == v}
            if new != ins[i]:
                ins[i] = new
                changed = True
            outs[i] = transfer(i, new) if new is not None else None
        if not changed:
            break
    if full:
        return ins, outs, preds
    return ins


def chain_off(d) -> int:
    """Constant offset of a base pointer formed by an add-immediate chain.
    A def is (kind, base, off, base_def)."""
    k = 0
    seen = 0
    while d is not None and d[0] == "add" and seen < 8:
        k += d[2]
        d = d[3]
        seen += 1
    return k


def site(vload, soff) -> tuple:
    """(Vraw, Vnorm, S) from the vptr-load def."""
    return (vload[2], vload[2] + chain_off(vload[3]), soff)


# ------------------------------------------------------------------ retail
CALLER_SAVED = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 31)
NO_GPR_WRITE = {0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17, 0x28, 0x29,
                0x2A, 0x2B, 0x2E, 0x2C, 0x2D, 0x3F, 0x1F, 0x31, 0x39, 0x3D, 0x35, 0x36,
                0x3E, 0x2F, 0x33}
STORES = {0x2B: 4, 0x3F: 8, 0x1F: 16}           # sw, sd, sq
LOADS = {0x23: 4, 0x37: 8, 0x1E: 16}            # lw, ld, lq


def retail_sites(im, f) -> list[tuple]:
    """Sites in [f, next symbol): a multi-entry unit's interior entries
    (`func_<addr>_e1`, ...) have no symbol of their own."""
    o = f.addr - im.base
    import bisect
    bs = getattr(im, "bounds", im.starts)
    k = bisect.bisect_right(bs, f.addr)
    end = bs[k] if k < len(bs) else f.addr + f.size
    n = max(f.size, end - f.addr) // 4
    n = max(0, min(n, (len(im.data) - o) // 4))
    words = [struct.unpack_from("<I", im.data, o + 4 * i)[0] for i in range(n)]
    succ: list = [[i + 1] for i in range(n)]
    call_after = [False] * n
    for i, w in enumerate(words):
        op, rs, rt, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 63
        simm = (w & 0xFFFF) - 0x10000 if w & 0x8000 else w & 0xFFFF
        t = i + 1 + simm
        kind = None
        if op in (4, 5, 6, 7):
            kind = "uncond" if (op == 4 and rs == 0 and rt == 0) else "cond"
        elif op in (0x14, 0x15, 0x16, 0x17):
            kind = "likely"
        elif op == 1 and rt in (0, 1, 0x10, 0x11):
            kind = "cond"
        elif op == 1 and rt in (2, 3, 0x12, 0x13):
            kind = "likely"
        elif op in (0x11, 0x12) and rs == 8:                 # bc1x / bc2x
            kind = "likely" if rt & 2 else "cond"
        elif op == 2:
            kind = "uncond"
            t = (((f.addr + 4 * i + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2))
            t = (t - f.addr) // 4
        elif op == 3 or (op == 0 and fn == 9):               # jal / jalr
            if i + 1 < n:
                call_after[i + 1] = True
            continue
        elif op == 0 and fn == 8:                             # jr
            if i + 1 < n:
                succ[i + 1] = []
            continue
        if kind is None or i + 1 >= n:
            continue
        if kind == "cond":
            succ[i + 1] = [t, i + 2]
        elif kind == "likely":
            succ[i] = [i + 1, i + 2]
            succ[i + 1] = [t]
        else:
            succ[i + 1] = [t]

    def transfer(i, st):
        st = dict(st)
        w = words[i]
        op, rs, rt, rd, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 63
        simm = (w & 0xFFFF) - 0x10000 if w & 0x8000 else w & 0xFFFF
        if op in STORES and rs == 29:
            if st.get(rt) is not None:
                st[("stk", simm)] = st[rt]
            else:
                st.pop(("stk", simm), None)
        elif op in LOADS:
            if rs == 29 and ("stk", simm) in st:
                st[rt] = st[("stk", simm)]
            elif op == 0x23:
                st[rt] = ("lw", rs, simm, st.get(rs))
            elif rt:
                st.pop(rt, None)
        elif op == 0x0F and rt:                               # lui: address constant
            st[rt] = ("k", 0, 0, None)
        elif op in (0x09, 0x19):                              # addiu / daddiu
            if rs == 0 or rt == 29:
                st.pop(rt, None)                              # li / sp adjust
            elif st.get(rs) is not None and st[rs][0] == "k":
                st[rt] = ("k", 0, 0, None)                    # %lo of a symbol address
            else:
                st[rt] = ("add", rs, simm, st.get(rs))
        elif op == 0 and fn in (0x21, 0x2D, 0x25) and (rt == 0 or rs == 0):
            src = rs if rt == 0 else rt
            if rd:
                if src and st.get(src) is not None:
                    st[rd] = st[src]
                else:
                    st.pop(rd, None)
        elif op == 0:
            if fn not in (8, 9, 0x18, 0x19, 0x1A, 0x1B, 0x0C, 0x0D, 0x0F, 0x11, 0x13) and rd:
                st.pop(rd, None)
        elif op in NO_GPR_WRITE:
            pass
        elif op in (0x11, 0x12):
            if rs in (0, 1, 2) and rt:                        # mfc1/cfc1, qmfc2/cfc2
                st.pop(rt, None)
        elif op == 0x1C:
            if rd:
                st.pop(rd, None)
        elif rt:
            st.pop(rt, None)
        if call_after[i]:
            for r in CALLER_SAVED:
                st.pop(r, None)
        return st

    ins = dataflow(n, succ, transfer)
    out = []
    for i, w in enumerate(words):
        if (w >> 26) == 0 and (w & 63) in (8, 9) and ((w >> 21) & 31) == 25 and ins[i] is not None:
            d = ins[i].get(25)
            if d and d[0] == "lw" and d[1] == 25 and d[3] and d[3][0] == "lw":
                out.append(site(d[3], d[2]))
            elif d and d[0] == "lw" and d[3] and d[3][0] == "k":
                out.append((None, None, d[2]))                # vptr known: lw $25,S(&D_vtbl)
    return out


LISTINGS = {"main": "asm/main.s", "title": "asm/overlays/title/title.s",
            "insmenu": "asm/overlays/insmenu/insmenu.s", "normal": "asm/overlays/normal/normal.s",
            "factory": "asm/overlays/factory/factory.s", "insect": "asm/overlays/insect/insect.s"}
GLABEL = re.compile(r"^glabel\s+(\S+)\s*\n\s*/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s", re.M)


def load_retail():
    """Images + function boundaries.  A unit's retail range is [symbol, next
    boundary), where boundaries are the symbol table AND every `glabel` of the
    snapshot's retail listings (read from git at the pinned commit), so a
    multi-entry unit's interior entries are scanned and nothing beyond it."""
    import pickle
    import common as C   # tools/census/platform/common.py (read-only)
    facts, imgs, edges, files = C.cached()
    cache = PORT / "out" / "devirt_glabels.pkl"
    bounds = None
    if cache.exists():
        d = pickle.load(open(cache, "rb"))
        if d.get("pin") == C.PIN:
            bounds = d["bounds"]
    if bounds is None:
        bounds = {}
        for img, rel in LISTINGS.items():
            r = subprocess.run(["git", "-C", C.SOURCE, "show", f"{C.PIN}:{rel}"],
                               capture_output=True, text=True, encoding="utf-8", errors="replace")
            bounds[img] = sorted({int(m.group(2), 16) for m in GLABEL.finditer(r.stdout)})
        cache.parent.mkdir(parents=True, exist_ok=True)
        pickle.dump({"pin": C.PIN, "bounds": bounds}, open(cache, "wb"))
    for img, im in imgs.items():
        im.bounds = sorted(set(im.starts) | set(bounds.get(img, [])))
    return imgs


# ------------------------------------------------------------------ port
FUNC = re.compile(r"^([0-9a-f]+) <(.+)>:$")
INSN = re.compile(r"^\s*([0-9a-f]+):\s+(\S+)\s*(.*?)\s*$")
MEM = re.compile(r"^(-?0x[0-9a-f]+|-?\d+)?\((%\w+)?(?:,(%\w+)(?:,(\d))?)?\)$")
R32 = {"al": "eax", "ah": "eax", "ax": "eax", "bl": "ebx", "bh": "ebx", "bx": "ebx",
       "cl": "ecx", "ch": "ecx", "cx": "ecx", "dl": "edx", "dh": "edx", "dx": "edx",
       "si": "esi", "di": "edi", "bp": "ebp", "sil": "esi", "dil": "edi"}
NOWRITE = ("cmp", "test", "push", "call", "jmp", "j", "ret", "nop", "ud2", "int3",
           "ucomis", "comis")


def reg(s: str) -> str | None:
    if not s.startswith("%"):
        return None
    r = s[1:]
    if r.startswith("e") and len(r) == 3:
        return r
    return R32.get(r, r)


def split_ops(s: str) -> list[str]:
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def num(s: str | None) -> int:
    if not s:
        return 0
    return int(s, 16) if "0x" in s else int(s)


def x86_transfer(ins_, relocs=frozenset()):
    def transfer(i, st):
        st = dict(st)
        esp = st.get("esp_d", 0)
        mn, ops = ins_[i][1], ins_[i][2]

        def stk(mm):                                  # stack-slot key of a (%esp) operand
            if mm and mm.group(2) == "%esp" and not mm.group(3):
                return ("stk", esp + num(mm.group(1)))
            return None
        if mn.startswith("call"):
            for r in ("eax", "ecx", "edx"):
                st.pop(r, None)
            return st
        if mn.startswith("push"):
            esp -= 4
            st["esp_d"] = esp
            if ops and reg(ops[0]) and st.get(reg(ops[0])) is not None:
                st[("stk", esp)] = st[reg(ops[0])]
            else:
                st.pop(("stk", esp), None)
            return st
        if mn.startswith("pop"):
            if ops and reg(ops[0]):
                r = reg(ops[0])
                if st.get(("stk", esp)) is not None:
                    st[r] = st[("stk", esp)]
                else:
                    st.pop(r, None)
            st["esp_d"] = esp + 4
            return st
        if mn in ("addl", "subl") and len(ops) == 2 and ops[0].startswith("$") and reg(ops[1]):
            dst = reg(ops[1])
            k = num(ops[0][1:]) * (1 if mn == "addl" else -1)
            if dst == "esp":
                st["esp_d"] = esp + k
            else:
                st[dst] = ("add", dst, k, st.get(dst))
            return st
        if mn == "movl" and len(ops) == 2:
            dst = reg(ops[1])
            mm_src = MEM.match(ops[0])
            if dst is None:                            # store
                key = stk(MEM.match(ops[1]))
                if key is not None:
                    src = reg(ops[0])
                    if src and st.get(src) is not None:
                        st[key] = st[src]
                    else:
                        st.pop(key, None)
                return st
            if mm_src:
                key = stk(mm_src)
                if key is not None and st.get(key) is not None:
                    st[dst] = st[key]
                    return st
                b = reg(mm_src.group(2)) if mm_src.group(2) else None
                st[dst] = ("ld", b, num(mm_src.group(1)), st.get(b) if b else None)
                return st
            if mm_src and mm_src.group(3) and i in relocs:   # table[idx] in .rdata
                st[dst] = ("tbl", 4, num(mm_src.group(1)), None)
                return st
            if re.fullmatch(r"-?0x[0-9a-f]+", ops[0]):   # load from a global (reloc'd absolute)
                st[dst] = ("ld", None, num(ops[0]), None)
                return st
            if ops[0].startswith("$") and i in relocs:     # $D_vtbl + k: a known vtable address
                st[dst] = ("vt", None, num(ops[0][1:]), None)
                return st
            if ops[0].startswith("$"):                     # constant (a selected slot offset)
                st[dst] = ("imm", None, num(ops[0][1:]), None)
                return st
            src = reg(ops[0])
            if src and st.get(src) is not None:
                st[dst] = st[src]
            else:
                st.pop(dst, None)
            return st
        if mn in ("movzwl", "movzbl", "movswl", "movsbl") and len(ops) == 2 and reg(ops[1]):
            mm = MEM.match(ops[0])
            if mm and mm.group(3) and i in relocs:          # switch -> slot-offset lookup table
                st[reg(ops[1])] = ("tbl", 2 if "w" in mn[4:] else 1, num(mm.group(1)), None)
            else:
                st.pop(reg(ops[1]), None)
            return st
        if mn == "leal" and len(ops) == 2:
            dst = reg(ops[1])
            mm = MEM.match(ops[0])
            if mm and mm.group(2) and not mm.group(3):
                b = reg(mm.group(2))
                st[dst] = ("add", b, num(mm.group(1)), st.get(b))
            elif mm and mm.group(2) and mm.group(3):   # base+index: keep the base chain
                b = reg(mm.group(2))
                st[dst] = ("add", b, num(mm.group(1)), None)
            else:
                st.pop(dst, None)
            return st
        if mn in ("cltd", "cdq", "mull", "divl", "idivl", "divw", "idivw", "divb", "idivb") or \
                (mn in ("imull", "imulw") and len(ops) == 1):
            st.pop("eax", None)
            st.pop("edx", None)
            return st
        if mn.startswith(NOWRITE):
            return st
        if ops:
            r = reg(ops[-1])
            if r:
                st.pop(r, None)
            if mn.startswith("xchg") and len(ops) == 2 and reg(ops[0]):
                st.pop(reg(ops[0]), None)
        return st
    return transfer


def port_sites(objdump_text: str) -> dict[str, list[tuple]]:
    funcs: list[tuple[str, list]] = []
    reloc_at: dict[str, set] = {}
    for ln in objdump_text.splitlines():
        m = FUNC.match(ln)
        if m:
            funcs.append((m.group(2), []))
            reloc_at[m.group(2)] = set()
            continue
        if "IMAGE_REL_I386_DIR32" in ln and funcs and funcs[-1][1]:
            reloc_at[funcs[-1][0]].add(len(funcs[-1][1]) - 1)
            continue
        if "IMAGE_REL_" in ln:
            continue
        m = INSN.match(ln)
        if not m or not funcs:
            continue
        addr, mn, ops_s = int(m.group(1), 16), m.group(2), m.group(3)
        ops_s = re.sub(r"\s*#.*$", "", ops_s)
        tgt = None
        tm = re.match(r"^(0x[0-9a-f]+)\s*<", ops_s)
        if tm:
            tgt = int(tm.group(1), 16)
        ops_s = re.sub(r"\s*<.*>$", "", ops_s)
        funcs[-1][1].append((addr, mn, split_ops(ops_s), tgt))
    res: dict[str, list] = {}
    rdata = rdata_sections(objdump_text)
    for name, ins_ in funcs:
        relocs = reloc_at.get(name, set())
        n = len(ins_)
        at = {a: k for k, (a, _, _, _) in enumerate(ins_)}
        succ = []
        for k, (a, mn, ops, tgt) in enumerate(ins_):
            if mn.startswith("ret") or (mn.startswith("jmp") and ops and ops[0].startswith("*")) \
                    or mn in ("ud2", "int3"):
                succ.append([])
            elif mn.startswith("jmp"):
                succ.append([at[tgt]] if tgt in at else [])
            elif mn.startswith("j"):
                succ.append([k + 1] + ([at[tgt]] if tgt in at else []))
            else:
                succ.append([k + 1])
        ins, outs, preds = dataflow(n, succ, x86_transfer(ins_, relocs), full=True)

        def writes(p, r):
            ops = ins_[p][2]
            return bool(ops) and reg(ops[-1]) == r

        def defs_at(r, k, depth=0):
            """Definitions of register r reaching k, one per predecessor path
            when the paths disagree (clang tail-merged several virtual calls
            into one `call` with the slot address computed per path)."""
            d = ins[k].get(r) if ins[k] is not None else None
            if d is not None or depth > 8:
                return [d]
            res_ = []
            for p in preds[k]:
                od = outs[p].get(r) if outs[p] is not None else None
                if od is not None:
                    res_.append(od)
                elif writes(p, r):
                    res_.append(None)
                else:
                    res_ += defs_at(r, p, depth + 1)
            return res_ or [None]

        def slot_site(d, disp, dyn):
            """d = def of the register the slot is loaded through."""
            k_ = 0
            while d is not None and d[0] == "add":   # vptr + k (per-path slot select)
                k_ += d[2]
                d = d[3]
            if d is not None and d[0] == "ld":
                return site(d, DYN if dyn else disp + k_)
            if d is not None and d[0] == "vt" and not dyn:
                return (None, None, d[2] + disp + k_)     # store-forwarded vptr
            return None
        sites = []
        for k, (a, mn, ops, tgt) in enumerate(ins_):
            if mn in ("calll", "jmpl") and ops and ops[0].startswith("*") and ins[k] is not None:
                t = ops[0][1:]
                mm = MEM.match(t)
                if mm and mm.group(2):                       # call *S(%x[,%i])
                    tbl = None
                    if mm.group(3):
                        td = defs_at(reg(mm.group(3)), k)
                        vals = []
                        for x in td:                       # per path: a table or a constant
                            if x is not None and x[0] == "tbl":
                                e = decode_table(x, ins_, k, rdata)
                            elif x is not None and x[0] == "imm":
                                e = [x[2]]
                            else:
                                e = None
                            if e is None:
                                vals = None
                                break
                            vals += e
                        tbl = sorted(set(vals)) if vals else None
                    for d in defs_at(reg(mm.group(2)), k):
                        if tbl:
                            for e in tbl:
                                s_ = slot_site(d, num(mm.group(1)) + e, False)
                                if s_:
                                    sites.append(s_)
                            continue
                        s_ = slot_site(d, num(mm.group(1)), bool(mm.group(3)))
                        if s_:
                            sites.append(s_)
                elif re.fullmatch(r"0x[0-9a-f]+", t) and k in relocs:
                    sites.append((None, None, num(t)))       # vptr store-forwarded: *(D_vtbl + S)
                elif not mm:                                 # call *%y, y = S(x), x = V(r)
                    for d in defs_at(reg(t), k):
                        if d and d[0] == "ld" and d[3] and d[3][0] == "ld":
                            sites.append(site(d[3], d[2]))
        res[name] = sites
    return res


def decode_table(td, ins_, k, rdata):
    """Entries of a switch lookup table of slot offsets: bound from the
    nearest preceding `cmpl $N, %reg` (N+1 entries); the .rdata section is the
    one whose entries at that offset are all plausible slot offsets."""
    width, off = td[1], td[2]
    n = None
    for j in range(k - 1, max(-1, k - 40), -1):
        mn, ops = ins_[j][1], ins_[j][2]
        if mn == "cmpl" and ops and ops[0].startswith("$"):
            n = num(ops[0][1:]) + 1
            break
    if not n or n > 256:
        return None
    for sec in rdata:
        if len(sec) < off + n * width:
            continue
        vals = [int.from_bytes(sec[off + i * width: off + (i + 1) * width], "little")
                for i in range(n) if off + i * width >= 0]
        if all(v >= 8 and v % 4 == 0 and v < 0x8000 for v in vals):
            return vals
    return None


def rdata_sections(text: str) -> list[bytes]:
    secs: list[bytearray] = []
    for ln in text.splitlines():
        if ln.startswith("Contents of section .rdata"):
            secs.append(bytearray())
            continue
        m = re.match(r"^ ([0-9a-f]{4,}) ((?:[0-9a-f]{2,8} ?){1,4})", ln)
        if m and secs:
            secs[-1] += bytes.fromhex(m.group(2).replace(" ", ""))
    return [bytes(s) for s in secs]


def objdump(path: Path) -> str:
    r = subprocess.run([str(OBJDUMP), "-d", "-r", "--no-show-raw-insn", str(path)],
                       capture_output=True, text=True, encoding="utf-8", errors="replace")
    out = r.stdout
    if "calll\t*(" in out or "jmpl\t*(" in out:
        r2 = subprocess.run([str(OBJDUMP), "-s", "-j", ".rdata", str(path)],
                            capture_output=True, text=True, encoding="utf-8", errors="replace")
        out += "\n" + r2.stdout
    return out


# ------------------------------------------------------------------ compare
def compare(retail: list, port: list) -> tuple[str, list, list]:
    """Greedy site matching.  Returns (status, retail_left, port_left)."""
    R = list(retail)
    P = [p for p in port if p[2] != DYN]
    dyn = [p for p in port if p[2] == DYN]

    def vmatch(a, b):
        if a[0] is None or b[0] is None:              # known-vtable call: any V
            return True
        return bool({a[0], a[1]} & {b[0], b[1]})
    # three passes, strictest first: raw V equal, normalised V equal, any
    tests = [lambda r, p: r[0] == p[0], lambda r, p: r[1] == p[1], vmatch]
    Pleft = P
    for tst in tests:
        nxt = []
        for p in Pleft:
            k = next((i for i, r in enumerate(R) if r[2] == p[2] and tst(r, p)), None)
            if k is None:
                nxt.append(p)
            else:
                R.pop(k)
        Pleft = nxt
    if not R and not Pleft and not dyn:
        return ("match" if len(retail) == len(port) else "set-match"), [], []

    def known(x, pool):
        return any(x[2] == y[2] and vmatch(x, y) for y in pool)
    if dyn:
        R = [r for r in R if not any(vmatch(r, d) for d in dyn)]
        if not R and not Pleft:
            return "dyn-slot", R, Pleft
    if R and Pleft and collections.Counter(r[2] for r in R) == collections.Counter(p[2] for p in Pleft):
        return "voff-fold", R, Pleft                # same slots, V formed differently
    Rc = [r for r in R if not known(r, P)]          # count-only leftovers are fine
    Pc = [p for p in Pleft if not known(p, retail)]
    if not Rc and not Pc:
        return ("dyn-slot" if dyn else "set-match"), R, Pleft
    rs = collections.Counter(r[2] for r in Rc)
    ps = collections.Counter(p[2] for p in Pc)
    if rs == ps:
        return "voff-fold", R, Pleft
    if not Pc:
        return "port-fewer", R, Pleft
    if not Rc:
        return "port-more", R, Pleft
    return "mismatch", R, Pleft


def fmt(sites: list) -> str:
    c = collections.Counter((s[0], s[2]) for s in sites)
    parts = []
    for (v, s), n in sorted(c.items(), key=lambda x: (x[0][0] is None, x[0][0] or 0, x[0][1])):
        ss = "*" if s == DYN else f"{s:X}"
        vs = "vt" if v is None else f"{v:X}"
        parts.append(f"{vs}:{ss}" + (f"x{n}" if n > 1 else ""))
    return " ".join(parts) or "-"


def manifest(game: Path):
    rows = []
    for ln in (game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]:
        f = ln.split("\t")
        rows.append((f[0], f[2], f[3], [s for s in f[4].split(",") if s and s != "-"]))
    return rows


def obj_path(objdir: Path, image: str, rel: str) -> Path:
    if (objdir / "CMakeFiles").is_dir():
        d = objdir / "CMakeFiles" / f"rg_game_{image}.dir"
        if (PORT / "overrides" / rel).exists():          # an override replaces the unit
            return d / "overrides" / (rel + ".obj")
        return d / "game" / (rel + ".obj")
    return objdir / (rel + ".obj")


OK = ("match", "set-match", "dyn-slot", "voff-fold", "none")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--game", type=Path, default=PORT / "game")
    ap.add_argument("--objdir", type=Path, default=PORT / "build" / "i686-windows")
    ap.add_argument("--out", type=Path)
    ap.add_argument("--only", default="")
    ap.add_argument("--fault", choices=["slot+1", "voff+4"], default=None)
    ap.add_argument("--jobs", type=int, default=12)
    ap.add_argument("--devirt", type=Path, help="DEVIRT.tsv (default <game>/DEVIRT.tsv)")
    ap.add_argument("--tolerate", action="append", default=[],
                    help="a status that does not fail the run (reported as tolerated): the "
                         "game objects at RG_GAME_OPT=-O2 inline and unroll, which adds call "
                         "sites (`port-more`, docs/UB-AUDIT.md); never used by the controls")
    a = ap.parse_args()
    out = a.out or (a.objdir / ("devirt_verify" + (f"_fault_{a.fault.replace('+', '')}" if a.fault else "") + ".tsv"))

    rows = [r for r in manifest(a.game) if r[2] == "unit" and r[0].endswith(".cpp") and a.only in r[0]]
    try:
        imgs = load_retail()
    except (OSError, SystemExit) as e:          # no retail binaries / snapshot repo
        print(f"devirt_verify: SKIP, retail images unavailable ({e})")
        return 77
    # files whose de-virtualised classes emit at least one thunk (game/DEVIRT.tsv);
    # in any other C++ file an indirect call is a plain C function pointer
    # (retail `jalr $2/$3`), not a virtual call, and is not compared
    thunk_files: set[str] = set()
    dv = a.devirt or (a.game / "DEVIRT.tsv")
    for ln in dv.read_text(encoding="utf-8").splitlines()[2:]:
        f = ln.split("\t")
        if len(f) > 10 and f[10] == "1":
            thunk_files.add(f[0])
    # units whose virtual tail jumps the protos stage turned into naked
    # forwarders (`def-vthunk-naked`: `movl V(%eax),%eax; jmp *S(%eax)`) keep
    # their virtual call sites without any devirt thunk
    pt = a.game / "PROTOS.tsv"
    if pt.exists():
        for ln in pt.read_text(encoding="utf-8", errors="replace").splitlines():
            f = ln.split("\t")
            if len(f) > 3 and f[3] == "def-vthunk-naked":
                thunk_files.add(f[0])
    hdrs = {p.rsplit("/", 1)[1] for p in thunk_files if p.startswith("include/")}
    if hdrs:      # a unit that includes a de-virtualised header uses its thunks
        rx = re.compile(r'#\s*include\s*"(?:[^"]*/)?(' + "|".join(map(re.escape, sorted(hdrs))) + r')"')
        for r in rows:
            src = a.game / r[0]
            if src.exists() and rx.search(src.read_text(encoding="utf-8", errors="replace")):
                thunk_files.add(r[0])

    def work(r):
        rel, image, kind, syms = r
        op = obj_path(a.objdir, image, rel)
        if not op.exists():
            return rel, image, syms, None
        return rel, image, syms, port_sites(objdump(op))
    with ThreadPoolExecutor(a.jobs) as ex:
        results = list(ex.map(work, rows))
    if not any(r[3] is not None for r in results):
        print(f"devirt_verify: SKIP, no game objects under {a.objdir} (build rg_game_objs)")
        return 77

    expected = {}
    if EXPECTED.exists():
        for ln in EXPECTED.read_text(encoding="utf-8").splitlines():
            if ln.strip() and not ln.startswith("#"):
                f = ln.split("\t")
                expected[f[0]] = f[1] if len(f) > 1 else ""
    tally = collections.Counter()
    ctl_n = ctl_caught = 0
    nsites_r = nsites_p = 0
    lines = ["file\timage\tstatus\tretail\tport\tretail_left\tport_left\tnote"]
    bad = []
    for rel, image, syms, ours in results:
        im = imgs.get(image)
        rsites = []
        missing = []
        for s in syms:
            f = im.by_name.get(s) if im else None
            if f is None:
                missing.append(s)
                continue
            rsites += retail_sites(im, f)
        if ours is None:
            status, rl, pl, psites = "no-object", [], [], []
        else:
            psites = [x for v in ours.values() for x in v]
            if rel not in thunk_files:
                psites = []
            if a.fault == "slot+1":
                psites = [(v, w, s + 4 if s != DYN else s) for v, w, s in psites]
            elif a.fault == "voff+4":
                psites = [(None, None, s) if v is None else (v + 4, w + 4, s)
                          for v, w, s in psites]
            if not rsites and not psites:
                status, rl, pl = "none", [], []
            else:
                status, rl, pl = compare(rsites, psites)
        nsites_r += len(rsites)
        nsites_p += len(psites)
        tally[status] += 1
        if psites:
            ctl_n += 1
            strict = ("match", "set-match", "dyn-slot") if a.fault == "voff+4" else OK
            if all(x[2] == DYN for x in psites) or (a.fault == "voff+4" and (
                    all(x[0] is None for x in psites) or all(x[0] is None for x in rsites))):
                ctl_n -= 1      # only runtime-slot / known-vtable sites: not perturbable
            elif status not in strict:
                ctl_caught += 1
        note = ("missing:" + ",".join(missing)) if missing else ""
        if status not in OK and status != "no-object":
            if status in a.tolerate and not a.fault:
                note = (note + " tolerated:" + status).strip()
                tally["(tolerated: " + status + ")"] += 1
            elif rel in expected:
                note = (note + " expected:" + expected[rel]).strip()
                tally["(listed in expected_mismatch.tsv)"] += 1
            else:
                bad.append(rel)
        lines.append("\t".join([rel, image, status, fmt(rsites), fmt(psites), fmt(rl), fmt(pl),
                                note or "-"]))
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(lines) + "\n", encoding="utf-8")
    with_calls = sum(v for k, v in tally.items() if k in OK[:-1] or k in ("port-fewer", "port-more", "mismatch"))
    good = sum(tally[k] for k in OK[:-1])
    print(f"devirt_verify{' FAULT ' + a.fault if a.fault else ''}: {len(results)} C++ units, "
          f"{with_calls} with virtual calls ({nsites_r} retail sites, {nsites_p} port sites); "
          + ", ".join(f"{k}={v}" for k, v in sorted(tally.items())))
    if with_calls:
        print(f"agreement: {good}/{with_calls} = {100.0 * good / with_calls:.2f}% "
              f"(exact multiset {tally['match']})")
    print(f"wrote {out}")
    if a.fault:
        armed = ctl_n > 0 and ctl_caught == ctl_n
        print(f"control: {ctl_caught}/{ctl_n} units with port sites caught -> "
              + ("ARMED" if armed else "NOT ARMED"))
        return 0 if armed else 1
    if bad:
        print(f"{len(bad)} unexpected disagreements, e.g. {bad[:5]}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
