#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""f32args.py: virtual / function-pointer calls whose i686 argument layout moves a float.

The EE passes integer/pointer arguments in $a0.. and f32 arguments in $f12.., two
independent register files.  A call through a vtable slot or a function pointer is
typed by the CALLER's view (devirt thunk `VCM(R, (void *, P..), soff, ..)`, a
function-pointer type); on i686 cdecl every argument is a stack word in that
order, so the callee's float sits wherever the caller's view put it.  When the
caller's view and the callee's real signature disagree on where a float goes
(`vcall-forward` appended GPR lanes in front of an f32, a slot shared by
`F(void *, f32)` and `G(void *, int, f32)`, a missing float), the callee reads an
integer as its float or the reverse.  Found 2026-10-31 (optgate): the INSECT
effect step called ModelObjExUpdate_1b02c0(this, f32 dt) through a
`(void *, int, int, int, f32)` thunk: dt read as 0, battle effects never ended.

Method (retail is the truth for which function a slot reaches):
  * port side: every devirt thunk in game/src/**/*.cpp and game/include/*.h
    (VCM / VCM0 / VCMQ / VCM_FN: slot offset S, the caller's parameter types)
    and every function-pointer type with a float parameter that a file calls;
  * retail side: the jalr sites of the file's definitions (retail listings of the
    pinned snapshot, tools/bringup/listings.py) with `lw $25, S($25)`; the vptr
    offset V (minus the `this` delta) gives the candidate vtables = every vtable
    retail code stores at +V of an object (tools/stages/sbresolve.py
    foreign_virtuals; overlay vtables read from the retail BIN files), slot S;
    plus the vtables a definition stores into its own frame objects;
  * truth: each candidate's C prototype (game/include/port/game_protos.h, else
    its C definition in game/src);
  * compare the i686 stack layout of the caller's view with the candidate's: a
    float parameter read from a word the caller filled with another lane
    (`float-misread`), a float pushed where the callee reads an integer lane
    (`float-to-int`), a callee float past the caller's last word
    (`float-missing`), f32 vs double width (`float-width`).  Integer-only
    disagreements are other censuses' business (protos_deficits, vslot).

A candidate set scanned from every vtable stored at +V mixes classes, so a row is
evidence only after review: the table REVIEWED settles each (file, slot) by hand
(OK + why, or FIXED-<how>).  Exit 1 when an unreviewed BUG-class row is left (the
ctest `census.f32args`; `--ignore-overrides` is its control: the overridden
sites come back).

    python tools/census/f32args.py [--game game] [--tsv out/f32args/f32args.tsv]
                                   [--ignore-overrides] [--all]

Original CC0 code.
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "stages"))
sys.path.insert(0, str(PORT / "tools" / "bringup"))

OVL = ("title", "insmenu", "normal", "factory", "insect")
OVL_FILES = {"title": "TITLE.BIN", "insmenu": "INSMENU.BIN", "normal": "NORMAL.BIN",
             "factory": "FACTORY.BIN", "insect": "INSECT.BIN"}
OVL_BASE = 0x004E9E80
WORK = Path("../work")
MAX_CANDS = 400

# Reviewed (file stem, slot offset) -> (verdict, why).  verdict OK = the
# disagreeing candidates are other classes / the lane is never read; FIXED-* =
# the generated code is correct now (the row only shows with --all).
REVIEWED: dict = {
    ("CharaActionKindAllowed_3b8830", "0x74"): (
        "OK", "bool predicates of the chara action-kind object (retail tests the low byte of $v0 "
              "after each jalr); EquipSlotDrainGauge* are the equip-slot class's void slot 0x74, "
              "sharing vptr +0 only by offset"),
    # ret-x87-underflow with the value discarded: the float view pops an empty ST0
    # (masked stack underflow, the x87 stack stays empty) -- harmless
    ("CharaMeterAdd_3b1640", "0x30c"): (
        "OK", "r0 = v193(..) is dead (retail returns the re-read m1E8 in $f0); the f32 view's pop of "
              "the void CharaMeterSet_3b1680 is a masked no-op"),
    ("CharaMeterAdd_3b16f0", "0x2fc"): ("OK", "as CharaMeterAdd_3b1640 (CharaMeterSet_3b1730)"),
    ("CharaMeterAdd_3b17a0", "0x2ec"): ("OK", "as CharaMeterAdd_3b1640 (CharaMeterSet_3b17e0)"),
    ("EffObjStepChannels_1a9b50", "0x18"): (
        "OK", "x64b override: the f32 view of slot 0x18 (EffCurveApply*, 19 of 20 return f32 in the "
              "D_00470A40..E00 vtables the scan does not see) drops the value; the void targets the "
              "scan does see make the pop a masked no-op"),
}

# ---------------------------------------------------------------- C types
FLOAT_T = re.compile(r"^(?:const\s+)?(?:f32|float)$")
DOUBLE_T = re.compile(r"^(?:const\s+)?(?:f64|double)$")
WIDE_T = re.compile(r"^(?:const\s+)?(?:s64|u64|long\s+long|unsigned\s+long\s+long|"
                    r"signed\s+long\s+long|__int64|int64_t|uint64_t)$")


def _split_top(s: str):
    out, dep, cur = [], 0, []
    for ch in s:
        if ch in "([{<":
            dep += 1
        elif ch in ")]}>":
            dep -= 1
        if ch == "," and dep == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur))
    return [x.strip() for x in out]


def _paren(s: str, i: int) -> int:
    """index of the ')' matching s[i] == '('."""
    d = 0
    for k in range(i, len(s)):
        if s[k] == "(":
            d += 1
        elif s[k] == ")":
            d -= 1
            if d == 0:
                return k
    return -1


def ptype_of(decl: str) -> str:
    """the type of one parameter declaration (name and default dropped)."""
    d = decl.split("=")[0].strip()
    if d in ("...",):
        return d
    if "*" in d or "&" in d or "[" in d:
        return "ptr"
    toks = d.split()
    base = {"const", "volatile", "unsigned", "signed", "long", "short", "int", "char",
            "struct", "union", "class", "enum"}
    if len(toks) > 1 and toks[-1] not in base and not FLOAT_T.match(" ".join(toks)) \
            and not DOUBLE_T.match(" ".join(toks)) and not WIDE_T.match(" ".join(toks)):
        toks = toks[:-1]           # drop the parameter name
    return " ".join(toks)


def kind(t: str) -> str:
    """i686 transport kind + EE lane class: f (f32, FPR), d (double: one GPR on the
    EE, 8 stack bytes), q (64-bit integer), v (variadic), i (4-byte GPR)."""
    t = t.strip()
    if t == "...":
        return "v"
    if t == "ptr":
        return "i"
    if FLOAT_T.match(t):
        return "f"
    if DOUBLE_T.match(t):
        return "d"
    if WIDE_T.match(t):
        return "q"
    return "i"


def layout(kinds):
    """[(stack offset, size, kind, lane)] -- lane = ('g', k) / ('f', k)."""
    out, off, g, f = [], 0, 0, 0
    for k in kinds:
        if k == "v":
            break
        sz = 8 if k in ("d", "q") else 4
        if k == "f":
            lane = ("f", f)
            f += 1
        else:
            lane = ("g", g)
            g += 1
        out.append((off, sz, k, lane))
        off += sz
    return out


def compare(caller, callee):
    """float-class disagreements between the caller's view and the callee's
    parameter kinds (both lists include `this`): [(class, detail, callee lane)]."""
    cl = {o: (sz, k, ln) for o, sz, k, ln in layout(caller)}
    nbytes = sum(8 if x in "dq" else 4 for x in caller if x != "v")
    probs = []
    for o, sz, k, ln in layout(callee):
        c = cl.get(o)
        if c is None:
            if k in ("f", "d") and "v" not in caller:
                probs.append(("float-missing", f"callee {ln[0]}{ln[1]} at +{o} past the "
                                               f"caller's {nbytes} bytes", ln))
            continue
        csz, ck, cln = c
        if k == "f" and ck == "f":
            if cln != ln:
                probs.append(("float-misread", f"callee f{ln[1]} at +{o} gets caller f{cln[1]}", ln))
        elif k == "f" and ck != "f":
            probs.append(("float-misread", f"callee f{ln[1]} at +{o} reads caller "
                                           f"{cln[0]}{cln[1]} ({ck})", ln))
        elif ck == "f" and k != "f":
            probs.append(("float-to-int", f"caller f{cln[1]} at +{o} lands in callee "
                                          f"{ln[0]}{ln[1]} ({k})", ln))
        elif (k == "d") != (ck == "d") and sz != csz:
            probs.append(("float-width", f"+{o}: callee {k} vs caller {ck}", ln))
    return probs


def entry_lanes(params):
    """argument registers a definition with these parameter types receives."""
    if params is None:
        return None
    return {lane_reg(ln) for _o, _sz, _k, ln in layout([kind(x) for x in params])}


def lane_reg(ln):
    return ("$%d" % (4 + ln[1])) if ln[0] == "g" else ("$f%d" % (12 + ln[1]))


# ---------------------------------------------------------------- port side
THUNK = re.compile(r"\bVCM(Q?)(0|_FN)?\(")


SPANS = {}


def thunks_of(text: str):
    """[(line, method, ret, ptypes, soff, variadic)] for every devirt thunk."""
    out = []
    spans = class_spans(text)
    for m in THUNK.finditer(text):
        lp = m.end() - 1
        rp = _paren(text, lp)
        if rp < 0:
            continue
        args = _split_top(text[lp + 1:rp])
        q, form = m.group(1), m.group(2) or ""
        if q:
            args = args[1:]
        try:
            if form == "0":
                ret, pts, soff = args[0], ["void *"], args[1]
            else:
                ret, pt, soff = args[0], args[1], args[2]
                pts = _split_top(pt.strip()[1:-1])
        except IndexError:
            continue
        try:
            so = int(soff, 0)
        except ValueError:
            continue
        ls = text.rfind("\n", 0, m.start()) + 1
        head = text[ls:m.start()]
        nm = re.search(r"(~?\w+)\s*\(", head)
        line = text.count("\n", 0, m.start()) + 1
        out.append((line, nm.group(1) if nm else "?", ret, pts, so, "..." in pts,
                    vptr_offset(text, spans, m.start())))
    return out


PRIM = {"u8": 1, "s8": 1, "char": 1, "bool": 1, "u16": 2, "s16": 2, "short": 2,
        "u32": 4, "s32": 4, "int": 4, "f32": 4, "float": 4, "long": 4, "unsigned": 4,
        "vc_u32": 4, "u64": 8, "s64": 8, "f64": 8, "double": 8, "u128": 16, "s128": 16}


def _eval(e):
    if not re.fullmatch(r"[0-9a-fA-FxX+\-*/() ]+", e):
        return None
    try:
        return int(eval(e, {"__builtins__": {}}))
    except Exception:
        return None


