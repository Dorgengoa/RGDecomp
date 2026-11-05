#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Call-ABI census and the derive pass `narrowabi` (docs/X64-PLAN.md sections 0.7, 0.14).

i686 cdecl passes every argument in a 4-byte stack word (1/2-byte integers EXTENDED to
32 bits, IR `signext` / `zeroext`), returns integers in EAX (narrow ones extended) and
floats on the x87 stack.  Win64 passes the first four arguments in registers chosen BY
POSITION AND TYPE (RCX/RDX/R8/R9 or XMM0-3), the rest in 8-byte stack slots, and extends
nothing but bool.  A caller whose declaration disagrees with the callee's definition was
harmless on i686 in several ways that are not harmless on x64:
  narrow   declaration s16, definition s32: the upper register bits are garbage
           (CharaEffEntrySpawn_22fad0 -> GetObjNodeByName_1ce3a0: the first battle's hit
           effects at the origin, run hash parted at field 24,824)
  int-ptr  declaration 32-bit integer, definition pointer: Win64 stores only the low 4
           bytes of a stack argument (ModelMeshUpdateBoundsMaybe_150170 ->
           ModelCalcNodesBoundsMaybe_1531c0 arg 4)
  ret      declaration 32-bit, definition narrow: EAX's upper bits are garbage
