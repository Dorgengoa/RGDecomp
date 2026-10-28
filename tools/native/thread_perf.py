#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Per-field host cost of the RG_THREADS modes (docs/NATIVE-THREADS.md "Perf").

    python tools/native/thread_perf.py save  [--exe EXE] [--modes hle,native] [--at 1500,8000,23000]
    python tools/native/thread_perf.py measure [--exe EXE] [--modes hle,native] [--at ...] [--run 300] [--reps 2]

A save state carries its RG_THREADS mode (the kernel refuses a state of the other mode), so
`save` makes one power-on run per mode (golden input, headless, one rg-game at a time) and
saves a state at each field of --at into out/nthreads/perf/<exe-id>/<mode>/.  `measure` then
loads each state in its mode and runs --run fields, --reps times, modes interleaved (so
machine load hits every mode alike), and reports per milestone and mode:
  cpu/field   process CPU time (user + kernel, all host threads: GS worker, audio, file
              jobs included) / fields run, load and init excluded by subtracting a
              zero-field load of the same state
  step med    median RG_FIELD_TIMES step_ms (wall time of the field's ps2k_step: game,
              models, GPU submit) over the run
"""
import argparse
import ctypes
import ctypes.wintypes as W
import hashlib
import os
import statistics
import subprocess
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
GOLDEN = os.path.join(ROOT, "tools", "trace", "goldens", "newgame_battle.input.txt")


def exe_id(exe):
    return hashlib.sha256(open(exe, "rb").read()).hexdigest()[:16]


def cpu_of(p):
    ft = [W.FILETIME() for _ in range(4)]
    if ctypes.windll.kernel32.GetProcessTimes(W.HANDLE(int(p._handle)), *[ctypes.byref(f) for f in ft]):
        v = lambda f: ((f.dwHighDateTime << 32) | f.dwLowDateTime) / 1e7
        return v(ft[2]) + v(ft[3])
    return 0.0


def run(exe, mode, args, d, ft=None):
    os.makedirs(os.path.join(d, "saves"), exist_ok=True)
    env = dict(os.environ, RG_THREADS=mode)
    env.setdefault("RG_DATA", os.path.join(ROOT, "data"))
    env.setdefault("RG_GPU", "hw")
    if ft:
        env["RG_FIELD_TIMES"] = ft
    cmd = [exe, "--headless", "--saves", os.path.join(d, "saves"), "--input", GOLDEN] + args
    p = subprocess.Popen(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
    out, _ = p.communicate()
    return p.returncode, cpu_of(p), out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("what", choices=["save", "measure"])
    ap.add_argument("--exe", default=os.path.join(ROOT, "build", "nthreads-i686", "rg-game.exe"))
    ap.add_argument("--modes", default="hle,native")
    ap.add_argument("--at", default="1500,8000,23000")
    ap.add_argument("--run", type=int, default=300)
    ap.add_argument("--reps", type=int, default=2)
    a = ap.parse_args()
    base = os.path.join(ROOT, "out", "nthreads", "perf", exe_id(a.exe))
    at = [int(x) for x in a.at.split(",")]
    modes = a.modes.split(",")
    if a.what == "save":
        for m in modes:
            d = os.path.join(base, m)
            args = ["--fields", str(max(at))]
            for f in at:
                args += ["--save-state", "%d:%s" % (f, os.path.join(d, "s%d.rgstate" % f))]
            rc, cpu, out = run(a.exe, m, args, d)
            print("save %-7s rc=%d cpu=%.1fs" % (m, rc, cpu))
            if rc:
                print(out[-2000:])
                return 1
        return 0
    res = {}
    for f in at:
        for rep in range(a.reps):
            for m in modes:
                d = os.path.join(base, m)
                st = os.path.join(d, "s%d.rgstate" % f)
                if rep == 0:  # load + init cost: a zero-field run
                    rc, c0, _ = run(a.exe, m, ["--load-state", st, "--fields", str(f)], os.path.join(d, "z"))
                    res.setdefault((f, m), {"zero": c0, "cpu": [], "step": []})
                ft = os.path.join(d, "ft%d_%d.tsv" % (f, rep))
                rc, c, out = run(a.exe, m, ["--load-state", st, "--fields", str(f + a.run)], os.path.join(d, "r"), ft)
                if rc:
                    print("run %s %d rc=%d\n%s" % (m, f, rc, out[-1500:]))
                    return 1
                r = res[(f, m)]
                r["cpu"].append((c - r["zero"]) / a.run)
                steps = [float(ln.split("\t")[2]) for ln in open(ft, encoding="utf-8") if not ln.startswith("#")]
                r["step"].append(statistics.median(steps))
    print("%-7s %-7s %14s %14s" % ("field", "mode", "cpu/field ms", "step med ms"))
    for (f, m), r in sorted(res.items()):
        print("%-7d %-7s %14s %14s" % (f, m, "/".join("%.2f" % (x * 1000) for x in r["cpu"]),
                                       "/".join("%.2f" % x for x in r["step"])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
