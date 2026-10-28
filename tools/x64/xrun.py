#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""x64 bring-up runner (docs/X64-PLAN.md step 6): run an rg-game headless on the
golden route and report the end state, resolving a crash report through the exe's map.

    python tools/x64/xrun.py EXE [--fields N] [--ref EXE_I686] [--work DIR] [-- extra args]

Runs EXE (and --ref, the i686 exe of the same tree) with `--headless --fields N --input
<golden>` (RG_DATA = data/, RG_GPU = hw, fresh saves dir) and prints the last lines,
`rg-game: run_hash=...`, and for an `rg-game: EXCEPTION` report every rva resolved to
symbol+offset with the map next to the exe.  With --ref the two run hashes are compared
(the x64 gate: the same input gives the same run hash as i686).
"""
from __future__ import annotations

import argparse
import bisect
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
GOLDEN = PORT / "tools" / "trace" / "goldens" / "newgame_save2.input.txt"
ROW = re.compile(r"\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)")


def load_map(exe: Path):
    m = exe.with_suffix(".map")
    rows = []
    if m.exists():
        for ln in m.read_text(encoding="utf-8", errors="replace").splitlines():
            r = ROW.match(ln)
            if r:
                rows.append((int(r.group(4), 16), r.group(3), r.group(5)))
    rows.sort()
    return rows


def resolve(rows, base: int, rva: int) -> str:
    if not rows:
        return "?"
    keys = [r[0] for r in rows]
    i = bisect.bisect_right(keys, base + rva) - 1
    if i < 0:
        return "?"
    a, n, obj = rows[i]
    return f"{n}+0x{base + rva - a:x} ({obj})"


def run(exe: Path, fields: int, work: Path, extra: list[str]) -> tuple[int, str, str]:
    shutil.rmtree(work, ignore_errors=True)
    (work / "saves").mkdir(parents=True)
    env = dict(os.environ)
    env.setdefault("RG_DATA", str(PORT / "data"))
    env.setdefault("RG_GPU", "hw")
    cmd = [str(exe), "--headless", "--fields", str(fields), "--saves", str(work / "saves"),
           "--input", str(GOLDEN)] + extra
    r = subprocess.run(cmd, cwd=str(work), env=env, capture_output=True, text=True,
                       encoding="utf-8", errors="replace", timeout=7200)
    (work / "stdout.txt").write_text(r.stdout, encoding="utf-8")
    (work / "stderr.txt").write_text(r.stderr, encoding="utf-8")
    return r.returncode, r.stdout, r.stderr


def report(tag: str, exe: Path, rc: int, out: str, err: str) -> str | None:
    h = re.search(r"run_hash=([0-9a-f]+)", out)
    f = re.search(r"rg-game: fields=(\d+)", out)
    print(f"[{tag}] rc={rc} fields={f.group(1) if f else '?'} run_hash={h.group(1) if h else '-'}")
    m = re.search(r"EXCEPTION (0x[0-9A-F]+) at eip=0x([0-9A-F]+) \(image base 0x([0-9A-F]+), rva 0x([0-9A-F]+)\)(.*)", err)
    if m:
        rows = load_map(exe)
        base = int(m.group(3), 16)
        print(f"[{tag}] EXCEPTION {m.group(1)} at {resolve(rows, base, int(m.group(4), 16))}{m.group(5)}")
        st = re.search(r"stack words in the image \(rva\):(.*)", err)
        if st:
            for w in st.group(1).split()[:16]:
                print(f"    {w} {resolve(rows, base, int(w, 16))}")
    tail = [ln for ln in err.splitlines() if ln.strip()][-6:]
    for ln in tail:
        print(f"[{tag}] | {ln[:200]}")
    return h.group(1) if h else None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("exe")
    ap.add_argument("--fields", type=int, default=600)
    ap.add_argument("--ref")
    ap.add_argument("--work", default=str(PORT / "build" / "x64-run"))
    ap.add_argument("extra", nargs="*")
    a = ap.parse_args()
    exe = Path(a.exe).resolve()
    work = Path(a.work)
    rc, out, err = run(exe, a.fields, work / "x64", a.extra)
    hx = report("x64", exe, rc, out, err)
    if a.ref:
        ref = Path(a.ref).resolve()
        rc2, out2, err2 = run(ref, a.fields, work / "ref", a.extra)
        hr = report("ref", ref, rc2, out2, err2)
        same = hx is not None and hx == hr
        print(f"run hash {'EQUAL' if same else 'DIFFERENT'} at field {a.fields}")
        return 0 if same else 1
    return 0 if rc == 0 and hx else 1


if __name__ == "__main__":
    sys.exit(main())
