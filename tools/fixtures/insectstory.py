#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Story Insectron driver: the Zerard tournament's final (Rank E, battle 5) played and won from
a manufactured card, through the rank reward (InsectBattleMatchUpdateMaybe_319800 ->
InsectronRewardLookupMaybe_3e84f0) back to the field (docs/TEST-FIXTURES.md "Story Insectron").

    python tools/fixtures/insectstory.py run    [--exe EXE] [--card insect_final_s] [--out D]
    python tools/fixtures/insectstory.py replay ROUTE [--exe EXE] [--card C] [--out D]

Card (saveedit.py make insect_final_s): late story point 13020 + the insect side of the
developers' start state initial_status 115 'Insectron E-5' (3 Insector Traps, 3 Rearing Cages,
15 named insects in the cages, feed, Insectron License; --strong-insects: level 5, stats 100)
and its vars (rank var 5 = 1, entered rank var 6 = 1, battle var 7 = 4), the party in front of
the receptionist (NPC 24228).  How the trigger was found (no input search): `evscan.py find
1574,1587` (event commands MenuInsectEntryOpen / InvCountInsects) -> map/m04/m04.pac m04.stb
routine 0xED04 (NPC 24228, run by the talk dispatcher when var 121 = 3): var 6 = 0 -> "Would you
like to enter the tournament?" + at least 5 insects (InvCountInsects_25c280) + rank menu; var 6 !=
0 -> "Continue from Rank X, Battle var7+1?" + 5 insects -> the match.  The NPC's place: zone
rc/param/zone/zl05_2_en.pac ZL05_*npc.cfg.bin (#101 id, #102 x, y, z, yaw).

run (closed loop, every segment from the previous one's state, the route kept for a power-on
replay):
  boot     bootcheck's card boot (CONTINUE .. recap) to field control C;
  talk     CROSS x8 from C+10: "Welcome to the Insectron Championship!" -> "Continue from Rank E,
           Battle 5?" Yes -> INSECT overlay (ovl 5, game mode 15/101), "it's the final round!";
  team     "Have your Insectors automatically selected?" Yes (LEFT + CROSS), "Is this team okay?"
           Yes, "Use Auto-Layout?" Yes -> BATTLE START;
  battle   one decision per segment from a memory probe (RG_STATUS_DUMP of the battle object
           *D_00482AF0: pieces +0x35F8 (2 sides x 5 x 0x1E8: +0x1A HP, +0x1E max, +0x71 side,
           status bits at +0, 27 in play, 26 king), board +0x4960 (7 x 5 piece pointers;
           +0x118 move marks bit 1, +0x13B attack marks bit 0), cursor set +0x4F90 (pages
           {key, .., +8 x, +9 y}; current page = last non-null of +0xC[8]), command menu
           list +0x502C (node +8 command: 0 attack, 1 move, 2 special, 3 help, 4 wait, 5 end
           turn, 6 parameters), state / step stacks +0x5DD4 / +0x5E34, side to move +0x5EF1):
           each own non-king piece attacks an adjacent enemy (king first, then the weakest) or
           moves to the reachable cell nearest the enemy king and attacks from there; then
           End Turn.  The enemy turns run by themselves;
  after    CROSS every 60 fields until field control (ovl 3, 6/100), then a segment without input
           (a press in the field would talk to the receptionist again).
Verdict: won (vars 115 / 116 = reward item / count set, var 5 raised, back in the field),
lost, timeout, crash, hang.  Output D (default out/fixtures/<exe-id>/insectstory/<card>/):
phases.tsv, decisions.tsv (one row per decision with the board), route.txt and
boot_route.txt (run_from.py --boot-save CARD --input), result.json, s*.png.

replay: one power-on run of boot_route.txt (factory.replay: run hash, STATUS rows, shots).
"""
from __future__ import annotations

import argparse
import json
import re
import shutil
import struct
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import bootcheck  # noqa: E402
import factory as fac  # noqa: E402  (run_game, status_rows, replay)
import fxlib  # noqa: E402

CARD = "insect_final_s"
TALK = [(10 + 60 * k, "CROSS") for k in range(8)]        # talk .. "Continue from Rank E, Battle 5?" Yes
TALK_LEN = 900
TEAM = [(280, "LEFT"), (320, "CROSS"),                   # "automatically selected?" Yes
        (440, "CROSS"),                                  # "Is this team okay?" Yes
        (530, "LEFT"), (560, "CROSS"),                   # "Use Auto-Layout?" Yes
        (680, "CROSS"), (800, "CROSS"), (920, "CROSS"),  # "Select a king." help, the default king
        (1040, "CROSS"), (1160, "CROSS")]                # BATTLE START -> PLAYER'S TURN
TEAM_LEN = 1500
PIECE = 0x1E8
SIDE = 0x994
CMD_ATTACK, CMD_MOVE, CMD_WAIT, CMD_END = 0, 1, 4, 5


# ---------------------------------------------------------------- memory probe
def map_rvas(exe: Path, names) -> dict:
    out = {}
    for line in open(Path(exe).with_suffix(".map"), encoding="latin-1"):
        m = re.match(r"\s*000[23]:[0-9a-f]+\s+_?(\w+)\s+([0-9a-f]{16})\s", line)
        if m and m.group(1) in names:
            out[m.group(1)] = int(m.group(2), 16) - 0x400000
    return out


def dump_spec(exe: Path) -> str:
    """Battle object *D_00482AF0 (InsectBattleGet_31a8d0) + the story vars (GameData D_004B8B30
    +0x10 = StateBlock, vars at +0x128)."""
    r = map_rvas(exe, {"D_00482AF0", "D_004B8B30"})
    b = r["D_00482AF0"]
    return ",".join([f"p0x{b:X}+0x35F8:0x1328", f"p0x{b:X}+0x4960:0x160", f"p0x{b:X}/0x4F98+0:0x200",
                     f"p0x{b:X}+0x5DB8:0x140", f"p0x{b:X}+0x0:4", f"p0x{r['D_004B8B30'] + 0x10:X}+0x128:0x100",
                     f"p0x{b:X}+0x4F90:0x30"] + [f"p0x{b:X}/0x5030" + "/4" * k + "+0:0x10" for k in range(7)])


VAR_IDS = (5, 6, 7, 11, 29, 115, 116, 121, 127)


def parse(log: str) -> dict | None:
    """The last DUMP block: {field, battle, vars, pieces, grid, mv, at, page, cur, cmds, sel, state,
    step, side}."""
    blocks = {}
    for ln in log.splitlines():
        m = re.match(r"DUMP field=(\d+) vbl=\d+ (\S+): (.*)$", ln)
        if m:
            d = m.group(3).strip()
            blocks.setdefault(int(m.group(1)), []).append(None if d == "NULL" else bytes.fromhex(d.replace(" ", "")))
    if not blocks:
        return None
    f = max(blocks)
    bl = blocks[f] + [None] * 14
    vv = bl[5]
    m = {"field": f, "battle": False,
         "vars": dict(zip(VAR_IDS, (struct.unpack("<128h", vv)[i] for i in VAR_IDS))) if vv else None}
    pcs, board, pages, tail, head, _, cs = bl[:7]
    if pcs is None or board is None or tail is None or cs is None or head is None:
        return m
    base = struct.unpack_from("<I", head, 0)[0]   # unused; the pieces are located by grid pointer arithmetic
    m["battle"] = True
    pieces = []
    for side in range(2):
        for j in range(5):
            p = pcs[side * SIDE + j * PIECE:side * SIDE + (j + 1) * PIECE]
            pieces.append({"side": side, "j": j, "hp": struct.unpack_from("<h", p, 0x1A)[0],
                           "max": struct.unpack_from("<h", p, 0x1E)[0], "inplay": bool(p[3] >> 3 & 1),
                           "king": bool(p[3] >> 2 & 1)})
    grid = struct.unpack_from("<35I", board, 0)
    nz = [g for g in grid if g]
    # piece (side, j) lives at P0 + side * 0x994 + j * 0x1E8; P0 = the smallest grid pointer minus
    # its own offset, found as the value that maps every grid pointer onto a valid (side, j)
    cell = {}
    if nz:
        for cand in nz:
            for side in range(2):
                for j in range(5):
                    p0 = cand - side * SIDE - j * PIECE
                    ok = all(0 <= (g - p0) < 2 * SIDE and ((g - p0) % SIDE) % PIECE == 0 and
                             ((g - p0) % SIDE) // PIECE < 5 for g in nz)
                    if ok:
                        break
                if ok:
                    break
            if ok:
                break
        for i, g in enumerate(grid):
            if g:
                k = (g - p0) // SIDE * 5 + ((g - p0) % SIDE) // PIECE
                cell[k] = (i % 5, i // 5)
    for k, p in enumerate(pieces):
        p["cell"] = cell.get(k)
    m["pieces"] = pieces
    m["mv"] = list(board[0x118:0x118 + 35])
    m["at"] = list(board[0x13B:0x13B + 35])
    pg = {}
    for i in range(len(pages) // 0x20 if pages else 0):
        k = struct.unpack_from("<h", pages, i * 0x20)[0]
        if k == -1:
            break
        pg[k] = tuple(x if x < 128 else x - 256 for x in pages[i * 0x20 + 8:i * 0x20 + 16])
    m["pages"] = pg
    pbase = struct.unpack_from("<I", cs, 8)[0]
    curp = next((c for c in reversed(struct.unpack_from("<8I", cs, 0xC)) if c), 0)
    m["page"], m["sel"] = None, None
    if curp and pages and 0 <= (curp - pbase) // 0x20 < len(pages) // 0x20:
        i = (curp - pbase) // 0x20
        m["page"] = struct.unpack_from("<h", pages, i * 0x20)[0]
        m["sel"] = pages[i * 0x20 + 9]
        m["cur"] = (pg[m["page"]][0] + pg[m["page"]][2], pg[m["page"]][1] + pg[m["page"]][3])
    m["cmds"] = [nd[8] for nd in bl[7:14] if nd is not None]

    def top(a, k):
        for i in range(7, -1, -1):
            if a[k * 8 + i] != 0xFF:
                return a[k * 8 + i]
        return -1
    m["state"] = [top(tail[0x1C:0x7C], k) for k in range(3)]
    m["step"] = [top(tail[0x7C:0xDC], k) for k in range(3)]
    m["side"] = tail[0x5EF1 - 0x5DB8]
    return m


def inv_spec(exe: Path) -> str:
    """Live inventory + GameRec + story vars (GameData D_004B8B30: +0x10 StateBlock, vars at +0x128;
    +0x18 party: +0x168 item pool {+0x08 base, +0x10 stride, +0x14 count, +0x20 used bitmap},
    +0x174 GameRec, 0x33C0 bytes)."""
    r = map_rvas(exe, {"D_004B8B30"})
    pa = r["D_004B8B30"] + 0x18
    return ",".join([f"p0x{pa:X}/0x168+0:0x24", f"p0x{pa:X}/0x168/0x20+0:0x80",
                     f"p0x{pa:X}/0x168/0x8+0:0x8000", f"p0x{pa:X}/0x174+0:0x33C0",
                     f"p0x{r['D_004B8B30'] + 0x10:X}+0x128:0x100"])


def inv_parse(log: str, field: int):
    """({item id: count}, GameRec bytes, vars) from the DUMP block of inv_spec at `field`.
    Item object: +0xA bit1 removed, +0xC s16 id, kind-1 stacks +0x14 count."""
    bl = []
    for ln in log.splitlines():
        m = re.match(r"DUMP field=(\d+) vbl=\d+ (\S+): (.*)$", ln)
        if m and int(m.group(1)) == field:
            d = m.group(3).strip()
            bl.append(None if d == "NULL" else bytes.fromhex(d.replace(" ", "")))
    if len(bl) < 5 or None in bl:
        return None, None, None
    hdr, bm, elems, grec, vv = bl
    stride, count = struct.unpack_from("<II", hdr, 0x10)
    inv = {}
    for i in range(count):
        if not (bm[i // 8] >> (i % 8)) & 1 or (i + 1) * stride > len(elems):
            continue
        e = elems[i * stride:(i + 1) * stride]
        if e[0xA] & 2:
            continue
        iid = struct.unpack_from("<h", e, 0xC)[0]
        c = struct.unpack_from("<i", e, 0x14)[0] if stride >= 0x18 else 1
        inv[iid] = inv.get(iid, 0) + (c if 1 <= c <= 999 else 1)
    vars_ = dict(zip(VAR_IDS, (struct.unpack("<128h", vv)[i] for i in VAR_IDS)))
    return inv, grec, vars_


def inv_probe(exe: Path, state: Path, out: Path):
    """inv_parse at a state (a 2-field run)."""
    f0 = fxlib.peek(state)["field"]
    out.mkdir(parents=True, exist_ok=True)
    (out / "input.txt").write_text("#!stick 1 0" + chr(10), encoding="utf-8")
    (out / "saves").mkdir(exist_ok=True)
    cmd = [str(exe), "--headless", "--fields", str(f0 + 2), "--saves", str(out / "saves"), "--input",
           str(out / "input.txt"), "--load-state", str(Path(state).resolve())]
    rc, log = fac.run_game(cmd, fxlib.game_env({"RG_SS": "1", "RG_STATUS_EVERY": "2", "RG_STATUS_DUMP": inv_spec(exe)}))
    (out / "log.txt").write_text(" ".join(cmd) + chr(10) + log, encoding="utf-8")
    inv, grec, _ = inv_parse(log, f0 + 2)
    return inv, grec


def gamerec_check(card: str, live: bytes) -> dict:
    """The card's GameRec (chunk 12, written by saveedit.py) against the live table after the game
    loaded it: equal except the Rearing Cage records' insect pointers (+0xC x 5, re-resolved by
    InsectRecSlotsResolve_3cfbd0) and the insects' satiety timers (+0x30 f32, ticking in the field)."""
    import saveedit
    s = saveedit.Save(fxlib.CARDS / card)
    g = s.gamerec()
    want = bytearray(s.b[g:g + saveedit.GAMEREC_SIZE])
    got = bytearray(live[:saveedit.GAMEREC_SIZE])
    ptrs = 0
    for k in range(3):
        r = saveedit.GAMEREC_REAR + 0x84C * k
        if want[r] & 1:
            ptrs += sum(1 for i in range(5) if struct.unpack_from("<I", got, r + 0xC + 4 * i)[0])
        want[r + 0xC:r + 0x20] = got[r + 0xC:r + 0x20] = bytes(0x14)
    timers = 0
    for k in range(15):   # +0x30 f32 satiety timer: ticks in the field (InsectItemTickSatiety_3d1110)
        r = saveedit.GAMEREC_INSECT + 0x34 * k
        if want[r] & 1 and want[r + 0x30:r + 0x34] != got[r + 0x30:r + 0x34]:
            timers += 1
        want[r + 0x30:r + 0x34] = got[r + 0x30:r + 0x34] = bytes(4)
    diff = [i for i in range(len(want)) if want[i] != got[i]]
    return {"equal_except_runtime": not diff, "diff_bytes": len(diff), "first_diff": diff[:8],
            "resolved_insect_pointers": ptrs, "satiety_timers_ticking": timers}


