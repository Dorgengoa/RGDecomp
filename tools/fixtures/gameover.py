#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Game-over driver: lose a random battle on purpose and follow the game over to the title
screen, closed loop (docs/TEST-FIXTURES.md "Game over").  Exercises the game-session
shutdown (GameSessionShutdown_1f5bf0: stream channels closed through the driven stream-slot
step, effect tables destroyed) on the game-over path; the Insectron "Return to title" path
is insectrun.py --title (both hung before 2026-10-25, BRINGUP-HISTORY "2026-10-25 (stream
close)" / "2026-10-25 (sweep)").

    python tools/fixtures/gameover.py make [--base ch01_salgin]          # the card
    python tools/fixtures/gameover.py run  [--base ch01_salgin] [--exe EXE] [--out D]
           [--max-fields 12000] [--after 6000] [--press CROSS|NONE] [--every 120]
           [--then continue|none]

make: out/fixtures/cards/gameover_<base> = the library card <base> (saveedit.py make) with
the party cut to its leader (initial-status mode 1; the others out) and every character's
HP = 1 (max HP kept): the first hit downs the leader, a party with no one left = game over.
run: autobattle.py prep on that card (box walk to the first random encounter, battle state
at the fight phase), then segments with no input until the STATUS game mode leaves the
fight (7/2xx); then `--after` fields more with `--press` every `--every` fields (dismisses
the game-over screens) until the title (ovl 2) shows; then (--then continue, default) the
title menu's CONTINUE -> slot 1 -> FILE 01 -> load -> recap -> field control (ovl 3, 6/100):
a new game session after the shut-down one.  Verdicts: title+continue / title, no loss (the
battle ended otherwise / timeout), crash, hang, stuck (no title), continue failed.
Output D (default out/fixtures/<exe-id>/gameover/<card>/): segments, shots, phases.tsv,
route.txt (play.py --from <state> --input), result.json.  One rg-game at a time.
"""
from __future__ import annotations

import argparse
import json
import shutil
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "trace"))
import fxlib  # noqa: E402
import factory as fac  # noqa: E402  (run_seg, status_rows, lines_at)
import autobattle  # noqa: E402  (prep)
import bootcheck  # noqa: E402  (LOAD, RECAP)


def card_name(base: str) -> str:
    return f"gameover_{base}"


def with_card(card: str, d: Path) -> None:
    """A segment's saves dir holds the card (run_seg starts from an empty one; a state does
    not carry the memory card, and the title / CONTINUE read it)."""
    shutil.copytree(fxlib.CARDS / card, d / "saves", dirs_exist_ok=True)


def cmd_make(a) -> int:
    import saveedit
    src = fxlib.CARDS / a.base
    if not src.is_dir():
        subprocess.run([sys.executable, str(HERE / "saveedit.py"), "make", a.base], check=True)
    dst = fxlib.CARDS / card_name(a.base)
    if dst.exists():
        shutil.rmtree(dst)
    shutil.copytree(src, dst)
    s = saveedit.Save(saveedit.find_save(dst))
    lead, act, res = s.party_members()
    ch = s.charas()
    by_id = {v["id"]: did for did, v in ch.items()}
    s.set_party([(by_id[lead], 1)] + [(by_id[c], 0) for c in act + res if c != lead and c in by_id])
    for did, c in ch.items():
        struct.pack_into("<i", s.b, c["off"] + 0x10, 1)          # HP 1, max HP kept
    s.sync_summary_party()
    s.write()
    lead2, act2, res2 = saveedit.Save(saveedit.find_save(dst)).party_members()
    print(f"gameover: card {dst.name}: leader {lead2}, active {act2}, reserve {res2}, every HP = 1")
    return 0


def cmd_run(a) -> int:
    exe = fxlib.exe_path(a.exe)
    card = card_name(a.base)
    if not (fxlib.CARDS / card).is_dir() or a.remake:
        cmd_make(a)
    out = Path(a.out) if a.out else fxlib.fixture_dir(exe) / "gameover" / card
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    t0 = time.time()
    info = autobattle.prep(card, exe)
    res = {"exe_id": fxlib.exe_id(exe), "card": card, "prep": info}
    if not info.get("state"):
        res["verdict"] = f"no battle ({info.get('why')})"
        (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
        print(f"gameover: {res['verdict']}")
        return 1
    state, f0 = Path(info["state"]), info["field"]
    f, route, k = f0, [], 0
    tsv = open(out / "phases.tsv", "w", encoding="utf-8")
    tsv.write("phase\tfrom\tto\trc\tlast STATUS\n")
    verdict, lost = None, None
    seen = []
    while verdict is None and lost is None:
        if f - f0 >= a.max_fields:
            verdict = "no loss (timeout)"
            break
        to = f + a.seg
        d = out / f"battle{k:02d}"
        rc, log, st = fac.run_seg(exe, state, route, to, d, shots=[to], status=10, hang_s=a.hang)
        rows = fac.status_rows(log)
        seen += rows
        crash = fxlib.crash_report(log, exe)
        tsv.write(f"battle{k:02d}\t{f}\t{to}\t{rc}\t{rows[-1] if rows else ''}\n")
        print(f"  battle{k:02d} {f}..{to}  {rows[-1] if rows else '-'}", flush=True)
        if "TIMEOUT" in log:
            verdict = "hang"
        elif crash or rc != 0 or st is None:
            verdict, res["crash"] = "crash", crash
        else:
            gone = [r for r in rows if r[0] > f and not (r[1] == 3 and r[2].startswith("7/2"))]
            if gone:
                lost = gone[0]
            state, f, k = st, to, k + 1
    res["left_fight"] = lost
    if verdict is None:
        if not lost[2].startswith("7/7"):
            res["note"] = f"left the fight as {lost} (not a 7/7xx loss)"
        # to the title: chunks of --every fields, one --press per chunk (none: NONE), stop
        # at the first chunk whose STATUS shows the title overlay (ovl 2)
        lines, title, j = [], None, 0
        while title is None and f < (res["left_fight"][0] + a.after):
            to = f + a.every
            seg = [] if a.press == "NONE" else [f"{f + a.every // 2} {f + a.every // 2 + 3} {a.press}"]
            with_card(card, out / f"after{j:02d}")
            rc, log, st = fac.run_seg(exe, state, route + lines + seg, to, out / f"after{j:02d}",
                                      shots=[to], status=10, hang_s=a.hang)
            rows = fac.status_rows(log)
            seen += rows
            crash = fxlib.crash_report(log, exe)
            tsv.write("\t".join(map(str, (f"after{j:02d}", f, to, rc, rows[-1] if rows else ""))) + "\n")
            if crash or rc != 0 or st is None or "TIMEOUT" in log:
                verdict = "hang" if "TIMEOUT" in log else "crash"
                res["crash"] = crash
                break
            lines += seg
            title = next((r for r in rows if r[1] == 2), None)
            if j > 0:
                shutil.rmtree(out / f"after{j - 1:02d}", ignore_errors=True)
            state, f, j = st, to, j + 1
        print(f"  after    ..{f}  title {title}", flush=True)
        modes = []
        for r in seen:
            if r[0] >= res["left_fight"][0] and (not modes or modes[-1][1:] != r[1:]):
                modes.append(r)
        res["after_modes"] = modes[:60]
        res["title"] = title
        if verdict is None and title is None:
            verdict = "stuck (no title)"
        elif verdict is None and a.then == "continue":
            # title menu -> CONTINUE -> slot 1 -> FILE 01 -> load (bootcheck.LOAD, which is
            # relative to the power-on title at ~field 39), recap, field control
            t = title[0] - 39
            seg = [f"{t + x} {t + x + 5} {b}" for x, b, _ in bootcheck.LOAD] + [f"{t + x} {t + x + 3} CROSS" for x in bootcheck.RECAP]
            to = t + 5000
            with_card(card, out / "continue")
            rc, log, st = fac.run_seg(exe, state, route + lines + seg, to, out / "continue",
                                      shots=[t + 2500, to], status=10, hang_s=a.hang)
            rows = fac.status_rows(log)
            crash = fxlib.crash_report(log, exe)
            tsv.write("\t".join(map(str, ("continue", f, to, rc, rows[-1] if rows else ""))) + "\n")
            print(f"  continue {f}..{to}  {rows[-1] if rows else '-'}", flush=True)
            ctl = next((r for r in rows if r[1] == 3 and r[2] == "6/100"), None)
            res["continue_control"] = ctl
            lines += seg
            f = to
            if crash or rc != 0:
                verdict, res["crash"] = "crash", crash
            elif ctl is not None:
                verdict = "title+continue"
            elif "TIMEOUT" in log:
                verdict = "hang"
            else:
                verdict = f"continue failed (last {rows[-1] if rows else '-'})"
        elif verdict is None:
            verdict = "title"
        route += lines
    tsv.close()
    res.update(verdict=verdict, to_field=f, wall_s=round(time.time() - t0))
    (out / "route.txt").write_text(f"# gameover.py route from {state}\n#!stick 1 0\n" + "\n".join(route) + "\n",
                                   encoding="utf-8")
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    print(f"gameover: {verdict}; left the fight {lost}; title {res.get('title')} ({time.time() - t0:.0f} s)")
    return 0 if verdict in ("title", "title+continue") else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    m = sp.add_parser("make")
    m.add_argument("--base", default="ch01_salgin")
    m.set_defaults(fn=cmd_make)
    r = sp.add_parser("run")
    r.add_argument("--base", default="ch01_salgin")
    r.add_argument("--remake", action="store_true")
    r.add_argument("--exe")
    r.add_argument("--out")
    r.add_argument("--seg", type=int, default=400, help="fields per battle segment")
    r.add_argument("--max-fields", type=int, default=12000)
    r.add_argument("--after", type=int, default=6000, help="fields after the loss")
    r.add_argument("--press", default="CROSS", help="button pressed once per --every fields on the "
                   "way to the title (NONE: no input)")
    r.add_argument("--every", type=int, default=120)
    r.add_argument("--then", choices=("none", "continue"), default="continue",
                   help="continue: from the title, CONTINUE -> FILE 01 -> load -> field control")
    r.add_argument("--hang", type=int, default=300, help="hang timeout (s) of a segment")
    r.set_defaults(fn=cmd_run)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
