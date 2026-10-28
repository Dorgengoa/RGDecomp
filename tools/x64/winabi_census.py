#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Win64 argument-position census (P7 risk R4, docs/X64-PLAN.md).

i686 cdecl passes every argument in a stack word, so a caller that passes an
int where the callee reads a float (or the reverse) at the SAME word works:
the callee reinterprets the 4 bytes.  Win64 passes argument k in a register
chosen by position AND class: RCX/RDX/R8/R9 for integers, pointers and
aggregates, XMM0-3 for float/double (stack slots beyond 4).  The same
mismatch reads an unrelated register on x64.  A 32-bit value read as a
64-bit one (i64 / size_t parameter) has undefined upper bits.

Three checks:

  direct   every direct call of every compiled unit against its callee's
           definition, from tools/bringup/protos_irabi.py's per-file IR
           summaries (i686 IR; one IR item per C argument, so positions are
           the C positions).  Rows: position k < len(def) whose class differs
           (G = integer / pointer / aggregate, X = float / double) or whose
           integer width differs (4 vs 8 bytes).
  family   vtable families (data tables sharing >= 2 (slot, function) pairs,
           as tools/bringup/vslot_census.py): every function in one slot must
           agree on the class of each position the others read.
  vcm      every devirt slot call `VCM*(ret, (ptypes), soff, ..)` /
           `VCALL*(.., soff, ret, (ptypes), ..)` in the compiled game sources
           against the functions found at that slot offset in the data tables:
           `none` = no table function at that offset agrees with the caller's
           view (a definite x64 bug candidate), `some` = only some do.

    python tools/x64/winabi_census.py [--sum out/protos2/ir/sum] [--out build/x64-probe]

