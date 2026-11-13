#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Insectron 2-Player Battle match driver for the online session (lane insnet 2026-11-12;
docs/INSECTRON-VERSUS.md "Online 2-Player Battle", "Tests").

    python tools/net/netmatch.py play [--exe EXE] [--saves DIR] [--out D] [--max-fields N]

Plays one whole 2-Player Battle in the online session's own layout, without a network:
`rg-game --net-solo` builds the session saves (card 1 = P1's save, card 2 = P2's save, as
FILE 01 each), runs the built-in prefix (title -> INSECTRON -> 2-Player Battle -> controllers
1P = 1 / 2P = 2 -> both players loaded) and from the hand-over on feeds the --net-input script
to BOTH ports, so one driver plays both players (each player's turns read that player's pad).
Closed loop, one save state per decision (insectstory.py's memory probe of the battle object:
the side to move, the cursor page, command menu, move / attack marks): each piece of the side
to move attacks an adjacent enemy (king first, then the weakest) or walks toward the enemy king;
then End Turn.  After the battle: the results, the rematch prompt ("No"), the tally, back to
the INSMENU mode list; the cards are compared before / after (experience, card writes).

Output D (default out/insnet/match): route.txt (the whole script, game VBlank keyed: the input
of BOTH players; tools/net/netpair.py splits it into the host's and the joiner's), decisions.tsv,
phases.tsv, segs/*/s*.png, result.json (verdict, fields, card diff, hashes).
"""
from __future__ import annotations

import argparse
import json
import re
import shutil
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
FX = HERE.parent / "fixtures"
sys.path.insert(0, str(FX))
import factory as fac  # noqa: E402
import fxlib  # noqa: E402
import insectstory as ins  # noqa: E402

PORT = fxlib.PORT
HANDOVER = 12100         # rg_insnet.c K_PREFIX_HANDOVER
# from the hand-over (cursor on "Begin battle", both players loaded) to BATTLE START, relative to
# HANDOVER; out/insvs/scripts/p9.txt timings (10,000 .. 20,800), each player's choices on their pad
SETUP = [(100, "CROSS"),                     # Begin battle
         (400, "CROSS"),                     # Are you ready? Yes
         (3200, "CROSS"),                    # Defeat the king
         (3600, "CROSS"),                    # Player 1, select your team
         (3900, "LEFT"), (3930, "CROSS"),    # auto select? Yes
         (4300, "CROSS"),                    # Is this team okay? Yes
         (4600, "LEFT"), (4630, "CROSS"),    # Use Auto-Layout? Yes
         (5000, "CROSS"), (5400, "CROSS"), (5800, "CROSS"),
         (6200, "LEFT"), (6230, "CROSS"),
         (6600, "CROSS"),                    # Player 2, select your team
         (7000, "LEFT"), (7030, "CROSS"),    # auto select? Yes
         (7400, "CROSS"),                    # Is this team okay? Yes
         (7600, "LEFT"), (7630, "CROSS"),    # Use Auto-Layout? Yes
         (8000, "CROSS"),                    # layout okay? Yes
         (8400, "CROSS"),                    # Select a king (message)
         (8800, "CROSS"),                    # king
         (9200, "CROSS"),                    # Is this okay? Yes
         (9600, "CROSS"),                    # Player 1 goes first
         (10300, "CROSS"), (10600, "CROSS"), (10900, "CROSS"), (11200, "CROSS")]
SETUP_LEN = 11600


class Driver(ins.Driver):
    def __init__(self, exe: Path, saves: Path, out: Path):
        self.saves = saves
        self.prev_saves = None
        super().__init__(exe, "net", out)
        # + the rematch prompt's step byte (insect_InsectBattleRematchPromptStep_4f0f60: battle
        # object +0x5FC2; 3 = waiting for Yes / No, CIRCLE = No)
        b = ins.map_rvas(exe, {"D_00482AF0"})["D_00482AF0"]
        self.spec += f",p0x{b:X}+0x5FC2:2"

    def seg(self, state, f0, keys, n, name, shots=(), every=10):
        """keys [(rel, BUTTON)] from state (None = power-on) at f0 for n fields."""
        self.route += [f"{f0 + r} {f0 + r + 3} {b}" for r, b in keys]
        d = self.out / "segs" / f"{self.k:04d}_{name}"
        self.k += 1
        d.mkdir(parents=True, exist_ok=True)
        inp = d / "input.txt"
        inp.write_text("\n".join(ln for ln in self.route if int(ln.split()[0]) > f0) + "\n", encoding="utf-8")
        to = f0 + n
        st = d / f"f{to}.rgstate"
        sv = d / "saves"
        shutil.rmtree(sv, ignore_errors=True)
        shutil.copytree(self.prev_saves or self.saves, sv)   # the session saves carry on
        cmd = [str(self.exe), "--headless", "--fields", str(to), "--saves", str(sv), "--net-solo",
               "--net-save", "1:0", "--net-save2", "2:0", "--net-input", str(inp), "--net-log", str(d / "net.log"),
               "--save-state", f"{to}:{st}"]
        if state is not None:
            cmd += ["--load-state", str(Path(state).resolve())]
        for s in shots:
            cmd += ["--shot", f"{f0 + s}:{d / f's{f0 + s:05d}.png'}"]
        import math
        every = math.gcd(to, n) if n < 10 or to % every else every
        env = {"RG_SS": "1", "RG_STATUS_EVERY": str(every), "RG_STATUS_DUMP": self.spec}
        rc, log = fac.run_game(cmd, fxlib.game_env(env))
        (d / "log.txt").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
        if st.exists():
            self.prev_saves = sv
        m = ins.parse(log)
        if m is not None:
            m["rematch_step"] = rematch_step(log)
        return rc, log, (st if st.exists() else None), m, d


def rematch_step(log: str):
    """the rematch prompt's step byte from the last DUMP block (the 15th region of the spec)"""
    blocks = {}
    for ln in log.splitlines():
        mm = re.match(r"DUMP field=(\d+) vbl=\d+ (\S+): (.*)$", ln)
        if mm:
            blocks.setdefault(int(mm.group(1)), []).append(mm.group(3).strip())
    if not blocks:
        return None
    bl = blocks[max(blocks)]
    if len(bl) < 15 or bl[14] == "NULL":
        return None
    v = int(bl[14].replace(" ", "")[:2], 16)
    return v - 256 if v >= 128 else v


def pick_target(m, side):
    best = None
    for p in m["pieces"]:
        if p["side"] != side and p["inplay"] and p["cell"]:
            x, y = p["cell"]
            if m["at"][y * 5 + x] & 1:
                key = (0 if p["king"] else 1, p["hp"])
                if best is None or key < best[0]:
                    best = (key, (x, y))
    return best[1] if best else None


def pick_move(m, side):
    en = [p for p in m["pieces"] if p["side"] != side and p["inplay"] and p["cell"]]
    if not en:
        return None
    king = next((p for p in en if p["king"]), en[0])
    best = None
    for i in range(35):
        if m["mv"][i] & 2:
            c = (i % 5, i // 5)
            key = (ins.cheb(c, king["cell"]), min(ins.cheb(c, p["cell"]) for p in en), abs(c[0] - 2))
            if best is None or key < best[0]:
                best = (key, c)
    return best[1] if best else None


def card_files(d: Path) -> dict:
    return {str(p.relative_to(d)).replace("\\", "/"): p.read_bytes() for p in sorted(d.rglob("*")) if p.is_file()}


def cmd_play(a) -> int:
    exe = fxlib.exe_path(a.exe)
    out = Path(a.out)
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    saves = Path(a.saves)
    drv = Driver(exe, saves, out)
    tsv = open(out / "phases.tsv", "w", encoding="utf-8")
    t0 = time.time()
    res = {"exe": str(exe)}

    def phase(name, f, note=""):
        tsv.write(f"{name}\t{f}\t{note}\n")
        tsv.flush()
        print(f"  {name:8s} {f:6d}  {note}", flush=True)

    def done(verdict, f):
        res.update(verdict=verdict, field=f, seconds=round(time.time() - t0))
        (out / "route.txt").write_text("# netmatch.py route: both players' input from the hand-over (game VBlank)\n" +
                                       f"# handover {HANDOVER}\n" + "\n".join(drv.route) + "\n", encoding="utf-8")
        (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
        print(f"netmatch: {verdict} at field {f} ({res['seconds']} s)")
        return 0 if verdict.startswith("done") else 1

    # boot: the prefix, to the hand-over
    f = HANDOVER + 50
    rc, log, state, m, d = drv.seg(None, 0, [], f, "boot", shots=(f,))
    if state is None:
        return done(f"boot failed (exit {rc})", f)
    phase("boot", f, f"STATUS {fac.status_rows(log)[-1] if fac.status_rows(log) else '-'}")
    # setup, closed loop: every prompt from "Battle Start!!" to BATTLE START is a yes / no
    # (LEFT = Yes), a list whose first entry will do, or a message: LEFT + CROSS until the side to
    # move has its cursor on the board (page 2, step 0x1C)
    for i in range(80):
        rc, log, state, m, d = drv.seg(state, f, [(20, "LEFT"), (60, "CROSS")], 150, f"setup{i:02d}", shots=(150,))
        f += 150
        if state is None:
            return done(f"setup: crash (exit {rc})", f)
        if m and m.get("battle") and m.get("page") == 2 and m.get("step") and m["step"][0] == 0x1C:
            break
    else:
        return done("setup: no battle cursor after 80 segments", f)
    phase("setup", f, f"board {ins.board_text(m)} side {m['side']}")

    # battle: both sides, one decision per segment
    acted, last_side, idle, turns, seen_kings = set(), None, 0, 0, False
    while True:
        if f > a.max_fields:
            return done("timeout", f)
        if not m or not m["battle"]:
            break
        side = m["side"]
        if side != last_side:
            acted, last_side = set(), side
            turns += 1
        own = [p for p in m["pieces"] if p["side"] == side and p["inplay"]]
        en = [p for p in m["pieces"] if p["side"] != side and p["inplay"]]
        kings = any(p["king"] for p in en) and any(p["king"] for p in own)
        seen_kings = seen_kings or kings
        if seen_kings and (not en or not kings):
            # the win, the announcer (CROSS pages through), then "Do you want a rematch?" with the
            # session tally: No (RIGHT + CROSS).  Measured: the prompt is up ~840 fields after the
            # first "decided" model (out/insnet/after_sheet.png)
            res.setdefault("decided_field", f)
            if m.get("rematch_step") == 3:
                keys, n, act = [(20, "CIRCLE")], 200, "rematch prompt: No (CIRCLE)"
                res["rematch_prompt_field"] = f
            else:
                keys, n, act = [(20, "CROSS")], 120, f"battle decided: CROSS (rematch step {m.get('rematch_step')})"
        elif m["page"] == 2 and m["step"][0] == 0x1C:
            cand = [p for p in own if p["j"] not in acted and p["cell"] and not p["king"]]
            king = next((p for p in own if p["king"]), None)
            if king and king["j"] not in acted and any(ins.cheb(king["cell"], e["cell"]) <= 1 for e in en if e["cell"]):
                cand.append(king)
            if cand:
                me = cand[0]
                drv.cur_piece = me
                keys, n, act = ins.cursor_keys(m["cur"], me["cell"]), 90, f"P{side + 1} select {me['j']} at {me['cell']}"
            else:
                anyp = next(p for p in own if p["cell"])
                drv.cur_piece = None
                keys, n, act = ins.cursor_keys(m["cur"], anyp["cell"]), 90, f"P{side + 1} select for End Turn"
        elif m["page"] == 4 and m["cmds"]:
            me = getattr(drv, "cur_piece", None)
            if me is None:
                keys, n, act = ins.menu_keys(m, ins.CMD_END) + [(160, "CROSS")], 260, f"P{side + 1} End Turn + Yes"
                acted = set(range(5))
            elif ins.CMD_ATTACK in m["cmds"]:
                keys, n, act = ins.menu_keys(m, ins.CMD_ATTACK), 90, "Attack"
            elif ins.CMD_MOVE in m["cmds"] and not me["king"]:
                keys, n, act = ins.menu_keys(m, ins.CMD_MOVE), 90, "Move"
            else:
                keys, n, act = ins.menu_keys(m, ins.CMD_WAIT if ins.CMD_WAIT in m["cmds"] else ins.CMD_END), 120, "Wait"
                acted.add(me["j"])
                drv.cur_piece = None
        elif m["page"] == 10:
            me = drv.cur_piece
            tgt = pick_move(m, side) if me else None
            if tgt is None:
                keys, n, act = [(10, "CIRCLE")], 90, "no move: back"
                if me:
                    acted.add(me["j"])
            else:
                keys, n, act = ins.cursor_keys(m["cur"], tgt), 200, f"move to {tgt}"
        elif m["page"] == 11:
            tgt = pick_target(m, side)
            me = drv.cur_piece
            if tgt is None:
                keys, n, act = [(10, "CIRCLE")], 90, "no target: back"
            else:
                keys, n, act = ins.cursor_keys(m["cur"], tgt), 400, f"attack {tgt}"
                if me:
                    acted.add(me["j"])
                drv.cur_piece = None
        else:
            idle += 1
            if idle > a.max_idle:
                return done(f"stuck (page {m['page']} state {m['state']} step {m['step']})", f)
            keys, n, act = ([(10, "CROSS")] if idle % 4 == 0 else []), 120, f"wait (page {m['page']} step {m['step']})"
        if keys and not act.startswith("wait"):
            idle = 0
        drv.note(m, act)
        rc, log, nstate, nm, d = drv.seg(state, f, keys, n, f"t{turns:03d}", shots=(n,))
        f += n
        rows = fac.status_rows(log)
        if "TIMEOUT" in log or rc != 0 or nstate is None or fxlib.crash_report(log, exe):
            return done(f"crash or hang (exit {rc})", f)
        state, m = nstate, nm
        if rows and rows[-1][1] != 5:
            phase("battle", f, f"left INSECT: {rows[-1]}")
            break
    res["turns"] = turns
    phase("battle", f, f"{turns} turns")
    # after: no input for a while (results, experience, card writes), then CROSS through the prompts
    after = []
    for i in range(a.after_segs):
        keys = []   # watch: the way out of the battle, experience, card writes
        rc, log, nstate, nm, d = drv.seg(state, f, keys, 200, f"after{i:02d}", shots=(100, 200))
        f += 200
        if nstate is None:
            return done(f"crash after the battle (exit {rc})", f)
        state = nstate
        rows = fac.status_rows(log)
        after.append((f, rows[-1] if rows else None))
        phase("after", f, f"STATUS {rows[-1] if rows else '-'}")
        if rows and rows[-1][1] == 6 and i >= 12:
            break
    res["after"] = after
    # the cards: the session saves the last segment ran with, against the ones the session built
    sess = d / "saves" / "netplay" / "session"
    base_sess = out / "segs" / "0000_boot" / "saves" / "netplay" / "session"
    a0, a1 = card_files(base_sess), card_files(sess)
    res["card_changes"] = sorted(k for k in set(a0) | set(a1) if a0.get(k) != a1.get(k))
    return done("done", f)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("play")
    p.add_argument("--exe")
    p.add_argument("--saves", default=str(PORT / "out" / "insvs" / "saves_base"))
    p.add_argument("--out", default=str(PORT / "out" / "insnet" / "match"))
    p.add_argument("--max-fields", type=int, default=120000)
    p.add_argument("--max-idle", type=int, default=40)
    p.add_argument("--after-segs", type=int, default=40)
    a = ap.parse_args(argv)
    return cmd_play(a)


if __name__ == "__main__":
    sys.exit(main())
