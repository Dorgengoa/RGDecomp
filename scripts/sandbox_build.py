#!/usr/bin/env python3
"""Compile and byte-score functions WITHOUT touching the shared build state.

    sandbox_build.py <symbol>...        compile these on the host, then score
    sandbox_build.py --all              everything in config/units.txt with a source
    sandbox_build.py --tag NAME         use a different sandbox (default: sbx)

Why this exists: hostbuild.py does `rm -rf ~/rgd/work` and writes build/obj,
and status.py writes objdiff.json -- so two sessions working the same tree at
once will wipe each other's remote tree mid-compile and score each other's
objects. That is the same stale/clobbered-object failure class the tree has
already been bitten by twice (status.py without --host; a compile error leaving
the previous object in place), reached from a third side.

This keeps the whole round trip in its own namespace:

    remote  ~/rgd/work-<tag>          instead of ~/rgd/work
    local   build/obj-<tag>/          instead of build/obj/
    score   bytecheck against SCUS_974.90 itself -- no objdiff.json, so nothing
            the other session reads or writes is touched.

The compiler, its flags and the byte comparison are identical to the shared
path, so a number from here is comparable with the board. Only the plumbing
differs.
"""
from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import rgd

HOST = rgd.BUILD_HOST
KEY = rgd.SSH_KEY
CC = "../mwcps2-3.0.1b210-060308/mwccps2.exe"
CC_FLAGS = ("-O4 -c -Cpp_exceptions off -RTTI off -strings readonly "
            "-nostdinc -stderr -i include")
SSH = ["ssh", "-i", str(KEY), "-o", "StrictHostKeyChecking=no",
       "-o", "UserKnownHostsFile=/dev/null", "-o", "BatchMode=yes"]
CHUNK = 12


def build(symbols: list, tag: str) -> list:
    remote = f"{rgd.REMOTE_ROOT}/work-{tag}"
    objdir = rgd.ROOT / "build" / f"obj-{tag}"
    objdir.mkdir(parents=True, exist_ok=True)

    srcs = [(s, rgd.src_path(s)) for s in symbols]
    missing = [s for s, p in srcs if p is None]
    srcs = [(s, p) for s, p in srcs if p is not None]
    rel = [str(p.relative_to(rgd.ROOT)).replace("\\", "/") for _, p in srcs]

    push = subprocess.Popen(["tar", "czf", "-", "include"] + rel,
                            cwd=rgd.ROOT, stdout=subprocess.PIPE)
    subprocess.run(SSH + [HOST, f"rm -rf {remote} && mkdir -p {remote} "
                                f"&& tar xzf - -C {remote}"],
                   cwd=rgd.ROOT, stdin=push.stdout)
    push.wait()

    # Drop the old object first: a failed compile that leaves the previous one
    # in place reads exactly as "the edit changed nothing".
    for s, _ in srcs:
        (objdir / f"{s}.o").unlink(missing_ok=True)

    for i in range(0, len(srcs), CHUNK):
        part = list(zip([s for s, _ in srcs], rel))[i:i + CHUNK]
        # * NEVER PIPE THE COMPILER STRAIGHT INTO `head`.  `head -8` closes
        # the pipe after eight lines, mwcc takes SIGPIPE, and a unit with more
        # than eight lines of WARNINGS dies before it writes its object -- so
        # it reads as "failed to compile" with no error in the log, and it
        # does so NONDETERMINISTICALLY (MenuResGroupStacksInit_42c810 failed in one batch and
        # matched in the next).  Redirect to a file, then head the file.
        script = "; ".join(
            f'echo "== {s}"; ../wibo {CC} {CC_FLAGS} {r} -o {s}.o '
            f'> {s}.log 2>&1; head -8 {s}.log'
            for s, r in part)
        r = subprocess.run(SSH + [HOST, f"cd {remote} && {script}"],
                           capture_output=True, text=True)
        cur = None
        for line in r.stdout.splitlines():
            if line.startswith("== "):
                cur = line[3:]
            elif line.strip():
                print(f"  [{cur}] {line}")

    pull = subprocess.Popen(SSH + [HOST, f"cd {remote} && tar czf - *.o 2>/dev/null"],
                            stdout=subprocess.PIPE)
    subprocess.run(["tar", "xzf", "-", "-C",
                    str(objdir.relative_to(rgd.ROOT)).replace("\\", "/")],
                   cwd=rgd.ROOT, stdin=pull.stdout)
    pull.wait()

    failed = [s for s, _ in srcs if not (objdir / f"{s}.o").exists()]
    return missing, failed, objdir


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("symbols", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--tag", default="sbx")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--align", action="store_true")
    a = ap.parse_args()

    syms = a.symbols or ([s for s in rgd.registered() if rgd.src_path(s)]
                         if a.all else [])
    if not syms:
        ap.error("name some symbols, or pass --all")

    missing, failed, objdir = build(syms, a.tag)
    if missing:
        print("no source: " + " ".join(missing))
    if failed:
        print("FAILED TO COMPILE: " + " ".join(failed))

    # Score in bytes, with bytecheck pointed at the sandbox objects.
    import bytecheck
    rgd.OBJ_DIR = bytecheck.rgd.OBJ_DIR = objdir
    table = bytecheck.symbol_addresses()
    retail = bytecheck.RETAIL.read_bytes()

    if a.align:
        for s in syms:
            bytecheck.align(s, table, retail)
        return 0

    rows = []
    for s in syms:
        r = bytecheck.check(s, table, retail,
                            a.verbose and len(syms) == 1)
        if r is not None:
            rows.append(r)
    rows.sort(key=lambda r: (r[3] is None, -(len(r[3]) if r[3] else 0)))
    print(f"\n{'function':<28} {'words':>6} {'bad':>5}  notes")
    matched = 0
    for sym, vram, n, bad, notes in rows:
        cell = "?" if bad is None else ("MATCH" if not bad else str(len(bad)))
        matched += (bad is not None and not bad)
        print(f"{sym:<28} {(n // 4) if n else 0:>6} {cell:>5}  "
              f"{'; '.join(sorted(set(notes)))}")
    print(f"\n{matched}/{len(rows)} byte-identical "
          f"({len(failed)} failed to compile, {len(missing)} have no source)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
