#!/usr/bin/env python3
"""Census 4: declarations (and call sites) that disagree with the definition.

Each registered unit declares its own prototypes, and nothing checks them
against the definition: mwcc's MIPS EABI tolerated a wrong count or a pointer/
int swap.  Under cdecl on x86 a wrong count, a float-vs-int swap or a 64-bit-
vs-32-bit swap is an ABI break; a pointer-vs-int swap is harmless on i686 but
fails once one unified game_protos.h is compiled into every file (plan
transform 2).

Parser (regex, no preprocessor -- pycparser cannot take this corpus: it is a
mix of C and mwcc C++ with `asm` functions, `__attribute__`, `extern "C"`
blocks and local class hierarchies):
  * definitions = top-level function bodies (snapshot.find_funcs); C++
    member functions (`A::f`) and class-inline bodies are skipped
  * declarations = top-level statements and block-scope `extern` statements
    of the form `<ret> name(<params>);` (function-pointer variables and
    typedefs are skipped)
  * types are reduced to classes: void int ptr f32 f64 i64 i128 struct
    varargs; file-local typedefs are resolved one level (pointer typedef ->
    ptr, struct typedef -> struct, scalar typedef -> its class); an unknown
    type name is `int?`
  * small-int width / signedness differences are ignored (promoted in cdecl)

category        what
count           declaration parameter count != definition's
varargs         one side is `...`, the other is not
ret             return class differs
param           a parameter class differs (first differing position shown)
unprototyped    C `f()` declaration of a function that takes parameters
call_count      a call site passes a different number of arguments than the
                definition takes (non-varargs, direct calls only)
arity_file      definition (or, for asm/no-C bodies, declaration) disagrees
                with config/arity.txt / arity_inferred.txt
severity        abi     -- breaks under cdecl (count, float/int, 64/32, struct,
                           decl expects a return value the definition lacks)
                type    -- ptr vs int and similar: fine on i686, a compile
                           error under a unified prototype header
                asmdecl -- the declaring file's only users are asm bodies
                           (`extern void f(void);` placeholders): goes away
                           with the asm unit
                addronly -- the declaring file never calls it, only takes
                           its address (callback tables): matters only for
                           the unified header / function-pointer casts
                sdk     -- the definition is an sdk/library unit (often an asm
                           placeholder signature): check the game's use
                           against the real SDK prototype in sce/
                check   -- disagreement with arity_inferred.txt (itself only
                           ~97% accurate) or a def vs arity file: verify by hand
"""
from __future__ import annotations

import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

INTS = {"s8", "u8", "s16", "u16", "s32", "u32", "int", "char", "short", "long", "unsigned",
        "signed", "bool", "size_t", "enum", "BOOL", "uint", "ushort", "uchar", "wchar_t"}
I64 = {"s64", "u64", "long long", "f64x"}
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "goto",
            "defined", "asm", "__attribute__", "typedef", "operator"}


def type_class(t: str, tdefs: dict) -> str:
    t = re.sub(r"__attribute__\s*\(\(.*?\)\)", "", t)
    t = re.sub(r"\b(const|volatile|register|static|extern|inline|restrict|__restrict)\b", "", t)
    t = re.sub(r'"[^"]*"', "", t).strip()
    if "*" in t or "[" in t or "&" in t or "(" in t:
        return "ptr"
    if not t or t == "void":
        return "void"
    if t == "...":
        return "varargs"
    words = t.split()
    if "long" in words and words.count("long") >= 2:
        return "i64"
    base = words[-1] if words[-1] not in ("int",) or len(words) == 1 else words[0]
    if words[0] in ("struct", "union", "class"):
        name = words[1] if len(words) > 1 else ""
        return tdefs.get(name, "struct")
    if words[0] == "enum":
        return "int"
    for w in words:
        if w in ("f32", "float"):
            return "f32"
        if w in ("f64", "double"):
            return "f64"
        if w in ("s64", "u64"):
            return "i64"
        if w in ("u128", "s128", "__int128"):
            return "i128"
    if all(w in INTS for w in words):
        return "int"
    if base in tdefs:
        return tdefs[base]
    return "int?"


