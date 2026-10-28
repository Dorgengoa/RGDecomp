#!/usr/bin/env python3
"""Build the game/ OBJECT libraries (cmake/game.cmake) with `-k 0` and write
an error census.

    python tools/gameerrors.py [--build build/i686-windows] [--target rg_game_objs]
                               [--log FILE]   # parse an existing build log only

Writes <build>/game_compile_errors.tsv (file, line, class, fix, message) and
<build>/game_compile_classes.tsv, and prints the classes.  `fix` is the
proposed fix category for a class (FIXES below; `?` = not triaged).
Run it from an environment where the build works (tools/build.ps1 sets up
vcvars; this script imports it the same way as tools/syntaxcheck.py).
"""
from __future__ import annotations

import argparse
import collections
import re
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(PORT / "tools"))
import syntaxcheck as S  # noqa: E402  (msvc_env, classify)

CMAKE = Path("../tools/cmake-3.31.7-windows-x86_64/bin/cmake.exe")
DIAG = re.compile(r"^(.*?)[:(](\d+)(?::|,)(\d+)\)?: (error|fatal error): (.*)$")
# proposed fix per error class (substring of the classified message)
FIXES = [
    ("should return a value", "flag:-Wno-return-mismatch (review: retail returns $v0)"),
    ("implicit function declaration", "flag:-Wno-implicit-function-declaration / protos"),
    ("cannot be defined in any other translation unit", "stage:dialect cxx-anon-extern"),
    ("argument type 'X' is incomplete", "stage:dialect proto-tag"),
    ("lvalue casts are not supported", "stage:dialect lvalue-cast"),
    ("conflicting types", "stage:protos"),
]


def fix_of(cls: str) -> str:
    for k, v in FIXES:
        if k in cls:
            return v
    return "?"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--build", type=Path, default=PORT / "build" / "i686-windows")
    ap.add_argument("--target", default="rg_game_objs")
    ap.add_argument("--jobs", type=int, default=0)
    ap.add_argument("--log", type=Path, help="parse this log instead of building")
    a = ap.parse_args()
    if a.log:
        text = a.log.read_text(encoding="utf-8", errors="replace")
    else:
        env = S.msvc_env()
        env["PATH"] = str(S.LLVM / "bin") + ";../tools/ninja;" + env["PATH"]
        cmd = [str(CMAKE), "--build", str(a.build), "--target", a.target, "--"]
        cmd += ["-k", "0"] + ([f"-j{a.jobs}"] if a.jobs else [])
        r = subprocess.run(cmd, capture_output=True, text=True, env=env,
                           encoding="utf-8", errors="replace")
        text = r.stdout + r.stderr
        (a.build / "game_build.log").write_text(text, encoding="utf-8")
    errs = []
    failed = set()
    for ln in text.splitlines():
        if ln.startswith("FAILED: "):
            failed.add(ln[8:].strip())
        m = DIAG.match(ln)
        if m:
            f = m.group(1).replace("\\", "/")
            if "/game/" in f:
                f = f.split("/game/", 1)[1]
            elif "/overrides/" in f:
                f = "overrides/" + f.split("/overrides/", 1)[1]
            errs.append((f, int(m.group(2)), m.group(5)))
    out = a.build / "game_compile_errors.tsv"
    with open(out, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("file\tline\tclass\tfix\tmessage\n")
        for f, ln, msg in errs:
            c = S.classify(msg)
            fh.write(f"{f}\t{ln}\t{c}\t{fix_of(c)}\t{msg}\n")
    cls = collections.Counter(S.classify(m) for _, _, m in errs)
    files = collections.defaultdict(set)
    for f, _, m in errs:
        files[S.classify(m)].add(f)
    with open(a.build / "game_compile_classes.tsv", "w", encoding="utf-8", newline="\n") as fh:
        fh.write("errors\tfiles\tclass\tfix\texamples\n")
        for c, n in cls.most_common():
            fh.write(f"{n}\t{len(files[c])}\t{c}\t{fix_of(c)}\t{' '.join(sorted(files[c])[:3])}\n")
    nobj = len(re.findall(r"^\[\d+/\d+\] Building", text, re.M))
    print(f"{nobj} compile steps run, {len(failed)} failed objects, {len(errs)} errors, "
          f"{len(cls)} classes -> {out}")
    for c, n in cls.most_common(30):
        print(f"{n:6d} {len(files[c]):5d}  {fix_of(c)[:30]:30s} {c[:100]}")
    return 1 if (errs or failed) else 0


if __name__ == "__main__":
    sys.exit(main())