def class_spans(text: str):
    """{class name: (open brace, close brace, base names)}"""
    out = {}
    for m in re.finditer(r"\b(?:class|struct)\s+(\w+)\s*(?::\s*([^{;]*))?\{", text):
        o = m.end() - 1
        d, k = 0, o
        while k < len(text):
            if text[k] == "{":
                d += 1
            elif text[k] == "}":
                d -= 1
                if d == 0:
                    break
            k += 1
        bases = [b.split()[-1] for b in (m.group(2) or "").split(",") if b.strip()]
        out.setdefault(m.group(1), (o, k, bases))
    return out


def data_size(text, spans, body: str, depth=0):
    """byte size of simple data members (pads / scalars / arrays), else None."""
    n = 0
    for decl in body.split(";"):
        d = re.sub(r"(public|private|protected)\s*:", "", decl).strip()
        if not d:
            continue
        m = re.fullmatch(r"(?:unsigned\s+|signed\s+)?(\w+)\s*\**\s*(\w+)\s*((?:\[[^\]]+\]\s*)*)", d)
        if not m:
            return None
        sz = 4 if "*" in d else PRIM.get(m.group(1))
        if sz is None:
            return None
        for dim in re.findall(r"\[([^\]]+)\]", m.group(3)):
            v = _eval(dim)
            if v is None:
                return None
            sz *= v
        n += sz
    return n


