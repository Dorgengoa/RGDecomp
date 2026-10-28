#!/usr/bin/env python3
"""Transform 3: de-virtualise the decomp's dummy classes (PLAN.md transform 3,
probes/vtable/README.md "Design B", docs/DEVIRT.md), plus the C/C++ linkage
fixes that let .cpp game code bind to C definitions on i686.

Runs after `dialect`, before `spin`.  Per C++ file (and per `include/*.h`
that declares virtuals):

  vptr        the root polymorphic class's FIRST virtual declaration becomes
              `VC_VPTR_MEMBER;` (vc_u32 __vptr) at the same position, so the
              class is non-dynamic and clang lays it out in declaration order
              (mwcc: vptr after the data declared before the first virtual).
  slots       root virtuals are numbered in declaration order; a derived class
              starts from its primary (first polymorphic) base's table, an
              exact redeclaration (same name + parameter types, C++ override
              rule) keeps the base slot, a new virtual gets base_count + i.
  thunks      a virtual whose name is referenced in the TU becomes an inline
              cdecl thunk dispatching through the game's own vtable at byte
              offset SOFF = 8 + 4*slot (port/vcall.h VCM*); unreferenced
              placeholders are deleted.  bool returns narrow the low byte;
              struct returns pass the result pointer first and `this` second;
              `f(...)` becomes a variadic template forwarding through a
              `(void *, ...)` slot type (default promotions as on mwcc).
              Overrides (same return type) are dropped: the base thunk serves
              them.  Overrides of a SECONDARY base's virtual are dropped too:
              the base thunk dispatches through that sub-object's vptr.
  linkage     (a) game-symbol function definitions (`*_xxxxxx`) in C++
              linkage, and their earlier namespace-scope declarations, get
              `extern "C"`;  (b) namespace-scope `extern` data declarations
              get `extern "C"`;  block-scope `extern` data declarations get a
              namespace-scope `extern "C"` twin in front of the enclosing
              function (a block-scope redeclaration inherits its linkage).

Line numbers are preserved (each rewritten member keeps its newlines).
Idempotent: the output has no `virtual` and every rewritten name is already
C-linkage.  Every class/slot/thunk is a row of game/DEVIRT.tsv, the table the
retail cross-check (tools/devirt_verify.py) reads.
"""
from __future__ import annotations

import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from portxform import blank, blank_pp, match_close, find_funcs  # noqa: E402

HEAD = re.compile(r"\b(class|struct)\s+([A-Za-z_]\w*)\s*(?::(?!:)\s*([^{;()]*?))?\s*\{")
ACCESS = re.compile(r"(public|private|protected)\s*:(?!:)")
IDENT = re.compile(r"[A-Za-z_]\w*")
GAME_SYM = re.compile(r"^[A-Za-z_]\w*_[0-9a-fA-F]{6,8}$")
CV = {"const", "volatile", "struct", "class", "union", "enum", "typename"}
BUILTIN = {"void", "bool", "char", "short", "int", "long", "unsigned", "signed",
           "float", "double", "wchar_t", "__int64", "_Bool"}
SCALAR_TYPEDEFS = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32",
                   "f64", "size_t", "vc_u32", "vc_u8", "rg_u128", "rg_s128",
                   "u128", "s128", "uintptr_t", "intptr_t", "BOOL", "uint", "ulong"}
# canonical spelling for signature comparison (types.h)
CANON = {"s8": "signed char", "u8": "unsigned char", "s16": "short",
         "u16": "unsigned short", "s32": "int", "u32": "unsigned int",
         "s64": "long long", "u64": "unsigned long long", "f32": "float",
         "f64": "double", "unsigned": "unsigned int", "signed": "int",
         "short int": "short", "unsigned short int": "unsigned short"}


def _ws(s: str) -> str:
    return " ".join(s.split())


@dataclass
class Param:
    decl: str          # declaration with a name (named or a0..)
    ptype: str         # type only
    name: str
    default: str = ""  # ` = expr` text or ""


@dataclass
class Method:
    name: str
    ret: str
    params: list
    variadic: bool
    quals: str          # trailing `const` etc.
    key: tuple          # (name, canonical param types, variadic)
    lo: int             # member span in the text
    hi: int
    is_virtual: bool
    slot: int = -1
    owner: str = ""     # class whose vptr dispatches it
    vq: str = ""        # qualifier for this->Q::__vptr ("" = unqualified)


@dataclass
class Klass:
    name: str
    head: int
    open: int
    close: int
    bases: list
    is_struct: bool
    local: bool = False
    methods: list = field(default_factory=list)     # Method (virtual / candidate)
    members: list = field(default_factory=list)     # (lo, hi, kind, access)
    poly: bool = False
    root: bool = False
    slots: list = field(default_factory=list)       # [(key, name, ret_canon)]
    primary: "Klass | None" = None
    poly_bases: list = field(default_factory=list)
    ctor: bool = False
    from_header: str = ""


