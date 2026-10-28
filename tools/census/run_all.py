#!/usr/bin/env python3
"""Run every game-code census against one snapshot (loaded once), then print
the per-TSV totals that census/README.md quotes.

    python tools/census/run_all.py --source ../RGDecomp --rev <commit>
    python tools/census/run_all.py --source <extracted dir> --rev WORKTREE
    python tools/census/run_all.py --summary-only        # just re-total the TSVs
"""
from __future__ import annotations

import sys
import time
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import snapshot as S

CENSUSES = ["asm_bodies", "vcalls", "addr_literals", "proto_conflicts", "div_sites",
            "wide_types", "pragmas_attrs"]


def read_tsv(p: Path):
    meta, rows, cols = {}, [], None
    for ln in p.read_text(encoding="utf-8").splitlines():
        if ln.startswith("# "):
            k, _, v = ln[2:].partition(": ")
            meta[k] = v
        elif cols is None:
            cols = ln.split("\t")
        else:
            rows.append(dict(zip(cols, ln.split("\t"))))
    return meta, rows


def summarize(out: Path) -> None:
    for name in CENSUSES:
        p = out / f"{name}.tsv"
        if not p.exists():
            print(f"== {name}: missing")
            continue
        meta, rows = read_tsv(p)
        files = {r["file"] for r in rows}
        syms = {(r["image"], r["symbol"]) for r in rows}
        print(f"== {name}: {len(rows)} sites, {len(files)} files, {len(syms)} symbols "
              f"(commit {meta.get('commit', '?')[:12]})")
        print("   by image:", dict(Counter(r["image"] for r in rows).most_common()))
        print("   by lib:  ", dict(Counter(r["lib"] for r in rows).most_common()))
        print("   by category:", dict(Counter(r["category"] for r in rows).most_common()))
        game = [r for r in rows if r["lib"] == "game"]
        print(f"   game-only: {len(game)} sites, {len({r['file'] for r in game})} files,"
              f" {len({(r['image'], r['symbol']) for r in game})} symbols;"
              f" by category {dict(Counter(r['category'] for r in game).most_common())}")
        for extra in ("body", "severity", "conf", "type", "group", "name_check"):
            if rows and extra in rows[0]:
                print(f"   game by {extra}:",
                      dict(Counter((r['category'], r[extra]) for r in game).most_common(30)))


def main() -> int:
    ap = S.arg_parser(__doc__.splitlines()[0])
    ap.add_argument("--summary-only", action="store_true")
    a = ap.parse_args()
    out = Path(a.out)
    if not a.summary_only:
        snap = S.load(a.source, a.rev)
        orig = S.load
        S.load = lambda *_a, **_k: snap     # every census reuses this snapshot
        try:
            for name in CENSUSES:
                t = time.time()
                mod = __import__(name)
                sys.argv = [name, "--out", str(out)]
                print(f"--- {name}", flush=True)
                mod.main()
                print(f"    ({time.time() - t:.0f}s)", flush=True)
        finally:
            S.load = orig
        unres = out / "unresolved_units.tsv"
        S.write_tsv(unres, ["image", "unit", "why"],
                    [dict(image=i, unit=u, why=w) for i, u, w in snap.unresolved],
                    S.meta(snap, "run_all", {"registered_units": snap.unit_count,
                                             "files": len(snap.files),
                                             "headers": [h.path for h in snap.headers]}))
    summarize(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
