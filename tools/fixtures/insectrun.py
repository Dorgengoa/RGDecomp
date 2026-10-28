#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Insectron driver: TITLE -> INSMENU -> a CPU-vs-CPU INSECT battle played to its end ->
INSMENU -> TITLE, closed loop (docs/TEST-FIXTURES.md "Factory and Insectron drivers").

    python tools/fixtures/insectrun.py run    [--exe EXE] [--out D] [--max-fields 40000]
    python tools/fixtures/insectrun.py replay ROUTE [--exe EXE] [--out D]

Card: out/fixtures/cards/insectron_play (saveedit.py make insectron_play: the insectron
card's two registered teams ALPHA / BRAVO with --insect-formation, so all five insects of
each team take the board; with the plain insectron card only the two leaders are placed and
the Watch Battle never ends).  Boot: boot_insectron.input.txt (title INSECTRON -> Watch
Battle -> both teams from FILE 01 -> Battle Start -> INSECT, 15/101 at 11,500).

run: from the battle-start state (once per exe, out/fixtures/<exe-id>/insect/), segments of
--seg fields (no input: the CPUs play both sides) until the STATUS game mode leaves 15
(battle end, field E), then the scripted way out, relative to P = E + 1,600 (the rematch
prompt is up by then): RIGHT + CROSS = rematch "No" -> "Thanks for watching!" -> INSMENU
(ovl 6) "How was the match?" -> mode list (done).  --title: on through Return to title ->
"Return to the title screen?" Yes -> "We look forward to your next battle!" -> TITLE (ovl 2);
TITLE at ~19,700 (hung before the 2026-10-25 stream-close fix, TITLE below).  A run under
other mode switches (RG_IOP / RG_AUDIO / RG_THREADS set) keeps its own battle-start state.
Verdicts: done (INSMENU / TITLE reached after
the battle), battle timeout (--max-fields), crash, hang, failed at <phase>.  Output D (default
out/fixtures/<exe-id>/insect/run/): route.txt, boot_route.txt (boot script + route, for
run_from.py --boot-save insectron_play --input), phases.tsv, s*.png, result.json (battle
fields, winner screenshot, final STATUS).