def split_top(s: str, sep: str = ",") -> list[tuple[int, int]]:
    out, depth, lo = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([{<":
            depth += 1
        elif ch in ")]}>":
            depth -= 1
        elif ch == sep and depth == 0:
            out.append((lo, i))
            lo = i + 1
    out.append((lo, len(s)))
    return out


def canon_type(t: str) -> str:
    t = _ws(re.sub(r"\s*([*&\[\]])\s*", r" \1 ", t))
    toks = []
    for w in t.split():
        if w in ("struct", "class", "union", "enum", "typename"):
            continue
        toks.append(w)
    t = " ".join(toks)
    for k in sorted(CANON, key=len, reverse=True):
        t = re.sub(r"(?<![\w])" + re.escape(k) + r"(?![\w])", CANON[k], t)
    return _ws(t)


def parse_params(ptext: str, raw: str) -> tuple[list, bool, list]:
    """(params, variadic, problems).  ptext is blanked, raw the original
    (default arguments may hold string literals)."""
    params, variadic, probs = [], False, []
    if not ptext.strip() or ptext.strip() == "void":
        return params, False, probs
    for i, (lo, hi) in enumerate(split_top(ptext)):
        p = ptext[lo:hi]
        praw = raw[lo:hi]
        ps = p.strip()
        if ps == "...":
            variadic = True
            continue
        default = ""
        eq = [k for k, ch in enumerate(p) if ch == "=" and _depth0(p, k)]
        if eq:
            default = " =" + praw[eq[0] + 1:].rstrip()
            p = p[:eq[0]]
            praw = praw[:eq[0]]
        d = _ws(p)
        fp = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)?\s*\)", d)
        if fp:
            if fp.group(1):
                name = fp.group(1)
                ptype = d[:fp.start()] + "(*)" + d[fp.end():]
                decl = d
            else:
                name = f"a{i}"
                ptype = d
                decl = d[:fp.start()] + f"(*{name})" + d[fp.end():]
        else:
            m = re.match(r"^(.*?)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$", d)
            ids = [x for x in IDENT.findall(re.sub(r"\[[^\]]*\]", "", d)) if x not in CV]
            named = (m is not None and len(ids) >= 2 and ids[-1] not in BUILTIN
                     and ids[-1] not in SCALAR_TYPEDEFS)
            if named:
                name = m.group(2)
                ptype = _ws(m.group(1) + m.group(3))
                decl = d
            else:
                name = f"a{i}"
                ptype = d
                if "[" in d:
                    k = d.index("[")
                    decl = d[:k] + f" {name}" + d[k:]
                else:
                    decl = f"{d} {name}"
            if "&" in ptype and "(" in ptype:
                probs.append("param-fnref")
        params.append(Param(decl, ptype, name, default))
    return params, variadic, probs


def _depth0(s: str, k: int) -> bool:
    d = 0
    for ch in s[:k]:
        if ch in "([{<":
            d += 1
        elif ch in ")]}>":
            d -= 1
    return d == 0


def split_members(code: str, lo: int, hi: int, is_struct: bool):
    """[(start, end, access)] of the member declarations in code[lo:hi]
    (end exclusive, includes the `;` or the closing `}` of an inline body).
    Access labels are consumed and not part of any member."""
    out = []
    access = "public" if is_struct else "private"
    i = lo
    n = hi
    while i < n:
        while i < n and code[i] in " \t\r\n;":
            i += 1
        if i >= n:
            break
        m = ACCESS.match(code, i)
        if m and m.end() <= n:
            access = m.group(1)
            i = m.end()
            continue
        start = i
        depth = 0
        first_brace = -1
        end = n
        while i < n:
            ch = code[i]
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
            elif ch == "{":
                if depth == 0 and first_brace < 0:
                    first_brace = i
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0 and first_brace >= 0:
                    pre = code[start:first_brace].rstrip()
                    pre = re.sub(r"\b(const|throw\s*\(\s*\))\s*$", "", pre).rstrip()
                    is_fn = pre.endswith(")") or re.search(r"\)\s*:(?!:)", pre) is not None
                    if is_fn and "=" not in pre.split("(")[0]:
                        end = i + 1
                        break
            elif ch == ";" and depth == 0:
                end = i + 1
                break
            i += 1
        out.append((start, end, access))
        i = end
    return out


def sig_of(code: str, raw: str, lo: int, hi: int):
    """Parse a member function declaration/definition.  Returns
    (name, ret, params, variadic, quals, is_virtual, problems) or None when
    the member is not a function."""
    t = code[lo:hi]
    # header = up to body `{` or `;` (depth 0)
    depth, end = 0, len(t)
    for k, ch in enumerate(t):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif depth == 0 and ch in "{;":
            end = k
            break
    h = t[:end]
    hs = h.rstrip()
    hs = re.sub(r"=\s*0\s*$", "", hs).rstrip()
    ci = re.search(r"\)\s*:(?!:)", hs)
    if ci:
        hs = hs[:ci.start() + 1]
    qm = re.search(r"\)((?:\s*(?:const|volatile|throw\s*\(\s*\)))*)\s*$", hs)
    if not qm:
        return None
    quals = _ws(qm.group(1))
    close = qm.start()
    # matching open paren
    d = 0
    o = -1
    for k in range(close, -1, -1):
        if hs[k] == ")":
            d += 1
        elif hs[k] == "(":
            d -= 1
            if d == 0:
                o = k
                break
    if o < 0:
        return None
    nm = re.search(r"(~?[A-Za-z_]\w*|operator\s*\S+)\s*$", hs[:o])
    if not nm:
        return None
    pre = hs[:nm.start()]
    if re.search(r"\(\s*\*\s*$", pre):
        return None                      # data: function pointer
    is_virtual = re.search(r"\bvirtual\b", pre) is not None
    ret = _ws(re.sub(r"\b(virtual|inline|__inline|static|explicit)\b", " ", pre))
    ret = _ws(re.sub(r"__attribute__\s*\(\(.*?\)\)", " ", ret))
    params, variadic, probs = parse_params(hs[o + 1:close], raw[lo + o + 1:lo + close])
    return nm.group(1), ret, params, variadic, quals, is_virtual, probs


class DevirtStage:
    name = "devirt"

    def __init__(self) -> None:
        self.stats: dict[str, int] = {}
        self.rows: list[tuple] = []          # DEVIRT.tsv
        self.errors: list[tuple[str, str]] = []
        self.flags: list[tuple[str, str, str]] = []   # (file, what, detail)
        self.headers: dict[str, dict] = {}   # basename -> {name: Klass}
        self.header_text: dict[str, str] = {}

    def _bump(self, k: str, n: int = 1) -> None:
        self.stats[k] = self.stats.get(k, 0) + n

    # ---------------------------------------------------------------- hooks
    def prepare(self, files: dict[str, bytes]) -> None:
        for p, d in files.items():
            if p.startswith("include/") and p.endswith(".h") and b"virtual" in d:
                text = d.decode("utf-8", "surrogateescape")
                code = blank_pp(blank(text))
                if not re.search(r"\bvirtual\b", code):
                    continue
                classes = self.parse_classes(p, text, code, {})
                self.headers[p.rsplit("/", 1)[1]] = classes

    def extra_outputs(self) -> dict[str, bytes]:
        lines = ["# devirt: one row per (class, slot thunk) -- tools/stages/devirt.py",
                 "file\tline\tclass\tvptr_owner\tvq\tmethod\tslot\tsoff\tret\tkind\temitted"]
        for r in sorted(self.rows):
            lines.append("\t".join(str(x) for x in r))
        flags = ["file\twhat\tdetail"] + ["\t".join(f) for f in sorted(set(self.flags))]
        return {"DEVIRT.tsv": ("\n".join(lines) + "\n").encode(),
                "DEVIRT_FLAGS.tsv": ("\n".join(flags) + "\n").encode()}

    def report(self) -> str:
        by: dict[str, int] = {}
        for f in set(self.flags):
            by[f[1]] = by.get(f[1], 0) + 1
        return ("devirt flags: " + (", ".join(f"{k}={v}" for k, v in sorted(by.items())) or "-")
                + (f"\ndevirt ERRORS: {len(self.errors)} " + str(self.errors[:10]) if self.errors else ""))

    # ---------------------------------------------------------------- parse
    def parse_classes(self, path: str, text: str, code: str, seed: dict) -> dict:
        funcs = [f for f in find_funcs(code) if not f.in_class]
        bodies = [(f.body_open, f.body_close) for f in funcs]
        classes: dict[str, Klass] = dict(seed)
        order: list[Klass] = []
        for m in HEAD.finditer(code):
            o = m.end() - 1
            c = match_close(code, o)
            bases = []
            if m.group(3):
                for b in m.group(3).split(","):
                    b = _ws(re.sub(r"\b(public|private|protected|virtual)\b", "", b))
                    if b:
                        bases.append(b)
            k = Klass(m.group(2), m.start(), o, c, bases, m.group(1) == "struct")
            k.local = any(lo < m.start() < hi for lo, hi in bodies)
            order.append(k)
        # members; lexical resolution: a base name binds to the latest class of
        # that name declared before the derived class head
        latest: dict[str, Klass] = dict(seed)
        for k in sorted(order, key=lambda x: x.head):
            for (lo, hi, acc) in split_members(code, k.open + 1, k.close, k.is_struct):
                kind = "data"
                sig = None
                head = code[lo:hi].lstrip()
                if not re.match(r"(typedef|friend|using|enum|static\b(?![^;{]*\bvirtual))", head) \
                        and not re.match(r"(struct|class|union)\b[^;(]*\{", head):
                    sig = sig_of(code, text, lo, hi)
                if sig is not None:
                    name, ret, params, variadic, quals, isv, probs = sig
                    kind = "virtual" if isv else "method"
                    if name == k.name or name == "~" + k.name:
                        k.ctor = True
                        kind = "ctor"
                    for pr in probs:
                        self.flags.append((path, pr, f"{k.name}::{name}"))
                    key = (name, tuple(canon_type(p.ptype) for p in params), variadic)
                    if kind in ("virtual", "method"):
                        k.methods.append(Method(name, ret, params, variadic, quals, key,
                                                lo, hi, isv))
                k.members.append((lo, hi, kind, acc))
            k.bases = [latest.get(b, b) for b in k.bases]
            latest[k.name] = k
            classes[k.name + f"@{k.head}"] = k
        # resolve polymorphism / slots in declaration order
        for k in sorted(order, key=lambda x: x.head):
            self._resolve(path, k)
        out = {}
        for k in order:
            out[k.name] = k   # last wins (only used to seed header classes)
        self._order = order
        return out

    def _resolve(self, path: str, k: Klass) -> None:
        k.poly_bases = [b for b in k.bases if isinstance(b, Klass) and b.poly]
        unknown = [b for b in k.bases if not isinstance(b, Klass)]
        own_virt = [m for m in k.methods if m.is_virtual]
        if unknown and own_virt:
            self.flags.append((path, "unknown-base", f"{k.name}: {unknown}"))
        if not k.poly_bases and not own_virt:
            return
        k.poly = True
        if not k.poly_bases:
            k.root = True
            k.slots = []
            for m in own_virt:
                m.slot = len(k.slots)
                m.owner = k.name
                k.slots.append((m.key, m.name, canon_type(m.ret), k))
            # implicit virtuals: none (no base)
            for m in k.methods:
                if not m.is_virtual:
                    m.slot = -2       # plain method, untouched
            return
        p = k.poly_bases[0]
        k.primary = p
        k.slots = list(p.slots)
        multi = len(k.poly_bases) > 1
        if multi:
            self.flags.append((path, "multiple-polymorphic-bases",
                               f"{k.name}: {[b.name for b in k.poly_bases]}"))
        if any(isinstance(b, Klass) and not b.poly for b in k.bases[:k.bases.index(p)]):
            self.flags.append((path, "pad-base-before-polymorphic-base", k.name))
        for m in k.methods:
            hit = next((i for i, s in enumerate(k.slots) if s[0] == m.key), None)
            sec = None
            if hit is None and multi:
                for b in k.poly_bases[1:]:
                    j = next((i for i, s in enumerate(b.slots) if s[0] == m.key), None)
                    if j is not None:
                        sec = (b, j)
                        break
            if hit is not None:
                m.slot = hit
                m.owner = k.slots[hit][3].name
                m.is_virtual = True
                if canon_type(m.ret) == k.slots[hit][2]:
                    m.slot = -3       # exact override: dropped
                    self._bump("override_dropped")
                else:
                    self.flags.append((path, "covariant-override", f"{k.name}::{m.name}"))
            elif sec is not None:
                m.is_virtual = True
                m.slot = -3
                self.flags.append((path, "mi-secondary-override",
                                   f"{k.name}::{m.name} -> {sec[0].name} slot {sec[1]}"))
                self._bump("override_dropped")
            elif m.is_virtual:
                m.slot = len(k.slots)
                m.owner = k.name
                k.slots.append((m.key, m.name, canon_type(m.ret), k))
                self._bump("derived_new_virtual")
                self.flags.append((path, "derived-new-virtual",
                                   f"{k.name}::{m.name} slot {m.slot} (base {p.name} has {len(p.slots)})"))
            else:
                m.slot = -2
        if multi:
            # this->P::__vptr for every thunk of this class (two __vptr members)
            for m in k.methods:
                if m.slot >= 0:
                    m.vq = p.name

    # ---------------------------------------------------------------- emit
    def thunk(self, k: Klass, m: Method, struct_names: set, scalar_names: set,
              path: str) -> str:
        soff = f"0x{8 + 4 * m.slot:X}"
        ret = m.ret
        q = m.vq
        # EE lanes: f32 arguments ride $f12.., every other one $a0..; only the
        # order within each lane is fixed.  The slot is called with the GPR
        # arguments first and the f32 ones after them, which is the order every
        # table-referenced definition uses (out/bringup-checkpoint/
        # vt_lane_census.py: 0 definitions put an f32 first).  Camera slot 0x20
        # `slot20(f32 t, a, b)` -> CameraBaseLookAt_15fae0(c, eye, at, f32 roll).
        isf = lambda p: (re.fullmatch(r"(const\s+)?(f32|float)", p.ptype.strip()) is not None)
        lane = [p for p in m.params if not isf(p)] + [p for p in m.params if isf(p)]
        if [p.name for p in lane] != [p.name for p in m.params] and not m.variadic:
            self._bump("lane_reordered")
            self.flags.append((path, "vcall-lane-reorder",
                               f"{k.name}::{m.name}: ({', '.join(p.ptype for p in m.params)}) "
                               f"called as ({', '.join(p.ptype for p in lane)})"))
        else:
            lane = m.params
        args = ", ".join(p.name for p in lane)
        ptys = ", ".join(p.ptype for p in lane)
        decls = ", ".join(p.decl + p.default for p in m.params)
        quals = (" " + m.quals) if m.quals else ""
        rk = self.ret_kind(ret, struct_names, scalar_names)
        if rk == "unknown":
            self.flags.append((path, "ret-unknown-type-assumed-scalar", f"{k.name}::{m.name}: {ret}"))
        self._bump(f"thunk_{rk}")

        def FN(r, pt):
            if q:
                return f"VCMQ_FN({q}, {r}, {pt}, {soff})"
            return f"VCM_FN({r}, {pt}, {soff})"
        if m.variadic:
            if k.local:
                self.errors.append((path, f"variadic virtual {k.name}::{m.name} in a local class"))
            fixed = (", " + decls) if decls else ""
            fargs = (", " + args) if args else ""
            fpt = (", " + ptys) if ptys else ""
            r = "void" if rk == "void" else ret
            call = f"{FN(r, f'(void *{fpt}, ...)')}((void *)this{fargs}, vc_va...)"
            self._bump("thunk_variadic")
            body = f"{call};" if rk == "void" else f"return {call};"
            return (f"template <class... VcA> {ret} {m.name}({decls}"
                    f"{', ' if decls else ''}VcA... vc_va){quals} {{ {body} }}")
        if rk == "struct":
            pt = f"({ret} *, void *" + (f", {ptys}" if ptys else "") + ")"
            call = f"{FN('void', pt)}(&vc_r, (void *)this" + (f", {args}" if args else "") + ")"
            return f"{ret} {m.name}({decls}){quals} {{ {ret} vc_r; {call}; return vc_r; }}"
        if rk == "bool":
            r = "vc_u32"
        else:
            r = ret
        if m.params:
            pt = "(void *, " + ptys + ")"
            call = (f"VCMQ({q}, {r}, {pt}, {soff}, {args})" if q
                    else f"VCM({r}, {pt}, {soff}, {args})")
        else:
            call = f"VCMQ0({q}, {r}, {soff})" if q else f"VCM0({r}, {soff})"
        if rk == "void":
            body = f"{call};"
        elif rk == "bool":
            body = f"return (vc_u8){call} != 0;"
        else:
            body = f"return {call};"
        return f"{ret} {m.name}({decls}){quals} {{ {body} }}"

    @staticmethod
    def ret_kind(ret: str, struct_names: set, scalar_names: set) -> str:
        r = _ws(re.sub(r"\b(const|volatile)\b", "", ret))
        if r == "void":
            return "void"
        if r == "bool":
            return "bool"
        if "*" in r or "&" in r:
            return "scalar"
        ids = [x for x in IDENT.findall(r) if x not in CV]
        if not ids:
            return "unknown"
        if all(x in BUILTIN for x in ids) or (len(ids) == 1 and ids[0] in SCALAR_TYPEDEFS):
            return "scalar"
        if re.match(r"enum\b", ret.strip()):
            return "scalar"
        if len(ids) == 1 and ids[0] in scalar_names:
            return "scalar"
        if len(ids) == 1 and ids[0] in struct_names:
            return "struct"
        return "unknown"

    # ---------------------------------------------------------------- apply
    def apply(self, path: str, data: bytes) -> tuple[bytes, int]:
        is_cpp = path.endswith(".cpp")
        is_hdr = path.startswith("include/") and path.endswith(".h")
        if not (is_cpp or is_hdr):
            return data, 0
        text = data.decode("utf-8", "surrogateescape")
        sites = 0
        if "virtual" in text and "#" in text:
            text, k = self.expand_virtual_macros(path, text)
            sites += k
        code = blank_pp(blank(text))
        edits: list[tuple[int, int, str]] = []
        if re.search(r"\bvirtual\b", code):
            sites += self.devirt(path, text, code, edits, is_hdr)
        if is_cpp:
            sites += self.linkage(path, text, code, edits)
        if not edits and not sites:
            return data, 0
        for lo, hi, rep in sorted(edits, key=lambda e: (e[0], e[1]), reverse=True):
            text = text[:lo] + rep + text[hi:]
        return text.encode("utf-8", "surrogateescape"), sites

    DEFINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\(([^)]*)\))?[ \t]*(.*)$", re.M)

    def expand_virtual_macros(self, path: str, text: str) -> tuple[str, int]:
        """Expand (in place, outside #define lines) every use of a macro whose
        expansion declares virtuals (`#define V1(n) virtual void v##n();`,
        `#define V4(n) V1(n##0) ...`), so the class parser sees the members."""
        macros = {}
        for m in self.DEFINE.finditer(text):
            params = [p.strip() for p in m.group(3).split(",")] if m.group(2) else None
            macros[m.group(1)] = (params, m.group(4).strip())
        virt = {n for n, (_, b) in macros.items() if re.search(r"\bvirtual\b", b)}
        while True:
            more = {n for n, (_, b) in macros.items() if n not in virt
                    and any(re.search(r"\b" + re.escape(v) + r"\b", b) for v in virt)}
            if not more:
                break
            virt |= more
        if not virt:
            return text, 0

        def expand_once(s: str) -> tuple[str, int]:
            n = 0
            out = []
            i = 0
            rx = re.compile(r"\b(" + "|".join(map(re.escape, sorted(virt))) + r")\b")
            while True:
                m = rx.search(s, i)
                if not m:
                    out.append(s[i:])
                    break
                params, body = macros[m.group(1)]
                if params is None:
                    out.append(s[i:m.start()] + body)
                    i = m.end()
                    n += 1
                    continue
                j = m.end()
                while j < len(s) and s[j] in " \t":
                    j += 1
                if j >= len(s) or s[j] != "(":
                    out.append(s[i:m.end()])
                    i = m.end()
                    continue
                c = match_close(s, j, "(", ")")
                args = [s[j + 1:c][lo:hi].strip() for lo, hi in split_top(s[j + 1:c])]
                b = body
                for p, a in zip(params, args):
                    b = re.sub(r"\b" + re.escape(p) + r"\b", a, b)
                b = re.sub(r"\s*##\s*", "", b)
                out.append(s[i:m.start()] + b)
                i = c + 1
                n += 1
            return "".join(out), n
        # only code lines (keep #define lines verbatim)
        lines = text.split("\n")
        total = 0
        for li, ln in enumerate(lines):
            if re.match(r"[ \t]*#", ln) or not re.search(
                    r"\b(" + "|".join(map(re.escape, sorted(virt))) + r")\b", blank(ln)):
                continue
            for _ in range(8):
                ln2, n = expand_once(ln)
                if not n:
                    break
                ln = ln2
                total += n
            lines[li] = ln
        if total:
            self._bump("virtual_macro_uses_expanded", total)
            self.flags.append((path, "virtual-macros-expanded", ",".join(sorted(virt))))
        return "\n".join(lines), total

    def devirt(self, path, text, code, edits, is_hdr) -> int:
        seed = {}
        for inc in re.findall(r'#\s*include\s*"([^"]+)"', text):
            base = inc.rsplit("/", 1)[-1]
            if base in self.headers:
                for nm, k in self.headers[base].items():
                    k.from_header = base
                    seed[nm] = k
        self.parse_classes(path, text, code, seed)
        order = [k for k in self._order if k.poly]
        if not order:
            return 0
        self._bump("files")
        # names: struct/class/union tags and typedefs (for return kinds)
        struct_names = set(m.group(2) for m in re.finditer(r"\b(struct|class|union)\s+([A-Za-z_]\w*)", code))
        struct_names |= {"Vec4", "Vec3", "Mtx4", "Mtx", "Bits48", "Mask64"}
        scalar_names = set()
        for m in re.finditer(r"\btypedef\s+([^;{}()]*?)\b([A-Za-z_]\w*)\s*;", code):
            base = m.group(1)
            ids = [x for x in IDENT.findall(base) if x not in CV]
            if "*" in base or (ids and (all(x in BUILTIN for x in ids) or ids[-1] in SCALAR_TYPEDEFS)):
                scalar_names.add(m.group(2))
            elif re.match(r"\s*(struct|union|class)\b", base):
                struct_names.add(m.group(2))
        for m in re.finditer(r"\btypedef\s+(struct|union)\b[^;]*?\}\s*([A-Za-z_]\w*)\s*;", code, re.S):
            struct_names.add(m.group(2))
        for m in re.finditer(r"\benum\s+([A-Za-z_]\w*)", code):
            scalar_names.add(m.group(1))
        struct_names -= scalar_names
        # references: identifier counts outside virtual declaration heads
        idcount: dict[str, int] = {}
        for m in IDENT.finditer(blank(text)):
            idcount[m.group(0)] = idcount.get(m.group(0), 0) + 1
        decl_names: dict[str, int] = {}
        for k in order:
            for m in k.methods:
                if m.is_virtual or m.slot == -3:
                    decl_names[m.name] = decl_names.get(m.name, 0) + 1
        sites = 0
        for k in order:
            if k.from_header and not is_hdr:
                continue
            first = None
            if k.root:
                first = min((m for m in k.methods if m.is_virtual), key=lambda m: m.lo)
            for m in k.methods:
                if m.slot == -2:
                    continue
                span_nl = text[m.lo:m.hi].count("\n")
                pieces = []
                if m is first:
                    acc = next(a for (lo, hi, kd, a) in k.members if lo == m.lo)
                    if acc != "public":
                        pieces.append(f"public: VC_VPTR_MEMBER; {acc}:")
                    else:
                        pieces.append("VC_VPTR_MEMBER;")
                    self._bump("vptr_inserted")
                referenced = is_hdr or idcount.get(m.name, 0) > decl_names.get(m.name, 0)
                if m.slot >= 0 and referenced:
                    pieces.append(self.thunk(k, m, struct_names, scalar_names, path))
                    emitted = 1
                else:
                    emitted = 0
                    self._bump("virtual_dropped" if m.slot >= 0 else "override_decl_removed")
                if m.slot >= 0:
                    self.rows.append((path, text.count("\n", 0, m.lo) + 1, k.name,
                                      m.owner, m.vq or "-", m.name, m.slot,
                                      f"0x{8 + 4 * m.slot:X}", _ws(m.ret) or "-",
                                      "variadic" if m.variadic else
                                      self.ret_kind(m.ret, struct_names, scalar_names),
                                      emitted))
                edits.append((m.lo, m.hi, " ".join(pieces) + "\n" * span_nl))
                sites += 1
            if k.ctor:
                self.flags.append((path, "ctor-in-polymorphic-class", k.name))
            if any(m.variadic and m.slot >= 0 for m in k.methods) and self._in_c_block(code, k.head):
                # member templates need C++ linkage: nest the class in extern "C++"
                s = k.head
                while s > 0 and code[s - 1] not in ";{}":
                    s -= 1
                while s < k.head and code[s].isspace():
                    s += 1
                e = code.find(";", k.close)
                edits.append((s, s, 'extern "C++" { '))
                edits.append((e + 1, e + 1, " }"))
                self._bump("class_wrapped_extern_cxx")
        return sites

    @staticmethod
    def _in_c_block(code: str, i: int) -> bool:
        for m in re.finditer(r'(?<![A-Za-z0-9_])extern\s+"\s*"\s*[{]', code[:i]):
            o = m.end() - 1
            if match_close(code, o) > i:
                return True
        return False

    # ---------------------------------------------------------------- linkage
    def linkage(self, path: str, text: str, code: str, edits) -> int:
        n = 0
        cblocks = []
        for m in re.finditer(r'\bextern\s+"\s*"\s*\{', code):
            o = m.end() - 1
            cblocks.append((o, match_close(code, o)))

        def in_c(i: int) -> bool:
            return any(lo < i < hi for lo, hi in cblocks)
        # namespace-scope statement starts: walk braces, transparent extern "C"/namespace
        funcs = find_funcs(code)
        top = [f for f in funcs if not f.in_class]
        fbodies = [(f.body_open, f.body_close) for f in top]

        def in_body(i: int) -> bool:
            return any(lo < i < hi for lo, hi in fbodies)
        # class bodies (a declaration inside a class is a member)
        cbodies = []
        for m in HEAD.finditer(code):
            o = m.end() - 1
            cbodies.append((o, match_close(code, o)))

        def in_class(i: int) -> bool:
            return any(lo < i < hi for lo, hi in cbodies)

        def stmt_start(i: int) -> int:
            k = i
            while k > 0 and code[k - 1] not in ";{}":
                k -= 1
            while k < i and code[k] in " \t\r\n":
                k += 1
            return k
        # (a) game-symbol function definitions with C++ linkage
        done_names = set()
        for f in top:
            nm = f.name
            if "::" in nm or not GAME_SYM.match(nm) or in_c(f.body_open) or in_class(f.body_open):
                continue
            h = code[f.start:f.body_open]
            if re.search(r'\bextern\s+"', h) or re.search(r"\b(static|inline|__inline)\b", h):
                continue
            # is there an earlier C-linkage declaration?  then it is already C
            prior_c = False
            for mm in re.finditer(r"\b" + re.escape(nm) + r"\s*\(", code[:f.start]):
                s = stmt_start(mm.start())
                if in_body(mm.start()) or in_class(mm.start()):
                    continue
                if in_c(mm.start()) or re.match(r'extern\s+"', code[s:]):
                    prior_c = True
            if prior_c:
                continue
            for mm in re.finditer(r"\b" + re.escape(nm) + r"\s*\(", code[:f.start]):
                if in_body(mm.start()) or in_class(mm.start()):
                    continue
                s = stmt_start(mm.start())
                edits.append((s, s, 'extern "C" '))
                n += 1
            s = f.start
            while s < f.body_open and code[s] in " \t\r\n":
                s += 1
            edits.append((s, s, 'extern "C" '))
            done_names.add(nm)
            n += 1
            self._bump("link_fn_extern_c")
            self.flags.append((path, "fn-made-extern-c", nm))
        # (b) extern data declarations
        hoisted: set[str] = set()
        ns_c_names: set[str] = set()
        decls = []
        for m in re.finditer(r"\bextern\b(?!\s*\")", code):
            i = m.start()
            if in_class(i) and not in_body(i):
                continue
            s = stmt_start(i)
            if s != i:
                continue
            e = code.find(";", i)
            if e < 0:
                continue
            st = code[i:e]
            # function declaration? (a paren group not of the form (*name));
            # `__attribute__((section(".sdata")))` on data is not one
            if re.search(r"[A-Za-z_]\w*\s*\((?!\s*\*)", self._strip_attrs(st)):
                continue
            names = self._declarator_names(st)
            if not names:
                continue
            decls.append((i, e, st, names))
        # names already declared with C linkage at namespace scope: `extern "C" T x;`
        for m in re.finditer(r'\bextern\s+"\s*"\s*(?!\{)', code):
            if in_body(m.start()) or in_c(m.start()):
                continue
            e = code.find(";", m.end())
            st = code[m.end():e] if e > 0 else ""
            if st and not re.search(r"[A-Za-z_]\w*\s*\((?!\s*\*)", st):
                ns_c_names.update(self._declarator_names("extern " + st))
        for i, e, st, names in decls:
            if not in_body(i):
                if in_c(i):
                    ns_c_names.update(names)
                    continue
                edits.append((i, i + len("extern"), 'extern "C"'))
                ns_c_names.update(names)
                n += 1
                self._bump("link_data_extern_c")
        for i, e, st, names in decls:
            if in_body(i) and not in_c(i):
                new = [x for x in names if x not in ns_c_names and x not in hoisted]
                if not new:
                    continue
                f = next(f for f in top if f.body_open < i < f.body_close)
                s = f.start
                while s < f.body_open and code[s] in " \t\r\n":
                    s += 1
                if self._mentions_local_type(st, code[f.body_open:i]):
                    self.flags.append((path, "block-extern-local-type", _ws(st)[:80]))
                    continue
                edits.append((s, s, 'extern "C"' + text[i + len("extern"):e] + "; "))
                hoisted.update(names)
                n += 1
                self._bump("link_block_extern_hoisted")
        return n

    @staticmethod
    def _strip_attrs(st: str) -> str:
        out = st
        while True:
            m = re.search(r"__attribute__\s*\(\(", out)
            if not m:
                return out
            c = match_close(out, m.end() - 2, "(", ")")
            out = out[:m.start()] + " " + out[c + 1:]

    @staticmethod
    def _declarator_names(st: str) -> list[str]:
        body = re.sub(r"^extern\s+", "", st.strip())
        body = re.sub(r"\{[^{}]*\}", " ", body)            # struct body (dialect tag)
        while re.search(r"\{[^{}]*\}", body):
            body = re.sub(r"\{[^{}]*\}", " ", body)
        body = re.sub(r"\[[^\]]*\]", "", body)
        body = DevirtStage._strip_attrs(body)
        body = re.sub(r"=.*$", "", body, flags=re.S)
        parts = split_top(body)
        names = []
        for lo, hi in parts:
            p = body[lo:hi]
            fp = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", p)
            if fp:
                names.append(fp.group(1))
                continue
            ids = IDENT.findall(p)
            if ids:
                names.append(ids[-1])
        return names

    @staticmethod
    def _mentions_local_type(st: str, fnbody: str) -> bool:
        for t in IDENT.findall(st):
            if re.search(r"\b(struct|class|union|typedef)\b[^;{]*\b" + re.escape(t) + r"\b", fnbody):
                return True
        return False


def _main() -> int:
    """python tools/stages/devirt.py IN OUT  -- one file, idempotence check."""
    if len(sys.argv) != 3:
        print(_main.__doc__)
        return 2
    st = DevirtStage()
    path = sys.argv[1].replace("\\", "/")
    data = open(sys.argv[1], "rb").read()
    out, n = st.apply(path, data)
    again, _ = st.apply(path, out)
    if again != out:
        print("NOT idempotent")
        return 1
    open(sys.argv[2], "wb").write(out)
    print(f"devirt: {n} sites; {st.stats}")
    for f in st.flags:
        print("flag", f)
    for e in st.errors:
        print("ERROR", e)
    return 0


if __name__ == "__main__":
    raise SystemExit(_main())