def class_size(text, spans, name, depth=0):
    sp = spans.get(name)
    if sp is None or depth > 4:
        return None
    o, c, bases = sp
    n = 0
    for b in bases:
        bs = class_size(text, spans, b, depth + 1)
        if bs is None:
            return None
        n += bs
    ds = data_size(text, spans, text[o + 1:c])
    return None if ds is None else n + ds


def vptr_offset(text, spans, pos):
    """vptr offset of the class whose body holds position pos, else None."""
    best = None
    for nm, (o, c, bases) in spans.items():
        if o < pos < c and (best is None or o > spans[best][0]):
            best = nm
    if best is None:
        return None

    def vo(nm, depth=0):
        o, c, bases = spans[nm]
        body = text[o + 1:c]
        k = body.find("VC_VPTR_MEMBER")
        n = 0
        for b in bases:
            if b in spans and "VC_VPTR_MEMBER" in text[spans[b][0]:spans[b][1]] and depth < 4:
                return vo(b, depth + 1)
            bs = class_size(text, spans, b)
            if bs is None:
                return None
            n += bs
        if k < 0:
            return None
        pre = body[:k]
        ds = data_size(text, spans, pre[:pre.rfind(";") + 1] if ";" in pre else "")
        return None if ds is None else n + ds
    return vo(best)