def board_text(m) -> str:
    rows = [["." for _ in range(5)] for _ in range(7)]
    for p in m.get("pieces", []):
        if p["cell"] and p["inplay"]:
            x, y = p["cell"]
            rows[y][x] = ("K" if p["king"] else "abcde"[p["j"]]) if p["side"] == 0 else ("Q" if p["king"] else "vwxyz"[p["j"]])
    return "/".join("".join(r) for r in rows)


# ---------------------------------------------------------------- runs
class Driver:
    def __init__(self, exe: Path, card: str, out: Path):
        self.exe, self.card, self.out = exe, card, out
        self.spec = dump_spec(exe)
        self.route: list[str] = []
        self.k = 0
        self.dec = open(out / "decisions.tsv", "w", encoding="utf-8")
        self.dec.write("n\tfield\tside\tstate\tstep\tpage\tcmds\tboard\thp own\thp enemy\taction\n")

    def seg(self, state: Path, f0: int, keys, n: int, name: str, shots=(), every=10):
        """Run keys [(rel, BUTTON)] from state at f0 for n fields; (rc, log, new state, model)."""
        self.route += [f"{f0 + r} {f0 + r + 3} {b}" for r, b in keys]
        d = self.out / "segs" / f"{self.k:04d}_{name}"
        self.k += 1
        d.mkdir(parents=True, exist_ok=True)
        inp = d / "input.txt"
        inp.write_text("#!stick 1 0\n" + "\n".join(ln for ln in self.route if int(ln.split()[0]) > f0) + "\n",
                       encoding="utf-8")
        to = f0 + n
        st = d / f"f{to}.rgstate"
        cmd = [str(self.exe), "--headless", "--fields", str(to), "--saves", str(d / "saves"), "--input", str(inp),
               "--load-state", str(Path(state).resolve()), "--save-state", f"{to}:{st}"]
        (d / "saves").mkdir(exist_ok=True)
        for s in shots:
            cmd += ["--shot", f"{f0 + s}:{d / f's{f0 + s:05d}.png'}"]
        import math
        every = math.gcd(to, n) if n < 10 or to % every else every   # a DUMP block at `to`
        env = {"RG_SS": "1", "RG_STATUS_EVERY": str(every), "RG_STATUS_DUMP": self.spec}
        rc, log = fac.run_game(cmd, fxlib.game_env(env))
        (d / "log.txt").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
        return rc, log, (st if st.exists() else None), parse(log), d

    def note(self, m, action):
        own = [p for p in m["pieces"] if p["side"] == 0]
        en = [p for p in m["pieces"] if p["side"] == 1]
        self.dec.write(f"{self.k}\t{m['field']}\t{m['side']}\t{m['state']}\t{m['step']}\t{m['page']}\t{m['cmds']}\t"
                       f"{board_text(m)}\t{[p['hp'] for p in own]}\t{[p['hp'] for p in en]}\t{action}\n")
        self.dec.flush()


