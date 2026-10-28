"""Retail-listing dataflow for the protos stage (docs/PROTOS-MISSING-ARGS.md).

Reads spimdisasm listings (asm/main.s split at `glabel`, per-function
asm/matchings files, asm/overlays/<ov>/<ov>.s) and answers two questions about
a call site whose C call is missing an argument:

  * caller side -- what does the argument register hold when the `jal` (or tail
    `j`) transfers control?  `value(cfg, j, reg)` -> a symbolic Term: the
    function's incoming value, a dead caller-saved register left by an earlier
    call, an earlier call's $v0, a constant, a symbol's address or contents,
    a load from an incoming pointer, a stack address, ...
  * callee side -- does the callee read the register before writing it?
    `Flow.reads(fn, reg)` -> 'yes:..' / 'maybe:..' / 'unknown:..' / 'no'
    (forward liveness from entry; follows `jal`s and tail `j`s into the
    target's listing; a `jalr` is "unknown"; a store to $sp that is never
    reloaded by offset is a varargs/RPC save area: "maybe").

Branch delay slots, branch-likely annulment and the caller-saved clobber of a
call are modelled.  The liveness is path-insensitive: it can only over-report
reads.  Pure functions of the listing text; no port state.
"""
from __future__ import annotations

import re
from dataclasses import dataclass

# ------------------------------------------------------------------ listing
_INSN = re.compile(r"\s*/\*\s*\w+\s+([0-9A-Fa-f]{8})\s+\w+\s*\*/\s+(\S+)\s*(.*)$")
_LABEL = re.compile(r"\s*(\.L[0-9A-Fa-f_]+|\w+):\s*$")


def parse_listing(text: str):
    """-> (insns [(op, [operands])] with ('.label', [name]) pseudo entries,
    vram of the first instruction or None)."""
    out, addr = [], None
    for ln in text.splitlines():
        m = _INSN.match(ln)
        if m:
            if addr is None:
                addr = int(m.group(1), 16)
            rest = m.group(3).split("#")[0].strip()
            ops = [x.strip() for x in split_ops(rest)] if rest else []
            out.append((m.group(2), ops))
            continue
        m = _LABEL.match(ln)
        if m:
            out.append((".label", [m.group(1)]))
    return out, addr


def split_ops(s: str):
    out, d, a = [], 0, 0
    for i, ch in enumerate(s):
        if ch == "(":
            d += 1
        elif ch == ")":
            d -= 1
        elif ch == "," and d == 0:
            out.append(s[a:i])
            a = i + 1
    out.append(s[a:])
    return out


def regs_in(s: str):
    return re.findall(r"\$(?:f\d+|\d+)\b", s)


STORE = re.compile(r"^(s[bhwdq]|swl|swr|sdl|sdr|swc1|sdc1|sqc2|sq)$")
BR = re.compile(r"^(b\w*|j|jr|jal|jalr)$")
NODEST1 = re.compile(r"^(b\w*|j|jr|jalr|jal|mt(c1|c0|hi|lo|hi1|lo1|sa)|ctc\w*|qmtc2|div\w*|"
                     r"t(eq|ne|ge|lt)\w*|pmthi|pmtlo|cache|pref|sync\w*|c\.\w+|\.word|nop|"
                     r"break|syscall|lqc2|sqc2|vi?\w*|mtsab|mtsah)$")
CALLS = ("jal", "bal", "bgezal", "bltzal", "bgezall", "bltzall")


def uses_defs(op, ops):
    """(uses, defs) register sets ('$n' GPR, '$fn' FPR) of one instruction
    (a call's own effect is modelled by the CFG, not here)."""
    if op in (".label", "nop", ".word"):
        return set(), set()
    allr = [regs_in(o) for o in ops]
    flat = [r for rs in allr for r in rs]
    if op in CALLS:
        return set(), set()
    if op == "jalr":
        return set(flat[-1:]), set()
    if op in ("mtc1", "qmtc2", "ctc2", "ctc1", "mtc0", "mtsab", "mtsah"):
        return (set(allr[0]) if allr else set(),
                set(allr[1]) if len(allr) > 1 and op == "mtc1" else set())
    if op in ("mfc1", "qmfc2", "cfc2", "cfc1", "mfc0"):
        return set(), set(allr[0]) if allr else set()
    if op.startswith(("lqc2", "sqc2")) or (op.startswith("v") and op not in ("vsub",)):
        return {r for r in flat if not r.startswith("$vf")}, set()
    if STORE.match(op):
        return set(flat), set()
    if op.startswith(("mult", "madd", "msub", "div")) and len(ops) == 2:
        return set(flat), set()
    if op.startswith("c.") or BR.match(op):
        return set(flat), set()
    if NODEST1.match(op):
        return set(flat), set()
    if not allr or not allr[0]:
        return set(flat), set()
    d = set(allr[0])
    u = {r for rs in allr[1:] for r in rs}
    if op in ("movn", "movz", "movn.s", "movz.s"):
        u |= d                      # conditional move keeps the old value
    if op.startswith(("madd", "msub")) and op.endswith(".s"):
        u |= d
    return u, d


CALLER_SAVED = ({"$%d" % i for i in list(range(1, 16)) + [24, 25, 31]}
                | {"$f%d" % i for i in range(0, 20)})
ARGREGS = ["$%d" % i for i in range(4, 12)] + ["$f%d" % i for i in range(12, 20)]


def arg_reg(cls: str, k: int) -> str:
    return ("$%d" % (4 + k)) if cls == "g" else ("$f%d" % (12 + k))


