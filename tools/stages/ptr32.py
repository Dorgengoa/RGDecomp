#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Stage `ptr32` (x64 only, P7 strategy A: docs/X64-PLAN.md step 2).

Every pointer that LIVES IN GAME MEMORY keeps its i686 size on x64: it is
spelled `T * RG_P32` (port/x64.h: `__ptr32 __uptr`, a 4-byte pointer that
zero-extends on load; every host address of the x64 exe is below 2 GB, see
tools/x64/pecheck.py).  Retail record layouts, the data layer, the asset
formats (in-place relocation), the save format and the trace mapping stay as
they are.  Locals, parameters and return values stay ordinary 8-byte
pointers: the conversions are implicit.

The stage is NOT part of the i686 ingest.  It runs on the generated tree
(game/ after every ingest stage, plus overrides/ and missing/) into the x64
source tree (tools/x64/derive.py), so the i686 build is untouched by
construction.  `Ptr32Stage` has the ingest Stage interface (prepare / apply /
extra_outputs / report), so it can also run as the last ingest stage.

Rewrites (text level, on comment/string-blanked code):
  member     record member declarators: every top-level `*` -> `* RG_P32`;
             a member whose type is a pointer TYPEDEF (`PX p;`, `Cb cb;`) gets
             `RG_P32` after the type name; inline anonymous records
             (`struct { .. } *p;`) are rewritten in their own body and in the
             declarator after the closing brace
  global     file-scope (column-0) and block-scope `extern` pointer
             declarations, not `static`, no non-null initializer (a
             `__ptr32` cannot be statically initialised with an address:
             LLVM "unsupported expression in static initializer: addrspacecast")
  ptrptr     pointer-loading casts `(T **)` -> `(T * RG_P32 *)`: the slot read
             through the cast is a game-memory word
  sizeof     `sizeof(T *)` -> `sizeof(T * RG_P32)`
  fncall     a call through a function-pointer member or global that became
             `RG_P32` is wrapped: `p->cb(x)` -> `RG_FPC(p->cb)(x)`,
             `(*p->cb)(x)` -> `(*RG_FPC(p->cb))(x)`.  RG_FPC casts to the
             ordinary (64-bit) function pointer type.  LLVM miscompiles a call
             THROUGH a `__ptr32` function pointer (tail call: an 8-byte load
             of the 4-byte slot; otherwise an isel crash: repro
             build/x64-probe/lowmem/t8.c).  The x64 game build passes
             -fno-optimize-sibling-calls, so a call site this rewrite misses
             is a hard compile error ("Cannot select X86ISD::CALL"), never a
             silent miscompile.

Rows: PTR32.tsv (relpath, line, rule, text).
"""
from __future__ import annotations

import os
import re
import sys
from collections import Counter
from pathlib import Path

P32 = "RG_P32"
FPC = "RG_FPC"
ID = r"[A-Za-z_]\w*"
QUALS = {"const", "volatile", "unsigned", "signed", "short", "long", "int", "char",
         "struct", "union", "enum", "class", "extern", "static", "register", "inline",
         "__restrict", "restrict", "__unaligned", "mutable", "typename", "volatile"}
SKIP_HEAD = ("typedef", "static ", "static\t", "static\n", "friend", "using ", "enum ",
             "template", "virtual", "operator", "return")
ACCESS = re.compile(r"^\s*(?:(?:public|private|protected)\s*:\s*)+")


# ------------------------------------------------------------------ lexing
def _line_start(s: str, i: int) -> bool:
    k = i - 1
    while k >= 0 and s[k] in " \t":
        k -= 1
    return k < 0 or s[k] == "\n"


def blank_attrs(s: str) -> str:
    """`__attribute__((..))` / `__declspec(..)` groups -> spaces (offsets kept)."""
    out = list(s)
    for m in re.finditer(r"\b(?:__attribute__|__declspec)\s*\(", s):
        i, d = m.end(), 1
        while i < len(s) and d:
            d += {"(": 1, ")": -1}.get(s[i], 0)
            i += 1
        for k in range(m.start(), i):
            if out[k] != "\n":
                out[k] = " "
    return "".join(out)


def includes_of(s: str) -> list[str]:
    """basenames of the quoted/angled #include lines of a file"""
    return [re.split(r"[\\/]", m.group(1))[-1]
            for m in re.finditer(r'(?m)^[ \t]*#[ \t]*include[ \t]*["<]([^">]+)[">]', s)]


def define_spans(s: str) -> list[tuple[int, int]]:
    """[start, end) of every `#define` directive (continuation lines included)."""
    out = []
    for m in re.finditer(r"(?m)^[ \t]*#[ \t]*define\b", s):
        j = m.start()
        while True:
            e = s.find("\n", j)
            e = len(s) if e < 0 else e
            if e > 0 and s[e - 1] == "\\" and e < len(s):
                j = e + 1
                continue
            break
        out.append((m.start(), e))
    return out