def menu_keys(m, want):
    """D-pad presses to bring the command menu's cursor onto command `want`, then CROSS."""
    cmds = m["cmds"]
    i = cmds.index(want)
    n = (i - (m["sel"] or 0)) % len(cmds)
    keys = [(10 + 16 * k, "DOWN") for k in range(n)]
    return keys + [(10 + 16 * n + 10, "CROSS")]


def cursor_keys(cur, target, t0=10):
    (x, y), (tx, ty) = cur, target
    keys, t = [], t0
    for _ in range(abs(tx - x)):
        keys.append((t, "RIGHT" if tx > x else "LEFT"))
        t += 16
    for _ in range(abs(ty - y)):
        keys.append((t, "DOWN" if ty > y else "UP"))
        t += 16
    return keys + [(t + 10, "CROSS")]


def cheb(a, b):
    return max(abs(a[0] - b[0]), abs(a[1] - b[1]))


def pick_target(m):
    """An attackable enemy cell (attack marks bit 0): the king first, then the lowest HP."""
    best = None
    for p in m["pieces"]:
        if p["side"] == 1 and p["inplay"] and p["cell"]:
            x, y = p["cell"]
            if m["at"][y * 5 + x] & 1:
                key = (0 if p["king"] else 1, p["hp"])
                if best is None or key < best[0]:
                    best = (key, (x, y))
    return best[1] if best else None


