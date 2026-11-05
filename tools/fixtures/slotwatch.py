#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""slotwatch.py: run a test command with a watchdog on its ACTIVE time, slot waits excluded.

    slotwatch.py --active-timeout S [--wait-dir D] -- <command ...>

rg-game's headless runs share rg_slots (src/game/rg_slots.c: 2 runs machine-wide).  A ctest
TIMEOUT counts the time a test's runs sit waiting for a slot, so under contention from other
lanes a fixture test timed out without being slow (2026-11-01: fixtures.shadowbands 274 s of a
300 s limit, fixtures.optgate_quick killed at 600 s while waiting).  This wrapper:

  * sets RG_SLOT_WAIT_DIR for the command (inherited by every rg-game it starts): each headless
    run writes slotwait-<pid>.txt there ("wait <ms>" when it has to wait, then "got <ms>" once it
    holds a slot);
  * every poll (1 s) the test is STALLED when at least one of its live runs is waiting and none
    of its live runs holds a slot (so with -j 2, one job waiting while its sibling runs is active
    time); active = wall - stalled time;
  * kills the command's process tree (its own child, by PID) once active > S and exits 1
    (--killed-rc 0 for a WILL_FAIL control: a kill must fail it, not pass it);
  * otherwise exits with the command's code (77 = ctest skip passes through) and prints
    "slotwatch: wall W s, stalled on slots X s (N runs waited), active A s of S".

The ctest TIMEOUT on a wrapped test is only a wall-clock backstop (tests/fixtures/CMakeLists.txt
rg_slot_test: max(4 x S, 3600)).  tools/fixtures/slot_census.py lists the ctests that start
rg-game and fails on any that are not wrapped.  docs/TEST-FIXTURES.md "Slot waits".
"""
from __future__ import annotations

import argparse
import os
import shutil
import signal
import subprocess
import sys
import time
from pathlib import Path


def pid_alive(pid: int) -> bool:
    if pid <= 0:
        return False
    if os.name == "nt":
        import ctypes
        k = ctypes.windll.kernel32
        h = k.OpenProcess(0x1000, False, pid)   # PROCESS_QUERY_LIMITED_INFORMATION
        if not h:
            return False
        code = ctypes.c_ulong()
        k.GetExitCodeProcess(h, ctypes.byref(code))
        k.CloseHandle(h)
        return code.value == 259   # STILL_ACTIVE
    try:
        os.kill(pid, 0)
        return True
    except OSError:
        return False


def slot_state(d: Path):
    """(live runs waiting, live runs holding a slot, runs that ever waited) from slotwait-*.txt."""
    waiting = holding = waited = 0
    for f in d.glob("slotwait-*.txt"):
        try:
            words = f.read_text(encoding="ascii", errors="replace").split()
            pid = int(f.stem.split("-", 1)[1])
        except (OSError, ValueError):
            continue
        last = words[-2] if len(words) >= 2 else None
        waited += "wait" in words[0::2]
        if last and pid_alive(pid):
            waiting += last == "wait"
            holding += last == "got"
    return waiting, holding, waited


def kill_tree(p: subprocess.Popen):
    if os.name == "nt":
        subprocess.run(["taskkill", "/PID", str(p.pid), "/T", "/F"],
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    else:
        try:
            os.killpg(p.pid, signal.SIGKILL)
        except OSError:
            p.kill()
    try:
        p.wait(timeout=30)
    except subprocess.TimeoutExpired:
        p.kill()


SELFTEST_CHILD = r"""
import os, sys, time
d = os.environ["RG_SLOT_WAIT_DIR"]
mode = sys.argv[1]
def note(w):
    with open(os.path.join(d, "slotwait-%d.txt" % os.getpid()), "a") as f:
        f.write("%s %d\n" % (w, time.time() * 1000))
if mode == "wait":      # 3 s in a slot wait, then 1 s of run: active ~1 s
    note("wait"); time.sleep(3); note("got"); time.sleep(1)
