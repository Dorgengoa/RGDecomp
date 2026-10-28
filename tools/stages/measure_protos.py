#!/usr/bin/env python3
"""Measure transform 2: clang -fsyntax-only over game sources, classify the
prototype-related diagnostics.

    python tools/stages/measure_protos.py --mode raw|naive|staged [--sample N] [--jobs 16]

  raw     game/ as ingested, no header (what each file says on its own)
  naive   game/ + the unified header force-included (-include, RGP_SELF_<f>
          defined on the command line for the file's own definitions), no
          call/declaration rewrites: the conflicts a unified header exposes
  staged  out/protos-test/ (run_protos.py output): rewrites applied

Diagnostics are counted with and without the downgrade flags
(-Wno-int-conversion etc.: see docs/PROTOS.md).  Writes a per-diagnostic TSV
to out/protos-measure/<mode>.tsv.
"""
from __future__ import annotations

import argparse
import random
import re
import subprocess
import sys
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
CLANG = Path("../tools/llvm/bin/clang.exe")
BASE = ["--target=i686-pc-windows-msvc", "-fsyntax-only", "-ferror-limit=0",
        "-fno-caret-diagnostics", "-fno-color-diagnostics"]
DOWNGRADE = ["-Wno-int-conversion", "-Wno-incompatible-function-pointer-types",
             "-Wno-incompatible-pointer-types"]

CLASSES = [
    ("arity", r"too (many|few) arguments to function call"),
    ("conflict", r"conflicting types for|static declaration of .* follows non-static|"
                 r"conflicting declaration|functions that differ only in their return type"),
    ("void-value", r"incompatible type 'void'|returning 'void'|void value|"
                   r"from incompatible type 'void'|operands? .*'void'|"
                   r"cannot initialize .* with an rvalue of type 'void'|"
                   r"expression of scalar type \('void'|of type 'void'"),
    ("implicit-decl", r"call to undeclared function|implicit declaration|"
                      r"use of undeclared identifier"),
    ("int-ptr", r"\[-Wint-conversion\]"),
    ("ptr-type", r"\[-Wincompatible(-function)?-pointer-types\]"),
    ("cpp-conv", r"no matching function for call|cannot initialize a (parameter|variable|"
                 r"return object)|cannot convert|assigning to '.*' from incompatible type"),
]
CLS = [(n, re.compile(p)) for n, p in CLASSES]
DIAG = re.compile(r"^(.*?):(\d+):(\d+): (error|warning): (.*)$")


def classify(msg: str) -> str:
    for n, rx in CLS:
        if rx.search(msg):
            return n
    return "other"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--mode", choices=("raw", "naive", "staged"), required=True)
    ap.add_argument("--sample", type=int, default=0, help="random sample size (0 = all)")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--jobs", type=int, default=16)
    ap.add_argument("--strict", action="store_true", help="no downgrade flags")
    ap.add_argument("--staged-dir", type=Path, default=PORT / "out" / "protos-test")
    a = ap.parse_args()

    game = PORT / "game"
    rows = [ln.split("\t") for ln in
            (game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    files = sorted(r[0] for r in rows if r[3] in ("unit", "data") and
                   r[0].endswith((".c", ".cpp")))
    if a.sample:
        random.Random(a.seed).shuffle(files)
        files = sorted(files[:a.sample])
    root = a.staged_dir if a.mode == "staged" else game
    hdr_inc = a.staged_dir / "include"
    selfdefs: dict[str, list] = {}
    if a.mode == "naive":
        sys.path.insert(0, str(HERE))
        import protos
        for p in files:
            fi = protos.parse_file(p, (game / p).read_bytes(), {})
            selfdefs[p] = sorted({d.name for d in fi.defs})

    def run(p: str):
        cmd = [str(CLANG), *BASE, "-I", str(root / "include"), "-I", str(hdr_inc)]
        cmd += ["-std=c99"] if p.endswith(".c") else ["-std=c++17"]
        if not a.strict:
            cmd += DOWNGRADE
        if a.mode == "naive" and p.endswith(".c"):
            cmd += ["-include", "port/game_protos.h"]
            cmd += [f"-DRGP_SELF_{n}=1" for n in selfdefs[p]]
        cmd.append(str(root / p))
        r = subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8",
                           errors="replace")
        out = []
        for ln in r.stderr.splitlines():
            m = DIAG.match(ln)
            if m and m.group(4) == "error":
                out.append((p, int(m.group(2)), classify(m.group(5)), m.group(5)))
        return p, out

    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(run, files))
    cnt, fcnt = Counter(), Counter()
    outdir = PORT / "out" / "protos-measure"
    outdir.mkdir(parents=True, exist_ok=True)
    tag = a.mode + ("-strict" if a.strict else "") + (f"-s{a.sample}" if a.sample else "")
    with open(outdir / f"{tag}.tsv", "w", encoding="utf-8") as f:
        f.write("file\tline\tclass\tmessage\n")
        for p, diags in res:
            seen = set()
            for d in diags:
                cnt[d[2]] += 1
                seen.add(d[2])
                f.write(f"{d[0]}\t{d[1]}\t{d[2]}\t{d[3]}\n")
            for s in seen:
                fcnt[s] += 1
            if not diags:
                fcnt["clean-files"] += 1
    print(f"mode={tag} files={len(files)}")
    for k in [n for n, _ in CLASSES] + ["other"]:
        print(f"  {k:14s} errors={cnt[k]:6d} files={fcnt[k]}")
    print(f"  files with no errors: {fcnt['clean-files']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
