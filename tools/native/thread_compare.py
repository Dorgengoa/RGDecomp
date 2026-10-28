#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Native threads vs the kernel HLE oracle (docs/NATIVE-THREADS.md "Verification").

    python tools/native/thread_compare.py [--exe build/nthreads-i686/rg-game.exe] [--fields 9000]
                                          [--from title|field|battle] [--run K]
                                          [--modes hle,native] [--shots a,b,c] [--timing] [--out DIR]
                                          [--input SCRIPT] [--spec LABEL=EXE:MODE ...]

Runs rg-game once per RG_THREADS mode (one process at a time, headless, golden input,
fresh saves dir each), then compares what each run prints and writes:
  run_hash   the runtime's run hash (kernel trace hash + clock + audio + pad words,
             folded every field): equal means every field's kernel event sequence matched
  shots      --shot PNGs at the listed fields (byte hash of the file)
  timing     (--timing) RG_TIMING records -> timing.py build + align --nowrap
  log        RG_THREADS_LOG's exit line (services, steps, deferred preemptions)
  cost       (--windows a-b,c-d) RG_FIELD_TIMES per mode: mean / median step_ms (the field's
             ps2k_step: game + models + GPU submit, wall clock) over each field window, and
             the process CPU time (user+kernel) of the whole run