The derive pass rewrites the CALLER's declaration (FIX rows):
  argument  view narrow (or bool), definition wider integer -> s32 / u32 (view's
            signedness: the caller extends as the i686 caller did)
  pointer   view 1/2/4-byte integer or bool, definition pointer -> long long /
            unsigned long long (pointers are below 2 GB: zero- and sign-extension agree;
            the low 32 bits are what the i686 callee read)
  size      view 32-bit integer, definition size_t / intptr_t -> __SIZE_TYPE__
  return    view integer, definition narrow (different type) -> the definition's type
            (the caller extends the callee's low bits as the i686 callee did)
  ptr-ret   view pointer, definition 32-bit integer return: the DEFINITION's return
            type becomes long long / unsigned long long (only in the derived tree; every
            other caller reads the low half, as before)
A declaration in the TU that defines the function is never rewritten; C++ declarations
with C++ linkage are matched only by return type (their parameters are in the mangled
name, a mismatch would not link); headers are rewritten too (game/include,
overrides/.../include) when no TU that includes them defines the function.

The census (this script) classifies every position where a caller's view and the
definition disagree:
  FIX     the derive pass rewrites it (left in a derived tree = --check fails)
  REAL    a Win64 ABI difference the pass cannot rewrite (--check fails unless the row
          is in tools/x64/narrowabi_accept.tsv with a reason)
  INSPECT a pairing the rules do not decide (records of unknown size, ...): fails
          --check until triaged into narrowabi_accept.tsv or a rule
  LINUX   differs only under SysV LP64 (`long` = 8 bytes, Win64 LLP64 keeps it 4; an
          all-float record travels in XMM registers under SysV, in a GPR on Win64)
  I686    already different on i686 (argument words shifted, x87 vs EAX return, garbage
          return): x64 behaves no worse; listed for the record
  BENIGN  same value on both (pointer view of an integer, wider view of a narrower
          argument, void view of a return, extra arguments, same-size signedness)

    python tools/x64/narrowabi.py [--root build/x64-src] [--tree game ..] [--check]
                                  [--tsv FILE] [--all]
    python tools/x64/narrowabi.py --control     # --check must fail on an injected pair

Parsing: comments, strings, preprocessor lines and attribute / asm-label groups are
blanked; signatures are found by balanced parentheses (function-pointer parameters,
multi-line lists); types are resolved through builtin specifiers (`long long`,
`unsigned long long`, ...), the header + per-file typedefs, object-like type macros
(`#define RT bool`) and record bodies (x64 size and alignment, RG_P32 words, MS
bit-field units), so records of 1/2/4/8 bytes compare as the integer Win64 passes.
"""
from __future__ import annotations

import argparse
import bisect
import re
import sys
import tempfile
from collections import Counter, namedtuple
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
ACCEPT = Path(__file__).resolve().parent / "narrowabi_accept.tsv"


def compiled_rels(src_root: Path = PORT) -> set[str]:
    """"tree/relpath" of every .c/.cpp the build compiles (tools/gamesrcs.py select:
    an override replaces its game/ file, PORT_PROVIDED and `excluded` game files are not
    compiled, a missing/ stand-in the snapshot now defines is skipped).  The census and
    the derive pass index only these TUs (plus every header): a superseded game/ file's
    definition or caller declaration is not in any exe (abifix 11-02: 166 of the 173
    I686 rows were the `excluded` asm syscall wrappers `void WaitSema(void)` .. and the
    replaced game/ RevelationBoardDrawSprite_34c170.c)"""
    sys.path.insert(0, str(PORT / "tools"))
    import gamesrcs
    src_root = Path(src_root)
    by = gamesrcs.select(src_root / "game", src_root / "overrides", src_root / "missing",
                         log=lambda *_a: None)[0]
    out = set()
    base = src_root.resolve()
    for paths in by.values():
        for q in paths:
            out.add(Path(q).relative_to(base).as_posix())
    return out


def keep_compiled(files, root: Path, rels: set[str]):
    """files under root/{game,overrides,missing}: drop a .c/.cpp not in rels"""
    root = Path(root).resolve()
    keep = []
    for f in files:
        fp = Path(f)
        if fp.suffix in (".c", ".cpp"):
            try:
                rel = fp.resolve().relative_to(root).as_posix()
            except ValueError:
                keep.append(f)
                continue
            if rel.split("/", 1)[0] in ("game", "overrides", "missing") and rel not in rels:
                continue
        keep.append(f)
    return keep
ID = r"[A-Za-z_]\w*"
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "else", "do", "case", "goto", "new",
            "delete", "defined", "operator", "typedef", "throw", "default", "__typeof__", "typeof",
            "_Static_assert", "static_assert", "alignof", "__alignof__", "decltype", "using",
            "template", "co_return", "asm", "__asm__", "__asm", "__builtin_offsetof", "offsetof"}
QUALS = {"const", "volatile", "register", "restrict", "__restrict", "__restrict__", "static", "extern",
         "inline", "__inline", "__inline__", "__forceinline", "RG_P32", "__cdecl", "__stdcall",
         "__fastcall", "__extension__", "auto", "mutable", "virtual", "explicit", "friend", "constexpr", "noexcept"}
BASEKW = {"unsigned", "signed", "char", "short", "int", "long", "float", "double", "void", "bool",
          "_Bool", "__int64", "__int32", "__int16", "__int8", "wchar_t"}
TAGKW = {"struct", "union", "class", "enum"}

# kind: void int ptr float bool struct va unk;  size: i686 bytes;  lp: 'long' (8 on LP64),
# 'size' (pointer-sized integer on x64), '' otherwise
Ty = namedtuple("Ty", "kind size signed lp name")
VOID = Ty("void", 0, False, "", "void")
PTR = Ty("ptr", 4, False, "", "*")
VA = Ty("va", 0, False, "", "...")


def I(size, signed, lp="", name=""):
    return Ty("int", size, signed, lp, name)


BUILTIN_TD = {
    "s8": I(1, True), "u8": I(1, False), "s16": I(2, True), "u16": I(2, False), "s32": I(4, True),
    "u32": I(4, False), "s64": I(8, True), "u64": I(8, False), "f32": Ty("float", 4, True, "", "float"),
    "f64": Ty("float", 8, True, "", "double"), "int8_t": I(1, True), "uint8_t": I(1, False),
    "int16_t": I(2, True), "uint16_t": I(2, False), "int32_t": I(4, True), "uint32_t": I(4, False),
    "int64_t": I(8, True), "uint64_t": I(8, False), "size_t": I(4, False, "size"),
    "__SIZE_TYPE__": I(4, False, "size"), "ssize_t": I(4, True, "size"), "intptr_t": I(4, True, "size"),
    "uintptr_t": I(4, False, "size"), "ptrdiff_t": I(4, True, "size"), "vc_u8": I(1, False),
    "vc_u32": I(4, False), "uchar": I(1, False), "ushort": I(2, False), "uint": I(4, False),
    "ulong": I(4, False, "long"), "BOOL": I(4, True), "va_list": PTR, "__builtin_va_list": PTR,
    "qword": Ty("struct", 16, False, "", "qword"), "u128": Ty("struct", 16, False, "", "u128"),
}


def tyname(t: Ty) -> str:
    if t.kind == "int":
        n = {1: "8", 2: "16", 4: "32", 8: "64"}.get(t.size, str(t.size * 8))
        return ("s" if t.signed else "u") + n + ("(long)" if t.lp == "long" else "(size)" if t.lp else "")
    if t.kind == "float":
        return "f32" if t.size == 4 else "f64"
    if t.kind in ("struct", "unk"):
        return t.kind + ":" + t.name
    return t.name if t.kind in ("void", "va") else t.kind


# ---------------------------------------------------------------- lexing helpers

ATTR = re.compile(r"\b(?:__attribute__|__declspec|__asm__|__asm|asm|alignas|_Alignas)\s*\(")


def blank(s: str) -> str:
    """comments, string / char literal contents, preprocessor lines and attribute /
    asm-label groups -> spaces (positions and newlines kept)"""
    out = list(s)
    n = len(s)

    def wipe(a, b):
        for k in range(a, b):
            if out[k] != "\n":
                out[k] = " "
    i = 0
    bol = True
    while i < n:
        c = s[i]
        if bol and c in " \t":
            i += 1
            continue
        if bol and c == "#":
            j = i
            while True:
                e = s.find("\n", j)
                e = n if e < 0 else e
                if e > 0 and s[e - 1] == "\\" and e < n:
                    j = e + 1
                    continue
                break
            # comments inside a directive are wiped with it
            wipe(i, e)
            i = e
            continue
        bol = False
        if c == "\n":
            bol = True
            i += 1
        elif s.startswith("//", i):
            j = s.find("\n", i)
            j = n if j < 0 else j
            wipe(i, j)
            i = j
        elif s.startswith("/*", i):
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            wipe(i, j)
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and s[j] != c and s[j] != "\n":
                j += 2 if s[j] == "\\" else 1
            if not (c == '"' and s[i:j + 1] == '"C"'):
                wipe(i + 1, min(j, n))
            i = j + 1
        else:
            i += 1
    t = "".join(out)
    # attribute groups: __attribute__((..)), __declspec(..), asm labels
    res = list(t)
    for m in ATTR.finditer(t):
        d, k = 1, m.end()
        while k < n and d:
            d += {"(": 1, ")": -1}.get(t[k], 0)
            k += 1
        for q in range(m.start(), k):
            if res[q] != "\n":
                res[q] = " "
    return "".join(res)


def split_top(s: str) -> list[tuple[int, int]]:
    out, d, st = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([{<":
            d += 1
        elif ch in ")]}>":
            d -= 1
        elif ch == "," and d == 0:
            out.append((st, i))
            st = i + 1
    out.append((st, len(s)))
    return out


TOK = re.compile(r"[A-Za-z_]\w*|::|\.\.\.|[*&\[\]()<>]")


def classify(text: str, tds: dict, param: bool):
    """(Ty, span) of one parameter / return type text (attributes already blanked);
    span = (start, end) of the type-specifier tokens inside text (for a rewrite)"""
    toks = [(m.group(0), m.start(), m.end()) for m in TOK.finditer(text)]
    words = [t for t in toks if t[0] not in QUALS]
    if not words:
        return None, None
    if words[0][0] == "...":
        return VA, None
    syms = [t[0] for t in words]
    if "(" in syms:
        # function pointer / pointer-to-array declarator, or a function-type parameter
        return PTR, None
    if "*" in syms or "&" in syms or ("[" in syms and param):
        return PTR, None
    if "<" in syms or "::" in syms:
        return Ty("unk", 0, False, "", "".join(syms)), None
    if syms[0] in TAGKW:
        if len(syms) < 2:
            return Ty("unk", 0, False, "", syms[0]), None
        if syms[0] == "enum":
            return I(4, True, "", "enum"), None
        t = tds.get("struct " + syms[1])
        return (t._replace(name=syms[1]) if t else Ty("struct", 0, 0, "", syms[1])), None
    base = [t for t in words if t[0] in BASEKW]
    if base and words[0][0] in BASEKW:
        b = [t[0] for t in base]
        span = (base[0][1], base[-1][2])
        nlong = b.count("long")
        uns = "unsigned" in b
        if "void" in b:
            return VOID, span
        if "float" in b:
            return Ty("float", 4, True, "", "float"), span
        if "double" in b:
            return Ty("float", 8, True, "", "double"), span
        if "bool" in b or "_Bool" in b:
            return Ty("bool", 1, False, "", "bool"), span
        if "char" in b or "__int8" in b:
            return I(1, not uns), span
        if "short" in b or "__int16" in b:
            return I(2, not uns), span
        if nlong >= 2 or "__int64" in b:
            return I(8, not uns), span
        if nlong == 1:
            return I(4, not uns, "long"), span
        if "wchar_t" in b:
            return I(2, False), span
        return I(4, not uns), span
    name = words[0][0]
    span = (words[0][1], words[0][2])
    t = tds.get(name) or BUILTIN_TD.get(name) or tds.get("struct " + name)   # C++: tags are types
    if t is None:
        return Ty("unk", 0, False, "", name), span
    return t, span


TYPEDEF = re.compile(r"\btypedef\b")
RECORD = re.compile(r"\b(struct|union|class)\s+(?:(" + ID + r")\s*)?\{|\b(struct|union)\s*\{")
ALIGNED = re.compile(r"aligned\s*\(\s*(\d+)\s*\)")
DEFTYPE = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+(" + ID + r")[ \t]+((?:(?:unsigned|signed|const|"
                     r"struct|union|enum)[ \t]+)*" + ID + r"(?:[ \t]+" + ID + r")?(?:[ \t]*\*)*)[ \t]*$")


def _dims(txt):
    """product of the [..] dimensions in a declarator text, None when not constant"""
    n = 1
    for e in re.findall(r"\[([^\]]*)\]", txt):
        e = e.strip()
        if not e:
            return 0
        if not re.fullmatch(r"[0-9a-fA-FxXuUlL+\-*/() \t]+", e):
            return None
        try:
            n *= int(eval(re.sub(r"(?<=[0-9a-fA-F])[uUlL]+", "", e), {"__builtins__": {}}))
        except Exception:
            return None
    return n


def _scalar(t, ptr_words: bool):
    """(size, align) of a member type on x64 (Win64 layout), None when unknown"""
    if t is None:
        return None
    if t.kind == "ptr":
        return (4, 4) if ptr_words else (8, 8)
    if t.kind in ("int", "float"):
        return (t.size, t.size)
    if t.kind == "bool":
        return (1, 1)
    if t.kind == "struct" and t.size:
        return (t.size, t.signed or 1)
    return None


def _members(body: str):
    out, d, st = [], 0, 0
    for k, ch in enumerate(body):
        if ch in "({[":
            d += 1
        elif ch in ")}]":
            d -= 1
        elif ch == ";" and d == 0:
            out.append((st, k))
            st = k + 1
    return out


def record_size(body: str, orig_body: str, look: dict, union: bool):
    """(size, align) of a struct / union body on x64, None when a member is unknown
    (Win64 layout: natural alignment, MS bit-field units)"""
    off = size = 0
    align = 1
    flt = None          # SysV SSE class: every scalar member a float (approximation)
    bf_unit = bf_left = 0
    for a, b in _members(body):
        mt = body[a:b]
        mo = orig_body[a:b]
        if not mt.strip():
            continue
        am = ALIGNED.search(mo)
        malign = int(am.group(1)) if am else None
        basetxt = None
        if "{" in mt:
            j = mt.index("{")
            e = mt.rindex("}")
            inner = record_size(mt[j + 1:e], mo[j + 1:e], look, bool(re.search(r"\bunion\b", mt[:j])))
            if inner is None:
                return None
            base = Ty("struct", inner[0], inner[1], "flt" if inner[2] else "", "anon")
            decls = mt[e + 1:] if mt[e + 1:].strip() else " __anon"
        else:
            parts = split_top(mt)
            first = mt[parts[0][0]:parts[0][1]]
            cut = re.split(r"[:\[]", first)[0]
            nms = [x for x in re.finditer(ID, cut) if x.group(0) not in QUALS and x.group(0) != "RG_P32"]
            if not nms:
                return None
            # the type words, then the declarator name (none: an unnamed bit-field)
            if nms[0].group(0) in BASEKW:
                k = 0
                while k < len(nms) and nms[k].group(0) in BASEKW:
                    k += 1
            elif nms[0].group(0) in TAGKW:
                k = 2
            else:
                k = 1
            nm = nms[k] if k < len(nms) else None
            if nm is None and ":" not in first:
                return None
            basetxt = (cut[:nm.start()] if nm else cut)
            base, _ = classify(basetxt.replace("*", " "), look, False)
            if "*" in basetxt:
                base = PTR
            decls = first[(nm.start() if nm else len(cut)):] + "".join("," + mt[x:y] for x, y in parts[1:])
        for dcl in decls.split(","):
            if not dcl.strip():
                continue
            ptr = "*" in dcl or (base is not None and base.kind == "ptr")
            t = PTR if ptr else base
            isf = t is not None and (t.kind == "float" or t.lp == "flt")
            flt = isf if flt is None else (flt and isf)
            sa = _scalar(t, "RG_P32" in dcl or "RG_P32" in (basetxt or ""))
            if sa is None:
                return None
            esz, eal = sa
            if malign:
                eal = max(eal, malign)
            bm = re.search(r":\s*(\d+)\s*$", dcl)
            if bm and not union:
                bits = int(bm.group(1))
                if bits == 0:
                    bf_left = 0
                    continue
                if bf_unit == esz and bf_left >= bits:
                    bf_left -= bits
                    continue
                off = (off + eal - 1) // eal * eal + esz
                bf_unit, bf_left = esz, esz * 8 - bits
                align = max(align, eal)
                continue
            bf_unit = bf_left = 0
            cnt = _dims(dcl)
            if cnt is None:
                return None
            msz = esz * cnt
            align = max(align, eal)
            if union:
                size = max(size, msz)
            else:
                off = (off + eal - 1) // eal * eal + msz
    total = size if union else off
    return (total + align - 1) // align * align, align, bool(flt)


def records(code: str, orig: str, look: dict) -> dict:
    """`struct Tag` / typedef name -> Ty('struct', x64 size, align in .signed) for every
    record body in blanked code (aligned() attributes read from the original text)"""
    out = {}
    for m in RECORD.finditer(code):
        j = m.end() - 1
        d, k = 0, j
        while k < len(code):
            if code[k] == "{":
                d += 1
            elif code[k] == "}":
                d -= 1
                if d == 0:
                    break
            k += 1
        if k >= len(code):
            continue
        kw = m.group(1) or m.group(3)
        tag = m.group(2)
        sz = record_size(code[j + 1:k], orig[j + 1:k], {**look, **out}, kw == "union")
        tail_end = code.find(";", k)
        tail = orig[k:tail_end if tail_end > 0 else k]
        am = ALIGNED.search(tail) or ALIGNED.search(orig[m.start():j])
        if sz is not None and am:
            al = max(sz[1], int(am.group(1)))
            sz = ((sz[0] + al - 1) // al * al, al, sz[2])
        t = Ty("struct", sz[0], sz[1], "flt" if sz[2] else "", tag or "anon") if sz else             Ty("struct", 0, 0, "", tag or "anon")
        if tag:
            out["struct " + tag] = t
        pre = code[max(0, m.start() - 40):m.start()]
        if re.search(r"\btypedef\s*$", pre) and tail_end > 0:
            for x in code[k + 1:tail_end].split(","):
                nm = [y for y in re.findall(ID, x) if y not in QUALS]
                if nm:
                    out[nm[-1]] = PTR if ("*" in x or "[" in x) else t._replace(name=nm[-1])
    return out


def typedefs(code: str, tds: dict | None = None, orig: str | None = None) -> dict:
    """name -> Ty for every `typedef` (and `struct Tag` -> its record) in blanked code,
    resolved through `tds` too"""
    look = dict(tds or {})
    out = records(code, orig if orig is not None else code, look)
    look.update(out)
    for m in DEFTYPE.finditer(orig if orig is not None else ""):
        t, _ = classify(m.group(2), look, False)
        if t is not None and t.kind not in ("unk", "va") and m.group(1) not in look:
            out[m.group(1)] = t
            look[m.group(1)] = t
    n = len(code)
    for m in TYPEDEF.finditer(code):
        i, d = m.end(), 0
        buf = []
        hadbody = False
        while i < n:
            ch = code[i]
            if ch == "{":
                d += 1
                hadbody = True
            elif ch == "}":
                d -= 1
            elif ch == ";" and d == 0:
                break
            elif d == 0:
                buf.append(ch)
            i += 1
        if hadbody:
            continue                      # records() named it
        st = "".join(buf)
        parts = split_top(st)
        if not parts:
            continue
        first = st[parts[0][0]:parts[0][1]]
        fm = re.search(r"\(\s*[*&^]\s*(" + ID + r")\s*\)", first)
        if fm:
            out[fm.group(1)] = PTR
            look[fm.group(1)] = PTR
            continue
        ids = [x for x in re.finditer(ID, first) if x.group(0) not in QUALS]
        if not ids:
            continue
        nm = ids[-1]
        rest = first[nm.end():]
        basetxt = first[:nm.start()]
        if "(" in rest:
            bt = PTR                          # a function type: decays to a pointer
        elif "*" in basetxt:
            bt = PTR
        elif "[" in rest:
            et, _ = classify(basetxt, look, False)
            sa = _scalar(et, "RG_P32" in first) if et is not None else None
            cnt = _dims(rest)
            # an array typedef: by value only inside records (a parameter decays)
            bt = Ty("struct", sa[0] * cnt if sa and cnt else 0, sa[1] if sa else 0, "array", nm.group(0))
        else:
            bt, _ = classify(basetxt, look, False)
            if bt is None:
                continue
            if bt.kind in ("struct", "unk") and re.match(r"\s*(struct|union|class)\b", basetxt):
                tagged = look.get("struct " + bt.name)
                bt = (tagged or Ty("struct", 0, 0, "", bt.name))._replace(name=nm.group(0))
        out[nm.group(0)] = bt
        look[nm.group(0)] = bt
        base_clean = basetxt.replace("*", " ")
        for a, b in parts[1:]:
            dcl = st[a:b]
            dm = re.search(ID, dcl)
            if not dm:
                continue
            if "*" in dcl or "(" in dcl or "[" in dcl:
                out[dm.group(0)] = PTR
            else:
                bt2, _ = classify(base_clean, look, False)
                if bt2 is not None:
                    out[dm.group(0)] = bt2
            look[dm.group(0)] = out.get(dm.group(0), PTR)
    return out


# ---------------------------------------------------------------- signatures

Sig = namedtuple("Sig", "kind name ret params start pstart pend rstart rend clink static line "
                        "variadic proto rspan pspans ptext rtext")
CAND = re.compile(r"\b(" + ID + r")\s*\(")
DELIM = re.compile(r"[;{}]")


def scopes(code: str):
    """for every '{' / '}' a scope kind: 'file' (extern "C" / namespace), 'rec'
    (struct / class / union / enum body), 'blk' (function body, init, control)"""
    events = []          # (pos, depth_after, kind-of-innermost)
    stack = []
    last = 0
    for m in re.finditer(r"[;{}]", code):
        ch = m.group(0)
        p = m.start()
        if ch == "{":
            head = code[last:p]
            if re.search(r'extern\s*"C"\s*$', head) or re.search(r"\bnamespace\b[^(){};=]*$", head):
                k = "file"
            elif re.search(r"\b(struct|class|union|enum)\b[^(){};=]*$", head) and "=" not in head:
                k = "rec"
            else:
                k = "blk"
            stack.append(k)
        elif ch == "}":
            if stack:
                stack.pop()
        last = p + 1
        events.append((p, tuple(stack)))
    return events


def scope_at(events, keys, pos):
    i = bisect.bisect_right(keys, pos) - 1
    return events[i][1] if i >= 0 else ()


def sigs(text: str, cxx: bool, tds: dict, code: str | None = None) -> list:
    code = blank(text) if code is None else code
    events = scopes(code)
    keys = [e[0] for e in events]
    dl = [m.start() for m in DELIM.finditer(code)]
    lines = [0] + [m.end() for m in re.finditer("\n", code)]
    out = []
    n = len(code)
    for m in CAND.finditer(code):
        name = m.group(1)
        if name in KEYWORDS or name in QUALS or name in BASEKW or name in TAGKW:
            continue
        # statement start
        k = bisect.bisect_left(dl, m.start()) - 1
        st = dl[k] + 1 if k >= 0 else 0
        pre = code[st:m.start()]
        # a label `x:` or access specifier ends the head
        pc = pre.rfind(":")
        if pc >= 0 and not (pc > 0 and pre[pc - 1] == ":") and pre[pc + 1:pc + 2] != ":":
            st = st + pc + 1
            pre = code[st:m.start()]
        if not re.fullmatch(r'[\sA-Za-z_0-9*&"]*', pre):
            continue
        ptoks = re.findall(ID + r'|"C"|\*|&', pre)
        if not ptoks or ptoks[-1] in KEYWORDS or any(t in KEYWORDS for t in ptoks):
            continue
        if not any(re.fullmatch(ID, t) and t not in QUALS for t in ptoks):
            continue
        # balanced parameter list
        i, d = m.end(), 1
        while i < n and d:
            ch = code[i]
            if ch == "(":
                d += 1
            elif ch == ")":
                d -= 1
            elif ch in ";{}":
                break
            i += 1
        if d:
            continue
        pend = i - 1
        j = i
        while j < n and code[j] in " \t\r\n":
            j += 1
        tail = ""
        while True:
            tm = re.match(r"(const|noexcept|override|final|throw\s*\(\s*\))\s*", code[j:])
            if not tm:
                break
            tail += tm.group(1)
            j += tm.end()
        if j >= n or code[j] not in ";{":
            continue
        if "const" in tail:
            continue                                   # member function
        sc = scope_at(events, keys, m.start())
        if "rec" in sc:
            continue
        inblk = "blk" in sc
        kind = "decl" if code[j] == ";" else "def"
        if kind == "def" and inblk:
            continue
        # C++ constructor-call / object definitions: `Foo x(1, 2);` look like a declaration
        # of x returning Foo; their arguments are expressions.  Kept only when every
        # parameter classifies as a type (below).
        clink = (not cxx) or '"C"' in pre or any(e == "file" for e in sc) and \
            _in_extern_c(code, events, keys, m.start())
        static = "static" in ptoks
        retxt = pre
        rstart = st
        # the return text without the leading storage words and extern "C"
        rt = re.sub(r'extern\s*"C"', lambda x: " " * len(x.group(0)), retxt)
        stars = rt.rstrip()
        ret_ptr = stars.endswith("*") or stars.endswith("&")
        ret, rspan = classify(rt, tds, False)
        if ret is None:
            continue
        if ret_ptr:
            ret, rspan = PTR, None
        ptxt = code[m.end():pend]
        pieces = split_top(ptxt) if ptxt.strip() else []
        params, spans = [], []
        variadic = False
        proto = True
        ok = True
        if not ptxt.strip():
            proto = cxx
        elif len(pieces) == 1 and ptxt.strip() == "void":
            pass
        else:
            for a, b in pieces:
                pt = ptxt[a:b]
                if not pt.strip():
                    ok = False
                    break
                t, sp = classify(pt, tds, True)
                if t is None:
                    ok = False
                    break
                if t.kind == "va":
                    variadic = True
                    continue
                # an expression, not a parameter (`Foo x(1, 2);`, `int a(b);`)
                if re.search(r"[-+/%^|!~=.]|\b0x|^\s*\d", pt) or (t.kind == "unk" and not re.search(ID + r"\s+" + ID, pt.strip()) and kind == "decl" and inblk and cxx):
                    ok = False
                    break
                if t.kind == "unk" and t.name not in tds and t.name not in BUILTIN_TD and inblk:
                    # `foo(x);` after a type word in a block: `T f(x)` with x a variable
                    if len(re.findall(ID, pt)) == 1 and cxx:
                        ok = False
                        break
                params.append(t)
                spans.append((m.end() + a + sp[0], m.end() + a + sp[1]) if sp else None)
        if not ok:
            continue
        line = bisect.bisect_right(lines, m.start())
        out.append(Sig(kind, name, ret, params, m.start(), m.end(), pend,
                       rstart, m.start(), clink, static, line, variadic, proto,
                       (rstart + rspan[0], rstart + rspan[1]) if rspan else None, spans,
                       [ptxt[a:b] for a, b in pieces], rt))
    return out


def _in_extern_c(code, events, keys, pos):
    # inside an `extern "C" {` block: scan back to its opening brace
    d = 0
    i = pos
    while i > 0:
        i -= 1
        ch = code[i]
        if ch == "}":
            d += 1
        elif ch == "{":
            if d == 0:
                head = code[max(0, i - 40):i]
                if re.search(r'extern\s*"C"\s*$', head):
                    return True
            else:
                d -= 1
    return False


# ---------------------------------------------------------------- tree index

def read(f) -> str:
    try:
        return Path(f).read_text(encoding="utf-8", errors="surrogateescape")
    except OSError:
        return ""


INCLUDE = re.compile(r'(?m)^[ \t]*#[ \t]*include[ \t]*[<"]([^>"]+)[>"]')


class Index:
    """global typedefs, definitions and the include graph of one tree set"""

    def __init__(self, files, inc_dirs=(), texts=None):
        """texts: {path: text} in place of reading the files (derive.py: the tree as
        the other x64 stages left it)"""
        self.files = [Path(f) for f in files]
        self.text = {}
        self.code = {}
        self.inc_dirs = [Path(d) for d in inc_dirs]
        self._sigs = {}
        hdr_tds = {}
        for f in self.files:
            t = texts[f] if texts is not None else read(f)
            self.text[f] = t
            self.code[f] = blank(t)
        for f in self.files:
            if f.suffix in (".h", ".hpp"):
                hdr_tds.update(typedefs(self.code[f], hdr_tds, self.text[f]))
        self.tds = hdr_tds
        self.defs: dict[str, list] = {}
        self.cxxdefs: dict[str, list] = {}
        self.local_tds = {}
        self._defs_done = False

    def tds_for(self, f):
        if f not in self.local_tds:
            c = self.code[f]
            loc = typedefs(c, self.tds, self.text[f]) if f.suffix not in (".h", ".hpp") else {}
            d = dict(self.tds)
            d.update(loc)
            self.local_tds[f] = d
        return self.local_tds[f]

    def sigs(self, f):
        if f not in self._sigs:
            self._sigs[f] = sigs(self.text[f], f.suffix in (".cpp", ".hpp"), self.tds_for(f), self.code[f])
            self.local_tds.pop(f, None)
        return self._sigs[f]

    def build_defs(self):
        for f in self.files:
            if f.suffix not in (".c", ".cpp"):
                continue
            for s in self.sigs(f):
                if s.kind != "def" or s.static:
                    continue
                tab = self.defs if s.clink else self.cxxdefs
                tab.setdefault(s.name, []).append((f, s))
        self._defs_done = True


# ---------------------------------------------------------------- comparison

def abi(t: Ty) -> Ty:
    """the Win64 passing form: a record of 1/2/4/8 bytes travels as an integer of that
    size (register or 8-byte slot, upper bits undefined); any other record by reference"""
    if t.kind == "struct" and t.lp != "array":
        if t.size in (1, 2, 4, 8):
            return Ty("int", t.size, False, "rec", t.name)
        if t.size:
            return Ty("ref", 8, False, "", t.name)
    return t


def _same_int(v: Ty, d: Ty) -> bool:
    return v.kind == d.kind == "int" and v.size == d.size and v.lp == d.lp


def cmp_arg(v0: Ty, d0: Ty):
    """(category, verdict) for one argument position, or None when they agree"""
    if v0 == d0 or (v0.kind == d0.kind == "ptr"):
        return None
    v, d = abi(v0), abi(d0)
    rec = "rec" in (v.lp, d.lp)
    if v.kind == "bool" and d.kind in ("int", "ptr"):
        v = I(1, False)
    if v.kind == "int" and d.kind == "bool":
        return "bool-def-arg", "BENIGN"            # the callee reads its low byte
    if v.kind == "int" and d.kind == "int":
        if v.size == d.size:
            if v.lp == "long" and d.lp != "long" or d.lp == "long" and v.lp != "long":
                return "lp64-long-arg", "LINUX"
            if d.lp == "size" and v.lp != "size":
                return "int-for-size-arg", "FIX"
            if "flt" in (v0.lp, d0.lp):
                return "rec-float-int-arg", "LINUX"      # SysV: SSE class, XMM register
            return ("rec-int-arg" if rec else "sign-arg"), "BENIGN"
        if v.size < d.size <= 4:
            if v.lp == "rec":
                # a 1/2-byte record for a wider integer: i686 stored the record's bytes
                # in a 4-byte word too (upper bytes not written): garbage on both
                return "rec-narrow-arg", "I686"
            return "narrow-arg", "FIX"
        if d.size < v.size <= 4:
            return ("wide-view-narrow-arg" if v.size == 4 else "narrow-wider-view-arg"), "BENIGN"
        if v.size < 8 and d.size == 8:
            return "int-for-s64-arg", "I686"          # i686: the words after it shift
        if v.size == 8 and d.size < 8:
            return "s64-for-int-arg", "I686"
    if v.kind == "int" and d.kind == "ptr":
        if v.size == 8:
            return None                      # the fix's own form (pointers below 2 GB)
        if v.lp == "rec":
            return "rec-for-ptr-arg", "REAL"
        return ("int-for-ptr-arg" if v.size == 4 else "narrow-for-ptr-arg"), "FIX"
    if v.kind == "ptr" and d.kind == "int":
        return ("ptr-for-int-arg" if d.size >= 4 else "ptr-for-narrow-arg"), "BENIGN"
    if v.kind == "ptr" and d.kind == "bool":
        return "ptr-for-bool-arg", "BENIGN"
    if v.kind == "float" and d.kind == "float":
        return "float-width-arg", "I686"
    if (v.kind == "float") != (d.kind == "float") and "unk" not in (v.kind, d.kind):
        if 8 in (v.size, d.size) and "float" in (v.kind, d.kind) and \
                (v.kind == "float" and v.size == 8 or d.kind == "float" and d.size == 8):
            return "double-int-arg", "I686"
        return "float-int-arg", "REAL"              # Win64: XMMn vs the GPR of the position
    if v.kind == d.kind == "ref":
        return ("ref-arg", "BENIGN") if v.name == d.name else ("ref-arg", "INSPECT")
    if v.kind == d.kind == "unk" and v.name == d.name:
        return None
    if "unk" in (v.kind, d.kind) or (v.kind == "struct" or d.kind == "struct"):
        return "named-arg", "INSPECT"
    return "other-arg", "INSPECT"


def cmp_ret(v0: Ty, d0: Ty):
    if v0 == d0 or (v0.kind == d0.kind == "ptr"):
        return None
    v, d = abi(v0), abi(d0)
    if v.kind == "void":
        return "void-view-ret", "BENIGN"
    if d.kind == "void":
        return "void-def-ret", "I686"                 # garbage EAX / RAX on both
    if v.kind in ("int", "bool") and d.kind in ("int", "bool"):
        vs, ds = v.size, d.size
        if vs == ds:
            if (v.lp == "long") != (d.lp == "long"):
                return "lp64-long-ret", "LINUX"
            if v.lp == "size" and d.lp != "size":
                return "size-view-ret", "REAL"
            if "flt" in (v0.lp, d0.lp):
                return "rec-float-int-ret", "LINUX"      # SysV: XMM0 vs RAX
            return ("bool-ret" if "bool" in (v.kind, d.kind) else "sign-ret"), "BENIGN"
        if ds < 4 and vs > ds:
            if "rec" in (v.lp, d.lp):
                return "rec-narrow-ret", "INSPECT"
            return "narrow-ret", "FIX"
        if vs < ds:
            return "narrow-view-ret", "BENIGN"     # the caller keeps its low bits
        if vs == 8 and ds == 4:
            return "s64-view-ret", "I686"             # EDX / upper RAX garbage on both
        return "int-ret", "INSPECT"
    if v.kind == "ptr" and d.kind in ("int", "bool"):
        if d.size == 8:
            return None
        if d.size == 4 and d.lp != "rec":
            return "ptr-view-int-ret", "FIX"
        return "ptr-view-narrow-ret", "REAL"
    if v.kind in ("int", "bool") and d.kind == "ptr":
        return "int-view-ptr-ret", "BENIGN"
    if v.kind == "float" and d.kind == "float":
        return "float-width-ret", "I686"
    if v.kind == "float" or d.kind == "float":
        return "float-ret", "I686"                    # x87 ST0 vs EAX on i686
    if v.kind == d.kind == "unk" and v.name == d.name:
        return None
    if v.kind == d.kind == "ref":
        return ("ref-ret", "BENIGN") if v.name == d.name else ("ref-ret", "INSPECT")
    return "named-ret", "INSPECT"


Row = namedtuple("Row", "file line func pos view defn cat verdict note")


def deftype(defs: dict, name: str):
    lst = defs.get(name)
    if not lst:
        return None
    first = lst[0][1]
    for _f, s in lst[1:]:
        if (s.ret, s.params, s.variadic) != (first.ret, first.params, first.variadic):
            return "ambiguous"
    return first


def compare(defs: dict, cxxdefs: dict, f, s: Sig, own: set):
    """census rows for one declaration"""
    rows = []
    if s.kind != "decl" or s.name in own or s.static:
        return rows
    d = deftype(defs if s.clink else cxxdefs, s.name)
    if d is None or d == "ambiguous":
        return rows
    if not s.clink:
        r = cmp_ret(s.ret, d.ret)
        if r and len(s.params) == len(d.params):
            rows.append(Row(f, s.line, s.name, "ret", s.ret, d.ret, r[0], r[1], "C++ linkage"))
        return rows
    if s.proto and not s.params and not s.variadic:
        # `f(void)`: no call through it can pass arguments (an address-only declaration)
        if d.params:
            rows.append(Row(f, s.line, s.name, "args", VOID, d.params[0], "address-only", "BENIGN",
                            f"0 of {len(d.params)}"))
    elif s.proto:
        for k, v in enumerate(s.params):
            if k >= len(d.params):
                if not d.variadic:
                    rows.append(Row(f, s.line, s.name, f"arg{k}", v, VA, "extra-arg", "BENIGN", ""))
                elif v.kind == "float" and v.size == 4:
                    rows.append(Row(f, s.line, s.name, f"arg{k}", v, VA, "float-to-varargs", "I686", ""))
                continue
            c = cmp_arg(v, d.params[k])
            if c:
                rows.append(Row(f, s.line, s.name, f"arg{k}", v, d.params[k], c[0], c[1], ""))
        if len(s.params) < len(d.params) and not s.variadic:
            rows.append(Row(f, s.line, s.name, f"arg{len(s.params)}", VA, d.params[len(s.params)],
                            "missing-arg", "I686", f"{len(s.params)} of {len(d.params)}"))
        if s.variadic and not d.variadic and len(s.params) < len(d.params):
            fl = [t for t in d.params[len(s.params):] if t.kind == "float"]
            rows.append(Row(f, s.line, s.name, f"arg{len(s.params)}", VA, d.params[len(s.params)],
                            "varargs-view", "REAL" if fl else "BENIGN",
                            "float in the variadic part" if fl else ""))
        if d.variadic and not s.variadic:
            rows.append(Row(f, s.line, s.name, "va", s.ret, d.ret, "fixed-view-of-varargs", "INSPECT", ""))
    else:
        fl = [t for t in d.params if t.kind == "float" and t.size == 4]
        if fl:
            rows.append(Row(f, s.line, s.name, "()", VA, fl[0], "unprototyped-float", "I686",
                            "default promotion: double"))
        elif d.params:
            rows.append(Row(f, s.line, s.name, "()", VA, d.params[0], "unprototyped", "BENIGN",
                            "default promotions"))
    r = cmp_ret(s.ret, d.ret)
    if r:
        rows.append(Row(f, s.line, s.name, "ret", s.ret, d.ret, r[0], r[1], ""))
    return rows


# ---------------------------------------------------------------- rewrite

def _intname(t: Ty) -> str:
    if t.kind == "bool":
        return "u8"
    return {(1, True): "s8", (1, False): "u8", (2, True): "s16", (2, False): "u16",
            (4, True): "s32", (4, False): "u32", (8, True): "long long",
            (8, False): "unsigned long long"}[(t.size, t.signed)]


def fix_edits(s: Sig, rows: list):
    """(start, end, new) edits for the FIX rows of one declaration, and the names whose
    DEFINITION return type is widened ((name, new type))"""
    edits, dedits = [], []
    for r in rows:
        if r.verdict != "FIX":
            continue
        if r.pos == "ret":
            if r.cat == "ptr-view-int-ret":
                dedits.append((s.name, "long long" if r.defn.signed else "unsigned long long"))
                continue
            if s.rspan is None:
                continue
            edits.append((s.rspan[0], s.rspan[1], _intname(r.defn)))
            continue
        k = int(r.pos[3:])
        sp = s.pspans[k] if k < len(s.pspans) else None
        if sp is None:
            continue
        v = r.view
        sig = v.kind == "int" and v.signed
        if r.cat == "narrow-arg":
            new = "s32" if sig else "u32"
        elif r.cat in ("int-for-ptr-arg", "narrow-for-ptr-arg"):
            new = "long long" if sig else "unsigned long long"
        elif r.cat == "int-for-size-arg":
            new = "__SIZE_TYPE__"
        else:
            continue
        edits.append((sp[0], sp[1], new))
    return edits, dedits


def apply(text: str, edits) -> str:
    for a, b, new in sorted(set(edits), reverse=True):
        text = text[:a] + new + text[b:]
    return text


def includes_of(idx):
    """header path -> set of TU files that include it (transitively), resolved against
    the including file's directory and the include dirs"""
    known = {Path(f).resolve(): f for f in idx.text}
    direct = {}
    for f in idx.files:
        incs = []
        for m in INCLUDE.finditer(idx.text.get(f, "")):
            nm = m.group(1)
            for base in [f.parent] + idx.inc_dirs:
                try:
                    p = (base / nm).resolve()
                except OSError:
                    continue
                if p in known:
                    incs.append(known[p])
                    break
        direct[f] = incs
    users = {}
    for f in idx.files:
        if f.suffix not in (".c", ".cpp"):
            continue
        seen, todo = set(), list(direct.get(f, []))
        while todo:
            h = todo.pop()
            if h in seen:
                continue
            seen.add(h)
            todo += direct.get(h, [])
        for h in seen:
            users.setdefault(h, set()).add(f)
    return users


def plan(idx):
    """(rows, decl edits by file, definition return widenings {name: type},
    header declarations a rewrite must not touch {(file, name)})"""
    if not idx._defs_done:
        idx.build_defs()
    users = None
    rows_all = []
    edits = {}
    dret = {}
    blocked = set()
    defined_in = {}
    for nm, lst in idx.defs.items():
        for f, _s in lst:
            defined_in.setdefault(nm, set()).add(f)
    for f in idx.files:
        ss = idx.sigs(f)
        own = {s.name for s in ss if s.kind == "def"}
        hdr = f.suffix in (".h", ".hpp")
        for s in ss:
            rows = compare(idx.defs, idx.cxxdefs, f, s, own)
            if not rows:
                continue
            if hdr and any(r.verdict == "FIX" and r.pos != "ret" or r.cat == "narrow-ret" for r in rows):
                if users is None:
                    users = includes_of(idx)
                if defined_in.get(s.name, set()) & users.get(f, set()):
                    # the header is seen by the defining TU: a rewrite would conflict
                    blocked.add((f, s.name))
                    rows = [r._replace(verdict="REAL", note="header seen by the defining TU")
                            if r.verdict == "FIX" and r.cat != "ptr-view-int-ret" else r for r in rows]
            rows_all += rows
            e, de = fix_edits(s, rows)
            if e:
                edits.setdefault(f, []).extend(e)
            for nm, new in de:
                dret[nm] = new
    return rows_all, edits, dret, blocked


def def_ret_edits(sigs_of_file, dret: dict):
    """the definition-side return widening (ptr-view-int-ret) inside one file that
    defines a name of `dret`: the definition and every declaration of it in the file"""
    out = []
    ss = sigs_of_file
    own = {s.name for s in ss if s.kind == "def" and not s.static}
    for s in ss:
        if s.name in dret and s.name in own and s.rspan and s.clink and \
                s.ret.kind == "int" and s.ret.size == 4:
            out.append((s.rspan[0], s.rspan[1], dret[s.name]))
    return out


# ---------------------------------------------------------------- derive entry point

def derive_apply(texts: dict, inc_dirs=(), root=None):
    """the derive pass over a whole tree: texts {path: text} (the tree as the other x64
    stages left it) -> ({path: new text} for the files it changes, edit count, census
    rows).  Definitions, typedefs and record sizes come from the same texts, so a census
    of the derived tree (`narrowabi.py --root <out> --check`) sees what the pass saw."""
    files = list(texts)
    if root is not None:
        # only the TUs the build compiles (the derived tree mirrors the source tree)
        files = keep_compiled(files, root, compiled_rels(PORT))
    idx = Index(files, inc_dirs, texts=texts)
    idx.build_defs()
    rows, edits, dret, _blocked = plan(idx)
    if dret:
        for nm in dret:
            for f, _s in idx.defs.get(nm, []):
                e = def_ret_edits(idx.sigs(f), {nm: dret[nm]})
                if e:
                    edits.setdefault(f, []).extend(e)
    out = {}
    n = 0
    for f, e in edits.items():
        e = sorted(set(e))
        out[f] = apply(idx.text[f], e)
        n += len(e)
    return out, n, rows


# ---------------------------------------------------------------- CLI

def tree_files(trees, root=PORT):
    for t in trees:
        base = Path(root) / t
        if not base.is_dir():
            continue
        for ext in ("*.c", "*.cpp", "*.h", "*.hpp"):
            yield from base.rglob(ext)


def inc_dirs_of(root: Path):
    root = Path(root)
    out = [root / "game" / "include"]
    for t in ("overrides", "missing"):
        out += [p for p in (root / t).rglob("include") if p.is_dir()] if (root / t).is_dir() else []
    out.append(PORT / "include")
    return out


def load_accept() -> dict:
    """(func, pos, view, definition) -> reason, from narrowabi_accept.tsv"""
    acc = {}
    if ACCEPT.exists():
        for ln in ACCEPT.read_text(encoding="utf-8").splitlines():
            if not ln.strip() or ln.startswith("#"):
                continue
            p = ln.split("\t")
            if len(p) >= 6:
                acc[(p[0], p[1], p[2], p[3])] = p[5]
    return acc


def run(root: Path, trees, check: bool, tsv: str | None, show_all: bool, extra=(),
        every_file: bool = False) -> int:
    files = list(tree_files(trees, root))
    if not every_file and (Path(root) / "game" / "MANIFEST.tsv").is_file():
        n0 = len(files)
        files = keep_compiled(files, root, compiled_rels(root))
        print(f"# {n0 - len(files)} superseded / uncompiled game, override or missing TUs skipped "
              f"(--every-file keeps them)")
    files += [Path(x) for x in extra]
    idx = Index(files, inc_dirs_of(root))
    idx.build_defs()
    rows, edits, dret, blocked = plan(idx)
    acc = load_accept()
    print(f"# {len(idx.files)} files, {sum(len(v) for v in idx.defs.values())} C-linkage definitions "
          f"({len(idx.defs)} names), {len(idx.tds)} header typedefs")
    cnt = Counter()
    bad = []
    lines = []
    used = set()
    for r in sorted(rows, key=lambda r: (str(r.file), r.line, r.pos)):
        rel = r.file.relative_to(root).as_posix() if r.file.is_relative_to(root) else str(r.file)
        verdict = r.verdict
        key = (r.func, r.pos, tyname(r.view), tyname(r.defn))
        note = r.note
        if verdict in ("REAL", "INSPECT") and key in acc:
            verdict, note = "ACCEPTED", acc[key]
            used.add(key)
        cnt[(verdict, r.cat)] += 1
        if verdict in ("FIX", "REAL", "INSPECT"):
            bad.append(r)
        lines.append(f"{rel}\t{r.line}\t{r.func}\t{r.pos}\t{tyname(r.view)}\t{tyname(r.defn)}\t"
                     f"{r.cat}\t{verdict}\t{note}")
    # in a derived tree the ptr-view-int-ret rows are cleared at the definition: count
    # what is left of them by the definition's form
    if tsv:
        Path(tsv).write_text("file\tline\tfunc\tpos\tview\tdefinition\tcategory\tverdict\tnote\n"
                             + "\n".join(lines) + "\n", encoding="utf-8")
    for ln in lines:
        if show_all or ln.split("\t")[7] in ("FIX", "REAL", "INSPECT"):
            print(ln)
    print("# by verdict / category:")
    for (v, c), n in sorted(cnt.items()):
        print(f"#   {v:8} {c:24} {n}")
    stale = sorted(set(acc) - used)
    for k in stale:
        print(f"# accept entry matches no row (stale): {' '.join(k)}")
    nfix = sum(1 for r in bad if r.verdict == "FIX")
    print(f"# {len(rows)} rows; {nfix} FIX (the derive pass rewrites them), "
          f"{len(bad) - nfix} REAL/INSPECT not accepted, {len(dret)} definition returns to widen, "
          f"{len(blocked)} header declarations blocked")
    if check and bad:
        print(f"# CHECK FAILED: {len(bad)} call-ABI mismatches left", file=sys.stderr)
        return 1
    return 0


CONTROL_DEF = ("s32 NarrowAbiControlCallee_ffff00(s32 id, void *p) { return id + (p != 0); }\n"
               "s32 NarrowAbiControlGet_ffff20(void *p) { return (s32)(long long)p; }\n")
CONTROL_DECL = ("extern s32 NarrowAbiControlCallee_ffff00(s16 id, u32 p);\n"
                "extern void *NarrowAbiControlGet_ffff20(void *p);\n"
                "s32 NarrowAbiControlCaller_ffff10(void) { return NarrowAbiControlCallee_ffff00(1, 0); }\n")


def control(root: Path, trees) -> int:
    """--check must FAIL with one injected mismatching declaration pair; the derive
    rewrite (the same code derive.py runs) must clear it"""
    inc = root / "game" / "include"
    with tempfile.TemporaryDirectory() as td:
        a = Path(td) / "ctl_def.c"
        b = Path(td) / "ctl_decl.c"
        a.write_text('#include "types.h"\n' + CONTROL_DEF, encoding="utf-8")
        b.write_text('#include "types.h"\n' + CONTROL_DECL, encoding="utf-8")
        files = [a, b, inc / "types.h"]
        idx = Index(files, [inc])
        idx.build_defs()
        rows, _, dret, _ = plan(idx)
        cats = sorted((r.func[-6:], r.pos, r.cat, r.verdict) for r in rows)
        want = [("ffff00", "arg0", "narrow-arg", "FIX"), ("ffff00", "arg1", "int-for-ptr-arg", "FIX"),
                ("ffff20", "ret", "ptr-view-int-ret", "FIX")]
        if cats != want:
            print(f"control: FAIL, rows {cats} != {want}")
            return 1
        new, n, _ = derive_apply({f: f.read_text(encoding="utf-8") for f in files}, [inc])
        for f, t in new.items():
            f.write_text(t, encoding="utf-8")
        fixed = b.read_text(encoding="utf-8") + a.read_text(encoding="utf-8")
        for want_txt in ("NarrowAbiControlCallee_ffff00(s32 id, unsigned long long p)",
                         "long long NarrowAbiControlGet_ffff20(void *p)"):
            if want_txt not in fixed:
                print("control: FAIL, the rewrite produced:\n" + fixed)
                return 1
        idx2 = Index(files, [inc])
        idx2.build_defs()
        rows2 = [r for r in plan(idx2)[0] if r.verdict not in ("BENIGN",)]
        if rows2:
            print(f"control: FAIL, rows left after the rewrite: {rows2}")
            return 1
        # the full check on the real tree plus the injected pair must fail
        a.write_text('#include "types.h"\n' + CONTROL_DEF, encoding="utf-8")
        b.write_text('#include "types.h"\n' + CONTROL_DECL, encoding="utf-8")
        rc = run(root, trees, True, None, False, extra=[a, b])
        if rc == 0:
            print("control: FAIL, --check passed with an injected mismatch")
            return 1
    print("control: PASS (--check fails on the injected mismatch; the derive rewrite clears it)")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", action="append")
    ap.add_argument("--root", default=str(PORT), help="tree root (an x64 derived tree: build/x64-src)")
    ap.add_argument("--check", action="store_true",
                    help="exit 1 when a FIX / REAL / INSPECT row is left (rows listed in "
                         "narrowabi_accept.tsv excepted)")
    ap.add_argument("--control", action="store_true",
                    help="inject a mismatching pair: --check must fail, the rewrite must clear it")
    ap.add_argument("--tsv", help="write every row (all verdicts) here")
    ap.add_argument("--all", action="store_true", help="print BENIGN / LINUX / I686 rows too")
    ap.add_argument("--every-file", action="store_true",
                    help="index every .c/.cpp of the trees, also the ones the build does not "
                         "compile (overridden, PORT_PROVIDED, `excluded` game files)")
    a = ap.parse_args()
    trees = a.tree or ["game", "overrides", "missing"]
    root = Path(a.root).resolve()
    if a.control:
        return control(root, trees)
    return run(root, trees, a.check, a.tsv, a.all, every_file=a.every_file)


if __name__ == "__main__":
    sys.exit(main())
