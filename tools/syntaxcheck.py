#!/usr/bin/env python3
"""clang -fsyntax-only over every compiled game/ file (MANIFEST kind unit or
data; kind `excluded` is skipped), with the port include order and the D2
flags, then an error-class census.

    python tools/syntaxcheck.py [--jobs 8] [--batch 40] [--limit N] [--out DIR]

Include order (docs/PORT-HEADERS.md):  -include port/prelude.h
    -I include  (port replacement headers: vu0inline.h, libvu0.h, port/...)
    -I game/include
The MSVC x86 INCLUDE (system headers) is imported from vcvarsall like
tools/build.ps1 does.  Writes <out>/syntax_errors.tsv (one row per error)
and <out>/syntax_classes.tsv, prints the top classes.
"""
from __future__ import annotations

import argparse
import collections
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PORT = Path(__file__).resolve().parent.parent
LLVM = Path(os.environ.get("LLVM_ROOT", "../tools/llvm"))
VCVARS = [
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat",
]
D2 = ["-target", "i686-pc-windows-msvc", "-m32", "-msse2", "-mfpmath=sse",
      "-fwrapv", "-fno-strict-aliasing", "-fno-delete-null-pointer-checks"]
# Game-only flags, the same as the rg_game_* CMake targets (cmake/game.cmake):
# docs/PROTOS.md (C int<->pointer conversions are left to the compiler).
C_FLAGS = ["-Wno-int-conversion", "-Wno-incompatible-pointer-types",
           "-Wno-incompatible-function-pointer-types", "-fgnu89-inline",
           "-Wno-implicit-function-declaration", "-Wno-return-mismatch"]
CXX_FLAGS: list[str] = ["-Wno-return-mismatch", "-Wno-c++11-narrowing"]
DIAG = re.compile(r"^(.*?):(\d+):(\d+): (error|fatal error): (.*)$")


def msvc_env() -> dict[str, str]:
    env = dict(os.environ)
    env["PATH"] = env.get("PATH", "").replace('"', "")
    if env.get("INCLUDE"):
        return env
    vc = next((v for v in VCVARS if Path(v).exists()), None)
    if not vc:
        return env
    r = subprocess.run(f'cmd /c ""{vc}" x86 >nul 2>&1 && set"', shell=True,
                       capture_output=True, text=True, env=env)
    for ln in r.stdout.splitlines():
        if "=" in ln:
            k, v = ln.split("=", 1)
            env[k] = v
    return env


def classify(msg: str) -> str:
    m = re.sub(r"'[^']*'", "'X'", msg)
    m = re.sub(r"\b\d+\b", "N", m)
    m = re.sub(r"\(aka [^)]*\)", "", m)
    return m.strip()


def run_batch(files: list[str], cxx: bool, env: dict) -> list[tuple]:
    exe = str(LLVM / "bin" / ("clang++.exe" if cxx else "clang.exe"))
    std = ["-std=gnu++17", *CXX_FLAGS] if cxx else ["-std=gnu99", *C_FLAGS]
    cmd = [exe, "-fsyntax-only", "-w", "-ferror-limit=0", "-fno-color-diagnostics",
           *D2, *std, "-include", "port/prelude.h",
           "-I", str(PORT / "include"), "-I", str(PORT / "game" / "include"), *files]
    r = subprocess.run(cmd, capture_output=True, text=True, env=env,
                       encoding="utf-8", errors="replace", cwd=str(PORT / "game"))
    out = []
    for ln in r.stderr.splitlines():
        m = DIAG.match(ln)
        if m:
            out.append((m.group(1).replace("\\", "/"), int(m.group(2)), m.group(5)))
    if r.returncode and not out:
        out.append((files[0] if len(files) == 1 else "<batch>", 0,
                    "driver failure: " + r.stderr.strip()[-200:]))
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--batch", type=int, default=40)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--out", type=Path, default=PORT / "build" / "syntax")
    ap.add_argument("--only", default="", help="substring filter on paths")
    a = ap.parse_args()
    rows = [ln.split("\t") for ln in (PORT / "game" / "MANIFEST.tsv")
            .read_text(encoding="utf-8").splitlines()[1:]]
    files = [r[0] for r in rows if r[3] in ("unit", "data")
             and r[0].endswith((".c", ".cpp")) and a.only in r[0]]
    nexcl = sum(1 for r in rows if r[3] == "excluded")
    if a.limit:
        files = files[:a.limit]
    env = msvc_env()
    jobs = []
    for cxx in (False, True):
        sel = [f for f in files if f.endswith(".cpp") == cxx]
        for i in range(0, len(sel), a.batch):
            jobs.append((sel[i:i + a.batch], cxx))
    errs: list[tuple] = []
    with ThreadPoolExecutor(a.jobs) as ex:
        for res in ex.map(lambda j: run_batch(j[0], j[1], env), jobs):
            errs.extend(res)
    a.out.mkdir(parents=True, exist_ok=True)
    with open(a.out / "syntax_errors.tsv", "w", encoding="utf-8", newline="\n") as fh:
        fh.write("file\tline\tclass\tmessage\n")
        for f, ln, msg in errs:
            fh.write(f"{f}\t{ln}\t{classify(msg)}\t{msg}\n")
    cls = collections.Counter()
    cls_files: dict[str, set] = collections.defaultdict(set)
    for f, ln, msg in errs:
        c = classify(msg)
        cls[c] += 1
        cls_files[c].add(f)
    bad = {f for f, _, _ in errs}
    with open(a.out / "syntax_classes.tsv", "w", encoding="utf-8", newline="\n") as fh:
        fh.write("errors\tfiles\tclass\texamples\n")
        for c, n in cls.most_common():
            ex_ = sorted(cls_files[c])[:3]
            fh.write(f"{n}\t{len(cls_files[c])}\t{c}\t{' '.join(ex_)}\n")
    print(f"checked {len(files)} files ({nexcl} excluded by MANIFEST), "
          f"{len(bad)} with errors, {len(errs)} errors, {len(cls)} classes")
    for c, n in cls.most_common(25):
        print(f"{n:7d} {len(cls_files[c]):6d}  {c[:110]}   e.g. {sorted(cls_files[c])[0]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
