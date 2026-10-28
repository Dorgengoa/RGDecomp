#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""altlink.py: link a TEST copy of rg-game.exe with some TUs swapped, without touching
the shared build dir (its objects, exe and ninja state stay as they are).

    python tools/bringup/altlink.py --build build/play-i686 --out OUTDIR \\
        game/src/main/menu/Foo_123.c=path/to/edited/Foo_123.c [more REL=SRC ...]

Each REL is the game-tree path the build compiles (game/src/... or overrides/src/...);
SRC is the edited source.  Compiles SRC with that TU's exact command (from
`ninja -t commands`) into OUTDIR, writes OUTDIR/rg-game.rsp with the object swapped,
and links OUTDIR/rg-game.exe (+ .map) with the build's own link flags.  Use it to try a
stage-rule / override fix on a play-test repro while another session owns the build dir.
--first OBJ (repeatable) links a prebuilt object ahead of everything: a layout-shift probe
(two exes from the same objects, different layout; BRINGUP-HISTORY 2026-10-24 "Revelation
flashing slot").
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

NINJA = r"../tools\ninja\ninja.exe"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--build", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--target", default="rg-game.exe")
    ap.add_argument("--first", action="append", default=[],
                    help="prebuilt object linked FIRST (ahead of the build's inputs; a library "
                         "member defining the same symbols is then not pulled, and the exe "
                         "layout shifts: use it to test layout dependence)")
    ap.add_argument("swaps", nargs="*", help="REL=SRC")
    a = ap.parse_args()
    bd = Path(a.build).resolve()
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    cmds = subprocess.run([NINJA, "-C", str(bd), "-t", "commands", a.target],
                          capture_output=True, text=True, check=True).stdout.splitlines()
    t = (bd / "build.ninja").read_text(encoding="utf-8", errors="replace")
    i = t.index(f"\nbuild {a.target}:")
    j = t.index("\nbuild ", i + 5)
    blk = t[i + 1:j].splitlines()
    head = blk[0].replace("$:", "").split(":", 1)[1].replace("", ":").split("||")[0].split("|")[0].split()
    ins = [x.replace("$:", ":") for x in head[1:]]          # drop the rule name
    var = {}
    for l in blk[1:]:
        m = re.match(r"\s+(\w+) = (.*)$", l)
        if m:
            var[m.group(1)] = m.group(2)
    for sw in a.swaps:
        rel, src = sw.split("=", 1)
        rel = rel.replace("\\", "/")
        objs = [x for x in ins if x.endswith("/" + rel + ".obj")]
        if len(objs) != 1:
            print(f"altlink: {rel}: {len(objs)} objects match", file=sys.stderr)
            return 2
        obj = objs[0]
        cc = [c for c in cmds if f"-o {obj} " in c]
        if len(cc) != 1:
            print(f"altlink: no compile command for {obj}", file=sys.stderr)
            return 2
        new_obj = out / (Path(rel).name + ".obj")
        c = cc[0]
        c = re.sub(r" -MD -MT \S+ -MF \S+", "", c)
        c = c.replace(f"-o {obj} ", f"-o {new_obj} ")
        c = re.sub(r" -c \S+$", lambda m: f" -c {Path(src).resolve()}", c)
        r = subprocess.run(c, cwd=bd, shell=True)
        if r.returncode:
            return r.returncode
        ins[ins.index(obj)] = new_obj.as_posix()   # rsp: GNU quoting eats backslashes
        print(f"altlink: {rel} -> {new_obj}")
    rsp = out / "rg-game.rsp"
    ins = [Path(f).resolve().as_posix() for f in a.first] + ins
    rsp.write_text(" ".join(ins) + " " + var.get("LINK_PATH", "") + " " + var.get("LINK_LIBRARIES", ""))
    link = [c for c in cmds if f"-o {a.target}" in c and "@" in c]
    if len(link) != 1:
        print("altlink: no link command", file=sys.stderr)
        return 2
    l = link[0]
    exe = out / a.target
    l = re.sub(r"@\S+\.rsp", lambda m: f"@{rsp.as_posix()}", l)
    l = l.replace(f"-o {a.target}", f"-o {exe}")
    stem = exe.with_suffix("")  # paths must not contain spaces (cmd /C quoting)
    l = re.sub(r"/implib:\S+", lambda m: f"/implib:{stem}.lib", l)
    l = re.sub(r"/pdb:\S+", lambda m: f"/pdb:{stem}.pdb", l)
    r = subprocess.run(l, cwd=bd, shell=True)
    if r.returncode == 0:
        print(f"altlink: linked {exe}")
    return r.returncode


if __name__ == "__main__":
    raise SystemExit(main())
