#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Syntax-check source files with the exact compile commands of a configured build tree.

Before a long ninja build (or while another lane builds the shared tree), compile only the
files you edited, every variant the tree has for them (default library and its native-only
clone, cmake/native_only.cmake), with -fsyntax-only: errors in seconds, no objects written.

  python tools/native/cc_check.py [--tree build/nrender2-i686] FILE [FILE ...]

FILE may be a path or a suffix (render/nr_interp.c).  Needs the tree's
compile_commands.json (CMAKE_EXPORT_COMPILE_COMMANDS, on in this repo's toolchain).  The
compiler must be on PATH or absolute in the command (tools/native/render_build.ps1 sets PATH).
"""
import argparse
import json
import os
import shlex
import subprocess
import sys

ap = argparse.ArgumentParser()
ap.add_argument("--tree", default="build/nrender2-i686")
ap.add_argument("--like", help="for a FILE the tree does not know yet (new file): use this file's commands")
ap.add_argument("files", nargs="+")
a = ap.parse_args()

db = json.load(open(os.path.join(a.tree, "compile_commands.json")))
rc = 0
for f in a.files:
    suf = f.replace("\\", "/")
    hits = [e for e in db if e["file"].replace("\\", "/").endswith(suf)]
    if not hits and a.like:
        like = [e for e in db if e["file"].replace("\\", "/").endswith(a.like)]
        src = os.path.abspath(f).replace("\\", "/")
        hits = []
        for e in like:
            e = dict(e)
            old = e["file"]
            e["command"] = (e.get("command") or " ".join(e["arguments"])).replace(old, src).replace(
                old.replace("/", "\\"), src)
            e["file"] = src
            hits.append(e)
    if not hits:
        print(f"{f}: not in {a.tree}/compile_commands.json")
        rc = 1
        continue
    for e in hits:
        cmd = e.get("command") or " ".join(e["arguments"])
        args = shlex.split(cmd, posix=False)
        # drop the output and dependency options, compile syntax only
        out, skip = [], False
        for x in args:
            if skip:
                skip = False
                continue
            if x in ("-o", "-MF", "-MT", "-MQ", "/Fo"):
                skip = True
                continue
            if x.startswith(("-o", "/Fo", "-MD", "-MMD", "-MF")) and x not in ("-o",):
                if x.startswith("-o") or x.startswith("/Fo") or x.startswith("-MF"):
                    continue
                if x in ("-MD", "-MMD"):
                    continue
            out.append(x.strip('"'))
        out.append("-fsyntax-only")
        tag = "native-only" if "RG_NATIVE_ONLY=1" in cmd else "default"
        p = subprocess.run(out, cwd=e["directory"], capture_output=True, text=True)
        msg = (p.stdout + p.stderr).strip()
        print(f"{f} [{tag}]: {'ok' if p.returncode == 0 else 'FAIL'}" + (f"\n{msg}" if msg else ""))
        rc |= p.returncode != 0
sys.exit(1 if rc else 0)