class CFG:
    """Instruction-level control flow of one listing.  succ/pred over
    instruction indices; `callafter[ds]` = the callee whose clobber takes
    effect after delay slot ds; `tail[ds]` = a tail jump's target."""

    def __init__(self, lst):
        self.ins, lab = [], {}
        self.jal_at = []                       # listing index of each insn
        for op, ops in lst:
            if op == ".label":
                lab[ops[0]] = len(self.ins)
            else:
                self.ins.append((op, ops))
        n = len(self.ins)
        self.succ = [[] for _ in range(n)]
        self.callafter, self.tail = {}, {}
        likely_ds = set()
        for i, (op, ops) in enumerate(self.ins):
            if i in likely_ds:
                continue
            if BR.match(op) and op != "break":
                ds = i + 1
                if ds >= n:
                    continue
                tgt = lab.get(ops[-1]) if ops else None
                if op in CALLS:
                    self.succ[i] = [ds]
                    self.succ[ds] = [i + 2] if i + 2 < n else []
                    self.callafter[ds] = ops[-1] if ops else "?"
                elif op == "jalr":
                    self.succ[i] = [ds]
                    self.succ[ds] = [i + 2] if i + 2 < n else []
                    self.callafter[ds] = "<indirect>"
                elif op == "jr":
                    self.succ[i] = [ds]
                    self.succ[ds] = []
                    if ops and ops[0] != "$31":
                        self.tail[ds] = "<indirect>"
                elif op in ("j", "b") or (op == "beq" and len(ops) > 1 and ops[0] == ops[1]):
                    self.succ[i] = [ds]
                    if tgt is not None:
                        self.succ[ds] = [tgt]
                    else:
                        self.succ[ds] = []
                        self.tail[ds] = ops[-1] if ops else "?"
                elif op.endswith("l"):
                    self.succ[i] = [ds] + ([i + 2] if i + 2 < n else [])
                    self.succ[ds] = [tgt] if tgt is not None else []
                    likely_ds.add(ds)
                else:
                    self.succ[i] = [ds]
                    self.succ[ds] = (([tgt] if tgt is not None else [])
                                     + ([i + 2] if i + 2 < n else []))
            elif not self.succ[i] and (i == 0 or not (BR.match(self.ins[i - 1][0])
                                                      and self.ins[i - 1][0] != "break")):
                self.succ[i] = [i + 1] if i + 1 < n else []
        # label positions, and `jr $r` switch dispatches through a jump table
        # (a %lo(jtbl_..) within the 12 instructions before): the delay slot
        # index -> True.  The CFG keeps them as indirect tails; Flow.extent
        # follows them to every label (the cases are among them).
        self.labels = sorted(set(lab.values()))
        self.switch = set()
        for i, (op, ops) in enumerate(self.ins):
            if op == "jr" and ops and ops[0] != "$31" and (i + 1) in self.tail and any(
                    "%lo(jtbl_" in " ".join(o) for _p, o in self.ins[max(0, i - 12):i]):
                self.switch.add(i + 1)
        self.pred = [[] for _ in range(n)]
        for i, ss in enumerate(self.succ):
            for s in ss:
                if s < n:
                    self.pred[s].append(i)
        # case entries: labels and instructions nothing else reaches (a jtbl
        # target needs no label in the listing)
        self.cases = sorted(set(self.labels) | {k for k in range(1, n) if not self.pred[k]})

    def calls(self):
        """[(insn index, op, target)] of every jal and tail `j` (not jalr)."""
        out = []
        for i, (op, ops) in enumerate(self.ins):
            if op in ("jal",) and ops:
                out.append((i, op, ops[-1]))
            elif op == "j" and ops and (i + 1) in self.tail:
                out.append((i, op, ops[-1]))
        return out

    def _def(self, i, reg):
        op, ops = self.ins[i]
        _u, d = uses_defs(op, ops)
        if i in self.callafter and reg in CALLER_SAVED:
            return ("call", i - 1, self.callafter[i])
        if reg in d:
            return ("insn", i)
        return None

    def reaching(self, i, reg, before=True):
        todo = list(self.pred[i]) if before else [i]
        if before and i == 0:
            todo.append(-1)
        seen, out = set(), set()
        while todo:
            k = todo.pop()
            if k == -1:
                out.add(("entry",))
                continue
            if k in seen:
                continue
            seen.add(k)
            dd = self._def(k, reg)
            if dd:
                out.add(dd)
                continue
            todo.extend(self.pred[k])
            if k == 0:
                out.add(("entry",))
        return out


# ------------------------------------------------------------------ terms
@dataclass(frozen=True)
class Term:
    """Symbolic register value.  kind:
      entry(reg)        the function's incoming value
      clobber(callee)   a dead caller-saved register after a call
      ret(j, callee)    $v0 of the call at insn j
      const(v)          an integer constant
      hi(v)             lui result (v already shifted)
      addr(v)           an absolute address (lui/addiu pair, or $gp+off)
      sym(name, off)    a relocated symbol's address (+off)
      load(op, base, off)  a load from base+off (base a Term)
      add(base, k)      base + k
      sp(off)           a stack address ($sp+off at that point)
      phi(terms)        several reaching definitions
      other(text)       anything else"""
    kind: str
    a: object = None
    b: object = None
    c: object = None

    def __str__(self):
        k = self.kind
        if k == "entry":
            return f"ENTRY({self.a})"
        if k == "clobber":
            return f"CLOBBER({self.a})"
        if k == "ret":
            return f"RET({self.b})"
        if k == "const":
            return hex(self.a) if abs(self.a) > 9 else str(self.a)
        if k in ("hi", "addr"):
            return f"{k}({self.a:#x})"
        if k == "sym":
            return f"&{self.a}" + (f"{self.b:+#x}" if self.b else "")
        if k == "load":
            return f"{self.a}[{self.b}{self.c:+#x}]"
        if k == "add":
            return f"{self.a}{self.b:+#x}"
        if k == "sp":
            return f"sp{self.a:+#x}"
        if k == "gp":
            return "gp"
        if k == "gpaddr":
            return f"gp{self.a:+#x}"
        if k == "phi":
            return "{" + " | ".join(sorted(str(t) for t in self.a)) + "}"
        return f"?{self.a}"


def _sext16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def _imm(s: str):
    """An immediate operand: 0x10, -0x4EB0, (0x4B2570 & 0xFFFF), (0xFFFFFFF0 >> 16)."""
    s = s.strip()
    m = re.fullmatch(r"\(\s*(-?0x[0-9A-Fa-f]+|-?\d+)\s*&\s*0xFFFF\s*\)", s)
    if m:
        return ("lo16", int(m.group(1), 0) & 0xFFFF)
    m = re.fullmatch(r"\(\s*(-?0x[0-9A-Fa-f]+|-?\d+)\s*>>\s*16\s*\)", s)
    if m:
        return ("int", (int(m.group(1), 0) >> 16) & 0xFFFF)
    try:
        return ("int", int(s, 0))
    except ValueError:
        return None


