#!/usr/bin/env python3
"""Function-pointer resolution for the protos `stack-block` rule.

asmflow.Flow.extent stops at a `jalr`: a stack address that reaches an
indirect call has only a lower-bound extent.  This module resolves the
targets of those calls from retail facts and the game tree, so the stage
measures the full reach itself (docs/PROTOS.md "Stack-block census",
2026-10-24 "function-pointer resolution in the stage"); the census tool
(tools/census/stackblock_census.py) uses the same class for its notes.

Target classes (escape `src` facts of Flow.extent):
  ('vt', V, S)     virtual call on the passed object itself: the vtable the
                   caller (or a ctor it calls) stores at sp+off+V, slot S;
  ('ovt', V, S)    virtual call on another object: slot S of every vtable
                   some code stores at offset V of an object (<= MAX_CANDS);
  ('fld'|'ofld', X) a function pointer loaded from offset X of an object:
                   every function whose address code stores at +X, else the
                   slot X of every vtable (a vptr loaded from a global);
  ('dtbl', D)      an entry of the function table D (`%lo(D)`/`%gp_rel(D)`
                   indexed): every function in that data2c object;
  ('arg'|'sym', ..) a function passed as an argument / named directly;
  JALR_SOURCES     reviewed: the jalr of a named function calls one of the
                   functions of the listed tables (script natives ...);
  REVIEWED         reviewed bounds (the reach stays inside a sub-object).
Vtable and table words come from the game tree's data2c tables (MAIN only;
overlay data is not in the tree, so overlay vtables stay unresolved).
"""
from __future__ import annotations

import collections
import re

import asmflow

TABLE_RE = re.compile(r"\bu32\s+(D_([0-9A-Fa-f]+))\s*\[(\d*)\][^=;{]*=\s*\{(.*?)\};", re.S)
SYM = re.compile(r"%(?:lo|gp_rel)\((\w+)\)")
# overlay listings spell a MAIN data address as `addiu r, r, (0x477600 & 0xFFFF)`
LOADDR = re.compile(r"\(\s*0x([0-9A-Fa-f]{6,8})\s*&\s*0xFFFF\s*\)")


class _M:
    def __init__(self, name):
        self._n = name

    def group(self, _k):
        return self._n


def sym_match(opnd):
    """match-like object whose group(1) is the symbol an addiu operand names
    (`%lo(S)`, `%gp_rel(S)`, `(0xADDR & 0xFFFF)` -> D_ADDR), or None."""
    opnd = opnd.strip()
    m = SYM.fullmatch(opnd)
    if m:
        return m
    m = LOADDR.fullmatch(opnd)
    return _M("D_%08X" % int(m.group(1), 16)) if m else None
MAX_CANDS = 40          # foreign-vtable candidates (as the census)
MAX_ANY = 400           # candidates of a reviewed / table source


def _split_top(s):
    out, dep, cur = [], 0, []
    for ch in s:
        if ch in "([{":
            dep += 1
        elif ch in ")]}":
            dep -= 1
        if ch == "," and dep == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur))
    return out


def data_words(texts):
    """{addr: ('fn', name) | ('int', v) | ('expr', text)} and {sym: (addr, n)}
    of every `u32 D_X[N] = {..}` table in src/main_data/data2c_*.c."""
    W, T = {}, {}
    for rel in sorted(texts):
        if "/data2c_" not in rel:
            continue
        t = texts[rel]
        if isinstance(t, bytes):
            t = t.decode("utf-8", "replace")
        for m in TABLE_RE.finditer(t):
            a = int(m.group(2), 16)
            ents = _split_top(m.group(4))
            T[m.group(1)] = (a, len(ents))
            for i, e in enumerate(ents):
                e = e.strip()
                k = re.fullmatch(r"\(u32\)\s*&\s*(\w+)", e)
                if k:
                    W[a + 4 * i] = ("fn", k.group(1))
                    continue
                k = re.fullmatch(r"(0x[0-9A-Fa-f]+|\d+)[uU]?", e)
                W[a + 4 * i] = ("int", int(k.group(1), 0)) if k else ("expr", e)
    return W, T


