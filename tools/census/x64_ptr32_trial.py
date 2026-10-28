#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Strategy-A trial (P7, docs/X64-PLAN.md): a THROWAWAY `__ptr32` rewrite of a
sample of game TUs, compiled for x64, struct layouts compared with the
unmodified i686 compile.  Answers "does a mechanical 4-byte-pointer rewrite
give x64 the i686 layouts, and what does it leave?"  It is a measurement, not
the stage: the rewritten copies live under <out>/ptr32 and are never built
into anything.

    python tools/census/x64_ptr32_trial.py [--db build/soak2-i686] [--out build/x64-probe]
                                           [--every 25] [--only REGEX] [-j 4]

Rewrite (text level, on copies; game/include headers rewritten too):
  * record member declarations: every `*` of the declarator -> `* __ptr32 __uptr`
    (data pointers, pointer-to-pointer, function-pointer members)
  * column-0 file-scope pointer declarations (extern / definitions, not functions)
  * file-scope pointer typedefs (`typedef T *P;`, `typedef R (*F)(...)`)
  * pointer-loading casts `(T **)` -> `(T * __ptr32 __uptr *)`
  * `sizeof(T *)` -> `sizeof(T * __ptr32 __uptr)`
Compile: the probe's x64 command + -fms-extensions -Wincompatible-pointer-types
(the game build silences it; here it finds `T **pp = &s->p32` mismatches).
Writes <out>/ptr32_summary.txt and <out>/ptr32_layout_left.tsv.
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import json
import re
import shlex
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from x64_census import blank, contexts, member_decls  # noqa: E402
from x64_probe import (LAYOUT, i686_cmd, is_game, norm, parse_diags, parse_layouts,  # noqa: E402
                       rel, summarize_layouts, x64_cmd)

P32 = "* __ptr32 __uptr "


def star_positions(code: str, s: int, e: int, decl_only: bool) -> list[int]:
    """'*' offsets in code[s:e] that belong to the declarator: stop at '=' (initializer)
    and skip '*' inside a parameter list / array bound (paren depth > the declarator's)."""
    out = []
    seg = code[s:e]
    stop = len(seg)
    depth = 0
    for i, ch in enumerate(seg):
        if ch == "=" and depth == 0:
            stop = i
            break
    # function-pointer declarator: `R (*name)(params)` -> only the '*' in the first parens
    m = re.search(r"\(\s*((?:\*\s*)+)(?:const\s*)?[A-Za-z_]\w*\s*(?:\[[^\]]*\])?\s*\)\s*\(", seg[:stop])
    if m:
        for k in range(m.start(1), m.end(1)):
            if seg[k] == "*":
                out.append(s + k)
        return out
    if decl_only and "(" in seg[:stop]:
        return []  # a function declaration / something else: leave
    bdepth = 0
    for i, ch in enumerate(seg[:stop]):
        if ch in "[(":
            bdepth += 1
        elif ch in "])":
            bdepth -= 1
        elif ch == "*" and bdepth == 0:
            out.append(s + i)
    return out


def rewrite(raw: str) -> tuple[str, Counter]:
    code = blank(raw)
    blocks, recspans = contexts(code)
    stars: set[int] = set()
    cnt = Counter()
    for o, c in recspans:
        for s, d in member_decls(code, o, c, []):
            dd = d.strip()
            if not dd or "*" not in dd or dd.startswith(("typedef", "static ", "friend", "using ")):
                continue
            if "{" in dd:
                continue
            # method declarations: `R name(params)` without a (*name) form
            if "(" in dd and not re.search(r"\(\s*\*", dd):
                continue
            ps = star_positions(code, s, s + len(d), decl_only=False)
            if ps:
                cnt["member"] += 1
                stars.update(ps)
    # column-0 file-scope declarations and typedefs (statement = up to ';' at depth 0)
    for m in re.finditer(r"(?m)^(?:extern\s+|static\s+|const\s+|volatile\s+|typedef\s+)*"
                         r"(?:struct\s+|union\s+|enum\s+)?[A-Za-z_]\w*[^;{}]*?;", code):
        st = m.group(0)
        if "*" not in st or st.startswith(("return", "#")):
            continue
        inside = any(o < m.start() < c for o, c, k in blocks if k in ("fn", "rec", "init"))
        if inside:
            continue
        is_td = st.startswith("typedef")
        ps = star_positions(code, m.start(), m.end(), decl_only=not is_td)
        if ps:
            cnt["typedef" if is_td else "global"] += 1
            stars.update(ps)
    # pointer-loading casts and sizeof(T *)
    for m in re.finditer(r"\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*(\*)\s*\*\s*\)", code):
        stars.add(m.start(1))
        cnt["ptrptr-cast"] += 1
    for m in re.finditer(r"\bsizeof\s*\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s+\w+)*\s*(\*)\s*\)", code):
        stars.add(m.start(1))
        cnt["sizeof"] += 1
    out = []
    last = 0
    for p in sorted(stars):
        out.append(raw[last:p])
        out.append(P32)
        last = p + 1
    out.append(raw[last:])
    return "".join(out), cnt


