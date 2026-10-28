#!/usr/bin/env python3
"""Transform 2 (PLAN.md): prototype unification.

The decomp declares every callee locally, per file, and nothing ties those
declarations to the definition: mwcc's MIPS EABI tolerated a wrong argument
count, a void-vs-value return or a pointer/int swap.  Under i686 cdecl a
wrong count, a float/int swap or a void-vs-value return is an ABI break.

Truth = the DEFINITION (the registered unit that defines the symbol).  This
stage:

  * builds an index of every definition, declaration and direct call in the
    ingested sources (regex/brace parser, comments and strings blanked;
    `snapshot.find_funcs` from tools/census does the top-level walk);
  * generates include/port/game_protos.h: one C prototype per externally
    linked C-linkage definition, types normalised to builtin C types
    (every pointer -> `void *`, s32 -> int, f32 -> float, ...), each guarded
    by `#ifndef RGP_SELF_<name>` so a file never redeclares what it defines;
  * C files (strict policy): a preamble defines RGP_SELF_<f> for every
    function the file defines and includes the header; every local
    declaration of a header symbol is removed (blanked, newlines kept), so
    every call is compiled against the definition's shape.  Pointer<->int
    differences are left to `-Wno-int-conversion` (clang C downgrades them);
    where a call's value is used and the local view's return type involves a
    pointer, the call is cast back to the local type so expressions such as
    `F()->x` or `F() + 1` keep their meaning;
  * C++ files (local policy -- C++ has no int<->pointer conversion, so the
    void*-typed header cannot be used): the header is not included; each
    ABI-wrong local declaration is patched in place to the definition's
    shape, reusing the local parameter spellings where the class agrees;
  * call sites are remapped the way MIPS EABI assigned registers: integer/
    pointer/64-bit arguments fill $a0.. in order, f32 arguments fill
    $f12.. in order, independently.  The k-th GPR parameter of the
    definition receives the k-th GPR argument of the caller's view; same for
    FPR.  Leftover arguments are dropped (kept as `(void)` comma operands if
    they have side effects); missing ones get 0 (what the callee read was an
    unset register in retail; 0 is the stand-in) and are logged;
  * void-defined callees whose value a caller uses: if the definition ends in
    a tail call to a value-returning function on its only exit path, retail
    returns that value ($v0/$f0 untouched by the epilogue) and the definition
    is rewritten `return G(..);` (rule def-tail-return); otherwise the use
    becomes `(F(..), (T)0)` (void-value-zero) and is listed for review.

Every rewrite and every flag goes to PROTOS.tsv.

Usage from ingest.py (see docs/PROTOS.md):

    stage = protos.ProtoStage()
    stage.prepare({relpath: bytes, ...})       # ALL ingested files, raw
    ... stage.apply(relpath, data) per file ...
    outputs.update(stage.extra_outputs())     # header + PROTOS.tsv
"""
from __future__ import annotations

import hashlib
import os
import re
import sys
from bisect import bisect_right
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "census"))
import snapshot as S  # noqa: E402  (read-only reuse: strip_comments, find_funcs)
sys.path.insert(0, str(Path(__file__).resolve().parent))
import asmflow
import clayout  # noqa: E402  (retail-listing dataflow: missing-argument rules)

HEADER_REL = "include/port/game_protos.h"
LOG_REL = "PROTOS.tsv"

# Port providers of symbols whose game body is asm (asmexclude, game/EXCLUDED.tsv;
# docs/BINDINGS.md).  For a callee with NO C truth in the corpus, the provider's
# declared prototype is the truth: overrides/ and missing/ C definitions, then the
# prototypes of these headers.  Paths relative to the port root.
PROVIDER_DIRS = ("overrides", "missing")
PROVIDER_HEADERS = ("src/crt/crt.h", "src/sce/vu0/sce_vu0.h")
# Unsuffixed libc names bound to the host CRT as is (BINDINGS.md `host-crt`).
# They never go into game_protos.h (clang knows them as builtins); a file whose
# local view is ABI-wrong gets that declaration patched in place.
HOST_CRT = """
void *memcpy(void *d, const void *s, unsigned int n);
void *memset(void *d, int c, unsigned int n);
void *memmove(void *d, const void *s, unsigned int n);
char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, unsigned int n);
char *strcat(char *d, const char *s);
unsigned int strlen(const char *s);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, unsigned int n);
"""
# 8-byte GPR transport: the EE passes double, s64 and u64 in one 64-bit GPR, so
# a value crosses a call as BITS whatever the two sides call it.  On i686 the
# C conversion between double and an integer type changes the bits, so the
# stage spells those crossings with __builtin_bit_cast (C and C++, clang).
BITS_Q = "long long"
MARK = "/* rgp:protos */"
SRC_EXT = (".c", ".cpp")

# ------------------------------------------------------------------ types
BUILTIN = {
    "s8": "signed char", "u8": "unsigned char", "s16": "short", "u16": "unsigned short",
    "s32": "int", "u32": "unsigned int", "s64": "long long", "u64": "unsigned long long",
    "f32": "float", "f64": "double", "BOOL": "int", "bool": "unsigned char",
    "size_t": "unsigned int", "uint": "unsigned int", "ushort": "unsigned short",
    "uchar": "unsigned char", "wchar_t": "unsigned short",
    # stdint spellings (port provider headers, src/crt/crt.h)
    "int8_t": "signed char", "uint8_t": "unsigned char", "int16_t": "short",
    "uint16_t": "unsigned short", "int32_t": "int", "uint32_t": "unsigned int",
    "int64_t": "long long", "uint64_t": "unsigned long long", "intptr_t": "int",
    "uintptr_t": "unsigned int", "ptrdiff_t": "int",
}
WIDE = ("long long", "unsigned long long", "double")   # 8 bytes on i686
NARROW_INT = ("char", "signed char", "unsigned char", "short", "unsigned short")
NARROW_SIZE = {"char": 1, "signed char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2}
INT_WORDS = {"char", "short", "int", "long", "unsigned", "signed"}
QUALS = re.compile(r"\b(const|volatile|register|static|extern|inline|__inline|restrict|"
                   r"__restrict|auto|virtual|asm|mutable)\b")
ATTR = re.compile(r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)")
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "goto",
            "defined", "asm", "__attribute__", "typedef", "operator", "new", "delete",
            "throw", "default", "break", "continue", "using", "template", "typename",
            "struct", "union", "class", "enum", "namespace", "public", "private",
            "protected", "static_cast", "reinterpret_cast", "const_cast", "__asm__"}
RET_BAD = KEYWORDS - {"struct", "union", "class", "enum", "typename"}


@dataclass
class T:
    """A reduced type.  cls: g (GPR: int/ptr/64-bit), f (f32), v (void),
    x (struct by value, 128-bit, unknown: not handled mechanically)."""
    cls: str
    c: str          # builtin C spelling for the header ('void *', 'int', ...)
    raw: str        # original spelling (type only, no name)
    ptr: bool = False
    name: str = ""  # parameter name, if any

    def key(self):
        return (self.cls, self.c)

    @property
    def kind(self) -> str:
        """i686 transport kind: v void, f float (x87 ST0 return / 4 stack
        bytes), d double (ST0 / 8 bytes), q 8-byte integer (EDX:EAX / 8
        bytes), i 4-byte-or-less integer/pointer (EAX / 4 bytes), x other."""
        if self.cls in ("v", "f", "x"):
            return self.cls
        if self.c == "rg_u128":         # a u128-view slot (rule u128-view)
            return "o"
        if self.c == "rg_aggbits":      # an agg-view slot (rule agg-view)
            return "a"
        if self.c == "double":
            return "d"
        if self.c in ("long long", "unsigned long long"):
            return "q"
        return "i"


def resolve_type(raw: str, tdefs: dict, depth: int = 0) -> T:
    t = ATTR.sub("", raw)
    t = re.sub(r'"[^"]*"', "", t)
    t = QUALS.sub(" ", t)
    t = " ".join(t.split())
    rawc = " ".join(raw.split())
    if not t or t == "void":
        return T("v", "void", rawc)
    if "*" in t or "&" in t or "[" in t or "(" in t:
        return T("g", "void *", rawc, True)
    words = t.split()
    if words[0] in ("struct", "union", "class"):
        nm = words[1] if len(words) > 1 else ""
        r = tdefs.get(nm)
        if isinstance(r, T):
            return T(r.cls, r.c, rawc, r.ptr)
        return T("x", rawc, rawc)
    if words[0] == "enum":
        return T("g", "int", rawc)
    if all(w in INT_WORDS for w in words):
        if "long" in words and words.count("long") >= 2:
            c = "unsigned long long" if "unsigned" in words else "long long"
        elif "char" in words:
            c = ("unsigned char" if "unsigned" in words else
                 "signed char" if "signed" in words else "char")
        elif "short" in words:
            c = "unsigned short" if "unsigned" in words else "short"
        elif "long" in words:
            c = "unsigned long" if "unsigned" in words else "long"
        else:
            c = "unsigned int" if "unsigned" in words else "int"
        return T("g", c, rawc)
    if len(words) == 1:
        w = words[0]
        if w in ("float", "f32"):
            return T("f", "float", rawc)
        if w in ("double", "f64"):
            return T("g", "double", rawc)     # EE: soft double, passed in a GPR
        if w in ("u128", "s128", "__int128"):
            return T("x", rawc, rawc)
        r = tdefs.get(w)
        if isinstance(r, T):
            return T(r.cls, r.c, rawc, r.ptr)
        if w in BUILTIN:
            b = BUILTIN[w]
            return T("f" if b == "float" else "g", b, rawc)
        return T("x", rawc, rawc)       # unknown name: struct? leave to a human
    if words[-1] in ("int", "__int128") and words[0] == "unsigned" and "__int128" in words:
        return T("x", rawc, rawc)
    return T("x", rawc, rawc)


def split_top(s: str, sep: str = ",") -> list[tuple[int, int]]:
    """Spans of top-level comma-separated pieces of s."""
    out, d, a = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        elif ch == sep and d == 0:
            out.append((a, i))
            a = i + 1
    out.append((a, len(s)))
    return out


def split_param(p: str) -> tuple[str, str]:
    """`s32 *name` -> ('s32 *', 'name');  `Foo` -> ('Foo', '')."""
    p = " ".join(ATTR.sub("", p).split())
    if "(" in p:  # function pointer: T (*name)(...)
        m = re.search(r"\(\s*[*&]\s*(\w*)\s*\)", p)
        nm = m.group(1) if m else ""
        return (p.replace(nm, "", 1) if nm else p), nm
    arr = ""
    m = re.search(r"((?:\[[^\]]*\]\s*)+)$", p)
    if m:
        arr = m.group(1)
        p = p[:m.start()].rstrip()
    m = re.match(r"^(.*?[\w*&\s])\s*\b([A-Za-z_]\w*)$", p)
    if m:
        typ, nm = m.group(1).strip(), m.group(2)
        tw = typ.split()
        if typ in ("unsigned", "signed") and nm not in INT_WORDS:
            return typ, nm
        if (typ and typ not in ("struct", "union", "enum", "class", "unsigned", "signed",
                                "const", "volatile")
                and nm not in INT_WORDS and nm not in ("float", "double", "void")
                and not (tw and tw[-1] in ("struct", "union", "enum", "class"))):
            return typ + (" *" if arr else ""), nm
    return p + (" *" if arr else ""), ""


@dataclass
class Sig:
    ret: T
    params: list            # list[T]
    va: bool = False
    unproto: bool = False   # C `f()`: no prototype

    def classes(self):
        return [p.cls for p in self.params]

    def shape(self):
        return (self.ret.cls, tuple(self.classes()), self.va)


def parse_params(ptext: str, tdefs: dict, cpp: bool) -> tuple[list, bool, bool] | None:
    p = ptext.strip()
    if p == "":
        return [], False, not cpp
    if p == "void":
        return [], False, False
    out, va = [], False
    for a, b in split_top(p):
        x = p[a:b].strip()
        if x == "...":
            va = True
            continue
        if not x:
            return None
        # a parameter must look like a type: words, *, &, [..], (*name)(..), =default
        x = re.sub(r"\s*=\s*[^,]*$", "", x) if cpp else x
        if re.search(r"[+\-/%!<>?|^~.'\"]|(?<![\w\s*&(\[])\d", x):
            return None
        if not re.match(r"\s*[A-Za-z_]", x):
            return None
        typ, nm = split_param(x)
        tt = resolve_type(typ, tdefs)
        tt.name = nm
        if tt.cls == "v":
            return None
        out.append(tt)
    return out, va, False


# ------------------------------------------------------------------ address table
OVL_BASE = 0x4E9E80
MAIN_LO = 0x100000


def snapshot_addr_table(repo, rev: str) -> dict:
    """MAIN's address table from the pinned snapshot (git objects only):
    {'main': {addr: name}} from config/main.symbols.txt, and
    {'entries': {addr: (container_name, k)}} from the `alabel func_XXXXXXXX`
    lines of MAIN's retail listing (the k-th interior entry of a multi-entry
    function, which the C side defines as `func_<start>_e<k>`).

    The listing is read from whichever form the snapshot carries:
      * per-function files asm/matchings/main/<fn>.s (decomp working trees,
        e.g. the interim snapshot), or
      * the combined image listing asm/main.s (the published decomp), split
        at each `glabel <fn>` line into the same per-function text.
    Both are spimdisasm output of the same image (identical lines), so the
    rules that read them (addr-alias, missing-entry) see the same input."""
    import subprocess

    def git(*a):
        r = subprocess.run(["git", "-C", str(repo), *a], capture_output=True, text=True,
                           encoding="utf-8", errors="replace")
        return r.stdout
    main: dict[int, str] = {}
    by_name: dict[str, int] = {}
    for ln in git("show", f"{rev}:config/main.symbols.txt").splitlines():
        f = ln.split("//")[0].split("=")
        if len(f) == 2 and f[1].strip().rstrip(";").startswith("0x"):
            a = int(f[1].strip().rstrip(";"), 16)
            main.setdefault(a, f[0].strip())
            by_name[f[0].strip()] = a
    entries: dict[int, tuple] = {}
    seen: dict[str, int] = defaultdict(int)
    # retail listings: the protos stage reads one on demand (missing-entry
    # rule); per-function files by path, or text split from asm/main.s
    asm_paths: dict[str, str] = {}
    asm_text: dict[str, str] = {}
    for ln in git("ls-tree", "-r", "--name-only", rev, "asm/matchings").splitlines():
        if ln.endswith(".s"):
            asm_paths.setdefault(ln.rsplit("/", 1)[1][:-2], ln)
    if any(p.startswith("asm/matchings/main/") for p in asm_paths.values()):
        for ln in git("grep", "-n", "alabel", rev, "--", "asm/matchings/main/").splitlines():
            m = re.match(r"[^:]*:asm/matchings/main/(\w+)\.s:\d+:\s*alabel\s+func_([0-9A-Fa-f]{8})\s*$", ln)
            if not m:
                continue
            seen[m.group(1)] += 1
            entries[int(m.group(2), 16)] = (m.group(1), seen[m.group(1)], by_name.get(m.group(1)))
    else:
        asm_text = split_listing(git("show", f"{rev}:asm/main.s"))
        for fn, text in asm_text.items():
            for m in re.finditer(r"^\s*alabel\s+func_([0-9A-Fa-f]{8})\s*$", text, re.M):
                seen[fn] += 1
                entries[int(m.group(1), 16)] = (fn, seen[fn], by_name.get(fn))
    # overlay listings (docs/PROTOS-MISSING-ARGS.md rule D): the combined
    # asm/overlays/<ov>/<ov>.s, split at each glabel like asm/main.s
    ovl_text: dict[str, dict] = {}
    for ln in git("ls-tree", "--name-only", rev, "asm/overlays/").splitlines():
        ov = ln.rstrip("/").rsplit("/", 1)[-1]
        txt = git("show", f"{rev}:asm/overlays/{ov}/{ov}.s")
        if txt:
            ovl_text[ov] = split_listing(txt)
    # _gp (gp-relative loads in the overlay listings carry no relocation)
    gp = None
    for ln in git("grep", "-h", "_gp\\s*=", rev, "--", "*.lcf").splitlines():
        m = re.search(r"\b_gp\s*=\s*(0x[0-9A-Fa-f]+)", ln)
        if m:
            gp = int(m.group(1), 16)
            break
    # data2c's interior-entry table (config/data2c.json "function_entries":
    # address -> {owner_address, symbol}): the address each C `func_<start>_e<k>`
    # really has.  The C's k is not always the alabel ordinal: a container of
    # 16-byte jr stubs (ContainerViewGetAtFwd_418ab0) defines e1..e15 for the
    # unlabelled stubs and e16 for its one alabel (0x418BB0).
    fentries: dict[int, str] = {}
    try:
        import json as _json
        fe = _json.loads(git("show", f"{rev}:config/data2c.json") or "{}").get("function_entries", {})
        for k, v in fe.items():
            fentries[int(k, 16)] = v.get("symbol", "")
    except ValueError:
        pass
    return {"main": main, "entries": entries, "asm_paths": asm_paths, "asm_text": asm_text,
            "ovl_text": ovl_text, "gp": gp, "by_name": by_name, "fentries": fentries,
            "repo": str(repo), "rev": rev}


def split_listing(text: str) -> dict[str, str]:
    """A combined spimdisasm listing (asm/main.s) -> {glabel name: its lines up
    to the next glabel or section directive} -- the body a per-function
    asm/matchings/<image>/<fn>.s holds (its preamble aside)."""
    out: dict[str, str] = {}
    cur, buf = None, []
    for ln in text.splitlines(keepends=True):
        m = re.match(r"\s*glabel\s+(\w+)\s*$", ln)
        if m or ln.lstrip().startswith(".section"):
            if cur is not None:
                out.setdefault(cur, "".join(buf))
            cur, buf = (m.group(1) if m else None), []
        if cur is not None:
            buf.append(ln)
    if cur is not None:
        out.setdefault(cur, "".join(buf))
    return out


# Hand overrides for missing arguments whose value retail's listing cannot
# decide (rule `missing-asm`): (file, callee, n-th call of callee in the
# enclosing function) -> {class index k: C expression}.  Empty: the former two
# rows (Fill3U64Default_3b0990(arg0 + 0x2F0) in the chara ctors) are now
# spelled by rule E from the listing (`addiu $4,$17,0x2F0`, $17 = entry $4).
MISSING_ARG_ASM: dict = {}

# ------------------------------------------------------------------ parsing
@dataclass
class Def:
    name: str
    rel: str
    sig: Sig
    static: bool
    clink: bool             # C linkage (all .c; extern "C" in .cpp)
    is_asm: bool
    start: int              # header start
    name_off: int
    lparen: int
    rparen: int
    body_open: int
    body_close: int
    proto_text: str         # `ret name(params)` as written


@dataclass
class Decl:
    name: str
    start: int
    end: int                # offset after ';'
    func: object            # enclosing S.Func or None
    sig: Sig
    text: str
    static: bool
    clink: bool
    lparen: int = 0
    rparen: int = 0
    ret_span: tuple = (0, 0)


@dataclass
class Call:
    name: str
    start: int              # name offset
    lparen: int
    rparen: int
    args: list              # [(a, b)] absolute spans (stripped)
    func: object            # enclosing S.Func


@dataclass
class FileInfo:
    rel: str
    text: str
    code: str               # comments + strings + preprocessor blanked
    cpp: bool
    funcs: list
    fstarts: list
    tdefs: dict
    defs: list = field(default_factory=list)
    decls: list = field(default_factory=list)
    calls: list = field(default_factory=list)
    ls: list = field(default_factory=list)
    externc: list = field(default_factory=list)
    objdecls: set = field(default_factory=set)   # names declared as OBJECTS

    def line(self, off: int) -> int:
        return bisect_right(self.ls, off)

    def enclosing(self, off: int):
        k = bisect_right(self.fstarts, off) - 1
        while k >= 0:
            f = self.funcs[k]
            if f.kind == "func" and f.body_open < off < f.body_close:
                return f
            k -= 1
        return None

    def in_class(self, off: int) -> bool:
        for f in self.funcs:
            if f.kind == "class" and f.body_open < off < f.body_close:
                return True
        return False

    def in_externc(self, off: int) -> bool:
        return any(a < off < b for a, b in self.externc)


_PP = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)


def blank(s: str) -> str:
    return re.sub(r"[^\n]", " ", s)


def blank_if0(code: str) -> str:
    """Blank `#if 0` ... `#else/#endif` regions (other conditionals: both kept)."""
    lines = code.split("\n")
    out, stack = [], []   # stack of (dead_now, was_if0)
    dead = False
    for ln in lines:
        m = re.match(r"\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)", ln)
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ("if", "ifdef", "ifndef"):
                stack.append((dead, d == "if" and rest == "0"))
                if d == "if" and rest == "0":
                    dead = True
            elif d in ("else", "elif") and stack and stack[-1][1]:
                dead = stack[-1][0]
            elif d == "endif" and stack:
                dead = stack.pop()[0]
            out.append(blank(ln))
            continue
        out.append(blank(ln) if dead else ln)
    return "\n".join(out)


def local_typedefs(code: str, base: dict) -> dict:
    td = dict(base)
    for m in re.finditer(r"\btypedef\b", code):
        d, k = 0, m.end()
        while k < len(code):
            c = code[k]
            if c in "{(":
                d += 1
            elif c in "})":
                d -= 1
            elif c == ";" and d == 0:
                break
            k += 1
        body = code[m.end():k]
        if "{" in body:
            head = body[:body.find("{")]
            tail = body[body.rfind("}") + 1:]
            is_enum = re.search(r"\benum\b", head) is not None
            for star, nm, arr in re.findall(r"(\**)\s*(\w+)\s*(\[[^\]]*\])?", ATTR.sub("", tail)):
                if star or arr:
                    td[nm] = T("g", "void *", nm, True)
                else:
                    td[nm] = T("g", "int", nm) if is_enum else T("x", nm, nm)
            tag = re.search(r"\b(?:struct|union|class)\s+(\w+)", head)
            if tag and not is_enum:
                td.setdefault(tag.group(1), T("x", tag.group(1), tag.group(1)))
            continue
        fp = re.search(r"\(\s*\*\s*(\w+)\s*\)", body)
        if fp:
            td[fp.group(1)] = T("g", "void *", fp.group(1), True)
            continue
        mm = re.match(r"\s*(.*?)\s*\b(\w+)\s*((?:\[[^\]]*\])*)\s*$",
                      ATTR.sub("", body), re.S)
        if mm:
            if "mode(TI)" in body or "__int128" in body:
                td[mm.group(2)] = T("x", mm.group(2), mm.group(2))
            elif mm.group(3):
                td[mm.group(2)] = T("x", mm.group(2), mm.group(2))
            else:
                r = resolve_type(mm.group(1), td)
                td[mm.group(2)] = T(r.cls, r.c, mm.group(2), r.ptr)
    for m in re.finditer(r"\b(?:struct|class|union)\s+(\w+)\s*(?::[^{;]*)?\{", code):
        td.setdefault(m.group(1), T("x", m.group(1), m.group(1)))
    return td


DECL = re.compile(r"""^\s*(?:__declspec\s*\(\w+\)\s*)?
    (?P<pre>(?:(?:extern|static|inline|__inline|asm)\s*(?:"[^"]*"\s*)?)*)
    (?P<ret>[A-Za-z_][\w\s\*&]*?[\s\*&])
    (?P<name>[A-Za-z_]\w*)\s*
    \((?P<params>[^()]*(?:\([^()]*(?:\([^()]*\))?[^()]*\)[^()]*)*)\)\s*
    (?:__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)\s*|asm\s*\(\s*"[^"]*"\s*\)\s*|throw\s*\(\s*\)\s*)*$""",
                  re.X | re.S)
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")


def match_paren(s: str, i: int) -> int:
    d = 0
    for k in range(i, len(s)):
        c = s[k]
        if c == "(":
            d += 1
        elif c == ")":
            d -= 1
            if d == 0:
                return k
    return -1


def _strip_lhs(s: str) -> str:
    """Text before a call with the call's own `L = (cast)` target removed
    (that assignment happens after the call)."""
    return re.sub(r"(?<![\w.>\]])[A-Za-z_]\w*\s*=(?!=)\s*(?:\([^()]*\)\s*)*$", "", s)


def blank_paren_structs(code: str) -> str:
    """Blank the member list of an inline `struct { .. }` / `union { .. }`
    written inside parentheses (a parameter or cast type:
    ObjRecTableBindSlot_1c53a0's `struct { u8 pad[0x434C]; s32 x; } *arg0`),
    so the brace walk does not take it for a function body and the
    parameter parses as a pointer.  Offsets are kept."""
    if "{" not in code:
        return code
    out = None
    depth = 0
    i = 0
    n = len(code)
    while i < n:
        ch = code[i]
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth = max(0, depth - 1)
        elif ch == "{" and depth > 0:
            m = re.search(r"\b(?:struct|union)\s*\w*\s*$", code[max(0, i - 80):i])
            if m:
                d, k = 0, i
                while k < n:
                    if code[k] == "{":
                        d += 1
                    elif code[k] == "}":
                        d -= 1
                        if d == 0:
                            break
                    k += 1
                if out is None:
                    out = list(code)
                for q in range(i, min(k + 1, n)):
                    if out[q] != "\n":
                        out[q] = " "
                i = k
        i += 1
    return code if out is None else "".join(out)


def parse_file(rel: str, data: bytes, gtd: dict) -> FileInfo:
    text = data.decode("latin-1")
    _code, nostr = S.strip_comments(text)
    # S.strip_comments keeps the quote characters; blank `extern "C"` survives
    code = _PP.sub(lambda m: blank(m.group(0)), blank_if0(nostr))
    code = blank_paren_structs(code)
    # keep extern "C" detectable: strings are blanked, so restore from text
    cpp = rel.endswith(".cpp")
    funcs = S.find_funcs(code)
    fi = FileInfo(rel, text, code, cpp, funcs, [f.start for f in funcs],
                  local_typedefs(code, gtd))
    ls = [0]
    for m in re.finditer("\n", text):
        ls.append(m.end())
    fi.ls = ls
    # object-like macros naming a scalar type (`#define RT bool` in
    # CharaCollClampFloorCeilingMaybe_2364e0: the definition returned `RT`, read as an
    # unknown type, so it stayed out of the header and its caller's s32 view read the
    # bool's garbage upper EAX bytes; switch RG_PROTOS_NO_TYPEMACRO)
    if not os.environ.get("RG_PROTOS_NO_TYPEMACRO"):
        for m in re.finditer(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)[ \t]+([A-Za-z_][\w \t]*?)[ \t]*$",
                             text, re.M):
            nm, rep = m.group(1), m.group(2)
            if nm in fi.tdefs or not all(w in INT_WORDS or w in BUILTIN or w in fi.tdefs
                                         for w in rep.split()):
                continue
            t = resolve_type(rep, fi.tdefs)
            if t.cls in ("g", "f"):
                fi.tdefs[nm] = t
    if cpp:
        for m in re.finditer(r'\bextern\s*"C"\s*\{', _code):
            o = m.end() - 1
            d = 0
            for k in range(o, len(code)):
                if code[k] == "{":
                    d += 1
                elif code[k] == "}":
                    d -= 1
                    if d == 0:
                        fi.externc.append((o, k))
                        break
    # ---- definitions
    for f in funcs:
        if f.kind != "func" or "::" in f.name or f.name == "<anon>":
            continue
        hdr = code[f.start:f.body_open]
        h = hdr.rstrip()
        h2 = re.sub(r"(\s*(__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)|const|throw\s*\(\s*\)))+\s*$",
                    "", h)
        if not h2.endswith(")"):
            continue
        rp = f.start + len(h2) - 1
        lp = S._match_paren_back(code, rp)
        if lp < 0:
            continue
        m = re.search(r"([A-Za-z_]\w*)\s*$", code[f.start:lp])
        if not m or m.group(1) != f.name:
            continue
        noff = f.start + m.start()
        pre = code[f.start:noff]
        cut = max(pre.rfind(";"), pre.rfind("}"))
        if cut >= 0:  # find_funcs header may include leftovers
            pre = pre[cut + 1:]
        pre = pre.lstrip()
        pre_s = " ".join(pre.split())
        static = bool(re.search(r"\bstatic\b", pre_s))
        # an asm function, or a C body with an asm block (syscall stubs, COP2
        # helpers): it reads/writes registers directly, so its C signature is
        # a placeholder and cannot be the truth
        is_asm = bool(re.search(r"\basm\b", pre_s)) or f.is_asm or bool(
            re.search(r"\b(asm|__asm__|__asm)\b", code[f.body_open:f.body_close]))
        clink = (not cpp) or bool(re.search(r'extern\s*"C"', text[f.start:noff])) \
            or fi.in_externc(f.start)
        rett = re.sub(r'extern\s*(?:"[^"]*")?|\bstatic\b|\binline\b|\b__inline\b|\basm\b', " ",
                      re.sub(r'"[^"]*"', "", pre))
        rett = ATTR.sub(" ", rett)
        pr = parse_params(code[lp + 1:rp], fi.tdefs, cpp)
        if pr is None:
            continue
        params, va, unproto = pr
        if unproto:  # a definition `f()` takes no parameters
            unproto = False
        ret = resolve_type(rett, fi.tdefs)
        # param spellings from the original text (names kept for C++ patching)
        fi.defs.append(Def(f.name, rel, Sig(ret, params, va, unproto), static, clink, is_asm,
                           noff - len(pre), noff, lp, rp, f.body_open, f.body_close,
                           " ".join(re.sub(r'extern\s*"\s*"', 'extern "C"',
                                           code[noff - len(pre):rp + 1]).split())))
    # ---- declarations (statement-wise, outside class bodies)
    class_ranges = [(f.body_open, f.body_close) for f in funcs if f.kind == "class"]
    prev = 0
    for m in re.finditer(r"[;{}]", code):
        i = m.start()
        if code[i] != ";":
            prev = i + 1
            continue
        st = code[prev:i]
        a = prev
        prev = i + 1
        dm = DECL.match(st) if "(" in st else None
        if not dm:
            # `extern u8 Func_123[];`: a data view of a code symbol
            if re.match(r"\s*extern\b", st) or (fi.enclosing(a) is None and st.strip()):
                head = st[:split_top(st, "=")[0][1]]
                for x, y in split_top(head):
                    dcl = ATTR.sub("", head[x:y])
                    if "(" in dcl:
                        continue
                    mm = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", dcl)
                    if mm:
                        fi.objdecls.add(mm.group(1))
            continue
        name = dm.group("name")
        ret = dm.group("ret")
        rw = ret.split()
        if not rw or name in KEYWORDS or any(w in RET_BAD for w in rw):
            continue
        if any(lo < a < hi for lo, hi in class_ranges):
            continue
        ff = fi.enclosing(a)
        if ff is not None and not re.search(r"\bextern\b", dm.group("pre")) and \
                not re.match(r"\s*(?:static\s+|extern\s+)?(?:const\s+)?(?:struct\s+|union\s+|enum\s+|unsigned\s+|signed\s+)?[A-Za-z_]\w*[\s*]", st):
            continue
        pr = parse_params(dm.group("params"), fi.tdefs, cpp)
        if pr is None:
            continue
        params, va, unproto = pr
        if ff is not None and not params and not unproto and False:
            pass
        rt = resolve_type(ret, fi.tdefs)
        lp = a + dm.start("params") - 1
        rp = a + dm.end("params")
        start = a + len(st) - len(st.lstrip())
        pre = dm.group("pre")
        clink = (not cpp) or 'extern "C"' in text[start:a + dm.start("name")] \
            or bool(re.search(r'extern\s*"C"', text[start:a + dm.start("name")])) \
            or fi.in_externc(a)
        # block-scope `T f(x);` with an identifier that is a local variable is
        # a C++ direct-init, not a declaration: params must be types
        if ff is not None and params and all(p.cls == "x" and not p.name for p in params):
            continue
        fi.decls.append(Decl(name, start, i + 1, ff, Sig(rt, params, va, unproto),
                             " ".join(text[start:i + 1].split()),
                             bool(re.search(r"\bstatic\b", pre)), clink, lp, rp,
                             (a + dm.start("ret"), a + dm.end("ret"))))
    # C++: a function first declared inside `extern "C" { .. }` keeps C
    # linkage at its later plain definition ([dcl.link]: the first
    # declaration's linkage wins).  HatenaMarkListAssignNearby_344900 is
    # declared in the file's extern "C" block and defined outside it; seen as
    # C++ linkage, its C callers were left `manual-call` with their wrong
    # views (BRINGUP.md 2026-10-18: the call without its list argument).
    if cpp and not os.environ.get("RG_PROTOS_NO_EXTERNC"):
        for d in fi.defs:
            if not d.clink and not d.static and any(
                    dc.name == d.name and dc.clink and dc.func is None and dc.start < d.start
                    for dc in fi.decls):
                d.clink = True
    return fi