Writes <out>/winabi_direct.tsv, winabi_family.tsv, winabi_vcm.tsv and
winabi_summary.txt.  The IR summaries come from
`tools/bringup/protos_irabi.py --all` (cached; refresh it after stage changes).
"""
from __future__ import annotations

import argparse
import glob
import json
import os
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(os.environ.get("RG_PORT_ROOT", Path(__file__).resolve().parents[2]))


def cls_of(kind: str) -> str:
    """i686 irabi slot kind -> Win64 class: X (xmm), G (gpr), V (varargs)."""
    if kind in ("f", "d"):
        return "X"
    if kind == "...":
        return "V"
    return "G"


def width(kind: str) -> int:
    return 8 if kind in ("q", "b8", "d") else 4


def ctype_class(t: str) -> str:
    t = t.strip()
    if t == "...":
        return "V"
    if "*" in t or "(" in t or "[" in t:
        return "G"
    base = re.sub(r"\b(const|volatile|register)\b", "", t).strip()
    base = re.sub(r"\s+\w+$", "", base) if re.search(r"\s", base) else base
    if re.search(r"\b(f32|f64|float|double)\b", base):
        return "X"
    return "G"


def split_params(s: str) -> list[str]:
    out, d, cur = [], 0, []
    for ch in s:
        if ch in "(<[":
            d += 1
        elif ch in ")>]":
            d -= 1
        if ch == "," and d == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur).strip())
    if out == ["void"]:
        return []
    return out


def direct(sumdir: Path, rows: list, cnt: Counter):
    defs = {}
    calls = []
    for f in sumdir.glob("*.json"):
        try:
            d = json.loads(f.read_text(encoding="utf-8"))
        except Exception:
            continue
        for nm, (ret, slots, internal) in d.get("defs", {}).items():
            if not internal:
                defs.setdefault(nm, (ret, slots))
        src = d.get("file", f.stem)
        for c in d.get("calls", []):
            calls.append((src, c))
    for src, c in calls:
        nm, ret, slots = c[0], c[1], c[2]
        if nm not in defs:
            continue
        cnt["direct-calls"] += 1
        dret, dslots = defs[nm]
        for k, ds in enumerate(dslots):
            if ds[2] == "...":
                break
            if k >= len(slots):
                break          # fewer args than the def reads: protos BUG-missing, not R4
            vs = slots[k]
            if vs[2] == "...":
                break
            a, b = cls_of(vs[2]), cls_of(ds[2])
            if a != b:
                rows.append((nm, src, k, vs[2], ds[2], "class"))
                cnt["direct-class"] += 1
                break
            if a == "G" and width(vs[2]) != width(ds[2]):
                rows.append((nm, src, k, vs[2], ds[2], "width"))
                cnt["direct-width"] += 1
                break
        # return class: float in XMM0 vs integer in RAX
        rv = str(ret)
        dr = str(dret)
        if (("float" in rv or "double" in rv) != ("float" in dr or "double" in dr)
                and "void" not in rv and "void" not in dr):
            rows.append((nm, src, -1, rv, dr, "ret-class"))
            cnt["direct-ret-class"] += 1


def protos(path: Path) -> dict[str, list[str]]:
    out = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = re.match(r"^\s*(?:extern\s+\"C\"\s+)?[^#/(]*?\b(\w+)\s*\((.*)\)\s*;\s*$", line)
        if m:
            out[m.group(1)] = split_params(m.group(2))
    return out


def tables(root: Path):
    for f in glob.glob(str(root / "game" / "src" / "**" / "data2c_*.c"), recursive=True):
        text = open(f, encoding="utf-8", errors="replace").read()
        for m in re.finditer(r"\bu32\s+(D_[0-9A-Fa-f]+)\s*\[\d*\][^=]*=\s*\{(.*?)\};", text, re.S):
            ents = [e.strip() for e in re.sub(r"/\*.*?\*/", "", m.group(2), flags=re.S).split(",")]
            fns = []
            for e in ents:
                k = re.fullmatch(r"\(u32\)&(\w+)", e)
                fns.append(k.group(1) if k else None)
            if sum(1 for x in fns if x) >= 2:
                yield m.group(1), fns


def agree(view: list[str], callee: list[str]) -> bool:
    for k in range(min(len(view), len(callee))):
        a, b = ctype_class(view[k]), ctype_class(callee[k])
        if "V" in (a, b):
            return True
        if a != b:
            return False
    return True


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--sum", default=str(ROOT / "out" / "protos2" / "ir" / "sum"))
    ap.add_argument("--out", default=str(ROOT / "build" / "x64-probe"))
    ap.add_argument("--min-shared", type=int, default=2)
    a = ap.parse_args()
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    cnt = Counter()
    drows: list = []
    if Path(a.sum).is_dir():
        direct(Path(a.sum), drows, cnt)
    pr = protos(ROOT / "game" / "include" / "port" / "game_protos.h")
    tabs = list(tables(ROOT))
    # families (union-find over shared (slot, fn) pairs)
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
        for j in idx[1:]:
            shared[(min(idx[0], j), max(idx[0], j))] += 1
    for (i, j), n in shared.items():
        if n >= a.min_shared:
            parent[find(i)] = find(j)
    fam = defaultdict(list)
    for i in range(len(tabs)):
        fam[find(i)].append(i)
    frows = []
    at_soff = defaultdict(set)        # byte offset in the table -> functions
    for members in fam.values():
        slots = defaultdict(set)
        for i in members:
            for s, fn in enumerate(tabs[i][1]):
                if fn and fn in pr:
                    slots[s].add(fn)
                    at_soff[4 * s].add(fn)
        for s, fns in sorted(slots.items()):
            fl = sorted(fns)
            for x in range(len(fl)):
                for y in range(x + 1, len(fl)):
                    if not agree(pr[fl[x]], pr[fl[y]]):
                        frows.append((4 * s, fl[x], "(" + ", ".join(pr[fl[x]]) + ")", fl[y],
                                      "(" + ", ".join(pr[fl[y]]) + ")",
                                      ",".join(sorted(tabs[i][0] for i in members))[:200]))
    cnt["family-pairs"] = len(frows)
    # devirt slot calls in the compiled game sources
    vrows = []
    rx = re.compile(r"\b(VCMQ?(?:_FN)?|VCMQ0|VCALL(?:_THIS|_BOOL)?)\s*\(")
    srcs = [r.split("\t") for r in (ROOT / "game" / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    files = [ROOT / "game" / r[0] for r in srcs if r[3] == "unit"]
    files += [Path(p) for p in glob.glob(str(ROOT / "overrides" / "src" / "**" / "*.c*"), recursive=True)]
    for f in files:
        try:
            t = f.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if "VC" not in t:
            continue
        for m in rx.finditer(t):
            # the argument text up to the matching paren
            i, d = m.end(), 1
            while i < len(t) and d:
                d += {"(": 1, ")": -1}.get(t[i], 0)
                i += 1
            args = split_params(t[m.end():i - 1])
            mac = m.group(1)
            try:
                if mac in ("VCM", "VCM_FN"):
                    ptypes, soff = args[1], args[2]
                elif mac in ("VCMQ", "VCMQ_FN"):
                    ptypes, soff = args[2], args[3]
                elif mac in ("VCALL", "VCALL_THIS"):
                    soff, ptypes = args[2], args[4]
                elif mac == "VCALL_BOOL":
                    soff, ptypes = args[2], args[3]
                else:
                    continue
                soff = int(soff, 0)
            except (IndexError, ValueError):
                cnt["vcm-unparsed"] += 1
                continue
            view = split_params(ptypes.strip()[1:-1])
            if not any(ctype_class(p) == "X" for p in view):
                cnt["vcm-no-float"] += 1
                cands = at_soff.get(soff - 8, set())
                fl = [fn for fn in cands if any(ctype_class(p) == "X" for p in pr[fn])]
                if not fl:
                    continue
            cnt["vcm-checked"] += 1
            cands = at_soff.get(soff - 8, set())
            ok = [fn for fn in cands if agree(view, pr[fn])]
            bad = [fn for fn in cands if not agree(view, pr[fn])]
            if not cands:
                verdict = "nocand"
            elif not bad:
                continue
            elif not ok:
                verdict = "none"
            else:
                verdict = "some"
            cnt["vcm-" + verdict] += 1
            line = t.count("\n", 0, m.start()) + 1
            vrows.append((verdict, str(f.relative_to(ROOT)).replace("\\", "/"), line, hex(soff),
                          ptypes.strip(), ",".join(sorted(bad))[:300], len(ok), len(bad)))
    with open(out / "winabi_direct.tsv", "w", encoding="utf-8") as fo:
        fo.write("callee\tcaller_file\tpos\tview\tdef\tkind\n")
        for r in sorted(drows):
            fo.write("\t".join(map(str, r)) + "\n")
    with open(out / "winabi_family.tsv", "w", encoding="utf-8") as fo:
        fo.write("table_off\tfn_a\tproto_a\tfn_b\tproto_b\ttables\n")
        for r in sorted(frows):
            fo.write("\t".join(map(str, r)) + "\n")
    with open(out / "winabi_vcm.tsv", "w", encoding="utf-8") as fo:
        fo.write("verdict\tfile\tline\tsoff\tview\tdisagreeing\tn_ok\tn_bad\n")
        for r in sorted(vrows):
            fo.write("\t".join(map(str, r)) + "\n")
    L = ["winabi census: " + ", ".join(f"{k}={v}" for k, v in sorted(cnt.items()))]
    (out / "winabi_summary.txt").write_text("\n".join(L) + "\n", encoding="utf-8")
    print("\n".join(L))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
