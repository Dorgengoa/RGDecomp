# SPDX-License-Identifier: CC0-1.0
"""vslot_census.py: float-lane mismatches between functions that share a table slot.

MIPS passes integer arguments in $a0.. and float arguments in $f12.. independently,
so `int F(void *, float)` and `int G(void *, H *, float)` are interchangeable in one
vtable slot (F simply never reads $a1).  On i686 cdecl the float is the 2nd stack
word for F and the 3rd for G: called through the slot as (this, h, f), F reads h as
its float.  (NodeRefObjUpdate_318af0 / JudgeObjectStep_314360 in the judge-object
vtables read the registry pointer as dt; the judges never expired, the judge pool
filled up and no attack judge could be allocated: BRINGUP.md 2026-10-17 part 3.)

Families: data tables (game/src/**/data2c_*.c, `(u32)&Fn` entries) that share at
least MIN_SHARED identical (slot, function) pairs are one vtable family; within a
family every slot's functions must agree on the GPR lanes in front of their float
parameters.  Prototypes come from game/include/port/game_protos.h (post-stage).

    python tools/bringup/vslot_census.py [--min-shared 2] [--tsv out.tsv]

Prints one row per slot whose float-taking functions place their floats after fewer
GPR parameters than a sibling takes in total.  Original CC0 code.
"""
import argparse
import glob
import os
import re
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FLOAT = re.compile(r"^\s*(const\s+)?(float|f32)\s*\w*\s*$")


def protos(path):
    out = {}
    for line in open(path, encoding="utf-8", errors="replace"):
        m = re.match(r"^\s*(?:extern\s+\"C\"\s+)?[^#/(]*?\b(\w+)\s*\((.*)\)\s*;\s*$", line)
        if not m:
            continue
        ps = [p.strip() for p in m.group(2).split(",")] if m.group(2).strip() not in ("", "void") else []
        out[m.group(1)] = ps
    return out


def tables(root):
    for f in glob.glob(os.path.join(root, "game", "src", "**", "data2c_*.c"), recursive=True):
        text = open(f, encoding="utf-8", errors="replace").read()
        for m in re.finditer(r"\bu32\s+(D_[0-9A-Fa-f]+)\s*\[\d*\][^=]*=\s*\{(.*?)\};", text, re.S):
            ents = [e.strip() for e in m.group(2).split(",")]
            fns = []
            for e in ents:
                k = re.fullmatch(r"\(u32\)&(\w+)", e)
                fns.append(k.group(1) if k else None)
            if sum(1 for x in fns if x) >= 2:
                yield m.group(1), fns, os.path.relpath(f, root)


def shape(ps):
    """(gpr params before the first float, total gpr params, float count)."""
    pre, g, nf, seen_f = 0, 0, 0, False
    for p in ps:
        if p == "...":
            continue
        if FLOAT.match(p):
            nf += 1
            seen_f = True
        else:
            g += 1
            if not seen_f:
                pre += 1
    return pre, g, nf


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-shared", type=int, default=2)
    ap.add_argument("--tsv")
    a = ap.parse_args()
    pr = protos(os.path.join(ROOT, "game", "include", "port", "game_protos.h"))
    tabs = list(tables(ROOT))
    # union-find over tables sharing (slot, fn) pairs
    parent = list(range(len(tabs)))

    def find(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i
    by_pair = defaultdict(list)
    for i, (_n, fns, _f) in enumerate(tabs):
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
    rows = []
    for members in fam.values():
        slots = defaultdict(set)
        for i in members:
            for s, fn in enumerate(tabs[i][1]):
                if fn and fn in pr:
                    slots[s].add(fn)
        for s, fns in sorted(slots.items()):
            if len(fns) < 2:
                continue
            sh = {fn: shape(pr[fn]) for fn in fns}
            gmax = max(g for _p, g, _f in sh.values())
            bad = [fn for fn, (p, g, nf) in sh.items() if nf and p < gmax]
            if not bad:
                continue
            fams = ",".join(sorted(tabs[i][0] for i in members))
            for fn in sorted(bad):
                p, g, nf = sh[fn]
                sib = max((f2 for f2 in fns if sh[f2][1] == gmax), key=str)
                rows.append((fn, s, p, gmax, sib, "(" + ", ".join(pr[fn]) + ")",
                             "(" + ", ".join(pr[sib]) + ")", fams))
    rows.sort()
    for r in rows:
        print("%s slot %d: floats after %d gpr, sibling takes %d (%s) %s vs %s  [%s]" % r)
    print("%d rows" % len(rows))
    if a.tsv:
        with open(a.tsv, "w", encoding="utf-8", newline="\n") as f:
            f.write("fn\tslot\tgpr_before_float\tsibling_gpr\tsibling\tproto\tsibling_proto\ttables\n")
            for r in rows:
                f.write("\t".join(str(x) for x in r) + "\n")


if __name__ == "__main__":
    main()