def find_calls(fi: FileInfo, names: set) -> None:
    code = fi.code
    decl_spans = [(d.start, d.end) for d in fi.decls]
    ds = [s for s, _ in decl_spans]
    for f in fi.funcs:
        if f.kind not in ("func", "member"):
            continue
        a, b = f.body_open, f.body_close
        for m in CALL.finditer(code, a, b):
            nm = m.group(1)
            if nm not in names:
                continue
            s = m.start(1)
            k = s - 1
            while k > a and code[k] in " \t\r\n":
                k -= 1
            if code[k] == "." or code[k - 1:k + 1] in ("->", "::"):
                continue
            j = bisect_right(ds, s) - 1
            if j >= 0 and decl_spans[j][0] <= s < decl_spans[j][1]:
                continue
            lp = m.end() - 1
            rp = match_paren(code, lp)
            if rp < 0 or rp > b:
                continue
            inner = code[lp + 1:rp]
            args = []
            if inner.strip():
                for x, y in split_top(inner):
                    seg = inner[x:y]
                    l = len(seg) - len(seg.lstrip())
                    r = len(seg.rstrip())
                    args.append((lp + 1 + x + l, lp + 1 + x + r))
            fi.calls.append(Call(nm, s, lp, rp, args, fi.enclosing(s) or f))


# ------------------------------------------------------------------ analysis helpers
SIDE = re.compile(r"\+\+|--|(?<![=!<>])=(?!=)|\b(?!sizeof\b)[A-Za-z_]\w*\s*\(")


def side_effect_free(expr: str) -> bool:
    e = expr
    # casts `(T)x` / `(T*)x` are not calls; an identifier directly before '(' is
    return SIDE.search(e) is None


STMT_KW = ("if", "while", "for", "switch")
ANYCALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
NOT_CALL = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case",
            "__attribute__", "defined"}


def value_used(fi: FileInfo, c: Call, encl_ret_void: bool) -> bool:
    code = fi.code
    # after
    k = c.rparen + 1
    while k < len(code) and code[k] in " \t\r\n":
        k += 1
    nxt = code[k] if k < len(code) else ";"
    # before (skip a `(void)` cast)
    k = c.start - 1
    while k >= 0 and code[k] in " \t\r\n":
        k -= 1
    before = code[max(0, k - 5):k + 1]
    if re.search(r"\(\s*void\s*\)$", code[max(0, k - 12):k + 1]):
        return False
    if nxt != ";" and nxt != ",":
        return True
    if nxt == ",":
        return True   # comma operand / argument: conservatively used
    prevc = code[k] if k >= 0 else ";"
    if prevc in ";{}":
        return False
    if prevc == ":":
        st = code[max(0, k - 400):k]
        st = st[max(st.rfind(";"), st.rfind("{"), st.rfind("}")) + 1:]
        return "?" in st
    if re.search(r"\b(else|do)$", before):
        return False
    if re.search(r"\breturn$", before):
        return not encl_ret_void
    if prevc == ")":
        o = S._match_paren_back(code, k)
        if o > 0 and re.search(r"\b(if|while|for|switch)\s*$", code[max(0, o - 10):o]):
            return False
        return True   # a cast
    return True


# ------------------------------------------------------------------ the index
class V0Tail:
    """Tail evidence of rule `def-v0-return`: the C calls whose result is
    $v0 at some exit of retail's listing."""

    def __init__(self, calls):
        self.calls = calls
        self.name = calls[0].name if calls else "?"


@dataclass
class Rewrite:
    start: int
    end: int
    kind: str        # 'call' | 'text'
    text: str = ""
    call: object = None
    newargs: list = None      # list of ('arg', idx) | ('zero', ctext)
    keep: list = None         # idx of dropped args kept for side effects
    wrap: tuple = None        # None | ('cast', T) | ('zero', T)


