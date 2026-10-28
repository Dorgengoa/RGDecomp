#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Prove that edits to port sources leave the i686 objects byte-identical
(docs/X64-PLAN.md: the i686 build must not change).

For every compile in an i686 build's compile_commands.json whose source is one
of the given files (or includes one of the given headers), the ORIGINAL and the
CURRENT version are compiled with the build's exact command AT THE SAME PATH
(the source's directory is mirrored into a temp dir, the edited files are put
there in their original, then their current form; include paths stay those of
the current tree, edited headers are shadowed by the mirror's copy), and the
two objects are compared byte for byte.  Compiling at the same path matters:
__FILE__ and the object's file record name the path.  --orig is a copy of the
tree from before the edit (e.g. the pre-x64 backup).  Optionally (--x64) the
current file is also compiled for x86_64-pc-windows-msvc (errors only).

    python tools/x64/i686_same.py --db build/<i686 dir> --orig ..-backups/port-pre-x64-20261025
        [--x64] FILE [FILE ...]      (port-relative: src/crt/crt_heap.c src/native/ovl/ovl_gen.h)

Exit 1 on any difference or x64 error.
"""
from __future__ import annotations

import argparse
import json
import os
import shlex
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(os.environ.get("RG_PORT_ROOT", Path(__file__).resolve().parents[2]))
N = lambda s: s.replace("\\", "/")  # noqa: E731


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--db", required=True)
    ap.add_argument("--orig", required=True)
    ap.add_argument("--x64", action="store_true")
    ap.add_argument("files", nargs="+")
    a = ap.parse_args()
    db = json.loads((Path(a.db) / "compile_commands.json").read_text(encoding="utf-8"))
    root = N(str(ROOT))
    want = [N(f) for f in a.files]
    srcs = [w for w in want if w.endswith((".c", ".cpp"))]
    hdrs = [w for w in want if w.endswith((".h", ".hpp", ".inc"))]
    ents = []
    for e in db:
        f = N(e["file"])
        rel = f[len(root) + 1:] if f.lower().startswith(root.lower() + "/") else None
        if rel is None:
            continue
        if rel in srcs:
            ents.append((e, rel))
        elif hdrs:
            try:
                t = Path(f).read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            # a TU sees the edited header only if its directory is on the TU's include
            # path (or is the TU's own directory): same-named headers elsewhere don't count
            incs = {N(x[2:]).rstrip("/").lower() for x in shlex.split(N(e["command"]), posix=True)
                    if x.startswith("-I")}
            incs.add(N(str(Path(f).parent)).lower())
            if any(Path(h).name in t and (root + "/" + str(Path(h).parent).replace("\\", "/")).lower()
                   in incs for h in hdrs):
                ents.append((e, rel))
    bad = 0
    tmp = Path(tempfile.mkdtemp(prefix="i686same_"))
    for e, rel in ents:
        src = Path(N(e["file"]))
        args = shlex.split(N(e["command"]), posix=True)
        out, skip = [], False
        for x in args:
            if skip:
                skip = False
                continue
            if x == "-o":
                skip = True
                continue
            out.append(x)
        mir = tmp / "m"
        if mir.exists():
            shutil.rmtree(mir)
        shutil.copytree(src.parent, mir / "src")
        hdir = mir / "hdr"
        hdir.mkdir()
        msrc = mir / "src" / src.name
        res = {}
        for tag in ("orig", "cur", "cur2"):
            base = Path(a.orig) if tag == "orig" else ROOT
            if rel in srcs:
                shutil.copyfile(base / rel, msrc)
            inc = []
            for h in hdrs:          # edited headers: the version under test, found first
                hp = base / h
                if hp.exists():
                    d = hdir / Path(h).parent.name
                    d.mkdir(exist_ok=True)
                    shutil.copyfile(hp, d / Path(h).name)
                    shutil.copyfile(hp, mir / "src" / Path(h).name) if (src.parent / Path(h).name).exists() else None
                    inc.append("-I" + N(str(d)))
            cmd = [out[0]] + inc + [N(str(msrc)) if N(x) == N(str(src)) else x for x in out[1:]]
            o = tmp / f"{tag}.obj"
            r = subprocess.run(cmd + ["-o", str(o)], cwd=e["directory"], capture_output=True, text=True)
            res[tag] = (r.returncode, o.read_bytes() if o.exists() else b"", r.stderr[-400:])
            if o.exists():
                if os.environ.get("RG_I686SAME_KEEP"):
                    k = Path(os.environ["RG_I686SAME_KEEP"])
                    k.mkdir(parents=True, exist_ok=True)
                    shutil.copyfile(o, k / f"{rel.replace('/', '_')}.{len(ents)}.{tag}.obj")
                o.unlink()
        # the COFF header's TimeDateStamp (bytes 4..7) is the compile time on the MSVC
        # target: masked; everything else must be equal
        strip = lambda b: b[:4] + b[8:] if len(b) > 8 else b  # noqa: E731
        ok = res["orig"][0] == 0 and res["cur"][0] == 0
        same = ok and strip(res["orig"][1]) == strip(res["cur"][1])
        nondet = strip(res["cur"][1]) != strip(res["cur2"][1])
        line = f"{'same' if same else ('NONDET' if nondet else 'DIFF')}  {rel}"
        if not same:
            bad += 1
            line += f"  (rc {res['orig'][0]}/{res['cur'][0]}) {res['cur'][2]}"
        if a.x64:
            cmd = [x for x in out if x != "-m32"]
            cmd = [("--target=x86_64-pc-windows-msvc" if x.startswith("--target=") else x) for x in cmd]
            r = subprocess.run(cmd + ["-o", str(tmp / "x64.obj")], cwd=e["directory"], capture_output=True,
                               text=True)
            line += "  x64 " + ("ok" if r.returncode == 0 else "ERROR " + r.stderr[-600:])
            bad += r.returncode != 0
        print(line, flush=True)
    shutil.rmtree(tmp, ignore_errors=True)
    print(f"{len(ents)} compiles, {bad} problems")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
