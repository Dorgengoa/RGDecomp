#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Regenerate the save-state fixtures for one rg-game build (docs/TEST-FIXTURES.md).

    python tools/fixtures/regen.py [--exe EXE] [--only title,field] [--check K] [--trace]

Replays the route input (fxlib.GOLDEN, tools/trace/goldens/newgame_save2.input.txt)
from power-on ONCE, headless, RG_GPU=hw, and writes a save state at every
milestone (fxlib.MILESTONES) into out/fixtures/<exe-id>/ with manifest.json.
The exe (+ its .map) is copied into the set's bin/, so the states stay
loadable after the build dir is rebuilt.  ~8 minutes to the first battle
(field 23,000), more to the last milestone (31,920); one rg-game process.
The memory card the run leaves is kept as <set>/cards/ (CARD_MILESTONES load
with it) and, when it holds the route's save, refreshed as the game-save
fixture out/fixtures/cards/<fxlib.ROUTE_CARD>/ (run_from.py --boot-save save2).

--check K   determinism evidence: also save a state at each milestone + K and a
            --shot there (run_hash + frame hash in the manifest); verify.py
            then loads each milestone, runs K fields and compares.
--trace     also record the state trace (src/trace, RG_TRACE_*, every 5th vbl)
            for port_trace.py compare against verify.py's loaded runs.