elif mode == "jwait":   # -j 2: this run holds a slot while a sibling waits 4 s: all active
    import subprocess
    note("got")
    sib = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(8)"])
    with open(os.path.join(d, "slotwait-%d.txt" % sib.pid), "a") as f:
        f.write("wait %d\n" % (time.time() * 1000))
    time.sleep(4)
    sib.kill()
elif mode == "slow":    # 6 s of run, no wait
    time.sleep(6)
sys.exit(77 if mode == "skip" else 0)
"""


def selftest() -> int:
    """The wrapper on a synthetic child (no game): wait excluded, slow run killed, 77 kept."""
    import tempfile
    tmp = Path(tempfile.mkdtemp(prefix="slotwatch_selftest"))
    child = tmp / "child.py"
    child.write_text(SELFTEST_CHILD, encoding="utf-8")
    bad = 0
    cases = (("wait", 2.5, 0), ("jwait", 2.0, 1), ("slow", 2.0, 1), ("skip", 5.0, 77), ("slow", 2.0, 0))
    for mode, limit, want in cases:
        t0 = time.time()
        rc = main(["--active-timeout", str(limit), "--wait-dir", str(tmp / mode),
                   "--killed-rc", str(want if mode == "slow" else 1), "--",
                   sys.executable, str(child), mode])
        ok = rc == want and (mode not in ("slow", "jwait") or time.time() - t0 < 3.9)
        print(f"selftest {mode:5} limit {limit} s: rc {rc} (want {want}) {'ok' if ok else 'FAIL'}", flush=True)
        bad += not ok
    shutil.rmtree(tmp, ignore_errors=True)
    print(f"slotwatch selftest: {len(cases) - bad}/{len(cases)} ok")
    return 1 if bad else 0


def main(argv=None) -> int:
    if argv is None and sys.argv[1:] == ["--selftest"]:
        return selftest()
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--active-timeout", type=float, required=True, help="seconds of run time, slot waits excluded")
    ap.add_argument("--wait-dir", help="slot-wait record dir (default: ./slotwait.<pid>, removed after)")
    ap.add_argument("--poll", type=float, default=1.0)
    ap.add_argument("--killed-rc", type=int, default=1,
                    help="exit code after a watchdog kill (0 for a WILL_FAIL control, so the kill fails it)")
    ap.add_argument("cmd", nargs=argparse.REMAINDER)
    a = ap.parse_args(argv)
    cmd = a.cmd[1:] if a.cmd and a.cmd[0] == "--" else a.cmd
    if not cmd:
        ap.error("no command")
    d = Path(a.wait_dir or f"slotwait.{os.getpid()}").resolve()
    shutil.rmtree(d, ignore_errors=True)
    d.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, RG_SLOT_WAIT_DIR=str(d))
    t0 = time.time()
    kw = {"start_new_session": True} if os.name != "nt" else {}
    p = subprocess.Popen(cmd, env=env, **kw)
    killed = False
    stall = active = 0.0
    prev = t0
    while True:
        try:
            rc = p.wait(timeout=a.poll)
            break
        except subprocess.TimeoutExpired:
            pass
        now = time.time()
        waiting, holding, _ = slot_state(d)
        if waiting and not holding:
            stall += now - prev
        prev = now
        active = now - t0 - stall
        if active > a.active_timeout:
            print(f"slotwatch: active time {active:.0f} s > {a.active_timeout:.0f} s "
                  f"(wall {now - t0:.0f} s, stalled on slots {stall:.0f} s): killing the test", flush=True)
            kill_tree(p)
            rc, killed = a.killed_rc, True
            break
    now = time.time()
    _, _, waited = slot_state(d)
    print(f"slotwatch: wall {now - t0:.0f} s, stalled on slots {stall:.0f} s ({waited} runs waited), "
          f"active {now - t0 - stall:.0f} s of {a.active_timeout:g}" + (" (KILLED)" if killed else ""),
          flush=True)
    shutil.rmtree(d, ignore_errors=True)
    return rc


if __name__ == "__main__":
    sys.exit(main())
