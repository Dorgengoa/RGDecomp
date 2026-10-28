#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Closed-loop route re-timer: from a save state, drive the game by its game mode with a
small policy, one short segment at a time, and write the input lines it used
(docs/TEST-FIXTURES.md "Re-timing the route").

    python tools/fixtures/retime.py --exe SET/bin/rg-game.exe --from SET/battle.rgstate \
        --base tools/trace/goldens/newgame_save2.input.txt --start 24720 --until 6/100 \
        --out out/route/rt1 [--seg 40] [--max 9000]

Policy (game mode/phase from the STATUS line at the end of each segment):
  7/201 (battle, fight)                 SQUARE 3 fields every 10 (the gun; a press during
                                        an action's recovery is buffered by the game)
  11/x  (event / help sheet)            START once the mode has lasted >= 60 fields, then
                                        every 120 (help pages)  -- while still in battle
                                        (no win seen yet); after the win: CROSS every 120
  7/4001, 7/500-504 (won, results)      CROSS every 120
  anything else                         nothing (wait)
Stops when the mode equals --until (e.g. 6/100: field control) and prints that field.
Base input lines whose first field is < --start are kept (the route prefix); the result is
OUT/route.txt = prefix + generated lines, and OUT/state_<field>.rgstate at the stop
(the next block of the route starts from it).  One rg-game at a time.
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402


def run(exe: Path, state: Path, inp: Path, to: int, save: Path, out: Path):
    saves = out / "saves"
    saves.mkdir(parents=True, exist_ok=True)
    cmd = [str(exe), "--headless", "--fields", str(to), "--saves", str(saves), "--input", str(inp),
           "--load-state", str(state), "--save-state", f"{to}:{save}"]
    p = subprocess.run(cmd, env=fxlib.game_env({"RG_STATUS_EVERY": "10"}), capture_output=True, text=True,
                       errors="replace", timeout=600)
    modes = {}
    for ln in (p.stdout + p.stderr).splitlines():
        m = re.match(r"STATUS field=(\d+) .*?gamemode=(\S+)", ln)
        if m:
            modes[int(m.group(1))] = m.group(2)
    return p.returncode, modes


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--exe", required=True)
    ap.add_argument("--from", dest="frm", required=True)
    ap.add_argument("--base", required=True)
    ap.add_argument("--start", type=int, required=True)
    ap.add_argument("--until", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--seg", type=int, default=40)
    ap.add_argument("--max", type=int, default=9000)
    ap.add_argument("--after-win", default="CROSS", help="button(s) for 11/x after the win (e.g. CROSS+START for help sheets)")
    a = ap.parse_args(argv)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    exe = Path(a.exe).resolve()
    base = [ln for ln in Path(a.base).read_text().splitlines()]
    prefix = []
    for ln in base:
        m = re.match(r"\s*(?:#!stick\s+)?(\d+)\s+\d+", ln)
        if ln.startswith("#!stick 1 0") or not m or int(m.group(1)) < a.start:
            prefix.append(ln)
    gen: list[str] = []
    state = Path(a.frm).resolve()
    f = fxlib.peek(state)["field"]
    mode, since, won, last_btn = "?", f, False, -10_000
    t_end = f + a.max
    while f < t_end:
        to = f + a.seg
        lines = []
        g0 = max(f + 1, a.start)
        if mode == "7/201":
            k = g0 + (-g0) % 10
            lines += [f"{x} {x + 2} SQUARE" for x in range(k, to, 10)]
        elif mode.startswith("11/") or mode.startswith("7/40") or mode.startswith("7/50"):
            btn = "START" if (mode.startswith("11/") and not won) else (a.after_win if mode.startswith("11/") else "CROSS")
            first = since + 60 if last_btn < since else last_btn + 120
            x = max(first, g0)
            while x < to:
                lines.append(f"{x} {x + 3} {btn}")
                last_btn = x
                x += 120
        inp = out / "seg.input.txt"
        inp.write_text("\n".join(prefix + gen + lines) + "\n")
        nxt = out / f"s{to}.rgstate"
        rc, modes = run(exe, state, inp, to, nxt, out)
        if rc != 0 or not nxt.exists():
            print(f"retime: segment {f}..{to} failed (exit {rc})")
            return 1
        gen += lines
        for k in sorted(modes):
            m = modes[k]
            if m != mode:
                print(f"  {k:6d} {mode} -> {m}", flush=True)
                mode, since = m, k
                if m in ("7/4001",) or m.startswith("7/50"):
                    won = True
            if m == a.until:
                (out / "route.txt").write_text("\n".join(prefix + gen) + "\n")
                print(f"retime: {a.until} at field {k}; route {out / 'route.txt'}; state {nxt}")
                return 0
        if state.parent == out and state.name.startswith("s"):
            state.unlink(missing_ok=True)
        state, f = nxt, to
    (out / "route.txt").write_text("\n".join(prefix + gen) + "\n")
    print(f"retime: {a.until} not reached by {f}")
    return 2


if __name__ == "__main__":
    sys.exit(main())
