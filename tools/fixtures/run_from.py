#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Start rg-game at a milestone instead of power-on (docs/TEST-FIXTURES.md).

    python tools/fixtures/run_from.py <milestone> [--run K | --fields N] [--input SCRIPT]
                                      [--exe EXE] [--windowed] [--no-regen] [--print]
                                      [-- extra rg-game args, e.g. --shot 23100:out/x.png]
    python tools/fixtures/run_from.py --boot-save save2 [--run K | --fields N] [--exe EXE] [-- ..]
    python tools/fixtures/run_from.py --list

Options may come before or after the milestone; everything after "--" goes
to rg-game.

Milestones (fields on the route, fxlib.MILESTONES): title 1500, field 8000,
battle 23000, battle_won 26780, town 28840, save_point 30220, trans_menu 30780,
saved 31700.
Loads out/fixtures/<exe-id>/<milestone>.rgstate into the same build
(regenerating the set first when it is missing or was written by another exe:
~20 min for the whole route; --no-regen fails instead) and runs headless from
there: --run K fields (default 300), or up to absolute field N.  Input: the
route script by default (keyed by the field number in a plain run, so it
continues where the state left it); --input gives another script (only its
lines after the milestone's field matter; never put a line AT the milestone
field: that VBlank's pad read happened before the save).  Each run gets a
fresh scratch saves dir; milestones in fxlib.CARD_MILESTONES (saved) get a
copy of the memory card the generating run left (<set>/cards/).

--boot-save NAME: no save state at all: power-on with the game-save fixture
out/fixtures/cards/NAME/ as the memory card and tools/trace/goldens/
boot_NAME.input.txt (title -> CONTINUE -> slot 1 -> FILE 01 -> load), so the
game itself loads the save.  Survives rebuilds (any exe; ~1 min to control).
The boot script's "# boot-end: N" line is the field where control starts;
--run K counts from there.  Regenerate the card with regen.py (the route
writes it) when the save format consumer changes, not per build.

Environment as for any rg-game run (RG_TIMING, RG_TRACE_*, RG_GS_DUMP_*, ...
work from the loaded field on); RG_GPU must match the set's (hw by default).
Exit code: rg-game's (3 = the state was refused).
"""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fxlib  # noqa: E402


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("milestone", nargs="?")
    ap.add_argument("--list", action="store_true", help="list milestones and the set's state")
    ap.add_argument("--run", type=int, default=300, metavar="K", help="fields to run after the milestone")
    ap.add_argument("--fields", type=int, default=0, metavar="N", help="run up to absolute field N")
    ap.add_argument("--input", help="input script (default: the golden one the states were saved with)")
    ap.add_argument("--exe", help="rg-game.exe (default build/fixtures-i686, or $RG_FIXTURES_EXE)")
    ap.add_argument("--windowed", action="store_true", help="open the window (default headless)")
    ap.add_argument("--no-regen", action="store_true", help="fail instead of regenerating a stale set")
    ap.add_argument("--print", action="store_true", help="print the command and exit")
    ap.add_argument("--saves", help="saves dir to use (default: a fresh scratch dir)")
    ap.add_argument("--boot-save", metavar="NAME", help="power-on with the game-save fixture NAME (no state)")
    # Everything after the first "--" goes to rg-game untouched; options may
    # come before or after the milestone (`battle --fields 24800 -- --shot ..`).
    argv = list(sys.argv[1:] if argv is None else argv)
    extra = []
    if "--" in argv:
        k = argv.index("--")
        argv, extra = argv[:k], argv[k + 1:]
    a = ap.parse_args(argv)
    a.extra = extra

    exe_src = fxlib.exe_path(a.exe)
    if not exe_src.exists():
        fxlib.say(f"run_from: {exe_src} not found; build with tools/fixtures/build.ps1")
        return 2
    if a.boot_save:
        return boot_save(a, exe_src)
    d = fxlib.fixture_dir(exe_src)
    if a.list or not a.milestone:
        m = fxlib.load_manifest(d) or {}
        fxlib.say(f"exe {exe_src}\nset {d} ({'present' if m else 'not generated yet'})")
        for n, f, desc in fxlib.MILESTONES:
            e = m.get("milestones", {}).get(n)
            st = f"{e['bytes'] / 1e6:.1f} MB, vbl {e['vbl']}, saves {e['wall_s']:.0f} s" if e else "-"
            fxlib.say(f"  {n:10s} field {f:6d}  {desc}  [{st}]")
        return 0
    if a.milestone not in fxlib.MILESTONE_FIELDS:
        fxlib.say(f"run_from: unknown milestone {a.milestone} (known: {', '.join(fxlib.MILESTONE_FIELDS)})")
        return 2
    ok, why = fxlib.fresh(d, exe_src, [a.milestone])
    if not ok and a.print:
        fxlib.say(f"run_from: (fixture set {d.name}: {why}; a real run regenerates it first)")
        man = {"exe": "bin/rg-game.exe", "milestones": {a.milestone: {
            "file": f"{a.milestone}.rgstate", "field": fxlib.MILESTONE_FIELDS[a.milestone], "wall_s": 0}}}
    elif not ok:
        if a.no_regen:
            fxlib.say(f"run_from: no usable fixture for {a.milestone} ({why}); run tools/fixtures/regen.py")
            return 2
        fxlib.say(f"run_from: fixture set {d.name}: {why}; regenerating (one power-on run)")
        import regen
        if regen.main([] if not a.exe else ["--exe", a.exe]) != 0:
            return 1
    if ok or not a.print:
        man = fxlib.load_manifest(d)
    e = man["milestones"][a.milestone]
    state = d / e["file"]
    exe = d / man["exe"]
    end = a.fields or (e["field"] + a.run)
    if a.saves:
        saves = Path(a.saves)
    else:
        saves = (d / "runs" / "PRINT" if a.print else _scratch(d / "runs", "")) / "saves"
    if a.print:
        cmd = [str(exe)] + ([] if a.windowed else ["--headless"]) + [
            "--fields", str(end), "--saves", str(saves),
            "--input", str(Path(a.input).resolve() if a.input else fxlib.GOLDEN),
            "--load-state", str(state)] + a.extra
        fxlib.say("run_from: " + " ".join(cmd))
        return 0
    saves.mkdir(parents=True, exist_ok=True)
    if a.milestone in fxlib.CARD_MILESTONES and not a.saves:
        if not (d / "cards").is_dir():
            fxlib.say(f"run_from: {a.milestone} needs the set's memory card ({d / 'cards'}); rerun regen.py")
            return 2
        shutil.rmtree(saves)
        shutil.copytree(d / "cards", saves)
    cmd = [str(exe)] + ([] if a.windowed else ["--headless"]) + [
        "--fields", str(end), "--saves", str(saves),
        "--input", str(Path(a.input).resolve() if a.input else fxlib.GOLDEN),
        "--load-state", str(state)] + a.extra
    fxlib.say("run_from: " + " ".join(cmd))
    if a.print:
        return 0
    t0 = time.time()
    rc = subprocess.call(cmd, env=fxlib.game_env({k: v for k, v in __import__("os").environ.items()
                                                  if k.startswith("RG_TRACE_") or k in ("RG_TIMING", "RG_SS_AUDIT")}))
    fxlib.say(f"run_from: exit {rc} after {time.time() - t0:.1f} s (power-on to this milestone: "
              f"{e['wall_s']:.0f} s)")
    if not a.saves:
        shutil.rmtree(saves.parent, ignore_errors=True)
    return rc


def _scratch(root: Path, prefix: str) -> Path:
    """A fresh, unique scratch run dir under root.  The name used to be the start second
    alone, so two runs starting in the same second (two agents' bootcheck / run_from, or
    consecutive passes) shared it: the second copytree failed at once ("FAIL at 0 s",
    BRINGUP.md "User play-test 2" item 4) or the first run's cleanup deleted the other's
    saves.  mkdtemp makes the name unique (time stamp kept for humans)."""
    root.mkdir(parents=True, exist_ok=True)
    return Path(tempfile.mkdtemp(prefix=prefix + time.strftime("%Y%m%d-%H%M%S") + "-", dir=root))


def boot_save(a, exe_src) -> int:
    card = fxlib.CARDS / a.boot_save
    script = fxlib.PORT / "tools" / "trace" / "goldens" / f"boot_{a.boot_save}.input.txt"
    if a.input:   # --input replaces the boot script (its "# boot-end:" line, if any, counts)
        script = Path(a.input).resolve()
    if not card.is_dir() or not any(card.rglob("BASCUS-97490LV5RG_*")):
        fxlib.say(f"run_from: no game-save fixture {card} (regen.py writes {fxlib.ROUTE_CARD} when the route reaches it)")
        return 2
    if not script.exists():
        fxlib.say(f"run_from: no boot script {script}")
        return 2
    boot_end = 0
    for line in script.read_text(encoding="utf-8").splitlines():
        if line.startswith("# boot-end:"):
            boot_end = int(line.split(":", 1)[1].split()[0])
    end = a.fields or (boot_end + a.run)
    if a.saves:
        saves = Path(a.saves)
        shutil.rmtree(saves, ignore_errors=True)
    else:
        saves = _scratch(fxlib.FIXTURES / "runs", "boot-") / "saves"
    saves.parent.mkdir(parents=True, exist_ok=True)
    shutil.copytree(card, saves)
    cmd = [str(exe_src)] + ([] if a.windowed else ["--headless"]) + [
        "--fields", str(end), "--saves", str(saves),
        "--input", str(Path(a.input).resolve() if a.input else script)] + a.extra
    fxlib.say("run_from: " + " ".join(cmd))
    if a.print:
        return 0
    t0 = time.time()
    rc = subprocess.call(cmd, env=fxlib.game_env({k: v for k, v in __import__("os").environ.items()
                                                  if k.startswith("RG_TRACE_") or k in ("RG_TIMING",)}))
    fxlib.say(f"run_from: exit {rc} after {time.time() - t0:.1f} s (boot from {card.name}, control at "
              f"field {boot_end})")
    if not a.saves:
        shutil.rmtree(saves.parent, ignore_errors=True)
    return rc


if __name__ == "__main__":
    sys.exit(main())
