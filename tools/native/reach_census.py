#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Static reachability of game objects in a linked rg-game (docs/NATIVE-CPU.md section 8).

    python tools/native/reach_census.py BUILD [--exe rg-game] [--why FUNC ...] [--dead out.tsv]
    python tools/native/reach_census.py BUILD --check ViBufAddDma_1d4240,ViBufStopDma_1d4180

Reads BUILD/<exe>.map (lld-link /MAP: which objects are linked), runs llvm-nm over every
linked object (game objects from CMakeFiles/rg_game_*.dir and rg-game.dir, port libraries
from their .lib files) and walks symbol references: an object is REACHABLE when a reachable
object references a symbol it defines.  Roots: every linked non-game object (port
libraries, the CRT, rg-game's own sources: a conservative over-approximation, they may
reference game code through tables or calls) -- game code reaches the rest, data2c tables
included (a function whose address sits in a reachable data table is reachable).

One game function per object (the decomp's unit layout), so object reachability is
function reachability.  An unreachable object can only run through a raw code-address
literal, and hw_census.py finds none in compiled code.

--check F1,F2  exit 1 if any named function is reachable (prints the reference chain)
--why F        print the chain from a root to F
--dead PATH    write every unreachable game object (tsv: object, defined symbols)
"""
from __future__ import annotations

import argparse
import os
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from link_audit import MapInfo, nm_symbols  # noqa: E402

NM = os.environ.get("RG_LLVM_NM", r"../tools\llvm\bin\llvm-nm.exe")


def collect(build: Path, exe: str):
    mi = MapInfo(build / f"{exe}.map")
    linked = set(mi.objs)
    gameobjs = {o for (l, o) in linked if not l}
    files: list[Path] = []
    seen: set[str] = set()
    host: set[str] = set()   # rg-game's own sources (rg_game_main.c, ...): roots, not game code
    for pat in (f"CMakeFiles/{exe}.dir", "CMakeFiles/rg_game_*.dir"):
        for d in build.glob(pat):
            for p in d.rglob("*.obj"):
                if p.name in gameobjs and p.name not in seen:
                    seen.add(p.name)
                    files.append(p)
                    if pat.startswith(f"CMakeFiles/{exe}"):
                        host.add(p.name)
    libfiles: dict[str, Path] = {}
    for root, dirs, fnames in os.walk(build):
        dirs[:] = [x for x in dirs if x not in ("_deps", "CMakeFiles", "Testing", "game-gen")]
        for fn in fnames:
            if fn.endswith(".lib"):
                stem = fn[:-4]
                if stem not in libfiles or Path(root).name == "nonly":
                    libfiles[stem] = Path(root) / fn
    files.extend(libfiles[l] for l in sorted(mi.libs()) if l in libfiles)
    syms = nm_symbols(NM, files)
    nodes: dict[str, tuple[set[str], set[str], bool]] = {}
    for key, (defs, undef) in syms.items():
        lib, _, obj = key.rpartition(":")
        if (lib, obj) not in linked:
            continue
        nodes[key] = (defs, undef, lib == "" and obj not in host)
    missing_game = gameobjs - {k for k, v in nodes.items() if v[2]}
    return nodes, missing_game


def walk(nodes):
    owner: dict[str, str] = {}
    for key, (defs, _u, _g) in nodes.items():
        for s in defs:
            owner.setdefault(s, key)
    parent: dict[str, tuple[str, str] | None] = {}
    q: deque[str] = deque()
    for key, (_d, _u, game) in nodes.items():
        if not game:
            parent[key] = None
            q.append(key)
    while q:
        k = q.popleft()
        for s in nodes[k][1]:
            o = owner.get(s)
            if o and o not in parent:
                parent[o] = (k, s)
                q.append(o)
    return owner, parent


def chain(parent, key):
    out = []
    while key is not None:
        p = parent.get(key)
        out.append(key if p is None else f"{key}  <- {p[1]} in")
        key = p[0] if p else None
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("build")
    ap.add_argument("--exe", default="rg-game")
    ap.add_argument("--check", default="")
    ap.add_argument("--why", nargs="*", default=[])
    ap.add_argument("--dead", default="")
    a = ap.parse_args()
    nodes, missing = collect(Path(a.build), a.exe)
    owner, parent = walk(nodes)
    game = [k for k, v in nodes.items() if v[2]]
    dead = sorted(k for k in game if k not in parent)
    print(f"reach_census: {len(nodes)} linked objects, {len(game)} game objects, "
          f"{len(game) - len(dead)} reachable, {len(dead)} unreachable"
          + (f" ({len(missing)} game objects not found as .obj)" if missing else ""))
    if a.dead:
        with open(a.dead, "w", encoding="utf-8") as f:
            f.write("object\tdefines\n")
            for k in dead:
                f.write(f"{k}\t{','.join(sorted(nodes[k][0]))}\n")
        print(f"reach_census: unreachable objects -> {a.dead}")
    bad = 0
    names = [n for n in a.check.split(",") if n] + list(a.why)
    for n in names:
        o = owner.get(n) or owner.get("_" + n)
        if not o:   # C++ units: mangled names; the object is named after the function
            o = next((k for k in nodes if k in (f"{n}.c.obj", f"{n}.cpp.obj")), None)
        if not o:
            print(f"{n}: not linked")
            continue
        if o in parent:
            print(f"{n}: REACHABLE ({o})")
            for line in chain(parent, o):
                print(f"    {line}")
            if n in a.check.split(","):
                bad += 1
        else:
            print(f"{n}: unreachable ({o})")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