BSN = chr(10)
BSL = chr(92)
FNPTR = re.compile(r"\(\s*\*\s*(\w*)\s*\)\s*\(([^()]*)\)")


def defs_of(text: str):
    """names of the game-symbol functions the file defines."""
    return sorted(set(m.group(1) for m in re.finditer(
        r"\b(\w+_[0-9A-Fa-f]{6}(?:_e\d+)?)\s*\([^;{}]*\)\s*(?:const\s*)?\{", text)))


def image_of(rel: str) -> str:
    m = re.match(r"src/overlays/(\w+)/", rel)
    return m.group(1) if m else "main"


RET = {}      # name -> return kind (v / i / f / d / q): game_protos.h, then the C definitions


def ret_kind(t: str) -> str:
    """return kind of a declaration's text in front of the name."""
    t = re.sub(r'\b(extern|static|inline|__inline)\b|"C"', " ", t)
    t = " ".join(t.split())
    if t == "void":
        return "v"
    if "*" in t:
        return "i"
    k = kind(t)
    return k if k in ("f", "d", "q") else "i"


def protos_index(game: Path):
    """{name: [param types]} from game_protos.h, then the C definitions."""
    P = {}
    hp = game / "include" / "port" / "game_protos.h"
    for ln in hp.read_text("latin-1").splitlines():
        m = re.match(r"^\s*((?:extern\s+\"C\"\s+)?[^#/(]*?)\b(\w+)\s*\((.*)\)\s*;\s*$", ln)
        if m:
            ps = _split_top(m.group(3)) if m.group(3).strip() not in ("", "void") else []
            P[m.group(2)] = [ptype_of(p) for p in ps]
            RET[m.group(2)] = ret_kind(m.group(1))
    return P