def split_params(p: str) -> list[str]:
    out, cur, d = [], [], 0
    for c in p:
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
        if c == "," and d == 0:
            out.append("".join(cur)); cur = []
        else:
            cur.append(c)
    if "".join(cur).strip():
        out.append("".join(cur))
    return [x.strip() for x in out]


def param_classes(params: str, tdefs: dict, cpp: bool):
    """-> (list of classes, varargs, unprototyped)"""
    p = params.strip()
    if p == "":
        return [], False, not cpp
    if p == "void":
        return [], False, False
    parts = split_params(p)
    va = False
    out = []
    for x in parts:
        if x == "...":
            va = True
            continue
        # strip a trailing parameter name: `s32 *name`, `f32 x`, `T name[4]`
        y = re.sub(r"\[[^\]]*\]\s*$", "*", x)
        m = re.match(r"(.*?[\w*&\s])\s*\b([A-Za-z_]\w*)\s*$", y)
        if m and m.group(1).strip() and m.group(1).strip() not in ("struct", "union", "enum", "unsigned", "signed") \
                and not re.fullmatch(r"(unsigned|signed|long|short)", m.group(2)):
            typ = m.group(1)
        else:
            typ = y
        out.append(type_class(typ, tdefs))
    return out, va, False


def local_typedefs(s: str) -> dict:
    td = {}
    for m in re.finditer(r"\btypedef\b", s):
        # find the end of the typedef statement at depth 0
        d, k = 0, m.end()
        while k < len(s):
            c = s[k]
            if c == "{":
                d += 1
            elif c == "}":
                d -= 1
            elif c == ";" and d == 0:
                break
            k += 1
        body = s[m.end():k]
        if "{" in body:
            tail = body[body.rfind("}") + 1:]
            for nm in re.findall(r"(\**)\s*(\w+)", tail):
                td[nm[1]] = "ptr" if nm[0] else "struct"
            continue
        fp = re.search(r"\(\s*\*\s*(\w+)\s*\)", body)
        if fp:
            td[fp.group(1)] = "ptr"
            continue
        mm = re.match(r"\s*(.*?)\s*\b(\w+)\s*(\[[^\]]*\])?\s*$", body, re.S)
        if mm:
            if mm.group(3):
                td[mm.group(2)] = "struct"
            else:
                td[mm.group(2)] = type_class(mm.group(1), td)
    for m in re.finditer(r"\b(?:struct|class|union)\s+(\w+)\s*(?::[^{;]*)?\{", s):
        td.setdefault(m.group(1), "struct")
    return td


DECL = re.compile(r"""^\s*(?:__declspec\s*\(\w+\)\s*)?
    (?P<pre>(?:(?:extern|static|inline|__inline|asm)\s+(?:"[^"]*"\s*)?)*)
    (?P<ret>[A-Za-z_][\w\s\*&]*?[\s\*&])
    (?P<name>[A-Za-z_]\w*)\s*
    \((?P<params>[^()]*(?:\([^()]*\)[^()]*)*)\)\s*
    (?:__attribute__\s*\(\(.*?\)\)\s*|asm\s*\(\s*"[^"]*"\s*\)\s*|throw\s*\(\s*\)\s*)*$""", re.X | re.S)


class Sig:
    __slots__ = ("file", "line", "image", "lib", "name", "ret", "params", "va", "unproto",
                 "static", "is_asm", "text", "kind")

    def __init__(self, **kw):
        for k, v in kw.items():
            setattr(self, k, v)

    def show(self):
        ps = list(self.params) + (["..."] if self.va else [])
        return f"{self.ret} ({', '.join(ps)})"