def blank(s: str, keep_define: bool = False) -> str:
    """Comments, string and char literals, preprocessor lines -> spaces
    (offsets and newlines kept).  keep_define: `#define` bodies stay (their
    comments and literals are still blanked)."""
    out = list(s)
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if c == "/" and i + 1 < n and s[i + 1] == "/":
            j = s.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c == "/" and i + 1 < n and s[i + 1] == "*":
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and s[j] != c and s[j] != "\n":
                j += 2 if s[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                out[k] = " "
            i = j + 1
        elif c == "#" and _line_start(s, i):
            if keep_define and re.match(r"#[ \t]*define\b", s[i:i + 20]):
                i += 1
                continue
            j = i
            while True:
                e = s.find("\n", j)
                e = n if e < 0 else e
                if e > 0 and s[e - 1] == "\\" and e < n:
                    j = e + 1
                    continue
                break
            for k in range(i, e):
                if out[k] != "\n":
                    out[k] = " "
            i = e
        else:
            i += 1
    return "".join(out)


REC_HDR = re.compile(r"\b(struct|union|class)\b")


def blocks_of(code: str) -> list[tuple[int, int, str]]:
    """Brace blocks (open, close, kind): fn / init / rec / enum / other."""
    blocks = []
    stack: list[tuple[int, str]] = []
    for i, ch in enumerate(code):
        if ch == "{":
            parent = stack[-1][1] if stack else None
            k = i - 1
            while k >= 0 and code[k] in " \t\r\n":
                k -= 1
            prev = code[k] if k >= 0 else ""
            start = max(code.rfind(";", 0, i), code.rfind("}", 0, i), code.rfind("{", 0, i))
            head = code[start + 1:i]
            if parent in ("fn", "init", "enum"):
                kind = parent
                if parent == "fn" and REC_HDR.search(head) and prev not in "=,)":
                    kind = "rec"          # a record defined inside a function
            elif prev in "=," or (parent == "init"):
                kind = "init"
            elif prev == ")" or re.search(r"\)\s*(const|override|noexcept|final|throw\s*\(\s*\))\s*$", head):
                kind = "fn"
            elif re.search(r"\benum\b", head):
                kind = "enum"
            elif REC_HDR.search(head):
                kind = "rec"
            else:
                kind = "other"            # extern "C" {, namespace X {
            stack.append((i, kind))
        elif ch == "}" and stack:
            o, kind = stack.pop()
            blocks.append((o, i, kind))
    return blocks


def match_close(code: str, o: int) -> int:
    depth = 0
    for i in range(o, len(code)):
        ch = code[i]
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
            if depth == 0:
                return i
    return len(code) - 1


def split_top(seg: str, sep: str) -> list[tuple[int, int]]:
    """Spans of seg split at `sep` characters at bracket depth 0."""
    out, depth, st = [], 0, 0
    for i, ch in enumerate(seg):
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif ch == sep and depth == 0:
            out.append((st, i))
            st = i + 1
    out.append((st, len(seg)))
    return out


# ---------------------------------------------------------------- typedefs
BUILTIN_TYPES = {"void", "char", "short", "int", "long", "float", "double", "unsigned", "signed",
                 "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64", "u128",
                 "s128", "rg_u128", "rg_s128", "uint8_t", "int8_t", "uint16_t", "int16_t",
                 "uint32_t", "int32_t", "uint64_t", "int64_t", "size_t", "bool", "_Bool"}


def strip_attrs(s: str) -> str:
    """remove every `__attribute__((..))` (balanced parentheses) from s"""
    out = []
    i = 0
    while True:
        k = s.find("__attribute__", i)
        if k < 0:
            out.append(s[i:])
            return "".join(out)
        j = k + len("__attribute__")
        while j < len(s) and s[j].isspace():
            j += 1
        if j >= len(s) or s[j] != "(":
            out.append(s[i:j])
            i = j
            continue
        depth = 0
        e = j
        while e < len(s):
            if s[e] == "(":
                depth += 1
            elif s[e] == ")":
                depth -= 1
                if depth == 0:
                    break
            e += 1
        out.append(s[i:k] + " ")
        i = e + 1


class Typedefs:
    """Pointer typedef names: data pointers (`typedef T *P;`), function
    pointers (`typedef R (*F)(..);`) and function types (`typedef R F(..);`)."""

    def __init__(self):
        self.ptr: set[str] = set()
        self.fnptr: set[str] = set()
        self.fn: set[str] = set()
        self.names: set[str] = set(BUILTIN_TYPES)   # every type name (dptr rule)

    def copy(self) -> "Typedefs":
        t = Typedefs()
        t.ptr, t.fnptr, t.fn = set(self.ptr), set(self.fnptr), set(self.fn)
        t.names = set(self.names)
        return t

    def scan(self, code: str) -> None:
        for m in re.finditer(r"\btypedef\b[^;]*?(" + ID + r")\s*(?:\[[^\]]*\]\s*)*;", code):
            self.names.add(m.group(1))
        for m in re.finditer(r"\b(?:struct|union|class)\s+(" + ID + r")", code):
            self.names.add(m.group(1))
        for m in re.finditer(r"\btypedef\b", code):
            i = m.end()
            depth = 0
            j = i
            while j < len(code):
                ch = code[j]
                if ch in "({[":
                    depth += 1
                elif ch in ")}]":
                    depth -= 1
                elif ch == ";" and depth == 0:
                    break
                j += 1
            st = code[i:j]
            # declarator part: after the body of an inline record
            body_end = -1
            if "{" in st:
                o = st.index("{")
                body_end = match_close(st, o)
            decl = st[body_end + 1:] if body_end >= 0 else st
            # `typedef struct {..} __attribute__((aligned(2))) Obj;`: the attribute is
            # not a declarator (it read as a function type `__attribute__(..)` and the
            # name was lost: ResGroupListInit_429fd0's `Obj **out` kept 8-byte slots)
            decl = strip_attrs(decl)
            base = None if body_end >= 0 else decl
            for a, b in split_top(decl, ","):
                d = decl[a:b]
                fm = re.search(r"\(\s*((?:\*\s*)+)(?:const\s*)?(" + ID + r")\s*\)\s*\(", d)
                if fm:
                    self.fnptr.add(fm.group(2))
                    continue
                fn = re.search(r"(" + ID + r")\s*\(", d)
                if fn and "*" not in d[:fn.start()].split()[-1:] and "(" not in d[:fn.start()]:
                    # `R F(params)` (a function type), unless the star belongs to the name
                    pre = d[:fn.start()]
                    if not pre.rstrip().endswith("*"):
                        self.fn.add(fn.group(1))
                        continue
                    self.fn.add(fn.group(1))  # `R *F(params)`: function returning pointer
                    continue
                nm = re.search(r"(" + ID + r")\s*(?:\[[^\]]*\]\s*)*$", d.strip())
                if not nm:
                    continue
                name = nm.group(1)
                self.names.add(name)       # `typedef struct { .. } Name;` too
                pre = d.strip()[:nm.start()]
                if "*" in pre and (base is None or a > 0 or True):
                    self.ptr.add(name)
                else:
                    # typedef of a typedef: inherits the class of its base name
                    toks = re.findall(ID, (base or decl[:a]) if a else pre)
                    toks = [t for t in toks if t not in QUALS]
                    if toks:
                        t = toks[-1]
                        if t in self.fnptr:
                            self.fnptr.add(name)
                        elif t in self.ptr:
                            self.ptr.add(name)
                        elif t in self.fn:
                            self.fn.add(name)


# ------------------------------------------------------------------ stage
class Ptr32Stage:
    name = "ptr32"

    def __init__(self):
        self.glob = Typedefs()          # from the shared headers (prepare)
        self.rows: list[str] = []
        self.stats: Counter = Counter()
        self.errors: list[str] = []
        # header basename -> (fn-pointer member names, method names, included basenames)
        self.hdr_fn_members: dict[str, tuple[set[str], set[str], set[str]]] = {}

    # shared headers: game/include and the port include/ headers every TU sees
    def prepare_headers(self, texts: dict[str, str]) -> None:
        for rel, t in sorted(texts.items()):
            code = blank(t)
            self.glob.scan(code)
        for rel, t in sorted(texts.items()):
            code = blank(t)
            base = re.split(r"[\\/]", rel)[-1]
            self.hdr_fn_members[base] = (self._fn_member_names(code, self.glob),
                                         self._method_names(code), set(includes_of(t)))

    def header_names(self, raw: str) -> tuple[set[str], set[str]]:
        """fn-pointer member names and method names of the headers a TU includes
        (transitively)."""
        fns, meth = set(), set()
        todo = list(includes_of(raw))
        seen = set()
        while todo:
            h = todo.pop()
            if h in seen or h not in self.hdr_fn_members:
                continue
            seen.add(h)
            f, mt, inc = self.hdr_fn_members[h]
            fns |= f
            meth |= mt
            todo += list(inc)
        return fns, meth

    @staticmethod
    def _method_names(code: str) -> set[str]:
        out = set()
        for o, c, k in blocks_of(code):
            if k != "rec":
                continue
            seg = code[o:c]
            for m in re.finditer(r"\b(" + ID + r")\s*\(", seg):
                k = m.start() - 1
                while k >= 0 and seg[k] in " \t\r\n":
                    k -= 1
                if k < 0 or not (seg[k].isalnum() or seg[k] in "_*&"):
                    continue            # `(*name)(` (a pointer member) or a call
                j = k
                while j >= 0 and seg[j] in "*& \t\r\n":
                    j -= 1
                if j >= 0 and seg[j] == "(":
                    continue
                out.add(m.group(1))
        return out

    def prepare(self, outputs: dict[str, bytes]) -> None:   # ingest interface
        hdr = {p: d.decode("utf-8", "replace") for p, d in outputs.items()
               if p.startswith("include/") and p.endswith((".h", ".hpp"))}
        self.prepare_headers(hdr)

    def _fn_member_names(self, code: str, td: Typedefs) -> set[str]:
        names = set()
        for o, c, k in blocks_of(code):
            if k != "rec":
                continue
            for s, e in self._member_spans(code, o, c):
                r = self._classify_decl(code, s, e, td)
                if r and r[2]:
                    names.update(r[3])
        return names

    @staticmethod
    def _member_spans(code: str, o: int, c: int):
        """Top-level member declarations of a record body; an inline method body
        `R f(..) { .. }` ends a declaration too (no `;` after it)."""
        depth, start = 0, o + 1
        body_at = None
        for i in range(o + 1, c):
            ch = code[i]
            if ch in "{([":
                if ch == "{" and depth == 0:
                    k = i - 1
                    while k > o and code[k] in " \t\r\n":
                        k -= 1
                    head = code[max(o, k - 20):k + 1]
                    if code[k] == ")" or re.search(r"\b(const|override|noexcept|final)$", head):
                        body_at = i
                depth += 1
            elif ch in "})]":
                depth -= 1
                if ch == "}" and depth == 0 and body_at is not None:
                    body_at = None
                    start = i + 1
            elif ch == ";" and depth == 0:
                yield start, i
                start = i + 1

    def _classify_decl(self, code: str, s: int, e: int, td: Typedefs, member: bool = True):
        """-> (star offsets, typedef-insert offset or None, is_fn, names) or None."""
        seg = code[s:e]
        m = ACCESS.match(seg)
        off = m.end() if m else 0
        body = seg[off:]
        st = body.strip()
        if not st or st.startswith(SKIP_HEAD) or st.startswith(("static", "typedef")):
            return None
        if re.match(r"(?:inline|virtual|explicit)\b", st) or "operator" in st:
            return None
        # declarator part: after an inline record's body
        dstart = off
        if "{" in body:
            o = body.index("{")
            cl = match_close(body, o)
            if not REC_HDR.search(body[:o]) and not re.search(r"\benum\b", body[:o]):
                return None
            if re.search(r"\benum\b", body[:o]):
                return None
            dstart = off + cl + 1
        # strip a bitfield / default member initializer / initializer
        dec = blank_attrs(seg[dstart:])
        stop = len(dec)
        depth = 0
        for i, ch in enumerate(dec):
            if ch in "({[":
                depth += 1
            elif ch in ")}]":
                depth -= 1
            elif ch in "=:" and depth == 0:
                if ch == ":" and i + 1 < len(dec) and dec[i + 1] == ":":
                    continue
                if ch == ":" and i > 0 and dec[i - 1] == ":":
                    continue
                stop = i
                break
        init = dec[stop:]
        dec = dec[:stop]
        if init.startswith(":") and member:
            pass  # bitfield: no pointer
        stars: list[int] = []
        names: list[str] = []
        is_fn = False
        tins = None
        # function-pointer declarators `(*name)(` or `(*name[N])(`
        fps = list(re.finditer(r"\(\s*((?:\*\s*)+)(?:const\s*)?(" + ID + r")\s*((?:\[[^\]]*\]\s*)*)\)\s*\(",
                               dec))
        if fps:
            for fm in fps:
                k0 = dstart + fm.start(1)
                for k in range(fm.start(1), fm.end(1)):
                    if dec[k] == "*":
                        stars.append(s + dstart + k)
                names.append(fm.group(2))
            return stars, None, True, names
        # pointer-to-array declarators `T (*name)[N]` (a data pointer)
        pas = list(re.finditer(r"\(\s*((?:\*\s*)+)(?:const\s*)?(" + ID + r")\s*\)\s*\[", dec))
        if pas:
            for fm in pas:
                for k in range(fm.start(1), fm.end(1)):
                    if dec[k] == "*":
                        stars.append(s + dstart + k)
                names.append(fm.group(2))
            return stars, None, False, names
        # a method / function declaration: `R name(params)`
        if "(" in re.sub(r"\[[^\]]*\]", "", dec):
            return None
        # plain declarators, comma-separated
        spans = split_top(dec, ",")
        first = dec[spans[0][0]:spans[0][1]]
        # base type = identifiers before the first declarator's name
        toks = list(re.finditer(ID, first))
        if not toks:
            return None
        has_star = "*" in dec
        base_names = [t.group(0) for t in toks[:-1] if t.group(0) not in QUALS]
        base = base_names[-1] if base_names else None
        if dstart != off and base is None:
            base = "<record>"
        for a, b in spans:
            d = dec[a:b]
            nm = re.search(r"(" + ID + r")\s*(?:\[[^\]]*\]\s*)*$", d.strip())
            if not nm:
                continue
            names.append(nm.group(1))
            depth = 0
            for i, ch in enumerate(d):
                if ch in "([":
                    depth += 1
                elif ch in ")]":
                    depth -= 1
                elif ch == "*" and depth == 0:
                    stars.append(s + dstart + a + i)
        if not stars:
            if base and (base in td.ptr or base in td.fnptr):
                # insert after the base type name (decl-specifier: applies to every declarator)
                bt = [t for t in toks[:-1] if t.group(0) == base][-1]
                tins = s + dstart + bt.end()
                is_fn = base in td.fnptr
                return [], tins, is_fn, names
            return None
        if base and base in td.fn:
            is_fn = True
        if base and (base in td.fnptr or base in td.ptr):
            # `Cb *tbl` / `PX *arr`: the pointee is itself a pointer in game memory (a
            # table of 4-byte words): RG_P32 after the typedef name too.  A call through
            # an element (`tbl[i](..)`) is an RG_P32 function pointer call.
            bt = [t for t in toks[:-1] if t.group(0) == base][-1]
            tins = s + dstart + bt.end()
            is_fn = is_fn or base in td.fnptr
        return stars, tins, is_fn, names

    # ------------------------------------------------------------ apply
    def apply(self, relpath: str, data: bytes) -> tuple[bytes, int]:
        if not relpath.endswith((".c", ".cpp", ".h", ".hpp", ".inc")) or relpath.endswith(".inc"):
            return data, 0
        raw = data.decode("utf-8", "surrogateescape")
        new, n = self.rewrite(relpath, raw)
        return new.encode("utf-8", "surrogateescape"), n

    def rewrite(self, relpath: str, raw: str) -> tuple[str, int]:
        if "rg:datareloc" in raw[:400] and relpath.startswith("src/") and "_data/" in relpath:
            return raw, 0       # data layer: tools/x64/addr32.py
        code = blank(raw)
        td = self.glob.copy()
        td.scan(code)
        blocks = blocks_of(code)
        ins: dict[int, str] = {}       # offset -> text inserted BEFORE code[offset]
        rep: dict[int, tuple[int, str]] = {}   # star offset -> replacement
        nl = [0] + [i + 1 for i, ch in enumerate(code) if ch == "\n"]
        import bisect

        def line(o):
            return bisect.bisect_right(nl, o)

        cnt = Counter()
        hfn, hmeth = self.header_names(raw)
        fn_names: set[str] = set(hfn)
        fn_globals: set[str] = set()

        def take(r, rule, at):
            stars, tins, is_fn, names = r
            for p in stars:
                rep[p] = (p + 1, "* " + P32 + " ")
            if tins is not None:
                ins[tins] = " " + P32
            cnt[rule] += 1
            if is_fn:
                cnt[rule + "-fn"] += 1
            self.rows.append(f"{relpath}\t{line(at)}\t{rule}{'-fn' if is_fn else ''}\t"
                             f"{' '.join(code[at:at + 70].split())}")
            return is_fn, names

        # ---- record members
        for o, c, k in blocks:
            if k != "rec":
                continue
            for s, e in self._member_spans(code, o, c):
                r = self._classify_decl(code, s, e, td)
                if r:
                    is_fn, names = take(r, "member", s + len(code[s:e]) - len(code[s:e].lstrip()))
                    if is_fn:
                        fn_names.update(names)
        # ---- file-scope and block-scope extern declarations
        fn_spans = sorted((o, c) for o, c, k in blocks if k in ("fn", "init", "rec", "enum"))
        rec_or_init = sorted((o, c) for o, c, k in blocks if k in ("init", "rec", "enum"))

        def inside(spans, p):
            i = bisect.bisect_right(spans, (p, 1 << 62)) - 1
            while i >= 0:
                o, c = spans[i]
                if o < p < c:
                    return True
                if c < p and o < p:
                    # spans are sorted by open; an earlier one may still contain p
                    pass
                i -= 1
                if i >= 0 and spans[i][1] < p and spans[i][0] < p - 200000:
                    break
            return False

        fnb = sorted((o, c) for o, c, k in blocks if k == "fn")
        for m in re.finditer(r"(?m)(?:^|(?<=;))[ \t]*((?:extern\s+(?:\"C\"\s+)?)?(?:const\s+|volatile\s+)*"
                             r"(?:struct\s+|union\s+|enum\s+|class\s+)?" + ID + r"[^;{}]*?;)", code):
            st = m.group(1)
            p = m.start(1)
            if st.startswith(("return", "typedef", "static", "goto", "case", "using", "friend",
                              "delete", "throw", "else", "do ", "break", "continue")):
                continue
            in_fn = inside(fnb, p)
            if in_fn:
                if not st.startswith("extern"):
                    continue
            else:
                q = p - 1
                while q >= 0 and code[q] in " \t":
                    q -= 1
                if q >= 0 and code[q] not in "\n;":
                    continue        # file scope: a statement at column 0 or after a `;`
                if inside(rec_or_init, p):
                    continue
                if inside(fn_spans, p):
                    continue
            if "*" not in st and not re.search(ID, st):
                continue
            # initializer: only a null one keeps the rewrite
            eq = None
            depth = 0
            for i, ch in enumerate(st):
                if ch in "({[":
                    depth += 1
                elif ch in ")}]":
                    depth -= 1
                elif ch == "=" and depth == 0:
                    eq = i
                    break
            if eq is not None:
                rhs = st[eq + 1:].strip().rstrip(";").strip()
                if rhs not in ("0", "NULL", "nullptr", "(void *)0", "((void *)0)"):
                    continue
            r = self._classify_decl(code, p, p + len(st) - 1, td, member=False)
            if not r:
                continue
            is_fn, names = take(r, "extern" if in_fn else "global", p)
            if is_fn:
                fn_globals.update(names)
        # ---- declarations with an inline record body: `extern struct { .. } *gCtx;`
        # (file scope, or a block-scope extern): the declarator after the `}`
        for o, c, k in blocks:
            if k != "rec":
                continue
            st0 = max(code.rfind(";", 0, o), code.rfind("}", 0, o), code.rfind("{", 0, o)) + 1
            head = code[st0:o]
            if "typedef" in head or "static" in head:
                continue
            outer = inside(fnb, o)
            if outer and "extern" not in head:
                continue
            if inside(rec_or_init, o) and not outer:
                continue                # a member's inline record: the member rule's
            e = code.find(";", c)
            if e < 0:
                continue
            tail = code[c + 1:e]
            if "=" in tail or "(" in tail or "*" not in tail:
                continue
            for i, ch in enumerate(tail):
                if ch == "*" and (c + 1 + i) not in rep:
                    rep[c + 1 + i] = (c + 2 + i, "* " + P32 + " ")
            cnt["global-rec"] += 1
            self.rows.append(f"{relpath}\t{line(st0)}\tglobal-rec\t{' '.join(code[c + 1:e].split())}")
        # ---- casts and sizeof
        for m in re.finditer(r"\(\s*(?:const\s+|volatile\s+)?(?:struct\s+|union\s+|unsigned\s+|signed\s+)?"
                             + ID + r"(?:\s+" + ID + r")*\s*(\*)\s*(?:const\s*|volatile\s*)*\*\s*\)", code):
            if inside(fnb, m.start()) or inside(rec_or_init, m.start()):
                p = m.start(1)
                if p not in rep:
                    rep[p] = (p + 1, "* " + P32 + " ")
                    cnt["ptrptr"] += 1
        for m in re.finditer(r"\bsizeof\s*\(\s*(?:const\s+)?(?:struct\s+|union\s+|unsigned\s+)?"
                             + ID + r"(?:\s+" + ID + r")*\s*(\*)\s*\)", code):
            p = m.start(1)
            if p not in rep:
                rep[p] = (p + 1, "* " + P32 + " ")
                cnt["sizeof"] += 1
        # ---- local arrays of pointers (`T *list[4];`): retail's stack held 4-byte
        # slots, and the code walks them with `T **` (dptr) or passes them to
        # callees that fill game-memory-shaped tables
        for m in re.finditer(r"(?m)(?:^[ \t]+|(?<=[;{])[ \t]*)(static\s+)?(?:const\s+|volatile\s+)*(?:struct\s+|union\s+)?("
                             + ID + r")\s*((?:\*\s*)+)(" + ID + r")\s*\[[^\]]*\]\s*([;=,])", code):
            if m.group(2) not in td.names or m.group(2) in ("return", "goto", "case"):
                continue
            if not inside(fnb, m.start()):
                continue
            if m.group(1) and m.group(5) == "=":
                continue      # static initialised with addresses: no __ptr32 initializer
            for k in range(m.start(3), m.end(3)):
                if code[k] == "*" and k not in rep:
                    rep[k] = (k + 1, "* " + P32 + " ")
            cnt["localarr"] += 1
            self.rows.append(f"{relpath}\t{line(m.start())}\tlocalarr\t{' '.join(code[m.start():m.end()].split())}")
        # ---- address-taken pointer locals (`T *self; f(&self);`): the callee sees a
        # game-memory-shaped slot (`T * RG_P32 *`), retail's stack slot was 4 bytes
        for o, c in fnb:
            body = code[o:c]
            taken = set(re.findall(r"&\s*(" + ID + r")\b(?!\s*(?:\[|->|\.|\())", body))
            if not taken:
                continue
            for m in re.finditer(r"(?m)(?:^[ \t]+|(?<=[;{])[ \t]*)(?:const\s+|volatile\s+|register\s+)*(?:struct\s+|union\s+)?("
                                 + ID + r")\s*(\*)\s*(" + ID + r")\s*([;=,)])", body):
                if m.group(1) not in td.names or m.group(3) not in taken:
                    continue
                if m.group(1) in ("return", "goto", "case", "else", "delete"):
                    continue
                k = o + m.start(2)
                if k in rep:
                    continue
                rep[k] = (k + 1, "* " + P32 + " ")
                cnt["addrlocal"] += 1
        # ---- dptr: every other `T **` (locals, parameters, return types, prototypes):
        # a pointer to a pointer in game code points at a game-memory slot (a list
        # link, a table entry, an out-parameter into an object), so its pointee is
        # a 4-byte pointer.  Applied to every file alike (headers and protos too),
        # so declarations stay consistent.
        # (macro bodies too: `#define FIND(s) Obj **rec; ...`; `T ***`: every star
        # but the last)
        code_d = blank(raw, keep_define=True)
        if not os.environ.get("RG_PTR32_NO_DPTR"):
            for m in re.finditer(r"\b(" + ID + r")((?:\s*(?:const\s*|volatile\s*)*\*){2,})", code_d):
                if m.group(1) not in td.names:
                    continue
                stars = [m.start(2) + i for i, ch in enumerate(m.group(2)) if ch == "*"]
                for p in stars[:-1]:
                    if p in rep:
                        continue
                    rep[p] = (p + 1, "* " + P32 + " ")
                    cnt["dptr"] += 1
            # a pointer to a function pointer, `R (**)(..)` / `R (**name)(..)`: the
            # pointee is a function pointer in game memory (MenuGridCursorInput_28e170
            # reads its callback table through `*(void (**)(void *, s32))(desc + 0x20)`)
            # (the dereferenced cast form `*(R (**)(A))(E)`; clang accepts no __ptr32 in
            # a function pointer's abstract declarator, so the 4-byte slot is read as a
            # u32 and converted: `((R (*)(A))(unsigned long long)*(unsigned int *)(E))`)
            for m in re.finditer(r"\((?P<ret>[ \t]*[A-Za-z_][\w \t\*]*?)\(\s*\*\s*\*\s*\)\s*"
                                 r"\((?P<args>[^()]*)\)\s*\)\s*\(", code_d):
                k = m.start() - 1
                while k >= 0 and code_d[k] in " \t":
                    k -= 1
                if k < 0 or code_d[k] != "*" or k in rep:
                    continue
                e = match_close(code_d, m.end() - 1)
                if e < 0:
                    continue
                expr = raw[m.end() - 1:e + 1]
                rep[k] = (e + 1, "((" + m.group("ret").strip() + " (*)(" + m.group("args")
                          + "))(unsigned long long)*(unsigned int *)" + expr + ")")
                cnt["dptr-fn"] += 1
            # a field-access macro `#define F(p, T, o) (*(T *)((u8 *)(p) + (o)))` invoked
            # with a pointer type (`F(nm, char *, 0x10)`, SaveHeaderBuild_3e5520): the slot
            # is a 4-byte game-memory word, so the argument becomes `char * RG_P32`
            for dm in re.finditer(r"(?m)^[ \t]*#[ \t]*define[ \t]+(" + ID + r")\(([^)]*)\)(.*)$", raw):
                mname = dm.group(1)
                mparams = [x.strip() for x in dm.group(2).split(",")]
                tpos = [i for i, x in enumerate(mparams)
                        if x and re.search(r"\(\s*" + re.escape(x) + r"\s*\*\s*\)", dm.group(3))]
                if not tpos:
                    continue
                for inv in re.finditer(r"\b" + re.escape(mname) + r"\s*\(", code_d):
                    if inv.start() >= dm.start() and inv.start() < dm.end():
                        continue
                    o = inv.end() - 1
                    c = match_close(code_d, o)
                    args = split_top(code_d[o + 1:c], ",")
                    for i in tpos:
                        if i >= len(args):
                            continue
                        a0, a1 = args[i]
                        seg = code_d[o + 1 + a0:o + 1 + a1]
                        if not seg.rstrip().endswith("*") or P32 in seg:
                            continue
                        p = o + 1 + a0 + len(seg.rstrip())
                        if p in ins:
                            continue
                        ins[p] = " " + P32
                        cnt["dptr-macro"] += 1
            # a pointer typedef with a star (`Native *f`, `PX *pp`, casts `(PX *)`) is a
            # pointer to a pointer as well: the typedef'd pointee gets RG_P32
            ptd = (td.ptr | td.fnptr) - {"va_list"}
            if ptd:
                rx = re.compile(r"\b(" + "|".join(sorted(map(re.escape, ptd), key=len, reverse=True))
                                + r")\b(?=\s*(?:const\s*|volatile\s*)*\*)")
                for m in rx.finditer(code_d):
                    p = m.end()
                    if p in ins:
                        continue
                    k = m.start() - 1
                    while k >= 0 and code_d[k] in " \t\r\n":
                        k -= 1
                    if k >= 0 and (code_d[k] == "." or code_d[k - 1:k + 1] == "->"):
                        continue        # a member access named like a typedef
                    ins[p] = " " + P32
                    cnt["dptr-td"] += 1
        # ---- calls through RG_P32 function pointers
        wraps: list[tuple[int, int]] = []
        if fn_names or fn_globals:
            # macro bodies count as call sites too (`#define NOTIFY(v) (v)->cb(..)`)
            dsp = define_spans(raw)
            # a C++ method of the same name (camera_cpp.h retarget()) is not a pointer
            if relpath.endswith(".cpp"):
                fn_names -= (hmeth | self._method_names(code))
            wraps = self._fn_calls(code_d, sorted(fnb + dsp), fn_names, fn_globals,
                                   relpath.endswith(".cpp"))
            for a, b in wraps:
                ins[a] = ins.get(a, "") + FPC + "("
                ins[b] = ")" + ins.get(b, "")
                cnt["fncall"] += 1
                self.rows.append(f"{relpath}\t{line(a)}\tfncall\t{' '.join(code[a:b].split())}")
        if not rep and not ins:
            return raw, 0
        # apply: inserts at offsets + star replacements (star offsets never coincide
        # with insert offsets of a different kind except `)` after a wrapped name)
        out = []
        last = 0
        keys = sorted(set(rep) | set(ins))
        for p in keys:
            if p < last:
                continue
            out.append(raw[last:p])
            if p in ins:
                out.append(ins[p])
            if p in rep:
                end, txt = rep[p]
                out.append(txt)
                last = end
            else:
                last = p
        out.append(raw[last:])
        n = sum(v for k, v in cnt.items() if not k.endswith("-fn"))
        self.stats.update(cnt)
        return "".join(out), n

    # a postfix expression ending at `end` (exclusive), walking backwards
    WS = " \t\r\n"
    KW = {"return", "if", "while", "for", "switch", "case", "else", "do", "throw", "new",
          "delete", "sizeof", "typeof", "__typeof__", "goto"}

    @classmethod
    def _postfix_start(cls, code: str, end: int) -> int:
        def back_ws(j):
            while j >= 0 and code[j] in cls.WS:
                j -= 1
            return j

        i = end
        while True:
            j = back_ws(i - 1)
            if j < 0:
                return i
            ch = code[j]
            if ch.isalnum() or ch == "_":
                k = j
                while k >= 0 and (code[k].isalnum() or code[k] == "_"):
                    k -= 1
                word = code[k + 1:j + 1]
                if word in cls.KW:
                    return i
                i = k + 1
                q = back_ws(i - 1)
                if q >= 1 and code[q - 1:q + 1] == "->":
                    i = q - 1
                    continue
                if q >= 1 and code[q - 1:q + 1] == "::":
                    i = q - 1
                    continue
                if q >= 0 and code[q] == "." and not (q >= 1 and code[q - 1].isdigit()):
                    i = q
                    continue
                return i
            if ch in ")]":
                depth = 0
                k = j
                while k >= 0:
                    if code[k] in ")]":
                        depth += 1
                    elif code[k] in "([":
                        depth -= 1
                        if depth == 0:
                            break
                    k -= 1
                if k < 0:
                    return i
                q = back_ws(k - 1)
                if q >= 0 and (code[q].isalnum() or code[q] == "_" or code[q] in ")]"):
                    # a call / index suffix -- unless the word before is a keyword
                    if code[q].isalnum() or code[q] == "_":
                        w = q
                        while w >= 0 and (code[w].isalnum() or code[w] == "_"):
                            w -= 1
                        if code[w + 1:q + 1] in cls.KW:
                            return k
                    i = k
                    continue
                return k
            return i

    def _fn_calls(self, code, fnb, fn_names, fn_globals, cxx) -> list[tuple[int, int]]:
        out = []
        import bisect

        def in_fn(p):
            i = bisect.bisect_right(fnb, (p, 1 << 62)) - 1
            while i >= 0:
                o, c = fnb[i]
                if o < p < c:
                    return True
                i -= 1
                if i >= 0 and fnb[i][1] < p - 500000:
                    break
            return False

        def after_name(p):
            """offset after `name` + any `[..]` groups if a call `(` follows, else None;
            also returns whether it is the `(*expr)(` form's inner end."""
            q = p
            while True:
                while q < len(code) and code[q] in " \t\r\n":
                    q += 1
                if q < len(code) and code[q] == "[":
                    q = match_close(code, q) + 1
                    continue
                break
            return q

        if fn_names:
            rx = re.compile(r"(->|\.)\s*(" + "|".join(sorted(map(re.escape, fn_names), key=len,
                                                              reverse=True)) + r")\b")
            for m in rx.finditer(code):
                if m.group(1) == "." and m.start() > 0 and code[m.start() - 1].isdigit():
                    continue
                if not in_fn(m.start()):
                    continue
                endname = m.end()
                q = after_name(endname)
                # end of the wrapped expression: after any [..] groups
                e = endname
                while True:
                    w = e
                    while w < len(code) and code[w] in " \t\r\n":
                        w += 1
                    if w < len(code) and code[w] == "[":
                        e = match_close(code, w) + 1
                        continue
                    break
                if q < len(code) and code[q] == "(":
                    s = self._postfix_start(code, m.start())
                    out.append((s, e))
                elif q < len(code) and code[q] == ")":
                    # `(*expr)(`
                    s = self._postfix_start(code, m.start())
                    k = s - 1
                    while k >= 0 and code[k] in " \t\r\n":
                        k -= 1
                    if k >= 1 and code[k] == "*":
                        k2 = k - 1
                        while k2 >= 0 and code[k2] in " \t\r\n*":
                            k2 -= 1
                        r = q + 1
                        while r < len(code) and code[r] in " \t\r\n":
                            r += 1
                        if k2 >= 0 and code[k2] == "(" and r < len(code) and code[r] == "(":
                            out.append((s, e))
        if fn_globals:
            rx = re.compile(r"(?<![\w.>])(" + "|".join(sorted(map(re.escape, fn_globals), key=len,
                                                               reverse=True)) + r")\b")
            for m in rx.finditer(code):
                if not in_fn(m.start()):
                    continue
                # not a member access (`x.name`, `x->name`)
                k = m.start() - 1
                while k >= 0 and code[k] in " \t\r\n":
                    k -= 1
                if k >= 0 and (code[k] == "." or code[k - 1:k + 1] == "->"):
                    continue
                e = m.end()
                q = after_name(e)
                ee = e
                while True:
                    w = ee
                    while w < len(code) and code[w] in " \t\r\n":
                        w += 1
                    if w < len(code) and code[w] == "[":
                        ee = match_close(code, w) + 1
                        continue
                    break
                if q < len(code) and code[q] == "(":
                    out.append((m.start(), ee))
                elif q < len(code) and code[q] == ")" and k >= 0 and code[k] == "*":
                    out.append((m.start(), ee))
        # drop nested duplicates (keep outermost per start)
        seen = set()
        res = []
        for a, b in sorted(set(out)):
            if (a, b) in seen:
                continue
            seen.add((a, b))
            res.append((a, b))
        return res

    def extra_outputs(self) -> dict[str, bytes]:
        return {"PTR32.tsv": ("relpath\tline\trule\ttext\n" + "\n".join(self.rows) + "\n").encode()}

    def report(self) -> str:
        return "ptr32: " + ", ".join(f"{k}={v}" for k, v in sorted(self.stats.items()))


def main(argv):
    """Debug: rewrite one file to stdout (headers from --inc DIR)."""
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("file")
    ap.add_argument("--inc", action="append", default=[])
    a = ap.parse_args(argv)
    st = Ptr32Stage()
    hdr = {}
    for d in a.inc:
        for h in Path(d).rglob("*.h"):
            hdr[str(h)] = h.read_text(encoding="utf-8", errors="replace")
    st.prepare_headers(hdr)
    t = Path(a.file).read_text(encoding="utf-8", errors="surrogateescape")
    out, n = st.rewrite(Path(a.file).name, t)
    sys.stdout.write(out)
    sys.stderr.write(st.report() + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