"""
from __future__ import annotations

import argparse
import json
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fxlib  # noqa: E402


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", help="rg-game.exe (default build/fixtures-i686, or $RG_FIXTURES_EXE)")
    ap.add_argument("--only", help="comma list of milestones (default: all)")
    ap.add_argument("--check", type=int, default=0, metavar="K", help="also save + shoot at milestone + K")
    ap.add_argument("--trace", action="store_true", help="record the state trace (RG_TRACE_*)")
    ap.add_argument("extra", nargs="*", help="extra rg-game arguments (after --)")
    a = ap.parse_args(argv)

    src = fxlib.exe_path(a.exe)
    if not src.exists() or not src.with_suffix(".map").exists():
        fxlib.say(f"regen: {src} (and its .map) not found; build with tools/fixtures/build.ps1")
        return 2
    d = fxlib.fixture_dir(src)
    names = a.only.split(",") if a.only else [n for n, _, _ in fxlib.MILESTONES]
    for n in names:
        if n not in fxlib.MILESTONE_FIELDS:
            fxlib.say(f"regen: unknown milestone {n} (known: {', '.join(fxlib.MILESTONE_FIELDS)})")
            return 2
    (d / "bin").mkdir(parents=True, exist_ok=True)
    exe = d / "bin" / "rg-game.exe"
    for s, t in ((src, exe), (src.with_suffix(".map"), exe.with_suffix(".map"))):
        if not t.exists() or fxlib.sha256(s) != fxlib.sha256(t):
            shutil.copy2(s, t)
    saves = d / "saves-regen"
    shutil.rmtree(saves, ignore_errors=True)
    saves.mkdir()

    points = []   # (field, file, milestone, kind)
    for n in names:
        f = fxlib.MILESTONE_FIELDS[n]
        points.append((f, d / f"{n}.rgstate", n, "state"))
        if a.check:
            points.append((f + a.check, d / f"{n}+{a.check}.check.rgstate", n, "check"))
    last = max(p[0] for p in points)
    cmd = [str(exe), "--headless", "--fields", str(last), "--saves", str(saves), "--input", str(fxlib.GOLDEN)]
    for f, path, _, _ in points:
        cmd += ["--save-state", f"{f}:{path}"]
    shots = {}
    if a.check:
        for n in names:
            f = fxlib.MILESTONE_FIELDS[n] + a.check
            shots[f] = d / f"{n}+{a.check}.poweron.png"
            cmd += ["--shot", f"{f}:{shots[f]}"]
    cmd += a.extra
    extra_env = {}
    if a.trace:
        extra_env = {"RG_TRACE_OUT": str(d / "poweron.trace.tsv"),
                     "RG_TRACE_REGIONS": str(fxlib.PORT / "tools" / "trace" / "regions_symbols.cfg"),
                     "RG_TRACE_PORTCFG": str(fxlib.PORT / "tools" / "trace" / "port_regions.cfg"),
                     "RG_TRACE_INPUT": str(fxlib.GOLDEN), "RG_TRACE_EVERY": "5"}
    env = fxlib.game_env(extra_env)
    fxlib.say("regen: " + " ".join(cmd))
    t0 = time.time()
    got = {}
    shot_hash = {}
    with open(d / "regen.log", "w", encoding="utf-8") as log:
        p = subprocess.Popen(cmd, env=env, cwd=str(d), stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True, encoding="utf-8", errors="replace")
        for line in p.stdout:
            log.write(line)
            m = re.match(r"SAVESTATE field=(\d+) vbl=(\d+) run_hash=(\w+) bytes=(\d+) ms=(\d+) (.*)", line)
            if m:
                got[int(m.group(1))] = {"vbl": int(m.group(2)), "run_hash": m.group(3),
                                        "bytes": int(m.group(4)), "save_ms": int(m.group(5)),
                                        "wall_s": round(time.time() - t0, 1)}
                fxlib.say(line.rstrip())
            m = re.match(r"SHOT field=(\d+) \S+ hash=(\w+)", line)
            if m:
                shot_hash[int(m.group(1))] = m.group(2)
            if "EXCEPTION" in line or "refused" in line or "cannot" in line:
                fxlib.say(line.rstrip())
        rc = p.wait()
    wall = time.time() - t0
    # the card the route wrote: per-set snapshot + the exe-independent game-save fixture
    if any(saves.rglob("BASCUS-97490LV5RG_*")):
        for dst in (d / "cards", fxlib.CARDS / fxlib.ROUTE_CARD):
            shutil.rmtree(dst, ignore_errors=True)
            shutil.copytree(saves, dst)
        fxlib.say(f"regen: memory card with the route's save -> {d / 'cards'}, {fxlib.CARDS / fxlib.ROUTE_CARD}")
    shutil.rmtree(saves, ignore_errors=True)
    missing = [f for f, _, _, _ in points if f not in got]
    if missing:
        fxlib.say(f"regen: FAILED (exit {rc}): no state at fields {missing}; see {d / 'regen.log'}")
        return 1

    old = fxlib.load_manifest(d) or {}
    man = {
        "generated_by": "tools/fixtures/regen.py",
        "created": time.strftime("%Y-%m-%d %H:%M:%S"),
        "exe_source": str(src),
        "exe": "bin/rg-game.exe",
        "exe_sha256": fxlib.sha256(exe),
        "exe_id": fxlib.exe_id(exe),
        "input": str(fxlib.GOLDEN.relative_to(fxlib.PORT)).replace("\\", "/"),
        "input_sha256": fxlib.sha256(fxlib.GOLDEN),
        "env": {k: env[k] for k in ("RG_GPU", "RG_GS_ASYNC", "RG_GPU_SCALE", "RG_DATA") if k in env},
        "regen_wall_s": round(wall, 1),
        "milestones": dict(old.get("milestones", {})) if old.get("exe_sha256") == fxlib.sha256(exe) else {},
        "checks": dict(old.get("checks", {})) if old.get("exe_sha256") == fxlib.sha256(exe) else {},
    }
    for f, path, n, kind in points:
        e = dict(got[f])
        e.update({"field": f, "file": path.name})
        if kind == "state":
            e["description"] = next(x[2] for x in fxlib.MILESTONES if x[0] == n)
            man["milestones"][n] = e
        else:
            e["k"] = a.check
            e["shot_hash"] = shot_hash.get(f)
            e["shot"] = shots[f].name if f in shots else None
            e["trace"] = "poweron.trace.tsv" if a.trace else None
            man["checks"][n] = e
    (d / "manifest.json").write_text(json.dumps(man, indent=2) + "\n", encoding="utf-8")
    fxlib.say(f"regen: {len(points)} states in {wall:.0f} s -> {d}")
    for n in names:
        e = man["milestones"][n]
        fxlib.say(f"  {n:7s} field {e['field']:6d} vbl {e['vbl']:6d}  {e['bytes'] / 1e6:6.1f} MB  "
                  f"reached after {e['wall_s']:6.1f} s")
    return 0


if __name__ == "__main__":
    sys.exit(main())