def value(cfg: CFG, i: int, reg: str, depth: int = 0, before: bool = True) -> Term:
    """Symbolic value of reg at instruction i (before it executes)."""
    if reg == "$0":
        return Term("const", 0)
    if depth > 8:
        return Term("other", "depth")
    vals = set()
    for d in cfg.reaching(i, reg, before):
        if d[0] == "entry":
            if reg in ARGREGS:
                vals.add(Term("entry", reg))
            elif reg == "$29":
                vals.add(Term("sp", 0))
            elif reg == "$28":
                vals.add(Term("gp"))
            else:
                vals.add(Term("other", "entry " + reg))
        elif d[0] == "call":
            if reg in ("$2", "$f0") and cfg.ins[d[1]][0] in CALLS:
                vals.add(Term("ret", d[1], d[2]))
            elif reg in ("$2", "$f0"):
                vals.add(Term("other", "ret of jalr"))
            else:
                vals.add(Term("clobber", d[2]))
        else:
            vals.add(_expr(cfg, d[1], depth))
    if len(vals) == 1:
        return next(iter(vals))
    return Term("phi", frozenset(vals))


def _expr(cfg, k, depth) -> Term:
    op, ops = cfg.ins[k]
    src = lambda r: value(cfg, k, r, depth + 1)
    if op in ("move", "addu", "daddu", "or", "dmove") and (
            len(ops) == 2 or (len(ops) == 3 and ops[2] == "$0")):
        return src(ops[1])
    if op in ("addu", "daddu", "or") and len(ops) == 3 and ops[1] == "$0":
        return src(ops[2])
    if op in ("addu", "daddu", "subu", "dsubu") and len(ops) == 3:
        # a frame larger than 32 KB: `lui $1, hi; ori $1, $1, lo; addu $29, $29, $1`
        # (CameraFollowLeaderStepMaybe_3081e0, sp-0x6xxx): sp plus a 32-bit constant
        # stays a stack address (entry-relative, like the addiu form)
        x, y = src(ops[1]), src(ops[2])
        if op in ("addu", "daddu") and y.kind == "sp" and x.kind != "sp":
            x, y = y, x
        if x.kind == "sp" and y.kind in ("const", "hi", "addr"):
            v = y.a & 0xFFFFFFFF
            v = v - (1 << 32) if v & 0x80000000 else v
            return Term("sp", x.a + (v if op in ("addu", "daddu") else -v))
    if op in ("addiu", "daddiu", "ori", "addi", "daddi") and len(ops) == 3:
        m = re.fullmatch(r"%lo\((\w+)\)", ops[2])
        if m:
            b = src(ops[1])
            if b.kind == "hi" and b.b == m.group(1):
                return Term("sym", m.group(1), 0)
            return Term("other", f"{op} {','.join(ops)}")
        m = re.fullmatch(r"%gp_rel\((\w+)\)", ops[2])
        if m:
            return Term("sym", m.group(1), 0)
        im = _imm(ops[2])
        if im is None:
            return Term("other", f"{op} {','.join(ops)}")
        b = src(ops[1])
        if op == "ori":
            v = im[1] & 0xFFFF
            if b.kind == "const":
                return Term("const", b.a | v)
            if b.kind == "hi":
                return Term("addr", b.a | v)
            return Term("other", f"ori {b}")
        v = _sext16(im[1]) if im[0] == "lo16" else im[1]
        if b.kind == "const":
            return Term("const", b.a + v)
        if b.kind == "hi":
            return Term("addr", (b.a + v) & 0xFFFFFFFF)
        if b.kind == "sp":
            return Term("sp", b.a + v)
        if b.kind == "gp":
            return Term("gpaddr", v)
        if b.kind == "sym":
            return Term("sym", b.a, b.b + v)
        if b.kind == "addr":
            return Term("addr", (b.a + v) & 0xFFFFFFFF)
        if b.kind == "add":
            return Term("add", b.a, b.b + v) if b.b + v else b.a
        return Term("add", b, v) if v else b
    if op == "lui":
        m = re.fullmatch(r"%hi\((\w+)\)", ops[1])
        if m:
            return Term("hi", 0, m.group(1))
        im = _imm(ops[1])
        if im is not None:
            return Term("hi", (im[1] & 0xFFFF) << 16)
        return Term("other", "lui " + ops[1])
    if op in ("lw", "ld", "lh", "lhu", "lb", "lbu", "lwc1", "lq", "lwu"):
        m = re.fullmatch(r"(.*)\((\$\w+)\)", ops[1])
        if m:
            off, base = m.group(1).strip(), m.group(2)
            g = re.fullmatch(r"%(?:gp_rel|lo)\((\w+)\)", off)
            if g:
                return Term("load", op, Term("sym", g.group(1), 0), 0)
            im = _imm(off) if off else ("int", 0)
            if im is None:
                return Term("other", f"{op} {ops[1]}")
            v = _sext16(im[1]) if im[0] == "lo16" else im[1]
            b = src(base)
            if b.kind == "gp":
                return Term("load", op, Term("gpaddr", v), 0)
            if b.kind == "hi":
                return Term("load", op, Term("addr", (b.a + v) & 0xFFFFFFFF), 0)
            if b.kind == "sp":
                return Term("load", op, Term("sp", b.a + v), 0)
            return Term("load", op, b, v)
    if op == "mtc1":
        return Term("other", f"bits({src(ops[0])})")
    if op == "mov.s":
        return src(ops[1])
    if op in ("sll", "dsll") and len(ops) == 3 and ops[2] == "0":
        return src(ops[1])
    return Term("other", f"{op} {','.join(ops)}")


def value_at_call(cfg: CFG, j: int, reg: str) -> Term:
    """reg's value when the call/jump at insn j transfers control (its delay
    slot included)."""
    ds = j + 1
    if ds < len(cfg.ins):
        dop, dops = cfg.ins[ds]
        if reg in uses_defs(dop, dops)[1]:
            return _expr(cfg, ds, 0)
    return value(cfg, j, reg)


def has_clobber(t: Term) -> bool:
    if t.kind == "clobber":
        return True
    if t.kind == "phi":
        return any(has_clobber(x) for x in t.a)
    return False