def def_proto(game: Path, name: str, cache={}):
    """param types of name's C definition in game/src (by file name), or None."""
    if name in cache:
        return cache[name]
    r = None
    for p in list((game / "src").rglob(f"{name}.c")) + list((game / "src").rglob(f"{name}.cpp")):
        t = p.read_text("latin-1")
        m = re.search(r"([^;{}()]*?)\b%s\s*\(([^;{}]*)\)\s*\{" % re.escape(name), t)
        if m:
            ps = _split_top(m.group(2)) if m.group(2).strip() not in ("", "void") else []
            r = [ptype_of(x) for x in ps]
            RET.setdefault(name, ret_kind(m.group(1).strip().splitlines()[-1] if m.group(1).strip() else "int"))
            break
    cache[name] = r
    return r


# ---------------------------------------------------------------- retail side
class Retail:
    """The protos stage's resolver (tools/stages/sbresolve.py) over the pinned
    listings, with overlay vtable words read from the retail BIN files."""

    def __init__(self, game: Path):
        import listings
        import protos
        import sbresolve
        self.st = protos.ProtoStage()
        self.st.addr_table = listings.table()
        self.flow = self.st._flow()
        texts = {"src/main_data/" + p.name: p.read_text("latin-1")
                 for p in (game / "src" / "main_data").glob("data2c_*.c")}
        W, T = sbresolve.data_words(texts)
        self.R = sbresolve.Resolver(self.st, self.flow, W, T)
        self.bins = {ov: (WORK / "BIN" / fn).read_bytes() for ov, fn in OVL_FILES.items()
                     if (WORK / "BIN" / fn).exists()}
        self.R.ovl_word = self.ovl_word
        self.game = game

    def ovl_word(self, img, a):
        b = self.bins.get(img)
        o = a - OVL_BASE
        if b is None or o < 0 or o + 4 > len(b):
            return None
        return struct.unpack_from("<I", b, o)[0]

    def jalrs(self, img, fn):
        """[(insn, V, S)] of the vtable jalrs of listing img:fn."""
        cfg = self.flow.cfg(f"{img}:{fn}")
        if cfg is None:
            return []
        out = []
        for j, (op, ops) in enumerate(cfg.ins):
            if op in ("jalr", "jr") and ops and ops[-1] != "$31":
                vs = self.R.vcall_site(f"{img}:{fn}", j)
                if vs is not None:
                    out.append((j, vs[0], vs[1]))
        return out


def vtable_majority(R, S):
    """([(fn, kind)], note) of the x87-returning functions at slot S when more
    than half of the vtables long enough for it (data2c tables starting with the
    two zero header words) hold one there, else ([], "")."""
    n_tab, ex = 0, set()
    for sym, (a, n) in R.R.T.items():
        if n <= S // 4 or n < 3:
            continue
        if R.R.W.get(a) != ("int", 0) or R.R.W.get(a + 4) != ("int", 0):
            continue
        w = R.R.W.get(a + S)
        if not w or w[0] != "fn":
            continue
        n_tab += 1
        if RET.get(w[1]) is None:
            def_proto(R.game, w[1])
        if RET.get(w[1]) in ("f", "d"):
            ex.add((w[1], RET[w[1]]))
    nx = sum(1 for sym, (a, n) in R.R.T.items()
             if n > S // 4 and R.R.W.get(a) == ("int", 0) and R.R.W.get(a + 4) == ("int", 0)
             and (R.R.W.get(a + S) or ("", ""))[0] == "fn" and RET.get(R.R.W[a + S][1]) in ("f", "d"))
    if n_tab and nx * 2 > n_tab:
        return sorted(ex), f"{nx} of {n_tab} vtables hold an x87 return at slot 0x{S:x}"
    return [], ""


# ---------------------------------------------------------------- census
def overridden(rel: str, ovr: Path) -> bool:
    return (ovr / rel).exists()