replay: one power-on run of a boot_route.txt; result.json as factory.py replay (run hash,
STATUS rows, screenshot hashes).  routecmp.py compares two builds on the boot route.  One rg-game at a time.
"""
from __future__ import annotations

import argparse
import json
import shutil
import os
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402
import factory as fac  # noqa: E402  (run_seg, status_rows, replay)

CARD = "insectron_play"
BOOT = fxlib.PORT / "tools" / "trace" / "goldens" / "boot_insectron.input.txt"
B0 = 11500        # battle running (boot_insectron.input.txt "boot-end")
PROMPT_DELAY = 1600
EXIT = [(20, "RIGHT"), (60, "CROSS"),           # "Do you want a rematch?" No
        (300, "CROSS"), (600, "CROSS"), (900, "CROSS")]   # "Thanks for watching!", INSMENU texts
EXIT_LEN = 1300                                  # INSMENU mode list (ovl 6, 11/0)
# --title: on to the title screen (off by default).  Hung on every exe until 2026-10-25
# (stream close): SoundStreamSlotShutdown_1bdfd0's kick loop never ran the driven slot step,
# then EffTableDestroyAll_1a0240 spun (HandleTableGet_1a1d50 lost its handle argument);
# docs/bringup/BRINGUP-HISTORY.md 2026-10-25 (stream close).  TITLE at ~19,700.
TITLE = [(1320, "DOWN"), (1350, "DOWN"), (1390, "CROSS"),  # Watch Battle -> Return to title
         (1600, "CROSS"),                                  # "Return to the title screen?" Yes
         (1900, "CROSS")]                                  # "We look forward to your next battle!"
TITLE_LEN = 3400


def boot_state(exe: Path) -> Path:
    d = fxlib.fixture_dir(exe) / "insect"
    d.mkdir(parents=True, exist_ok=True)
    # a state only loads under the init fingerprint it was saved with: one per mode switch set
    tag = "".join(f"_{k[3:].lower()}-{os.environ[k]}" for k in ("RG_IOP", "RG_AUDIO", "RG_THREADS")
                  if os.environ.get(k))
    st = d / f"{CARD}_{B0}{tag}.rgstate"
    if st.exists():
        return st
    if not (fxlib.CARDS / CARD).is_dir():
        subprocess.run([sys.executable, str(HERE / "saveedit.py"), "make", CARD], check=True)
    cmd = [sys.executable, str(HERE / "run_from.py"), "--boot-save", CARD, "--input", str(BOOT),
           "--exe", str(exe), "--fields", str(B0 + 2), "--", "--save-state", f"{B0}:{st}"]
    p = subprocess.run(cmd, env=fxlib.game_env({"RG_SS": "1", "RG_STATUS_EVERY": "100"}),
                       capture_output=True, text=True, errors="replace")
    (d / f"boot{tag}.log").write_text(p.stdout + p.stderr, encoding="utf-8")
    if not st.exists():
        raise SystemExit(f"insectrun: boot state not written (exit {p.returncode}, log {d / ('boot' + tag + '.log')})")
    return st


def cmd_run(a) -> int:
    exe = fxlib.exe_path(a.exe)
    out = Path(a.out) if a.out else fxlib.fixture_dir(exe) / "insect" / "run"
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    state = boot_state(exe)
    f, route, t0 = B0, [], time.time()
    res = {"exe_id": fxlib.exe_id(exe), "card": CARD, "from_state": str(state)}
    tsv = open(out / "phases.tsv", "w", encoding="utf-8")
    tsv.write("phase\tfrom\tto\trc\tlast STATUS\n")
    verdict, end_field, k = None, None, 0
    while verdict is None and end_field is None:
        if f - B0 >= a.max_fields:
            verdict = "battle timeout"
            break
        to = f + a.seg
        d = out / f"battle{k:02d}"
        rc, log, st = fac.run_seg(exe, state, route, to, d, shots=[to], status=50)
        rows = fac.status_rows(log)
        crash = fxlib.crash_report(log, exe)
        tsv.write(f"battle{k:02d}\t{f}\t{to}\t{rc}\t{rows[-1] if rows else ''}\n")
        print(f"  battle{k:02d} {f}..{to}  {rows[-1] if rows else '-'}", flush=True)
        if "TIMEOUT" in log:
            verdict = "hang"
        elif crash or rc != 0 or st is None:
            verdict, res["crash"] = "crash", crash
        else:
            ended = [r for r in rows if r[0] > f and not r[2].startswith("15/")]
            if ended:
                end_field = ended[0][0]
            shutil.copyfile(d / f"s{to:05d}.png", out / f"s{to:05d}_battle.png")
            if k > 0:
                (out / f"battle{k - 1:02d}" / f"f{f}.rgstate").unlink(missing_ok=True)
            state, f, k = st, to, k + 1
    res["battle_end"] = end_field
    if verdict is None:
        p0 = end_field + PROMPT_DELAY
        if p0 > f:   # play on (no input) to the prompt
            rc, log, st = fac.run_seg(exe, state, route, p0, out / "prompt", shots=[p0], status=50)
            if st is None:
                verdict = "crash"
            else:
                shutil.copyfile(out / "prompt" / f"s{p0:05d}.png", out / f"s{p0:05d}_prompt.png")
                state, f = st, p0
        if verdict is None:
            lines = fac.lines_at(f, EXIT + (TITLE if a.title else []))
            to = f + (TITLE_LEN if a.title else EXIT_LEN)
            rc, log, st = fac.run_seg(exe, state, route + lines, to, out / "exit", shots=[f + 900, to], status=50,
                                      hang_s=a.hang)
            rows = fac.status_rows(log)
            crash = fxlib.crash_report(log, exe)
            tsv.write(f"exit\t{f}\t{to}\t{rc}\t{rows[-1] if rows else ''}\n")
            print(f"  exit     {f}..{to}  {rows[-1] if rows else '-'}", flush=True)
            for s in (f + 900, to):
                if (out / "exit" / f"s{s:05d}.png").exists():
                    shutil.copyfile(out / "exit" / f"s{s:05d}.png", out / f"s{s:05d}_exit.png")
            insmenu = any(r[1] == 6 for r in rows)
            if crash or rc != 0:
                verdict, res["crash"] = "crash", crash
            elif rows and insmenu and rows[-1][1] == (2 if a.title else 6):
                verdict = "done"
            elif "TIMEOUT" in log:
                verdict = "hang"
            else:
                verdict = f"failed at exit (INSMENU {'seen' if insmenu else 'not seen'}, last {rows[-1] if rows else '-'})"
            route += lines
            f = to
    tsv.close()
    res.update(verdict=verdict, to_field=f, battle_fields=(end_field - B0) if end_field else None,
               wall_s=round(time.time() - t0))
    (out / "route.txt").write_text(f"# insectrun.py route from {res['from_state']}\n#!stick 1 0\n" + "\n".join(route) + "\n",
                                   encoding="utf-8")
    boot = [ln for ln in BOOT.read_text(encoding="utf-8").splitlines() if ln.split("#", 1)[0].strip()]
    (out / "boot_route.txt").write_text(
        "# insectrun.py: boot_insectron.input.txt + route (run_from.py --boot-save insectron_play --input)\n"
        f"# boot-end: {B0}\n" + "\n".join(boot) + "\n" + "\n".join(route) + "\n", encoding="utf-8")
    res["phase_ends"] = [B0] + ([end_field + PROMPT_DELAY, f] if end_field else [])
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    print(f"insectrun: {verdict}; battle {res['battle_fields']} fields; route {out / 'boot_route.txt'} "
          f"({time.time() - t0:.0f} s)")
    return 0 if verdict == "done" else 1


def cmd_replay(a) -> int:
    exe = fxlib.exe_path(a.exe)
    rt = Path(a.route)
    rj = rt.parent / "result.json"
    info = json.loads(rj.read_text()) if rj.exists() else {}
    ends = info.get("phase_ends") or [B0]
    shots = sorted(set(ends + ([info["battle_end"]] if info.get("battle_end") else []) + [2300, 10300]))
    end = max(ends) + 20
    out = Path(a.out) if a.out else rt.parent / f"replay_{fxlib.exe_id(exe)}"
    res = fac.replay(exe, rt, out, CARD, shots, end)
    print(json.dumps({k: v for k, v in res.items() if k != "status"}, indent=1))
    return 0 if res["rc"] == 0 and not res["crash"] else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    r = sp.add_parser("run")
    r.add_argument("--exe")
    r.add_argument("--out")
    r.add_argument("--seg", type=int, default=1000, help="fields per battle segment")
    r.add_argument("--max-fields", type=int, default=40000)
    r.add_argument("--title", action="store_true", help="go on to the title screen (Return to title; "
                   "the session shutdown that hung before 2026-10-25, see TITLE)")
    r.add_argument("--hang", type=int, default=300, help="hang timeout (s) of a segment after the slot wait")
    r.set_defaults(fn=cmd_run)
    p = sp.add_parser("replay")
    p.add_argument("route")
    p.add_argument("--exe")
    p.add_argument("--out")
    p.set_defaults(fn=cmd_replay)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
