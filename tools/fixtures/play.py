#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Iterate on route input from a save state (docs/TEST-FIXTURES.md "Route").

    python tools/fixtures/play.py --from battle --to 25000 --input trial.txt \\
        --out out/route/t1 [--shots 24700:25000:50] [--status 20] \\
        [--save 25000] [--exe EXE] [-- extra rg-game args]

--from: a milestone name of the exe's fixture set (fxlib.MILESTONES) or a
.rgstate path (any state written by the same exe, e.g. a --save of an
earlier play.py step: chain segments without replaying from power-on).
--shots FIRST:LAST:STEP writes <out>/sNNNNN.png; --status N prints the
STATUS lines (vbl, game mode) every N fields to <out>/log.txt and stdout;
--save F writes <out>/fF.rgstate after field F (repeatable).  The saves dir
is <out>/saves (kept: the memory card the run wrote; --saves-from DIR copies
an existing card dir in first).
"""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fxlib  # noqa: E402


def resolve_state(exe_src: Path, spec: str) -> tuple[Path, Path, int]:
    """(state file, exe that wrote it, field)"""
    if spec in fxlib.MILESTONE_FIELDS:
        d = fxlib.fixture_dir(exe_src)
        ok, why = fxlib.fresh(d, exe_src, [spec])
        if not ok:
            raise SystemExit(f"play: fixture set {d}: {why} (run regen.py or run_from.py first)")
        m = fxlib.load_manifest(d)
        e = m["milestones"][spec]
        return d / e["file"], d / m["exe"], e["field"]
    p = Path(spec).resolve()
    h = fxlib.peek(p)
    return p, exe_src, h["field"]


def main(argv=None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    extra = []
    if "--" in argv:
        k = argv.index("--")
        argv, extra = argv[:k], argv[k + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="frm", required=True)
    ap.add_argument("--to", type=int, required=True, help="absolute end field")
    ap.add_argument("--input", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--exe")
    ap.add_argument("--shots", help="FIRST:LAST:STEP")
    ap.add_argument("--status", type=int, default=0)
    ap.add_argument("--save", type=int, action="append", default=[])
    ap.add_argument("--saves-from", help="copy this saves (memory card) dir in first")
    ap.add_argument("--windowed", action="store_true")
    a = ap.parse_args(argv)

    exe_src = fxlib.exe_path(a.exe)
    state, exe, f0 = resolve_state(exe_src, a.frm)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    saves = out / "saves"
    if a.saves_from:
        if saves.exists():
            shutil.rmtree(saves)
        shutil.copytree(a.saves_from, saves)
    saves.mkdir(exist_ok=True)
    cmd = [str(exe)] + ([] if a.windowed else ["--headless"]) + [
        "--fields", str(a.to), "--saves", str(saves), "--input", str(Path(a.input).resolve()),
        "--load-state", str(state)]
    if a.shots:
        s0, s1, st = (int(x) for x in a.shots.split(":"))
        fs = list(range(max(s0, f0 + 1), s1 + 1, st))
        if len(fs) > 32:  # rg-game RG_MAX_SHOTS: more is a usage error (exit 2)
            raise SystemExit(f"play: --shots gives {len(fs)} shots; rg-game takes at most 32")
        for f in fs:
            cmd += ["--shot", f"{f}:{out / f's{f:05d}.png'}"]
    for f in a.save:
        cmd += ["--save-state", f"{f}:{out / f'f{f}.rgstate'}"]
    cmd += extra
    env = {}
    if a.status:
        env["RG_STATUS_EVERY"] = str(a.status)
    t0 = time.time()
    with open(out / "log.txt", "w", encoding="utf-8") as log:
        log.write(" ".join(cmd) + "\n")
        p = subprocess.Popen(cmd, env=fxlib.game_env(env), stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT, text=True, errors="replace")
        for line in p.stdout:
            log.write(line)
            if line.startswith(("STATUS", "rg-game:", "SAVESTATE", "LOADSTATE", "RG_")) or "crash" in line.lower():
                print(line.rstrip(), flush=True)
        rc = p.wait()
    print(f"play: exit {rc} after {time.time() - t0:.1f} s, fields {f0}..{a.to}, out {out}")
    return rc


if __name__ == "__main__":
    sys.exit(main())