def parse_sig(text: str, tdefs: dict, cpp: bool):
    text = " ".join(text.split())
    if len(text) > 600 or "(" not in text:
        return None
    m = DECL.match(text)
    if not m:
        return None
    name = m.group("name")
    if name in KEYWORDS:
        return None
    ret = m.group("ret").strip()
    if re.search(r"\b(typedef|return|else|case|goto|new|delete)\b", ret) or ret in ("", "struct", "union", "enum"):
        return None
    if re.match(r"(struct|union|class|enum)\s*$", ret):
        return None
    params, va, unproto = param_classes(m.group("params"), tdefs, cpp)
    pre = m.group("pre") or ""
    return dict(name=name, ret=type_class(ret, tdefs), params=params, va=va, unproto=unproto,
                static="static" in pre.split() or re.search(r"\bstatic\b", ret) is not None,
                is_asm="asm" in pre.split())


_NONNL = re.compile(r"[^\n]")
_BR = re.compile(r"[()\[\]{}]")


def blank_bodies(sf: S.SrcFile) -> str:
    s = sf.nostr
    out, pos = [], 0
    for f in sorted((f for f in sf.funcs if f.kind in ("func", "class")), key=lambda f: f.body_open):
        if f.body_open < pos:
            continue  # nested (class inside class)
        out.append(s[pos:f.body_open])
        out.append((";" if f.kind == "func" else " ") + _NONNL.sub(" ", s[f.body_open + 1:f.body_close + 1]))
        pos = f.body_close + 1
    out.append(s[pos:])
    return "".join(out)