def run(game: Path, ovr: Path, ignore_ovr: bool, want_all: bool, control: bool = False):
    P = protos_index(game)
    R = Retail(game)
    rows = []
    hdr_thunks = {}
    for h in (game / "include").glob("*.h"):
        t = h.read_text("latin-1")
        if "VCM" in t:
            hdr_thunks[h.name] = thunks_of(t)

    def row(**kw):
        rows.append(kw)

    for p in sorted((game / "src").rglob("*.cpp")):
        rel = str(p.relative_to(game)).replace("\\", "/")
        text = p.read_text("latin-1")
        if ovr.exists() and not ignore_ovr and overridden(rel, ovr):
            # an override replaces the generated file: judge the override's text
            text = (ovr / rel).read_text("latin-1")
        th = [(rel,) + x for x in thunks_of(text)]
        if control:
            # control: the slot calls typed GPR-first, f32 last (devirt before the
            # vcall-target-lanes order; the overrides ignored)
            th = [x[:4] + ([t for t in x[4] if kind(ptype_of(t)) != "f"] +
                           [t for t in x[4] if kind(ptype_of(t)) == "f"],) + x[5:] for x in th]
        for hn, hts in hdr_thunks.items():
            if re.search(r'#\s*include\s*"%s"' % re.escape(hn), text):
                for x in hts:
                    if re.search(r"(?:->|\.)\s*%s\s*\(" % re.escape(x[1]), text):
                        th.append((f"include/{hn}",) + x)
        if not th:
            continue
        img = image_of(rel)
        jal = defaultdict(set)
        for d in defs_of(text):
            for j, V, S in R.jalrs(img, d):
                jal[S].add((d, V, j))
        for (where, line, meth, ret, pts, soff, va, cv) in th:
            ck = [kind(ptype_of(x)) for x in pts]
            sites = jal.get(soff) or set()
            if cv is not None:
                # the thunk's class puts its vptr at +cv: only those jalrs
                sites = {x for x in sites if x[1] == cv}
            base = dict(file=rel, where=f"{where}:{line}", method=meth, soff=hex(soff),
                        caller="(" + ", ".join(pts) + ")")
            # the view's return kind (x87: f / d come back in ST0 on i686)
            tret = "i" if ret.startswith("vc_u") else ret_kind(ret)
            if control and tret in ("f", "d"):
                tret = "v"     # control: the x87 views typed void again (before vcall-x87-return)
            if len(pts) > 1 and "*" in pts[0] and pts[1].replace(" ", "") == "void*" \
                    and pts[0].replace(" ", "") != "void*":
                tret = None         # struct return through the hidden result pointer
            if not sites and tret in ("v", "i", "q") and not va:
                # no retail jalr paired: the vtables long enough for the slot decide
                x87, maj = vtable_majority(R, soff)
                if x87 and re.search(r"(?:->|\.)\s*%s\s*\(" % re.escape(meth), text):
                    row(**base, target=" ".join(c for c, _k in x87), callee=f"returns {x87[0][1]}",
                        cls="ret-x87-leak" if tret == "v" else "ret-x87-int",
                        detail=f"view returns {ret}; no retail jalr paired; {maj}", verdict="BUG?")
            for d, V, j in sorted(sites):
                rets = []
                el = entry_lanes(P.get(d) or def_proto(game, d))
                tg = R.R.vcall_targets(f"{img}:{d}", j, V, soff, el)
                if len(tg) > MAX_CANDS:
                    if "f" in ck or tret in ("f", "d"):
                        row(**base, target=f"{len(tg)} candidates", callee="-", cls="unresolved",
                            detail=f"{d}@{j} vptr +0x{V:x}: too many candidate vtables",
                            verdict="needs-review")
                    continue
                for lst, rd, ok, why in tg:
                    if not ok and not want_all:
                        continue
                    timg, _c, cn = lst.partition(":")
                    cn = cn.split("@")[0]
                    tp = P.get(cn) or def_proto(game, cn)
                    if tp is None:
                        if "f" in ck:
                            row(**base, target=cn, callee="?", cls="no-proto",
                                detail=f"{d}@{j} vptr +0x{V:x}; {why}", verdict="needs-review")
                        continue
                    tk = [kind(x) for x in tp]
                    if ok:
                        rets.append((cn, RET.get(cn, "?")))
                    if va:
                        if any(k in "fd" for k in tk):
                            row(**base, target=cn, callee="(" + ", ".join(tp) + ")", cls="variadic-float",
                                detail=f"variadic slot (an f32 argument is promoted to double); "
                                       f"{d}@{j} vptr +0x{V:x}; {why}", verdict="needs-review")
                        continue
                    for cls, det, ln in compare(ck, tk):
                        reg = lane_reg(ln)
                        read = None if rd is None else (reg in rd)
                        if read is False and not want_all:
                            continue        # the callee never reads that lane
                        st = R.R.lane_state(f"{img}:{d}", j, reg)
                        row(**base, target=cn, callee="(" + ", ".join(tp) + ")", cls=cls,
                            detail=f"{det}; retail site {d}@{j} vptr +0x{V:x}: {reg} {st}; {cn} {why}",
                            verdict=("BUG?" if ok else "OK-implausible") if read is not False
                            else "OK-unread")
                # ---- return side (x64b lane 2026-11-01: EffObjStepChannels_1a9b50)
                if tret is None or not rets:
                    continue
                own = any(c == d for c, _k in rets)
                if own:
                    # the slot is the caller's own listing (an interior entry): its class
                    rets = [(c, k) for c, k in rets if c == d]
                x87 = sorted({(c, k) for c, k in rets if k in ("f", "d")})
                other = sorted({(c, k) for c, k in rets if k in ("i", "q")})
                maj = ""
                if not x87 and not other and tret in ("v", "i", "q") and not own:
                    # no retail target returns a value: the vtables long enough for the
                    # slot (as the protos rule vcall-x87-return)
                    x87, maj = vtable_majority(R, soff)
                    rets = rets + list(x87)
                kinds = ",".join(f"{c}={k}" for c, k in sorted(set(rets)))
                # retail evidence: which result register the caller reads after the jalr
                import asmflow
                cfg = R.flow.cfg(f"{img}:{d}")
                f0 = asmflow.reg_after_call(cfg, j, "$f0")
                v0 = asmflow.reg_after_call(cfg, j, "$2")
                ev = f"retail caller after the jalr: $f0 {f0}, $v0 {v0}" + (f"; {maj}" if maj else "")
                if tret in ("v", "i", "q") and x87:
                    # strong: every non-void plausible target returns in ST0, and the
                    # retail caller does not read $v0 as the result
                    strong = not other and v0 != "read"
                    row(**base, target=" ".join(c for c, _k in x87), callee=f"returns {x87[0][1]}",
                        cls="ret-x87-leak" if tret == "v" else "ret-x87-int",
                        detail=f"view returns {ret}; {len(x87)} of {len(set(rets))} plausible targets return "
                               f"in ST0 (never popped: the 9th call overflows the x87 stack); {ev}; "
                               f"{d}@{j} vptr +0x{V:x}; {kinds}",
                        verdict="BUG?" if strong else "OK-implausible (mixed classes / $v0 read)")
                elif tret in ("f", "d") and not x87 and all(k != "?" for _c, k in rets):
                    row(**base, target=" ".join(sorted({c for c, _k in rets})), callee="no x87 return",
                        cls="ret-x87-underflow",
                        detail=f"view returns {ret} but no plausible target returns in ST0 (the caller "
                               f"reads an empty register); {ev}; {d}@{j} vptr +0x{V:x}; {kinds}",
                        verdict="OK-implausible ($f0 read: the target set is another class)"
                        if f0 == "read" else "BUG?")
    # ---- function-pointer types with a float parameter (C and C++)
    for p in sorted((game / "src").rglob("*.c*")):
        text = p.read_text("latin-1")
        if "(*" not in text:
            continue
        rel = str(p.relative_to(game)).replace("\\", "/")
        for m in FNPTR.finditer(text):
            pts = _split_top(m.group(2)) if m.group(2).strip() not in ("", "void") else []
            ck = [kind(ptype_of(x)) for x in pts]
            if not any(k in "fd" for k in ck):
                continue
            nm = m.group(1)
            line = text.count(BSN, 0, m.start()) + 1
            base = dict(file=rel, where=f"{rel}:{line}", method=nm or "?", soff="-",
                        caller="(" + ", ".join(pts) + ")")
            tdef = re.search(r"\btypedef\b[^;]*$", text[:m.start()].rsplit(";", 1)[-1])
            if tdef and nm:
                # tables declared with the typedef: every entry's prototype
                tabs = re.findall(r"\bextern\s+%s\s+(D_[0-9A-Fa-f]+)" % re.escape(nm), text)
                if not tabs:
                    continue
                for sym in tabs:
                    a_n = R.R.T.get(sym)
                    if a_n is None:
                        row(**base, target=sym, callee="?", cls="fnptr-unresolved",
                            detail="table words not in the tree", verdict="needs-review")
                        continue
                    a, n = a_n
                    for i in range(n):
                        w = R.R.W.get(a + 4 * i)
                        if not w or w[0] != "fn":
                            continue
                        tp = P.get(w[1]) or def_proto(game, w[1])
                        if tp is None:
                            continue
                        for cls, det, ln in compare(["i"] * 0 + ck, [kind(x) for x in tp]):
                            row(**base, target=w[1], callee="(" + ", ".join(tp) + ")", cls=cls,
                                detail=f"{det}; table {sym}[{i}]", verdict="BUG?")
                continue
            # a struct member: only a member the file calls matters
            calls = list(re.finditer(
                r"(?:->|\.)\s*%s\s*\(|\(\s*\*\s*[\w>.-]+(?:->|\.)%s\s*\)\s*\("
                % (re.escape(nm), re.escape(nm)), text)) if nm else []
            # a same-named method of another class (a devirt thunk) is not this member
            thunk_names = {x[1] for x in thunks_of(text)}
            if calls and nm not in thunk_names:
                row(**base, target="-", callee="-", cls="fnptr-call",
                    detail="called function pointer with a float parameter: targets not resolved",
                    verdict="needs-review")
    # reviewed verdicts
    for r in rows:
        stem = Path(r["file"]).stem
        rv = REVIEWED.get((stem, r["soff"], r.get("target"))) or REVIEWED.get((stem, r["soff"]))
        if rv and r["verdict"] in ("BUG?", "needs-review"):
            r["verdict"], r["why"] = rv
    return rows, R