# ------------------------------------------------------------------ liveness
class Flow:
    """Callee-side liveness over a set of listings.  listing(name) -> insns
    or None; resolve(target, from_name) -> listing name of a jal/j target."""

    def __init__(self, listing, resolve):
        self.listing = listing
        self.resolve = resolve
        self._cfg: dict = {}
        self._live: dict = {}

    def cfg(self, name):
        if name not in self._cfg:
            lst = self.listing(name)
            self._cfg[name] = CFG(lst) if lst else None
        return self._cfg[name]

    def reads(self, fn, reg, depth=0, seen=None):
        """Does fn read reg's incoming value on some path?"""
        key = (fn, reg)
        if key in self._live:
            return self._live[key]
        seen = (seen or frozenset()) | {fn}
        cfg = self.cfg(fn)
        if cfg is None:
            return "unknown:no listing for " + fn
        n = len(cfg.ins)
        todo, vis, reasons = [0], set(), []
        while todo:
            i = todo.pop()
            if i in vis or i >= n:
                continue
            vis.add(i)
            op, ops = cfg.ins[i]
            u, d = uses_defs(op, ops)
            if reg in u:
                m = (re.fullmatch(r"(-?\w+)\(\$29\)", ops[-1])
                     if STORE.match(op) and ops and ops[0] == reg else None)
                if m:
                    off = m.group(1)
                    rel = [x for x in cfg.ins if not STORE.match(x[0]) and x[1]
                           and x[1][-1] == off + "($29)"]
                    if rel:
                        reasons.append(f"yes:spill {op} {','.join(ops)} reloaded")
                        break
                    # the slot's address is taken (fptodp: `swc1 $f12,0x10($sp)`,
                    # `addiu $4,$sp,0x10`, jal UnpackF): read through a pointer
                    esc = [x for x in cfg.ins if x[0] in ("addiu", "daddiu") and len(x[1]) == 3
                           and x[1][1] == "$29" and x[1][2] == off]
                    if esc:
                        reasons.append(f"yes:{op} {','.join(ops)}; the slot's address escapes")
                        break
                    reasons.append(f"maybe:stored to {off}($sp), never reloaded by offset")
                    continue
                reasons.append(f"yes:{op} {','.join(ops)} @{i}")
                break
            if i in cfg.callafter:
                tgt = cfg.callafter[i]
                if reg in d:
                    continue
                if reg in ARGREGS:
                    r = self._sub(tgt, reg, depth, seen, fn)
                    if r.startswith("yes"):
                        reasons.append(f"yes:passed to {tgt} ({r})")
                        break
                    if r.startswith(("unknown", "maybe")):
                        reasons.append(f"maybe:via {tgt} ({r})")
                if reg in CALLER_SAVED:
                    continue
            if i in cfg.tail:
                if reg not in d:
                    r = self._sub(cfg.tail[i], reg, depth, seen, fn)
                    if r.startswith("yes"):
                        reasons.append(f"yes:tail to {cfg.tail[i]} ({r})")
                        break
                    if r.startswith(("unknown", "maybe")):
                        reasons.append(f"maybe:via {cfg.tail[i]} ({r})")
                continue
            if reg in d:
                continue
            todo.extend(cfg.succ[i])
        yes = [r for r in reasons if r.startswith("yes")]
        unk = [r for r in reasons if r.startswith(("unknown", "maybe"))]
        res = yes[0] if yes else (unk[0] if unk else "no")
        self._live[key] = res
        return res

    WIDTH = {"lb": 1, "lbu": 1, "sb": 1, "lh": 2, "lhu": 2, "sh": 2, "lw": 4, "lwu": 4,
             "sw": 4, "lwc1": 4, "swc1": 4, "ld": 8, "sd": 8, "ldc1": 8, "sdc1": 8, "lq": 16,
             "sq": 16, "lqc2": 16, "sqc2": 16, "lwl": 4, "lwr": 4, "swl": 4, "swr": 4,
             "ldl": 8, "ldr": 8, "sdl": 8, "sdr": 8}

    # Callees whose reach through a pointer is set by another argument, not by
    # their code: an unrolled word loop (memcpy, Md5Update -> Md5Transform)
    # would otherwise report its unroll width.  {name: {lane: length lane}}.
    LEN_ARG = {"memcpy": {0: 2, 1: 2}, "memmove": {0: 2, 1: 2}, "memset": {0: 2},
               "memcmp": {0: 2, 1: 2}, "memchr": {0: 2}, "strncpy": {0: 2},
               "strncmp": {0: 2, 1: 2}, "Strncasecmp_134ce8": {0: 2, 1: 2},
               "Md5Update_369280": {1: 2}}
    # NUL-terminated string arguments: the reach is the string's, assumed to
    # stay inside the C object (C semantics); kind `str`, not an escape.
    STR_ARG = {"strlen": (0,), "strcmp": (0, 1), "strcpy": (0, 1), "strcat": (0, 1),
               "strncpy": (1,), "Strchr_1347c0": (0,), "Strstr_135138": (0, 1),
               "Strcasecmp_1345b8": (0, 1), "Index_1308f0": (0,), "Strupr_136390": (0,),
               "atoi": (0,), "Atof_12dee8": (0,), "Strtol_136360": (0,),
               "Strtod_1360d8": (0,), "Strtof_136100": (0,), "Sprintf_1343b8": (0, 1),
               "SprintfR_134330": (1, 2)}
    max_depth = 4

    def _lane_rule(self, fn, reg, kargs):
        """(E, complete, escapes) for a LEN_ARG / STR_ARG lane, else None."""
        nm = fn.split(":", 1)[-1]
        k = int(reg[1:]) - 4 if reg[1:].isdigit() else -1
        if k in self.LEN_ARG.get(nm, {}):
            lr = "$%d" % (4 + self.LEN_ARG[nm][k])
            v = (kargs or {}).get(lr)
            if v is not None:
                return (max(v, 0), True, [])
            return (0, False, [{"fn": fn, "kind": "lenvar", "reg": reg, "c": 0, "tgt": nm,
                                "src": None}])
        if k in self.STR_ARG.get(nm, ()):
            return (0, True, [{"fn": fn, "kind": "str", "reg": reg, "c": 0, "tgt": nm,
                               "src": None}])
        return None

    def extent(self, fn, reg, depth=0, seen=None, kargs=None):
        """(E, complete) -- the end offset of the memory fn reaches through its
        incoming pointer in reg: max(c + off + width) over the loads/stores
        whose base holds ENTRY(reg) + c, following `jal`s and tail `j`s that are
        passed ENTRY(reg) + c (depth max_depth).  complete is False when the
        pointer escapes to a `jalr`, a callee with no listing, or deeper calls.

        A forward must-dataflow over the CFG: each register is either unknown
        or exactly ENTRY(reg) + c (moves and addiu propagate it; any other
        write, and a call's clobber of the caller-saved registers, kill it;
        joins keep only facts that agree).  Also tracked: small constants
        (the length argument of LEN_ARG callees), values stored to memory and
        loaded back from the same base + offset (sp slots survive calls), and
        the null tests of the pointer (a stack address is never 0, so the
        `beqz ptr` edge is not taken: IterInit_370170 stores the container
        only when it is non-null).  kargs = {reg: constant} of the call.

        Why an extent is incomplete is kept in `self.escapes(fn, reg)`: dicts
        {fn, kind (jalr | nolisting | depth | lenvar), reg, c, tgt, src} where
        for a jalr `src` is ('fld', X) -- the function pointer was loaded from
        ENTRY(reg) + X (a callback stored in the object) -- or ('vt', V, S) --
        slot offset S of the vtable loaded from ENTRY(reg) + V (a virtual
        method of the object) -- or None (any other pointer).  Kind `str`
        rows (a STR_ARG callee) are assumptions, not escapes.  The read and
        write ends are `self.rw_extent(fn, reg)`."""
        lr = self._lane_rule(fn, reg, kargs)
        if lr is not None:
            return lr[:2]
        key = ("ext", fn, reg)
        if key in self._live:
            return self._live[key]
        esc = []
        self._live[("esc", fn, reg)] = esc
        seen = (seen or frozenset()) | {fn}
        # "img:name@OFF": an interior entry OFF bytes into name's listing
        fbase, _at, eoff = fn.partition("@")
        cfg = self.cfg(fbase)
        if cfg is None:
            esc.append({"fn": fn, "kind": "nolisting", "reg": reg, "c": 0, "tgt": fn, "src": None})
            self._live[key] = (0, False)
            return (0, False)
        n = len(cfg.ins)
        i0 = int(eoff, 0) // 4 if eoff else 0
        IN = [None] * n
        # the other argument registers: a function pointer passed beside the
        # object (Qsort's comparator, a collision query's collect callback)
        IN[i0] = {reg: 0, **{r: ("arg", r) for r in ("$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11") if r != reg}}
        work = [i0]
        afacts = {}      # call insn -> {argreg: arg/sym fact}
        hi, ok = 0, True
        hr, hw = 0, 0
        sites = {}       # (insn, argreg) -> c for calls
        kat = {}         # call insn -> {argreg: constant}
        jsrc = {}        # jalr insn -> what its target register held
        dead = {}        # insn -> "taken" / "fall": the edge that cannot be followed

        def kill(st, r):
            st.pop(r, None)
            for x in [x for x in st if isinstance(x, tuple) and x[1] == r]:
                del st[x]
        NZ_T = {"beqz": True, "beqzl": True, "bnez": False, "bnezl": False}
        while work:
            i = work.pop()
            st = dict(IN[i])
            op, ops = cfg.ins[i]
            w = self.WIDTH.get(op)
            ld = None
            mkey = None
            o = None
            if w and len(ops) >= 2:
                m = re.fullmatch(r"(.*)\((\$\w+)\)", ops[1].strip())
                if m:
                    off = m.group(1).strip()
                    try:
                        o = int(off, 0) if off else 0
                    except ValueError:
                        o = None
                    if o is not None:
                        mkey = ("m", m.group(2), o)
                        if isinstance(st.get(m.group(2)), int) and m.group(2) != "$29":
                            # a field of the passed object, whichever register
                            # holds its address (`sw vt, 0xF0($4)`; `lw t, 0xF0($16)`)
                            mkey = ("m", "@", st[m.group(2)] + o)
                if m and m.group(2) in st:
                    b = st[m.group(2)]
                    if o is not None and isinstance(b, int):
                        hi = max(hi, b + o + w)
                        if STORE.match(op):
                            hw = max(hw, b + o + w)
                        else:
                            hr = max(hr, b + o + w)
                        if op == "lw":
                            ld = ("fld", b + o)
                    elif o is not None and op == "lw" and b[0] == "fld":
                        ld = ("vt", b[1], o)
                    elif o is not None and op == "lw" and b[0] == "ofld":
                        ld = ("ovt", b[1], o)       # a virtual of ANOTHER object
                    elif o is not None and op == "lw" and b[0] == "ovt":
                        # `lw o, X(b); lw vt, V(o); lw f, S(vt)`: the object came
                        # from a field, its vptr at V (the pair above was not a slot)
                        ld = ("ovt", b[2], o)
                    elif o is not None and op == "lw" and b[0] == "vt":
                        ld = ("ovt", b[2], o)       # field V of ours points to another object
                    elif o is not None and op == "lw" and b[0] == "arg":
                        ld = ("ofld", o)            # a field of another argument (its vptr)
                    elif o == 0 and op == "lw" and b[0] == "tbl" and b[1].startswith("D_"):
                        ld = ("dtbl", b[1])         # an entry of a function table
                    elif o is not None and op == "lw" and b[0] == "sym" and b[1].startswith("D_"):
                        ld = ("dsym", b[1], o)      # one word of a data object (a vtable slot)
                elif m and o is not None and op == "lw" and m.group(2) not in ("$29", "$28"):
                    ld = ("ofld", o)                # field o of an object we do not track
                elif m and op == "lw" and m.group(2) != "$28" and                         re.fullmatch(r"%lo\((D_\w+)\)", off):
                    ld = ("dtbl", off[4:-1])        # `lui; addu idx; lw f, %lo(D)(r)`
            if op == "jalr" or (op == "jr" and ops and ops[0] != "$31"):
                tr = ops[-1] if ops else None
                jsrc[i] = st.get(tr) if tr and not isinstance(st.get(tr), int) else None
            # a branch on the pointer itself: the pointer is a non-null stack address
            tz = None
            if op in NZ_T and ops:
                tz = (ops[0], NZ_T[op])
            elif op in ("beq", "bne", "beql", "bnel") and len(ops) == 3 and "$0" in ops[:2] \
                    and ops[0] != ops[1]:
                tz = (ops[1] if ops[0] == "$0" else ops[0], op.startswith("beq"))
            if tz is not None:
                dk = i if op.endswith("l") else i + 1
                if isinstance(st.get(tz[0]), int):
                    dead[dk] = "taken" if tz[1] else "fall"
                elif st.get(tz[0]) == ("k", 0):
                    # a register known to be 0 on every path here (`daddu $16,
                    # $0, $0` before a join): the zero test always goes one way
                    dead[dk] = "fall" if tz[1] else "taken"
                else:
                    dead.pop(dk, None)
            _u, d = uses_defs(op, ops)
            if STORE.match(op) and mkey is not None and ops:
                # kill what the store may overwrite: an overlapping slot of the
                # same base, and any slot of another non-sp base (may alias)
                for x in [x for x in st if isinstance(x, tuple) and x[0] == "m"
                          and ((x[1] == mkey[1] and x[2] < o + w and o < x[2] + x[3])
                               or (x[1] != mkey[1] and "$29" not in (x[1], mkey[1])))]:
                    del st[x]
                if ops[0] in st and op in ("sw", "sd", "sq"):
                    st[mkey + (w,)] = st[ops[0]]
            elif op in ("move", "dmove") and len(ops) == 2:
                v = st.get(ops[1])
                kill(st, ops[0])
                if v is not None:
                    st[ops[0]] = v
            elif op in ("addu", "daddu", "or") and len(ops) == 3 and (ops[2] == "$0" or ops[1] == "$0"):
                src = ops[1] if ops[2] == "$0" else ops[2]
                v = ("k", 0) if src == "$0" else st.get(src)
                kill(st, ops[0])
                if v is not None:
                    st[ops[0]] = v
            elif op == "addiu" and len(ops) == 3 and ops[2].strip().startswith("%lo("):
                kill(st, ops[0])
                st[ops[0]] = ("sym", ops[2].strip()[4:-1])
            elif op == "addiu" and len(ops) == 3 and ops[1] == "$28" and                     ops[2].strip().startswith("%gp_rel("):
                kill(st, ops[0])
                st[ops[0]] = ("sym", ops[2].strip()[8:-1])
            elif op in ("addu", "daddu") and len(ops) == 3 and "$0" not in ops[1:] and any(
                    isinstance(st.get(x), tuple) and st[x][0] in ("sym", "tbl")
                    and st[x][1].startswith("D_") for x in ops[1:]):
                # a function table indexed: `addiu t, %lo(D); addu t, t, idx; lw f, 0(t)`
                v = next(st[x] for x in ops[1:] if isinstance(st.get(x), tuple)
                         and st[x][0] in ("sym", "tbl") and st[x][1].startswith("D_"))
                kill(st, ops[0])
                st[ops[0]] = ("tbl", v[1])
            elif op in ("addiu", "daddiu", "ori") and len(ops) == 3 and \
                    (ops[1] == "$0" or isinstance(st.get(ops[1]), int)
                     or (isinstance(st.get(ops[1]), tuple) and st[ops[1]][0] == "k")):
                im = _imm(ops[2])
                v0 = ("k", 0) if ops[1] == "$0" else st.get(ops[1])
                kill(st, ops[0])
                if im is not None and im[0] == "int" and (op != "ori" or v0 == ("k", 0)):
                    if isinstance(v0, int):
                        st[ops[0]] = v0 + im[1]
                    else:
                        st[ops[0]] = ("k", v0[1] + im[1])
            elif mkey is not None and op in ("lw", "ld", "lq") and ops and                     any(mkey + (w2,) in st for w2 in (4, 8, 16)):
                v = next(st[mkey + (w2,)] for w2 in (4, 8, 16) if mkey + (w2,) in st)
                # a value stored there earlier (spill / field)
                kill(st, ops[0])
                st[ops[0]] = v
            elif ld is not None and len(ops) >= 1:
                kill(st, ops[0])
                st[ops[0]] = ld
            else:
                for r in d:
                    kill(st, r)
            if (i in cfg.callafter or i in cfg.tail) and i not in cfg.switch:
                # i is a call's delay slot: the call transfers with st (delay applied)
                j = i - 1
                kk = {}
                for k2 in range(8):   # EABI: 8 GPR argument registers
                    r = "$%d" % (4 + k2)
                    v = st.get(r)
                    if isinstance(v, int):
                        sites[(j, r)] = v
                    elif isinstance(v, tuple) and v[0] == "k":
                        kk[r] = v[1]
                kat[j] = kk
                afacts[j] = {r: st[r] for r in ("$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11")
                             if isinstance(st.get(r), tuple) and st[r][0] in ("arg", "sym")}
                if i in cfg.callafter:
                    for r in [r for r in st if r in CALLER_SAVED]:
                        kill(st, r)
                    for x in [x for x in st if isinstance(x, tuple) and x[1] != "$29"]:
                        del st[x]
            succ = cfg.succ[i]
            if i in cfg.switch:
                succ = cfg.cases            # a switch: labels + unreached code
            if i in dead:
                op_i = cfg.ins[i][0]
                if BR.match(op_i) and op_i.endswith("l"):      # likely: [ds (taken), fall]
                    succ = [s for s in succ if s != (i + 1 if dead[i] == "taken" else i + 2)]
                elif len(succ) == 2:                           # delay slot: [label, fall]
                    succ = [succ[1]] if dead[i] == "taken" else [succ[0]]
            for sx in succ:
                if sx >= n:
                    continue
                if IN[sx] is None:
                    IN[sx] = st
                    work.append(sx)
                else:
                    mg = {r: c for r, c in IN[sx].items() if st.get(r) == c}
                    if mg != IN[sx]:
                        IN[sx] = mg
                        work.append(sx)
        for (j, r), c in sites.items():
            cop, cops = cfg.ins[j]
            if cop == "jalr" or (cop == "jr" and cops and cops[0] != "$31"):
                ok = False
                esc.append({"fn": fn, "kind": "jalr", "reg": r, "c": c, "tgt": None,
                            "src": jsrc.get(j), "insn": j})
                continue
            tgt = cops[-1] if cops else None
            nm = self.resolve(tgt, fn) if tgt else None
            if nm is None or depth >= self.max_depth:
                ok = False
                esc.append({"fn": fn, "kind": "nolisting" if nm is None else "depth", "reg": r,
                            "c": c, "tgt": nm or tgt, "src": None, "insn": j})
                continue
            if nm in seen:
                continue
            sub, sok = self.extent(nm, r, depth + 1, seen, kargs=kat.get(j))
            if sub:
                hi = max(hi, c + sub)
                sr, sw_ = self.rw_extent(nm, r, kat.get(j))
                hr = max(hr, c + sr) if sr else hr
                hw = max(hw, c + sw_) if sw_ else hw
            for e in self.escapes(nm, r, kat.get(j)):
                e2 = dict(e)
                e2["c"] = e["c"] + c
                e2["base"] = e.get("base", 0) + c     # the escaping fn's ENTRY, from ours
                if e2.get("src") and e2["src"][0] == "arg":
                    e2["src"] = afacts.get(j, {}).get(e2["src"][1])     # ours, a symbol, or None
                e2["path"] = [fn] + e.get("path", [])
                esc.append(e2)
            ok = ok and sok
        self._live[key] = (hi, ok)
        self._live[("rw", fn, reg)] = (hr, hw)
        return (hi, ok)

    def rw_extent(self, fn, reg, kargs=None):
        """(read end, write end) of extent(fn, reg)."""
        lr = self._lane_rule(fn, reg, kargs)
        if lr is not None:
            nm = fn.split(":", 1)[-1]
            wr = nm in ("memcpy", "memmove", "memset", "strncpy") and reg == "$4"
            return (0, lr[0]) if wr else (lr[0], 0)
        e, _ok = self.extent(fn, reg)
        r = self._live.get(("rw", fn, reg))
        return r if r is not None else (e, e)

    def escapes(self, fn, reg, kargs=None):
        """Why extent(fn, reg) is incomplete (see extent); [] when complete,
        plus `str` assumption rows."""
        lr = self._lane_rule(fn, reg, kargs)
        if lr is not None:
            return lr[2]
        self.extent(fn, reg)
        return self._live.get(("esc", fn, reg), [])

    def _sub(self, tgt, reg, depth, seen, frm):
        if tgt == "<indirect>":
            return "unknown:indirect call"
        nm = self.resolve(tgt, frm)
        if nm is None:
            return "unknown:no listing " + tgt
        if nm in seen:
            return "no"
        if depth > 4:
            return "unknown:depth"
        return self.reads(nm, reg, depth + 1, seen)