def close_paren(s: str, o: int) -> int:
    depth = 0
    for m in _BR.finditer(s, o):
        c = m.group(0)
        if c in "([{":
            depth += 1
        else:
            depth -= 1
            if depth == 0:
                return m.start()
    return len(s) - 1


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    a = ap.parse_args()
    snap = S.load(a.source, a.rev)

    defs: dict[str, list[Sig]] = defaultdict(list)
    decls: list[Sig] = []
    asm_users: dict[str, set] = {}      # file -> names referenced inside asm bodies
    c_users: dict[str, set] = {}        # file -> names referenced inside C bodies
    called: dict[str, set] = {}         # file -> names CALLED inside C bodies
    for sf in snap.files:
        cpp = sf.path.endswith(".cpp")
        tdefs = local_typedefs(sf.nostr)
        au, cu = set(), set()
        for f in sf.funcs:
            if f.kind != "func":
                continue
            body_idents = set(re.findall(r"[A-Za-z_]\w*", sf.nostr[f.body_open:f.body_close]))
            (au if f.is_asm else cu).update(body_idents)
            if not f.is_asm:
                called.setdefault(sf.path, set()).update(
                    re.findall(r"([A-Za-z_]\w*)\s*\(", sf.nostr[f.body_open:f.body_close]))
            if "::" in f.name or f.name == "<anon>":
                continue
            hdr = f.header.strip()
            hdr = re.sub(r'^.*\bextern\s+"[^"]*"\s*', "", hdr)   # leftover extern "C" on same stmt
            p = parse_sig(hdr, tdefs, cpp)
            if not p or p["name"] != f.name:
                continue
            defs[f.name].append(Sig(file=sf.path, line=sf.line(f.body_open), image=sf.image,
                                    lib=sf.lib, text=hdr, kind="def", **p))
        asm_users[sf.path], c_users[sf.path] = au, cu
        # declarations: top-level statements, plus block-scope `extern` ones
        top = blank_bodies(sf)
        # statements = text between delimiters ; { } ending in ';' (a manual
        # walk: the regex [^;{}]+; is O(n^2) on a long ;-less tail)
        prev = 0
        for dm in re.finditer(r"[;{}]", top):
            start, prev = prev, dm.end()
            if dm.group(0) != ";":
                continue
            stmt = top[start:dm.start()]
            if "(" not in stmt or "typedef" in stmt:
                continue
            st = re.sub(r'^\s*extern\s+"[^"]*"\s*\{?', "", stmt)
            p = parse_sig(st, tdefs, cpp)
            if p:
                off = start + len(stmt) - len(stmt.lstrip())
                decls.append(Sig(file=sf.path, line=sf.line(off), image=sf.image, lib=sf.lib,
                                 text=" ".join(st.split()), kind="decl", **p))
        for f in sf.funcs:
            if f.kind != "func" or f.is_asm:
                continue
            body = sf.nostr[f.body_open + 1:f.body_close]
            for m in re.finditer(r"\bextern\b[^;{}]*;", body):
                p = parse_sig(m.group(0)[:-1], tdefs, cpp)
                if p:
                    decls.append(Sig(file=sf.path, line=sf.line(f.body_open + 1 + m.start()),
                                     image=sf.image, lib=sf.lib, text=" ".join(m.group(0).split()),
                                     kind="decl", **p))

    def pick_def(name, d: Sig):
        cands = defs.get(name) or []
        same = [c for c in cands if c.file == d.file]
        if same:
            return same[0]
        glob = [c for c in cands if not c.static]
        if not glob:
            return None
        # prefer one in the same image, then main
        for c in glob:
            if c.image == d.image:
                return c
        for c in glob:
            if c.image == "main":
                return c
        return glob[0]

    ABI = {"f32", "f64", "i64", "i128", "struct"}

    def cls_sev(a_, b_):
        if a_ == b_:
            return None
        if {a_, b_} <= {"int", "int?", "ptr"}:
            return "type"
        if "int?" in (a_, b_) and not ({a_, b_} & ABI):
            return "type"
        return "abi"

    rows = []
    for d in decls:
        df = pick_def(d.name, d)
        if df is None or df.is_asm:
            continue
        if df.file == d.file and df.line == d.line:
            continue
        asm_only = d.name in asm_users.get(d.file, ()) and d.name not in c_users.get(d.file, ())
        base = dict(file=d.file, line=d.line, symbol=d.name, image=d.image, lib=d.lib,
                    decl=d.show(), def_sig=df.show(), def_file=f"{df.file}:{df.line}",
                    decl_text=S.snippet(d.text, 140))
        problems = []
        if d.unproto and not df.unproto:
            if df.params:
                problems.append(("unprototyped", "type", f"f() vs {len(df.params)} params"))
        elif d.va != df.va:
            problems.append(("varargs", "abi", "decl ..." if d.va else "def ..."))
        elif len(d.params) != len(df.params):
            problems.append(("count", "abi", f"{len(d.params)} vs {len(df.params)}"))
        else:
            for i, (x, y) in enumerate(zip(d.params, df.params)):
                sev = cls_sev(x, y)
                if sev:
                    problems.append(("param", sev, f"arg{i}: {x} vs {y}"))
                    break
        if d.ret != df.ret:
            if df.ret == "void" and d.ret != "void":
                problems.append(("ret", "abi", f"decl {d.ret}, def void (caller reads garbage)"))
            elif d.ret == "void":
                problems.append(("ret", "type", f"decl void, def {df.ret} (result ignored)"))
            else:
                sev = cls_sev(d.ret, df.ret)
                if sev:
                    problems.append(("ret", sev, f"{d.ret} vs {df.ret}"))
        addr_only = (not asm_only and d.name in c_users.get(d.file, ())
                     and d.name not in called.get(d.file, ()))
        for cat, sev, why in problems:
            if asm_only:
                sev = "asmdecl"
            elif addr_only:
                sev = "addronly"
            elif df.lib != "game":
                sev = "sdk"
            rows.append(dict(base, category=cat, severity=sev, why=why))

    # call sites with the wrong argument count (direct calls to a C definition)
    callrx = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)\s*\(")
    for sf in snap.files:
        for f in sf.funcs:
            if f.kind not in ("func", "member") or f.is_asm:
                continue
            body = sf.nostr[f.body_open + 1:f.body_close]
            for m in callrx.finditer(body):
                name = m.group(1)
                if name not in defs or name in KEYWORDS:
                    continue
                # skip declarations `T name(` and pointer decls
                pre = body[max(0, m.start() - 40):m.start()]
                if re.search(r"(\b(extern|void|s32|u32|f32|int|char|static|struct)\s*\**\s*$)|\*\s*$", pre) and \
                        not re.search(r"(return|=|\(|,)\s*\**\s*$", pre):
                    continue
                d = Sig(file=sf.path, image=sf.image, static=False)
                df = pick_def(name, d)
                if df is None or df.is_asm or df.va:
                    continue
                o = f.body_open + 1 + m.end() - 1
                k = close_paren(sf.nostr, o)
                args = sf.nostr[o + 1:k].strip()
                n = 0 if not args or args == "void" else len(split_params(args))
                if n != len(df.params):
                    rows.append(dict(file=sf.path, line=sf.line(o), symbol=f.name, image=sf.image,
                                     lib=sf.lib, category="call_count",
                                     severity="abi" if df.lib == "game" else "sdk", why=f"{name}: {n} args vs {len(df.params)} params",
                                     decl=S.snippet(args, 80), def_sig=df.show(),
                                     def_file=f"{df.file}:{df.line}",
                                     decl_text=S.snippet(sf.line_text(sf.line(o), "code"), 140)))

    # config/arity*.txt
    arity = {}
    for fn, conf in (("config/arity.txt", "hand"), ("config/arity_inferred.txt", "inferred")):
        for ln in (snap.tree.read(fn) or "").splitlines():
            ln2 = ln.split("#")[0].strip()
            if not ln2 or ln2.startswith("//"):
                continue
            p = ln2.split()
            if len(p) >= 3 and p[1].isdigit():
                arity.setdefault(p[0], (int(p[1]), int(p[2]), conf + (":" + ln.split("#")[1].strip() if "#" in ln else "")))
    allsyms = set()
    for img in S.IMAGES:
        allsyms |= set(snap.symbols[img])
    known = sum(1 for n in arity if n in allsyms)
    decls_by = defaultdict(list)
    for d in decls:
        decls_by[d.name].append(d)

    def counts(sig: Sig):
        ni = sum(1 for c in sig.params if c not in ("f32", "f64"))
        nf = sum(1 for c in sig.params if c in ("f32", "f64"))
        return ni, nf
    for name, (ni, nf, conf) in sorted(arity.items()):
        cands = [d for d in defs.get(name, []) if not d.is_asm]
        if cands:
            df = cands[0]
            if counts(df) != (ni, nf) and not df.va:
                rows.append(dict(file=df.file, line=df.line, symbol=name, image=df.image, lib=df.lib,
                                 category="arity_file", severity="check",
                                 why=f"def {counts(df)} vs arity file ({ni},{nf}) [{conf}]",
                                 decl="", def_sig=df.show(), def_file=f"{df.file}:{df.line}",
                                 decl_text=S.snippet(df.text, 140)))
            continue
        # no C body: compare every declaration against the arity file
        for d in decls_by.get(name, ()):
            if d.va:
                continue
            asm_only = d.name in asm_users.get(d.file, ()) and d.name not in c_users.get(d.file, ())
            if counts(d) != (ni, nf):
                rows.append(dict(file=d.file, line=d.line, symbol=name, image=d.image, lib=d.lib,
                                 category="arity_file",
                                 severity="asmdecl" if asm_only else ("abi" if conf.startswith("hand") else "check"),
                                 why=f"decl {counts(d)} vs arity file ({ni},{nf}) [{conf}]; no C body",
                                 decl=d.show(), def_sig="", def_file="(asm / no C definition)",
                                 decl_text=S.snippet(d.text, 140)))

    rows.sort(key=lambda r: (r["category"], r["severity"], r["symbol"], r["file"], r["line"]))
    cols = S.BASE_COLS + ["severity", "why", "decl", "def_sig", "def_file", "decl_text"]
    out = Path(a.out) / "proto_conflicts.tsv"
    nd = sum(len(v) for v in defs.values())
    S.write_tsv(out, cols, rows, S.meta(snap, "proto_conflicts", {
        "parsed": f"{nd} definitions ({len(defs)} names), {len(decls)} declarations",
        "arity_files": f"{len(arity)} entries, {known} name a current symbol"}))
    print(f"defs {nd} names {len(defs)} decls {len(decls)} arity {len(arity)} (current names {known})")
    print(Counter((r["category"], r["severity"]) for r in rows))
    print(f"wrote {out} ({len(rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