class Resolver:
    # Reviewed sources: the jalr in <function> calls a function of these data
    # tables (every `(u32)&F` entry).  {escaping fn: ([table syms], why)}
    JALR_SOURCES = {
        "ScriptCallWithArgs_302770": (
            ["D_00452250", "D_0044B7D0"],
            "script native = ScriptCall entry f0, set only by ScriptCallInit_302ad0 from "
            "the event call table D_00452250 (EvScriptCmdScriptRecAddCall_3016b0) or the "
            "chara command table D_0044B7D0 (ScriptCallBuildCharaCmd_23f980)"),
    }
    # Reviewed receivers: a jalr of <function> (at vtable slot S, None = any
    # slot; S read from the listing) is a virtual call on an object of these
    # classes.  {(escaping fn, S): ([vtable syms], why)}
    CHARA_VTABLES = ["D_004722A0", "D_004727B0", "D_00472CC0", "D_004731D0", "D_004736E0",
                     "D_00473BF0", "D_00474100", "D_004746C0", "D_00474B20", "D_00474F80",
                     "D_004753E0"]
    REVIEWED_VTABLES = {
        ("CharaActBlownAway_217de0", 0x20C): (
            CHARA_VTABLES,
            "c->x0 = the actor ActorFindById_3eb870 returned (ActionMgrRunActions_231f90 st.o, "
            "MainMenuModeUpdate_27d460 tmp[0]); slot 0x20C of every chara/unit vtable is "
            "CharaTopPriorityStatusMaybe_3b6a80"),
        ("CharaActDamage_218880", 0x20C): (CHARA_VTABLES, "as CharaActBlownAway_217de0"),
        ("SceneMapAreasCollectCollTrisMaybe_1c5090", 0x60): (
            ["D_00470480"],
            "the static scene's live objects are map area models: MapDataLoadRequest*_1e6* / "
            "MapAreaStartLoad_1d8370 store D_00470410 then D_00470480 at data+0x98 = model "
            "(data+0x30) + 0x68; slot 0x60 = func_00187D40_e1"),
        ("MapAreaModelCollectTrisAllMaybe_187d40@48", 0x5C): (
            ["D_00470480"], "func_00187D40_e1 tail-calls its own object's slot 0x5C (MapAreaModel)"),
        ("MapAreaModelCollectTrisAllMaybe_187d40", 0x5C): (
            ["D_00470480"], "MapAreaModelCollectTrisAll tail-calls its own object's slot 0x5C"),
        ("EventObjMgrFindFirstHit_2e8560", 0x24): (
            ["D_004717D0", "D_00471820", "D_00471870", "D_004718C0", "D_00471910", "D_00471960",
             "D_004719B0", "D_00471A00", "D_00471D70", "D_00471DC0", "D_00471E20", "D_00471E70",
             "D_00471EC0", "D_00471F10", "D_00472000"],
            "the event-object manager's lists hold event objects (vptr at +0xDC of the object = "
            "list node + 0x10); slot 0x24 = their HitTest (EvFollowObj, EvDoorObj, EvObjLift, "
            "ObjTypeVehicle, EvM05Change, EvNodeAttachObj, ObjTypeMonograph, EvObjHitTestNone)"),
        ("CameraApplyAnimSample_154400", None): (
            ["D_00470090", "D_004700E0", "D_00470340"],
            "`out` is the camera CameraApplyMotionTrack_154170 drives (vptr +0xC0: CameraBase / "
            "CameraObj vtables)"),
        ("MapDataCollectCollTrisMaybe_1e6c80", 0x60): (
            ["D_00470480"], "MapData's area model at +0x30 (vptr data+0x98, D_00470480)"),
        ("MapDataQueryCollTrisMaybe_1e6bc0", 0x64): (
            ["D_00470480"], "MapData's area model at +0x30 (vptr data+0x98, D_00470480)"),
        ("CameraObjOrbitControlMaybe_161260", None): (
            ["D_00470090", "D_004700E0", "D_00470340"],
            "this = a camera object (vptr +0xC0: CameraBase / CameraObj vtables)"),
        ("CameraSweepEyeCollisionMaybe_160c90", None): (
            ["D_00470090", "D_004700E0", "D_00470340"], "this = a camera object (vptr +0xC0)"),
        ("CameraCollideGroundMaybe_160500", None): (
            ["D_00470090", "D_004700E0", "D_00470340"], "this = a camera object (vptr +0xC0)"),
        ("CameraFindClearYawMaybe_160730", None): (
            ["D_00470090", "D_004700E0", "D_00470340"], "this = a camera object (vptr +0xC0)"),
        ("InsectGetStats_3d1470", None): (
            ["D_00475B10"],
            "arg0 is an insect inventory object (InvObjCreateByKind_3c75c0 kind -> vtable "
            "D_00475B10); callers InsectBreedInheritStats/InsectRollStatGain/InsectBreedCreate"),
        ("InsectStatsGet_386a10", None): (
            ["D_00475B10"],
            "arg0+0x96C = the cage menu's current insect item (InsectCageMenuGetCurCageItem); "
            "vtable D_00475B10"),
    }
    # Reviewed port arities where the jalr does not pair with a C member call
    # (an inline operator makes it): {(escaping fn, slot): (GPR lanes, why)}
    REVIEWED_PORT_LANES = {
        ("NumPutPadOutput_1a4610", 0x34): (
            2, "Streambuf::overflow(c) through OutIt::operator= (`*out++ = c`): the C passes "
               "(this, c); prefix/digits stay in retail's $8/$10 only"),
    }
    # Reviewed callback sources (a field retail code copies around, so no
    # `sw <F>, X(base)` names it): {(escaping fn, field): ([listings], why)}
    CALLBACK_SOURCES = {
        ("VariantFireChangeCallback_36e480", 0x20): (
            ["main:ScriptEmitCmdHandlerMaybe_3da110"],
            "Variant change callback = the ScriptFn* handlers ScriptEmitCmdHandlerMaybe_3da110 "
            "stores (e.fn = ..; VariantRecCopy_36ee10 copies the record into pool variants)"),
        ("Variant*", 0x20): (
            ["main:ScriptEmitCmdHandlerMaybe_3da110"], "as VariantFireChangeCallback_36e480"),
    }
    # Reviewed bounds: (predicate(x, where, fn), bytes from the passed
    # pointer the reach stays inside, why)
    REVIEWED = [
        (lambda x, where, fn: x["kind"] == "lenvar" and where in (
            "StringReplace_106f90", "StringReplaceFill_1075d0", "StringReserve_107e80"),
         None, "MSL string: memcpy into the inline (short) buffer is bounded by the string's own capacity"),
        (lambda x, where, fn: x["kind"] == "jalr" and fn == "CfgVmStep_42f6e0",
         0x400, "cfg VM command handler: gets the argument block inside the VM context "
         "(+0x428, 0x80 args x 8 bytes); the default handler (+0x404) is only ever zeroed "
         "(CfgVmReset_42fc10)"),
    ]

    def __init__(self, stage, flow, words, tables):
        # port_lanes(listing, jalr insn) -> GPR lanes the PORT's C call at that
        # jalr passes (this + C arguments + vcall-forward), or None (unpaired)
        self.port_lanes = None
        self.st = stage
        self.flow = flow
        self.W = words
        self.T = tables
        self._cb = None
        self._dv = None
        self._vtc = {}
        self.unknown = set()
        self.nolisting = set()
        self.scan_hi = 0            # largest reach of a disagreeing scanned set (census)
        # port_nparams(name) -> parameter count of a C definition (stage), or None
        self.port_nparams = None

    # ------------------------------------------------------------ names
    def sym_addr(self, name, img):
        m = re.fullmatch(r"(?:D|jtbl|func)_([0-9A-Fa-f]{6,8})", name)
        if m:
            return int(m.group(1), 16)
        return self.st._name_addr(name, img)

    def fn_listing(self, addr, img):
        r = self.st._fn_at(addr, img)
        if r and r[1]:
            return f"{r[0]}:{r[1]}"
        return self.flow.resolve(f"func_{addr:08X}", f"{img}:x")

    def word_fn(self, addr, img):
        """Listing of the function whose address the data word at addr holds."""
        w = self.W.get(addr)
        if not w or w[0] != "fn":
            return None
        return self.flow.resolve(w[1], f"{img}:x") or self.flow.resolve(w[1], "main:x")             or self._interior(w[1])

    def _interior(self, name):
        """`main:Owner@OFF` for an interior entry the address table lists in
        `fentries` ({addr: func_XXXXXXXX_eK}) inside a MAIN listing."""
        if not hasattr(self, "_fent"):
            tab = self.st.addr_table or {}
            self._fent = {v: a for a, v in (tab.get("fentries") or {}).items()}
            idx = self.st._addr_index("main")
            self._starts = sorted(idx)
            self._idx = idx
        a = self._fent.get(name)
        if a is None:
            return None
        import bisect
        k = bisect.bisect_right(self._starts, a) - 1
        if k < 0:
            return None
        base = self._starts[k]
        cfg = self.flow.cfg(f"main:{self._idx[base]}")
        if cfg is None or (a - base) // 4 >= len(cfg.ins):
            return None
        return f"main:{self._idx[base]}@{a - base}"

    def table_fns(self, sym, img="main"):
        if sym not in self.T:
            return []
        a, n = self.T[sym]
        return sorted({t for t in (self.word_fn(a + 4 * i, img) for i in range(n)) if t})

    # ------------------------------------------------------------ vtables
    def vptr_stores(self, fn, base_reg, depth=0):
        """[(offset from ENTRY(base_reg) (or the entry sp), symbol, insn)] of
        every `sw <%lo(SYM)>, off(<ENTRY-based>)` in fn in listing order,
        following jal callees passed an ENTRY-based $4 (constructors).  Linear
        scan; a jal's delay slot is applied before the call."""
        key = (fn, base_reg)
        if key in self._vtc:
            return self._vtc[key]
        self._vtc[key] = []
        base, _a, eoff = fn.partition("@")
        cfg = self.flow.cfg(base)
        if cfg is None or depth > 4:
            return []
        st = {base_reg: 0}
        out = []

        def step(st, op, ops, i):
            """Apply one non-call instruction; record vptr stores."""
            if op in ("addiu", "daddiu") and len(ops) == 3:
                m = sym_match(ops[2])
                if m:
                    st[ops[0]] = ("sym", m.group(1))
                    return
                im = asmflow._imm(ops[2])
                if isinstance(st.get(ops[1]), int) and im and im[0] == "int":
                    st[ops[0]] = st[ops[1]] + im[1]
                    return
            if op in ("daddu", "addu", "or", "move") and len(ops) >= 2:
                src = [x for x in ops[1:] if x != "$0"]
                if len(src) == 1 and (len(ops) == 2 or "$0" in ops[1:]):
                    v = st.get(src[0])
                    st.pop(ops[0], None)
                    if v is not None:
                        st[ops[0]] = v
                    return
            if op == "sw" and len(ops) == 2:
                m = re.fullmatch(r"(.*)\((\$\w+)\)", ops[1])
                if m and isinstance(st.get(m.group(2)), int) and                         isinstance(st.get(ops[0]), tuple):
                    try:
                        o = int(m.group(1) or "0", 0)
                    except ValueError:
                        o = None
                    if o is not None:
                        out.append((st[m.group(2)] + o, st[ops[0]][1], i))
                return
            _u, dd = asmflow.uses_defs(op, ops)
            sp0 = st.get("$29")
            for r in dd:
                st.pop(r, None)
            if op == "addiu" and ops and ops[0] == "$29" and isinstance(sp0, int):
                im = asmflow._imm(ops[2])
                if im and im[0] == "int":
                    st["$29"] = sp0 + im[1]

        i = int(eoff or 0) // 4
        n = len(cfg.ins)
        while i < n:
            op, ops = cfg.ins[i]
            if op == "jal" and i + 1 < n:
                op2, ops2 = cfg.ins[i + 1]
                step(st, op2, ops2, i + 1)           # the delay slot runs first
                c = st.get("$4")
                tgt = self.flow.resolve(ops[-1], fn) if ops else None
                if isinstance(c, int) and tgt:
                    for o, s, _j in self.vptr_stores(tgt, "$4", depth + 1):
                        out.append((c + o, s, i))
                for r in list(st):
                    if r in asmflow.CALLER_SAVED:
                        del st[r]
                i += 2
                continue
            step(st, op, ops, i)
            i += 1
        self._vtc[key] = out
        return out

    def vtables_of_slot(self, caller, slot_off):
        return sorted({s for o, s, _i in self.vptr_stores(caller, "$29") if o == slot_off})

    # ------------------------------------------------------------ callbacks
    def _scan(self):
        """One pass over every listing: function addresses (self._cb) and data
        symbols (self._dv: vtable candidates) stored at offset X of a non-sp base."""
        if self._cb is not None:
            return
        self._cb = collections.defaultdict(set)
        self._dv = collections.defaultdict(set)
        tab = self.st.addr_table or {}
        imgs = [("main", n) for n in (tab.get("asm_text") or {})] + \
            [(img, n) for img, d in (tab.get("ovl_text") or {}).items() for n in d]
        for img, n in imgs:
            r = self.st._listing(img, n)
            if not r:
                continue
            ins = [x for x in r[0] if x[0] != ".label"]
            for i, (op, ops) in enumerate(ins):
                if op != "addiu" or len(ops) != 3:
                    continue
                m = sym_match(ops[2])
                if not m or m.group(1).startswith("jtbl_"):
                    continue
                if m.group(1).startswith("D_"):
                    tgt, dst = (img, m.group(1)), self._dv
                else:
                    a = self.sym_addr(m.group(1), img)
                    tgt = self.fn_listing(a, img) if a else None
                    dst = self._cb
                if not tgt:
                    continue
                reg = ops[0]
                for op2, ops2 in ins[i + 1:i + 10]:
                    if op2 == "sw" and ops2 and ops2[0] == reg:
                        mm = re.fullmatch(r"(.*)\((\$\w+)\)", ops2[1])
                        if mm and mm.group(2) != "$29":
                            try:
                                dst[int(mm.group(1) or "0", 0)].add(tgt)
                            except ValueError:
                                pass
                    _u, dd = asmflow.uses_defs(op2, ops2)
                    if reg in dd:
                        break

    def fn_refs(self, listing):
        img, _c, nm = listing.partition(":")
        r = self.st._listing(img, nm)
        out = set()
        for op, ops in (r[0] if r else []):
            if op == "addiu" and len(ops) == 3:
                m = sym_match(ops[2])
                if m and not m.group(1).startswith(("D_", "jtbl_")):
                    a = self.sym_addr(m.group(1), img)
                    t = self.fn_listing(a, img) if a else None
                    if t:
                        out.add(t)
        return out

    def _reviewed_cb(self, off, where):
        return bool(self.CALLBACK_SOURCES.get((where, off)) or (
            self.CALLBACK_SOURCES.get(("Variant*", off)) if (where or "").startswith("Variant") else None))

    def callbacks(self, off, where=None):
        self._scan()
        src = self.CALLBACK_SOURCES.get((where, off)) or (
            self.CALLBACK_SOURCES.get(("Variant*", off)) if (where or "").startswith("Variant") else None)
        if src:
            out = set()
            for lst in src[0]:
                out |= self.fn_refs(lst)
            return sorted(out)
        return sorted(self._cb.get(off, ()))

    def _slot_fn(self, img, sym, S):
        """Listing at vtable sym + S; None for a null word.  A vtable whose
        words the tree does not hold (overlay data, a non-u32 object) is
        recorded in self.unknown (the caller keeps the site open)."""
        a = self.sym_addr(sym, img)
        w = self.W.get(a + S) if a is not None else None
        if w is not None and w[0] == "fn" and not self.word_fn(a + S, img):
            self.nolisting.add(w[1])        # a port-only C function (split entry)
            return None
        if w is None or w[0] == "expr":
            self.unknown.add(sym)
            return None
        return self.word_fn(a + S, img) if w[0] == "fn" else None

    def foreign_virtuals(self, V, S):
        self._scan()
        out = set()
        for img, sym in self._dv.get(V, ()):
            t = self._slot_fn(img, sym, S)
            if t:
                out.add(t)
        return sorted(out)

    def _jalr_slot(self, fn, j):
        """S of the `lw f, S(f)` feeding the jalr at insn j of listing fn."""
        if not fn or j is None:
            return None
        cfg = self.flow.cfg(fn.partition("@")[0])
        if cfg is None or j >= len(cfg.ins) or cfg.ins[j][0] not in ("jalr", "jr"):
            return None
        f = cfg.ins[j][1][-1]
        for op, ops in reversed(cfg.ins[max(0, j - 8):j]):
            if ops and ops[0] == f:
                m = re.fullmatch(r"(-?\w+)\((\$\w+)\)", ops[1]) if op == "lw" and len(ops) == 2 else None
                if m and m.group(2) == f:
                    im = asmflow._imm(m.group(1))
                    return im[1] if im and im[0] == "int" else None
                return None
        return None

    def _this_delta(self, fn, j, V=None):
        """d when the jalr at insn j of listing fn is `lw f, V(b)` .. `lw f,
        S(f)` .. $4 = b + d (same straight-line run, b not redefined), else None."""
        if not fn or j is None:
            return None
        cfg = self.flow.cfg(fn.partition("@")[0])
        if cfg is None or j >= len(cfg.ins) or cfg.ins[j][0] not in ("jalr", "jr"):
            return None
        f = cfg.ins[j][1][-1]
        run = cfg.ins[max(0, j - 16):j + 2]       # + the delay slot
        b = this = None
        for op, ops in run:
            if op in ("lw",) and ops and ops[0] == f:
                m = re.fullmatch(r"(-?\w+)\((\$\w+)\)", ops[1])
                if m and m.group(2) != f:
                    b = m.group(2)
            if ops and ops[0] == "$4":
                if op in ("daddu", "addu", "or", "move") and len(ops) >= 2:
                    src = [r for r in ops[1:] if r != "$0"]
                    this = (src[0], 0) if len(src) == 1 else None
                elif op in ("addiu", "daddiu") and len(ops) == 3:
                    im = asmflow._imm(ops[2])
                    this = (ops[1], im[1]) if im and im[0] == "int" else None
                else:
                    this = None
        if b is None and V is not None:
            # the vptr load sits in a branch-likely delay slot / loop head:
            # every `lw f, V(b)` of the listing names the same base
            bs = set()
            for op, ops in cfg.ins:
                if op == "lw" and ops and ops[0] == f:
                    m = re.fullmatch(r"(-?\w+)\((\$\w+)\)", ops[1])
                    if m and m.group(2) != f and asmflow._imm(m.group(1)) == ("int", V):
                        bs.add(m.group(2))
            b = bs.pop() if len(bs) == 1 else None
        if b and this and this[0] == b:
            return this[1]
        return None

    def reviewed(self, x, where, fn):
        for pred, bound, why in self.REVIEWED:
            if pred(x, where, fn):
                return bound, "reviewed: " + why
        return None

    # ------------------------------------------------------------ one site
    def _targets_extent(self, cands, reg, src, depth, seen, cctx=None):
        """(max extent, incomplete targets) over candidate listings."""
        mx, inc, es = 0, [], set()
        for tgt in cands:
            se, sok, _n, _t, _w = self.extent(tgt, reg, None, cctx, depth + 1, seen, own_src=src)
            mx = max(mx, se)
            es.add(se)
            if not sok:
                inc.append(tgt.split(":")[-1])
        self._es = es
        return mx, inc

    def extent(self, listing, reg, kargs=None, ctx=None, depth=0, seen=frozenset(), own_src=None):
        """(E, complete, notes, targets, write end) of `listing` through reg,
        with jalr targets resolved (notes of what stays open start with "? ").
        ctx = {img, def, off, terms} of the call site (own-local vtables,
        function-pointer arguments); nested levels get {img, vmap}: the
        vtables stored in the caller's frame at offsets from the pointer."""
        e, ok = self.flow.extent(listing, reg, kargs=kargs)
        wend = self.flow.rw_extent(listing, reg, kargs)[1]
        if ok:
            return e, True, [], [], wend
        if depth > 2 or (listing, reg) in seen:
            return e, False, [f"? resolution depth at {listing.split(':')[-1]}"], [], wend
        seen = seen | {(listing, reg)}
        notes, targets, done = [], [], True
        vmap = None
        if ctx is not None and "vmap" in ctx:
            vmap = ctx["vmap"]
        elif ctx is not None and "def" in ctx:
            vmap = collections.defaultdict(set)
            for o, sym, _i in self.vptr_stores(f"{ctx['img']}:{ctx['def']}", "$29"):
                vmap[o - ctx["off"]].add(sym)
        for x in self.flow.escapes(listing, reg, kargs):
            k = x["kind"]
            where = (x.get("path") or [x["fn"]])[-1] if x.get("fn") else listing
            where = (where or "").split(":")[-1]
            esc_fn = (x.get("fn") or "").split(":")[-1]
            src = x.get("src")
            if k == "str":
                notes.append(f"str:{x['tgt']}")
                continue
            # a callback whose only escape is the same callback field (ScriptFn*
            # -> VariantSetS32 -> VariantFireChangeCallback): covered by the fixpoint
            if own_src is not None and k == "jalr" and tuple(src or ()) == tuple(own_src) \
                    and x.get("base", 0) == 0:
                continue
            rv = self.reviewed(x, where, esc_fn)
            if rv:
                if rv[0] is not None:
                    e = max(e, x["c"] + rv[0])
                notes.append(rv[1])
                continue
            if k != "jalr":
                done = False
                if k == "lenvar":
                    notes.append(f"? {x['tgt']}(ptr+0x{x['c']:x}) length from data (via {where})")
                else:
                    notes.append(f"? {k} {x['tgt']} (via {where})")
                continue
            c, xr = x["c"], x["reg"]
            cands, what, scanned = None, None, False
            self.unknown = set()
            self.nolisting = set()
            pl = self.port_lanes(x["fn"], x.get("insn")) if self.port_lanes and x.get("fn") else None
            if pl is None:
                rl = self.REVIEWED_PORT_LANES.get((esc_fn, self._jalr_slot(x.get("fn"), x.get("insn"))))
                pl = rl[0] if rl else None
            if pl is not None and int(xr[1:]) - 4 >= pl:
                # retail's register still holds the pointer at the jalr, but the
                # C member call there (paired with the jalr, vcall-forward
                # included) passes only lanes 0..pl-1: no port callee gets it
                notes.append(f"jalr in {esc_fn} @{x.get('insn')}: the port's member call passes "
                             f"{pl} GPR lane(s), {xr} (=ptr+0x{c:x}) is only a retail leftover")
                continue
            S = self._jalr_slot(x.get("fn"), x.get("insn"))
            rv_vt = self.REVIEWED_VTABLES.get((esc_fn, S)) or self.REVIEWED_VTABLES.get((esc_fn, None))
            if rv_vt is not None and S is not None:
                vts, why = rv_vt
                cands = sorted({t for t in (self._slot_fn("main", vt, S) for vt in vts) if t})
                what = f"vcall in {esc_fn} {'/'.join(vts)}+0x{S:x} [reviewed: {why}]"
            elif esc_fn in self.JALR_SOURCES:
                tabs, why = self.JALR_SOURCES[esc_fn]
                cands = sorted({t for s in tabs for t in self.table_fns(s)})
                what = f"jalr in {esc_fn}: {len(cands)} reviewed targets [{why}]"
            elif src and src[0] == "dsym":
                t = self.word_fn(self.sym_addr(src[1], "main") + src[2], "main")                     if self.sym_addr(src[1], "main") is not None else None
                cands = [t] if t else None
                what = f"vcall in {esc_fn} {src[1]}+0x{src[2]:x}"
            elif src and src[0] == "vt" and vmap is not None:
                _v, V, S = src
                vts = sorted(vmap.get(x.get("base", 0) + V, ()))
                cands = sorted({t for t in (self._slot_fn(ctx["img"], vt, S) for vt in vts) if t})
                what = f"vcall in {esc_fn} {'/'.join(vts)}+0x{S:x}" if cands else None
                if not cands:
                    what = f"vcall in {esc_fn} slot+0x{S:x} (vptr at +0x{V:x}): no vtable store found"
                    cands = None
            elif src and src[0] == "vt":
                what = f"vcall in {esc_fn} slot+0x{src[2]:x} (vptr at +0x{src[1]:x})"
            elif src and src[0] == "ovt":
                _v, V, S = src
                # the vptr offset relative to `this` ($4 = base + d at the jalr,
                # vptr loaded from base + V: EventObjMgrFindFirstHit_2e8560 calls
                # the object at list node + 0x10, vptr at node + 0xEC)
                d = self._this_delta(x.get("fn"), x.get("insn"), V)
                Vt = V - d if d is not None else V
                cands = self.foreign_virtuals(Vt, S)
                scanned = True
                what = f"vcall in {esc_fn} on another object (vptr +0x{Vt:x}, slot +0x{S:x})"
                if len(cands) > MAX_CANDS:
                    what += f": {len(cands)} candidates"
                    cands = None
            elif src and src[0] in ("fld", "ofld"):
                X = src[1]
                cands = self.callbacks(X, esc_fn)
                scanned = not self._reviewed_cb(X, esc_fn)
                what = f"callback in {esc_fn} at +0x{X:x}"
                if not cands:
                    what += ": no stored targets found"
            elif src and src[0] == "dtbl":
                cands = self.table_fns(src[1])
                what = f"function table {src[1]} in {esc_fn}"
            elif src and src[0] in ("arg", "sym") and ctx is not None:
                if src[0] == "arg":
                    t = (ctx.get("terms") or {}).get(src[1])
                    tgt = None
                    if t and t[0] == "sym":
                        tgt = self.flow.resolve(t[1], f"{ctx['img']}:{ctx['def']}")
                    elif t and t[0] == "addr":
                        tgt = self.fn_listing(t[1], ctx["img"])
                else:
                    tgt = self.flow.resolve(src[1], f"{ctx['img']}:{ctx['def']}")
                cands = [tgt] if tgt else None
                what = f"fnptr in {esc_fn}"
            if not cands or len(cands) > MAX_ANY:
                done = False
                notes.append("? " + (what or f"jalr in {esc_fn} (pointer from elsewhere)")
                             + (f": {len(cands)} candidates" if cands else ": no targets")
                             + f" ({xr}=ptr+0x{c:x})")
                continue
            unk = sorted(self.unknown)
            for nm in sorted(self.nolisting):
                # a target with no retail listing (entry_002d94b0_e6: a split
                # entry the port defines in C): fine when its C definition
                # does not take the lane at all
                npar = self.port_nparams(nm) if self.port_nparams else None
                if npar is not None and int(xr[1:]) - 4 >= npar:
                    notes.append(f"{nm}: no listing; its C definition takes {npar} parameter(s), "
                                 f"not {xr}")
                else:
                    unk.append(nm)
            cctx = None
            if vmap is not None:
                cctx = {"img": ctx["img"], "vmap": {o - c: v for o, v in vmap.items()}}
            mx, inc = self._targets_extent(cands, xr, src, depth, seen, cctx)
            if unk:
                inc.append("vtable words not in the tree: " + " ".join(unk[:3]))
            if scanned and len(self._es) > 1:
                # a candidate set from the store scan (every vtable / callback
                # stored at that offset anywhere) mixes classes: when they
                # disagree, the max is not evidence (CameraApplyAnimSample_154400:
                # CameraBaseSetPos 0x10 vs an event object's 0x120)
                inc.append(f"scanned candidates disagree (E {', '.join(hex(v) for v in sorted(self._es))})")
            if scanned and inc and all(x.startswith("scanned candidates disagree") for x in inc):
                # every candidate measured: the census may still call the site
                # OK when even the largest stays inside the C object
                self.scan_hi = max(self.scan_hi, c + mx)
            if not (scanned and inc):
                # (a scanned set that stays open is no lower bound either: its
                # members may all be other classes)
                e = max(e, c + mx)
                wend = max(wend, c + mx) if mx else wend
            targets += [t.split(":")[-1] for t in cands[:3]]
            notes.append(("? " if inc else "") + f"{what} ({xr}=ptr+0x{c:x}): {len(cands)} targets, max E 0x{c + mx:x}"
                         + (f", incomplete: {' '.join(inc[:4])}" if inc else ""))
            done = done and not inc
        return e, done, notes, targets, wend