class ProtoStage:
    name = "protos"

    def __init__(self, port_root=None, provider_dirs=None, provider_headers=None):
        # provider prototype sources (tests point these at a fixture tree)
        self.port_root = Path(port_root) if port_root is not None else PORT
        self.provider_dirs = PROVIDER_DIRS if provider_dirs is None else tuple(provider_dirs)
        self.provider_headers = (PROVIDER_HEADERS if provider_headers is None
                                 else tuple(provider_headers))
        self.addr_table = None
        # RG_PROTOS_SB_CENSUS=<path>: JSON lines of every stack-address call
        # argument (tools/census/stackblock_census.py classifies them)
        self.sb_census = [] if os.environ.get("RG_PROTOS_SB_CENSUS") else None
        self._asm_cache: dict = {}
        self._asm_arg_cache: dict = {}
        self._site_cache: dict = {}
        self._ph_cache: dict = {}
        self._sbv_cache: dict = {}
        self._cfg_cache: dict = {}
        self.entry_copies: dict = {}          # id(Def) -> {param name: Def}
        self.files: dict[str, FileInfo] = {}
        self.out: dict[str, bytes] = {}
        self.inhash: dict[str, str] = {}
        self.log: list[tuple] = []
        self.header = b""
        self.stats = Counter()
        self._tm = {}
        self.prepared = False

    # -------------------------------------------------------------- prepare
    def prepare(self, files: dict[str, bytes]) -> None:
        gtd: dict = {}
        hdr = []
        for rel in sorted(files):
            if rel.startswith("include/") and rel.endswith(".h"):
                txt = files[rel].decode("latin-1")
                c = _PP.sub(lambda m: blank(m.group(0)), S.strip_comments(txt)[1])
                gtd = local_typedefs(c, gtd)
                if not rel.startswith("include/port/"):
                    # C view of the header for struct layouts (stack-block sizes):
                    # the C++-only parts (Vec4's operator=) dropped
                    t = re.sub(r"^[ \t]*#\s*ifdef\s+__cplusplus\b.*?^[ \t]*#\s*endif[^\n]*", "",
                               S.strip_comments(txt)[1], flags=re.M | re.S)
                    hdr.append(_PP.sub(lambda m: blank(m.group(0)), t))
        self.gtd = gtd
        self.hdr_code = "\n".join(hdr)
        srcs = sorted(r for r in files if r.startswith("src/") and r.endswith(SRC_EXT))
        for rel in srcs:
            self.files[rel] = parse_file(rel, files[rel], gtd)
            self.inhash[rel] = hashlib.sha256(files[rel]).hexdigest()
        self.hosted = {}
        if "config/hosted.txt" in files:
            for ln in files["config/hosted.txt"].decode("latin-1").splitlines():
                f = ln.split("#")[0].split()
                if len(f) >= 2:
                    self.hosted[f[0]] = f[1]
        self._load_providers()
        self._address_aliases(gtd)
        # header-owned symbols: prototypes in include/*.h
        self.hdr_owned: dict[str, str] = {}
        for rel in sorted(files):
            if rel.startswith("include/") and rel.endswith(".h") and not rel.startswith(
                    "include/port/"):
                fi = parse_file(rel, files[rel], gtd)
                for d in fi.decls:
                    self.hdr_owned.setdefault(d.name, rel)
        self._index()
        self._u128_views()
        self._agg_views()
        self._plan()
        self.prepared = True

    _I128 = re.compile(r"^(?:const\s+|volatile\s+)*(?:u128|s128|__int128|rg_u128|"
                       r"unsigned\s+__int128)$")

    def _agg_views(self) -> None:
        """Rule `agg-view` (2026-10-25, protos manual-row close-out).  A local view that
        takes an OVER-ALIGNED aggregate by value (alignment > 4: `RGBAQ`, `RGBA` declared
        `aligned(8)`) where the definition has an integer scalar of the same size in that
        GPR lane (FontDrawGaiji_26dd50(.., s64 rgba)).  On the EE both are one 64-bit GPR
        holding the same bytes; i686-windows-msvc cannot pass an over-aligned aggregate by
        value and passes its ADDRESS instead (clang: `ptr dead_on_return`), so the callee
        read the pointer and a stale stack word as the colour (every gaiji glyph in the
        message windows / text renderers: FontDrawText_26cdc0, FontDrawTextGradient_26c6e0,
        MesWinDrawGlyphs_271b70).  The view's slot becomes `rg_aggbits` (kind `a`): the
        ordinary rules bind the call to the definition (C: header prototype; C++: patched
        declaration) and the argument is passed as `__builtin_bit_cast(<def type>, (x))`
        (`agg-bits` rows).  Aggregates of alignment <= 4 are passed by value in the same
        stack words on i686 (bit-identical; tools/bringup/protos_irabi.py `OK-bits`) and
        are left alone.  Switch RG_PROTOS_NO_AGGVIEW."""
        if os.environ.get("RG_PROTOS_NO_AGGVIEW"):
            return
        for fi in self.files.values():
            for dc in fi.decls:
                s = dc.sig
                if s.unproto or s.va or s.ret.cls == "x":
                    continue
                xs = [i for i, p in enumerate(s.params) if p.cls == "x"]
                if not xs or any(self._I128.match(" ".join(s.params[i].raw.split())) for i in xs):
                    continue
                d = self.resolve(fi, dc.name)
                if d is None or d.is_asm:
                    continue
                ds = d.sig
                if ds.va or ds.unproto or ds.ret.cls == "x" or any(p.cls == "x" for p in ds.params):
                    continue
                vg = [i for i, p in enumerate(s.params) if p.cls != "f"]
                dg = [i for i, p in enumerate(ds.params) if p.cls != "f"]
                newp, what, ok = list(s.params), [], True
                for k, i in enumerate(vg):
                    p = s.params[i]
                    if p.cls != "x":
                        continue
                    tn = re.sub(r"^\s*(struct|union)\s+", "", p.raw)
                    sz = self._type_size(fi, tn, "")
                    q = ds.params[dg[k]] if k < len(dg) else None
                    want = {"q": 8, "i": 4}.get(q.kind) if q is not None and q.cls == "g" \
                        and not q.ptr else None
                    # MSVC x86 passes by address only an aggregate whose alignment is
                    # REQUIRED > 4 (an aligned(N) attribute); a struct holding an s64 has
                    # natural alignment 8 but goes by value (clang: i64 coerced)
                    if sz is None or want is None or self._explicit_align(fi, tn) <= 4 \
                            or sz[0] != want:
                        ok = False
                        break
                    newp[i] = T("g", "rg_aggbits", p.raw, False, p.name)
                    what.append(f"param{i + 1} {p.raw} ({sz[0]} bytes, align {sz[1]}) vs {q.raw}")
                if not ok or not what:
                    continue
                dc.sig = Sig(s.ret, newp, s.va, s.unproto)
                self._log(fi, dc.start, dc.name, "agg-view",
                          f"{'; '.join(what)}: one EE register either way; i686 passes an "
                          f"over-aligned aggregate by address -> bound to the definition as bits "
                          f"({d.rel})")

    def _explicit_align(self, fi, typ: str, depth=0) -> int:
        """The largest `aligned(N)` attribute on aggregate type typ (its definition in
        the file, else the game headers' C view; typedef aliases followed; an attribute
        inside the body counts too), 0 when none."""
        if depth > 6:
            return 0
        name = re.sub(r"^(struct|union|class)\s+", "", typ.strip())
        d = self._find_typedef(fi.code, name)
        if d is None:
            d = self._find_typedef(getattr(self, "hdr_code", ""), name)
        if d is None or d[0] == "enum":
            return 0
        if d[0] == "alias":
            own = [int(x) for x in clayout.ALIGNED.findall(d[2] or "")]
            return max(own + [self._explicit_align(fi, d[1], depth + 1)])
        own = max([int(x) for x in clayout.ALIGNED.findall((d[2] or "") + " " + d[1])] + [0])
        if d[0] != "union" and re.search(r":\s*\d+\s*[;,]", d[1]):
            # the dialect stage (after this one) re-declares a GCC-packed bitfield run with
            # 1-byte types and pins mwcc's alignment with aligned(A): RGBAQ `u64 r:8 ..`
            # becomes `unsigned char r:8 .. } __attribute__((aligned(8)))`, over-aligned
            own = max(own, self._dialect_bitfield_align(d[1]))
        return own

    @staticmethod
    def _dialect_bitfield_align(body: str) -> int:
        """aligned(A) the dialect stage's bitfield-gcc rule will put on `struct { body }`."""
        try:
            import importlib.util
            spec = importlib.util.spec_from_file_location(
                "rg_portxform", str(Path(__file__).resolve().parents[1] / "portxform.py"))
            px = ProtoStage.__dict__.get("_px")
            if px is None:
                px = importlib.util.module_from_spec(spec)
                sys.modules["rg_portxform"] = px
                spec.loader.exec_module(px)
                ProtoStage._px = px
            code = "struct rgp_probe {" + body + "};"
            al = 0
            for _a, _b, txt in px._bitfield_edits(code, "rgp_probe.c"):
                al = max([al] + [int(x) for x in clayout.ALIGNED.findall(txt)])
            return al
        except Exception:
            return 0

    def _u128_views(self) -> None:
        """Rule `u128-view`.  A local view that returns or takes a 128-bit
        integer (u128/s128) where the definition has a 4/8-byte scalar: on
        the EE both are ONE general register ($v0 / $aN), mwcc moved the
        value with lq/sq and the low bits are the scalar.  On i686 a u128
        return is a hidden sret pointer and a u128 argument 16 stack bytes,
        so such a call reads the wrong slots
        (ActionPacketInitBattleDefeat_3e33e0's `u128
        CharaSysGetEncounterEntryIdMaybe_3a36f0(..)`: the callee took the sret
        pointer as its object and faulted at the first enemy defeat,
        BRINGUP.md 2026-10-18).  The view's 128-bit slots become kind `o`
        (T c = "rg_u128"): the slot no longer blocks the call as a struct by
        value, and the ordinary rules make the call ABI-correct against the
        definition (C: the local declaration is dropped for the header
        prototype; C++: patched to the definition's shape).  The value then
        converts to/from the caller's u128 local as a C integer conversion
        (unsigned _BitInt(128), include/port/u128.h)."""
        if os.environ.get("RG_PROTOS_NO_U128VIEW"):
            return
        for fi in self.files.values():
            for dc in fi.decls:
                s = dc.sig
                if s.unproto or s.va:
                    continue
                slots = [s.ret] + list(s.params)
                i128 = [t.cls == "x" and bool(self._I128.match(" ".join(t.raw.split()))) for t in slots]
                if not any(i128) or any(t.cls == "x" and not w for t, w in zip(slots, i128)):
                    continue
                d = self.resolve(fi, dc.name)
                if d is None or d.is_asm:
                    continue
                ds = d.sig
                if ds.va or ds.unproto or ds.ret.cls == "x" or any(p.cls == "x" for p in ds.params):
                    continue
                vg = [i for i, p in enumerate(s.params) if p.cls != "f"]
                dg = [i for i, p in enumerate(ds.params) if p.cls != "f"]
                ok, what = True, []
                newp = list(s.params)
                for k, i in enumerate(vg):
                    p = s.params[i]
                    if p.cls != "x":
                        continue
                    if k >= len(dg) and not os.environ.get("RG_PROTOS_NO_U128EXTRA") \
                            and self._def_reads_reg(d, "$%d" % (4 + k)) == "no":
                        # an EXTRA GPR lane: the definition has no parameter there and its
                        # listing never reads the register (VecSolveDistanceConstraint_364740
                        # viewed as (Vec4 *, Vec4 *, u128, f32, f32): retail's $a2 is ignored,
                        # the floats are $f12/$f13).  On i686 the u128 is a hidden pointer
                        # word in front of the floats, so the callee read the pointer as its
                        # first float.  Kind `o`: the ordinary mapping drops it (drop-extra).
                        newp[i] = T("g", "rg_u128", p.raw, False, p.name)
                        what.append(f"param{i + 1} {p.raw}: extra GPR lane $a{k} the definition "
                                    f"never reads (dropped)")
                        continue
                    if k >= len(dg) or ds.params[dg[k]].cls != "g":
                        ok = False
                        break
                    newp[i] = T("g", "rg_u128", p.raw, False, p.name)
                    what.append(f"param{i + 1} {p.raw} vs {ds.params[dg[k]].raw}")
                newr = s.ret
                if ok and s.ret.cls == "x":
                    if ds.ret.cls != "g":
                        ok = False
                    else:
                        newr = T("g", "rg_u128", s.ret.raw)
                        what.append(f"ret {s.ret.raw} vs {ds.ret.raw}")
                if not ok:
                    continue
                dc.sig = Sig(newr, newp, s.va, s.unproto)
                self._log(fi, dc.start, dc.name, "u128-view",
                          f"{'; '.join(what)}: one EE register either way; i686 passes a "
                          f"128-bit integer by hidden pointer / 16 stack bytes -> the view's "
                          f"128-bit slots are bound to the definition ({d.rel})")

    def image_of(self, rel: str) -> str:
        m = re.search(r"(?:^|/)src/overlays/(\w+)/", rel)
        return m.group(1) if m else "main"

    # -------------------------------------------------------------- providers
    def _load_providers(self) -> None:
        """Prototypes of the port providers (PROVIDER_DIRS definitions, then
        PROVIDER_HEADERS declarations, then HOST_CRT).  Used in _index() for
        callees that have no C truth in the corpus."""
        self.prov_defs: dict[str, Def] = {}
        self.host_crt: dict[str, Def] = {}

        def add(nm, d, table):
            if nm not in table and nm not in KEYWORDS and not d.sig.va:
                table[nm] = d

        for root in self.provider_dirs:
            base = self.port_root / root
            if not base.is_dir():
                continue
            for f in sorted(base.rglob("*")):
                if f.suffix not in SRC_EXT or not f.is_file():
                    continue
                rel = f"{root}/{f.relative_to(base).as_posix()}"
                pf = parse_file(rel, f.read_bytes(), self.gtd)
                for d in pf.defs:
                    if not d.static and d.clink and not d.is_asm:
                        add(d.name, d, self.prov_defs)

        def decls_of(rel, data, table):
            # array typedefs (Sony's `typedef float sceVu0FVECTOR[4] ..;`) decay to
            # pointers as parameters: spell them so (src/sce/vu0/sce_vu0.h)
            txt = data.decode("utf-8", "replace")
            for m in list(re.finditer(r"\btypedef\s+([\w ]+?)\s+(\w+)\s*\[[^;]*;", txt)):
                txt = re.sub(r"\b%s\b(?=\s+\w+\s*[,)])" % re.escape(m.group(2)),
                             m.group(1) + " *", txt)
            data = txt.encode()
            pf = parse_file(rel, data, self.gtd)
            for dc in pf.decls:
                if dc.func is not None or dc.static or dc.sig.unproto:
                    continue
                add(dc.name, Def(dc.name, rel, dc.sig, False, True, False, dc.start,
                                 dc.start, dc.lparen, dc.rparen, -1, -1,
                                 " ".join(dc.text.rstrip(";").split())), table)

        for h in self.provider_headers:
            f = self.port_root / h
            if f.is_file():
                decls_of(f"port:{h}", f.read_bytes(), self.prov_defs)
        decls_of("port:host-crt.h", HOST_CRT.encode(), self.host_crt)

    _ADDR_NAME = re.compile(r"\b(?:func|FUN)_([0-9A-Fa-f]{6,8})\b(?!_e\d)")

    def _entry_ordinal(self, a, cont, ca, k, entries, defined) -> int:
        """The k of the C entry `func_<ca>_e<k>` at address a.  Default: a is
        the k-th `alabel` of the container's listing.  data2c's
        function_entries pins some `_e<k>` names to addresses (vtable words
        into unlabelled jr stubs); those k are taken, and the alabels the table
        does not cover get the remaining defined k in address order.  Without
        that, func_00418BB0 (the 17th entry of ContainerViewGetAtFwd_418ab0, its
        only alabel) bound to `_e1` (0x418AC0, a `jr *0x10(vptr)` stub) and every
        DataTable view's GetAt called LoadResidentBin (BRINGUP fix 14)."""
        fe = (getattr(self, "addr_table", None) or {}).get("fentries") or {}
        if ca is None or not fe:
            return k
        pat = re.compile(r"(?:func|FUN)_%08X_e(\d+)$" % ca, re.I)
        if a in fe:
            m = pat.match(fe[a])
            return int(m.group(1)) if m else k
        known = {int(m.group(1)): ad for ad, sym in fe.items() for m in [pat.match(sym)] if m}
        if not known:
            return k
        dk = sorted({int(m.group(1)) for n in defined for m in [pat.match(n)] if m} - set(known))
        labs = sorted(ad for ad, (c2, _k2, _ca2) in entries.items()
                      if c2 == cont and ad not in known.values())
        if len(dk) == len(labs) and a in labs:
            return dk[labs.index(a)]
        return k

    def _address_aliases(self, gtd: dict) -> None:
        """Address-style names at a MAIN address (`func_1594D0`, `FUN_001cb3c0`:
        a call the decomp spelled by address, mostly overlay code calling MAIN)
        that no file defines are renamed, in every file, to the MAIN symbol
        defined at that address (config/main.symbols.txt), or for an interior
        entry of a multi-entry function (an `alabel` of its listing) to the C
        entry `func_<start>_e<k>`.  The call then binds to the real definition
        (header prototype, ABI mapping) and the object references the real
        symbol, so no link-time alias is needed (rule `addr-alias`).  Names
        that cannot be renamed are logged `addr-alias-unresolved` with why
        (kernel-RAM address, interior entry without a C entry, no symbol)."""
        tab = getattr(self, "addr_table", None)
        self.renamed: dict[str, str] = {}
        self.renamed_files: set[str] = set()
        if not tab:
            return
        defined = {d.name for fi in self.files.values() for d in fi.defs}
        refs: dict[str, list] = defaultdict(list)
        for fi in self.files.values():
            for m in self._ADDR_NAME.finditer(fi.code):
                refs[m.group(0)].append(fi.rel)
        main, entries = tab["main"], tab["entries"]
        # (container start, k) -> address of every C interior entry, for
        # _name_addr (def-vthunk-naked reads the entry's listing by it)
        self._entry_rev = {}
        for a0, (cont0, k0, ca0) in entries.items():
            if ca0 is not None:
                self._entry_rev[(ca0, self._entry_ordinal(a0, cont0, ca0, k0, entries, defined))] = a0
        for a0, sym in (tab.get("fentries") or {}).items():
            mm = re.search(r"_([0-9A-Fa-f]{8})_e(\d+)$", sym)
            if mm:
                self._entry_rev[(int(mm.group(1), 16), int(mm.group(2)))] = a0
        for nm in sorted(refs):
            if nm in defined:
                continue
            a = int(nm.split("_", 1)[1], 16)
            if a >= OVL_BASE:
                continue                       # overlay import (_overlay_imports)
            where = sorted(set(refs[nm]))
            why = None
            tgt = main.get(a)
            if a < MAIN_LO:
                why = "kernel-RAM address (EE kernel code the SDK patch calls; the kernel HLE replaces it)"
            elif tgt and tgt != nm:
                self.renamed[nm] = tgt
            elif a in entries:
                cont, k, ca = entries[a]
                k = self._entry_ordinal(a, cont, ca, k, entries, defined)
                e = f"func_{ca:08X}_e{k}" if ca is not None else None
                # the C entry may be spelled Ghidra-style (TaskLoadSound_207a80.c
                # defines FUN_00207a80_e1 for func_00207A90)
                alt = [x for x in (e, f"FUN_{ca:08x}_e{k}", f"FUN_{ca:08X}_e{k}")
                       if ca is not None and x in defined]
                if alt:
                    self.renamed[nm] = alt[0]
                else:
                    why = f"interior entry {k} of {cont}: no C definition of {e}"
            else:
                why = "no MAIN symbol or listing entry at this address"
            if why:
                self.log.append((where[0], 0, nm, "addr-alias-unresolved",
                                 f"{why}; {len(where)} file(s)"))
                self.stats["addr-alias-unresolved"] += 1
            else:
                tg = self.renamed[nm]
                how = ("C definition" if tg in defined else
                       "port provider" if tg in self.prov_defs else "no definition in the corpus")
                self.log.append((where[0], 0, nm, "addr-alias",
                                 f"-> {tg} ({how}); {len(where)} file(s)"))
                self.stats["addr-alias"] += 1
        # rule `text-alias`: a data-style name D_<addr> at a MAIN address where a
        # C function is defined (NORMAL's MenuBattleEndInit passes D_002931A0,
        # declared `extern const u8 D_002931A0[]`, to ConstructNewArray_100710
        # as the element constructor = UiTextElemInit_2931a0): the name is
        # renamed to the function and its data declaration dropped, so the
        # pointer is the function (it was a zero-filled UNBOUND data stub).
        drop_decl: set[str] = set()
        drefs: dict[str, list] = defaultdict(list)
        for fi in self.files.values():
            for m in re.finditer(r"\bD_([0-9A-Fa-f]{8})\b", fi.code):
                drefs[m.group(0)].append(fi.rel)
        for nm in sorted(drefs):
            a = int(nm[2:], 16)
            tgt = main.get(a)
            if a < MAIN_LO or a >= OVL_BASE or not tgt or tgt == nm or tgt.startswith("D_") \
                    or tgt not in defined:
                continue
            # only a name some file declares as a data array (`extern const u8
            # D_002931A0[];`); D_0022f1e0-style names are struct tags/typedefs
            dre = re.compile(r"\bextern\s+(?:const\s+)?\w+\s+%s\s*\[" % re.escape(nm))
            if not any(dre.search(self.files[r].code) for r in set(drefs[nm])):
                continue
            self.renamed[nm] = tgt
            drop_decl.add(tgt)
            where = sorted(set(drefs[nm]))
            self.log.append((where[0], 0, nm, "text-alias",
                             f"-> {tgt} (C definition at the same MAIN text address); "
                             f"{len(where)} file(s)"))
            self.stats["text-alias"] += 1
        if not self.renamed:
            return
        rx = re.compile(r"\b(" + "|".join(re.escape(n) for n in sorted(self.renamed)) + r")\b")
        for rel, fi in list(self.files.items()):
            hits = [m for m in rx.finditer(fi.code)]
            if not hits:
                continue
            t, pos, out = fi.text, 0, []
            for m in hits:
                out.append(t[pos:m.start()])
                out.append(self.renamed[m.group(1)])
                pos = m.end()
            out.append(t[pos:])
            new = "".join(out)
            for tg in drop_decl:
                new = re.sub(r"^[ \t]*extern\s+(?:const\s+)?\w+\s+%s\s*\[\s*\]\s*;" % re.escape(tg),
                             "/* rgp text-alias: %s is the C function */" % tg, new, flags=re.M)
            self.files[rel] = parse_file(rel, new.encode("latin-1"), gtd)
            self.renamed_files.add(rel)
            self.stats["addr-alias-files"] += 1

    def _index(self):
        self.defs_by_name: dict[str, list[Def]] = defaultdict(list)
        self.asm_defs: set[str] = set()
        for fi in self.files.values():
            for d in fi.defs:
                if d.is_asm:      # asm body: its C signature is a placeholder
                    self.asm_defs.add(d.name)
                    continue
                self.defs_by_name[d.name].append(d)
        self.stats["info-asm-defs-not-truth"] = len(self.asm_defs)
        # port providers: truth for names with no C definition in the corpus
        self.provider: dict[str, Def] = {}
        # only names the corpus refers to: an override may define port-side
        # helpers (rg_FileReqPrefetch in the file lane's FileReqThread_182c30.c)
        # that no game file declares; a header prototype of those only
        # conflicts with the overrides' own declarations
        mentioned = {dc.name for fi in self.files.values() for dc in fi.decls}
        mentioned |= set(getattr(self, "hdr_owned", {}) or {})
        for nm, d in sorted(self.prov_defs.items()):
            if nm in self.defs_by_name:
                continue
            if (nm not in mentioned and not re.search(r"_[0-9a-fA-F]{6}$", nm)
                    and d.rel.startswith(tuple(f"{r}/" for r in self.provider_dirs))):
                continue
            self.defs_by_name[nm].append(d)
            self.provider[nm] = d
        # host CRT names: local policy only (never in game_protos.h)
        self.local_names: set[str] = set()
        for nm, d in sorted(self.host_crt.items()):
            if nm in self.defs_by_name:
                continue
            self.defs_by_name[nm].append(d)
            self.provider[nm] = d
            self.local_names.add(nm)
        self.stats["info-provider-protos"] = len(self.provider)
        self._overlay_imports()
        # + the printf family (variadic providers are not in defs_by_name):
        # their calls are only read by rule vararg-missing
        names = set(self.defs_by_name) | set(self._PRINTF_FMT)
        for fi in self.files.values():
            find_calls(fi, names)
        self._unstatic_hosted()
        # the global (externally linked, C linkage) definition per name
        self.gdef: dict[str, Def] = {}
        self.dup_ext: dict[str, list] = {}
        for nm, ds in self.defs_by_name.items():
            if nm in self.import_multi:
                continue
            ext = [d for d in ds if not d.static]
            if not ext:
                continue
            if len(ext) > 1:
                self.dup_ext[nm] = ext
                self.stats["info-dup-external-defs"] += 1
            # prefer MAIN, then C over asm
            ext.sort(key=lambda d: (self.image_of(d.rel) != "main", d.is_asm, d.rel))
            self.gdef[nm] = ext[0]

    def _unstatic_hosted(self):
        """A hosted guest (config/hosted.txt) is `static` inside its host's
        file (an mwcc register-allocation lever).  When other units call it
        (with their own declarations, which nothing could resolve at link) and
        it is the only definition of the name, `static` is dropped from the
        definition and from the host file's own declarations of it (rule
        `hosted-unstatic`); its callers then bind to it like any definition."""
        self.unstatic: set[int] = set()
        users_of: dict[str, set] = defaultdict(set)
        for fi in self.files.values():
            for c in fi.calls:
                users_of[c.name].add(fi.rel)
        for nm, ds in sorted(self.defs_by_name.items()):
            if len(ds) != 1 or not ds[0].static or ds[0].rel not in self.files:
                continue
            d = ds[0]
            if nm not in self.hosted:
                continue
            users = sorted(u for u in users_of.get(nm, ()) if u != d.rel)
            if not users:
                continue
            d.static = False
            self.unstatic.add(id(d))
            self.log.append((d.rel, self.files[d.rel].line(d.start), nm, "hosted-unstatic",
                             f"static in its host, called from {len(users)} other unit(s), "
                             f"e.g. {users[0]}"))
            self.stats["hosted-unstatic"] += 1

    _IMPORT = re.compile(r"^(?:func|FUN)_([0-9A-Fa-f]{6,8})$")
    _ADDR_SFX = re.compile(r"_([0-9a-f]{6,8})$")

    def _overlay_imports(self):
        """MAIN calls overlay code by address-style names (`func_4EC3E0`,
        `FUN_004efc40`: the linker import of whichever overlay is resident).
        No MAIN file defines them, so without help every MAIN thunk around
        one looked like `void T(void) { func_X(); }` calling an unknown and
        its callers read `(T(), 0)`.  The truth is the overlay definition at
        that address (the same `import-proto` rows tools/gen_overlay_registry.py
        reports): when every overlay defining the address agrees on the i686
        ABI shape, the import name is bound to that definition (an alias Def),
        so game_protos.h declares it and the tail-return rule types the thunks.
        When only the return differs and the value views are all integer
        (void vs EAX/EDX:EAX: a void caller ignores the register), the
        value-returning view is taken (`overlay-import-disagree`, ret only).
        Otherwise the import is bound PER CALLING FILE
        (`overlay-import-per-site` + one `overlay-import-site` row per file):
        the overlay resident when that MAIN code runs is the one whose
        definition the caller's own view matches (the decomp view was written
        against that overlay's code), so the file binds the name to that
        definition, gets no game_protos.h prototype for it, and has its local
        declaration patched in place to that definition's shape.  The overlay
        trampoline behind the import name is a bare jump, so a per-file
        prototype is all the ABI needs (docs/PROTOS.md)."""
        self.import_alias: dict[str, Def] = {}
        self.import_src: dict[str, Def] = {}
        self.import_multi: dict[str, list] = {}
        self.import_pick: dict[tuple, Def] = {}
        by_addr: dict[int, list[Def]] = defaultdict(list)
        for nm, ds in self.defs_by_name.items():
            for d in ds:
                img = self.image_of(d.rel)
                m = self._ADDR_SFX.search(nm)
                if img != "main" and m and not d.static and d.rel in self.files:
                    by_addr[int(m.group(1), 16)].append(d)
        wanted: set[str] = set()
        for fi in self.files.values():
            if self.image_of(fi.rel) != "main":
                continue
            for m in re.finditer(r"\b(?:func|FUN)_[0-9A-Fa-f]{6,8}\b", fi.code):
                wanted.add(m.group(0))
        for nm in sorted(wanted):
            if nm in self.defs_by_name:
                continue
            a = int(self._IMPORT.match(nm).group(1), 16)
            if a < 0x4E9E80:
                continue
            cands = by_addr.get(a, [])
            if not cands:
                continue
            shapes = {(d.sig.ret.kind, tuple(p.kind for p in d.sig.params), d.sig.va)
                      for d in cands}
            pick = cands[0]
            if len(shapes) > 1:
                params = {(s[1], s[2]) for s in shapes}
                desc = "; ".join(f"{self.image_of(d.rel)}: {d.proto_text}" for d in cands)
                pick = None
                if len(params) == 1:
                    vals = [d for d in cands if d.sig.ret.cls != "v"]
                    rets = {d.sig.ret.kind for d in vals}
                    if len(rets) == 1 and rets <= {"i", "q"}:
                        pick = vals[0]
                        self.log.append(("-", 0, nm, "overlay-import-disagree",
                                         f"ret only; took {self.image_of(pick.rel)}: {desc}"))
                        self.stats["overlay-import-disagree"] += 1
                if pick is None:
                    al = [Def(**{**d.__dict__, "name": nm}) for d in cands]
                    self.import_multi[nm] = al
                    for x, d in zip(al, cands):
                        self.import_src[id(x)] = d
                    self.defs_by_name[nm].extend(al)
                    self.local_names.add(nm)
                    self.log.append(("-", 0, nm, "overlay-import-per-site",
                                     f"bound per calling file: {desc}"))
                    self.stats["overlay-import-per-site"] += 1
                    continue
            alias = Def(**{**pick.__dict__, "name": nm})
            self.import_alias[nm] = alias
            self.import_src[id(alias)] = pick
            self.defs_by_name[nm].append(alias)
            self.stats["overlay-import-bound"] += 1

    def _pick_import(self, fi: FileInfo, name: str) -> Def:
        """Per-site binding of a disagreeing overlay import: the candidate the
        file's own view matches best (parameter kinds, then classes, then
        count, then the return kind); ties go to the overlay whose name the
        calling file's path carries (FieldHud = normal, InsectVs = insmenu)."""
        key = (fi.rel, name)
        if key in self.import_pick:
            return self.import_pick[key]
        cands = self.import_multi[name]
        views = [dc.sig for dc in fi.decls if dc.name == name and not dc.sig.unproto]
        low = fi.rel.lower()
        hints = {"insmenu": ("insectvs",), "insect": ("insectbattle", "insect"),
                 "normal": ("fieldhud", "battleend", "normal"), "factory": ("factory",),
                 "title": ("title",)}

        def score(d):
            s = 0
            for v in views:
                if [p.kind for p in v.params] == [p.kind for p in d.sig.params]:
                    s += 8
                elif [p.cls for p in v.params] == [p.cls for p in d.sig.params]:
                    s += 6
                elif len(v.params) == len(d.sig.params):
                    s += 2
                if v.ret.kind == d.sig.ret.kind:
                    s += 1
            img = self.image_of(d.rel)
            if any(h in low for h in hints.get(img, (img,))) and not (
                    img == "insect" and "insectvs" in low):
                s += 1
            return s
        best = max(cands, key=lambda d: (score(d), -cands.index(d)))
        self.import_pick[key] = best
        self.log.append((fi.rel, 0, name, "overlay-import-site",
                         f"bound to {self.image_of(best.rel)}: {best.proto_text}"))
        self.stats["overlay-import-site"] += 1
        return best

    def resolve(self, fi: FileInfo, name: str) -> Def | None:
        for d in fi.defs:
            if d.name == name:
                return None if d.is_asm else d
        if name in self.import_multi:
            return self._pick_import(fi, name)
        ds = self.defs_by_name.get(name)
        if not ds:
            return None
        img = self.image_of(fi.rel)
        ext = [d for d in ds if not d.static]
        for d in ext:
            if self.image_of(d.rel) == img:
                return d
        return self.gdef.get(name)

    def in_header(self, d: Def) -> bool:
        """Emitted into game_protos.h?"""
        if d.static or not d.clink or d.name in self.hdr_owned or d.name in self.local_names:
            return False
        if d.sig.ret.cls == "x" or any(p.cls == "x" for p in d.sig.params):
            return False
        return self.gdef.get(d.name) is d

    def view(self, fi: FileInfo, c: Call):
        """The declaration the call was compiled against (mwcc view)."""
        best = None
        for d in fi.decls:
            if d.name != c.name or d.start > c.start:
                continue
            if d.func is not None and d.func is not c.func:
                continue
            best = d
        if best is not None:
            return best.sig, best
        for d in fi.defs:
            if d.name == c.name and d.rparen < c.start:
                return d.sig, d
        return None, None

    # -------------------------------------------------------------- planning
    def _log(self, fi, off, callee, rule, detail=""):
        self.log.append((fi.rel, fi.line(off), callee, rule, detail))
        self.stats[rule] += 1

    def sig(self, d: Def) -> Sig:
        """Effective (post-stage) signature of a definition."""
        return self.eff[id(d)]

    def _plan(self):
        # 1. tail-value evidence for void definitions whose value is used
        used_from_void: dict[str, list] = defaultdict(list)   # name -> [(fi, call, viewret)]
        for fi in self.files.values():
            for c in fi.calls:
                d = self.resolve(fi, c.name)
                if d is None or d.sig.ret.cls not in ("v", "g", "f"):
                    continue
                vs, _ = self.view(fi, c)
                vret = vs.ret if vs is not None else T("g", "int", "int")
                if vret.cls not in ("g", "f") or vret.cls == d.sig.ret.cls:
                    continue
                if value_used(fi, c, self._encl_void_raw(fi, c)):
                    used_from_void[c.name].append((fi, c, vret))
        self.tail: dict[int, tuple] = {}    # id(def) -> (Def, tail Call, ret T)
        self.vtail: dict[int, tuple] = {}   # id(def) -> (stmt off, method span, ret T)
        # value definitions that only forward a call's value (pure forwarders)
        fwd = []
        for fi in self.files.values():
            for d in fi.defs:
                if not d.is_asm and d.sig.ret.cls in ("g", "f"):
                    tc = self._tail_return(d)
                    if tc is not None:
                        fwd.append((d, tc))
        changed = True
        while changed:
            changed = False
            for nm in sorted(used_from_void):
                uses = used_from_void[nm]
                d = self.resolve(uses[0][0], nm)
                # a MAIN->overlay import name: the tail evidence is the overlay
                # definition's (MenuTransIsReady_203870 reads func_516A90 =
                # normal_TransMenuResReady_516a90, a bare `j` to the ready poll);
                # the alias takes the definition's tail (aliases loop below)
                if d is not None and id(d) in self.import_src:
                    if os.environ.get("RG_PROTOS_NO_IMPORTTAIL"):
                        continue
                    d = self.import_src[id(d)]
                if d is None or id(d) in self.tail or d.rel not in self.files:
                    continue
                tc = (self._tail_call(d) if d.sig.ret.cls == "v"
                      else self._tail_return(d))
                if tc is None:
                    vt = self._tail_vcall(d, uses) if d.sig.ret.cls == "v" else None
                    if vt is not None:
                        self.tail[id(d)] = (d, None, vt[2])
                        self.vtail[id(d)] = vt
                        changed = True
                        continue
                    lv = (self._v0_listing(d) if d.sig.ret.cls == "v"
                          and not os.environ.get("RG_PROTOS_NO_V0RET") else None)
                    if lv is not None:
                        self.tail[id(d)] = (d, lv[0], lv[1])
                        changed = True
                    continue
                gret = self._tail_target(d, tc)
                if gret is None:
                    continue
                want = Counter(v.cls for _, _, v in uses).most_common(1)[0][0]
                # a VOID definition ending in a tail call returns whatever G
                # left in $v0/$f0 (the epilogue does not touch them): G's type
                # is the truth whatever class the callers read.  A value
                # definition is retyped when its callers read G's class (or
                # below, when it is a pure forwarder).
                if gret.cls != want and d.sig.ret.cls != "v":
                    continue
                self.tail[id(d)] = (d, tc, gret)
                changed = True
            # pure forwarders: `T F(..) { return G(..); }` where F's own view of
            # G returns T (so mwcc emitted a bare tail jump: no conversion) but
            # G is defined in the other register class.  Retail F returns G's
            # $v0/$f0 as G left them: F takes G's type (def-tail-retype).
            for d, tc in fwd:
                if id(d) in self.tail:
                    continue
                gret = self._tail_target(d, tc)
                if gret is None:
                    continue
                vs_, _ = self.view(self.files[d.rel], tc)
                if gret.cls == d.sig.ret.cls:
                    # same GPR class: only an int def forwarding a double
                    # (the whole 64-bit register) is retyped
                    if not (gret.kind == "d" and d.sig.ret.kind == "i" and vs_ is not None
                            and vs_.ret.kind == "i"):
                        continue
                elif vs_ is None or vs_.ret.cls != d.sig.ret.cls:
                    continue
                self.tail[id(d)] = (d, tc, gret)
                changed = True
        self.used_from_void = used_from_void
        self._force_ret: dict[str, set] = defaultdict(set)
        for d, tc, _g in self.tail.values():
            if isinstance(tc, V0Tail):
                for c in tc.calls:
                    self._force_ret[d.rel].add(c.name)
            elif tc is not None:
                self._force_ret[d.rel].add(tc.name)
        self._changed: dict[str, set] = defaultdict(set)
        # 2. effective signatures; widen definitions that pass an incoming
        #    register straight through to an under-argued first call
        self.eff: dict[int, Sig] = {}
        self.added: dict[int, list] = defaultdict(list)
        for fi in self.files.values():
            for d in fi.defs:
                ret = self.tail[id(d)][2] if id(d) in self.tail else d.sig.ret
                params = list(d.sig.params)
                for k in self._sbv_params(fi, d):
                    q = params[k]
                    params[k] = T("g", "void *", q.raw + " *", True, q.name)
                self.eff[id(d)] = Sig(ret, params, d.sig.va, False)
        for d in self.provider.values():
            self.eff[id(d)] = Sig(d.sig.ret, list(d.sig.params), d.sig.va, False)
        aliases = list(self.import_alias.values()) + [
            a for al in self.import_multi.values() for a in al]
        for al in aliases:   # an import alias shares its definition's signature
            src = self.import_src[id(al)]
            self.eff[id(al)] = self.eff[id(src)]
            if id(src) in self.tail:
                self.tail[id(al)] = self.tail[id(src)]
        self._infer_double_carriers()
        self._infer_wide_carriers()
        if not os.environ.get('RG_PROTOS_NO_VCALL'):
            self._vcall_widen()
        self.lanepad = {}
        if not os.environ.get('RG_PROTOS_NO_VSLOT'):
            self._vslot_lanes()
        for _ in range(16):
            changed = False
            for rel in sorted(self.files):
                fi = self.files[rel]
                for c in fi.calls:
                    d = self.resolve(fi, c.name)
                    if d is None or not self._callable(fi, c, d):
                        continue
                    m = self._map(fi, c, d)
                    if m is None:
                        continue
                    newargs, _extra, _acls = m
                    miss = [x for x in newargs if x[0] == "miss"]
                    if not miss:
                        continue
                    clean = self._clean(fi, c)
                    F = self._encl_def(fi, c)
                    if F is None or F.sig.va:
                        continue
                    fs = self.eff[id(F)]
                    for _, p, cls, k, _i in miss:
                        # retail's listing decides when it exists (the C may
                        # call an inline helper first that never touches the
                        # register: SoundStreamSlotAlloc_1bd560); else the
                        # textual "no call before it" rule
                        r = self._asm_arg(fi, c, cls, k)
                        if r == "noasm":
                            if not clean:
                                continue
                        elif r is None or r[0] != "entry":
                            continue      # retail sets the register itself
                        else:
                            # rule A: never widen for a register the callee
                            # does not read (0 is exact).  An FPR needs a proven
                            # read: $f12.. reaching only a varargs save area
                            # (SystemVmCall_250a50 -> Fprintf) is garbage.
                            rd = self._callee_reads(fi, c, d, cls, k)
                            if rd == "no" or (cls == "f" and not rd.startswith("yes")):
                                continue
                        have = [q for q in fs.params if q.cls == cls]
                        while len(have) <= k:
                            last = len(have) == k
                            t = T(cls, p.c if last else ("float" if cls == "f" else "int"),
                                  p.c if last else ("float" if cls == "f" else "int"),
                                  p.ptr if last else False,
                                  f"rgp_{'f' if cls == 'f' else 'a'}{len(have)}")
                            fs.params.append(t)
                            self.added[id(F)].append(t)
                            have.append(t)
                            changed = True
            if not changed:
                break
        # 3. per-file rewrites
        for rel, fi in self.files.items():
            self.out[rel] = self._plan_file(fi)
        # 4. header
        self.header = self._gen_header()

    def _tail_target(self, d: Def, tc):
        """Return type the tail call `tc` of definition `d` leaves in
        $v0/$f0, or None when it is not mechanical."""
        dfi = self.files[d.rel]
        gd = self.resolve(dfi, tc.name)
        if gd is None:
            return None
        if gd.rel != d.rel:
            if not dfi.cpp and not self.in_header(gd) and gd.name not in self.local_names:
                return None
            if dfi.cpp:
                vs_, vsrc_ = self.view(dfi, tc)
                if not isinstance(vsrc_, Decl) or vs_.unproto or \
                        vs_.ret.cls == "x" or "x" in vs_.classes():
                    return None
        src = self.import_src.get(id(gd), gd)
        gret = gd.sig.ret if gd.sig.ret.cls != "v" else (
            self.tail[id(src)][2] if id(src) in self.tail else None)
        if gret is None or gret.cls not in ("g", "f"):
            return None
        return gret

    # ---------------------------------------------- soft-double carriers
    _INT4 = re.compile(r"^(?:const\s+|volatile\s+|register\s+)*(?:s32|u32|int|unsigned int|"
                       r"unsigned|signed int|long|unsigned long|uint|BOOL)$")

    def _infer_double_carriers(self):
        """The EE keeps a soft-double in ONE 64-bit GPR, so the decomp could
        type a variable that only ever carries a double from a double-returning
        call into double parameters as `s32` (mwcc never narrowed the register
        between the calls).  On i686 an int would cut the value to 32 bits.
        A 4-byte integer parameter (`double-param`) or local (`double-local`)
        whose every occurrence is one of
            v = F(..);   with F returning double (whole statement),
            G(.., v, ..) as a whole argument that lands in a double parameter,
            return v;    from a function returning double,
            its own declaration (no initialiser),
        and that has at least one such use, is retyped `double`.  Iterated
        to a fixpoint (a retyped parameter makes the callers' arguments land
        in a double parameter).  Calls whose argument or result is such a
        variable then pass it unconverted (no bit transport)."""
        self.carriers: dict[tuple, set] = defaultdict(set)   # (rel, body_open) -> names
        self.dparams: dict[int, set] = defaultdict(set)      # id(def) -> param indexes
        self.dlocals: dict[str, list] = defaultdict(list)    # rel -> (start, end, text)
        cand_files = []
        dnames = {nm for nm, ds in self.defs_by_name.items()
                  if any(self.eff.get(id(d)) is not None and (
                      self.eff[id(d)].ret.kind == "d" or
                      any(q.kind == "d" for q in self.eff[id(d)].params)) for d in ds)}
        for fi in self.files.values():
            if any(c.name in dnames for c in fi.calls):
                cand_files.append(fi)
        for _ in range(8):
            changed = False
            for fi in cand_files:
                if self._carriers_file(fi):
                    changed = True
            if not changed:
                break
            dnames |= {d.name for fi in cand_files for d in fi.defs if self.dparams.get(id(d))}
            cand_files = [fi for fi in self.files.values()
                          if any(c.name in dnames for c in fi.calls)]

    def _carriers_file(self, fi) -> bool:
        code = fi.code
        argpos = {}
        callat = {}
        for c in fi.calls:
            callat[c.start] = c
            for i, (a, b) in enumerate(c.args):
                argpos[(a, b)] = (c, i)
        changed = False
        for d in fi.defs:
            if d.is_asm or id(d) not in self.eff:
                continue
            key = (fi.rel, d.body_open)
            es = self.eff[id(d)]
            names = {}
            for k, q in enumerate(es.params):
                if q.name and q.kind == "i" and not q.ptr and k not in self.dparams[id(d)] \
                        and self._INT4.match(" ".join(q.raw.split())):
                    names[q.name] = ("param", k)
            for m in re.finditer(r"(?:^|(?<=[;{}]))\s*((?:const\s+|register\s+)*(?:s32|u32|int|unsigned int|"
                                 r"unsigned|long|BOOL))\s+([A-Za-z_]\w*)\s*;",
                                 code[d.body_open:d.body_close]):
                nm = m.group(2)
                if nm not in names and nm not in self.carriers[key]:
                    names[nm] = ("local", d.body_open + m.start(1), d.body_open + m.end(0))
            for nm, kind in names.items():
                if self._is_carrier(fi, d, nm, kind, argpos, callat):
                    changed = True
                    self.carriers[key].add(nm)
                    if kind[0] == "param":
                        k = kind[1]
                        self.dparams[id(d)].add(k)
                        q = es.params[k]
                        es.params[k] = T("g", "double", "double", False, q.name)
                        self._log(fi, d.start, d.name, "double-param",
                                  f"param {k + 1} `{q.raw} {nm}` only carries a soft-double "
                                  f"between double calls: retyped double")
                    else:
                        a, e = kind[1], kind[2]
                        self.dlocals[fi.rel].append((a, e, f"double {nm};"))
                        self._log(fi, a, d.name, "double-local",
                                  f"local `{nm}` only carries a soft-double between double "
                                  f"calls: retyped double")
        return changed

    def _is_carrier(self, fi, d, nm, kind, argpos, callat) -> bool:
        code = fi.code
        key = (fi.rel, d.body_open)
        ev = 0
        for m in re.compile(rf"(?<![\w.>]){re.escape(nm)}\b").finditer(code, d.body_open,
                                                                     d.body_close):
            a, b = m.start(), m.end()
            if kind[0] == "local" and kind[1] <= a < kind[2]:
                continue                                    # its declaration
            # whole argument of a call landing in a double parameter
            hit = argpos.get((a, b))
            if hit is not None:
                c, i = hit
                cd = self.resolve(fi, c.name)
                if cd is None or id(cd) not in self.eff:
                    return False
                mp = self._map(fi, c, cd)
                if mp is None:
                    return False
                k = [j for j, x in enumerate(mp[0]) if x[0] == "arg" and x[1] == i]
                if not k or self.eff[id(cd)].params[k[0]].kind not in ("d", "q"):
                    return False
                ev += 1
                continue
            j = b
            while j < len(code) and code[j] in " \t\r\n":
                j += 1
            h = a - 1
            while h > d.body_open and code[h] in " \t\r\n":
                h -= 1
            # v = F(..);
            if code[j] == "=" and code[j + 1] != "=" and code[h] in ";{}":
                j += 1
                while code[j] in " \t\r\n":
                    j += 1
                c = callat.get(j)
                if c is None:
                    return False
                e = c.rparen + 1
                while code[e] in " \t\r\n":
                    e += 1
                if code[e] != ";":
                    return False
                cd = self.resolve(fi, c.name)
                if cd is None or id(cd) not in self.eff or self.eff[id(cd)].ret.kind != "d":
                    return False
                ev += 1
                continue
            # return v;
            if code[j] == ";" and re.search(r"\breturn$", code[max(0, h - 6):h + 1]):
                if self.eff[id(d)].ret.kind != "d":
                    return False
                ev += 1
                continue
            return False
        return ev > 0

    # ---------------------------------------------- 64-bit values in 4-byte C
    _WLOCAL = re.compile(r"(?:^|(?<=[;{}]))\s*((?:register\s+)?(?:s32|u32|int|unsigned int|"
                         r"unsigned|signed int|long|unsigned long|uint|BOOL))\s+([A-Za-z_]\w*)\s*;")
    _NARROW_CAST = re.compile(r"^\(\s*(?:s32|u32|int|unsigned int|unsigned|signed int|signed|"
                              r"long|unsigned long|uint)\s*\)\s*")

    def _def_key(self, d):
        """'img:name' of a definition's retail listing, or None."""
        img = self.image_of(d.rel) if d.rel.startswith("src/") else "main"
        if self._listing(img, d.name):
            return f"{img}:{d.name}"
        return None

    def _key_def(self, key):
        """The C definition (truth) behind a listing key 'img:name'."""
        img, nm = key.split(":", 1)
        ds = self.defs_by_name.get(nm) or []
        # an external definition first: a file may carry a static (inline) copy
        # under the listing's name (ActCfgTableEvalNormalAttrFlags_221cc0.c's
        # CharaTableDataCollectPrmtFlags_226710)
        ds = sorted(ds, key=lambda d: d.static)
        for d in ds:
            if id(d) in self.eff and (self.image_of(d.rel) if d.rel.startswith("src/")
                                      else "main") == img:
                return d
        return ds[0] if ds and id(ds[0]) in self.eff else None

    @staticmethod
    def _gpr_index(sig, k):
        """Index in sig.params of the k-th GPR parameter, or None."""
        n = 0
        for i, p in enumerate(sig.params):
            if p.cls == "g":
                if n == k:
                    return i
                n += 1
        return None

    def _wide_reads(self, key, k, depth=0, seen=frozenset()):
        """Does the listing `key` read all 64 bits of its k-th GPR argument
        (asmflow.wide_flow: a compare, slt, sd, dsrl.. on it or on a value
        derived through copies / logical / doubleword ops), directly or by
        passing it to a callee that does or whose C parameter is 8 bytes?"""
        ck = (key, k)
        if ck in self._wsens:
            return self._wsens[ck]
        if depth > 4 or ck in seen:
            return None
        fl = self._flow()
        cfg = fl.cfg(key)
        res = None
        if cfg is not None and k < 8:
            ev = asmflow.wide_flow(cfg, {"$%d" % (4 + k): "P"}, None, gen_insn=False)
            sens = sorted(e for e in ev if e[0] == "sens")
            if sens:
                op, ops = cfg.ins[sens[0][1]]
                res = f"{op} {','.join(ops)}"
            else:
                for e in sorted((e for e in ev if e[0] == "arg"), key=lambda e: (e[1], e[3])):
                    if e[2] == "<indirect>":
                        continue
                    sub = fl.resolve(e[2], key)
                    if sub is None:
                        continue
                    kk = int(e[3][1:]) - 4
                    sd = self._key_def(sub)
                    if sd is not None:
                        pi = self._gpr_index(self.eff[id(sd)], kk)
                        if pi is not None and self.eff[id(sd)].params[pi].kind == "q":
                            res = f"passed to {sub.split(':', 1)[1]} (8-byte parameter)"
                            break
                    r = self._wide_reads(sub, kk, depth + 1, seen | {ck})
                    if r:
                        res = f"passed to {sub.split(':', 1)[1]}: {r}"
                        break
        self._wsens[ck] = res
        return res

    def _infer_wide_carriers(self):
        """The EE's registers are 64 bits and mwcc never narrows one for a C
        conversion to a 4-byte integer: `(int)c->flags64` passes the whole `ld`,
        `s32 a = F64()` is a `daddu` move.  When the value then reaches an op
        that reads all 64 bits (a mask compare, slt, sd ..), retail sees the
        high word and the port's C conversion does not
        (ActCfgTableFindCallNameByFlags_2207b0: the 64-bit action-call mask
        against the chara's 64-bit state flags).  From the listings
        (asmflow.wide_flow):
          wide-param  a call passes a 64-bit value (ld / an 8-byte call result /
                      an 8-byte parameter) in the k-th GPR and the callee's
                      listing reads all 64 bits of it: the definition's 4-byte
                      parameter becomes long long (unsigned kept);
          wide-arg    that call's argument, an explicit 4-byte cast in the C, is
                      passed without the cast;
          wide-local  a 4-byte local assigned `v = F(..);` (F returns an 8-byte
                      integer) whose register reaches such an op or a wide-param:
                      retyped to F's return type.
        Iterated (a widened parameter is a 64-bit source in its own body)."""
        self._wsens: dict = {}
        self.wparams: dict[int, dict] = defaultdict(dict)    # id(def) -> {param idx: ctype}
        self.wargs: set = set()                              # (rel, call start, arg idx)
        self.wlocals: dict[str, dict] = defaultdict(dict)    # rel -> {decl start: (end, text)}
        self.wrets: dict[int, str] = {}                      # id(def) -> ctype (wide-ret)
        if os.environ.get("RG_PROTOS_NO_WIDE"):
            return
        fl = self._flow()
        # wide-ret candidates: listing key -> (def, labels of the wide $v0)
        wcand: dict[str, tuple] = {}
        whot: dict[str, str] = {}

        def ret_def(key):
            def gen(tgt):
                if tgt == "<indirect>":
                    return None
                sub = fl.resolve(tgt, key)
                sd = self._key_def(sub) if sub else None
                if sd is not None and self.eff[id(sd)].ret.kind == "q":
                    return "ret"
                if sub in wcand:
                    return "cnd:" + sub      # a 4-byte def returning a wide $v0 (under test)
                return None
            return gen

        def nocand(lab):
            return frozenset(x for x in lab if not x.startswith("cnd:"))

        def cand_of(lab):
            return {x[4:].rsplit("@", 1)[0] for x in lab if x.startswith("cnd:")}
        for _ in range(8):
            changed = False
            if self._wide_inline(fl):
                changed = True
            for rel in sorted(self.files):
                fi = self.files[rel]
                for d in fi.defs:
                    if d.is_asm or id(d) not in self.eff:
                        continue
                    key = self._def_key(d)
                    if key is None:
                        continue
                    calls = [c for c in fi.calls if c.func is not None
                             and c.func.body_open == d.body_open]
                    if not calls:
                        continue
                    es = self.eff[id(d)]
                    seeds = {}
                    for k in range(8):
                        pi = self._gpr_index(es, k)
                        if pi is not None and es.params[pi].kind == "q":
                            seeds["$%d" % (4 + k)] = "Q"
                    cfg = fl.cfg(key)
                    gen = ret_def(key)
                    # each 8-byte call result is labelled by its jal: `ret@j`
                    ev = asmflow.wide_flow(cfg, seeds, gen, gen_insn=True)
                    argev = {}
                    for e in ev:
                        if e[0] == "arg" and nocand(e[4]):
                            argev[(e[1], e[3])] = nocand(e[4])
                    hot = set()          # ret@j labels reaching a 64-bit read / wide param
                    for e in ev:
                        if e[0] == "sens":
                            hot |= {x for x in e[3] if x.startswith("ret@")}
                            for ck in cand_of(e[3]):
                                op_, ops_ = cfg.ins[e[1]]
                                whot.setdefault(ck, f"{d.name}: {op_} {','.join(ops_)}")
                        elif e[0] == "ret" and es.ret.kind == "q":
                            # $v0 of an 8-byte definition: all 64 bits are its value
                            hot |= {x for x in e[2] if x.startswith("ret@")}
                            for ck in cand_of(e[2]):
                                whot.setdefault(ck, f"returned by {d.name} ({es.ret.c})")
                        elif e[0] == "arg" and cand_of(e[4]) and e[2] != "<indirect>":
                            sub = fl.resolve(e[2], key)
                            sd = self._key_def(sub) if sub else None
                            if sd is None or id(sd) not in self.eff:
                                continue
                            kk = int(e[3][1:]) - 4
                            pi = self._gpr_index(self.eff[id(sd)], kk)
                            if pi is None:
                                continue
                            why = ("8-byte parameter" if self.eff[id(sd)].params[pi].kind == "q"
                                   else self._wide_reads(sub, kk))
                            if why:
                                for ck in cand_of(e[4]):
                                    whot.setdefault(ck, f"{d.name}: passed to {sd.name} ({why})")
                    # wide-ret candidate: a 4-byte definition whose $v0 at the
                    # return is an 8-byte call result / an 8-byte parameter
                    if (not d.static and key not in wcand and id(d) not in self.tail
                            and es.ret.kind == "i" and not es.ret.ptr
                            and self._INT4.match(" ".join(es.ret.raw.split()))):
                        src = set()
                        for e in ev:
                            if e[0] == "ret":
                                src |= {x for x in e[2] if x.startswith(("ret@", "Q"))}
                        if src:
                            wcand[key] = (d, src)
                            changed = True
                    for c in calls:
                        cd = self.resolve(fi, c.name)
                        if cd is None or id(cd) not in self.eff or cd.is_asm:
                            continue
                        st = self._site(fi, c)
                        if st is None or len(st[1]) != 1:
                            continue
                        j = st[1][0]
                        cs = self.eff[id(cd)]
                        ckey = self._def_key(cd)
                        m = self._map(fi, c, cd)
                        for k in range(8):
                            lab = argev.get((j, "$%d" % (4 + k)))
                            if not lab:
                                continue
                            pi = self._gpr_index(cs, k)
                            if pi is None:
                                continue
                            p = cs.params[pi]
                            if p.kind == "q" and pi in self.wparams.get(id(cd), {}):
                                hot |= {x for x in lab if x.startswith("ret@")}
                            if p.kind != "i" or p.ptr or not self._INT4.match(" ".join(p.raw.split())):
                                continue
                            why = self._wide_reads(ckey, k) if ckey else None
                            if not why:
                                continue
                            hot |= {x for x in lab if x.startswith("ret@")}
                            ct = "unsigned long long" if "unsigned" in p.c else "long long"
                            self.wparams[id(cd)][pi] = ct
                            cs.params[pi] = T("g", ct, ct, False, p.name)
                            changed = True
                            src = ", ".join(sorted(lab))
                            self._log(self.files.get(cd.rel, fi), cd.start, cd.name, "wide-param",
                                      f"param {pi + 1} `{p.raw} {p.name}` receives a 64-bit value "
                                      f"({c.name} from {d.name}: {src}) and the listing reads all "
                                      f"64 bits ({why}): retyped {ct}")
                            # the caller's argument
                            if m is None or pi >= len(m[0]) or m[0][pi][0] != "arg":
                                continue
                            ai = m[0][pi][1]
                            a0, b0 = c.args[ai]
                            expr = fi.code[a0:b0]
                            if self._NARROW_CAST.match(expr):
                                if (rel, c.start, ai) not in self.wargs:
                                    self.wargs.add((rel, c.start, ai))
                                    self._log(fi, c.start, c.name, "wide-arg",
                                              f"arg {ai + 1} `{' '.join(expr.split())}`: retail "
                                              f"passes the 64-bit register, cast dropped")
                    # locals assigned an 8-byte call result that is hot
                    for c in calls:
                        st = self._site(fi, c)
                        if st is None or len(st[1]) != 1 or f"ret@{st[1][0]}" not in hot:
                            continue
                        cd = self.resolve(fi, c.name)
                        if cd is None or id(cd) not in self.eff:
                            continue
                        rt = self.eff[id(cd)].ret
                        if rt.kind != "q":
                            continue
                        # `v = F(..)`, or an accumulator `v |= F(..)` (also ^=, &=)
                        mm = re.search(r"(?<![\w.>])([A-Za-z_]\w*)\s*[|^&]?=\s*$",
                                       fi.code[max(d.body_open, c.start - 200):c.start])
                        if not mm or fi.code[c.start - len(mm.group(0)) - 1:c.start - len(mm.group(0))] == "=":
                            continue
                        if re.search(r"[=!<>]=\s*$", mm.group(0)) and not re.search(r"[|^&]=\s*$", mm.group(0)):
                            continue
                        nm = mm.group(1)
                        body = fi.code[d.body_open:d.body_close]
                        if re.search(rf"&\s*{re.escape(nm)}\b", body):
                            continue
                        for dm in self._WLOCAL.finditer(body):
                            if dm.group(2) != nm:
                                continue
                            a = d.body_open + dm.start(1)
                            e = d.body_open + dm.end(0)
                            if a in self.wlocals[rel]:
                                break
                            self.wlocals[rel][a] = (e, f"{rt.c} {nm};")
                            changed = True
                            self._log(fi, a, d.name, "wide-local",
                                      f"local `{dm.group(1)} {nm}` = {c.name}(..) (8-byte result) "
                                      f"reaches a 64-bit read in the listing: retyped {rt.c}")
                            break
            # wide-ret: a candidate whose result some caller reads whole
            for ck in sorted(whot):
                if ck not in wcand:
                    continue
                d2, src = wcand[ck]
                if id(d2) in self.wrets:
                    continue
                es2 = self.eff[id(d2)]
                if es2.ret.kind != "i":
                    continue
                ct = "unsigned long long" if "unsigned" in es2.ret.c else "long long"
                self.wrets[id(d2)] = ct
                es2.ret = T("g", ct, ct, False, "")
                changed = True
                self._log(self.files[d2.rel], d2.start, d2.name, "wide-ret",
                          f"returns `{d2.sig.ret.raw}` but retail's $v0 at the return is a 64-bit "
                          f"value ({', '.join(sorted(src))}) and a caller reads all 64 bits "
                          f"({whot[ck]}): retyped {ct}")
            if not changed:
                break

    def _wide_inline(self, fl) -> bool:
        """Listing-less static helpers (mwcc inlined them; retail kept the
        caller's 64-bit register, a C conversion to a 4-byte parameter does not
        narrow it):
          wide-inline-param  a call passes an 8-byte integer parameter of the
                             caller, by name, to a helper's 4-byte parameter:
                             retyped to an 8-byte integer;
          wide-param (helper) inside such a helper, that parameter passed by
                             name to a listed definition whose listing reads all
                             64 bits of it: that definition's parameter widened.
        -> True if anything changed."""
        WID = re.compile(r"^\(*\s*(?:\(\s*(?:long long|signed long long|unsigned long long|s64|u64)"
                         r"\s*\)\s*)?\(*\s*([A-Za-z_]\w*)\s*\)*$")
        changed = False
        for rel in sorted(self.files):
            fi = self.files[rel]
            for d in fi.defs:
                if d.is_asm or id(d) not in self.eff or d.body_close <= d.body_open:
                    continue
                es = self.eff[id(d)]
                qn = {p.name for p in es.params if p.kind == "q" and p.name}
                if not qn:
                    continue
                own_listing = self._def_key(d) is not None
                for c in fi.calls:
                    if c.func is None or c.func.body_open != d.body_open:
                        continue
                    h = self.resolve(fi, c.name)
                    if h is None or h.is_asm or id(h) not in self.eff or h is d:
                        continue
                    hs = self.eff[id(h)]
                    if hs.va or len(c.args) != len(hs.params):
                        continue
                    helper = (h.static and h.rel == rel and self._def_key(h) is None
                              and h.body_close > h.body_open)
                    hkey = None if helper else self._def_key(h)
                    if not helper and (own_listing or hkey is None):
                        continue      # listed callers: the site-based rules decide
                    for i, (a0, b0) in enumerate(c.args):
                        m = WID.match(fi.code[a0:b0].strip())
                        if not m or m.group(1) not in qn:
                            continue
                        p = hs.params[i]
                        if p.kind != "i" or p.ptr or not self._INT4.match(" ".join(p.raw.split())):
                            continue
                        if i in self.wparams.get(id(h), {}):
                            continue
                        ct = "unsigned long long" if "unsigned" in p.c else "long long"
                        if helper:
                            why = f"{d.name} passes its 8-byte `{m.group(1)}`; {h.name} is inlined"
                            rule = "wide-inline-param"
                        else:
                            k = sum(1 for q in hs.params[:i] if q.cls == "g")
                            why = self._wide_reads(hkey, k)
                            if not why:
                                continue
                            why = (f"inlined helper {d.name} passes its 8-byte `{m.group(1)}` "
                                   f"and the listing reads all 64 bits ({why})")
                            rule = "wide-param"
                        self.wparams[id(h)][i] = ct
                        hs.params[i] = T("g", ct, ct, False, p.name)
                        changed = True
                        self._log(self.files.get(h.rel, fi), h.start, h.name, rule,
                                  f"param {i + 1} `{p.raw} {p.name}`: {why}: retyped {ct}")
        return changed

    def _encl_def(self, fi, c):
        f = c.func
        if f is None:
            return None
        for d in fi.defs:
            if d.body_open == f.body_open:
                return d
        return None

    def _encl_void_raw(self, fi, c) -> bool:
        d = self._encl_def(fi, c)
        return d is not None and d.sig.ret.cls == "v"

    def _encl_void(self, fi, c) -> bool:
        d = self._encl_def(fi, c)
        return d is not None and self.sig(d).ret.cls == "v"

    def _clean(self, fi, c) -> bool:
        """No other call is evaluated before `c` in its function, so the
        argument registers still hold the function's incoming values."""
        f = c.func
        if f is None:
            return False
        code = fi.code
        for m in ANYCALL.finditer(code, f.body_open, c.rparen):
            s = m.start(1)
            if s == c.start or m.group(1) in NOT_CALL:
                continue
            if s < c.start:
                rp = match_paren(code, m.end() - 1)
                if rp >= c.rparen:
                    continue          # an outer call: evaluated after c
            return False
        return True

    def _passthrough(self, fi, c, cls, k):
        """Name of the enclosing function's k-th incoming `cls` parameter if it
        is provably still in its register at call `c`, else None.  When
        retail's listing is available it decides (SaveCardHasFreeSpace_37b8c0
        loads $a0 itself before `jal SaveCalcSizeKB_3735e0`)."""
        r = self._asm_arg(fi, c, cls, k)
        if r != "noasm" and (r is None or r[0] != "entry"):
            return None
        if r == "noasm" and not self._clean(fi, c):
            return None
        F = self._encl_def(fi, c)
        if F is None:
            return None
        have = [q for q in self.sig(F).params if q.cls == cls]
        if len(have) <= k or not have[k].name:
            return None
        nm = have[k].name
        pre = fi.code[F.body_open:c.start]
        if re.search(rf"(?<![\w.>])(?:&\s*{nm}\b(?!\s*(?:->|\.|\[))|{nm}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|"
                     rf"{nm}\s*(?:\+\+|--)|(?:\+\+|--)\s*{nm}\b)", pre):
            return None
        return nm

    def _missing_asm(self, fi, c, cls, k):
        """MISSING_ARG_ASM's expression for this missing argument, or None."""
        if cls != "g" or c.func is None:
            return None
        nth = sum(1 for x in fi.calls if x.name == c.name and x.func is not None
                  and x.func.body_open == c.func.body_open and x.start < c.start)
        return MISSING_ARG_ASM.get((fi.rel, c.name, nth), {}).get(k)

    def _entry_value(self, fi, c, cls, k):
        """A missing argument whose register, in RETAIL's code, still holds the
        enclosing function's incoming value although the C body modified the
        parameter first (DataTableCmdEntryDefine_40f6e0: `arg` advanced in
        $s1 before `jal VariantGetInt_15f780`, $a0 untouched).  The snapshot's
        asm/matchings listing decides: no instruction from the function's
        entry to the jal's delay slot writes the register and no other call
        precedes it.  -> the name of an entry copy of the parameter
        (`rgp_entry_<p>`, declared at the top of the body by the caller of
        this stage), or None.  FPR lanes too ($f12..: EventCastSetScale_257fb0)."""
        if k >= 8:
            return None
        F = self._encl_def(fi, c)
        if F is None:
            return None
        have = [q for q in self.sig(F).params if q.cls == cls]
        if len(have) <= k or not have[k].name:
            return None
        r = self._asm_arg(fi, c, cls, k)
        if r == "noasm" or r is None or r[0] != "entry":
            return None
        nm = have[k].name
        self.entry_copies.setdefault(id(F), {})[nm] = F
        return "rgp_entry_" + nm

    # ---------------------------------------------------- retail listings
    # docs/PROTOS-MISSING-ARGS.md rules A-G.  Listings are keyed "img:name"
    # (MAIN and each overlay: the overlays reuse one address range).
    def _listing_text(self, img, fn):
        tab = self.addr_table or {}
        if img == "main":
            text = (tab.get("asm_text") or {}).get(fn)
            path = (tab.get("asm_paths") or {}).get(fn)
            if text is None and path:
                import subprocess
                r = subprocess.run(["git", "-C", str(tab["repo"]), "show",
                                    f"{tab['rev']}:{path}"], capture_output=True, text=True,
                                   encoding="utf-8", errors="replace")
                text = r.stdout
            return text
        return ((tab.get("ovl_text") or {}).get(img) or {}).get(fn)

    def _listing(self, img, fn):
        """asmflow.parse_listing of img's listing of fn (insns, vram) or None."""
        key = (img, fn)
        if key not in self._asm_cache:
            text = self._listing_text(img, fn)
            self._asm_cache[key] = asmflow.parse_listing(text) if text else None
        return self._asm_cache[key]

    def _asm_insns(self, fn, img="main"):
        r = self._listing(img, fn)
        return r[0] if r else None

    def _addr_index(self, img):
        """{vram: listing name} of an image's listings."""
        if not hasattr(self, "_addr_idx"):
            self._addr_idx = {}
        if img not in self._addr_idx:
            tab = self.addr_table or {}
            names = (list((tab.get("asm_text") or {})) + list((tab.get("asm_paths") or {}))
                     if img == "main" else list(((tab.get("ovl_text") or {}).get(img) or {})))
            idx = {}
            for nm in names:
                if img == "main":
                    a = (tab.get("by_name") or {}).get(nm)
                    if a is None:
                        r = self._listing(img, nm)
                        a = r[1] if r else None
                else:
                    r = self._listing(img, nm)
                    a = r[1] if r else None
                if a is not None:
                    idx.setdefault(a, nm)
            self._addr_idx[img] = idx
        return self._addr_idx[img]

    def _name_addr(self, name, img="main"):
        """Address a function name stands for (MAIN symbol table, address-
        style names, interior entries `_e<k>`, `<..>_xxxxxx` suffixes)."""
        if not hasattr(self, "_na_cache"):
            self._na_cache = {}
        k = (name, img)
        if k not in self._na_cache:
            self._na_cache[k] = self._name_addr_raw(name, img)
        return self._na_cache[k]

    def _name_addr_raw(self, name, img="main"):
        tab = self.addr_table or {}
        m = re.search(r"_([0-9A-Fa-f]{6,8})_e(\d+)$", name)
        if m:
            if not hasattr(self, "_entry_rev"):
                self._entry_rev = {}
                for a, (cont, k, *rest) in (tab.get("entries") or {}).items():
                    ca = rest[0] if rest and rest[0] is not None else (
                        (tab.get("by_name") or {}).get(cont))
                    if ca is not None:
                        self._entry_rev[(ca, k)] = a
            return self._entry_rev.get((int(m.group(1), 16), int(m.group(2))))
        a = (tab.get("by_name") or {}).get(name)
        if a is not None:
            return a
        m = re.fullmatch(r"(?:\w+_)?(?:func|FUN)_([0-9A-Fa-f]{6,8})", name)
        if m:
            return int(m.group(1), 16)
        if img != "main":
            r = self._listing(img, name)
            if r and r[1] is not None:
                return r[1]
        m = re.search(r"_([0-9a-f]{6})$", name)
        if m:
            return int(m.group(1), 16)
        return None

    def _fn_at(self, addr, img):
        """Listing name of the function at addr, seen from image img."""
        if addr is None:
            return None
        if addr < OVL_BASE or img == "main":
            return ("main", self._addr_index("main").get(addr)) if addr < OVL_BASE else None
        nm = self._addr_index(img).get(addr)
        return (img, nm) if nm else None

    def _flow(self):
        if getattr(self, "_flow_obj", None) is None:
            def listing(key):
                img, fn = key.split(":", 1)
                return self._asm_insns(fn, img)

            def resolve(tgt, frm):
                img = frm.split(":", 1)[0]
                a = self._name_addr(tgt, img)
                r = self._fn_at(a, img)
                if r and r[1]:
                    return f"{r[0]}:{r[1]}"
                # an interior entry (sceVu0RotMatrixZ's second entry func_0010ACB8):
                # its owner's listing from the entry on (asmflow "name@OFF")
                e = ((self.addr_table or {}).get("entries") or {}).get(a) if a is not None else None
                if e and img == "main" or (e and a < OVL_BASE):
                    r = self._fn_at(e[2], "main")
                    if r and r[1]:
                        return f"main:{r[1]}@{a - e[2]}"
                return None
            self._flow_obj = asmflow.Flow(listing, resolve)
        return self._flow_obj

    def _site(self, fi, c):
        """(cfg, [insn indices of the jal/j that IS call c]) in retail's
        listing of the enclosing function, or None.  Calls are paired with
        jals by order among the calls to the same ADDRESS (overlay listings
        name MAIN targets func_XXXXXX; the C may use either spelling)."""
        if c.func is None:
            return None
        key = (fi.rel, c.start)
        if key in self._site_cache:
            return self._site_cache[key]
        res = None
        F = self._encl_def(fi, c)
        img = self.image_of(fi.rel)
        r = self._listing(img, F.name) if F is not None else None
        if r:
            if not hasattr(self, "_renamed_from"):
                self._renamed_from = defaultdict(set)
                for o, n in getattr(self, "renamed", {}).items():
                    self._renamed_from[n].add(o)
            ca = self._name_addr(c.name, img)
            names = {c.name} | self._renamed_from.get(c.name, set())

            def same_target(nm, tgt_is_listing):
                if nm in names:
                    return True
                a = self._name_addr(nm, img)
                return ca is not None and a == ca
            cfg = self._cfg_cache.get((img, F.name))
            if cfg is None:
                cfg = self._cfg_cache[(img, F.name)] = asmflow.CFG(r[0])
            same = [x for x in fi.calls if x.func is not None
                    and x.func.body_open == F.body_open
                    and (x.name == c.name or (ca is not None
                                              and self._name_addr(x.name, img) == ca))]
            if not hasattr(cfg, "_calls_cache"):
                cfg._calls_cache = cfg.calls()
            jals = [i for i, op, tgt in cfg._calls_cache if same_target(tgt, True)]
            if jals:
                if len(jals) == len(same):
                    res = (cfg, [jals[sum(1 for x in same if x.start < c.start)]])
                else:
                    res = (cfg, jals)
        self._site_cache[key] = res
        return res

    def _asm_term(self, fi, c, cls, k):
        """What retail holds in the k-th `cls` argument register when call c
        transfers control: an asmflow.Term, or 'noasm' (no listing / the call
        cannot be paired with its jal / the paired jals disagree)."""
        if k >= 8 or c.func is None:
            return "noasm"
        key = (fi.rel, c.start, cls, k)
        if key in self._asm_arg_cache:
            return self._asm_arg_cache[key]
        res = "noasm"
        st = self._site(fi, c)
        if st is not None:
            cfg, js = st
            reg = asmflow.arg_reg(cls, k)
            ts = [asmflow.value_at_call(cfg, j, reg) for j in js]
            if all(asmflow.has_clobber(t) for t in ts) or len(set(ts)) == 1:
                res = ts[0]
        self._asm_arg_cache[key] = res
        return res

    def _asm_arg(self, fi, c, cls, k):
        """'noasm', ('entry', None) when the register still holds the
        enclosing function's incoming value, else None (retail sets it)."""
        t = self._asm_term(fi, c, cls, k)
        if t == "noasm":
            return "noasm"
        if t.kind == "entry" and t.a == asmflow.arg_reg(cls, k):
            return ("entry", None)
        return None

    def _callee_reads(self, fi, c, d, cls, k):
        """Rule A: does the callee's retail listing read the argument register
        before writing it (following jal / tail j)?  'yes:..', 'no',
        'maybe:..' (varargs/RPC save area, jalr) or 'unknown:..'."""
        img = self.image_of(fi.rel)
        dimg = self.image_of(d.rel) if d.rel.startswith("src/") else "main"
        cand = []
        if d.name:
            cand.append((dimg, d.name))
        r = self._fn_at(self._name_addr(c.name, img), img)
        if r and r[1]:
            cand.append(r)
        for ci, cn in cand:
            if self._listing(ci, cn):
                return self._flow().reads(f"{ci}:{cn}", asmflow.arg_reg(cls, k))
        return "unknown:no listing for " + c.name

    def _def_reads_reg(self, d, reg):
        """Does definition d's retail listing read reg on entry ('yes..', 'no', 'maybe..',
        'unknown..')?  For a definition with no listing: 'unknown'."""
        if d is None or not d.name:
            return "unknown:no definition"
        img = self.image_of(d.rel) if d.rel.startswith("src/") else "main"
        if not self._listing(img, d.name):
            return "unknown:no listing for " + d.name
        return self._flow().reads(f"{img}:{d.name}", reg)

    # --------------------------------------------- rule E: spell a value
    _CAST = re.compile(r"^\(\s*(?:const\s+|volatile\s+|struct\s+|unsigned\s+|signed\s+)*"
                       r"[A-Za-z_]\w*(?:\s+\w+)*\s*\**\s*\)\s*")

    @classmethod
    def _norm(cls, e: str) -> str:
        e = " ".join(e.split())
        while True:
            e0 = e
            if e.startswith("(") and match_paren(e, 0) == len(e) - 1:
                e = e[1:-1].strip()
            m = cls._CAST.match(e)
            if m and m.end() < len(e) and not re.match(r"[-+*/%&|^<>=?]", e[m.end():].lstrip()):
                e = e[m.end():].strip()
            if e == e0:
                return e.replace(" ", "")

    def _assigns(self, fi, c):
        """{local: rhs} of the last plain assignment `L = rhs;` to each name
        before call c in its function, for names not modified again between
        that assignment and the call."""
        f = c.func
        code = fi.code
        out = {}
        for m in re.finditer(r"(?<![\w.>\]])([A-Za-z_]\w*)\s*=(?!=)\s*([^;{}]+);", code[f.body_open:c.start]):
            out[m.group(1)] = (m.group(2), f.body_open + m.end())
        res = {}
        for nm, (rhs, end) in out.items():
            between = _strip_lhs(code[end:c.start])
            if re.search(rf"(?<![\w.>])(?:&\s*{nm}\b(?!\s*(?:->|\.|\[))|{nm}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|"
                         rf"{nm}\s*(?:\+\+|--)|(?:\+\+|--)\s*{nm}\b)", between):
                continue
            res[nm] = self._norm(rhs)
        return res

    def _local_for(self, fi, c, forms):
        """A C local the function assigned one of `forms` (normalized) to."""
        if not forms:
            return None
        for nm, rhs in self._assigns(fi, c).items():
            if rhs in forms and not nm.startswith("rgp_"):
                return nm
        return None

    def _sym_name(self, fi, addr):
        """A symbol at addr that the file declares."""
        tab = self.addr_table or {}
        cands = ["D_%08X" % addr]
        if (tab.get("main") or {}).get(addr):
            cands.append(tab["main"][addr])
        for n in cands:
            if re.search(rf"\b{re.escape(n)}\b", fi.code):
                return n
        return None

    def _is_array(self, fi, name):
        return bool(re.search(rf"\b{re.escape(name)}\s*\[", fi.code))

    _LOAD_T = {"lw": "int", "lwu": "unsigned int", "lh": "short", "lhu": "unsigned short",
               "lb": "signed char", "lbu": "unsigned char", "lwc1": "float"}

    def _call_var(self, fi, c, j, cfg):
        """The C variable assigned from the call that retail's jal at insn j
        is (`v = G(..);`), or None."""
        F = self._encl_def(fi, c)
        img = self.image_of(fi.rel)
        tgt = cfg.ins[j][1][-1] if cfg.ins[j][1] else None
        if tgt is None:
            return None, None
        ta = self._name_addr(tgt, img)
        calls = [x for x in fi.calls if x.func is not None and x.func.body_open == F.body_open
                 and (x.name == tgt or (ta is not None and self._name_addr(x.name, img) == ta))]
        jals = [i for i, op, t in cfg.calls() if op == "jal" and (
            t == tgt or (ta is not None and self._name_addr(t, img) == ta))]
        if len(calls) != len(jals) or j not in jals:
            return None, None
        g = calls[jals.index(j)]
        pre = fi.code[F.body_open:g.start]
        m = re.search(r"(?<![\w.>\]])([A-Za-z_]\w*)\s*=(?!=)\s*(?:\([^()]*\)\s*)*$", pre)
        if not m:
            return None, g
        nm = m.group(1)
        between = _strip_lhs(fi.code[g.rparen + 1:c.start])
        if re.search(rf"(?<![\w.>])(?:{nm}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|{nm}\s*(?:\+\+|--)|"
                     rf"(?:\+\+|--)\s*{nm}\b|&\s*{nm}\b(?!\s*(?:->|\.|\[)))", between):
            return None, g
        return nm, g

    def _param_ref(self, fi, c, reg):
        """C spelling of the enclosing function's incoming value of reg:
        the parameter if unmodified before c, else an entry copy."""
        F = self._encl_def(fi, c)
        if F is None:
            return None, None
        cls = "f" if reg.startswith("$f") else "g"
        k = int(reg[2:]) - 12 if cls == "f" else int(reg[1:]) - 4
        have = [q for q in self.sig(F).params if q.cls == cls]
        if len(have) <= k or not have[k].name:
            return None, None
        nm = have[k].name
        pre = fi.code[F.body_open:c.start]
        if re.search(rf"(?<![\w.>])(?:&\s*{nm}\b(?!\s*(?:->|\.|\[))|{nm}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|"
                     rf"{nm}\s*(?:\+\+|--)|(?:\+\+|--)\s*{nm}\b)", pre):
            self.entry_copies.setdefault(id(F), {})[nm] = F
            return "rgp_entry_" + nm, nm
        return nm, nm

    def _spell(self, fi, c, t):
        """Rule E: a C expression for retail's value t at call c, preferring
        an existing C local assigned the same value.  -> (expr, how) or None."""
        gp = (self.addr_table or {}).get("gp")
        k = t.kind
        if k == "const":
            return str(t.a), "constant"
        if k == "gpaddr" and gp is not None:
            t = asmflow.Term("addr", (gp + t.a) & 0xFFFFFFFF)
            k = "addr"
        if k in ("sym", "addr"):
            nm = t.a if k == "sym" else self._sym_name(fi, t.a)
            off = t.b if k == "sym" else 0
            if nm is None or not re.search(rf"\b{re.escape(nm)}\b", fi.code):
                return None
            forms = {f"&{nm}"} | ({nm} if self._is_array(fi, nm) else set())
            if off:
                forms = {f"{x}+{off:#x}" for x in forms} | {f"{x}+{off}" for x in forms}
            loc = self._local_for(fi, c, forms)
            if loc:
                return loc, f"local {loc} = &{nm}"
            return (f"((char *)&{nm} + {off:#x})" if off else f"((void *)&{nm})"), f"&{nm}"
        if k == "load":
            op, base, off = t.a, t.b, t.c
            ty = self._LOAD_T.get(op)
            if ty is None:
                return None
            if base.kind == "gpaddr" and gp is not None:
                base = asmflow.Term("addr", (gp + base.a) & 0xFFFFFFFF)
            if base.kind in ("sym", "addr") and not off:
                nm = base.a if base.kind == "sym" else self._sym_name(fi, base.a)
                boff = base.b if base.kind == "sym" else 0
                if nm is None or boff:
                    return None
                if not self._is_array(fi, nm):
                    loc = self._local_for(fi, c, {nm})
                    if loc:
                        return loc, f"local {loc} = {nm}"
                return f"(*({ty} *)&{nm})", f"{op} {nm}"
            if base.kind == "entry":
                pnm, orig = self._param_ref(fi, c, base.a)
                if pnm is None:
                    return None
                if orig == pnm:
                    hx = f"{off:X}"
                    forms = {f"{orig}->{p}{hx}" for p in ("f", "f0", "f00", "unk", "_", "field")}
                    forms |= {f"{orig}->{p}{hx.lower()}" for p in ("f", "f0", "f00", "unk", "_")}
                    loc = self._local_for(fi, c, forms)
                    if loc:
                        return loc, f"local {loc} = {orig}->f{hx}"
                return f"(*({ty} *)((char *){pnm} + {off:#x}))", f"{op} {off:#x}({base.a} entry)"
            return None
        if k == "ret":
            st = self._site(fi, c)
            var, _g = self._call_var(fi, c, t.a, st[0]) if st else (None, None)
            if var:
                return var, f"{var} = {t.b}(..)"
            return None
        if k == "add" and t.a.kind == "entry" and isinstance(t.b, int):
            pnm, orig = self._param_ref(fi, c, t.a.a)
            if pnm is None:
                return None
            v = t.b
            if orig == pnm:
                forms = ({f"{orig}+{v:#x}", f"{orig}+{v}"} if v > 0
                         else {f"{orig}-{-v:#x}", f"{orig}-{-v}"})
                loc = self._local_for(fi, c, forms)
                if loc:
                    return loc, f"local {loc} = {orig} {v:+#x}"
            return (f"((__typeof__({pnm}))((unsigned)({pnm}) + {v:#x}))",
                    f"{t.a.a} entry {v:+#x}")
        if k == "add" and t.a.kind == "ret":
            st = self._site(fi, c)
            var, _g = self._call_var(fi, c, t.a.a, st[0]) if st else (None, None)
            if not var:
                return None
            v = t.b
            forms = {f"{var}+{v:#x}", f"{var}+{v}", f"{var}+{v:#X}".replace("0X", "0x")} if v > 0 \
                else {f"{var}-{-v:#x}", f"{var}-{-v}"}
            loc = self._local_for(fi, c, forms)
            if loc:
                return loc, f"local {loc} = {var} {v:+#x}"
            return f"((__typeof__({var}))((unsigned)({var}) + {v:#x}))", f"{var} {v:+#x}"
        return None

    def _vthunk(self, d):
        """(vptr offset, slot offset) when d's retail listing is exactly the
        virtual tail jump `lw $25,V($4); lw $25,S($25); jr $25` (+ nop): a
        forwarder that passes every argument register and the callee's
        return value through untouched (DataTableCompareThunk_418960 ->
        slot 0x88 DataTableCompareById_4188f0, the bubble sort's compare).
        The C spells these as `void F(T *o) { o->vN(); }`, which drops the
        arguments and the result on the port."""
        if d.is_asm:
            return None
        img = self.image_of(d.rel)
        r = self._listing(img, d.name)
        if not r:
            # an interior entry `<container>_e<k>` / `func_<start>_e<k>`: the
            # k-th `alabel` of the container's listing
            m = re.fullmatch(r"(.+)_e(\d+)", d.name)
            a = self._name_addr(d.name, img) if m else None
            if a is None:
                return None
            cont = self._fn_at(self._name_addr(m.group(1), img), img)
            text = self._listing_text(*cont) if cont and cont[1] else None
            if not text:
                return None
            mm = re.search(r"^\s*alabel\s+func_%08X\s*$" % a, text, re.M | re.I)
            if mm:
                r = asmflow.parse_listing(text[mm.end():])
            else:
                # an entry with no label (data2c function_entries: a vtable
                # word into a run of jr stubs): start at its instruction line
                mm = re.search(r"^[ \t]*/\*\s*[0-9A-Fa-f]+\s+%08X\s" % a, text, re.M | re.I)
                if not mm:
                    return None
                r = asmflow.parse_listing(text[mm.start():])
        ins = [x for x in r[0] if x[0] != ".label"]
        # what follows the jump's (nop) delay slot is not reachable from the
        # entry (another `alabel` entry of the same listing, or padding)
        if len(ins) < 3 or (len(ins) > 3 and ins[3][0] != "nop"):
            return None
        (o1, a1), (o2, a2), (o3, a3) = ins[:3]
        m1 = re.fullmatch(r"(0x[0-9A-Fa-f]+|\d+)\(\$4\)", a1[1]) if o1 == "lw" and len(a1) == 2             and a1[0] == "$25" else None
        m2 = re.fullmatch(r"(0x[0-9A-Fa-f]+|\d+)\(\$25\)", a2[1]) if o2 == "lw" and len(a2) == 2             and a2[0] == "$25" else None
        if not (m1 and m2 and o3 == "jr" and a3 == ["$25"]):
            return None
        return int(m1.group(1), 0), int(m2.group(1), 0)

    def _sbv_params(self, fi, d):
        """Indices of d's struct-by-value parameters that retail passes BY
        ADDRESS: mwcc's EE code gives an aggregate larger than a register to
        the callee as a pointer (GameSessionInit_1f5d80 copies its 0x70-byte
        Cfg from $a0; MainLoop_1c2c10 passes &D_004A3EF0).  Decided from the
        definition's listing: every first read of the parameter's register is
        the base of a load.  Small aggregates (8-byte handles) travel in the
        register itself and are left alone."""
        key = id(d)
        if key in self._sbv_cache:
            return self._sbv_cache[key]
        out = []
        if not d.is_asm and any(q.cls == "x" for q in d.sig.params):
            r = self._listing(self.image_of(d.rel), d.name)
            cfg = asmflow.CFG(r[0]) if r else None
            lane = 0
            for k, q in enumerate(d.sig.params):
                if q.cls == "x" and cfg is not None and lane < 8 and q.name                         and not re.search(r"\b(u128|s128|__int128)\b", q.raw):
                    if asmflow.first_uses_are_loads(cfg, asmflow.arg_reg("g", lane)):
                        out.append(k)
                if q.cls != "f":
                    lane += 1
        self._sbv_cache[key] = out
        return out

    def _missing_value(self, fi, c, d, cls, k):
        """Rules A, B, E for a missing argument that neither passthrough nor
        an entry copy filled.  -> (rule, expr or None, detail)."""
        t = self._asm_term(fi, c, cls, k)
        if t == "noasm":
            return "missing-zero", None, "no retail listing / call not paired with its jal"
        reg = asmflow.arg_reg(cls, k)
        rd = self._callee_reads(fi, c, d, cls, k)
        if rd == "no":
            return "missing-unused", None, f"{reg}: callee never reads it (retail {t})"
        if asmflow.has_clobber(t):
            return "missing-dead", None, f"{reg} = {t}: a dead caller-saved register"
        sp = self._spell(fi, c, t)
        if sp is not None:
            return "missing-asm", sp[0], f"{reg} = {t} -> {sp[0]} ({sp[1]})"
        if rd.startswith(("maybe", "unknown")) and t.kind != "entry":
            return "manual-missing", None, f"{reg} = {t}; callee {rd}"
        return "manual-missing", None, f"{reg} = {t}; callee {rd}"

    def _callable(self, fi, c, d) -> bool:
        """Will the call be compiled against the definition's shape?"""
        if d.rel == fi.rel:
            return True
        if not fi.cpp and d.name not in self.local_names:
            return (self.in_header(d) and not self._xview(fi, c)
                    and c.name not in fi.objdecls)
        vs, vsrc = self.view(fi, c)
        return isinstance(vsrc, Decl) and self._patchable(d)

    def _patchable(self, d: Def) -> bool:
        s = self.sig(d)
        return s.ret.cls != "x" and not any(p.cls == "x" for p in s.params)

    def _xview(self, fi, c) -> bool:
        """The caller's view passes or returns a struct/128-bit by value
        (struct returns use a hidden pointer on the EE): not mechanical."""
        vs, _ = self.view(fi, c)
        return "x" in self._acls(fi, c) or (vs is not None and vs.ret.cls == "x")

    def _acls(self, fi, c):
        vs, _ = self.view(fi, c)
        nargs = len(c.args)
        if vs is not None and not vs.unproto:
            return vs.classes()[:nargs] + ["g?"] * max(0, nargs - len(vs.params))
        return ["g?"] * nargs

    def _map(self, fi, c, d):
        """Remap the call's arguments onto the definition by EABI register
        class.  -> (newargs, extra, acls) or None (not mechanical)."""
        dsig = self.sig(d)
        if dsig.va or dsig.ret.cls == "x" or any(p.cls == "x" for p in dsig.params):
            return None
        acls = self._acls(fi, c)
        if any(a == "x" for a in acls):
            return None
        ph = self._reg_placeholders(fi, c)
        qs = {"g": [], "f": []}
        for i, a in enumerate(acls):
            qs["f" if a == "f" else "g"].append(i)   # promoted float = double = GPR
        newargs, seen = [], {"g": 0, "f": 0}
        for p in dsig.params:
            lst = qs[p.cls]
            k = seen[p.cls]
            seen[p.cls] += 1
            if lst and lst[0] in ph:
                # the register itself: a missing argument (index kept: a C++
                # view's slot type for the fill's cast)
                newargs.append(("miss", p, p.cls, k, lst.pop(0)))
            elif lst:
                newargs.append(("arg", lst.pop(0)))
            else:
                newargs.append(("miss", p, p.cls, k, None))
        return newargs, sorted(qs["g"] + qs["f"] + [i for i in ph if i < len(acls)
                                                     and i not in qs["g"] + qs["f"]]), acls

    def _reg_placeholders(self, fi, c):
        """Call arguments that are m2c's spelling of a register the
        function never set: an uninitialised local `u_<n>` that is never
        assigned (DataTableCmdAllocSubEntries_422f40's `VariantGetInt_15f780(u_0)`
        is retail's `jal` with the incoming $a0 untouched).  They are treated
        as MISSING arguments (passthrough / def-widen / missing-entry) and the
        placeholder is dropped.  -> [arg indices]"""
        key = (fi.rel, c.start)
        if key not in self._ph_cache:
            self._ph_cache[key] = self._reg_placeholders1(fi, c)
        return self._ph_cache[key]

    def _reg_placeholders1(self, fi, c):
        out = []
        f = c.func
        if f is None:
            return out
        body = fi.code[f.body_open:f.body_close]
        acls = None
        for i in range(len(c.args)):
            a, b = c.args[i]
            nm = fi.code[a:b].strip()
            if not re.fullmatch(r"[A-Za-z_]\w*", nm):
                continue
            m2c = re.fullmatch(r"u(?:_?\d+)?", nm) is not None
            # `T u;` or `T *u;` (NodeObjBasicDrawModel_196b10's `void *u` is
            # retail's untouched $a0 = arg0)
            dm = re.search(rf"\b(\w+)(\s*\*+\s*|\s+){nm}\s*(\[[^\]]*\]\s*)?;", body)
            if not dm or dm.group(1) in KEYWORDS:
                continue
            # an array or aggregate local is a real buffer whose ADDRESS is
            # passed (DynClothSubstep_1697c0's `VEC u;`, VEC = f32[4]: retail
            # `addiu $4,$sp,0xB0`), not an unset register
            if dm.group(3) or ("*" not in dm.group(2)
                                and resolve_type(dm.group(1), fi.tdefs).cls == "x"):
                continue
            if re.search(rf"(?<![\w.>])(?:&\s*{nm}\b|{nm}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|"
                         rf"{nm}\s*(?:\+\+|--)|(?:\+\+|--)\s*{nm}\b)", body):
                continue
            if not m2c:
                # any other never-assigned scalar local: only when retail's
                # listing proves the register still holds the caller's
                # incoming value (SoundStreamSlotOpenLoop_1bce80 passes an
                # unset `x` where retail leaves $a1 = the stream name)
                if acls is None:
                    acls = self._acls(fi, c)
                if i >= len(acls) or acls[i] not in ("g", "f", "g?"):
                    continue
                cl = "f" if acls[i] == "f" else "g"
                lane = sum(1 for q in acls[:i] if ("f" if q == "f" else "g") == cl)
                r = self._asm_arg(fi, c, cl, lane)
                if r == "noasm" or r is None:
                    continue
            out.append(i)
        return out

    def _tail_return(self, d: Def):
        """`T F(..) { ..; return G(..); }` with that as the only return: F
        returns whatever G left in $v0/$f0."""
        fi = self.files[d.rel]
        body = fi.code[d.body_open + 1:d.body_close]
        rets = list(re.finditer(r"\breturn\b", body))
        if len(rets) != 1:
            return None
        s = body.rstrip()
        if not s.endswith(";"):
            return None
        end = d.body_open + 1 + len(s) - 1
        r0 = d.body_open + 1 + rets[0].end()
        for c in fi.calls:
            if c.func is None or c.func.body_open != d.body_open:
                continue
            if fi.code[r0:c.start].strip():
                continue
            k = c.rparen + 1
            while fi.code[k] in " \t\r\n":
                k += 1
            if k != end:
                return None
            seg = fi.code[d.body_open:c.start]
            if seg.count("{") - seg.count("}") != 1:
                return None
            return c
        return None

    def _bare_return_call(self, fi, d: Def, ra: int):
        """The call statement `G(..);` right before the bare `return;` at ra
        (same block, unconditional: preceded by `;`, `{` or `}`), or None."""
        j = ra - 1
        while j > d.body_open and fi.code[j] in " \t\r\n":
            j -= 1
        if fi.code[j] != ";":
            return None
        for c in fi.calls:
            if c.func is None or c.func.body_open != d.body_open:
                continue
            k = c.rparen + 1
            while fi.code[k] in " \t\r\n":
                k += 1
            if k != j:
                continue
            i = c.start - 1
            while fi.code[i] in " \t\r\n":
                i -= 1
            if fi.code[i] not in ";{}":
                return None
            return c
        return None

    _VCM_RET = {"g": r"(?:s8|u8|s16|u16|s32|u32|int|unsigned|bool|long|char|short|"
                     r"unsigned\s+int|signed\s+int|void\s*\*|\w+\s*\*)",
                "f": r"(?:f32|float)"}

    def _bare_return_member(self, fi, d: Def, ra: int, cls: str):
        """`<obj>-><m>(..); return;` right before the bare `return;` at ra in a
        value def, where <m> is a method the file declares as a VCM/VCM0
        accessor returning a value of the def's class (`s32 v103() { return
        VCM0(s32, 0x1A4); }`): retail tail-returns the virtual's $v0
        (MenuObjInsectGetLevel_386b90, CharaFindActivatableSlotByRec_3ac460;
        docs/UNBOUND-TRIAGE.md "Compile review").  -> (statement start, m)."""
        j = ra - 1
        while j > d.body_open and fi.code[j] in " \t\r\n":
            j -= 1
        if fi.code[j] != ";":
            return None
        i = j - 1
        while i > d.body_open and fi.code[i] not in ";{}":
            i -= 1
        stmt = i + 1
        while fi.code[stmt] in " \t\r\n":
            stmt += 1
        s = fi.code[stmt:j]
        m = re.fullmatch(r"\(\s*\(\s*(?:struct\s+|class\s+)?\w+\s*\*\s*\)\s*\w+\s*\)\s*->\s*(\w+)"
                         r"\s*\((.*)\)\s*", s, re.S)
        if not m or "=" in m.group(2).replace("==", ""):
            return None
        mname = m.group(1)
        rt = self._VCM_RET.get(cls)
        if rt is None:
            return None
        # the snapshot spells the method `virtual s32 v103();` (the devirt
        # stage, which runs later, turns it into the VCM accessor)
        if not (re.search(r"\bvirtual\s+%s\s+%s\s*\([^)]*\)\s*(?:const\s*)?;"
                          % (rt, re.escape(mname)), fi.code) or
                re.search(r"\b%s\s+%s\s*\([^)]*\)\s*(?:const\s*)?\{\s*return\s+VCM0?\s*\(\s*%s\s*,"
                          % (rt, re.escape(mname), rt), fi.code)):
            return None
        return stmt, mname

    def _ret_span(self, fi, d):
        """Absolute span of the definition's return-type spelling."""
        rs = fi.code[d.start:d.name_off]
        m = re.match(r'(\s*(?:extern\s*"[^"]*"\s*|static\s+|inline\s+|__inline\s+)*)(.*?)\s*$',
                     rs, re.S)
        return d.start + m.end(1), d.start + m.end(2)

    def _tail_call(self, d: Def):
        fi = self.files[d.rel]
        body = fi.code[d.body_open + 1:d.body_close]
        if re.search(r"\breturn\b|\bgoto\b|\blongjmp\b", body):
            return None
        s = body.rstrip()
        if not s.endswith(";"):
            return None
        end = d.body_open + 1 + len(s) - 1          # offset of the final ';'
        for c in fi.calls:
            if c.func is None or c.func.body_open != d.body_open:
                continue
            k = c.rparen + 1
            while fi.code[k] in " \t\r\n":
                k += 1
            if k != end:
                continue
            # the call must be the whole statement, at body top level, unconditional
            j = c.start - 1
            while fi.code[j] in " \t\r\n":
                j -= 1
            if fi.code[j] not in ";{}":
                return None
            seg = fi.code[d.body_open:c.start]
            if seg.count("{") - seg.count("}") != 1:
                return None
            return c
        return None

    def _v0_listing(self, d: Def):
        """Rule `def-v0-return` (listing-driven tail value).  A void C
        definition whose callers read its value, where retail's listing
        returns a call's result at EVERY exit (asmflow.exit_class 'pass':
        $v0 after each `jr $31` is the RET of a jal, or the exit is a tail
        `j`), and every such jal/j pairs with one C call of a value-returning
        definition.  Shapes `_tail_call` cannot see: one tail call per
        branch (insect_InsectBattleIsSideAi_4f1950: `if (f) T(o, 1); else
        T(o, 0);`), or a conditional second call falling off the end with
        the first call's $v0 live (insect_InsectStoryGetRankTierMaybe_510420).
        -> (V0Tail(calls), ret T) or None."""
        fi = self.files[d.rel]
        if d.is_asm or d.body_close <= d.body_open:
            return None
        img = self.image_of(d.rel)
        r = self._listing(img, d.name)
        if not r:
            return None
        cfg = self._cfg_cache.get((img, d.name))
        if cfg is None:
            cfg = self._cfg_cache[(img, d.name)] = asmflow.CFG(r[0])
        cls, callees = asmflow.exit_class(cfg)
        if cls != "pass" or "<indirect>" in callees:
            return None
        J = set()
        for kind, v in asmflow.exit_values(cfg):
            if kind == "jr":
                for t in asmflow._flat(v):
                    if t.kind != "ret":
                        return None
                    J.add(t.a)
        for ds in cfg.tail:
            if cfg.tail[ds] == "<indirect>":
                return None
            J.add(ds - 1)
        hit, got = [], set()
        for c in fi.calls:
            if c.func is None or c.func.body_open != d.body_open:
                continue
            st = self._site(fi, c)
            if st is None:
                continue
            js = st[1]
            if len(js) != 1:
                if set(js) & J:
                    return None
                continue
            if js[0] in J:
                hit.append(c)
                got.add(js[0])
        if not hit or got != J:
            return None
        rets = []
        for c in hit:
            g = self.resolve(fi, c.name)
            if g is None:
                return None
            src = self.import_src.get(id(g), g)
            gr = g.sig.ret if g.sig.ret.cls != "v" else (
                self.tail[id(src)][2] if id(src) in self.tail else None)
            if gr is None or gr.cls not in ("g", "f"):
                return None
            rets.append(gr)
        if len({x.cls for x in rets}) != 1 or len({x.kind for x in rets}) != 1:
            return None
        if fi.cpp and len({(x.c, x.ptr) for x in rets}) != 1:
            return None
        if len({x.c for x in rets}) == 1:
            gret = rets[0]
        elif rets[0].cls == "g" and rets[0].kind == "i" and not any(x.ptr for x in rets):
            gret = T("g", "int", "int")
        else:
            return None
        if fi.cpp:
            # C++: only whole-statement calls (no int<->pointer conversions to spell)
            for c in hit:
                k = c.start - 1
                while fi.code[k] in " \t\r\n":
                    k -= 1
                e = c.rparen + 1
                while fi.code[e] in " \t\r\n":
                    e += 1
                if fi.code[k] not in ";{})" or fi.code[e] != ";":
                    return None
        return V0Tail(hit), gret

    def _v0_rewrite(self, fi, d, vt, gret, rw) -> None:
        code = fi.code
        tt = "void *" if gret.ptr else gret.c
        a, b = self._ret_span(fi, d)
        rw.append(Rewrite(a, b, "text", tt))
        rw.append(Rewrite(d.body_open + 1, d.body_open + 1, "text", f" {tt} rgp_v0 = 0;"))
        # C++ has no implicit int<->pointer conversion: the view may read the
        # callee as a pointer (ret-cast) where the effective type is int, or
        # the reverse; spell the assignment through `long` (4 bytes on i686)
        pre = (f"(rgp_v0 = ({tt})(long)(" if fi.cpp and gret.cls == "g" else "(rgp_v0 = ")
        post = "))" if fi.cpp and gret.cls == "g" else ")"
        for c in vt.calls:
            rw.append(Rewrite(c.start, c.start, "text", pre))
            rw.append(Rewrite(c.rparen + 1, c.rparen + 1, "text", post))
        body_a, body_b = d.body_open + 1, d.body_close
        for m in re.finditer(r"\breturn\s*;", code[body_a:body_b]):
            rw.append(Rewrite(body_a + m.start(), body_a + m.end(), "text", "return rgp_v0;"))
        # GNU `return (void)expr;` in the void definition: evaluate, then return
        for m in re.finditer(r"\breturn\s*(\(\s*void\s*\))?(?=\s*[^\s;])", code[body_a:body_b]):
            k, dep = body_a + m.end(), 0
            while k < body_b and not (code[k] == ";" and dep == 0):
                dep += code[k] in "([{"
                dep -= code[k] in ")]}"
                k += 1
            rw.append(Rewrite(body_a + m.start(), body_a + m.end(), "text", "return ("))
            rw.append(Rewrite(k, k, "text", ", rgp_v0)"))
        rw.append(Rewrite(d.body_close, d.body_close, "text", "return rgp_v0; "))
        self._log(fi, d.start, d.name, "def-v0-return",
                  f"void def; retail's $v0 at every exit is the result of "
                  f"{', '.join(sorted({c.name for c in vt.calls}))} ({len(vt.calls)} call(s)) -> "
                  f"definition returns it ({tt}); {len(self.used_from_void.get(d.name, ()))} "
                  f"caller(s) use the value")

    def _tail_vcall(self, d: Def, uses):
        """C++ `void F(..) { ..; p->m(..); }` whose callers use the value:
        retail returns the virtual call's $v0/$f0 (no instruction after the
        jalr touches it; e.g. CharaGetIconRecMaybe_3ae3e0's slot-0x340 call).
        Only when `m` is declared once in the file, `virtual void m(..)`: the
        method gets the callers' type (they are the only evidence of it), F
        returns it (`def-tail-vcall-return`).  -> (stmt off, (a, b) span of
        the method's `void`, ret T) or None."""
        fi = self.files[d.rel]
        if not fi.cpp:
            return None
        code = fi.code
        body = code[d.body_open + 1:d.body_close]
        if re.search(r"\b(return|goto|longjmp)\b", body):
            return None
        s = body.rstrip()
        if not s.endswith(";"):
            return None
        end = d.body_open + 1 + len(s) - 1
        k, dep = end - 1, 0
        while k > d.body_open:
            ch = code[k]
            if ch in ")]":
                dep += 1
            elif ch in "([":
                dep -= 1
            elif dep == 0 and ch in ";{}":
                break
            k -= 1
        if code[k] not in "{;":
            return None
        seg = code[d.body_open:k + 1]
        if seg.count("{") - seg.count("}") != 1:
            return None
        st = code[k + 1:end]
        m = re.fullmatch(r"\s*[A-Za-z_]\w*\s*(?:->|\.)\s*([A-Za-z_]\w*)\s*\((.*)\)\s*",
                         st, re.S)
        if not m:
            return None
        lp = k + 1 + m.start(2) - 1
        if match_paren(code, lp) != k + 1 + m.end(2):
            return None
        meth = m.group(1)
        decls = [x for x in re.finditer(rf"\b{meth}\s*\(", code) if fi.in_class(x.start())]
        if len(decls) != 1:
            return None
        head = code[max(0, decls[0].start() - 80):decls[0].start()]
        mv = re.search(r"\bvirtual\s+(void)\s*$", head)
        if not mv:
            return None
        a = decls[0].start() - len(head) + mv.start(1)
        cls = Counter(v.cls for _, _, v in uses).most_common(1)[0][0]
        if cls == "f":
            rt = T("f", "float", "float")
        elif any(v.ptr for _, _, v in uses if v.cls == "g"):
            rt = T("g", "void *", "void *", True)
        else:
            rt = T("g", "int", "int")
        stmt = k + 1 + (len(st) - len(st.lstrip()))
        return (stmt, (a, a + 4), rt)

    # ------------------------------------------------ vararg-narrow
    _VA_INT = {"s32", "u32", "int", "unsigned", "unsigned int", "signed int", "s16", "u16",
               "s8", "u8", "char", "short", "long", "unsigned long"}

    def _va_reads(self) -> dict:
        """Variadic definitions whose every `va_arg(ap, T)` reads the same
        4-byte-or-less integer type T: {name: T}."""
        if getattr(self, "_va_cache", None) is not None:
            return self._va_cache
        out = {}
        for fi in self.files.values():
            for d in fi.defs:
                if d.is_asm or not d.sig.va:
                    continue
                body = fi.code[d.body_open:d.body_close]
                ts = {" ".join(m.group(1).split())
                      for m in re.finditer(r"\bva_arg\s*\(\s*\w+\s*,\s*([\w\s\*]+?)\s*\)", body)}
                if len(ts) == 1:
                    t = ts.pop()
                    if t in self._VA_INT:
                        out[d.name] = t
                    else:
                        tt = resolve_type(t, fi.tdefs)
                        if tt.kind == "i" and not tt.ptr:
                            out[d.name] = t
        self._va_cache = out
        return out

    def _expr_kind(self, fi, c, expr: str):
        """i686 transport kind ('q' 8-byte int, 'd' double, ...) of a simple
        argument expression, or None when it cannot be told: an identifier
        (parameter of the enclosing definition or a local declared in it), a
        cast `(T)x`, an integer literal with an LL suffix, a call."""
        e = expr.strip()
        m = re.fullmatch(r"\(\s*([A-Za-z_][\w\s\*]*?)\s*\)\s*[\w\.\->\[\]]+", e)
        if m:
            try:
                return resolve_type(m.group(1), fi.tdefs).kind
            except Exception:
                return None
        if re.fullmatch(r"-?(0[xX][0-9A-Fa-f]+|\d+)[uU]?(ll|LL)[uU]?", e):
            return "q"
        m = re.fullmatch(r"([A-Za-z_]\w*)\s*\(.*\)", e, re.S)
        if m:
            g = self.resolve(fi, m.group(1))
            return self.sig(g).ret.kind if g is not None else None
        if not re.fullmatch(r"[A-Za-z_]\w*", e):
            return None
        encl = None
        for d in fi.defs:
            if c.func is not None and d.body_open == c.func.body_open:
                encl = d
        if encl is not None:
            for p in encl.sig.params:
                if p.name == e:
                    return p.kind
            body = fi.code[encl.body_open:c.start]
            ds = list(re.finditer(r"(?:^|[;{}])\s*((?:const\s+|unsigned\s+|signed\s+|struct\s+)*"
                                  r"[A-Za-z_]\w*)\s+(?:[A-Za-z_]\w*\s*(?:=[^;,]*)?,\s*)*\**\s*"
                                  r"%s\s*(?:[;=,\[])" % re.escape(e), body))
            if ds:
                raw = ds[-1].group(1)
                if raw in KEYWORDS - {"struct", "union", "unsigned", "signed", "const"}:
                    return None
                star = ds[-1].group(0).rstrip().endswith("*")
                try:
                    tt = resolve_type(raw, fi.tdefs)
                except Exception:
                    return None
                return "i" if "*" in ds[-1].group(0).split(raw, 1)[1].split(e)[0] else tt.kind
        g = self.gdef.get(e)
        return None

    _PRINTF_FMT = {"Sprintf_1343b8": 1, "Fprintf_12f9a0": 1, "DbgPrintf_15e780": 0}

    def _data_string(self, name: str):
        """The C string a MAIN data object `char D_x[] = "..."` holds."""
        if not hasattr(self, "_dstr"):
            self._dstr = {}
            for rel, fi in self.files.items():
                if "/main_data/" not in "/" + rel:
                    continue
                for m in re.finditer(r'\bchar\s+(D_[0-9A-Fa-f]{8})\s*\[[^\]]*\][^=;]*=\s*"((?:[^"\\]|\\.)*)"',
                                     fi.text):
                    self._dstr[m.group(1)] = m.group(2)
        return self._dstr.get(name)

    def _vararg_missing(self, fi: FileInfo, rw: list) -> None:
        """Rule `vararg-missing`: a printf-family call whose format reads more
        arguments than the C passes.  mwcc passed whatever the argument
        registers held: when retail's listing shows the register still holds
        the caller's incoming value (or a spellable value), it is passed
        (EvMonographChrName_2e93f0: `Sprintf(a1, "mono_chr_%03d_%s")` with a2/a3
        untouched -> `Sprintf(a1, fmt, a2, a3)`); otherwise
        `manual-vararg-missing` is logged."""
        for c in fi.calls:
            k = self._PRINTF_FMT.get(c.name)
            if k is None or c.func is None or len(c.args) <= k:
                continue
            a, b = c.args[k]
            ex = fi.text[a:b].strip()
            m = re.fullmatch(r'"((?:[^"\\]|\\.)*)"', ex)
            fmt = m.group(1) if m else None
            if fmt is None:
                m = re.fullmatch(r"(?:\([^()]*\)\s*)?&?\s*(D_[0-9A-Fa-f]{8})(?:\s*\[\s*0\s*\])?", ex)
                fmt = self._data_string(m.group(1)) if m else None
            if fmt is None:
                continue
            fmt = re.split(r"\\0+(?![0-7])|\\000", fmt)[0]
            convs =[x for x in re.findall(r"%[-+ #0]*(\*|\d+)?(?:\.(\*|\d+))?[hlLqjzt]*([diouxXcspfeEgGn%])",
                                           fmt.replace("%%", "")) if x[2] != "%"]
            need = len(convs) + sum(1 for x in convs for y in x[:2] if y == "*")
            have = len(c.args) - k - 1
            # an unprototyped (C) / all-variadic (C++) function type: i686 cdecl
            # passes every argument as the variadic call does, and the view's
            # fixed parameter types (s32 for a pointer) need no conversion
            pro = "int (*)(...)" if fi.cpp else "int (*)()"
            # a fixed-arity local view with 8-byte parameters at variadic
            # positions (TaskEntryFormatStatus_208a90: `Sprintf(s32, void *,
            # s64, s64, s32)` for " [%c][%c]%s"): mwcc converted the argument to
            # the view's type and the callee read the slot's low word; here the
            # argument is narrowed to int and the call goes through the
            # variadic type, so the view cannot widen it again
            vs, _src = self.view(fi, c)
            narrowed = []
            if vs is not None and not vs.va:
                for i in range(k + 1, min(len(c.args), len(vs.params))):
                    j = i - k - 1
                    if vs.params[i].kind == "q" and j < len(convs) and convs[j][2] in "diouxXcsp":
                        a, b = c.args[i]
                        rw.append(Rewrite(a, b, "text", f"(int)({fi.text[a:b]})"))
                        narrowed.append(i + 1)
            if narrowed and need <= have:
                rw.append(Rewrite(c.start, c.start, "text", f"(({pro})"))
                rw.append(Rewrite(c.start + len(c.name), c.start + len(c.name), "text", ")"))
                self._log(fi, c.start, c.name, "vararg-narrow",
                          f"local view {vs.ret.c}({', '.join(p.c for p in vs.params)}) widens "
                          f"args {narrowed} to 8 bytes; format {fmt!r} reads 4 -> (int), "
                          f"called through the variadic type")
            if need <= have:
                continue
            add = []
            encl = next((d for d in fi.defs if d.body_open == c.func.body_open), None)
            for lane in range(len(c.args), len(c.args) + need - have):
                t = self._asm_term(fi, c, "g", lane)
                sp = self._spell(fi, c, t) if t != "noasm" and not asmflow.has_clobber(t) else None
                if sp is None and t != "noasm" and str(t).startswith("ENTRY($") and encl is not None:
                    # the caller's own incoming register: its parameter, when
                    # the C never assigns it before the call
                    r = int(re.search(r"\$(\d+)", str(t)).group(1)) - 4
                    ps = self.sig(encl).params if id(encl) in self.eff else encl.sig.params
                    if 0 <= r < len(ps) and ps[r].name and ps[r].cls == "g" and all(
                            p.cls == "g" for p in ps[:r]):
                        nm = ps[r].name
                        body = fi.code[encl.body_open:c.start]
                        if not re.search(r"\b%s\s*(?:[-+*/|&^%%]?=(?!=)|\+\+|--)|(?:\+\+|--)\s*%s\b|&\s*%s\b"
                                         % (re.escape(nm), re.escape(nm), re.escape(nm)), body):
                            sp = (nm, "entry")
                if sp is None:
                    break
                add.append(sp[0])
            if len(add) != need - have:
                self._log(fi, c.start, c.name, "manual-vararg-missing",
                          f"format {fmt!r} reads {need} argument(s), {have} passed; "
                          f"retail's registers cannot be spelled")
                continue
            rw.append(Rewrite(c.rparen, c.rparen, "text", "".join(", " + x for x in add)))
            # call through the provider's variadic type (the C file declares a
            # fixed-arity local view)
            rw.append(Rewrite(c.start, c.start, "text", f"(({pro})"))
            rw.append(Rewrite(c.start + len(c.name), c.start + len(c.name), "text", ")"))
            self._log(fi, c.start, c.name, "vararg-missing",
                      f"format {fmt!r} reads {need} argument(s), {have} passed; retail "
                      f"passed the argument registers' values -> {', '.join(add)}")

    def _vararg_narrow(self, fi: FileInfo, rw: list) -> None:
        """Rule `vararg-narrow`: a variadic argument wider than what the callee's
        va_arg reads.  On the EE every variadic argument is one 64-bit GPR/stack
        slot, so `SoundSendCmd_1b6cc0(0x20, 10, .. s64 vel, s64 pan, s64 bend ..)`
        with ten `va_arg(ap, s32)` reads the low word of each; on i686 an s64
        takes two 4-byte slots and every later read shifts (every sound effect
        played hard left, two semitones flat).  The argument is cast to the
        callee's va_arg type."""
        va = self._va_reads()
        if not va:
            return
        for c in fi.calls:
            t = va.get(c.name)
            if t is None or c.func is None:
                continue
            d = self.resolve(fi, c.name)
            if d is None:
                continue
            nfix = len(d.sig.params)
            for i in range(nfix, len(c.args)):
                a, b = c.args[i]
                ex = fi.code[a:b]
                k = self._expr_kind(fi, c, ex)
                if k == "q":
                    if "(" in ex.replace(")", "") and not re.fullmatch(r"\s*\([\w\s\*]+\)\s*\w+\s*", ex):
                        self._log(fi, a, c.name, "info-vararg-wide",
                                  f"arg {i + 1} `{' '.join(ex.split())}` is 64-bit, callee reads "
                                  f"va_arg({t}); not rewritten (complex expression)")
                        continue
                    rw.append(Rewrite(a, b, "text", f"({t})({fi.text[a:b]})"))
                    self._log(fi, a, c.name, "vararg-narrow",
                              f"arg {i + 1} `{' '.join(ex.split())}` is 64-bit; callee reads "
                              f"va_arg({t}) (EE: one 64-bit slot per vararg) -> ({t})")
                elif k == "d":
                    self._log(fi, a, c.name, "info-vararg-wide",
                              f"arg {i + 1} `{' '.join(ex.split())}` is a double, callee reads "
                              f"va_arg({t})")

    # ------------------------------------------------ stack blocks
    _PRIM_SIZE = {"s8": 1, "u8": 1, "char": 1, "s16": 2, "u16": 2, "short": 2, "s32": 4,
                  "u32": 4, "int": 4, "f32": 4, "float": 4, "s64": 8, "u64": 8, "f64": 8,
                  "double": 8, "unsigned char": 1, "signed char": 1, "unsigned short": 2,
                  "short int": 2, "unsigned int": 4, "unsigned": 4, "signed": 4, "long": 4,
                  "unsigned long": 4, "long long": 8, "unsigned long long": 8, "bool": 1,
                  "vc_u32": 4, "size_t": 4, "uintptr_t": 4}

    @staticmethod
    def _find_typedef(code: str, name: str):
        """(kind, body, attr) of struct/union/class `name` defined in code
        (`struct name {..}`, `typedef struct [tag] {..} name;`), ('alias', T)
        for `typedef T name;`, ('enum',) for an enum, or None.  A class with
        base classes is None."""
        en = re.escape(name)
        for m in re.finditer(r"\b(struct|union|class)\s+%s\s*((?::[^{;]*)?)((?:__attribute__\s*\(\(.*?\)\)\s*)*)\{" % en, code):
            if m.group(2).strip():
                return None
            i = m.end()
            depth, j = 1, i
            while j < len(code) and depth:
                if code[j] == "{":
                    depth += 1
                elif code[j] == "}":
                    depth -= 1
                j += 1
            k = code.find(";", j)
            return (m.group(1), code[i:j - 1], m.group(3) + " " + code[j:k if k >= 0 else j])
        # `} NAME;`, `} __attribute__((..)) NAME;` or `} NAME __attribute__((..));`
        for m in re.finditer(r"\}\s*((?:__attribute__\s*\(\(.*?\)\)\s*)*)%s\s*"
                             r"((?:__attribute__\s*\(\(.*?\)\)\s*)*);" % en, code):
            j = m.start()
            depth, i = 1, j - 1
            while i >= 0 and depth:
                if code[i] == "}":
                    depth += 1
                elif code[i] == "{":
                    depth -= 1
                i -= 1
            head = code[max(0, i - 200):i + 1]
            hm = re.search(r"\btypedef\s+(struct|union|enum)\s*(\w+)?\s*((?:__attribute__\s*\(\(.*?\)\)\s*)*)$", head)
            if not hm:
                continue
            if hm.group(1) == "enum":
                return ("enum",)
            return (hm.group(1), code[i + 2:j], (hm.group(3) or "") + " " + m.group(1) + " " + m.group(2))
        if re.search(r"\benum\s+%s\s*\{" % en, code):
            return ("enum",)
        m = re.search(r"\btypedef\s+((?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|union\s+)*\w+(?:\s+\w+)?)\s*(\**)\s*%s\s*((?:\[\s*\w+\s*\]\s*)*);" % en, code)
        if m:
            return ("alias", m.group(1) + (" *" if m.group(2) else ""), m.group(3))
        return None

    def _struct_layout(self, fi: FileInfo, typ: str, depth=0):
        """(size, align, {member: offset}) of a struct / union / class type
        defined in the file (else in the game headers' C view), laid out the
        mwcc way (tools/stages/clayout.py), or None."""
        if depth > 6:
            return None
        cache = fi.__dict__.setdefault("_rgp_layouts", {})
        if typ in cache:
            return cache[typ]
        cache[typ] = None
        name = re.sub(r"^(struct|union|class|enum)\s+", "", typ.strip())
        d = self._find_typedef(fi.code, name)
        if d is None:
            hc = self.__dict__.setdefault("_hdr_find2", {})
            if name not in hc:
                hc[name] = self._find_typedef(getattr(self, "hdr_code", ""), name)
            d = hc[name]
        if d is None:
            return None
        if d[0] == "enum":
            cache[typ] = (4, 4, {})
            return cache[typ]
        if d[0] == "alias":
            r = self._type_size(fi, d[1], d[2], depth + 1)
            cache[typ] = None if r is None else (r[0], r[1], {})
            return cache[typ]
        lay = clayout.layout(d[1], lambda t: self._type_size(fi, t, "", depth + 1),
                             d[0] == "union", d[2])
        cache[typ] = lay
        return lay

    def _type_size(self, fi: FileInfo, typ: str, dims: str, depth=0):
        """(size, align) of a local's declared type (+ array dims), or None."""
        t = " ".join(re.sub(r"\b(const|volatile)\b", "", typ).split())
        if t.endswith("*"):
            s, a = 4, 4
        elif t in self._PRIM_SIZE:
            s = a = self._PRIM_SIZE[t]
        elif t in ("u128", "s128", "rg_u128", "qword"):
            s = a = 16
        else:
            lay = self._struct_layout(fi, t, depth)
            if lay is None:
                return None
            s, a = lay[0], lay[1]
        for x in re.findall(r"\[([^\]]*)\]", dims or ""):
            v = clayout._dim(x)         # `s32 sp[0x30 / 4]`: literal arithmetic
            if v is None:
                return None
            s *= v
        return (s, a)

    def _member_offset(self, fi: FileInfo, typ: str, path: str):
        lay = self._struct_layout(fi, typ)
        if lay is None or "." in path:
            return None
        return lay[2].get(path)

    # `(E + C) - C` with C = 1.5 * 2^23 (or 2^23): the "add a big constant"
    # float-to-integer rounding trick.  The EE FPU has ONE rounding mode,
    # toward zero, so on retail the sum drops E's fraction toward zero and
    # the expression is floor(E) (|E| < 2^22; for E < 0 the sum C + E is
    # positive and truncates down).  SSE rounds to nearest, so the same C
    # gives round(E).  AngleWrap_1cbf30 computes
    # `x - 2pi * sign(x) * trick(0.5 + |x| / 2pi)`: with round-to-nearest every
    # |x| < pi wrapped to -sign(x) * pi, the chara turn controller
    # (CharaUpdateMovement_20a7d0) never converged and the leader stayed in
    # the run state after the stick was released (BRINGUP.md 2026-10-18 b).
    _EE_ROUND = re.compile(r"\(\s*(?P<e>(?:[^()]|\((?:[^()]|\([^()]*\))*\))+?)\s*\+\s*"
                           r"(?P<c>12582912|8388608)(?:\.0*)?[fF]\s*\)\s*-\s*(?P=c)(?:\.0*)?[fF](?![\w.])")

    def _ee_round(self, fi: FileInfo, rw: list) -> None:
        """Rule `ee-round-floor`: `(E + 12582912.0f) - 12582912.0f` (or
        8388608.0f) -> `__builtin_floorf(E)` (EE round-toward-zero result)."""
        for m in self._EE_ROUND.finditer(fi.code):
            e = fi.code[m.start("e"):m.end("e")]
            if any(r.start < m.end() and m.start() < r.end for r in rw):
                continue
            rw.append(Rewrite(m.start(), m.end(), "text", f"__builtin_floorf({e})"))
            self._log(fi, m.start(), "-", "ee-round-floor",
                      f"`({' '.join(e.split())} + {m.group('c')}.0f) - {m.group('c')}.0f`: "
                      f"EE FPU rounds toward zero, so retail's result is floor(); SSE "
                      f"rounds to nearest -> __builtin_floorf")

    def _sb_resolver(self):
        """sbresolve.Resolver over this stage (None with RG_PROTOS_NO_SBRESOLVE=1)."""
        if os.environ.get("RG_PROTOS_NO_SBRESOLVE"):
            return None
        if getattr(self, "_sbr", None) is None:
            import sbresolve
            W, T = sbresolve.data_words({rel: fi.text for rel, fi in self.files.items()
                                         if "/data2c_" in rel})
            self._sbr = sbresolve.Resolver(self, self._flow(), W, T)
            self._sbr.port_lanes = self._sb_port_lanes
            self._sbr.port_nparams = (lambda nm: len(self.sig(self.gdef[nm]).params)
                                      if nm in self.gdef else None)
        return self._sbr

    def _sb_port_lanes(self, fn, j):
        """GPR lanes the port's C member call paired with jalr j of listing fn
        passes (this + C GPR arguments + the vcall-forward lanes), else None."""
        img, _c, nm = fn.partition(":")
        if "@" in nm or j is None:
            return None
        d = self.gdef.get(nm)
        fi = self.files.get(d.rel) if d is not None else None
        if fi is None or not fi.cpp or d.is_asm or self.image_of(fi.rel) != img:
            return None
        vp = self._vcall_pairs(fi, d)
        if vp is None:
            return None
        cfg, mcalls, jalrs, _v0j = vp
        if j not in jalrs:
            return None
        _arrow, noff, _nm, lp, decls = mcalls[jalrs.index(j)]
        _n, ngpr = self._vcall_ngpr(fi.code, lp, decls[0])
        return ngpr + 1 + len(self._vcall_fwd(fi, d, cfg, j, ngpr, noff))

    def _sb_term(self, fi, c, k):
        """[kind, value] of call c's GPR lane k in the listing when it is a
        symbol / absolute address / constant (stack-block census), else None."""
        t = self._asm_term(fi, c, "g", k)
        if isinstance(t, asmflow.Term) and t.kind in ("sym", "addr", "const"):
            return [t.kind, t.a]
        return None

    def _stack_blocks(self, fi: FileInfo, rw: list) -> None:
        """Rule `stack-block` (CollRaycastNearest* / CollSweepTri class).

        mwcc gave each address-taken local a fixed frame slot, and some callees
        reach past the local they are handed: CollSweepTri_1c7790(&point, ..)
        reads the Ray two locals further (point+0x50/+0x60), TriCalcBounds_1cb540
        stores 16 bytes into `f32 mn[3]`.  From retail's listing: every call
        argument that is a stack address sp+OFF (paired with the C argument
        `&x`, `&x.f..`, or an array `x`), and the extent E the callee reaches
        through it (asmflow Flow.extent).  When [OFF, OFF+E) holds another
        local's address, or E exceeds the local's own (primitive) size, the
        locals involved are placed in one 16-aligned byte block at retail's
        relative offsets (a local known only through a member address `&r.d0`
        is placed with __builtin_offsetof) and every use is rewritten to
        `(*(T *)(rgp_blkN + POS))`.  Logged `manual-stack-block` when a local
        cannot be rewritten (parameter, initialiser, several declarators)."""
        img = self.image_of(fi.rel)
        code = fi.code
        flow = self._flow()
        flow.max_depth = int(os.environ.get("RG_PROTOS_SB_DEPTH", "8"))
        nblk = 0
        trace_re = os.environ.get("RG_PROTOS_SB_TRACE")     # regex of def names: print the analysis
        guard_on = bool(os.environ.get("RG_PROTOS_SB_GUARD"))
        pend = None         # (d, locs, addrs, blocked) awaiting the guard pass
        for d in fi.defs:
            if pend is not None:
                self._sb_guard(fi, *pend, rw)
                pend = None
            if d.is_asm or d.body_close <= d.body_open:
                continue
            tr = (lambda *m, _n=d.name: print(f"sb-trace {_n}:", *m, file=sys.stderr))                 if trace_re and re.search(trace_re, d.name) else (lambda *m: None)
            r = self._listing(img, d.name)
            if not r:
                tr("no listing")
                continue
            body_a, body_b = d.body_open + 1, d.body_close
            # top-level single-declarator locals: name -> (decl span, type text, dims)
            locs = {}
            dup = set()
            for m in re.finditer(r"(?:(?<=[;{}])|^)(\s*)((?:const\s+|volatile\s+|struct\s+|union\s+|unsigned\s+|signed\s+)*"
                                 r"[A-Za-z_]\w*)\s+(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]\[;]*\]\s*)*)"
                                 r"((?:__attribute__\s*\(\(\s*aligned\s*\(\s*\w+\s*\)\s*\)\)\s*)?);",
                                 code[body_a:body_b], re.M):
                st = body_a + m.start(2)
                seg = code[d.body_open:st]
                if seg.count("{") - seg.count("}") != 1:
                    continue
                typ = m.group(2).strip()
                if typ in ("return", "goto", "case", "else", "do") or typ in KEYWORDS - {
                        "struct", "union", "unsigned", "signed", "const", "volatile", "char",
                        "short", "int", "long", "float", "double", "void"}:
                    continue
                nm = m.group(4)
                if nm in locs:
                    dup.add(nm)
                locs[nm] = (st, body_a + m.end(), (typ + " " + m.group(3)).strip(), m.group(5).strip())
            for nm in dup:
                locs.pop(nm, None)
            tr("locals", sorted(locs), "dup", sorted(dup))
            if not locs:
                continue
            calls = [c for c in fi.calls if c.func is not None and c.func.body_open == d.body_open]
            census = self.sb_census if self.sb_census is not None else None
            c0 = len(census) if census is not None else 0
            addrs = []      # (name, member path or '', off)
            wreach = []     # (name, off, write end): what the callee stores through the pointer
            sites = []      # (name, off, E)
            unres = []      # (callee, lane, C arg, off, E or None): extent not complete
            for c in calls:
                g = self.resolve(fi, c.name)
                gp = self.sig(g).params if g is not None and id(g) in self.eff else None
                lane = 0
                for i, (a, b) in enumerate(c.args):
                    if gp is not None and i < len(gp) and gp[i].cls != "g":
                        continue
                    if gp is None and re.fullmatch(r"\s*-?[\d.]+f\s*", fi.code[a:b]):
                        continue
                    k = lane
                    lane += 1
                    if k >= 8:           # EABI: $4..$11
                        break
                    ex = code[a:b].strip()
                    while True:
                        mm = re.match(r"\(\s*(?:const\s+|struct\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*[\s\*]*\)\s*", ex)
                        if not mm or mm.end() == len(ex):
                            break
                        ex = ex[mm.end():]
                    mm = re.fullmatch(r"&\s*([A-Za-z_]\w*)((?:\s*\.\s*[A-Za-z_]\w*)*)", ex) or \
                        re.fullmatch(r"\(?\s*([A-Za-z_]\w*)()\s*\)?", ex) or \
                        re.fullmatch(r"\(?\s*([A-Za-z_]\w*)((?:\s*\.\s*[A-Za-z_]\w*)+)\s*\)?", ex)
                    if not mm or mm.group(1) not in locs:
                        continue
                    nm, mem = mm.group(1), re.sub(r"\s", "", mm.group(2)).lstrip(".")
                    if not ex.startswith("&") and not locs[nm][3] and not mem:
                        continue            # a plain scalar value, not an address
                    # (a member `x.f` without `&` is an array member when the listing
                    # passes a stack address: checked by the term below)
                    t = self._asm_term(fi, c, "g", k)
                    if t == "noasm" or not isinstance(t, asmflow.Term) or t.kind != "sp":
                        tr(f"call {c.name} arg {k} {ex}: listing term {t!r} (not a stack address)")
                        continue
                    addrs.append((nm, mem, t.a))
                    callee = flow.resolve(c.name, f"{img}:{d.name}") or (
                        f"{img}:{c.name}" if c.name in asmflow.Flow.LEN_ARG
                        or c.name in asmflow.Flow.STR_ARG else None)
                    # integer-literal arguments: the length of a LEN_ARG callee (memcpy ..)
                    kargs = {}
                    if callee and callee.split(":")[-1] in asmflow.Flow.LEN_ARG:
                        for i2 in range(min(4, len(c.args))):
                            t2 = self._asm_term(fi, c, "g", i2)
                            if isinstance(t2, asmflow.Term) and t2.kind == "const":
                                kargs["$%d" % (4 + i2)] = t2.a
                    rnotes = []
                    if callee:
                        e, _ok = flow.extent(callee, "$%d" % (4 + k), kargs=kargs)
                        wend = flow.rw_extent(callee, "$%d" % (4 + k), kargs)[1]
                        R = self._sb_resolver() if not _ok else None
                        if R is not None:
                            # function-pointer targets (vtables, callbacks, tables,
                            # reviewed sources): tools/stages/sbresolve.py
                            e2, _ok, rnotes, _tg, w2 = R.extent(
                                callee, "$%d" % (4 + k), kargs,
                                ctx={"img": img, "def": d.name, "off": t.a,
                                     "terms": {"$%d" % (4 + i2): self._sb_term(fi, c, i2)
                                               for i2 in range(min(8, len(c.args)))}})
                            tr(f"  resolved: E 0x{e2:x} complete={_ok}: {'; '.join(rnotes)}")
                            e, wend = max(e, e2), max(wend, w2)
                        tr(f"call {c.name} arg {k} {ex}: sp{t.a:+#x}, extent 0x{e:x} complete={_ok}")
                        if e:
                            sites.append((nm, mem, t.a, e))
                            wreach.append((nm, t.a, wend))
                        if not _ok:
                            unres.append((c.name, k, ex, t.a, e))
                    else:
                        tr(f"call {c.name} arg {k} {ex}: sp{t.a:+#x}, callee has no listing")
                        unres.append((c.name, k, ex, t.a, None))
                    if census is not None:
                        census.append({"kind": "site", "file": fi.rel, "def": d.name, "img": img,
                                       "callee": c.name, "listing": callee, "lane": k, "arg": ex,
                                       "local": nm, "member": mem, "off": t.a, "kargs": kargs,
                                       "moff": self._member_offset(fi, locs[nm][2], mem) if mem else 0,
                                       "terms": {"$%d" % (4 + i2): self._sb_term(fi, c, i2)
                                                 for i2 in range(min(4, len(c.args)))}
                                       if callee and not _ok else {},
                                       "E": e if callee else None,
                                       "complete": bool(callee and _ok),
                                       "resolved": rnotes,
                                       "rw": flow.rw_extent(callee, "$%d" % (4 + k), kargs) if callee else None,
                                       "escapes": flow.escapes(callee, "$%d" % (4 + k), kargs) if callee else
                                       [{"fn": None, "kind": "nolisting", "tgt": c.name, "c": 0,
                                         "src": None, "reg": "$%d" % (4 + k)}]})
            if census is not None and len(census) > c0:
                lin = {}
                for n2 in locs:
                    sz = self._type_size(fi, locs[n2][2], locs[n2][3])
                    lin[n2] = {"type": locs[n2][2], "dims": locs[n2][3],
                               "size": sz[0] if sz else None,
                               "offs": sorted({o for nn, m, o in addrs if nn == n2 and not m}),
                               "moffs": sorted({(m, o) for nn, m, o in addrs if nn == n2 and m})}
                census.append({"kind": "locals", "file": fi.rel, "def": d.name, "img": img,
                               "locals": lin, "cpp": fi.cpp})
            blocked = set()
            if guard_on:
                pend = (d, locs, addrs, blocked)
            for cn, k, ex, off, e in unres:
                # the extent through this stack address is a lower bound only (the
                # pointer reaches a jalr, a callee without a listing, or depth > 4):
                # listed so misses of the rule can be reviewed (BRINGUP 2026-10-18 (f))
                self._log(fi, d.start, d.name, "info-stack-block-unresolved",
                          f"{cn} arg {k} `{ex}` = sp{off:+#x}: extent "
                          + ("unknown (no listing)" if e is None else f">= 0x{e:x} (incomplete)"))
            if not sites:
                continue
            # local sizes we can tell (primitive scalars / arrays)
            def psize(nm):
                typ, dims = locs[nm][2], locs[nm][3]
                if "*" in typ:
                    base = 4
                else:
                    base = self._PRIM_SIZE.get(typ)
                    if base is None:
                        return None
                n = 1
                for x in re.findall(r"\[([^\]]*)\]", dims):
                    v = clayout._dim(x)
                    if v is None:
                        return None
                    n *= v
                return base * n
            groups = []     # sets of names
            for nm, mem, off, e in sites:
                inside = {n2 for n2, m2, o2 in addrs if off <= o2 < off + e}
                own = psize(nm)
                if own is None:
                    tsz = self._type_size(fi, locs[nm][2], locs[nm][3])
                    own = tsz[0] if tsz else None
                if mem and own is not None:
                    mo = self._member_offset(fi, locs[nm][2], mem)
                    own = None if mo is None else own - mo
                tr(f"site {nm}{'.' + mem if mem else ''} sp{off:+#x} E=0x{e:x}: inside {sorted(inside)}, own size {own}")
                if inside - {nm} or (own is not None and e > own):
                    groups.append(inside | {nm})
            tr("addrs", addrs, "groups", groups)
            if not groups:
                continue
            # merge overlapping groups
            merged = []
            for g in groups:
                for h in [h for h in merged if h & g]:
                    merged.remove(h)
                    g = g | h
                merged.append(g)
            for g in merged:
                bad = [n for n in g if n in {p.name for p in d.sig.params}]
                ents = [(n, m, o) for n, m, o in addrs if n in g]
                base = min(o for _n, _m, o in ents) & ~15
                pos = {}
                for n in sorted(g):
                    cs = {o - base for nn, m, o in ents if nn == n and not m}
                    if len(cs) > 1:
                        bad.append(n)
                    elif cs:
                        pos[n] = "0x%x" % cs.pop()
                    else:
                        ms = sorted({(m, o) for nn, m, o in ents if nn == n})
                        m, o = ms[0]
                        typ = locs[n][2]
                        if locs[n][3]:
                            bad.append(n)
                            continue
                        pos[n] = f"(0x{o - base:x} - __builtin_offsetof({typ}, {m}))"
                if census is not None:
                    census.append({"kind": "group", "file": fi.rel, "def": d.name,
                                   "names": sorted(g), "bad": sorted(set(bad)), "base": base})
                if bad:
                    self._log(fi, d.start, d.name, "manual-stack-block",
                              f"locals {sorted(g)} are one retail stack block; cannot place "
                              f"{sorted(set(bad))}")
                    continue
                # every 16-byte slot the callees reach must belong to a placed
                # local: a slot no C local maps to is a retail local the C keeps
                # elsewhere (CameraBaseLookAt_15fae0's `up` row between `side`
                # and `dir`, written by inline VU0 code, not a call) -- placing
                # the others would hand the callee the wrong bytes
                spans, unk, named = [], [], []
                g = set(g)
                for n in g:
                    sz = self._type_size(fi, locs[n][2], locs[n][3])
                    p0 = pos[n]
                    if not p0.startswith("0x"):
                        mm = re.match(r"\(0x([0-9a-f]+) - __builtin_offsetof\((.*), (.*)\)\)$", p0)
                        mo = self._member_offset(fi, mm.group(2), mm.group(3)) if mm else None
                        p0 = None if mo is None else int(mm.group(1), 16) - mo
                    else:
                        p0 = int(p0, 16)
                    if sz is None or p0 is None:
                        unk.append(n)
                    else:
                        spans.append((p0, p0 + sz[0]))
                reach = max(o + e - base for n, m, o, e in sites if n in g)
                lo = min(o - base for n, m, o, e in sites if n in g) & ~15
                holes = [s for s in range(lo, reach, 16)
                         if not any(a < s + 16 and s < b for a, b in spans)]
                # a hole a C local NAMED for its retail slot fills (`spNNN`, the
                # decomp's spelling of sp+0xNNN): factory_FactoryStep_5069e0 hands
                # `VP8 sp1D0` (0x20 bytes) to FactoryPartGroupStep_4fea10, which reads
                # +0x20..0x28 = `sp1F0` (its flag and Def pointer), never address-taken
                # sp60q = sp+0x60 too; any lower-case prefix + hex offset (MapAreaModel
                # AddDrawOffRect_189300 `u8 b90[16]`, `bA0[16]`: one {lo, hi} pair),
                # candidates must share the anchor's prefix
                SPN = r"([a-z]+?)([0-9A-F]{2,}|[0-9a-f]{2,})[g-z]*"
                anchors = [(n, int(re.fullmatch(SPN, n).group(2), 16)) for n in g
                           if re.fullmatch(SPN, n) and pos[n].startswith("0x")]
                pfx = {re.fullmatch(SPN, n).group(1) for n, _v in anchors}
                if holes and anchors and len(pfx) == 1 and all(
                        int(pos[a], 16) - int(pos[b], 16) == va - vb
                        for a, va in anchors for b, vb in anchors):
                    an, av = anchors[0]
                    for n in sorted(locs):
                        mm = re.fullmatch(SPN, n)
                        if not mm or mm.group(1) != re.fullmatch(SPN, an).group(1)                                 or n in g or n in {p.name for p in d.sig.params}:
                            continue
                        rel = int(pos[an], 16) + int(mm.group(2), 16) - av
                        sz = self._type_size(fi, locs[n][2], locs[n][3])
                        if sz is None or rel < 0 or not any(h <= rel < h + 16 for h in holes):
                            continue
                        if any(a < rel + sz[0] and rel < b for a, b in spans):
                            continue
                        g.add(n)
                        pos[n] = "0x%x" % rel
                        ents.append((n, "", base + rel))
                        spans.append((rel, rel + sz[0]))
                        named.append(n)
                    holes = [h for h in holes if not any(a < h + 16 and h < b for a, b in spans)]
                # trailing slots past every placed local that a callee WRITES
                # (EffectCopyHandle_2dd3b0 stores a 20-byte handle into `s32
                # sp40[4]`): the C object is under-declared; the block pads it.
                # A slot only read stays a hole (it may be a retail local the C
                # keeps elsewhere: CameraBaseLookAt_15fae0's 4th row).
                top = max((b for _a, b in spans), default=0)
                padded = [h for h in holes if h >= top and any(
                    o - base <= h and h + 16 <= o - base + ((we + 15) & ~15)
                    for n, o, we in wreach if n in g)]
                holes = [h for h in holes if h not in padded]
                # a name used inside a macro body (PtalkFindPairRowMaybe_3e2160's
                # TRY(X) spells `&big`) or redeclared in a nested scope cannot be
                # rewritten use by use
                odd = [n for n in g if re.search(r"#[ \t]*define[^\n]*\b%s\b" % re.escape(n), fi.text)
                       or re.search(r"\b(?:s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|short|"
                                    r"float|double|long|unsigned|signed|struct\s+\w+|[A-Z]\w*)\s*\**\s+%s\s*"
                                    r"(?:\[[^\]]*\]\s*)*[;=,]" % re.escape(n), code[locs[n][1]:body_b])]
                if census is not None:
                    census.append({"kind": "outcome", "file": fi.rel, "def": d.name,
                                   "names": sorted(g), "built": not (unk or holes or odd),
                                   "unk": sorted(unk), "holes": holes})
                if odd and not (unk or holes):
                    self._log(fi, d.start, d.name, "manual-stack-block",
                              f"locals {sorted(g)} are one retail stack block, but {sorted(odd)} "
                              f"appear in a macro or a nested redeclaration")
                    continue
                if unk or holes:
                    self._log(fi, d.start, d.name, "manual-stack-block",
                              f"locals {sorted(g)} are one retail stack block, but "
                              + (f"sizes unknown for {sorted(unk)}" if unk else
                                 f"block slot(s) {', '.join(hex(h) for h in holes)} hold no C local"))
                    continue
                nblk += 1
                bn = f"rgp_blk{nblk}"
                ends = [f"{pos[n]} + sizeof({locs[n][2]}{locs[n][3]})" for n in sorted(g)]
                ends += [f"0x{o + e - base:x}" for n, m, o, e in sites if n in g]
                # max of the ends: the size of a union of byte arrays
                # (C++ cannot define a type inside sizeof: the sum bounds the max)
                if fi.cpp:
                    size = " + ".join(f"({x})" for x in dict.fromkeys(ends))
                else:
                    size = "sizeof(union { " + " ".join(
                        f"char m{i}[{x}];" for i, x in enumerate(dict.fromkeys(ends))) + " })"
                first = min(locs[n][0] for n in g)
                # members must not overlap (the C types may be larger than
                # retail's slots): a negative array size stops the build
                order = sorted(g, key=lambda n: [o for nn, m, o in ents if nn == n][0])
                chk = "".join(
                    f" typedef char {bn}_chk{i}[({pos[a]}) + sizeof({locs[a][2]}{locs[a][3]}) <= ({pos[b]}) && ({pos[a]}) >= 0 ? 1 : -1];"
                    for i, (a, b) in enumerate(zip(order, order[1:])))
                for n in sorted(g):
                    st, en, typ, dims = locs[n]
                    rep = "" if st != first else \
                        f"__attribute__((aligned(16))) unsigned char {bn}[{size}];{chk}"
                    rw.append(Rewrite(st, en, "text", rep + blank(fi.text[st:en]).replace(" ", "")[:0]
                                      + "\n" * fi.text[st:en].count("\n")))
                    ref = (f"(*({typ} (*){dims})({bn} + {pos[n]}))" if dims
                           else f"(*({typ} *)({bn} + {pos[n]}))")
                    for m in re.finditer(r"(?<![\w.>])\b%s\b" % re.escape(n), code[en:body_b]):
                        a = en + m.start()
                        prev = code[max(body_a, a - 2):a].rstrip()
                        if prev.endswith(".") or prev.endswith("->"):
                            continue
                        rw.append(Rewrite(a, a + len(n), "text", ref))
                blocked |= set(g)
                self._log(fi, d.start, d.name, "stack-block",
                          f"locals {', '.join(f'{n}@{pos[n]}' for n in sorted(g))} -> one "
                          f"16-aligned block {bn} (retail frame offsets from sp+0x{base:x}; "
                          f"callee extents {', '.join(f'{n}+0x{e:x}' for n, m, o, e in sites if n in g)})"
                          + (f"; padded slot(s) {', '.join(hex(h) for h in padded)} (written by the callee)"
                             if padded else "")
                          + (f"; {', '.join(named)} placed by their sp+0xNNN names" if named else ""))
        if pend is not None:
            self._sb_guard(fi, *pend, rw)

    # RG_PROTOS_SB_GUARD=1: the stack-guard census build (docs/PROTOS.md
    # "Stack-block census").  Every local whose address a call receives (and
    # the stage did not already place in a block) lives inside a guarded byte
    # array: 16 canary bytes before it, 48 after, checked when it goes out of
    # scope (__attribute__((cleanup))) by src/game/sbguard_census.c.  A callee
    # writing past the C object (or before it) is logged once per site.
    # Never a shipping build: it moves every such local.
    SBG_PRE, SBG_POST = 16, 48

    def _sb_guard(self, fi, d, locs, addrs, blocked, rw):
        code = fi.code
        body_a, body_b = d.body_open + 1, d.body_close
        params = {p.name for p in d.sig.params}
        for n in sorted({n for n, _m, _o in addrs} - blocked - params):
            st, en, typ, dims = locs[n]
            if self._type_size(fi, typ, dims) is None or re.search(r"\b(const|volatile)\b", typ):
                continue
            if re.search(r"\b%s\b[^;\n]*<<\s*(?:0x[2-3][0-9A-Fa-f]|3[2-9]|[4-6]\d)\b" % re.escape(n),
                         code[en:body_b]):
                continue            # dialect `wide-shift` matches the call text: keep it intact
            # dialect `arg-order` (`F(G(.., &x), x)`) matches the call text too
            if any(len(re.findall(r"\b%s\b" % re.escape(n), st_)) > 1
                   for st_ in re.findall(r"[^;{}]*&\s*%s\b[^;{}]*" % re.escape(n), code[en:body_b])):
                continue
            if re.search(r"#[ \t]*define[^\n]*\b%s\b" % re.escape(n), fi.text):
                continue            # used through a macro the rewrite cannot see
            # a nested redeclaration of the name (`{ s32 v; ..}`) would be rewritten too
            if re.search(r"\b(?:s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|short|float|double|"
                         r"long|unsigned|signed|struct\s+\w+|[A-Z]\w*)\s*\**\s+%s\s*"
                         r"(?:\[[^\]]*\]\s*)*[;=,]" % re.escape(n), code[en:body_b]):
                continue
            if fi.cpp and "*" not in typ and typ not in self._PRIM_SIZE:
                td = self._find_typedef(code, re.sub(r"^(struct|union|class)\s+", "", typ)) \
                    or self._find_typedef(getattr(self, "hdr_code", ""),
                                          re.sub(r"^(struct|union|class)\s+", "", typ))
                if not td or td[0] in ("class", "alias") or "(" in td[1]:
                    continue        # may have constructors: keep the real object
            k = fi.__dict__.setdefault("_sbg_n", [0])
            if k[0] == 0:       # one-line declarations (not every file includes game_protos.h)
                dcl = ("typedef struct rg_sbguard_site { const char *site; unsigned size; "
                       "unsigned hits; } rg_sbguard_site; int rg_sbguard_init(unsigned char *g, "
                       "rg_sbguard_site *s); void rg_sbguard_chk(void *g);")
                rw.append(Rewrite(0, 0, "text", (f'extern "C" {{ {dcl} }}' if fi.cpp else dcl) + chr(10)))
            k[0] += 1
            g = f"rgp_sbg{k[0]}"
            sz = f"sizeof({typ}{dims})"
            site = f"{fi.rel}:{d.name}:{n}".replace("\\", "/").replace('"', "")
            rw.append(Rewrite(st, en, "text",
                              f"static rg_sbguard_site {g}_s = {{\"{site}\", {sz}, 0}}; "
                              f"__attribute__((aligned(16), cleanup(rg_sbguard_chk))) unsigned char "
                              f"{g}[{self.SBG_PRE} + {sz} + {self.SBG_POST}]; "
                              f"int {g}_i = rg_sbguard_init({g}, &{g}_s);"
                              + "\n" * fi.text[st:en].count("\n")))
            ref = (f"(*({typ} (*){dims})({g} + {self.SBG_PRE}))" if dims
                   else f"(*({typ} *)({g} + {self.SBG_PRE}))")
            for m in re.finditer(r"(?<![\w.>])\b%s\b" % re.escape(n), code[en:body_b]):
                a = en + m.start()
                prev = code[max(body_a, a - 2):a].rstrip()
                if prev.endswith(".") or prev.endswith("->"):
                    continue
                rw.append(Rewrite(a, a + len(n), "text", ref))
            self._log(fi, d.start, d.name, "info-sb-guard", f"{n} ({typ}{dims}) guarded as {g}")

    def _vcall_pairs(self, fi: FileInfo, d, log=False):
        """Retail jalr sites of definition d paired in order with its C member
        calls to methods declared `virtual` in the file (counts must agree):
        (cfg, mcalls, jalrs, v0j) or None.  v0j = the jalr whose $v0 reaches
        every `jr $31`, else None."""
        img = self.image_of(fi.rel)
        code = fi.code
        r = self._listing(img, d.name)
        if not r:
            return None
        cfg = self._cfg_cache.get((img, d.name))
        if cfg is None:
            cfg = self._cfg_cache[(img, d.name)] = asmflow.CFG(r[0])
        jalrs = [i for i, (op, _o) in enumerate(cfg.ins) if op == "jalr"]
        if not jalrs:
            return None
        # C member calls to methods declared `virtual` in this file
        body_a, body_b = d.body_open + 1, d.body_close
        mcalls = []
        for m in re.finditer(r"(?:->|\.)\s*([A-Za-z_]\w*)\s*\(", code[body_a:body_b]):
            nm = m.group(1)
            lp = body_a + m.end() - 1
            decls = [x for x in re.finditer(r"\bvirtual\s+([^;{}()]*?)\b%s\s*\(" % re.escape(nm), code)
                     if fi.in_class(x.start())]
            if not decls:
                continue
            mcalls.append((body_a + m.start(), body_a + m.start(1), nm, lp, decls))
        if len(mcalls) != len(jalrs):
            if mcalls and log:
                self._log(fi, d.start, d.name, "info-vcall-unpaired",
                          f"{len(jalrs)} jalr in the listing, {len(mcalls)} virtual member "
                          f"calls in the C")
            return None
        # $v0 at the returns
        rets = [i for i, (op, o) in enumerate(cfg.ins) if op == "jr" and o and o[0] == "$31"]
        v0j = None
        if rets:
            srcs = set()
            for ri in rets:
                ds = ri + 1
                if ds < len(cfg.ins) and "$2" in asmflow.uses_defs(*cfg.ins[ds])[1]:
                    srcs.add(("insn", ds))
                else:
                    srcs |= cfg.reaching(ri, "$2")
            if len(srcs) == 1:
                s0 = next(iter(srcs))
                if s0[0] == "call" and cfg.ins[s0[1]][0] == "jalr":
                    v0j = s0[1]
        return cfg, mcalls, jalrs, v0j

    def _vcall_fwd(self, fi, d, cfg, j, ngpr, noff):
        """`vcall-forward`: the definition's parameters retail's jalr j still
        holds untouched in $a(ngpr+1).. (the C call passes ngpr GPR args)."""
        params = self.sig(d).params
        code = fi.code
        body_a = d.body_open + 1
        fwd = []
        for lane in range(ngpr + 1, 4):
            reg = "$%d" % (4 + lane)
            t = asmflow.value_at_call(cfg, j, reg)
            if not (t.kind == "entry" and t.a == reg):
                break
            if lane >= len(params) or any(p.cls != "g" for p in params[:lane + 1]) \
                    or not params[lane].name:
                break
            pn = params[lane].name
            if lane in (self._sbv_params(fi, d) or ()):
                pn = f"rgp_sbv_{pn}"      # def-struct-by-ref: the register is the pointer
            if re.search(r"\b%s\s*(?:[-+*/|&^%%]?=(?!=)|\+\+|--)|(?:\+\+|--)\s*%s\b|&\s*%s\b"
                         % ((re.escape(pn),) * 3), code[body_a:noff]):
                break
            fwd.append(pn)
        return fwd

    def _vcall_ngpr(self, code, lp, decl):
        """GPR lanes taken by the C arguments of the member call whose '(' is
        at lp, against the virtual's declaration match decl (f32 parameters
        ride $f12..; devirt passes the GPR ones first)."""
        rp = match_paren(code, lp)
        n = len([x for x in split_top(code[lp + 1:rp]) if code[lp + 1 + x[0]:lp + 1 + x[1]].strip()])
        vps = [code[decl.end() + x[0]:decl.end() + x[1]]
               for x in split_top(code[decl.end():match_paren(code, decl.end() - 1)])]
        fl = [bool(re.fullmatch(r"\s*(const\s+)?(f32|float)\b\s*\w*\s*(=.*)?", t, re.S)) for t in vps]
        return n, sum(1 for i in range(n) if not (i < len(fl) and fl[i]))

    def _vcall_widen(self):
        """Rule `vcall-widen` (before the def-widen fixpoint): a C++ definition
        whose retail virtual call receives an incoming argument register,
        untouched since entry, that the C definition never declared
        (CharaGetEquippedWeapon_3acd40: `this->slot374()` is
        CharaGetWeaponId_2f5a50(chara, slot), the slot index being
        CharaGetEquippedWeapon's own $a1) gets the parameter; its callers then
        pass what retail held (missing-* rules), and `vcall-forward` passes it
        on."""
        for fi in self.files.values():
            if not fi.cpp:
                continue
            for d in fi.defs:
                if d.is_asm or d.body_close <= d.body_open or d.sig.va or id(d) in self.tail \
                        or id(d) in self.vtail or id(d) not in self.eff \
                        or self._vthunk(d) is not None:
                    continue
                fs = self.eff[id(d)]
                if any(q.cls != "g" for q in fs.params):
                    continue
                vp = self._vcall_pairs(fi, d)
                if vp is None:
                    continue
                cfg, mcalls, jalrs, _v0j = vp
                need, via = 0, ""
                for (arrow, noff, nm, lp, decls), j in zip(mcalls, jalrs):
                    if len(decls) != 1:
                        continue
                    _n, ngpr = self._vcall_ngpr(fi.code, lp, decls[0])
                    for lane in range(ngpr + 1, 4):
                        reg = "$%d" % (4 + lane)
                        t = asmflow.value_at_call(cfg, j, reg)
                        if not (t.kind == "entry" and t.a == reg):
                            break
                        if lane + 1 > need:
                            need, via = lane + 1, nm
                added = []
                while len(fs.params) < need:
                    t = T("g", "int", "int", False, f"rgp_a{len(fs.params)}")
                    fs.params.append(t)
                    self.added[id(d)].append(t)
                    added.append(t.name)
                if added:
                    self._log(fi, d.start, d.name, "vcall-widen",
                              f"retail's jalr ({via}) receives the untouched incoming register(s) "
                              f"of {', '.join(added)}, which the C never declared -> parameter(s) added")

    # ------------------------------------------------ vtable slot float lanes
    _TABLE_RE = re.compile(r"\bu32\s+(D_[0-9A-Fa-f]+)\s*\[\d*\][^=;{]*=\s*\{(.*?)\};", re.S)

    def _vslot_lanes(self):
        """Rule `vslot-lane` (BRINGUP.md 2026-10-17 part 3).  EABI passes GPR
        and float arguments in separate register files, so `F(void *, float)`
        and `G(void *, H *, float)` share one vtable slot in retail (F never
        reads $a1).  On i686 the float is F's 2nd stack word but the slot's
        callers push (this, h, f): F read h as its float.  Families = data
        tables sharing >= 2 identical (slot, function) entries; in a family
        slot, a definition whose float parameters follow fewer GPR parameters
        than a sibling definition takes in total gets `int rgp_aN` parameters
        inserted in front of its first float (NodeRefObjUpdate_318af0,
        JudgeObjectStep_314360 next to ProjectileMoveStep_317db0: the judge
        objects' dt was the registry pointer, they never expired and the judge
        pool ran dry).  Census: tools/bringup/vslot_census.py."""
        self.lanepad: dict[int, tuple] = {}
        byid = {id(d): d for d in self.gdef.values()}
        tabs = []
        for rel in sorted(self.files):
            if "/data2c_" not in rel:
                continue
            code = self.files[rel].code
            for m in self._TABLE_RE.finditer(code):
                fns = []
                for e in m.group(2).split(","):
                    k = re.fullmatch(r"\s*\(u32\)&(\w+)\s*", e)
                    fns.append(k.group(1) if k else None)
                if sum(1 for x in fns if x) >= 2:
                    tabs.append((m.group(1), fns))
        parent = list(range(len(tabs)))

        def find(i):
            while parent[i] != i:
                parent[i] = parent[parent[i]]
                i = parent[i]
            return i
        by_pair = defaultdict(list)
        for i, (_n, fns) in enumerate(tabs):
            for s, fn in enumerate(fns):
                if fn:
                    by_pair[(s, fn)].append(i)
        shared = defaultdict(int)
        for idx in by_pair.values():
            for j in sorted(set(idx[1:]) - {idx[0]}):
                shared[(idx[0], j)] += 1
        for (i, j), n in shared.items():
            if n >= 2:
                parent[find(i)] = find(j)
        fam = defaultdict(list)
        for i in range(len(tabs)):
            fam[find(i)].append(i)

        def shape(ps):
            pre, g, nf = 0, 0, 0
            for p in ps:
                if p.cls == "f":
                    nf += 1
                elif p.cls == "g":
                    g += 1
                    if not nf:
                        pre += 1
            return pre, g, nf
        for members in fam.values():
            slots = defaultdict(set)
            for i in members:
                for s, fn in enumerate(tabs[i][1]):
                    d = self.gdef.get(fn) if fn else None
                    if d is not None and id(d) in self.eff and not d.is_asm:
                        slots[s].add(id(d))
            for s, ids in sorted(slots.items()):
                if len(ids) < 2:
                    continue
                defs = {i: byid[i] for i in ids}
                if any(self.eff[i].va or any(p.cls == "x" for p in self.eff[i].params) for i in ids):
                    continue
                sh = {i: shape(self.eff[i].params) for i in ids}
                gmax = max(g for _p, g, _f in sh.values())
                sib = next(defs[i].name for i in sorted(ids, key=lambda i: defs[i].name)
                           if sh[i][1] == gmax)
                for i in sorted(ids, key=lambda i: defs[i].name):
                    pre, g, nf = sh[i]
                    if not nf or pre >= gmax or i in self.lanepad:
                        continue
                    d = defs[i]
                    fi = self.files[d.rel]
                    if self.wparams.get(i) or self.dparams.get(i) or self.added.get(i) \
                            or g != pre:
                        self._log(fi, d.start, d.name, "manual-vslot-lane",
                                  f"slot {s}: floats after {pre} GPR, {sib} takes {gmax}")
                        continue
                    fs = self.eff[i]
                    at = next(k for k, p in enumerate(fs.params) if p.cls == "f")
                    new = [T("g", "int", "int", False, f"rgp_a{pre + n}") for n in range(gmax - pre)]
                    fs.params[at:at] = new
                    self.lanepad[i] = (at, new)
                    self._log(fi, d.start, d.name, "vslot-lane",
                              f"slot {s} of {','.join(sorted(tabs[m][0] for m in members))}: "
                              f"floats after {pre} GPR, sibling {sib} takes {gmax}: "
                              f"inserted {', '.join('int ' + t.name for t in new)}")

    def _lanepad_params(self, d, params: str) -> str:
        """The definition's parameter text with the vslot-lane GPR pads inserted."""
        lp = self.lanepad.get(id(d))
        if not lp:
            return params
        at, new = lp
        parts = [params[a:b].strip() for a, b in split_top(params)] if params.strip() not in ("", "void") else []
        parts[at:at] = [f"int {t.name}" for t in new]
        return ", ".join(parts)

    # ------------------------------------------------ vcall passthrough
    def _vcall_passthrough(self, fi: FileInfo, rw: list) -> None:
        """Rules `vcall-forward` and `def-vcall-v0` (ModelMeshGetGroupPkts class).

        Retail's listing is the truth for a C++ definition's virtual calls
        (`jalr`), paired with the C member calls to virtuals in textual order
        when the counts agree:

          * `vcall-forward`: at the jalr, $a(n+1).. still hold the definition's
            incoming registers (asmflow ENTRY) where the C call passes only n
            GPR arguments after `this`: the callee received them.  The call
            gets the definition's parameters appended (unassigned before the
            call in the C), and the virtual's declaration (once in the file)
            gets `int rgp_fwdK = 0` parameters for them (other calls pass 0).
          * `def-vcall-v0`: $v0 at every `jr $31` is that jalr's result, and
            the C definition is void: retail returns the virtual's value
            (ModelQueueSortedPackets_14f0d0 adds the mesh slot-0x18 result to
            its packet cursor).  The call becomes `rgp_v0 = obj->m(..);`, the
            definition returns rgp_v0 (typed as the virtual; a void virtual
            declared once in the file is typed int).
        Only top-level statement calls are rewritten; the rest is logged
        `manual-vcall-*`.  Definitions owned by def-tail-(v)call-return and
        def-vthunk-naked are left to those rules."""
        if not fi.cpp:
            return
        img = self.image_of(fi.rel)
        code = fi.code
        vadded: dict = {}      # virtual decl offset -> forwarded params added
        vretyped: set = set()  # virtual decl offsets retyped void -> int
        for d in fi.defs:
            if d.is_asm or d.body_close <= d.body_open or id(d) in self.tail \
                    or id(d) in self.vtail or self._vthunk(d) is not None:
                continue
            vp = self._vcall_pairs(fi, d, log=True)
            if vp is None:
                continue
            cfg, mcalls, jalrs, v0j = vp
            body_a, body_b = d.body_open + 1, d.body_close
            params = self.sig(d).params
            for (arrow, noff, nm, lp, decls), j in zip(mcalls, jalrs):
                rp = match_paren(code, lp)
                args = [x for x in split_top(code[lp + 1:rp]) if code[lp + 1 + x[0]:lp + 1 + x[1]].strip()]
                vd = decls[0]
                # ---- forwarded argument registers
                n = len(args)
                # GPR lanes taken by the C arguments (f32 parameters ride $f12..;
                # devirt passes the GPR ones first, `lane_reordered`)
                vps = [code[vd.end() + x[0]:vd.end() + x[1]]
                       for x in split_top(code[vd.end():match_paren(code, vd.end() - 1)])]
                fl = [bool(re.fullmatch(r"\s*(const\s+)?(f32|float)\b\s*\w*\s*(=.*)?", t, re.S)) for t in vps]
                ngpr = sum(1 for i in range(n) if not (i < len(fl) and fl[i]))
                fwd = self._vcall_fwd(fi, d, cfg, j, ngpr, noff)
                if fwd:
                    if len(decls) != 1:
                        self._log(fi, noff, nm, "manual-vcall-forward",
                                  f"{d.name}: retail passes entry {', '.join(fwd)} to the virtual; "
                                  f"{nm} is declared {len(decls)} times in the file")
                    else:
                        vlp = vd.end() - 1
                        vrp = match_paren(code, vlp)
                        cur = code[vlp + 1:vrp].strip()
                        have = 0 if cur in ("", "void") else len(split_top(cur))
                        have0, have = have, have + vadded.get(vd.start(), 0)
                        if have > n + len(fwd) or (have > n and vadded.get(vd.start(), 0) == 0):
                            self._log(fi, noff, nm, "manual-vcall-forward",
                                      f"{d.name}: the call passes {n} of {nm}'s {have} parameters")
                        else:
                            extra = ", ".join(f"int rgp_fwd{n + 1 + k} = 0" for k in range(have - n, len(fwd)))
                            if extra:
                                vadded[vd.start()] = vadded.get(vd.start(), 0) + (len(fwd) - (have - n))
                                if cur in ("", "void") and have == 0:
                                    rw.append(Rewrite(vlp + 1, vrp, "text", extra))
                                else:
                                    rw.append(Rewrite(vrp, vrp, "text", ", " + extra))
                            rw.append(Rewrite(rp, rp, "text",
                                              ("" if n == 0 else ", ") +
                                              ", ".join(f"(int)(long)({x})" for x in fwd)))
                            self._log(fi, noff, nm, "vcall-forward",
                                      f"{d.name}: retail's jalr gets the untouched entry "
                                      f"register(s) of {', '.join(fwd)} -> passed")
                # ---- census: further argument registers retail sets before the
                # jalr that the C does not pass (DataTableOwnerLoadResidentBin_3b8b70:
                # `p3 & 1` and a status byte); not rewritten, listed for review
                more = []
                for lane in range(ngpr + 1 + len(fwd), 8):
                    reg = "$%d" % (4 + lane)
                    t = asmflow.value_at_call(cfg, j, reg)
                    if t.kind in ("clobber", "phi", "ret") or asmflow.has_clobber(t) \
                            or (t.kind == "other" and "entry" in str(t.a)):
                        break
                    if t.kind == "entry":
                        break
                    more.append(f"{reg}={t}")
                if more:
                    self._log(fi, noff, nm, "info-vcall-set-args",
                              f"{d.name}: retail's jalr also gets {', '.join(more)} "
                              f"(the C passes {ngpr} GPR argument(s) after this)")
                # ---- surviving $v0
                if j != v0j or d.sig.ret.cls != "v":
                    continue
                if any(dc.name == d.name for dc in fi.decls):
                    self._log(fi, noff, nm, "manual-vcall-v0",
                              f"{d.name}: retail returns {nm}'s $v0; the file also declares "
                              f"{d.name} (void)")
                    continue
                vret = " ".join(vd.group(1).split())
                if len({" ".join(x.group(1).split()) for x in decls}) != 1:
                    self._log(fi, noff, nm, "manual-vcall-v0",
                              f"{d.name}: retail returns {nm}'s $v0; {nm} is declared with "
                              f"different returns in the file")
                    continue
                if vret == "void":
                    if len(decls) != 1:
                        self._log(fi, noff, nm, "manual-vcall-v0",
                                  f"{d.name}: retail returns {nm}'s $v0; void {nm} declared "
                                  f"{len(decls)} times")
                        continue
                    if vd.start() not in vretyped:
                        vretyped.add(vd.start())
                        va = vd.start(1)
                        vrel = code[va:vd.end(1)]
                        k = vrel.find("void")
                        rw.append(Rewrite(va + k, va + k + 4, "text", "int"))
                    vret = "int"
                elif re.search(r"\b(f32|float|double|f64)\b", vret) and "*" not in vret:
                    continue
                # the call must be a whole top-level statement `obj->m(..);`
                k = arrow - 1
                dep = 0
                while k > d.body_open:
                    ch = code[k]
                    if ch in ")]":
                        dep += 1
                    elif ch in "([":
                        dep -= 1
                    elif dep == 0 and ch in ";{}":
                        break
                    k -= 1
                stmt = k + 1
                while code[stmt] in " \t\r\n":
                    stmt += 1
                after = rp + 1
                while code[after] in " \t\r\n":
                    after += 1
                seg = code[d.body_open:stmt]
                if code[after] != ";" or "=" in code[stmt:arrow] or code[k] not in ";{}" \
                        or seg.count("{") - seg.count("}") != 1 \
                        or re.search(r"\b(return|if|while|for|switch)\b", code[stmt:arrow]):
                    self._log(fi, noff, nm, "manual-vcall-v0",
                              f"{d.name}: retail returns {nm}'s $v0, the call is not a "
                              f"top-level statement")
                    continue
                a, b = self._ret_span(fi, d)
                rt = vret
                rw.append(Rewrite(a, b, "text", rt))
                rw.append(Rewrite(d.body_open + 1, d.body_open + 1, "text", f" {rt} rgp_v0;"))
                rw.append(Rewrite(stmt, stmt, "text", "rgp_v0 = "))
                for m in re.finditer(r"\breturn\s*;", code[body_a:body_b]):
                    rw.append(Rewrite(body_a + m.start(), body_a + m.end(), "text", "return rgp_v0;"))
                rw.append(Rewrite(d.body_close, d.body_close, "text", "return rgp_v0; "))
                self._log(fi, noff, nm, "def-vcall-v0",
                          f"{d.name}: $v0 at every return is the result of `{nm}` (retail "
                          f"jalr, nothing after it writes $v0) -> definition returns it ({rt})")

    def _plan_file(self, fi: FileInfo) -> bytes:
        rw: list[Rewrite] = []
        cpp = fi.cpp
        # C: header symbols this file must keep its own view of -- data views
        # of a code symbol, and callees passed a struct/128-bit by value
        keep_local = set()
        if not cpp:
            keep_local = {n for n in fi.objdecls if n in self.gdef and
                          self.in_header(self.gdef[n])}
            for c in fi.calls:
                d = self.resolve(fi, c.name)
                if (d is not None and d.rel != fi.rel and self.in_header(d)
                        and self._xview(fi, c)):
                    keep_local.add(c.name)
            # the same for a local DECLARATION with a struct/128-bit by value
            # whose calls the scan cannot see (inside a macro body, e.g.
            # StringVectorInsert_1a6240's CONSTRUCT passing Alloc6240)
            for dc in fi.decls:
                d = self.resolve(fi, dc.name)
                if (d is not None and d.rel != fi.rel and self.in_header(d) and not dc.sig.unproto
                        and (dc.sig.ret.cls == "x" or any(p.cls == "x" for p in dc.sig.params))):
                    keep_local.add(dc.name)
            # a name the header declares, but this file binds to ANOTHER
            # definition (same-image duplicate): keep the local view
            for n in {dc.name for dc in fi.decls} | {c.name for c in fi.calls}:
                g = self.gdef.get(n)
                d = self.resolve(fi, n)
                if (g is not None and self.in_header(g) and d is not None and d is not g
                        and d.rel != fi.rel):
                    keep_local.add(n)
        self.keep_local = keep_local
        self_names = sorted({d.name for d in fi.defs} | keep_local)
        self._vararg_narrow(fi, rw)
        self._vararg_missing(fi, rw)
        # ---- value definitions with `G(..); return;`: retail returns G's $v0/$f0
        for d in fi.defs:
            if d.is_asm:
                continue
            dret = self.sig(d).ret
            if dret.cls not in ("g", "f"):
                continue
            if isinstance((self.tail.get(id(d)) or (None, None))[1], V0Tail):
                continue        # def-v0-return rewrites its own returns
            for m in re.finditer(r"\breturn\s*;", fi.code[d.body_open:d.body_close]):
                ra = d.body_open + m.start()
                rb = d.body_open + m.end()
                c = self._bare_return_call(fi, d, ra)
                if c is None:
                    mb = self._bare_return_member(fi, d, ra, dret.cls)
                    if mb is not None:
                        stmt, mname = mb
                        a, b = self._ret_span(fi, d)
                        rw.append(Rewrite(stmt, stmt, "text",
                                          f"return ({fi.code[a:b].strip()})"))
                        rw.append(Rewrite(ra, rb, "text", ""))
                        self._log(fi, stmt, d.name, "def-bare-return",
                                  f"`obj->{mname}(..); return;` (member call through VCM) in "
                                  f"{d.name} (returns {dret.c}): retail tail-returns the "
                                  f"virtual's value -> `return obj->{mname}(..);`")
                        continue
                    self._log(fi, ra, d.name, "info-bare-return",
                              "value def has a bare `return;` with no call before it "
                              "(retail returns whatever $v0/$f0 held)")
                    continue
                g = self.resolve(fi, c.name)
                gs = self.sig(g) if g is not None else self.view(fi, c)[0]
                if gs is None or gs.ret.cls != dret.cls:
                    self._log(fi, ra, c.name, "info-bare-return",
                              f"value def has `{c.name}(..); return;` but {c.name} does not "
                              f"return a {dret.cls} value")
                    continue
                a, b = self._ret_span(fi, d)
                rw.append(Rewrite(c.start, c.start, "text",
                                  f"return ({fi.code[a:b].strip()})"))
                rw.append(Rewrite(ra, rb, "text", ""))
                self._log(fi, c.start, c.name, "def-bare-return",
                          f"`{c.name}(..); return;` in {d.name} (returns {dret.c}): retail "
                          f"returns {c.name}'s value -> `return {c.name}(..);`")
        # ---- value definitions that fall off their end right after `G(..);`
        # (-Wreturn-type census, out/bringup-checkpoint/returntype-census.tsv):
        # retail returns G's $v0/$f0 (EvTargetPointInVolumes_3527a0 ends in
        # `EventVolumeRecAnyHitRideAllowed_2e4b50(p2, &v20);`, its result is the
        # function's).  Rule `def-fallthrough-return`.
        for d in fi.defs:
            if d.is_asm or d.body_close <= d.body_open:
                continue
            dret = self.sig(d).ret
            if dret.cls not in ("g", "f") or d.sig.ret.cls not in ("g", "f") \
                    or self.tail.get(id(d)) is not None:
                continue        # void defs retyped by def-tail-return are that rule's
            ra = d.body_close
            c = self._bare_return_call(fi, d, ra)
            a, b = self._ret_span(fi, d)
            if c is not None:
                g = self.resolve(fi, c.name)
                gs = self.sig(g) if g is not None else self.view(fi, c)[0]
                if gs is None or gs.ret.cls != dret.cls:
                    self._log(fi, c.start, d.name, "info-fallthrough-return",
                              f"value def falls off its end after `{c.name}(..);`, which "
                              f"does not return a {dret.cls} value")
                    continue
                rw.append(Rewrite(c.start, c.start, "text", f"return ({fi.code[a:b].strip()})"))
                self._log(fi, c.start, c.name, "def-fallthrough-return",
                          f"{d.name} (returns {dret.c}) falls off its end after `{c.name}(..);`:"
                          f" retail returns its value -> `return {c.name}(..);`")
                continue
            mb = self._bare_return_member(fi, d, ra, dret.cls)
            if mb is not None:
                rw.append(Rewrite(mb[0], mb[0], "text", f"return ({fi.code[a:b].strip()})"))
                self._log(fi, mb[0], d.name, "def-fallthrough-return",
                          f"{d.name} falls off its end after `obj->{mb[1]}(..);` -> returned")
        # ---- virtual calls: forwarded argument registers and a surviving $v0
        import time as _t
        _t0 = _t.perf_counter()
        if not os.environ.get('RG_PROTOS_NO_VCALL'):
            self._vcall_passthrough(fi, rw)
        _t1 = _t.perf_counter()
        # ---- split locals retail keeps as one stack block
        if not os.environ.get('RG_PROTOS_NO_STACKBLOCK'):
            self._stack_blocks(fi, rw)
        # ---- EE FPU rounding tricks (round toward zero only)
        if not os.environ.get('RG_PROTOS_NO_EEROUND'):
            self._ee_round(fi, rw)
        self._tm["vcall"] = self._tm.get("vcall", 0) + _t1 - _t0
        self._tm["stack"] = self._tm.get("stack", 0) + _t.perf_counter() - _t1
        # ---- definitions: tail-return and widening rewrites
        for d in fi.defs:
            t = self.tail.get(id(d))
            if t is not None and t[1] is None:      # virtual-call tail
                stmt, (ma, mb), gret = self.vtail[id(d)]
                a, b = self._ret_span(fi, d)
                tt = "void *" if gret.ptr else gret.c
                rw.append(Rewrite(a, b, "text", tt))
                rw.append(Rewrite(stmt, stmt, "text", "return "))
                rw.append(Rewrite(ma, mb, "text", tt))
                self._log(fi, d.start, d.name, "def-tail-vcall-return",
                          f"void def ends in a virtual call; retail returns its $v0/$f0: "
                          f"method and def typed {tt} ({len(self.used_from_void[d.name])} "
                          f"caller(s) use the value)")
            elif t is not None and isinstance(t[1], V0Tail):
                self._v0_rewrite(fi, d, t[1], t[2], rw)
            elif t is not None:
                _, tc, gret = t
                a, b = self._ret_span(fi, d)
                rw.append(Rewrite(a, b, "text", "void *" if gret.ptr else gret.c))
                n = len(self.used_from_void[d.name])
                if d.sig.ret.cls == "v":
                    rw.append(Rewrite(tc.start, tc.start, "text", "return "))
                    self._log(fi, d.start, d.name, "def-tail-return",
                              f"void def ends in {tc.name}() returning {gret.c}; "
                              f"{n} caller(s) use the value")
                else:
                    self._log(fi, d.start, d.name, "def-tail-retype",
                              f"{d.sig.ret.c} def returns {tc.name}() which returns "
                              f"{gret.c}; {n} caller(s) read {gret.c}")
            vt = self._vthunk(d)
            if (vt is not None and id(d) not in self.tail and id(d) not in self.vtail
                    and self.sig(d).ret.cls != "x"):
                voff, soff = vt
                rw.append(Rewrite(d.name_off, d.name_off, "text", "__attribute__((naked)) "))
                rw.append(Rewrite(d.body_open + 1, d.body_close, "text",
                                  f' __asm__ volatile("movl 4(%esp), %eax\\n\\t"'
                                  f' "movl {voff}(%eax), %eax\\n\\t" "jmp *{soff}(%eax)"); '
                                  + "\n" * fi.text[d.body_open + 1:d.body_close].count("\n")))
                self._log(fi, d.start, d.name, "def-vthunk-naked",
                          f"retail is a bare virtual tail jump (lw $25,{voff:#x}($4); "
                          f"lw $25,{soff:#x}($25); jr $25): every argument register and the "
                          f"return value pass through -> naked i686 forwarder (cdecl stack "
                          f"arguments and EAX/ST0 pass through the same way)")
            sbv = [] if vt is not None else self._sbv_params(fi, d)
            if sbv:
                spans = split_top(fi.code[d.lparen + 1:d.rparen])
                copies = []
                for k in sbv:
                    pa, pb = spans[k]
                    typ, nm = split_param(fi.code[d.lparen + 1 + pa:d.lparen + 1 + pb])
                    lead = " " if pa else ""
                    rw.append(Rewrite(d.lparen + 1 + pa, d.lparen + 1 + pb, "text",
                                      f"{lead}{typ} *rgp_sbv_{nm}"))
                    copies.append(f" {typ} {nm} = *rgp_sbv_{nm};")
                rw.append(Rewrite(d.body_open + 1, d.body_open + 1, "text", "".join(copies)))
                self._log(fi, d.start, d.name, "def-struct-by-ref",
                          "struct parameter(s) " + ", ".join(d.sig.params[k].name for k in sbv)
                          + ": retail's callee copies the aggregate from the address in its "
                          "argument register (callers pass a pointer) -> pointer + local copy")
            if self.dparams.get(id(d)):
                spans = split_top(fi.code[d.lparen + 1:d.rparen])
                for k in sorted(self.dparams[id(d)]):
                    pa, pb = spans[k]
                    nm = self.eff[id(d)].params[k].name
                    rw.append(Rewrite(d.lparen + 1 + pa, d.lparen + 1 + pb, "text",
                                      (" " if pa else "") + f"double {nm}"))
            if id(d) in self.wrets and id(d) not in self.tail:
                a, b = self._ret_span(fi, d)
                rw.append(Rewrite(a, b, "text", self.wrets[id(d)]))
            if self.wparams.get(id(d)):
                spans = split_top(fi.code[d.lparen + 1:d.rparen])
                for k, ct in sorted(self.wparams[id(d)].items()):
                    pa, pb = spans[k]
                    nm = self.eff[id(d)].params[k].name
                    rw.append(Rewrite(d.lparen + 1 + pa, d.lparen + 1 + pb, "text",
                                      (" " if pa else "") + f"{ct} {nm}"))
            if id(d) in self.unstatic:
                for m in re.finditer(r"\bstatic\b\s*", fi.code[d.start:d.name_off]):
                    rw.append(Rewrite(d.start + m.start(), d.start + m.end(), "text", ""))
            lp = self.lanepad.get(id(d))
            if lp:
                spans = split_top(fi.code[d.lparen + 1:d.rparen])
                at, new = lp
                pa = spans[at][0]
                rw.append(Rewrite(d.lparen + 1 + pa, d.lparen + 1 + pa, "text",
                                  (" " if pa else "") + ", ".join(f"int {t.name}" for t in new)
                                  + ("," if pa else ", ")))
            add = self.added.get(id(d))
            if add:
                cur = fi.code[d.lparen + 1:d.rparen].strip()
                new = ", ".join(f"{p.c} {p.name}" if not p.c.endswith("*") else f"{p.c}{p.name}"
                                for p in add)
                txt = new if cur in ("", "void") else None
                if txt is None:
                    rw.append(Rewrite(d.rparen, d.rparen, "text", ", " + new))
                else:
                    rw.append(Rewrite(d.lparen + 1, d.rparen, "text", txt))
                self._log(fi, d.start, d.name, "def-widen",
                          f"first call passes incoming register(s) through: added {new}")
        for a, e, txt in self.dlocals.get(fi.rel, ()):
            nl = fi.text[a:e].count("\n")
            rw.append(Rewrite(a, e, "text", txt + "\n" * nl))
        for a, (e, txt) in sorted(self.wlocals.get(fi.rel, {}).items()):
            nl = fi.text[a:e].count("\n")
            rw.append(Rewrite(a, e, "text", txt + "\n" * nl))
        # ---- struct returns spelled by value against an out-pointer definition
        sret_calls, sret_decls = self._sret_sites(fi, rw)
        # ---- short local views of a callee kept out of the header by a word-size
        #      aggregate parameter (rule `short-agg`)
        sa_calls, sa_decls = self._short_agg_sites(fi, rw)
        sret_calls |= sa_calls
        sret_decls |= sa_decls
        # ---- declarations
        called = {c.name for c in fi.calls}
        for d in fi.defs:
            if id(d) in self.tail or self.added.get(id(d)) or id(d) in self.wrets \
                    or id(d) in self.lanepad:
                self._changed[fi.rel].add(d.name)
        ok_decl = set()     # C++: decls whose post-stage shape == definition
        for dc in fi.decls:
            if id(dc) in sret_decls:
                continue
            d = self.resolve(fi, dc.name)
            if d is None:
                continue
            ds = self.sig(d)
            own = d.rel == fi.rel
            nl = "\n" * fi.text[dc.start:dc.end].count("\n")
            if own:
                if self._same_sig(dc.sig, ds) and id(d) not in self.added \
                        and id(d) not in self.lanepad and id(d) not in self.tail and not (dc.static and id(d) in self.unstatic):
                    continue
                rw.append(Rewrite(dc.start, dc.end, "text", self._self_proto(fi, d) + ";" + nl))
                ok_decl.add(id(dc))
                self._log(fi, dc.start, dc.name, "decl-replaced-self", dc.text)
                continue
            abi = self._abi_diff(dc.sig, ds)
            if not cpp and dc.name not in self.local_names:
                if self.in_header(d) and dc.name not in keep_local:
                    rw.append(Rewrite(dc.start, dc.end, "text", "/*rgp*/" + nl))
                    self.stats["decl-removed"] += 1
                    if abi:
                        self._log(fi, dc.start, dc.name, "decl-removed", f"{abi}: {dc.text}")
                elif abi:
                    self._log(fi, dc.start, dc.name, "manual-decl",
                              f"{abi}; not in header ({self._why_not(d)}): {dc.text}")
                continue
            force = dc.name in self._force_ret.get(fi.rel, ())
            if not abi and not force:
                ok_decl.add(id(dc))
                continue
            if not force and dc.name not in called:
                continue     # address-only use: nothing to fix, keep its type
            new = self._patch_decl(fi, dc, d)
            if new is None:
                self._log(fi, dc.start, dc.name, "manual-decl", f"{abi}: {dc.text}")
                continue
            rw.append(Rewrite(dc.start, dc.end, "text", new))
            ok_decl.add(id(dc))
            self._changed[fi.rel].add(dc.name)
            self._log(fi, dc.start, dc.name, "decl-patched",
                      f"{abi}: {dc.text} -> {' '.join(new.split())}")
        # ---- calls
        # a double-returning call written straight as the argument of a double
        # parameter: retail moved the 64-bit register as is (no narrowing), so
        # neither side converts (`self._dtrans` = inner call starts)
        self._dtrans = set()
        callat = {(c.start, c.rparen + 1): c for c in fi.calls}
        for c in fi.calls:
            d = self.resolve(fi, c.name)
            if d is None or id(d) not in self.eff:
                continue
            mp = self._map(fi, c, d)
            if mp is None:
                continue
            for x, p in zip(mp[0], self.sig(d).params):
                if x[0] != "arg" or p.kind not in ("d", "q"):
                    continue
                c2 = callat.get(tuple(c.args[x[1]]))
                d2 = self.resolve(fi, c2.name) if c2 is not None else None
                if d2 is not None and id(d2) in self.eff and self.sig(d2).ret.kind == "d":
                    self._dtrans.add(c2.start)
        for c in fi.calls:
            if c.start in sret_calls:
                continue
            d = self.resolve(fi, c.name)
            if d is None:
                continue
            vs, vsrc = self.view(fi, c)
            if d.rel == fi.rel:
                ok = True
            elif not cpp and c.name not in self.local_names:
                ok = self.in_header(d) and c.name not in keep_local
            else:
                ok = isinstance(vsrc, Decl) and id(vsrc) in ok_decl
            r = self._plan_call(fi, c, d, vs, ok)
            if r is not None:
                rw.append(r)
        # entry copies for missing-entry arguments: `__typeof__(p) rgp_entry_p = p;`
        # first thing in the body (before the parameter is modified)
        for d in fi.defs:
            for nm in sorted(self.entry_copies.get(id(d), {})):
                rw.append(Rewrite(d.body_open + 1, d.body_open + 1, "text",
                                  f" __typeof__({nm}) rgp_entry_{nm} = {nm};"))
        # ---- assemble
        text = fi.text
        body = render(text, 0, len(text),
                      sorted(rw, key=lambda r: (r.start, r.end > r.start, -r.end)))
        if not cpp:
            pre = [MARK]
            for n in self_names:
                pre.append(f"#define RGP_SELF_{n} 1")
            pre.append('#include "port/game_protos.h"')
            pre.append("#line 1")
            body = "\n".join(pre) + "\n" + body
        elif rw or fi.rel in self.renamed_files:
            body = MARK + "\n#line 1\n" + body
        return body.encode("latin-1")

    def _sret_sites(self, fi, rw):
        """`R F(a..)` declared by the caller (R a struct by value) against a
        definition `void F(R *out, a..)`: the EE returns a struct through a
        hidden pointer in $a0, which IS the definition's first parameter
        (TextStyleGetRgba_26f2a0 from FontDrawText_26cdc0).  i686/MSVC returns
        structs of <= 8 bytes in EDX:EAX instead, so the call is spelled out:
        `({ R rgp_sret; F(&rgp_sret, a..); rgp_sret; })` and the caller's
        declaration becomes `void F(void *, ..)` (rule `sret-call`).
        -> (call starts, decl ids) handled."""
        calls, decls = set(), set()
        for c in fi.calls:
            d = self.resolve(fi, c.name)
            if d is None or id(d) not in self.eff:
                continue
            vs, vsrc = self.view(fi, c)
            if vs is None or not isinstance(vsrc, Decl) or vs.unproto or vs.va:
                continue
            ds = self.sig(d)
            if vs.ret.cls != "x" or ds.ret.cls != "v" or ds.va:
                continue
            if len(ds.params) != len(vs.params) + 1 or not ds.params[0].ptr:
                continue
            if any(p.cls == "x" for p in ds.params) or \
                    [p.cls for p in ds.params[1:]] != [p.cls for p in vs.params]:
                continue
            if len(c.args) != len(vs.params):
                continue
            rtype = vs.ret.raw.strip()
            if not re.fullmatch(r"(?:struct\s+|union\s+)?[A-Za-z_]\w*", rtype):
                continue
            # a call rewrite (arguments rendered with their own nested
            # rewrites, cast to the definition's parameter types) wrapped by
            # two insertions
            ptr = T("g", "void *", "void *", True)
            newargs = [("name", ("&rgp_sret", ptr))] + \
                [("cast", (i, p.c)) for i, p in enumerate(ds.params[1:])]
            rw.append(Rewrite(c.start, c.start, "text", f"({{ {rtype} rgp_sret; "))
            rw.append(Rewrite(c.start, c.rparen + 1, "call", call=c, newargs=newargs, keep=[]))
            rw.append(Rewrite(c.rparen + 1, c.rparen + 1, "text", "; rgp_sret; })"))
            calls.add(c.start)
            if id(vsrc) not in decls:
                decls.add(id(vsrc))
                nl = "\n" * fi.text[vsrc.start:vsrc.end].count("\n")
                ps = ", ".join(p.c for p in ds.params)
                link = 'extern "C" ' if (fi.cpp and vsrc.clink and vsrc.func is None
                                         and not fi.in_externc(vsrc.start)) else ""
                rw.append(Rewrite(vsrc.start, vsrc.end, "text",
                                  f"{link}void {c.name}({ps});{nl}"))
            self._log(fi, c.start, c.name, "sret-call",
                      f"caller returns {rtype} by value; definition takes the out pointer "
                      f"first ({d.rel}): spelled as an explicit out pointer")
        return calls, decls

    def _short_agg_sites(self, fi, rw):
        """Rule `short-agg` (2026-10-25, BRINGUP-HISTORY "2026-10-25 (sweep)"): a C file's
        local declaration that is SHORT of a definition kept out of game_protos.h only
        because it takes a word-size aggregate by value (`HandleTableGet_1a1d50(Table *,
        Handle h)`, Handle a 4-byte union).  On the EE such an aggregate is one GPR, on
        i686 one 4-byte stack slot: an `int` slot either way.  The declaration gets the
        missing slots (`int` for the aggregate, the definition's builtin spelling
        otherwise) and every call the missing arguments, chosen exactly as for a header
        callee (MISSING_ARG_ASM, passthrough, the retail entry value, the listing, else
        0).  Without it the callee read a stale stack word: EffTableDestroyAll_1a0240
        spun forever at the Insectron return to title (BRINGUP-HISTORY 2026-10-25 (stream
        close)).  Switch RG_PROTOS_NO_SHORTAGG.  -> (call starts, decl ids) handled."""
        calls, decls = set(), set()
        if fi.cpp or os.environ.get("RG_PROTOS_NO_SHORTAGG"):
            return calls, decls
        bydecl: dict = {}
        for c in fi.calls:
            d = self.resolve(fi, c.name)
            if d is None or id(d) not in self.eff or d.rel == fi.rel or self.in_header(d):
                continue
            vs, vsrc = self.view(fi, c)
            if vs is None or not isinstance(vsrc, Decl) or vs.unproto or vs.va:
                continue
            bydecl.setdefault(id(vsrc), (vsrc, d, []))[2].append(c)
        for dc, d, cl in bydecl.values():
            ds, vs = self.sig(d), dc.sig
            if ds.va or ds.ret.cls == "x" or vs.ret.cls == "x" or len(vs.params) >= len(ds.params):
                continue
            if vs.ret.cls not in ("v", ds.ret.cls) or dc.rparen <= dc.lparen:
                continue
            df = self.files.get(d.rel)
            slots = []
            for p in ds.params:
                if p.cls == "x":
                    sz = self._type_size(df, p.raw, "") if df is not None else None
                    if sz is None or sz[0] > 4 or re.search(r"\b(u128|s128|__int128)\b", p.raw):
                        slots = None
                        break
                    p = T("g", "int", "int", False, p.name)     # a word-size aggregate
                slots.append(p)
            if slots is None or any(q.cls == "x" for q in vs.params):
                continue
            if [q.cls for q in vs.params] != [q.cls for q in slots[:len(vs.params)]]:
                continue
            if any(len(c.args) != len(vs.params) for c in cl):
                continue
            encl = [self._encl_def(fi, c) for c in cl]
            if any(F is None or any(q.cls == "x" for q in self.sig(F).params) for F in encl):
                continue      # passthrough lanes count GPR / FPR parameters only
            miss = slots[len(vs.params):]
            plans = []
            for c in cl:
                fill = [("arg", i) for i in range(len(c.args))]
                lanes = {"g": 0, "f": 0}
                for q in slots[:len(vs.params)]:
                    lanes["f" if q.cls == "f" else "g"] += 1
                how = []
                for p in miss:
                    cls = "f" if p.cls == "f" else "g"
                    k = lanes[cls]
                    lanes[cls] += 1
                    man = self._missing_asm(fi, c, cls, k)
                    nm = None if man else self._passthrough(fi, c, cls, k)
                    ent = None if (nm or man) else self._entry_value(fi, c, cls, k)
                    if man:
                        fill.append(("name", (f"({man})", p)))
                        how.append(f"{cls}{k} = {man} (MISSING_ARG_ASM)")
                    elif nm:
                        fill.append(("name", (nm, p)))
                        how.append(f"{cls}{k} = {nm} (passthrough)")
                    elif ent:
                        fill.append(("name", (ent, p)))
                        how.append(f"{cls}{k} = {ent} (retail entry value)")
                    else:
                        rule, expr, why = self._missing_value(fi, c, d, cls, k)
                        if expr is None and rule != "missing-unused":
                            # a value the listing cannot name (NumPutDoubleThunk_1b2840's
                            # entry $a2..$t0 with no parameter to pass): no guess, the site
                            # stays manual for an override (tools/bringup/protos_deficits.py)
                            fill = None
                            break
                        fill.append(("name", (f"({expr})", p)) if expr is not None else ("zero", p))
                        how.append(f"{cls}{k} {rule}: {why}")
                if fill is None:
                    plans = None
                    break
                plans.append((c, fill, how))
            if plans is None:
                continue
            for c, fill, how in plans:
                rw.append(Rewrite(c.start, c.rparen + 1, "call", call=c, newargs=fill, keep=[]))
                calls.add(c.start)
                self._log(fi, c.start, c.name, "short-agg-call",
                          f"{len(c.args)} args -> def {len(ds.params)} ({d.rel}); " + "; ".join(how))
            cur = fi.code[dc.lparen + 1:dc.rparen].strip()
            add = ", ".join(p.c for p in miss)
            if cur in ("", "void"):
                rw.append(Rewrite(dc.lparen + 1, dc.rparen, "text", add))
            else:
                rw.append(Rewrite(dc.rparen, dc.rparen, "text", ", " + add))
            decls.add(id(dc))
            self._log(fi, dc.start, dc.name, "short-agg-decl",
                      f"view {len(vs.params)} of {len(ds.params)} params; added {add} "
                      f"(word-size aggregate = one int slot): {dc.text}")
        return calls, decls

    def _why_not(self, d: Def) -> str:
        if d.static:
            return "static"
        if not d.clink:
            return "C++ linkage"
        if d.name in self.hdr_owned:
            return f"declared in {self.hdr_owned[d.name]}"
        if d.sig.ret.cls == "x" or any(p.cls == "x" for p in d.sig.params):
            return "struct/128-bit/unknown type"
        return "duplicate definition"

    @staticmethod
    def _same_sig(a: Sig, b: Sig) -> bool:
        return ([(p.cls, p.c) for p in a.params] == [(p.cls, p.c) for p in b.params]
                and a.va == b.va and a.ret.key() == b.ret.key() and not a.unproto
                and [p.raw for p in a.params] == [p.raw for p in b.params]
                and a.ret.raw == b.ret.raw)

    def _abi_diff(self, v: Sig, d: Sig) -> str:
        """Empty when the view is ABI-identical to the definition (i686)."""
        why = []
        if v.unproto:
            why.append("unprototyped")
        elif v.va != d.va:
            why.append("varargs")
        elif len(v.params) != len(d.params):
            why.append(f"count {len(v.params)} vs {len(d.params)}")
        else:
            for i, (a, b) in enumerate(zip(v.params, d.params)):
                if a.cls != b.cls or a.kind != b.kind:
                    why.append(f"param{i + 1} {a.c} vs {b.c}")
                    break
        rv, rd = v.ret, d.ret
        if rv.cls == "v" and rd.kind in ("f", "d"):
            why.append(f"ret void vs {rd.c} (x87 ST0 left on the stack)")
        elif rv.kind != rd.kind and rv.cls != "v":
            why.append(f"ret {rv.c} vs {rd.c}")
        return ", ".join(why)

    def _self_proto(self, fi: FileInfo, d: Def) -> str:
        """The definition's own head as a prototype, after this stage's
        rewrites of the definition (tail return, widening)."""
        code = fi.code
        head = code[d.start:d.name_off]
        if id(d) in self.tail:
            g = self.tail[id(d)][2]
            a, b = self._ret_span(fi, d)
            head = code[d.start:a] + ("void *" if g.ptr else g.c) + " " + code[b:d.name_off]
        elif id(d) in self.wrets:
            a, b = self._ret_span(fi, d)
            head = code[d.start:a] + self.wrets[id(d)] + " " + code[b:d.name_off]
        params = code[d.lparen + 1:d.rparen].strip()
        retyped = dict(self.wparams.get(id(d), {}))
        for k in self.dparams.get(id(d), ()):
            retyped[k] = "double"
        if retyped:
            raw = code[d.lparen + 1:d.rparen]
            parts = [raw[a:b].strip() for a, b in split_top(raw)]
            for k, ct in retyped.items():
                if k < len(parts):
                    parts[k] = f"{ct} {self.eff[id(d)].params[k].name}"
            params = ", ".join(parts)
        params = self._lanepad_params(d, params)
        add = self.added.get(id(d))
        if add:
            new = ", ".join(f"{p.c} {p.name}" for p in add)
            params = new if params in ("", "void") else params + ", " + new
        if id(d) in self.unstatic:
            head = re.sub(r"\bstatic\b", " ", head)
        t = " ".join((head + d.name + "(" + params + ")").split())
        t = re.sub(r'\bextern\s*"[^"]*"\s*', 'extern "C" ' if fi.cpp else "", t)
        t = re.sub(r"\b(inline|__inline)\b\s*", "", t)
        return t

    def _patch_decl(self, fi: FileInfo, dc: Decl, d: Def) -> str | None:
        """C++: rewrite a local declaration to the definition's ABI shape,
        keeping local spellings per class slot."""
        ds = self.sig(d)
        if not self._patchable(d):
            return None
        if dc.sig.ret.cls == "x" or "x" in dc.sig.classes() or dc.sig.unproto:
            return None
        q = {"g": [], "f": []}
        for p in dc.sig.params:
            if p.cls in q:
                q[p.cls].append(p)
        out = []
        for p in ds.params:
            lst = q[p.cls]
            if lst:
                lp = lst.pop(0)
                out.append(lp.raw if lp.kind == p.kind else p.c)
            else:
                out.append("void *" if p.ptr else p.c)
        if ds.va:
            out.append("...")
        ps = ", ".join(out) if out else "void"
        rt = fi.text[dc.ret_span[0]:dc.ret_span[1]].strip()
        if ds.ret.cls == "v" and dc.sig.ret.cls != "v":
            rt = "void"     # call sites using the value become (F(), (T)0)
        elif dc.sig.ret.cls == "v" and ds.ret.cls != "v":
            if dc.name in self._force_ret.get(fi.rel, ()) or ds.ret.kind in ("f", "d"):
                # tail callee (value returned), or an x87 return: a call
                # statement against `void` would leave ST0 on the FPU stack
                rt = "void *" if ds.ret.ptr else ds.ret.c
        elif ds.ret.kind != dc.sig.ret.kind:
            if ds.ret.cls not in ("g", "f") or dc.sig.ret.cls not in ("g", "f"):
                return None
            rt = "void *" if ds.ret.ptr else ds.ret.c   # call sites: manual-ret-class
        pre = fi.text[dc.start:dc.ret_span[0]]
        nl = fi.text[dc.start:dc.end].count("\n")
        return f"{pre}{rt} {dc.name}({ps});" + "\n" * nl

    def _assigned_to(self, fi, c, names) -> bool:
        """`v = c(..);` with v in names (or `return c(..);` from a function
        whose own return was retyped double)."""
        code = fi.code
        h = c.start - 1
        while h > 0 and code[h] in " \t\r\n":
            h -= 1
        if code[h] == "=" and code[h - 1] not in "=!<>":
            m = re.search(r"([A-Za-z_]\w*)\s*$", code[max(0, h - 64):h])
            return bool(m) and m.group(1) in names
        return False

    def _ret_zext(self, fi, c):
        """Does retail's listing zero-extend $v0 right after call c?  Every
        jal paired with c must, on its straight-line path after the delay
        slot, have `dsll32 X, $2, 0` as the first reader of $2 (before any
        redefinition or call), followed by `dsrl32 Y, X, 0`."""
        st = self._site(fi, c)
        if st is None:
            return False
        cfg, js = st
        for j in js:
            if not self._zext_after(cfg, j):
                return False
        return bool(js)

    @staticmethod
    def _zext_after(cfg, j):
        i, n, seen = j + 2, len(cfg.ins), 0
        while i < n and seen < 12:
            op, ops = cfg.ins[i]
            if op == "dsll32" and len(ops) == 3 and ops[1] == "$2" and ops[2] == "0":
                x, k = ops[0], i
                for _ in range(6):
                    if len(cfg.succ[k]) != 1:
                        return False
                    k = cfg.succ[k][0]
                    o2, a2 = cfg.ins[k]
                    if o2 == "dsrl32" and len(a2) == 3 and a2[1] == x and a2[2] == "0":
                        return True
                    u, d = asmflow.uses_defs(o2, a2)
                    if x in u or x in d:
                        return False
                return False
            u, d = asmflow.uses_defs(op, ops)
            if "$2" in u or "$2" in d or op in ("jal", "jalr") or len(cfg.succ[i]) != 1:
                return False
            i = cfg.succ[i][0]
            seen += 1
        return False

    def _ret_class(self, fi, c, d, vret, dret):
        """Caller reads $v0 (int view) where the callee returns $f0 (float),
        or the reverse.  When the call is the tail value of its enclosing
        definition and that definition was retyped to the callee's class
        (def-tail-return / def-tail-retype), the value flows through
        unchanged and nothing is logged.  Otherwise retail's reader got
        whatever the callee left in the OTHER register (the callee's asm sets
        only the register of its own class), i.e. no value of the callee's:
        C's conversion stands in for it (`ret-class-convert`)."""
        F = self._encl_def(fi, c)
        t = self.tail.get(id(F)) if F is not None else None
        if t is not None and (t[1] is c or (isinstance(t[1], V0Tail) and c in t[1].calls)):
            return
        self._log(fi, c.start, c.name, "ret-class-convert",
                  f"caller reads {vret.c} ({'$f0' if vret.cls == 'f' else '$v0'}), "
                  f"definition returns {dret.c} ({'$f0' if dret.cls == 'f' else '$v0'}): "
                  f"retail read a register the callee does not set; C conversion")

    def _plan_call(self, fi, c, d, vs, ok):
        dsig = self.sig(d)
        if dsig.va:
            return None
        if not ok:
            if d.name in self.host_crt and self.provider.get(d.name) is d:
                return None     # host CRT name without a local declaration: as before
            if vs is None or self._abi_diff(vs, dsig):
                why = self._why_not(d)
                if vs is not None and (vs.ret.cls == "x" or "x" in vs.classes()):
                    why = "caller view has a struct/128-bit/unknown type"
                elif why == "duplicate definition" and self.gdef.get(d.name) is not d:
                    why = "binds to a duplicate definition"
                self._log(fi, c.start, c.name, "manual-call",
                          f"call left as is: callee not in header / decl not patchable "
                          f"({why})")
            return None
        m = self._map(fi, c, d)
        if m is None:
            if vs is None or self._abi_diff(vs, dsig):
                self._log(fi, c.start, c.name, "manual-call",
                          "struct/128-bit/unknown type in definition or caller view")
            return None
        newargs, extra, acls = m
        nargs = len(c.args)
        unproto = vs is None or vs.unproto
        code = fi.code
        keep = [i for i in extra if not side_effect_free(code[c.args[i][0]:c.args[i][1]])]
        fill, n_pass, n_zero, n_cast, n_bits, n_entry = [], 0, 0, 0, 0, 0
        zero_why = []
        carriers = self.carriers.get((fi.rel, c.func.body_open), set()) if c.func else set()
        changed = self._changed.get(fi.rel, set())
        for x, p in zip(newargs, dsig.params):
            if x[0] == "arg":
                i = x[1]
                vp = vs.params[i] if vs is not None and not vs.unproto and \
                    i < len(vs.params) else None
                expr = code[c.args[i][0]:c.args[i][1]].strip()
                a0, b0 = c.args[i]
                inner = [c2 for c2 in fi.calls if c2.start == a0 and c2.rparen + 1 == b0]
                if (fi.rel, c.start, i) in self.wargs:
                    fill.append(("wide", (i, p.c)))     # wide-arg: the 64-bit register
                    n_cast += 1
                elif p.kind == "d" and (expr in carriers or (inner and inner[0].start in self._dtrans)):
                    fill.append(x)      # a double already (double-local/param, nested call)
                elif p.kind == "q" and (expr in carriers or (inner and inner[0].start in self._dtrans)):
                    fill.append(("bits", (i, T("g", "double", "double"), p)))
                    n_cast += 1
                    n_bits += 1
                elif vp is not None and vp.kind == "a":
                    fill.append(("abits", (i, p)))      # agg-view: the aggregate's bytes
                    n_cast += 1
                elif vp is not None and vp.kind != p.kind and "d" in (vp.kind, p.kind) \
                        and {vp.kind, p.kind} <= {"i", "q", "d"}:
                    fill.append(("bits", (i, vp, p)))   # EE GPR bits, not a C conversion
                    n_cast += 1
                    n_bits += 1
                elif vp is not None and (vp.c in WIDE) != (p.c in WIDE):
                    fill.append(("cast", (i, p.c)))      # 4 <-> 8 byte slot
                    n_cast += 1
                elif fi.cpp and vp is None and p.ptr:
                    # C++ view without that parameter (`f(...)`): the patched
                    # declaration says void *, the argument may be an int
                    fill.append(("cast", (i, "void *")))
                    n_cast += 1
                elif fi.cpp and vp is not None and expr in changed:
                    fill.append(("cast", (i, vp.raw)))   # function we retyped
                    n_cast += 1
                else:
                    fill.append(x)
                continue
            _, p, cls, k, phi = x
            if (fi.cpp and phi is not None and vs is not None and not vs.unproto
                    and phi < len(vs.params)):
                # C++ keeps its local view: cast to that slot's type
                p = T(p.cls, vs.params[phi].raw, vs.params[phi].raw, vs.params[phi].ptr, p.name)
            man = self._missing_asm(fi, c, cls, k)
            nm = None if man else self._passthrough(fi, c, cls, k)
            ent = None if (nm or man) else self._entry_value(fi, c, cls, k)
            if man:
                fill.append(("name", (f"({man})", p)))
                n_entry += 1
                self._log(fi, c.start, c.name, "missing-asm",
                          f"arg {k} = {man} (reviewed table MISSING_ARG_ASM)")
            elif nm:
                fill.append(("name", (nm, p)))
                n_pass += 1
            elif ent:
                fill.append(("name", (ent, p)))
                n_entry += 1
            else:
                rule, expr, why = self._missing_value(fi, c, d, cls, k)
                lane = f"{'f' if cls == 'f' else 'g'}{k}"
                if expr is not None:
                    fill.append(("name", (f"({expr})", p)))
                    n_entry += 1
                else:
                    fill.append(("zero", p))
                    n_zero += 1
                zero_why.append((rule, f"{lane} {why}"))
        identity = (not n_pass and not n_zero and not n_entry and not extra and not n_cast and
                    [x[1] for x in fill] == list(range(nargs)))
        # return value
        wrap = None
        vret = vs.ret if vs is not None else T("g", "int", "int")
        dret = dsig.ret
        used = vret.cls != "v" and value_used(fi, c, self._encl_void(fi, c))
        if used and vret.cls == "x":
            self._log(fi, c.start, c.name, "manual-ret-class",
                      f"caller reads {vret.raw} by value, definition returns {dret.c}")
        elif used:
            if dret.cls == "v":
                wrap = ("zero", vret)
            elif dret.cls != vret.cls:
                self._ret_class(fi, c, d, vret, dret)
            elif vret.kind != dret.kind and "d" in (vret.kind, dret.kind) and not (
                    dret.kind == "d" and (self._assigned_to(fi, c, carriers)
                                          or c.start in self._dtrans)):
                wrap = ("bits", vret, dret)
            elif not fi.cpp and (vret.ptr or dret.ptr) and d.rel != fi.rel \
                    and not re.fullmatch(r"(const\s+)?void\s*\*", vret.raw):
                wrap = ("cast", vret)
            elif (dret.cls == "g" and not dret.ptr and dret.c in NARROW_INT and not vret.ptr
                  and vret.cls == "g" and vret.c not in NARROW_INT and vret.kind == "i"):
                # rule `ret-narrow`: the definition returns u8/s8/u16/s16/bool, the
                # caller's view a full int.  The EE extends every result to the
                # register (`sltiu`, `lbu`); i686 returns only AL/AX and the rest
                # of EAX is garbage (MapAreaDataIsLoadDone_1e8ba0 read as s32 by
                # MapAreaLoadUpdate_1d9300 said "done" with 0x067A0E00).
                wrap = ("cast", T(dret.cls, dret.c, dret.c))
                self._log(fi, c.start, c.name, "ret-narrow",
                          f"definition returns {dret.raw}, caller reads {vret.raw}: "
                          f"result cast to {dret.c} (i686 leaves EAX's upper bits undefined)")
            elif (dret.cls == "g" and not dret.ptr and dret.c in NARROW_INT and vret.cls == "g"
                  and vret.kind == "i" and fi.cpp and not os.environ.get("RG_PROTOS_NO_NARROWVIEW")
                  and (vret.ptr or (vret.c in NARROW_INT and vret.c != dret.c
                                    and NARROW_SIZE[vret.c] > NARROW_SIZE[dret.c]))):
                # rule `ret-narrow-view` (2026-10-25, protos_irabi.py whole-corpus audit): the
                # same garbage-upper-bits read through a C++ view the patched declaration
                # keeps -- a POINTER spelling of an s16 id / u8 flag
                # (`void *ObjRecHasFlags6_1c3eb0(..)` tested `== 0` in EventSysUpdate_26ac10;
                # `void *CharaGetId_214a80(..)` passed on as a script argument) or a WIDER
                # narrow type (`s16` view of a `u8` definition: AH is garbage).  The result
                # is cast to the definition's type first, then back to the view's.
                wrap = ("ncast", vret, dret)
                self._log(fi, c.start, c.name, "ret-narrow-view",
                          f"definition returns {dret.raw}, caller's view reads {vret.raw}: "
                          f"result cast to {dret.c} then {vret.raw} (i686 leaves the upper "
                          f"bits of EAX undefined)")
            elif (dret.cls == "g" and not dret.ptr and dret.kind == "i" and not vret.ptr
                  and vret.cls == "g" and vret.kind == "i" and vret.c not in NARROW_INT
                  and "unsigned" not in dret.c and dret.c not in NARROW_INT
                  and not os.environ.get("RG_PROTOS_NO_ZEXT") and not os.environ.get("RG_PROTOS_NO_WIDE")
                  and self._ret_zext(fi, c)):
                # rule `ret-zext`: a signed 4-byte result that retail's caller
                # zero-extends (`dsll32 x, $v0, 0; dsrl32 y, x, 0`, the unit's
                # own view said u32) before using it as 64 bits.  The unified
                # prototype says int, so `(u64)F()` sign-extended: an attr flag
                # set with bit 31 (ParseFlagNames_1ca700) became 0xFFFFFFFF in the
                # high word and switched off a chara's collision (BRINGUP.md
                # 2026-10-17 "battle tutorial").
                wrap = ("cast", T("g", "unsigned int", "unsigned int"))
                self._log(fi, c.start, c.name, "ret-zext",
                          f"definition returns {dret.raw}; the caller's listing zero-extends "
                          f"$v0 (dsll32/dsrl32): result cast to unsigned int")
        if identity and wrap is None:
            if unproto and nargs and any(p.cls == "f" for p in dsig.params):
                self._log(fi, c.start, c.name, "manual-unproto",
                          "unprototyped call to a function with f32 params")
            return None
        if not identity:
            det = (f"{nargs} args ({''.join('f' if a == 'f' else 'g' for a in acls)}) -> "
                   f"def {len(dsig.params)} ({''.join(dsig.classes())})")
            if unproto:
                self._log(fi, c.start, c.name, "unproto-call", det)
            drop_free = [i for i in extra if i not in keep]
            q = lambda i: repr(" ".join(code[c.args[i][0]:c.args[i][1]].split()))
            if drop_free:
                self._log(fi, c.start, c.name, "drop-extra",
                          det + "; dropped " + ", ".join(q(i) for i in drop_free))
            if keep:
                self._log(fi, c.start, c.name, "drop-extra-keep-eval",
                          det + "; kept for side effects " + ", ".join(q(i) for i in keep))
            if n_pass:
                self._log(fi, c.start, c.name, "missing-passthrough",
                          det + "; passed " + ", ".join(x[1][0] for x in fill if x[0] == "name"))
            for rule in sorted({r for r, _ in zero_why}):
                self._log(fi, c.start, c.name, rule,
                          det + "; " + "; ".join(w for r, w in zero_why if r == rule))
            if any(x[0] == "name" and x[1][0].startswith("rgp_entry_") for x in fill):
                self._log(fi, c.start, c.name, "missing-entry",
                          det + "; passed the caller's ENTRY value (retail asm: the "
                          "register is never written before the jal) "
                          + ", ".join(x[1][0] for x in fill if x[0] == "name"
                                      and x[1][0].startswith("rgp_entry_")))
            if any(k == "abits" for k, _v in fill):
                self._log(fi, c.start, c.name, "agg-bits",
                          det + "; " + ", ".join(f"arg{v[0] + 1} -> {v[1].c}"
                                                 for k, v in fill if k == "abits")
                          + ": the over-aligned aggregate's bytes (__builtin_bit_cast), "
                            "rule agg-view")
            if n_cast - n_bits - sum(1 for k, _v in fill if k == "abits"):
                self._log(fi, c.start, c.name, "arg-cast",
                          det + "; 4/8-byte slot or retyped function pointer cast")
            if n_bits:
                self._log(fi, c.start, c.name, "arg-bitcast",
                          det + "; " + ", ".join(f"arg{v[0] + 1} {v[1].c} -> {v[2].c}"
                                                 for k, v in fill if k == "bits")
                          + " as 64-bit GPR bits (__builtin_bit_cast)")
            if not extra and not n_pass and not n_zero and not n_cast and not n_entry:
                self._log(fi, c.start, c.name, "reorder", det)
        if wrap is not None:
            if wrap[0] == "bits":
                self._log(fi, c.start, c.name, "ret-bitcast",
                          f"definition returns {dret.c}, caller reads {vret.c}: "
                          f"64-bit GPR bits (__builtin_bit_cast)")
            elif wrap[0] == "zero":
                self._log(fi, c.start, c.name, "void-value-zero",
                          f"definition is void (no tail value); caller reads {vret.c}")
            else:
                self._log(fi, c.start, c.name, "ret-cast",
                          f"({vret.raw}) over {'void *' if dret.ptr else dret.c}")
        return Rewrite(c.start, c.rparen + 1, "call", call=c,
                       newargs=None if identity else fill,
                       keep=keep if not identity else [], wrap=wrap)

    # -------------------------------------------------------------- header
    def _gen_header(self) -> bytes:
        out = ["/* GENERATED by tools/stages/protos.py (transform 2) -- do not edit.",
               "   One prototype per externally linked C-linkage definition (C only).",
               "   Types are reduced to builtin C types; every pointer is void *.",
               "   A file that defines <f> defines RGP_SELF_<f> first (the stage does",
               "   that), so it never sees a second, differently spelled prototype. */",
               "#ifndef RGP_GAME_PROTOS_H", "#define RGP_GAME_PROTOS_H",
               "#ifndef __cplusplus", ""]
        n = 0
        for nm in sorted(self.gdef):
            d = self.gdef[nm]
            if not self.in_header(d):
                continue
            s = self.sig(d)
            rs = "void *" if s.ret.ptr else s.ret.c
            ps = [("void *" if p.ptr else p.c) for p in s.params]
            if s.va:
                ps.append("...")
            out.append(f"#ifndef RGP_SELF_{nm}")
            out.append(f"{rs} {nm}({', '.join(ps) or 'void'});")
            out.append("#endif")
            n += 1
        out += ["", "#endif /* !__cplusplus */"]
        out += ["#endif", ""]
        self.stats["header-protos"] = n
        return "\n".join(out).encode()

    # -------------------------------------------------------------- Stage API
    def apply(self, relpath: str, data: bytes) -> tuple[bytes, int]:
        if relpath not in self.out:
            return data, 0
        if data.startswith(MARK.encode()):
            return data, 0          # idempotent
        if hashlib.sha256(data).hexdigest() != self.inhash[relpath]:
            raise RuntimeError(f"protos: {relpath} changed after prepare()")
        new = self.out[relpath]
        sites = sum(1 for r in self.log if r[0] == relpath)
        return new, sites

    def extra_outputs(self) -> dict[str, bytes]:
        if self.sb_census is not None:
            import json
            with open(os.environ["RG_PROTOS_SB_CENSUS"], "w", encoding="utf-8") as fh:
                for r in self.sb_census:
                    fh.write(json.dumps(r, default=list) + chr(10))
        if self._tm:
            print("protos rule time: " + ", ".join(f"{k} {v:.1f}s" for k, v in sorted(self._tm.items())),
                  file=sys.stderr, flush=True)
        rows = ["file\tline\tcallee\trule\tdetail"]
        for r in sorted(self.log, key=lambda r: (r[0], r[1], r[2], r[3])):
            rows.append("\t".join(str(x).replace("\t", " ").replace("\n", " ") for x in r))
        return {HEADER_REL: self.header, LOG_REL: ("\n".join(rows) + "\n").encode("latin-1")}