def pick_move(m, me):
    """The reachable cell (move marks bit 1) nearest the enemy king (then any enemy)."""
    en = [p for p in m["pieces"] if p["side"] == 1 and p["inplay"] and p["cell"]]
    if not en:
        return None
    king = next((p for p in en if p["king"]), en[0])
    best = None
    for i in range(35):
        if m["mv"][i] & 2:
            c = (i % 5, i // 5)
            key = (cheb(c, king["cell"]), min(cheb(c, p["cell"]) for p in en), abs(c[0] - 2))
            if best is None or key < best[0]:
                best = (key, c)
    if best is None:
        return None
    here = min(cheb(me["cell"], king["cell"]), 99)
    return best[1] if best[0][0] <= here else best[1]


def cmd_run(a) -> int:
    exe = fxlib.exe_path(a.exe)
    card = a.card
    out = Path(a.out) if a.out else fxlib.fixture_dir(exe) / "insectstory" / card
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    if not (fxlib.CARDS / card).is_dir():
        import subprocess
        subprocess.run([sys.executable, str(HERE / "saveedit.py"), "make", card], check=True)
    t0 = time.time()
    res = {"exe_id": fxlib.exe_id(exe), "card": card}
    tsv = open(out / "phases.tsv", "w", encoding="utf-8")
    tsv.write("phase\tfield\tnote\n")

    def phase(name, f, note=""):
        tsv.write(f"{name}\t{f}\t{note}\n")
        tsv.flush()
        print(f"  {name:8s} {f:6d}  {note}", flush=True)

    if a.battle_state:   # debugging the battle policy: start at a team-phase end state (no boot route)
        drv = Driver(exe, card, out)
        state, boot, ctl = Path(a.battle_state), [], 0
        f = fxlib.peek(state)["field"]
        rc, log, state, m, d = drv.seg(state, f, [], 2, "probe")
        f += 2
        res["vars_before"] = m and m["vars"]
        return battle(a, exe, out, res, drv, boot, state, f, m, ctl, t0, tsv, phase)
    # boot (bootcheck pass 1 finds the control field; the boot route is LOAD + the recap presses before it)
    rc, log, st = bootcheck.run_status(card, bootcheck.lib_script(None), exe, 4700, 10, [], {}, card + "_story1", None)
    ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v == (3, "6/100")), None)
    if ctl is None:
        res["verdict"] = f"no field control (exit {rc})"
        (out / "result.json").write_text(json.dumps(res, indent=1))
        print(f"insectstory: {res['verdict']}")
        return 1
    boot = [f"{f} {f + 5} {b}" for f, b, c in bootcheck.LOAD] + [f"{f} {f + 3} CROSS" for f in bootcheck.RECAP if f < ctl]
    f = ctl + 20
    s0 = out / f"boot_{f}.rgstate"
    rc, log, _ = bootcheck.run_status(card, "\n".join(boot) + "\n", exe, f + 2, 10, ["--save-state", f"{f}:{s0}"],
                                      {"RG_SS": "1"}, card + "_story2", None)
    if not s0.exists():
        raise SystemExit(f"insectstory: boot state not written (exit {rc})")
    phase("boot", f, f"control {ctl}")
    inv0, grec0 = inv_probe(exe, s0, out / "inv_before")
    res["inventory_before"] = inv0
    if grec0 is not None:
        res["gamerec_live_vs_card"] = gamerec_check(card, grec0)
        phase("gamerec", f, str(res["gamerec_live_vs_card"]))
    drv = Driver(exe, card, out)
    state = s0
    rc, log, state, m, d = drv.seg(state, f, TALK, TALK_LEN, "talk", shots=(TALK_LEN,))
    f += TALK_LEN
    rows = fac.status_rows(log)
    if not state or not any(r[1] == 5 for r in rows):
        res["verdict"] = f"talk: no INSECT overlay (last {rows[-1] if rows else '-'})"
        return finish(out, res, drv, boot, t0, tsv)
    phase("talk", f, f"INSECT from {next(r[0] for r in rows if r[1] == 5)}; vars {m and m['vars']}")
    res["vars_before"] = m and m["vars"]
    rc, log, state, m, d = drv.seg(state, f, TEAM, TEAM_LEN, "team", shots=(TEAM_LEN,))
    f += TEAM_LEN
    phase("team", f, f"board {board_text(m) if m and m['battle'] else '-'}")
    return battle(a, exe, out, res, drv, boot, state, f, m, ctl, t0, tsv, phase)


