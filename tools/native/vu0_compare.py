#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Run two or more rg-game builds on the golden route and compare them
(docs/NATIVE-CPU.md "Verification"): e.g. RG_VU0_MODE=model (the oracle) against
local / native.

    python tools/native/vu0_compare.py --exe NAME=PATH --exe NAME=PATH [...]
                                       [--fields 9000] [--shots a,b,c] [--timing]
                                       [--input tools/trace/goldens/newgame_save1.input.txt]
                                       [--from title|field|battle --run K]
                                       [--out out/nvu0/cmp] [--imgcmp]

One process at a time (shared PC), headless, RG_GPU=hw, fresh saves dir each.
Per build:
  run_hash   rg-game's run hash (kernel trace hash + clock + audio + pad words, every
             field): equal = every field's thread/sema/audio/pad sequence matched
  shots      --shot PNGs at the listed fields: byte hash (equal = identical frame)
  timing     (--timing) RG_TIMING record -> timing.py build; with two builds,
             timing.py align --nowrap on the milestone tables (same milestones at the
             same VBlank?)
  imgcmp     (--imgcmp) render_imgcmp.py on the shots of the first build against each
             other (PSNR / bad% / SSIM) for builds whose frames are not byte-identical
--from M runs from the milestone state of EACH build's own fixture set (run_from.py
regenerates a set per exe on first use; that replays the route from power-on once).
Exit 0 when run hashes and shot hashes are identical across builds.
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
GOLDEN = os.path.join(ROOT, "tools", "trace", "goldens", "newgame_save1.input.txt")


def sha(path):
    try:
        return hashlib.sha256(open(path, "rb").read()).hexdigest()[:16]
    except OSError:
        return "-"


def run_one(a, name, exe, out):
    d = os.path.join(out, name)
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(os.path.join(d, "saves"))
    env = dict(os.environ)
    env.setdefault("RG_DATA", os.path.join(ROOT, "data"))
    env.setdefault("RG_GPU", "hw")
    if a.timing:
        env["RG_TIMING"] = os.path.join(d, "port.jsonl")
    if a.windows:
        env["RG_FIELD_TIMES"] = os.path.join(d, "field_times.tsv")
    shots = [int(x) for x in a.shots.split(",") if x] if a.shots else []
    extra = []
    for f in shots:
        extra += ["--shot", "%d:%s" % (f, os.path.join(d, "f%05d_display.png" % f))]
    if a.from_:
        cmd = [PY, os.path.join(ROOT, "tools", "fixtures", "run_from.py"), a.from_, "--run", str(a.run),
               "--exe", exe, "--"] + extra
    else:
        cmd = [exe, "--headless", "--fields", str(a.fields), "--saves", os.path.join(d, "saves"),
               "--input", a.input] + extra
    t = time.time()
    p = subprocess.run(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                       errors="replace")
    open(os.path.join(d, "log.txt"), "w", encoding="utf-8").write(p.stdout)
    m = re.findall(r"run_hash=([0-9a-f]+)", p.stdout)
    res = {"name": name, "rc": p.returncode, "run_hash": m[-1] if m else "-", "wall": time.time() - t,
           "shots": {f: sha(os.path.join(d, "f%05d_display.png" % f)) for f in shots}, "dir": d,
           "cost": windows(os.path.join(d, "field_times.tsv"), a.windows)}
    if a.timing and os.path.exists(env["RG_TIMING"]):
        subprocess.run([PY, os.path.join(ROOT, "tools", "trace", "timing.py"), "build", env["RG_TIMING"]],
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return res


def windows(path, spec):
    """mean / median step_ms per field window 'a-b' (RG_FIELD_TIMES, fields a < f <= b)"""
    out = {}
    if not spec or not os.path.exists(path):
        return out
    rows = []
    for ln in open(path, encoding="utf-8"):
        if ln.startswith("#"):
            continue
        c = ln.split("\t")
        if len(c) >= 3:
            try:
                rows.append((int(c[0]), float(c[2])))
            except ValueError:
                pass
    for w in spec.split(","):
        lo, hi = (int(x) for x in w.split("-"))
        v = sorted(ms for f, ms in rows if lo < f <= hi)
        if v:
            out[w] = (sum(v) / len(v), v[len(v) // 2], len(v))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", action="append", required=True, help="NAME=PATH (repeat)")
    ap.add_argument("--fields", type=int, default=9000)
    ap.add_argument("--input", default=GOLDEN)
    ap.add_argument("--from", dest="from_")
    ap.add_argument("--run", type=int, default=300)
    ap.add_argument("--shots", default="")
    ap.add_argument("--timing", action="store_true")
    ap.add_argument("--imgcmp", action="store_true")
    ap.add_argument("--windows", default="", help="field windows for step-time cost, e.g. 7000-9000")
    ap.add_argument("--out", default=os.path.join(ROOT, "out", "nvu0", "cmp"))
    a = ap.parse_args()
    if not a.shots and not a.from_:
        a.shots = "%d" % a.fields
    os.makedirs(a.out, exist_ok=True)
    exes = [e.split("=", 1) for e in a.exe]
    rs = [run_one(a, n, os.path.abspath(p), a.out) for n, p in exes]
    for r in rs:
        print("%-8s rc=%d run_hash=%s wall=%.0fs shots=%s" % (
            r["name"], r["rc"], r["run_hash"], r["wall"],
            " ".join("%d:%s" % kv for kv in sorted(r["shots"].items()))))
        if r["cost"]:
            print("         " + "  ".join("%s: mean %.3f ms median %.3f ms (n=%d)" % (w, m, md, n)
                                      for w, (m, md, n) in r["cost"].items()))
    ok = len({r["run_hash"] for r in rs}) == 1 and "-" not in {r["run_hash"] for r in rs}
    shots_ok = all(r["shots"] == rs[0]["shots"] for r in rs)
    if a.timing and len(rs) >= 2:
        for r in rs[1:]:
            ms = [os.path.join(x["dir"], "port.milestones.tsv") for x in (rs[0], r)]
            if all(os.path.exists(m) for m in ms):
                p = subprocess.run([PY, os.path.join(ROOT, "tools", "trace", "timing.py"), "align", "--nowrap"] + ms,
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
                print("== timing align %s vs %s\n%s" % (rs[0]["name"], r["name"], p.stdout[-2500:]))
                ok = ok and p.returncode == 0
    if a.imgcmp and not shots_ok:
        for r in rs[1:]:
            if r["shots"] != rs[0]["shots"]:
                p = subprocess.run([PY, os.path.join(ROOT, "tools", "native", "render_imgcmp.py"), rs[0]["dir"],
                                    r["dir"], "--fields", a.shots],
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
                print("== imgcmp %s vs %s\n%s" % (rs[0]["name"], r["name"], p.stdout[-2500:]))
    print("RESULT: run_hash %s, shots %s" % ("IDENTICAL" if ok else "DIFFERENT",
                                             "IDENTICAL" if shots_ok else "DIFFERENT"))
    return 0 if ok and shots_ok else 1


if __name__ == "__main__":
    sys.exit(main())
