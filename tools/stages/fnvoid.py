#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Ingest stage `fnvoid`: a function designator converted to `void *` in C++ gets an
explicit `(void *)` cast (docs/LINUX.md "Stage proposal: C++ function -> void * rule").

mwcc and clang on the MSVC target (i686-pc-windows-msvc, Microsoft extensions) convert a
function to `void *` implicitly; clang on any other C++ target rejects it ("no matching
function" for an argument, "converts between void pointer and function pointer" for an
assignment), which stops the Linux build.  The cast is what the MSVC target does
implicitly, so Windows objects do not change.

Rewrites, C++ files only (`.cpp`), on code with comments / strings / preprocessor lines
blanked (offsets map 1:1 onto the original):

  * a call F(.., X, ..) where the nearest preceding declaration of F in the file declares
    that parameter exactly `void *` (optionally named / const) and X is `Fn` or `&Fn`, Fn a
    function declared or defined in the file:      X -> (void *)X
  * an assignment `lhs = Fn;` / `lhs = &Fn;` where lhs is a plain name or a member
    (`.m` / `->m`) declared `void *` in the file, Fn as above: Fn -> (void *)Fn

Idempotent (an already cast argument no longer has the `Fn` / `&Fn` shape).  No other
spelling is touched.

Standalone test on a copy of game/:  python tools/stages/fnvoid.py --game game [--list]
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
import portxform as X  # noqa: E402  (read-only reuse: blank, blank_pp)

KEYWORDS = {"return", "else", "case", "goto", "sizeof", "new", "delete", "throw", "do", "if", "while",
            "for", "switch", "typedef", "using", "operator"}
IDENT = r"[A-Za-z_]\w*"
_DECL = re.compile(r"^\s*(?:\s*(?:extern\s+\"\s*\"|extern|static|inline|__inline)\s+)*"
                   r"((?:" + IDENT + r"(?:::" + IDENT + r")*)(?:\s+" + IDENT + r")*)"
                   r"([\s\*&]+)(" + IDENT + r")\s*\((.*)\)\s*(?:const\s*)?$", re.S)
_VOIDP = re.compile(r"\s*(?:const\s+)?void\s*\*\s*(?:const\s+)?(?:" + IDENT + r")?\s*")
_FNARG = re.compile(r"\s*(&\s*)?(" + IDENT + r")\s*")
_VOIDP_NAME = re.compile(r"\bvoid\s*\*\s*(" + IDENT + r")\s*[;,=)]")
_ASSIGN = re.compile(r"(?:(?:\.|->)\s*|(?<![\w.>]))(" + IDENT + r")\s*=\s*(?!=)(&\s*)?(" + IDENT + r")\s*;")


def split_top(s: str) -> list[tuple[int, int]]:
    """top-level comma-separated spans of s (offsets into s)"""
    out, depth, start = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == "," and depth == 0:
            out.append((start, i))
            start = i + 1
    out.append((start, len(s)))
    return out


_TYPE_HEAD = re.compile(r"\b(?:struct|class|union|enum)\b")


def declarations(code: str):
    """(name, offset of the name, [param texts]) for every function declaration or
    definition head outside class / struct / union bodies (member functions, e.g. the
    devirt slot thunks, are not designators a call can pass): statements split at ; { }"""
    decls = []
    start = 0
    stack: list[bool] = []   # per open brace: a type body?
    for m in re.finditer(r"[;{}]", code):
        stmt = code[start:m.start()]
        off = start
        start = m.end()
        in_type = any(stack)
        if m.group(0) == "{":
            head = stmt.strip()
            stack.append(bool(_TYPE_HEAD.search(head)) and not head.endswith(")"))
        elif m.group(0) == "}":
            if stack:
                stack.pop()
        if in_type:
            continue
        if "(" not in stmt or "=" in stmt.split("(", 1)[0]:
            continue
        d = _DECL.match(stmt)
        if not d:
            continue
        spec = d.group(1).split()
        if not spec or spec[-1] in KEYWORDS or spec[0] in KEYWORDS:
            continue
        params = d.group(4)
        if params.count("(") != params.count(")"):
            continue
        ps = [params[a:b] for a, b in split_top(params)]
        decls.append((d.group(3), off + d.start(3), ps))
    return decls


def edits_for(code: str) -> list[tuple[int, str]]:
    decls = declarations(code)
    fn_names = {n for n, _, _ in decls}
    by_name: dict[str, list[tuple[int, list[str]]]] = {}
    decl_at = set()
    for n, o, ps in decls:
        by_name.setdefault(n, []).append((o, ps))
        decl_at.add(o)
    ins: list[tuple[int, str]] = []
    # calls whose parameter is void *
    for n, lst in by_name.items():
        if not any(any(_VOIDP.fullmatch(p) for p in ps) for _, ps in lst):
            continue
        for m in re.finditer(r"\b" + re.escape(n) + r"\s*\(", code):
            if m.start() in decl_at:
                continue
            prev = [(o, ps) for o, ps in lst if o < m.start()]
            if not prev:
                continue
            ps = prev[-1][1]
            op = m.end() - 1
            cl = X.match_close(code, op, "(", ")")
            args = code[op + 1:cl]
            for k, (a, b) in enumerate(split_top(args)):
                if k >= len(ps) or not _VOIDP.fullmatch(ps[k]):
                    continue
                am = _FNARG.fullmatch(args[a:b])
                if am and am.group(2) in fn_names:
                    pos = op + 1 + a + (len(args[a:b]) - len(args[a:b].lstrip()))
                    ins.append((pos, "(void *)"))
    # assignments to void * names / members
    vnames = {m.group(1) for m in _VOIDP_NAME.finditer(code)}
    for m in _ASSIGN.finditer(code):
        if m.group(1) in vnames and m.group(3) in fn_names:
            ins.append((m.start(2) if m.group(2) else m.start(3), "(void *)"))
    return sorted(set(ins))


def apply(path: str, data: bytes) -> tuple[bytes, int]:
    if not path.endswith(".cpp"):
        return data, 0
    text = data.decode("utf-8", "surrogateescape")
    code = X.blank_pp(X.blank(text))
    ins = edits_for(code)
    if not ins:
        return data, 0
    for pos, s in reversed(ins):
        text = text[:pos] + s + text[pos:]
    return text.encode("utf-8", "surrogateescape"), len(ins)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("files", nargs="*", help="files to show (default: every .cpp under --game)")
    a = ap.parse_args(argv)
    files = [Path(f) for f in a.files] or sorted(Path(a.game).rglob("*.cpp"))
    total = 0
    for f in files:
        new, n = apply(f.as_posix(), f.read_bytes())
        if n:
            total += n
            print(f"{f}: {n} site(s)")
            old = f.read_bytes().decode("utf-8", "surrogateescape").splitlines()
            for i, ln in enumerate(new.decode("utf-8", "surrogateescape").splitlines()):
                if i < len(old) and ln != old[i]:
                    print(f"  {i + 1}: {ln.strip()}")
    print(f"fnvoid: {total} sites")
    return 0


if __name__ == "__main__":
    sys.exit(main())