def battle(a, exe, out, res, drv, boot, state, f, m, ctl, t0, tsv, phase):
    # battle loop
    turns, idle, verdict, seen_kings = 0, 0, None, False
    acted = set()
    last_side = None
    while verdict is None:
        if f - ctl > a.max_fields:
            verdict = "timeout"
            break
        if not m or not m["battle"]:
            break
        if m["side"] != last_side:
            if m["side"] == 0:
                turns += 1
                acted = set()
            last_side = m["side"]
        own = [p for p in m["pieces"] if p["side"] == 0 and p["inplay"]]
        en = [p for p in m["pieces"] if p["side"] == 1 and p["inplay"]]
        kings = any(p["king"] for p in en) and any(p["king"] for p in own)
        seen_kings = seen_kings or kings
        if seen_kings and (not en or not kings):
            keys, n, act = [(20, "CROSS")], 120, "battle decided: CROSS (Insector Report, results)"
        elif m["side"] != 0:
            keys, n, act = [], 180, "enemy turn: wait"
        elif m["page"] == 2 and m["step"][0] == 0x1C:
            # cursor pick: the next own piece that has not acted (non-king first; the king only attacks)
            cand = [p for p in own if p["j"] not in acted and p["cell"] and not p["king"]]
            king = next((p for p in own if p["king"]), None)
            if king and king["j"] not in acted and any(cheb(king["cell"], e["cell"]) <= 1 for e in en if e["cell"]):
                cand.append(king)
            if cand:
                me = cand[0]
                drv.cur_piece = me
                keys, n, act = cursor_keys(m["cur"], me["cell"]), 90, f"select {'K' if me['king'] else 'abcde'[me['j']]} at {me['cell']}"
            else:
                any_own = next(p for p in own if p["cell"])
                drv.cur_piece = None
                keys, n, act = cursor_keys(m["cur"], any_own["cell"]), 90, "select for End Turn"
        elif m["page"] == 4 and m["cmds"]:
            me = getattr(drv, "cur_piece", None)
            if me is None:
                keys, n, act = menu_keys(m, CMD_END) + [(160, "CROSS")], 260, "End Turn + Yes"
                acted = set(range(5))
            elif CMD_ATTACK in m["cmds"]:
                keys, n, act = menu_keys(m, CMD_ATTACK), 90, "Attack"
            elif CMD_MOVE in m["cmds"] and not me["king"]:
                keys, n, act = menu_keys(m, CMD_MOVE), 90, "Move"
            else:
                keys, n, act = menu_keys(m, CMD_WAIT if CMD_WAIT in m["cmds"] else CMD_END), 120, "Wait"
                acted.add(me["j"])
                drv.cur_piece = None
        elif m["page"] == 10:
            me = drv.cur_piece
            tgt = pick_move(m, me) if me else None
            if tgt is None:
                keys, n, act = [(10, "CIRCLE")], 90, "no move: back"
                acted.add(me["j"]) if me else None
            else:
                keys, n, act = cursor_keys(m["cur"], tgt), 200, f"move to {tgt}"
        elif m["page"] == 11:
            tgt = pick_target(m)
            me = drv.cur_piece
            if tgt is None:
                keys, n, act = [(10, "CIRCLE")], 90, "no target: back"
            else:
                keys, n, act = cursor_keys(m["cur"], tgt), 400, f"attack {tgt}"
                if me:
                    acted.add(me["j"])
                drv.cur_piece = None
        else:
            idle += 1
            keys, n, act = ([(10, "CROSS")] if idle % 4 == 0 else []), 120, f"wait (page {m['page']} state {m['state']} step {m['step']})"
        if keys or "wait" not in act:
            idle = 0
        drv.note(m, act)
        rc, log, nstate, nm, d = drv.seg(state, f, keys, n, f"t{turns:02d}", shots=(n,))
        f += n
        rows = fac.status_rows(log)
        if "TIMEOUT" in log:
            verdict = "hang"
        elif fxlib.crash_report(log, exe) or rc != 0 or nstate is None:
            verdict, res["crash"] = "crash", fxlib.crash_report(log, exe)
        elif rows and rows[-1][1] != 5:
            phase("battle", f, f"left INSECT: {rows[-1]}")
            state, m = nstate, nm
            break
        state, m = nstate, nm
    res["turns"] = turns
    if verdict is None:
        # after: results, announcer, the warp back.  A press in the field would talk to the
        # receptionist again (she stands in front of the party), so the loop alternates a
        # segment without input and, only when that one did not end in field control (ovl 3,
        # 6/100), one CROSS; it stops at the first quiet segment that ends in field control.
        for i in range(60):
            rc, log, nstate, nm, d = drv.seg(state, f, [], 40, "after", shots=(40,))
            f += 40
            if nstate is None:
                verdict = "crash after the battle"
                break
            state, m = nstate, nm
            rows = fac.status_rows(log)
            if rows and rows[-1][1] == 3 and rows[-1][2] == "6/100":
                phase("field", f, f"field control (STATUS {rows[-1]})")
                break
            rc, log, nstate, nm, d = drv.seg(state, f, [(5, "CROSS")], 40, "after", shots=(40,))
            f += 40
            if nstate is None:
                verdict = "crash after the battle"
                break
            state, m = nstate, nm
        res["vars_after"] = m and m["vars"]
        inv, _ = inv_probe(exe, state, out / "inv_after")
        if inv is not None and res.get("vars_after"):
            item = res["vars_after"].get(115)
            res["reward_item_in_inventory"] = {"item": item, "count": inv.get(item, 0)}
        va, vb = res.get("vars_after") or {}, res.get("vars_before") or {}
        if verdict is None:
            if va.get(115, 0) > 0 and va.get(116, 0) > 0:
                verdict = "won"
            elif va.get(7) == 0 and va.get(5) == vb.get(5):
                verdict = "lost"
            else:
                verdict = f"ended (vars {va})"
        phase("after", f, f"vars {va}")
    res["verdict"] = verdict
    res["field"] = f
    return finish(out, res, drv, boot, t0, tsv)


