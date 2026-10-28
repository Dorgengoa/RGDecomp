#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Relink rg-game from an existing build dir with a few objects replaced
(docs/TEST-FIXTURES.md "Route").  For testing a new override or a changed
game file in minutes when the build dir you would normally rebuild is stale
(a full rebuild is ~23k objects, hours at -j4) or belongs to another lane.

    python tools/fixtures/relink.py --build-dir build/battle-i686 --out out/route/exe1 \\
        overrides/src/main/ai/ActionPacketInitBattleDefeat_3e33e0.cpp [more sources]

Each source is compiled with the build dir's own compile command for the
same relative path (overrides/<p> uses the command of game/<p>; any other
file the command of that file) into <out>/obj/, and the link of rg-game.exe
(rule and inputs read from <build-dir>/build.ninja) is rerun with those
objects in place of the originals, writing <out>/rg-game.exe, .map, .pdb.
Nothing in the build dir is written.  The result is an ordinary rg-game
(save states, fixtures and run_from.py --exe accept it; the link map names
the replaced objects by their own file names, which the save-state map
classifies as GAME code like any bare object).  A source whose object lives in
a static library (src/host, src/runtime, ...) replaces its member in a copy
of that library (<out>/lib/), so the map still says lib:obj.  Note: a source
that changes a header's struct layout needs every includer that depends on
it listed too (relink does not track dependencies).
"""
from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
LLVM = Path(os.environ.get("LLVM_ROOT", "../tools/llvm")) / "bin"
VCVARS = [
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat",
]


def vc_env() -> dict:
    vc = next((p for p in VCVARS if Path(p).exists()), None)
    if not vc:
        raise SystemExit("relink: vcvarsall.bat not found")
    out = subprocess.run(f'cmd.exe /c ""{vc}" x86 >nul 2>&1 && set"', shell=True, capture_output=True,
                         text=True, errors="replace").stdout
    env = dict(os.environ)
    for line in out.splitlines():
        if "=" in line:
            k, v = line.split("=", 1)
            env[k] = v
    return env


def ninja_unescape(tok: str) -> str:
    return re.sub(r"\$(.)", lambda m: m.group(1), tok)


def link_block(build_dir: Path):
    """(explicit inputs, variables) of `build rg-game.exe:`"""
    lines = (build_dir / "build.ninja").read_text(encoding="utf-8", errors="replace").splitlines()
    for i, ln in enumerate(lines):
        if ln.startswith("build rg-game.exe: "):
            break
    else:
        raise SystemExit("relink: no rg-game.exe link in build.ninja")
    # join `$`-continued lines
    body = ln
    j = i
    while body.endswith("$") and not body.endswith("$$"):
        j += 1
        body = body[:-1] + lines[j].lstrip()
    toks = re.split(r"(?<!\$) ", body)
    toks = [t for t in toks if t]
    ins = []
    for t in toks[3:]:
        if t in ("|", "||"):
            break
        ins.append(ninja_unescape(t))
    var = {}
    for ln2 in lines[j + 1:]:
        if not ln2.startswith("  "):
            break
        k, _, v = ln2.strip().partition(" = ")
        var[k] = v
    return ins, var


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--build-dir", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--prebuilt", action="append", default=[], metavar="SRC=OBJ",
                    help="use an already compiled object for SRC (e.g. one from an earlier relink "
                         "when the tree's SRC has moved on)")
    ap.add_argument("sources", nargs="+",
                    help="SRC, or SRC=GAMEPATH: compile SRC (any path, e.g. a scratch copy of a "
                         "game file under out/) with the compile command of GAMEPATH")
    a = ap.parse_args(argv)
    bd = Path(a.build_dir).resolve()
    out = Path(a.out).resolve()
    (out / "obj").mkdir(parents=True, exist_ok=True)
    env = vc_env()
    cc = {}
    for e in json.loads((bd / "compile_commands.json").read_text(encoding="utf-8")):
        cc[os.path.normcase(os.path.normpath(e["file"]))] = e
    ins, var = link_block(bd)
    for src in a.sources:
        like = None
        if "=" in src:
            src, like = src.split("=", 1)
        sp = Path(src).resolve()
        if like:
            key_rel = Path(like).resolve().relative_to(PORT)
        else:
            rel = sp.relative_to(PORT)
            key_rel = Path("game", *rel.parts[1:]) if rel.parts[0] == "overrides" else rel
        e = cc.get(os.path.normcase(os.path.normpath(str(PORT / key_rel))))
        if not e:
            raise SystemExit(f"relink: no compile command for {key_rel} in {bd}")
        args = shlex.split(e["command"], posix=False)
        oi = args.index("-o")
        old_obj = args[oi + 1]
        new_obj = out / "obj" / (sp.name + ".obj")
        args[oi + 1] = str(new_obj)
        args[-1] = str(sp)
        pre = {os.path.normcase(str(Path(x.split("=", 1)[0]).resolve())): x.split("=", 1)[1] for x in a.prebuilt}
        if os.path.normcase(str(sp)) in pre:
            new_obj.write_bytes(Path(pre[os.path.normcase(str(sp))]).read_bytes())
        else:
            r = subprocess.run(args, cwd=e["directory"], env=env)
            if r.returncode:
                raise SystemExit(f"relink: compile of {src} failed")
        on = os.path.normcase(os.path.normpath(old_obj))
        hit = [k for k, t in enumerate(ins) if os.path.normcase(os.path.normpath(t)) == on]
        if len(hit) > 1:
            raise SystemExit(f"relink: {old_obj} is a link input {len(hit)} times")
        if hit:
            ins[hit[0]] = new_obj.as_posix()
        else:
            # a static library member (src/host, src/runtime, ...): replace the
            # member in a copy of the library (same member name, so the link
            # map and the save-state classification see lib:obj as before)
            m = re.search(r"[\\/]([^\\/]+)\.dir[\\/]", old_obj)
            libs = var.get("LINK_LIBRARIES", "").split()
            cand = [l for l in libs if m and Path(l).stem == m.group(1)]
            if not cand:
                raise SystemExit(f"relink: {old_obj}: neither a link input nor a member of a known library")
            lib = cand[0]
            copy = out / "lib" / Path(lib).name
            if not copy.exists() or copy.stat().st_mtime < (bd / lib).stat().st_mtime:
                copy.parent.mkdir(exist_ok=True)
                copy.write_bytes((bd / lib).read_bytes())
            r = subprocess.run([str(LLVM / "llvm-ar.exe"), "r", str(copy), str(new_obj)], env=env)
            if r.returncode:
                raise SystemExit(f"relink: llvm-ar on {copy} failed")
            var["LINK_LIBRARIES"] = " ".join(copy.as_posix() if l == lib else l for l in libs)
        print(f"relink: {key_rel} -> {new_obj}")
    rsp = out / "rg-game.rsp"
    rsp.write_text(" ".join(f'"{t}"' if " " in t else t for t in ins) + " " + var.get("LINK_PATH", "") + " "
                   + var.get("LINK_LIBRARIES", ""), encoding="utf-8")
    exe = out / "rg-game.exe"
    cmd = (f'../tools\\llvm\\bin\\clang++.exe --target=i686-pc-windows-msvc -nostartfiles -nostdlib '
           f'{var.get("FLAGS", "")} {var.get("LINK_FLAGS", "")} @{rsp.as_posix()} -o {exe.as_posix()} -Xlinker /MANIFEST:EMBED '
           f'-Xlinker /implib:{out / "rg-game.lib"} -Xlinker /pdb:{out / "rg-game.pdb"} -Xlinker /version:0.0')
    r = subprocess.run(cmd, cwd=bd, env=env, shell=True)
    if r.returncode:
        print("relink: link failed")
        return 1
    print(f"relink: {exe}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