# ------------------------------------------------------------------ 64-bit values
# The EE's GPRs are 64 bits wide and mwcc never narrows a register for a C
# conversion to a 4-byte type: `s32 a = F64()` is a `daddu` move, `(int)u64`
# passes the whole `ld`.  A 32-bit ALU op (addu, sll, ...) sign-extends its
# result, so a value is only "wide" (high word not the sign of the low word)
# while it travels through copies and the doubleword / logical ops below.
# On i686 the C conversion really cuts the value: the port and retail differ
# when such a wide value reaches an op that reads all 64 bits.
WIDE_KEEP = ("move", "dmove", "daddu", "dsubu", "daddiu", "and", "or", "xor", "nor",
             "ori", "xori", "dsll", "dsllv", "movn", "movz")
# dsll32 keeps only the low word of its source (`dsll32 / dsra32` is mwcc's
# sign extension of a narrow value): it ends a wide value and makes a new one
WIDE_GEN = ("ld", "ldl", "ldr", "lq", "dsll32")     # results that are wide by themselves
WIDE_SENS = re.compile(r"^(beq|bne|beql|bnel|beqz|bnez|beqzl|bnezl|blez|bgtz|bltz|bgez|"
                       r"blezl|bgtzl|bltzl|bgezl|slt|sltu|slti|sltiu|dsrl|dsra|dsrl32|dsra32|"
                       r"dsrlv|dsrav|sd|sq|sdl|sdr|teq|tne|tge|tlt|tgeu|tltu)$")


