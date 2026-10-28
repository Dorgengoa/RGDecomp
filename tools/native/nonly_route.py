#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Golden-route run of one rg-game build, with startup / memory numbers (docs/NATIVE-ONLY.md).

    python tools/native/nonly_route.py run EXE OUTDIR [--fields 31700] [--input GOLDEN]
    python tools/native/nonly_route.py startup EXE OUTDIR [--reps 3]
    python tools/native/nonly_route.py compare OUTDIR_A OUTDIR_B

run      copies EXE + .map into OUTDIR/bin, runs it headless (RG_GPU=hw) on the golden
         input with RG_TIMING, builds the milestones (tools/trace/timing.py build --map),
         and writes OUTDIR/route.json: run_hash, wall time, peak working set / private
         bytes (psutil, polled every 0.5 s), exe size.
startup  power-on to the end of field 1, REPS times (process wall time incl. init and
         shutdown; RG_GPU=hw, headless); OUTDIR/startup.json.
compare  route.json side by side + `timing.py align --nowrap` of the two milestone tables.

One rg-game process at a time (shared machine).
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
GOLDEN = PORT / "tools" / "trace" / "goldens" / "newgame_save1.input.txt"


def env_for(extra=None):
    e = dict(os.environ)
    e.setdefault("RG_DATA", str(PORT / "data"))
    e.setdefault("RG_GPU", "hw")
    for k in [k for k in e if k.startswith("RG_TRACE_") or k in ("RG_TIMING", "RG_IOP", "RG_AUDIO")]:
        e.pop(k)
    if extra:
        e.update(extra)
    return e


def run_proc(cmd, env, log, cwd):
    import psutil
    t0 = time.perf_counter()
    with open(log, "wb") as lf:
        p = subprocess.Popen(cmd, env=env, cwd=cwd, stdout=lf, stderr=subprocess.STDOUT)
        peak_ws = peak_priv = 0
        try:
            pp = psutil.Process(p.pid)
            while p.poll() is None:
                try:
                    mi = pp.memory_info()
                    peak_ws = max(peak_ws, getattr(mi, "peak_wset", mi.rss))
                    peak_priv = max(peak_priv, getattr(mi, "private", 0))
                except psutil.Error:
                    break
                time.sleep(0.5)
        finally:
            rc = p.wait()
    return rc, time.perf_counter() - t0, peak_ws, peak_priv


def run_hash(log: Path) -> str | None:
    for line in log.read_text(errors="replace").splitlines()[::-1]:
        if "run_hash=" in line:
            return line.split("run_hash=")[1].strip()
    return None


def copy_bin(exe: Path, out: Path) -> Path:
    b = out / "bin"
    b.mkdir(parents=True, exist_ok=True)
    for s in (exe, exe.with_suffix(".map")):
        shutil.copy2(s, b / s.name)
    return b / exe.name


def cmd_run(a):
    out = Path(a.outdir).resolve()
    exe = copy_bin(Path(a.exe), out)
    saves = out / "saves"
    if saves.exists():
        shutil.rmtree(saves)
    saves.mkdir(parents=True)
    tj = out / "port.jsonl"
    env = env_for({"RG_TIMING": str(tj)})
    cmd = [str(exe), "--headless", "--fields", str(a.fields), "--saves", str(saves), "--input", a.input]
    rc, wall, ws, priv = run_proc(cmd, env, out / "port.log", str(out))
    res = {"exe": str(Path(a.exe)), "exe_bytes": Path(a.exe).stat().st_size, "fields": a.fields, "rc": rc,
           "wall_s": round(wall, 1), "peak_wset_mb": round(ws / 2**20, 1), "peak_private_mb": round(priv / 2**20, 1),
           "run_hash": run_hash(out / "port.log")}
    subprocess.run([sys.executable, str(PORT / "tools" / "trace" / "timing.py"), "build", str(tj), "--map",
                    str(exe.with_suffix(".map"))], check=False, stdout=subprocess.DEVNULL)
    (out / "route.json").write_text(json.dumps(res, indent=1))
    print(json.dumps(res, indent=1))
    return 0 if rc == 0 else 1


def cmd_startup(a):
    out = Path(a.outdir).resolve()
    out.mkdir(parents=True, exist_ok=True)
    exe = Path(a.exe).resolve()
    times, peaks = [], []
    for i in range(a.reps):
        saves = out / f"su_saves{i}"
        shutil.rmtree(saves, ignore_errors=True)
        saves.mkdir()
        rc, wall, ws, _ = run_proc([str(exe), "--headless", "--fields", "1", "--saves", str(saves)], env_for(),
                                   out / f"startup{i}.log", str(out))
        times.append(round(wall, 3))
        peaks.append(round(ws / 2**20, 1))
    res = {"exe": str(exe), "wall_s": times, "min_s": min(times), "peak_wset_mb": peaks}
    (out / "startup.json").write_text(json.dumps(res, indent=1))
    print(json.dumps(res, indent=1))
    return 0


def cmd_compare(a):
    A, B = Path(a.a), Path(a.b)
    ra, rb = (json.loads((d / "route.json").read_text()) for d in (A, B))
    for k in ra:
        print(f"{k:18s} {ra[k]!s:40s} {rb.get(k)!s}")
    ma, mb = A / "port.milestones.tsv", B / "port.milestones.tsv"
    if ma.exists() and mb.exists():
        subprocess.run([sys.executable, str(PORT / "tools" / "trace" / "timing.py"), "align", "--nowrap",
                        str(ma), str(mb)], check=False)
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    r = sp.add_parser("run")
    r.add_argument("exe")
    r.add_argument("outdir")
    r.add_argument("--fields", type=int, default=31700)
    r.add_argument("--input", default=str(GOLDEN))
    s = sp.add_parser("startup")
    s.add_argument("exe")
    s.add_argument("outdir")
    s.add_argument("--reps", type=int, default=3)
    c = sp.add_parser("compare")
    c.add_argument("a")
    c.add_argument("b")
    a = ap.parse_args()
    return {"run": cmd_run, "startup": cmd_startup, "compare": cmd_compare}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
