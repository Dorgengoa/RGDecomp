#!/usr/bin/env python3
"""UB-relevant warning census of the game sources (docs/UB-AUDIT.md).

    python tools/ubaudit/wcensus.py BUILD_DIR [--jobs 4] [--only SUBSTR]
                                    [--out out/ubaudit/wcensus] [--warn LIST]
                                    [--define NAME[=V] ...] [--strict-vu0]

Takes every game compile (game/src, overrides/, missing/) from BUILD_DIR's
compile_commands.json and re-runs it with clang -fsyntax-only, the game's
`-w` replaced by `-Wno-everything` + the UB-relevant frontend warnings below
(the same flags otherwise: include order, D2 flags, RG_VU0_* defines).
Writes OUT/warnings.tsv (file, line, col, flag, message) and
OUT/classes.tsv (flag, sites, files), prints the class table.

--strict-vu0 adds -DRG_VU0_STRICT (port/vu0.h drops the file-scope VU0
register fallback) and reports ERRORS instead: every function that names the
VU0 model without a `vu0frame` RG_VU0_FRAME fails (`use of undeclared
identifier 'rg_vu0'`).  0 errors = no game code uses a per-file register file.

Front-end only (no codegen), so it costs a fraction of a build; still mind
the shared-PC limit (--jobs 4).
"""
from __future__ import annotations

import argparse
import collections
import json
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
WARN = ("-Wuninitialized -Wsometimes-uninitialized -Wshift-count-overflow "
        "-Wshift-count-negative -Wshift-negative-value -Wshift-overflow "
        "-Winteger-overflow -Wreturn-type -Warray-bounds -Warray-bounds-pointer-arithmetic "
        "-Wdivision-by-zero -Wunsequenced -Wnull-dereference -Wvarargs -Wfortify-source "
        "-Wconstant-conversion -Wbitfield-constant-conversion -Wfloat-overflow-conversion "
        "-Wreturn-stack-address -Wsizeof-array-argument -Wtautological-constant-out-of-range-compare "
        "-Wimplicit-const-int-float-conversion -Wnon-pod-varargs -Wuninitialized-const-reference "
        "-Wstring-plus-int -Wincompatible-library-redeclaration -Wbuiltin-memcpy-chk-size")
VU0_HINT = re.compile(r"rg_vu0|RG_VU0_|\b_v[a-z][a-z0-9]*\s*\(|\bVu0[A-Z]\w*|vu0inline")
DIAG = re.compile(r"^(.*?):(\d+):(\d+): (warning|error|fatal error): (.*?)(?: \[(-W[\w-]+)[^\]]*\])?$")


def game_file(f: str) -> bool:
    f = f.replace("\\", "/")
    return "/game/src/" in f or "/overrides/" in f or "/missing/" in f


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("build", type=Path)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--only", default="")
    ap.add_argument("--out", type=Path, default=PORT / "out" / "ubaudit" / "wcensus")
    ap.add_argument("--warn", default=WARN)
    ap.add_argument("--define", action="append", default=[])
    ap.add_argument("--strict-vu0", action="store_true")
    a = ap.parse_args()
    cc = json.loads((a.build / "compile_commands.json").read_text(encoding="utf-8"))
    jobs = []
    extra = " ".join(f"-D{d}" for d in a.define + (["RG_VU0_STRICT"] if a.strict_vu0 else []))
    for e in cc:
        f = e["file"]
        if not game_file(f) or (a.only and a.only not in f.replace("\\", "/")):
            continue
        if a.strict_vu0:
            try:
                src = Path(f).read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            if not VU0_HINT.search(src):
                continue
        cmd = e["command"]
        cmd = re.sub(r"\s-o\s+\S+", " ", cmd)
        cmd = cmd.replace(" -c ", " -fsyntax-only ")
        cmd = re.sub(r"\s-fsanitize\S*", " ", cmd)
        if a.strict_vu0:
            cmd = cmd.replace(" -w ", f" -w {extra} ")
        else:
            cmd = cmd.replace(" -w ", f" -Wno-everything {a.warn} {extra} ")
        jobs.append((f, cmd, e["directory"]))
    print(f"wcensus: {len(jobs)} game compiles", file=sys.stderr)

    def run(j):
        f, cmd, d = j
        r = subprocess.run(cmd, cwd=d, capture_output=True, text=True, errors="replace")
        return f, r.returncode, r.stderr

    rows, errs_files = [], 0
    with ThreadPoolExecutor(a.jobs) as ex:
        for f, rc, err in ex.map(run, jobs):
            if rc:
                errs_files += 1
            for ln in err.splitlines():
                m = DIAG.match(ln)
                if not m:
                    continue
                kind = m.group(4)
                if a.strict_vu0 and kind == "warning":
                    continue
                flag = m.group(6) or ("error" if kind != "warning" else "-W?")
                rows.append((m.group(1).replace("\\", "/"), m.group(2), m.group(3), flag,
                             m.group(5).replace("\t", " ")))
    a.out.mkdir(parents=True, exist_ok=True)
    rows = sorted(set(rows))
    with (a.out / "warnings.tsv").open("w", encoding="utf-8", newline="\n") as o:
        o.write("file\tline\tcol\tflag\tmessage\n")
        for r in rows:
            o.write("\t".join(r) + "\n")
    cls = collections.defaultdict(lambda: [0, set()])
    for r in rows:
        cls[r[3]][0] += 1
        cls[r[3]][1].add(r[0])
    with (a.out / "classes.tsv").open("w", encoding="utf-8", newline="\n") as o:
        o.write("flag\tsites\tfiles\n")
        for k, (n, fs) in sorted(cls.items(), key=lambda kv: -kv[1][0]):
            o.write(f"{k}\t{n}\t{len(fs)}\n")
            print(f"{n:6d} {len(fs):6d}  {k}")
    print(f"wcensus: {len(rows)} diagnostics, {errs_files} compiles failed -> {a.out}")
    return 1 if (a.strict_vu0 and rows) else 0


if __name__ == "__main__":
    sys.exit(main())