def wide_flow(cfg: CFG, seeds: dict, gen_ret=None, gen_insn=True):
    """Forward may-taint of 64-bit values over one listing.
    seeds: {reg: label} at entry (an 8-byte parameter, or a 4-byte one under
    test).  gen_ret(target) -> label or None: a jal whose $v0 is wide (the
    callee returns an 8-byte integer).  gen_insn: `ld`/`lq`/`dsll32` results
    are wide (label 'ld@i').
    -> events: ('sens', i, op, labels)  an op that reads all 64 bits
               ('arg', j, target, reg, labels)  a call/tail jump receives one
               ('ret', i, labels)  $v0 at `jr $31`"""
    n = len(cfg.ins)
    IN = [None] * n
    IN[0] = {r: frozenset([lb]) for r, lb in seeds.items()}
    work = [0]
    ev = set()
    rets = {k + 1 for k, (o, xs) in enumerate(cfg.ins) if o == "jr" and xs and xs[0] == "$31"}
    while work:
        i = work.pop()
        st = dict(IN[i])
        op, ops = cfg.ins[i]
        u, d = uses_defs(op, ops)
        mem = re.fullmatch(r"(.*)\((\$\w+)\)", ops[-1].strip()) if ops else None
        base = mem.group(2) if mem and (STORE.match(op) or op.startswith("l")) else None
        vals = [r for r in u if r != base and r != "$0"]
        tl = frozenset().union(*[st.get(r, frozenset()) for r in vals]) if vals else frozenset()
        if tl and WIDE_SENS.match(op):
            if STORE.match(op):
                if ops and ops[0] in st and base != "$29":
                    ev.add(("sens", i, op, st[ops[0]]))
            else:
                ev.add(("sens", i, op, tl))
        if base == "$29" and op in ("sd", "sq", "sdl", "sdr") and ops:
            k = "sp" + mem.group(1).strip()
            if ops[0] in st:
                st[k] = st[ops[0]]
            else:
                st.pop(k, None)
        if op in ("movn", "movz") and len(ops) == 3 and ops[2] in st:
            ev.add(("sens", i, op, st[ops[2]]))
        # transfer
        if d:
            src = tl
            if op in ("movn", "movz") and len(ops) == 3:
                src = st.get(ops[1], frozenset()) | st.get(ops[0], frozenset())
            if op in WIDE_KEEP:
                keep = src
            else:
                keep = frozenset()
            if base == "$29" and op in ("ld", "lq", "ldl", "ldr"):
                # a spill reload: the value the matching `sd`/`sq` saved
                keep = st.get("sp" + mem.group(1).strip(), frozenset())
            elif gen_insn and op in WIDE_GEN:
                keep = keep | {f"ld@{i}"}
            for r in d:
                if keep:
                    st[r] = keep
                else:
                    st.pop(r, None)
        # $v0 at the return: after the jr's delay slot (mwcc often computes
        # the result there: `jr $31; sltu $2,$0,$2`, `jr $31; dsra32 ..`)
        if i in rets and "$2" in st:
            ev.add(("ret", i - 1, st["$2"]))
        if i in cfg.callafter or i in cfg.tail:
            j = i - 1
            cop, cops = cfg.ins[j]
            tgt = cfg.callafter.get(i) or cfg.tail.get(i)
            for k in range(8):
                r = "$%d" % (4 + k)
                if r in st:
                    ev.add(("arg", j, tgt, r, st[r]))
            if i in cfg.callafter:
                for r in list(st):
                    if r in CALLER_SAVED:
                        del st[r]
                if gen_ret and cop in CALLS:
                    lb = gen_ret(tgt)
                    if lb:
                        st["$2"] = frozenset([f"{lb}@{j}"])
        for sx in cfg.succ[i]:
            if sx >= n:
                continue
            if IN[sx] is None:
                IN[sx] = st
                work.append(sx)
            else:
                mg = dict(IN[sx])
                ch = False
                for r, v in st.items():
                    w = mg.get(r, frozenset())
                    if not v <= w:
                        mg[r] = w | v
                        ch = True
                if ch:
                    IN[sx] = mg
                    work.append(sx)
    return ev


