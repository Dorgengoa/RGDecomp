#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Relink rg-game.exe from an EXISTING build tree's objects and libraries, with some sources
recompiled from the working tree (docs/WIDESCREEN.md "Stage 3 gaps").

Use when the shared tree is mid-change in a lane you do not own (e.g. the renderer agent's
src/native/render) and you need an exe that differs from a known-good build ONLY in your
own files: the build tree's objects stay as they were built, the named sources are
compiled with that tree's own flags (compile_commands.json) into OUT, and the link puts
those objects first (a library member defining the same symbols is then not pulled).
The exe built from the tree unchanged (BUILD/rg-game.exe) is the same-tree baseline.

    python tools/wide/relink.py --build build/wide3-i686 --out out/wide4/r1 \\
           src/settings/rg_layout.c [more sources]
Writes OUT/rg-game.exe and OUT/rg-game.map.  Nothing in BUILD is written.
"""
import argparse
import json
import re
import shlex
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]


def ninja_link(build: Path):
    """(inputs, variables) of the rg-game.exe link statement in BUILD/build.ninja"""
    lines = (build / "build.ninja").read_text(errors="replace").splitlines()
    for i, ln in enumerate(lines):
        if ln.startswith("build rg-game.exe:"):
            rhs = ln.split(":", 1)[1].split()
            ins = []
            for tok in rhs[1:]:
                if tok in ("|", "||"):
                    break
                ins.append(tok.replace("$:", ":"))
            var = {}
            for v in lines[i + 1:]:
                m = re.match(r"  (\w+) = (.*)", v)
                if not m:
                    break
                var[m.group(1)] = m.group(2)
            return ins, var
    raise SystemExit("relink: no rg-game.exe link statement in build.ninja")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--build", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("sources", nargs="+")
    a = ap.parse_args(argv)
    build = Path(a.build).resolve()
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    cc = json.loads((build / "compile_commands.json").read_text())
    objs = []
    for src in a.sources:
        sp = (PORT / src).resolve()
        ent = next((e for e in cc if Path(e["file"]).resolve() == sp), None)
        if ent is None:
            raise SystemExit(f"relink: {src} not in {build}/compile_commands.json")
        args = shlex.split(ent["command"], posix=False)
        o = out / (sp.stem + ".obj")
        for k, t in enumerate(args):
            if t == "-o":
                args[k + 1] = str(o)
        args = [t.strip('"') for t in args]
        p = subprocess.run(args, cwd=ent["directory"], capture_output=True, text=True)
        sys.stderr.write(p.stdout + p.stderr)
        if p.returncode:
            return p.returncode
        objs.append(o.as_posix())
    ins, var = ninja_link(build)
    rsp = out / "rg-game.rsp"
    rsp.write_text(" ".join(objs + ins) + " " + var.get("LINK_PATH", "") + " " + var.get("LINK_LIBRARIES", ""))
    cmd = [r"../tools\llvm\bin\clang++.exe", "--target=i686-pc-windows-msvc", "-nostartfiles", "-nostdlib"]
    cmd += shlex.split(var.get("FLAGS", ""), posix=False) + shlex.split(var.get("LINK_FLAGS", ""), posix=False)
    cmd += [f"@{rsp}", "-o", str(out / "rg-game.exe"), "-Xlinker", "/MANIFEST:EMBED",
            "-Xlinker", f"/implib:{out / 'rg-game.lib'}", "-Xlinker", f"/pdb:{out / 'rg-game.pdb'}",
            "-Xlinker", "/version:0.0"]
    p = subprocess.run(cmd, cwd=str(build), capture_output=True, text=True)
    sys.stderr.write(p.stdout + p.stderr)
    if p.returncode == 0:
        print(f"relink: {out / 'rg-game.exe'}")
    return p.returncode


if __name__ == "__main__":
    sys.exit(main())
