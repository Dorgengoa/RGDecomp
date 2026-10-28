# SPDX-License-Identifier: CC0-1.0
"""sce_arity_census.py: game calls to native SDK functions (src/sce/**/*.h) whose
argument count differs from the native prototype.

The decomp's SDK units are `asm` (game/src/main/sdk), so the protos stage had no C
truth for them and left the game's views alone: GuardWaveEffectStart_2d5ad0 calls
`sceVu0CopyVector(dst)` (its view has one parameter; retail passes its own $a1 as
the source untouched), the native sceVu0CopyVector(dst, src) read a stale stack
word and the first guarded hit faulted (BRINGUP.md 2026-10-17 part 3).  With the
native headers in PROVIDER_HEADERS (tools/stages/protos.py) the stage maps these
calls like any other provider call; this census lists what is left.

    python tools/bringup/sce_arity_census.py [--game game]

Counts are textual (top-level commas of the call), good enough for a census.
Original CC0 code.
"""
import argparse
import glob
import os
import re
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def split_args(s):
    depth, cur, out = 0, "", []
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def call_args(text, i):
    """text[i] == '(' -> argument string up to the matching ')'."""
    depth = 0
    for j in range(i, len(text)):
        if text[j] == "(":
            depth += 1
        elif text[j] == ")":
            depth -= 1
            if depth == 0:
                return text[i + 1:j]
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--game", default=os.path.join(ROOT, "game"))
    a = ap.parse_args()
    protos = {}
    for h in glob.glob(os.path.join(ROOT, "src", "sce", "**", "*.h"), recursive=True):
        t = open(h, encoding="utf-8", errors="replace").read()
        t = re.sub(r"/\*.*?\*/|//[^\n]*", " ", t, flags=re.S)
        for m in re.finditer(r"\b(sce\w+|isce\w+)\s*\(([^;{}()]*)\)\s*;", t):
            ps = m.group(2).strip()
            n = 0 if ps in ("", "void") else len(split_args(ps))
            if "..." not in ps:
                protos.setdefault(m.group(1), (n, os.path.relpath(h, ROOT)))
    rows = Counter()
    sites = {}
    for f in glob.glob(os.path.join(a.game, "src", "**", "*.c*"), recursive=True):
        if os.sep + "sdk" + os.sep in f:
            continue
        t = open(f, encoding="utf-8", errors="replace").read()
        t2 = re.sub(r"/\*.*?\*/|//[^\n]*", lambda m: " " * len(m.group(0)), t, flags=re.S)
        for m in re.finditer(r"\b(sce\w+|isce\w+)\s*\(", t2):
            nm = m.group(1)
            if nm not in protos:
                continue
            pre = t2[max(0, m.start() - 80):m.start()]
            if re.search(r"(extern|void|s32|int|u32|\*)\s*$", pre) and not re.search(r"[=(,;]\s*$", pre):
                continue              # a declaration, not a call
            args = call_args(t2, m.end() - 1)
            if args is None:
                continue
            n = 0 if not args.strip() else len(split_args(args))
            want = protos[nm][0]
            if n != want:
                rows[(nm, n, want)] += 1
                sites.setdefault((nm, n, want), os.path.relpath(f, a.game))
    for (nm, n, want), c in sorted(rows.items()):
        print(f"{nm}\t{n} args vs native {want}\t{c} site(s)\te.g. {sites[(nm, n, want)]}")
    print(f"{sum(rows.values())} call sites, {len(rows)} (function, count) classes")


if __name__ == "__main__":
    main()
