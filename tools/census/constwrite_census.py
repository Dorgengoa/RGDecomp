#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""constwrite_census.py [GAME_SRC]: list writes to objects a file declares `extern const`.

Matching-decomp sources declare some .sdata/.rodata words `extern const` (an mwcc
addressing trick) and write them through a cast, `*(s16 *)&D_x = v` or a `#define W
(*(s16 *)&D_x)` macro.  Writing a const-defined object is UB; clang (LLVM marks the
external global `constant`) deletes such stores, so the game's state never changes
(BRINGUP item 7: item-menu Use soft lock).  Prints file, name, line for every write found.
"""
import re, sys
from pathlib import Path

root = Path(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).resolve().parents[2] / "game" / "src")
decl = re.compile(r'^\s*extern\s+const\s+(?:volatile\s+)?(?:unsigned\s+|signed\s+)?\w+\s+(D_\w+|\w+)\s*(\[[^\]]*\])?\s*(?:__attribute__\(\(.*?\)\))?\s*;', re.M)
ASSIGN = r'\s*(?:=(?!=)|\+=|-=|\*=|/=|\|=|&=|\^=|<<=|>>=|\+\+|--)'
n = 0
for f in sorted(list(root.rglob("*.c")) + list(root.rglob("*.cpp"))):
    t = f.read_text(errors="replace")
    if "extern const" not in t:
        continue
    names = {m.group(1) for m in decl.finditer(t)}
    if not names:
        continue
    macros = {}
    for m in re.finditer(r'^#define\s+(\w+)\s+(.*)$', t, re.M):
        for nm in names:
            if re.search(r'&\s*' + re.escape(nm) + r'\b', m.group(2)):
                macros[m.group(1)] = nm
    pats = []
    for nm in names:
        # cast-deref / cast-index of &NAME used as an lvalue
        pats.append((nm, re.compile(r'\*\s*\(\s*(?:volatile\s+)?[\w ]+\*\s*\)\s*&\s*' + re.escape(nm) + r'\b\s*\)?' + ASSIGN)))
        pats.append((nm, re.compile(r'\(\s*\(\s*(?:volatile\s+)?[\w ]+\*\s*\)\s*&?\s*' + re.escape(nm) + r'\s*\)\s*(?:\[[^\]]*\]|->\w+)' + ASSIGN)))
        pats.append((nm, re.compile(r'(?:\+\+|--)\s*\*\s*\(\s*[\w ]+\*\s*\)\s*&\s*' + re.escape(nm) + r'\b')))
    for mac, nm in macros.items():
        pats.append((nm, re.compile(r'(?<![#\w])' + re.escape(mac) + r'\b' + ASSIGN)))
        pats.append((nm, re.compile(r'(?:\+\+|--)\s*' + re.escape(mac) + r'\b')))
    for i, line in enumerate(t.splitlines(), 1):
        if line.lstrip().startswith("#define"):
            continue
        for nm, p in pats:
            if p.search(line):
                print(f"{f.relative_to(root).as_posix()}\t{nm}\t{i}\t{line.strip()}")
                n += 1
                break
print(f"# {n} writes", file=sys.stderr)
