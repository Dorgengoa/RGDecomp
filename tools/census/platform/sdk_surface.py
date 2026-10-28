#!/usr/bin/env python3
"""platform_sdk_surface.tsv -- the game -> library boundary.

One row per MAIN library function (LIB_RANGES in common.py).  `role`:
  boundary        called (jal/j) by game code directly        -> src/sce implements
  boundary-ptr    only its ADDRESS is taken by game code (lui+addiu: a
                  callback/handler/thread entry handed to the SDK) -> src/sce
  data-ref        not reached from the boundary, but its address sits in a
                  data word (library vtables, libmpeg MC tables, default
                  handlers, kernel-patch tables) -> library-internal
  internal        reached only from other library functions (transitively from
                  the boundary) -> not needed if src/sce reimplements the API
  unreached       no edge from the game boundary closure (dead library code,
                  or reached only by crt0/kernel entry)
"""
from __future__ import annotations

import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

COLS = ["addr", "symbol", "family", "sub", "role", "body", "game_callers",
        "game_sites", "game_images", "game_addr_refs", "data_refs",
        "lib_callers", "lib_sites", "reach_depth", "size", "file",
        "example_game_callers"]


def main(argv=None):
    facts, imgs, edges, _ = C.cached("--rebuild" in (argv or sys.argv))
    main_im = imgs["main"]
    lib = [f for f in main_im.fns if f.lib]
    gc = defaultdict(set); gs = Counter(); gimg = defaultdict(set)
    gaddr = Counter(); dref = Counter()
    lc = defaultdict(set); ls = Counter()
    lib_out = defaultdict(set)   # lib fn -> lib fns it references
    for e in edges:
        d = e.dst
        if not d.lib:
            continue
        if e.kind == "data":
            dref[d.key] += 1
            continue
        s = e.src
        if s.is_game:
            if e.kind in ("call", "tail"):
                gc[d.key].add(s.key); gs[d.key] += 1; gimg[d.key].add(s.image)
            else:
                gaddr[d.key] += 1; gimg[d.key].add(s.image)
        else:
            if s.key != d.key:
                lib_out[s.key].add(d.key)
                if e.kind in ("call", "tail"):
                    lc[d.key].add(s.key); ls[d.key] += 1
    # closure from the boundary through library-internal edges
    roots = {f.key for f in lib if gc[f.key] or gaddr[f.key]}
    depth = {k: 0 for k in roots}
    frontier = list(roots)
    while frontier:
        nxt = []
        for k in frontier:
            for d in lib_out[k]:
                if d not in depth:
                    depth[d] = depth[k] + 1
                    nxt.append(d)
        frontier = nxt
    rows = []
    for f in lib:
        k = f.key
        if gc[k]:
            role = "boundary"
        elif gaddr[k]:
            role = "boundary-ptr"
        elif k in depth:
            role = "internal"
        elif dref[k]:
            role = "data-ref"
        else:
            role = "unreached"
        path, body = facts.get(("main", f.name), ("", "asm-only-unit"))
        ex = sorted({main_im.by_addr[a].name if i == "main" else imgs[i].by_addr[a].name
                     for i, a in gc[k]})[:4]
        rows.append({
            "addr": f"0x{f.addr:06X}", "symbol": f.name, "family": f.lib[0],
            "sub": f.lib[1], "role": role, "body": body,
            "game_callers": len(gc[k]), "game_sites": gs[k],
            "game_images": ",".join(i for i in C.IMAGES if i in gimg[k]),
            "game_addr_refs": gaddr[k], "data_refs": dref[k],
            "lib_callers": len(lc[k]), "lib_sites": ls[k],
            "reach_depth": depth.get(k, ""), "size": f"0x{f.size:X}",
            "file": path, "example_game_callers": " ".join(ex)})
    rows.sort(key=lambda r: ({"boundary": 0, "boundary-ptr": 1, "internal": 2,
                              "data-ref": 3, "unreached": 4}[r["role"]], r["addr"]))
    cnt = Counter(r["role"] for r in rows)
    C.write_tsv(C.OUT / "platform_sdk_surface.tsv", COLS, rows, C.meta(
        "sdk_surface", {
            "rows": len(rows),
            "roles": ", ".join(f"{k}={v}" for k, v in sorted(cnt.items())),
            "note": "edges decoded from retail jal/j/lui+addiu and data words; "
                    "family = link-order band (common.LIB_RANGES); body from "
                    "source at the pinned commit (asm-only-unit = no C file "
                    "defines it)"}))
    fam = defaultdict(Counter)
    for r in rows:
        fam[r["family"]][r["role"]] += 1
    for k in sorted(fam):
        print(k, dict(fam[k]))
    print(cnt)


if __name__ == "__main__":
    main()