def first_uses_are_loads(cfg: CFG, reg: str) -> bool:
    """Every first read of reg's incoming value (forward from entry, up to a
    redefinition or a call) is the base address of a load."""
    todo, seen, uses = [0], set(), []
    while todo:
        i = todo.pop()
        if i in seen or i >= len(cfg.ins):
            continue
        seen.add(i)
        op, ops = cfg.ins[i]
        u, d = uses_defs(op, ops)
        if reg in u:
            uses.append((op, ops))
            continue
        if reg in d or i in cfg.callafter or i in cfg.tail:
            continue
        todo.extend(cfg.succ[i])
    return bool(uses) and all(
        re.fullmatch(r"l[bhwdq]u?|lwc1|lq|ldc1|lwl|lwr|ldl|ldr", op) and ops
        and ops[-1].endswith("(%s)" % reg) for op, ops in uses)


# ------------------------------------------------------------------ return values
def exit_values(cfg: CFG, reg: str = "$2"):
    """[(kind, info)] for every way the function returns: ('jr', Term) =
    reg's value after the `jr $31` delay slot; ('tail', target) = a tail
    jump (`j G` / `jr $reg`): the value is whatever G leaves."""
    out = []
    for i, (op, ops) in enumerate(cfg.ins):
        if op == "jr" and ops and ops[0] == "$31" and i + 1 < len(cfg.ins):
            ds = i + 1
            dop, dops = cfg.ins[ds]
            if reg in uses_defs(dop, dops)[1]:
                out.append(("jr", _expr(cfg, ds, 0)))
            else:
                out.append(("jr", value(cfg, i, reg)))
    for ds, tgt in cfg.tail.items():
        out.append(("tail", tgt))
    return out