def run_one(e: dict, out: Path, inc: Path) -> dict:
    f = norm(e["file"])
    src = Path(f)
    r = rel(f)
    dst = out / "ptr32" / r
    dst.parent.mkdir(parents=True, exist_ok=True)
    text, cnt = rewrite(src.read_text(encoding="utf-8", errors="replace"))
    dst.write_text(text, encoding="utf-8", newline="")
    args = shlex.split(norm(e["command"]), posix=True)
    # i686 baseline on the original
    r32 = subprocess.run(i686_cmd(args) + LAYOUT, cwd=e["directory"], capture_output=True,
                         text=True, encoding="utf-8", errors="replace")
    # x64 on the rewritten copy, rewritten headers first, original dir for quoted includes
    xa = []
    for a in x64_cmd(args, None):
        if norm(a) == f:
            a = norm(str(dst))
        xa.append(a)
    xa = [xa[0], "-I" + norm(str(inc)), "-I" + norm(str(src.parent))] + xa[1:]
    xa += ["-fms-extensions", "-Wincompatible-pointer-types", "-Wno-error=incompatible-pointer-types"]
    xa += LAYOUT
    r64 = subprocess.run(xa, cwd=e["directory"], capture_output=True, text=True,
                         encoding="utf-8", errors="replace")
    left = summarize_layouts(parse_layouts(r32.stdout), parse_layouts(r64.stdout))
    return {"file": r, "rc": r64.returncode, "cnt": dict(cnt), "diags": parse_diags(r64.stderr),
            "left": [(d["name"], d["size32"], d["size64"]) for d in left],
            "nrec": len(parse_layouts(r32.stdout))}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--db", default="build/soak2-i686")
    ap.add_argument("--out", default="build/x64-probe")
    ap.add_argument("--every", type=int, default=25)
    ap.add_argument("--only", default="")
    ap.add_argument("-j", "--jobs", type=int, default=4)
    a = ap.parse_args()
    out = Path(a.out)
    out = out if out.is_absolute() else ROOT / out
    db = Path(a.db)
    db = db if db.is_absolute() else ROOT / db
    entries = [e for e in json.loads((db / "compile_commands.json").read_text(encoding="utf-8"))
               if is_game(norm(e["file"])) and "/main_data/" not in norm(e["file"])
               and (not a.only or re.search(a.only, norm(e["file"])))]
    entries = entries[:: a.every]
    inc = out / "ptr32" / "game" / "include"
    inc.mkdir(parents=True, exist_ok=True)
    hc = Counter()
    for h in sorted((ROOT / "game" / "include").rglob("*.h")):
        t, c = rewrite(h.read_text(encoding="utf-8", errors="replace"))
        d = inc / h.relative_to(ROOT / "game" / "include")
        d.parent.mkdir(parents=True, exist_ok=True)
        d.write_text(t, encoding="utf-8", newline="")
        hc.update(c)
    print(f"{len(entries)} sampled game TUs (every {a.every}th); headers rewritten: {dict(hc)}", flush=True)
    res = []
    with cf.ThreadPoolExecutor(a.jobs) as ex:
        for r in ex.map(lambda e: run_one(e, out, inc), entries):
            res.append(r)
    tot = Counter()
    for r in res:
        tot.update(r["cnt"])
    dcls = Counter()
    dtu = Counter()
    for r in res:
        seen = set()
        for f, l, c, kind, cls in r["diags"]:
            dcls[cls] += 1
            if cls not in seen:
                dtu[cls] += 1
                seen.add(cls)
    left = Counter()
    lefttu = 0
    with open(out / "ptr32_layout_left.tsv", "w", encoding="utf-8") as fo:
        fo.write("tu\trecord\tsize32\tsize64\n")
        for r in res:
            if r["left"]:
                lefttu += 1
            for n, s32, s64 in r["left"]:
                left[n] += 1
                fo.write(f"{r['file']}\t{n}\t{s32}\t{s64}\n")
    # baseline: the same TUs' differing records WITHOUT the rewrite (x64_probe results)
    base = None
    pr = out / "results.jsonl"
    if pr.exists():
        want = {r["file"] for r in res}
        got = {}
        for ln in pr.read_text(encoding="utf-8").splitlines():
            try:
                d = json.loads(ln)
            except Exception:
                continue
            if d["file"] in want and "ldiff" in d:
                got[d["file"]] = len(d["ldiff"])
        base = (sum(got.values()), sum(1 for v in got.values() if v), len(got))
    L = [f"ptr32 trial: {len(res)} TUs, {sum(1 for r in res if r['rc'])} fail to compile; "
         f"records compared {sum(r['nrec'] for r in res)}; still differing {sum(left.values())} "
         f"in {lefttu} TUs"
         + (f" (without the rewrite: {base[0]} differing in {base[1]} of the {base[2]} TUs "
            f"the probe has)" if base else ""),
         "rewrites: " + ", ".join(f"{k}={v}" for k, v in tot.most_common()),
         "diagnostics (sites / TUs):"]
    for k, v in dcls.most_common(25):
        L.append(f"  {v:7d} {dtu[k]:5d}  {k}")
    L.append("records still differing (top): " + ", ".join(f"{k}={v}" for k, v in left.most_common(15)))
    (out / "ptr32_summary.txt").write_text("\n".join(L) + "\n", encoding="utf-8")
    print("\n".join(L))
    return 0


if __name__ == "__main__":
    sys.exit(main())