def finish(out, res, drv, boot, t0, tsv):
    tsv.close()
    res["wall_s"] = round(time.time() - t0)
    (out / "route.txt").write_text("#!stick 1 0\n" + "\n".join(drv.route) + "\n", encoding="utf-8")
    (out / "boot_route.txt").write_text(
        f"# insectstory.py: card boot + route (run_from.py --boot-save {res['card']} --input)\n#!stick 1 0\n"
        + "\n".join(boot + drv.route) + "\n", encoding="utf-8")
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    print(f"insectstory: {res['verdict']} ({res['wall_s']} s); {out / 'result.json'}")
    return 0 if res["verdict"] == "won" else 1


def cmd_replay(a) -> int:
    exe = fxlib.exe_path(a.exe)
    route = Path(a.route)
    out = Path(a.out) if a.out else route.parent / "replay"
    end = (max(int(ln.split()[1]) for ln in route.read_text().splitlines() if ln and ln[0].isdigit()) + 300) // 100 * 100
    r = fac.replay(exe, route, out, a.card, [end - 100], end, every=end,
                   env_extra={"RG_STATUS_DUMP": inv_spec(exe)})
    inv, _, va = inv_parse((out / "log.txt").read_text(encoding="utf-8", errors="replace"), end)
    r["vars_end"] = va
    if va:
        r["reward"] = {"item": va.get(115), "count": va.get(116), "in_inventory": (inv or {}).get(va.get(115), 0)}
    (out / "result.json").write_text(json.dumps(r, indent=1), encoding="utf-8")
    print(f"insectstory replay: rc {r['rc']} run_hash {r['run_hash']} last {r['status'][-1] if r['status'] else '-'}; "
          f"vars {va}; reward {r.get('reward')}")
    return 0 if r["rc"] == 0 else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    r = sp.add_parser("run")
    r.add_argument("--exe")
    r.add_argument("--card", default=CARD)
    r.add_argument("--out")
    r.add_argument("--max-fields", type=int, default=60000)
    r.add_argument("--battle-state", help="debug: start the battle loop at this team-phase state (no boot route)")
    r.set_defaults(fn=cmd_run)
    p = sp.add_parser("replay")
    p.add_argument("route")
    p.add_argument("--exe")
    p.add_argument("--card", default=CARD)
    p.add_argument("--out")
    p.set_defaults(fn=cmd_replay)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