def _flat(t: Term):
    return list(t.a) if t.kind == "phi" else [t]


def exit_class(cfg: CFG, reg: str = "$2"):
    """Summarise exit_values: -> (cls, [callees]) with cls
      'pass'    every exit returns a call's result (RET of a jal, or a tail
                jump): the function forwards that callee's value
      'set'     every exit's value is computed by the function itself
      'mixed'   some exits forward a call's result, others compute
      'undef'   some exit returns a register nobody set (caller-saved clobber,
                the caller's own value)
      'none'    no exit (noreturn)"""
    ex = exit_values(cfg, reg)
    if not ex:
        return "none", []
    calls, kinds = [], set()
    for k, v in ex:
        if k == "tail":
            calls.append(v)
            kinds.add("pass")
            continue
        for t in _flat(v):
            if t.kind == "ret":
                calls.append(t.b)
                kinds.add("pass")
            elif t.kind == "other" and str(t.a).startswith(("ret of jalr",)):
                calls.append("<indirect>")
                kinds.add("pass")
            elif t.kind in ("clobber",) or (t.kind == "other" and str(t.a).startswith("entry")):
                kinds.add("undef")
            else:
                kinds.add("set")
    if "undef" in kinds:
        cls = "undef"
    elif kinds == {"pass"}:
        cls = "pass"
    elif kinds == {"set"}:
        cls = "set"
    else:
        cls = "mixed"
    return cls, sorted(set(calls))


def reg_after_call(cfg: CFG, j: int, reg: str = "$2") -> str:
    """What happens to reg (the call's result) after the call at insn j:
    'read' (some path reads it before it is redefined / clobbered),
    'returned' (reaches `jr $31` or a tail jump untouched: the enclosing
    function forwards it), 'dead'."""
    n = len(cfg.ins)
    todo, seen, res = [j + 2], set(), "dead"
    while todo:
        k = todo.pop()
        if k in seen or k >= n:
            continue
        seen.add(k)
        op, ops = cfg.ins[k]
        u, d = uses_defs(op, ops)
        if op in CALLS and reg.startswith("$") and reg in ("$4", "$5", "$6", "$7"):
            pass
        if reg in u:
            return "read"
        if op == "jr" and ops and ops[0] == "$31":
            ds = k + 1
            if ds < n and reg in uses_defs(*cfg.ins[ds])[0]:
                return "read"
            if ds < n and reg in uses_defs(*cfg.ins[ds])[1]:
                continue
            res = "returned"
            continue
        if k in cfg.tail and reg not in d:
            res = "returned"
            continue
        if reg in d:
            continue
        if k in cfg.callafter and reg in CALLER_SAVED:
            continue
        todo.extend(cfg.succ[k])
    return res