COLS = ["file", "where", "method", "soff", "caller", "target", "callee", "cls", "detail", "verdict", "why"]


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--overrides", default=str(PORT / "overrides"))
    ap.add_argument("--ignore-overrides", action="store_true")
    ap.add_argument("--all", action="store_true", help="also the reviewed OK / FIXED rows")
    ap.add_argument("--control", action="store_true",
                    help="ctest control: thunks re-typed GPR-first, overrides ignored (must fail)")
    ap.add_argument("--tsv")
    a = ap.parse_args(argv)
    rows, R = run(Path(a.game), Path(a.overrides), a.ignore_overrides or a.control, a.all,
                  a.control)
    if a.tsv:
        Path(a.tsv).parent.mkdir(parents=True, exist_ok=True)
        with open(a.tsv, "w", encoding="utf-8", newline="\n") as fh:
            fh.write("\t".join(COLS) + "\n")
            for r in rows:
                fh.write("\t".join(str(r.get(c, "")) for c in COLS) + "\n")
    bad = [r for r in rows if not r["verdict"].startswith(("OK", "FIXED"))]
    show = rows if a.all else bad
    for r in show:
        print("\t".join(str(r.get(c, "")) for c in COLS))
    print(f"f32args: {len(rows)} rows, {len(bad)} open "
          f"({len({(r['file'], r['soff']) for r in bad})} sites)", file=sys.stderr)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