def render(text: str, a: int, b: int, rws: list) -> str:
    """text[a:b] with the (possibly nested) rewrites inside it applied."""
    out, pos, i = [], a, 0
    while i < len(rws):
        r = rws[i]
        if r.start < pos:
            i += 1
            continue
        if r.start >= b:
            break
        # rewrites nested in r
        j = i + 1
        while j < len(rws) and rws[j].start < r.end:
            j += 1
        inner = rws[i + 1:j]
        out.append(text[pos:r.start])
        if r.kind == "text":
            out.append(r.text)
            if r.start == r.end:      # pure insertion
                pos = r.end
                i += 1
                continue
        else:
            out.append(render_call(text, r, inner))
        pos = r.end
        i = j
    out.append(text[pos:b])
    return "".join(out)


def render_call(text: str, r: Rewrite, inner: list) -> str:
    c = r.call
    head = text[c.start:c.lparen + 1]
    if r.newargs is None:
        s = render(text, c.start, c.rparen + 1, inner)
    else:
        arg = lambda i: render(text, c.args[i][0], c.args[i][1], inner)
        parts = []
        for kind, v in r.newargs:
            if kind == "arg":
                parts.append(arg(v))
            elif kind == "cast":
                parts.append(f"({v[1]})({arg(v[0])})")
            elif kind == "wide":
                a = arg(v[0])
                parts.append(f"({v[1]})({ProtoStage._NARROW_CAST.sub('', a.lstrip(), 1)})")
            elif kind == "name":
                parts.append(f"({v[1].c}){v[0]}")
            elif kind == "abits":
                i, p = v
                parts.append(f"__builtin_bit_cast({p.c}, ({arg(i)}))")
            elif kind == "bits":
                i, vp, p = v
                if p.kind == "d":
                    vt = "" if vp.kind == "q" else f"({'void *' if vp.ptr else vp.c})"
                    parts.append(f"__builtin_bit_cast(double, ({BITS_Q}){vt}({arg(i)}))")
                else:
                    parts.append(f"({p.c})__builtin_bit_cast({BITS_Q}, (double)({arg(i)}))")
            else:
                parts.append("0" if v.cls == "g" and not v.ptr else
                             "0.0f" if v.cls == "f" else "0")
        keeps = [f"(void)({arg(i)})" for i in r.keep]
        nl = text[c.lparen:c.rparen + 1].count("\n")
        body = ", ".join(parts)
        if keeps and parts:
            parts[0] = "(" + ", ".join(keeps + [parts[0]]) + ")"
            body = ", ".join(parts)
        s = head + body + "\n" * max(0, nl - body.count("\n")) + ")"
        if keeps and not parts:
            s = "(" + ", ".join(keeps) + ", " + s + ")"
    if r.wrap is not None:
        t = r.wrap[1]
        if r.wrap[0] == "bits":
            if r.wrap[2].kind == "d":
                s = f"(({t.raw})__builtin_bit_cast({BITS_Q}, {s}))"
            else:
                s = f"__builtin_bit_cast(double, ({BITS_Q})({s}))"
        elif r.wrap[0] == "cast":
            s = f"(({t.raw}){s})"
        elif r.wrap[0] == "ncast":
            mid = "(long)" if t.ptr else ""
            s = f"(({t.raw}){mid}({r.wrap[2].c}){s})"
        else:
            z = "0.0f" if t.cls == "f" else "0"
            s = f"({s}, ({t.raw}){z})"
    return s