Modes: native (slice 5, frame-driven kernel), frame (slices 2-3), service, hle (oracle).
--from M loads the milestone state of the exe's fixture set (run_from.py; the state
carries the mode it was saved in, so --from compares only the mode the set was made
with: use it for determinism, not for hle-vs-native).
Exit 0 when run hashes and shots are equal across modes.
"""
import argparse
import hashlib
import os
import re
import shutil
import subprocess
import sys
import time

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
PY = sys.executable
GOLDEN = os.path.join(ROOT, "tools", "trace", "goldens", "newgame_battle.input.txt")


def sha(path):
    try:
        return hashlib.sha256(open(path, "rb").read()).hexdigest()[:16]
    except OSError:
        return "-"


def run_one(a, mode, out, exe=None, label=None):
    exe = os.path.abspath(exe or a.exe)
    d = os.path.join(out, label or mode)
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(os.path.join(d, "saves"))
    env = dict(os.environ)
    env["RG_THREADS"] = mode
    env["RG_THREADS_LOG"] = "1"
    env.setdefault("RG_DATA", os.path.join(ROOT, "data"))
    env.setdefault("RG_GPU", "hw")
    if a.timing:
        env["RG_TIMING"] = os.path.join(d, "port.jsonl")
    if a.kcensus:
        env["RG_KCENSUS"] = os.path.join(d, "kcensus.tsv")
    if a.windows:
        env["RG_FIELD_TIMES"] = os.path.join(d, "field_times.tsv")
    shots = [int(x) for x in a.shots.split(",") if x] if a.shots else []
    extra = []
    for f in shots:
        extra += ["--shot", "%d:%s" % (f, os.path.join(d, "f%05d.png" % f))]
    if a.from_:
        cmd = [PY, os.path.join(ROOT, "tools", "fixtures", "run_from.py"), a.from_, "--run", str(a.run),
               "--exe", exe, "--no-regen", "--"] + extra
    else:
        cmd = [exe, "--headless", "--fields", str(a.fields), "--saves", os.path.join(d, "saves"),
               "--input", a.input] + extra
    t = time.time()
    p = subprocess.Popen(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                         errors="replace")
    out_text, _ = p.communicate()
    cpu = proc_cpu(p)
    p = subprocess.CompletedProcess(cmd, p.returncode, out_text)
    open(os.path.join(d, "log.txt"), "w", encoding="utf-8").write(p.stdout)
    m = re.findall(r"run_hash=([0-9a-f]+)", p.stdout)
    th = re.findall(r"rg_threads: mode=.*", p.stdout)
    res = {"mode": label or mode, "rc": p.returncode, "run_hash": m[-1] if m else "-", "wall": time.time() - t,
           "threads": th[-1] if th else "-", "shots": {f: sha(os.path.join(d, "f%05d.png" % f)) for f in shots},
           "dir": d, "cpu": cpu, "cost": windows(os.path.join(d, "field_times.tsv"), a.windows)}
    if a.timing and os.path.exists(env["RG_TIMING"]):
        subprocess.run([PY, os.path.join(ROOT, "tools", "trace", "timing.py"), "build", env["RG_TIMING"]],
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return res


def proc_cpu(p):
    """user + kernel seconds of a finished child (Windows: GetProcessTimes on its handle;
    the direct child only, so run_from.py runs report the wrapper)"""
    try:
        import ctypes
        import ctypes.wintypes as W
        ft = [W.FILETIME() for _ in range(4)]
        h = int(p._handle)
        if ctypes.windll.kernel32.GetProcessTimes(W.HANDLE(h), *[ctypes.byref(f) for f in ft]):
            v = lambda f: ((f.dwHighDateTime << 32) | f.dwLowDateTime) / 1e7
            return v(ft[2]) + v(ft[3])
    except Exception:
        pass
    return 0.0


def windows(path, spec):
    """mean / median step_ms per field window 'a-b' (fields a < f <= b)"""
    out = {}
    if not spec or not os.path.exists(path):
        return out
    rows = []
    for ln in open(path, encoding="utf-8"):
        if ln.startswith("#"):
            continue
        c = ln.split("\t")
        if len(c) >= 3:
            rows.append((int(c[0]), float(c[2])))
    for w in spec.split(","):
        lo, hi = (int(x) for x in w.split("-"))
        v = sorted(ms for f, ms in rows if lo < f <= hi)
        if v:
            out[w] = (sum(v) / len(v), v[len(v) // 2], len(v))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", default=os.path.join(ROOT, "build", "nthreads-i686", "rg-game.exe"))
    ap.add_argument("--fields", type=int, default=9000)
    ap.add_argument("--from", dest="from_")
    ap.add_argument("--run", type=int, default=300)
    ap.add_argument("--modes", default="hle,native")
    ap.add_argument("--input", default=GOLDEN, help="input script (default: newgame_battle golden)")
    ap.add_argument("--spec", action="append", default=[],
                    help="LABEL=EXE:MODE, repeatable: runs across executables (e.g. a native-only exe "
                         "and its rg-game-oracle twin); replaces --modes")
    ap.add_argument("--shots", default="")
    ap.add_argument("--timing", action="store_true")
    ap.add_argument("--kcensus", action="store_true", help="also record RG_KCENSUS per run")
    ap.add_argument("--windows", default="", help="field windows for the cost report, e.g. 1500-1800,8000-8300")
    ap.add_argument("--out", default=os.path.join(ROOT, "out", "nthreads", "cmp"))
    a = ap.parse_args()
    if not a.shots and not a.from_:
        a.shots = "%d" % a.fields
    os.makedirs(a.out, exist_ok=True)
    if a.spec:
        rs = []
        for sp in a.spec:
            label, rest = sp.split("=", 1)
            exe, mode = rest.rsplit(":", 1)
            rs.append(run_one(a, mode, a.out, exe=exe, label=label))
    else:
        rs = [run_one(a, m, a.out) for m in a.modes.split(",")]
    for r in rs:
        print("%-7s rc=%d run_hash=%s wall=%.0fs shots=%s\n        %s" % (
            r["mode"], r["rc"], r["run_hash"], r["wall"], " ".join("%d:%s" % kv for kv in sorted(r["shots"].items())),
            r["threads"]))
        if r.get("cost") or a.windows:
            print("        cpu=%.1fs  " % r["cpu"] + "  ".join(
                "%s: mean %.3f ms median %.3f ms (n=%d)" % (w, m, md, n) for w, (m, md, n) in r["cost"].items()))
    ok = len({r["run_hash"] for r in rs}) == 1 and "-" not in {r["run_hash"] for r in rs}
    ok = ok and all(r["shots"] == rs[0]["shots"] for r in rs)
    if a.timing and len(rs) >= 2:
        for r in rs[1:]:  # the first run against each other run
            ms = [os.path.join(x["dir"], "port.milestones.tsv") for x in (rs[0], r)]
            if all(os.path.exists(m) for m in ms):
                p = subprocess.run([PY, os.path.join(ROOT, "tools", "trace", "timing.py"), "align", "--nowrap"] + ms,
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
                print("align %s vs %s:" % (rs[0]["mode"], r["mode"]))
                print(p.stdout[-1500:])
                ok = ok and p.returncode == 0
    print("RESULT:", "IDENTICAL" if ok else "DIFFERENT")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
