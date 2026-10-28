#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Play-test exe in one command: ingest check, configure + build in an own build dir, snapshot,
the play-test gates, copy to out/playtest and point the .bat launchers at it, windowed smoke.

The recipe of the 1024a / 1025a play-test builds (docs/bringup/BRINGUP-HISTORY.md "play-test
build 1025a"; docs/BRINGUP.md resume item 4 and "Tools (bring-up)"): Release, RG_GAME_OPT=-O2, RG_NATIVE_ONLY=ON,
RG_NATIVE_OVL=ON, RG_VU0_MODE=native, no UBSan / sbguard; the gates run on the snapshot exe one
rg-game at a time (the exes' own slot mutex limits the machine to two).

    python tools/playtest/build_playtest.py --tag 1025b --note "1025a + ..."
    python tools/playtest/build_playtest.py --tag 1025b --steps gates --gates insect,gameover
    python tools/playtest/build_playtest.py --tag 1025b --steps install,smoke --note "..."

Steps (default all, in this order): check configure build snapshot gates install smoke.
Gates (default all): regen verify boot map link addr insect gameover factory place shop render
(shop = tools/fixtures/shopcrash.py, the 1025b shop-close crash, D3D11 + Vulkan).
`install` also copies the link map beside the exe (rg-game-<TAG>.map): the crash handler names
functions in rg-game-crash.txt from it.
`install` refuses when a gate of this run (or of OUT/summary.tsv) failed, unless --force-install.
Build dir default build/pt<TAG>-i686, gate dir default out/regress<TAG>; summary in
OUT/summary.tsv (one row per gate: name, PASS/FAIL, detail) and on stdout.
Never touches other build dirs or processes; out/fixtures/cards/save2 is restored from a backup
when regen.py changes it (as in every earlier gate script).
Timing (1025b, machine shared with other lanes): fresh build ~21 min at -j4; the gates without
render ~75 min (bootcheck ~40); render ~1 h+. Whole run > 2 h: from an agent shell with a 2 h
background limit, run `--steps check,configure,build,snapshot`, then `--steps gates --gates
<all but render>`, then `--steps gates --gates render`, then `--steps install,smoke`.
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PY = sys.executable
# tool locations: $RG_TOOLS, default <repo>/../tools (the workspace layout in README.md)
TOOLS = Path(os.environ.get("RG_TOOLS", ROOT.parent / "tools"))
CMAKE = str(TOOLS / "cmake-3.31.7-windows-x86_64" / "bin" / "cmake.exe")
NINJA = str(TOOLS / "ninja" / "ninja.exe")
LLVM = str(TOOLS / "llvm")
VCVARS = [
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
    r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat",
]
# the play-test configuration (= build/play-i686's cache for 1025a)
CONFIG = [
    "-DCMAKE_BUILD_TYPE=Release",
    f"-DCMAKE_TOOLCHAIN_FILE={(ROOT / 'cmake' / 'toolchain-i686-windows-clang.cmake').as_posix()}",
    f"-DCMAKE_MAKE_PROGRAM={NINJA}",
    f"-DLLVM_ROOT={Path(LLVM).as_posix()}",
    f"-DRG_GPU_REPLAY_DIR={(ROOT / 'out' / 'p3' / 'gsrec').as_posix()}",
    f"-DRG_PYTHON={Path(PY).as_posix()}",
    f"-DRG_SDL3_ARCHIVE={(TOOLS / 'dl' / 'SDL3-3.4.18.tar.gz').as_posix()}",
    # optional overrides: fxc is otherwise found on the vcvars PATH (Windows SDK); FFmpeg is
    # only a verification tool for one test
    *([f"-DRG_FXC={os.environ['RG_FXC']}"] if os.environ.get("RG_FXC") else []),
    *([f"-DRG_FFMPEG={os.environ['RG_FFMPEG']}"] if os.environ.get("RG_FFMPEG") else []),
    "-DRG_GAME_OPT=-O2",
    "-DRG_NATIVE_ONLY=ON",
    "-DRG_NATIVE_OVL=ON",
    "-DRG_VU0_MODE=native",
    "-DRG_UBSAN=OFF",
    "-DRG_SBGUARD=OFF",
]
BATS = ["play.bat", "play-from-save.bat", "play-test-save.bat"]
ALL_STEPS = ["check", "configure", "build", "snapshot", "gates", "install", "smoke"]
ALL_GATES = ["regen", "verify", "boot", "map", "link", "addr", "insect", "gameover", "factory",
             "place", "shop", "render"]
PLACE_INPUT = "out/soak/o2/findings/002/poweron.input.txt"  # the 1024a FACTORY -> Place crash


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


def vc_env():
    vc = next((p for p in VCVARS if Path(p).exists()), None)
    if not vc:
        raise SystemExit("vcvarsall.bat not found")
    env = dict(os.environ)
    env["PATH"] = env.get("PATH", "").replace('"', "")
    out = subprocess.run(f'cmd.exe /c ""{vc}" x86 >nul 2>&1 && set"', shell=True, env=env,
                         capture_output=True, text=True, errors="replace").stdout
    for line in out.splitlines():
        if "=" in line and not line.startswith("="):
            k, v = line.split("=", 1)
            env[k] = v
    env["PATH"] = f"{LLVM}\\bin;{Path(NINJA).parent};" + env["PATH"]
    return env


def bash_exe():
    for c in [os.environ.get("RG_BASH"), shutil.which("bash"),
              r"C:\Program Files\Git\usr\bin\bash.exe", r"C:\Program Files\Git\bin\bash.exe"]:
        if c and "system32" not in c.lower() and Path(c).exists():
            return c
    raise SystemExit("Git bash not found (render_gate.sh needs it)")


def run(cmd, outfile, env=None, cwd=ROOT):
    """Run, tee nothing: stdout+stderr to outfile; returns (rc, text)."""
    t0 = time.time()
    with open(outfile, "w", encoding="utf-8", errors="replace") as f:
        rc = subprocess.run(cmd, cwd=cwd, env=env, stdout=f, stderr=subprocess.STDOUT).returncode
    with open(outfile, "a", encoding="utf-8") as f:
        f.write(f"\n# exit {rc} ({time.time() - t0:.0f} s)\n")
    return rc, Path(outfile).read_text(encoding="utf-8", errors="replace")


class Ctx:
    def __init__(self, a):
        self.a = a
        self.tag = a.tag
        self.build = ROOT / (a.build or f"build/pt{a.tag}-i686")
        self.out = ROOT / (a.out or f"out/regress{a.tag}")
        self.exe = self.out / "rg-game.exe"
        self.oracle = self.out / "rg-game-oracle.exe"
        self.out.mkdir(parents=True, exist_ok=True)
        self.summary = self.out / "summary.tsv"
        self.rows = {}
        if self.summary.exists():
            for line in self.summary.read_text(encoding="utf-8").splitlines():
                p = line.split("\t")
                if len(p) == 3:
                    self.rows[p[0]] = (p[1], p[2])

    def result(self, name, ok, detail):
        self.rows[name] = ("PASS" if ok else "FAIL", detail.replace("\t", " ").replace("\n", " "))
        self.summary.write_text("".join(f"{k}\t{v[0]}\t{v[1]}\n" for k, v in self.rows.items()),
                                encoding="utf-8")
        log(f"{name}: {'PASS' if ok else 'FAIL'} {detail}")
        return ok


# ---------------------------------------------------------------- steps
def step_check(c):
    rc, t = run([PY, "tools/ingest.py", "--check"], c.out / "ingest_check.txt")
    probs = re.findall(r"(\d+) problems", t)
    ok = rc == 0 and probs and all(p == "0" for p in probs)
    c.result("ingest_check", ok, " / ".join(l.strip() for l in t.splitlines() if "problems" in l))
    if not ok:
        raise SystemExit("ingest.py --check reports problems: game/ is stale; re-ingest first "
                         "(coordinate with other lanes) and say so in the history entry")


def step_configure(c):
    env = vc_env()
    rc, t = run([CMAKE, "-S", str(ROOT), "-B", str(c.build), "-G", "Ninja"] + CONFIG,
                c.out / "configure.log", env=env)
    cache = (c.build / "CMakeCache.txt").read_text(encoding="utf-8", errors="replace")
    keys = ["CMAKE_BUILD_TYPE", "RG_GAME_OPT", "RG_NATIVE_ONLY", "RG_NATIVE_OVL", "RG_VU0_MODE",
            "RG_UBSAN", "RG_SBGUARD"]
    vals = {k: (re.search(rf"^{k}:\w+=(.*)$", cache, re.M) or [None, "?"])[1] for k in keys}
    c.result("configure", rc == 0, " ".join(f"{k}={v}" for k, v in vals.items()))
    if rc:
        raise SystemExit("configure failed, see " + str(c.out / "configure.log"))


def step_build(c):
    env = vc_env()
    rc, t = run([CMAKE, "--build", str(c.build), "-j", str(c.a.jobs), "--target", "rg-game",
                 "rg-game-oracle"], c.out / "build.log", env=env)
    errs = len(re.findall(r" error: ", t))
    warns = len(re.findall(r" warning: ", t))
    steps = re.findall(r"^\[(\d+)/(\d+)\]", t, re.M)
    c.result("build", rc == 0, f"rg-game + rg-game-oracle, {steps[-1][1] if steps else 0} steps, "
             f"{errs} errors, {warns} warnings")
    if rc:
        raise SystemExit("build failed, see " + str(c.out / "build.log"))


def step_snapshot(c):
    for n in ["rg-game.exe", "rg-game.map", "rg-game-oracle.exe", "rg-game-oracle.map"]:
        src = c.build / n
        if src.exists():
            shutil.copy2(src, c.out / n)
    c.result("snapshot", c.exe.exists(), f"{c.exe} {c.exe.stat().st_size} bytes")


def gate_regen(c):
    card, bak = ROOT / "out/fixtures/cards/save2", c.out / "save2_backup"
    shutil.rmtree(bak, ignore_errors=True)
    shutil.copytree(card, bak)
    rc, t = run([PY, "tools/fixtures/regen.py", "--exe", str(c.exe), "--check", "300"],
                c.out / "regen.txt")
    same = subprocess.run(["diff", "-r", str(card), str(bak)], capture_output=True).returncode == 0 \
        if shutil.which("diff") else None
    note = "card save2 identical"
    if same is not True:
        shutil.rmtree(card)
        shutil.copytree(bak, card)
        note = "card save2 differed after regen -> restored from the backup"
    c.result("regen", rc == 0, f"regen.py --check 300 exit {rc}; {note}")


def gate_verify(c):
    rc, t = run([PY, "tools/fixtures/verify.py", "--exe", str(c.exe)], c.out / "verify.txt")
    rows = [l for l in t.splitlines() if "run_hash" in l and " vs " in l]
    good = [l for l in rows if l.count(" OK") >= 2]
    c.result("verify", rc == 0 and rows and len(good) == len(rows), f"{len(good)}/{len(rows)}")


def gate_boot(c):
    rc, t = run([PY, "tools/fixtures/bootcheck.py", "--all", "--exe", str(c.exe), "--tsv",
                 str(c.out / "boot.tsv"), "--keep-logs", str(c.out / "bootlogs")], c.out / "boot.txt")
    p = len(re.findall(r"^\s*PASS\s", t, re.M))
    f = [l.strip() for l in t.splitlines() if re.match(r"^\s*FAIL\s", l)]
    c.result("bootcheck", rc == 0 and not f and p > 0, f"{p}/{p + len(f)} PASS " + "; ".join(f))


def gate_map(c):
    rc, t = run([PY, "tools/fixtures/mapcheck.py", "--exe", str(c.exe), "--out",
                 str(c.out / "mapcheck")], c.out / "map.txt")
    d, m = len(re.findall(r"\sDRAWN\s", t)), len(re.findall(r"\sMISSING\s", t))
    c.result("mapcheck", rc == 0 and m == 0 and d > 0, f"{d}/{d + m} DRAWN")


def gate_link(c):
    rc, t = run([PY, "tools/native/link_audit.py", "check", str(c.out / "rg-game.map"), "--forbid",
                 "all", "--extra", "rg_ps2_hwbus"], c.out / "link_audit.txt")
    line = next((l for l in t.splitlines() if l.startswith("link_audit:")), "")
    c.result("link_audit", rc == 0 and "PASS" in line, line)


def gate_addr(c):
    rc, t = run([PY, "tools/native/addr_census.py", "--build", str(c.build), "--check"],
                c.out / "addr_census.txt")
    line = next((l for l in reversed(t.splitlines()) if "PASS" in l or "FAIL" in l), t[-200:])
    c.result("addr_census", rc == 0, line.strip())


def gate_insect(c):
    rc, t = run([PY, "tools/fixtures/insectrun.py", "run", "--title", "--exe", str(c.exe), "--out",
                 str(c.out / "insect")], c.out / "insect.txt")
    ex = re.findall(r"^\s*exit\s.*\((\d+), (\d+), '([^']*)'\)", t, re.M)
    title = bool(ex) and ex[-1][1] == "2"
    c.result("insectrun_title", rc == 0 and "insectrun: done" in t and title,
             f"exit row {ex[-1] if ex else None} (ovl 2 = TITLE)")


def gate_gameover(c):
    rc, t = run([PY, "tools/fixtures/gameover.py", "run", "--exe", str(c.exe), "--out",
                 str(c.out / "gameover")], c.out / "gameover.txt")
    line = next((l for l in t.splitlines() if l.startswith("gameover:")), "")
    c.result("gameover", rc == 0 and "title+continue" in line, line)


def gate_factory(c):
    rc, t = run([PY, "tools/fixtures/factory.py", "run", "--exe", str(c.exe), "--out",
                 str(c.out / "factory")], c.out / "factory.txt")
    line = next((l for l in t.splitlines() if l.startswith("factory:")), "")
    c.result("factory", rc == 0 and "exit to field ok" in line, line)


def gate_place(c):
    d = c.out / "place"
    shutil.rmtree(d, ignore_errors=True)
    d.mkdir(parents=True)
    shutil.copytree(ROOT / "out/fixtures/cards/ch06_mines", d / "saves")
    env = dict(os.environ, RG_SS="1", RG_DATA=(ROOT / "data").as_posix(), RG_GPU="hw", RG_STATUS_EVERY="100")
    rc, t = run([str(c.exe), "--headless", "--fields", "5700", "--saves", str(d / "saves"),
                 "--input", str(ROOT / PLACE_INPUT), "--shot", f"4950:{d / 's4950.png'}"],
                d / "log.txt", env=env)
    done = re.search(r"fields=5700\b.*rc=0", t)
    exc = re.search(r"exception|EXCEPTION_|access violation", t)
    c.result("factory_place", rc == 0 and bool(done) and not exc,
             f"rc {rc}, {'reached 5700' if done else 'did not reach 5700'}, "
             f"{'exception: ' + exc.group(0) if exc else 'no exception'}")


def gate_shop(c):
    """the 1025b shop-close crash: buy Grand Edge in Salgin's item shop, close (both APIs)"""
    rc, t = run([PY, "tools/fixtures/shopcrash.py", "--exe", str(c.exe), "--out", str(c.out / "shop")],
                c.out / "shop.txt")
    rows = [l.strip() for l in t.splitlines() if l.startswith("shopcrash ")]
    c.result("shop_close", rc == 0 and len(rows) == 2 and all(": PASS" in r for r in rows),
             "; ".join(r.split(" (")[0] for r in rows) or t[-200:])


def gate_render(c):
    tag = f"pt{c.tag}"
    # Git's usr/bin first: started from PowerShell, bash.exe alone has no grep / awk / tail
    b = Path(bash_exe())
    usr = b.parent if b.parent.name.lower() == "bin" and b.parent.parent.name.lower() == "usr" \
        else b.parent.parent / "usr" / "bin"
    env = dict(os.environ)
    env["PATH"] = f"{usr};{b.parent};" + env.get("PATH", "")
    rc, t = run([str(b), str(ROOT / "tools/native/render_gate.sh"),
                 c.oracle.as_posix(), c.exe.as_posix(), tag], c.out / "render_gate.txt", env=env)
    g = (ROOT / f"out/nrender/runs/gate_{tag}.txt")
    t = g.read_text(encoding="utf-8", errors="replace") if g.exists() else t
    route = re.search(r"\d+ fields, PSNR min ([\d.]+).*failing (\d+)", t)
    boots = re.findall(r"^\s*(\S+) x1: .*: (PASS|FAIL)", t, re.M)
    mp = re.search(r"mapcheck: (\d+) DRAWN, (\d+) MISSING", t)
    hashes = re.findall(r"(emu|nat): rg-game: run_hash=(\w+)", t)
    ok = (rc == 0 and route and route.group(2) == "0" and boots and all(b[1] == "PASS" for b in boots)
          and mp and mp.group(2) == "0" and len({h for _, h in hashes}) == 1)
    c.result("render_gate", bool(ok),
             f"route PSNR min {route.group(1) if route else '?'} failing {route.group(2) if route else '?'}; "
             f"boot {sum(b[1] == 'PASS' for b in boots)}/{len(boots)} PASS; "
             f"map {mp.group(1) if mp else '?'} DRAWN; run hashes {sorted({h for _, h in hashes})}")


GATES = {"regen": gate_regen, "verify": gate_verify, "boot": gate_boot, "map": gate_map,
         "link": gate_link, "addr": gate_addr, "insect": gate_insect, "gameover": gate_gameover,
         "factory": gate_factory, "place": gate_place, "shop": gate_shop, "render": gate_render}


def step_gates(c):
    for g in c.a.gates.split(","):
        log(f"gate {g} ...")
        GATES[g](c)


def step_install(c):
    bad = [k for k, v in c.rows.items() if v[0] != "PASS" and k != "smoke"]
    if bad and not c.a.force_install:
        raise SystemExit(f"not installing: failed rows {bad} (use --force-install)")
    pt = ROOT / "out/playtest"
    dst = pt / f"rg-game-{c.tag}.exe"
    shutil.copy2(c.exe, dst)
    if (c.out / "rg-game.map").exists():   # the crash log's function names (rg_game_crash)
        shutil.copy2(c.out / "rg-game.map", dst.with_suffix(".map"))
    for b in BATS:
        p = pt / b
        raw = p.read_bytes()
        new = re.sub(rb"rg-game-[0-9A-Za-z_]+\.exe", f"rg-game-{c.tag}.exe".encode(), raw)
        if b == "play.bat" and c.a.note:
            line = f"rem Play-test build {time.strftime('%Y-%m-%d')} ({c.tag}: {c.a.note})".encode()
            new = re.sub(rb"^rem Play-test build [^\r\n]*", lambda m: line, new, count=1, flags=re.M)
        if new != raw:
            p.write_bytes(new)
    c.result("install", True, f"{dst} + {', '.join(BATS)}")


def step_smoke(c):
    pt = ROOT / "out/playtest"
    d = c.out / "smoke"
    d.mkdir(parents=True, exist_ok=True)
    rel = os.path.relpath(d, pt).replace("\\", "/")
    env = dict(os.environ, RG_GPU="hw", RG_SLOTS_PRIORITY="normal")
    exe = pt / f"rg-game-{c.tag}.exe"
    t0 = time.time()
    with open(d / "stdout.txt", "w") as so, open(d / "stderr.txt", "w") as se:
        rc = subprocess.run([str(exe), "--fields", "1600", "--shot", f"600:{rel}/f600.png",
                             "--shot", f"1500:{rel}/title1500.png"], cwd=pt, env=env,
                            stdout=so, stderr=se).returncode
    out = (d / "stdout.txt").read_text(errors="replace")
    err = (d / "stderr.txt").read_text(errors="replace")
    h = re.search(r"run_hash=(\w+)", out)
    dev = re.search(r"GS drawn by the GPU renderer: ([^\n]*)", err)
    ok = rc == 0 and "rc=0" in out and (d / "title1500.png").exists()
    c.result("smoke", ok, f"windowed from out/playtest, 1600 fields, rc {rc}, run hash "
             f"{h.group(1) if h else '?'}, {dev.group(1) if dev else 'device ?'} ({time.time() - t0:.0f} s)")


STEPS = {"check": step_check, "configure": step_configure, "build": step_build,
         "snapshot": step_snapshot, "gates": step_gates, "install": step_install, "smoke": step_smoke}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tag", required=True, help="e.g. 1025b -> out/playtest/rg-game-1025b.exe")
    ap.add_argument("--build", help="build dir (default build/pt<TAG>-i686)")
    ap.add_argument("--out", help="gate dir (default out/regress<TAG>)")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--steps", default=",".join(ALL_STEPS))
    ap.add_argument("--gates", default=",".join(ALL_GATES))
    ap.add_argument("--note", help="contents summary for play.bat's comment line")
    ap.add_argument("--force-install", action="store_true")
    a = ap.parse_args()
    c = Ctx(a)
    for s in a.steps.split(","):
        log(f"step {s}")
        STEPS[s](c)
    print("\n".join(f"{k:16s} {v[0]}  {v[1]}" for k, v in c.rows.items()))
    return 0 if all(v[0] == "PASS" for v in c.rows.values()) else 1


if __name__ == "__main__":
    sys.exit(main())
