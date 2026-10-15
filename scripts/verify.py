#!/usr/bin/env python3
"""Rebuild every image from source and compare it with retail.

    python scripts/verify.py              compile + link + compare
    python scripts/verify.py --link-only  relink existing objects

MAIN: hostbuild.py (mwcc on the build host, then the generated data C),
link.py.  Overlays: sandbox_build.py in 120-unit chunks, then
<x>_olink.py.  Prints one line per image and ALL BYTE-IDENTICAL.
"""
import re
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SCRIPTS = ROOT / "scripts"
OVS = {"title": ("ti", "t"), "insmenu": ("im", "i"), "normal": ("nm", "n"),
       "factory": ("fc", "f"), "insect": ("ix", "x")}
CHUNK = 120
PY = sys.executable


def units(p):
    return [l.split("#")[0].strip() for l in p.read_text().splitlines()
            if l.split("#")[0].strip()]


def build_main() -> bool:
    # data2c is admitted: hostbuild's __main__ routes through data2c_runner, which
    # uses its own session-isolated remote dir and writes build/obj + data objects.
    r = subprocess.run([PY, "scripts/hostbuild.py"], cwd=ROOT,
                       capture_output=True, text=True)
    tail = [l for l in r.stdout.splitlines() if l.startswith(("built ", "FAILED"))]
    print("MAIN compile:", " / ".join(tail) or (r.stdout[-800:] + r.stderr[-800:]))
    return r.returncode == 0


def build_overlays() -> bool:
    jobs = []
    for ov, (t, _) in OVS.items():
        dst = ROOT / "build" / f"obj-{t}"
        shutil.rmtree(dst, ignore_errors=True)
        dst.mkdir(parents=True)
        syms = units(ROOT / "config" / "ocunits" / f"{ov}.txt")
        for k in range(0, len(syms), CHUNK):
            jobs.append((t, f"rel-{t}{k // CHUNK:02d}", syms[k:k + CHUNK]))

    def run(j):
        t, tag, syms = j
        r = subprocess.run([PY, "scripts/sandbox_build.py", "--tag", tag] + syms,
                           cwd=ROOT, capture_output=True, text=True)
        src, dst = ROOT / "build" / f"obj-{tag}", ROOT / "build" / f"obj-{t}"
        miss = [s for s in syms if not (src / f"{s}.o").exists()]
        for s in syms:
            if (src / f"{s}.o").exists():
                shutil.move(str(src / f"{s}.o"), str(dst / f"{s}.o"))
        shutil.rmtree(src, ignore_errors=True)
        return tag, miss, r.stdout[-1500:]

    bad = 0
    with ThreadPoolExecutor(10) as pool:
        for tag, miss, out in pool.map(run, jobs):
            if miss:
                bad += len(miss)
                print(f"!! {tag}: no object for {' '.join(miss)}\n{out}")
    total = sum(len(j[2]) for j in jobs)
    print(f"overlay compile: {total - bad}/{total}")
    return bad == 0


def link_main() -> str:
    r = subprocess.run([PY, "scripts/link.py"], cwd=ROOT, capture_output=True, text=True)
    m = re.search(r"^SCUS_974\.90\s*:\s*(.+)$", r.stdout, re.M)
    if not m:
        print(r.stdout[-2000:] + r.stderr[-2000:])
    return m.group(1).strip() if m else "LINK FAILED"


def link_overlay(ov) -> str:
    x = OVS[ov][1]
    r = subprocess.run([PY, str(SCRIPTS / f"{x}_olink.py"), ov], cwd=ROOT,
                       capture_output=True, text=True)
    m = re.search(r"^%s\.BIN\s*:\s*(.+)$" % ov.upper(), r.stdout, re.M)
    if not m:
        print(r.stdout[-2000:] + r.stderr[-2000:])
    return m.group(1).strip() if m else "LINK FAILED"


def main() -> int:
    if not (ROOT / "asm" / "main.s").exists():
        print("asm/ has not been extracted yet -- running scripts/extract.py")
        if subprocess.run([PY, "scripts/extract.py"], cwd=ROOT).returncode:
            return 1
    if "--link-only" not in sys.argv:
        with ThreadPoolExecutor(2) as pool:
            fm, fo = pool.submit(build_main), pool.submit(build_overlays)
            if not (fm.result() and fo.result()):
                print("compile failed -- not linking")
                return 1
    with ThreadPoolExecutor(6) as pool:
        fut = {"SCUS_974.90": pool.submit(link_main)}
        for ov in OVS:
            fut[f"{ov.upper()}.BIN"] = pool.submit(link_overlay, ov)
        res = {k: f.result() for k, f in fut.items()}
    ok = True
    for k, v in res.items():
        print(f"{k:<13}: {v}")
        ok &= v.startswith("BYTE-IDENTICAL")
    print("ALL BYTE-IDENTICAL" if ok else "!! NOT ALL IDENTICAL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
