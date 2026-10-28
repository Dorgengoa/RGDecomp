#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Auto-battle: fight a random encounter of a library card to the end, closed loop
(docs/TEST-FIXTURES.md "Auto-battle").

    python tools/fixtures/autobattle.py prep  CARD [--exe EXE]            # battle state
    python tools/fixtures/autobattle.py fight CARD|STATE [--exe EXE] [--out D] [--seg 40]
                                        [--max-fields 8000] [--shots] [--attack CROSS] ..
    python tools/fixtures/autobattle.py probe STATE [--exe EXE]           # one reading

prep: the bootcheck.py card-library script (pass 1 finds field control C, pass 2 the
first battle of the box walk), then a third run of the same script with RG_SS=1 writes
out/fixtures/<exe-id>/fight/CARD_battle.rgstate at the first fight-phase field (game mode
7/201) + 4 and CARD_battle.json (fields, script).

fight: from that state, one rg-game segment at a time (play.py rule: new input lines start
after the state's field); each segment ends with a memory probe (parse_probe: party HP from
the party records, live enemies = action-manager charas with id >= 128 and their HP records,
the leader position, the camera) and a screenshot, and the next segment is chosen:
  - leader HP below --heal x max: open the battle menu (TRIANGLE) and walk its cursor to
    Items closed loop (menu_row() reads the highlighted row from the screenshot: the cursor
    wraps, remembers its row and skips disabled rows), first item (Heal Potion), on the
    leader, CIRCLE out; at most --max-heals, given up when Items is disabled;
  - leader down ("Jaster is down and cannot fight..."; the game keeps the menu open): cursor
    to Switch Characters, RIGHT to the next member's page (downed members' pages show no
    bar: page on), CROSS = that member leads;
  - otherwise run at the nearest live enemy (camera-relative stick, navprobe.stick_for)
    while farther than --reach, then --attack (CROSS = sword; retail's tutorial: X sword,
    SQUARE gun, CIRCLE jump) every --tap fields, CIRCLE first for targets --high above;
    L1 every third segment (accept the allies' suggestion); an enemy that loses no HP for
    8 segments is skipped for a while.
Verdicts: won (7/500, 7/504, 7/4000), lost (7/7xx), escaped (7/600), ended (mode left 7),
timeout (--max-fields), stuck (nothing changed for 12 segments), crash, hang.
Output D (default out/fixtures/<exe-id>/fight/CARD/): fight.tsv (per segment: field, mode,
leader pos, HP, party, enemies alive, enemy HP, decision), route.txt (the whole input:
`play.py --from <state> --input route.txt` replays the fight in one run), s*.png (--shots;
montage.py D), result.json.  bootcheck.py --fight runs prep + fight per library card.

--wide (soak2): abilities (menu row 0, a seeded list row), items, voluntary leader switches, the
gun, ability cut-ins (game mode 10/*) played through, the in-battle item screen (17/*) backed out
of; result fields ability_tries / cutins / items / lead_switch / gun / other_modes.

One rg-game at a time (machine limits); a segment costs ~2-3 s.
"""
from __future__ import annotations

import argparse
import json
import shutil
import math
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "trace"))
import fxlib  # noqa: E402
import bootcheck  # noqa: E402

FIGHT_PHASE = "7/201"
WON = {"7/500", "7/504", "7/4000"}
CUTIN = {"10"}
SUBMENU = {"17"}  # the battle menu's item screen (main-menu game mode 17 inside a battle)    # ability cut-in game mode (10/2 seen: Flash Sword, 2026-10-25 soak2)
MENU = "7/2000"   # battle command menu open (BtlChgMenuOpen_204b50; the action is paused)


def fight_dir(exe: Path) -> Path:
    d = fxlib.fixture_dir(exe) / "fight"
    d.mkdir(parents=True, exist_ok=True)
    return d


def prep(card: str, exe: Path, keep: Path | None = None, quiet=False) -> dict:
    """Make the battle state of a library card (see module doc).  Returns the json info
    ({'state': None, 'why': ..} when the box walk meets no battle)."""
    fd = fight_dir(exe)
    info_p = fd / f"{card}_battle.json"
    if info_p.exists():
        info = json.loads(info_p.read_text())
        if info.get("state") is None or Path(info["state"]).exists():
            return info
    t0 = time.time()
    rc, log, st = bootcheck.run_status(card, bootcheck.lib_script(None), exe, 4700, 10, [], {},
                                       card + "_fpass1", keep)
    ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v == (3, "6/100")), None)
    info = {"card": card, "exe_id": fxlib.exe_id(exe), "control": ctl, "state": None}
    if ctl is None:
        info["why"] = f"no field control (exit {rc})"
        info_p.write_text(json.dumps(info, indent=1))
        return info
    script = bootcheck.lib_script(ctl)
    end = ctl + 3500
    rc, log, st = bootcheck.run_status(card, script, exe, end, 10, [], {}, card + "_fpass2", keep)
    enc = next((k for k, v in sorted(st.items()) if k >= ctl + 340 and v[0] == 3 and v[1].startswith("7/")), None)
    fight = next((k for k, v in sorted(st.items()) if enc and k >= enc and v[1] == FIGHT_PHASE), None)
    crash = fxlib.crash_report(log, exe)
    info.update(encounter=enc, fight=fight, crash=crash)
    if fight is None:
        info["why"] = "no battle in the box walk" if enc is None else f"battle at {enc} never reached {FIGHT_PHASE}"
        info_p.write_text(json.dumps(info, indent=1))
        return info
    at = fight + 4
    stp = fd / f"{card}_battle.rgstate"
    rc, log, st = bootcheck.run_status(card, script, exe, at + 2, 10, ["--save-state", f"{at}:{stp}"],
                                       {"RG_SS": "1"}, card + "_fpass3", keep)
    if not stp.exists():
        info["why"] = f"state not written (exit {rc})"
    else:
        info["state"] = str(stp)
        info["field"] = at
    info["prep_s"] = round(time.time() - t0)
    info_p.write_text(json.dumps(info, indent=1))
    if not quiet:
        print(f"prep {card}: control {ctl}, encounter {enc}, fight {fight}, state {info['state']}")
    return info


# ---- memory probe (RG_STATUS_DUMP pointer chains; RVAs from the exe's map) ----
# CharaSys D_004837C0: +0x14 -> party record manager (+0x8 = pool), +0x18 -> party object,
# +0x1C -> enemy object manager (+0x10 = pool).  Pools (PoolGetUsedElem_36acb0): +0x08 base,
# +0x10 stride, +0x14 count, +0x20 used bitmap.  Records (party 0x4C8, enemies 0x410 bytes):
# +0xC s32 chara id, +0x14 HP, +0x1C max HP.  Party object: +0x18C s16 active count, +0x18E
# leader id, +0x190 active[3].  Action manager D_004B8680: +0x20 DList head (node +4 next, the
# Chara at node +0x10 sorted by id: party 0..9, enemies 128..): Chara +0x64 yaw, +0x70 pos,
# +0x424 s16 id.  Cameras: Camera0..5 at PS2 0x4B5660 + k x 0x2F0 (+0x50 look, +0x60 eye).
PARTY_STRIDE, ENEMY_STRIDE = 0x4C8, 0x410
NODES = 12


def _sym_rvas(exe: Path) -> dict:
    mp = Path(exe).with_suffix(".map")
    want = {"D_004837C0", "D_004B8680"}
    out = {}
    for line in open(mp, encoding="latin-1"):
        m = re.match(r"\s*0003:[0-9a-f]+\s+_?(D_004837C0|D_004B8680)\s+([0-9a-f]{16})\s", line)
        if m and m.group(1) in want:
            out[m.group(1)] = int(m.group(2), 16) - 0x400000
    return out


def dump_spec(exe: Path) -> str:
    r = _sym_rvas(exe)
    cs, am = r["D_004837C0"], r["D_004B8680"] + 0x20
    items = [f"p0x{cs:X}/0x18+0x18C:0x10", f"p0x{cs:X}/0x14/0x8/0x8+0:0x{PARTY_STRIDE * 10:X}",
             f"p0x{cs:X}/0x1C/0x10/0x8+0:0x{ENEMY_STRIDE * 15:X}", "0x4B5660:0x11A0"]
    items += [f"p0x{am:X}" + "/4" * k + "+0x60:0x3D8" for k in range(NODES)]
    s = ",".join(items)
    assert len(s) < 511, len(s)
    return s


def parse_probe(log: str, field: int | None = None) -> dict:
    """The last dump block of a log (or the one at `field`): {field, mode, leader, party:
    [(id, hp, max)], enemies: [{id, hp, max, pos}], cam: (eye, look) or None}."""
    lines = log.splitlines()
    blocks = {}
    for ln in lines:
        m = re.match(r"DUMP field=(\d+) ", ln)
        if m:
            blocks.setdefault(int(m.group(1)), []).append(ln)
    modes = {}
    for ln in lines:
        m = re.match(r"STATUS field=(\d+) .*?gamemode=(\S+)", ln)
        if m:
            modes[int(m.group(1))] = m.group(2)
    res = {"field": None, "mode": modes[max(modes)] if modes else None, "leader": None, "party": [],
           "enemies": [], "cam": None, "charas": {}}
    if not blocks:
        return res
    f = field if field in blocks else max(blocks)
    res["field"], res["mode"] = f, modes.get(f, res["mode"])
    bl = blocks[f]
    def data(ln):
        w = ln.split()
        if len(w) < 5 or w[3] == "NULL" or w[-1] == "NULL":
            return None
        return bytes.fromhex("".join(w[4:]))
    if len(bl) < 4:
        return res
    pb, prec, erec, camb = (data(x) for x in bl[:4])
    lead_id = struct.unpack_from("<h", pb, 2)[0] if pb else -1
    active = [i for i in struct.unpack_from("<3h", pb, 4)] if pb else []
    recs = {}
    for buf, stride, n in ((prec, PARTY_STRIDE, 10), (erec, ENEMY_STRIDE, 15)):
        if not buf:
            continue
        for k in range(n):
            o = k * stride
            if o + 0x20 > len(buf):
                break
            cid, hp, mx = struct.unpack_from("<i", buf, o + 0xC)[0], *struct.unpack_from("<i4xi", buf, o + 0x14)
            recs.setdefault(cid, (hp, mx))
    charas = {}
    for ln in bl[4:]:
        b = data(ln)
        if not b or len(b) < 0x3D8:
            continue
        cid = struct.unpack_from("<h", b, 0x3D4)[0]
        charas[cid] = {"pos": struct.unpack_from("<3f", b, 0x20), "yaw": struct.unpack_from("<f", b, 0x14)[0]}
    res["charas"] = charas
    res["party"] = [(i, *recs.get(i, (None, None))) for i in active if i >= 0]
    if lead_id in charas:
        res["leader"] = {"id": lead_id, "pos": charas[lead_id]["pos"], "hp": recs.get(lead_id, (None, None))}
    for cid, c in sorted(charas.items()):
        if cid >= 128 and cid in recs:
            hp, mx = recs[cid]
            res["enemies"].append({"id": cid, "hp": hp, "max": mx, "pos": c["pos"]})
    if camb and res["leader"]:
        lp = res["leader"]["pos"]
        cams = []
        for k in range(6):
            fl = struct.unpack_from("<12f", camb, k * 0x2F0 + 0x50)
            look, eye = fl[0:3], fl[4:7]
            if math.dist(look, eye) > 1:
                cams.append((math.dist(eye, lp), eye, look))
        if cams:
            _, eye, look = min(cams)
            res["cam"] = (eye, look)
    return res


def run_seg(exe: Path, state: Path, inp_text: str, to: int, out: Path, save: int | None,
            shots=(), every: int = 0) -> tuple[int, str, Path | None]:
    """One rg-game segment from `state` to field `to` (dump at `to`); (rc, log, state)."""
    out.mkdir(parents=True, exist_ok=True)
    inp = out / "input.txt"
    inp.write_text(inp_text, encoding="utf-8")
    sv = out / "saves"
    sv.mkdir(exist_ok=True)
    f0 = fxlib.peek(state)["field"]
    every = every or math.gcd(to, to - f0)
    cmd = [str(exe), "--headless", "--fields", str(to), "--saves", str(sv), "--input", str(inp),
           "--load-state", str(Path(state).resolve())]
    st = None
    if save:
        st = out / f"f{save}.rgstate"
        cmd += ["--save-state", f"{save}:{st}"]
    for f in shots:
        cmd += ["--shot", f"{f}:{out / f's{f:05d}.png'}"]
    env = {"RG_STATUS_EVERY": str(every), "RG_STATUS_DUMP": dump_spec(exe), "RG_SS": "1"}
    for attempt in range(2):
        try:
            p = subprocess.run(cmd, env=fxlib.game_env(env), capture_output=True, text=True, errors="replace",
                               timeout=240)
            rc, log = p.returncode, p.stdout + p.stderr
            if attempt:
                log += "\nautobattle: the first attempt timed out; this retry finished\n"
            break
        except subprocess.TimeoutExpired as e:
            # a stall of the machine (other lanes' builds, an rg_slots wait) is not a game hang:
            # the segment is deterministic, so run it once more before calling it one (soak
            # 2026-10-25: a 40-field segment timed out once and replayed cleanly)
            rc, log = -9, (e.stdout or b"").decode("utf-8", "replace") if isinstance(e.stdout, bytes) else (e.stdout or "")
            log += "\nautobattle: TIMEOUT (hang?)\n"
    (out / "log.txt").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    return rc, log, (st if st and st.exists() else None)


def probe(state: Path, exe: Path, out: Path) -> dict:
    f0 = fxlib.peek(state)["field"]
    to = f0 + 2
    rc, log, _ = run_seg(exe, state, "#!stick 1 0\n", to, out, None, every=2)
    r = parse_probe(log, to)
    r["rc"] = rc
    return r


def _xz(a, b):
    return math.hypot(b[0] - a[0], b[2] - a[2])


def menu_row(png) -> int | None:
    """Battle-menu cursor row from a 512x448 screenshot: the highlighted row (0 Abilities,
    1 Change Equipment, 2 Items, 3 Switch Characters) is a blue bar across the panel.  Rows
    at y 266-286, 290-310, 314-334, 342-358 (measured on the port's shots); the panel's x
    depends on the leader's party slot, so 120-pixel windows are scanned and a row counts
    when its bar is blue over the whole window (20th percentile of the column scores, so a
    blue enemy behind the panel does not count)."""
    if not png or not Path(png).exists():
        return None
    from PIL import Image
    im = Image.open(png).convert("RGB")
    if im.size != (512, 448):
        im = im.resize((512, 448))
    px = im.load()
    rows = ((266, 286), (290, 310), (314, 334), (342, 358))
    col = {}
    for k, (y0, y1) in enumerate(rows):
        for x in range(0, 512, 4):
            col[k, x] = sum(px[x, y][2] - px[x, y][0] for y in range(y0, y1 + 1, 4)) / len(range(y0, y1 + 1, 4))
    best, row = 30.0, None
    for x0 in range(0, 512 - 120, 8):
        for k in range(4):
            v = sorted(col[k, x] for x in range(x0, x0 + 120, 4))
            q = v[len(v) // 5]
            if q > best:
                best, row = q, k
    return row


def plan(r: dict, f0: int, seg: int, k: int, mem: dict, cfg) -> tuple[list[str], str, int]:
    """Input lines for fields f0+1 .. f0+seg from probe result r; (lines, note)."""
    import navprobe as nav
    L = []
    lead = r["leader"]
    alive = [e for e in r["enemies"] if e["hp"] and e["hp"] > 0]
    hp, mx = (lead["hp"] if lead else (None, None))
    low = bool(hp and mx and hp < cfg.heal * mx)
    note = ""
    menu = r["mode"] == MENU
    if menu and (mem.get("goal") or hp == 0):
        # closed loop on the battle menu's cursor, read from the last segment's screenshot
        # (menu_row(); the cursor wraps and remembers its row, and presses while the menu
        # is still opening are lost, so open-loop counts drift): one UP/DOWN per short
        # segment until the goal row, then the confirm presses.
        goal = mem.get("goal") or "switch"
        mem["goal"] = goal
        want = {"heal": 2, "switch": 3, "ability": 0, "item": 2, "lead": 3}[goal]
        row = menu_row(mem.get("shot"))
        mem["menu_steps"] = mem.get("menu_steps", 0) + 1
        if mem["menu_steps"] > 6:           # give up and back out: the cursor skips a disabled
            # row (Items greys out when nothing usable is left: the cursor then jumps 1 <-> 3)
            mem.pop("goal", None)
            mem["menu_steps"] = 0
            mem["menu_fail"] = mem.get("menu_fail", 0) + 1
        elif row is None and goal in ("switch", "lead"):
            # a downed member's page shows no highlight bar: page on to the next member
            return [f"{f0 + 4} {f0 + 6} RIGHT"], "switch: no cursor bar (downed member's page), next page", 30
        elif row is None:
            return [], f"{goal}: menu cursor not seen, wait", 24
        elif row != want:
            btn = "DOWN" if (want - row) % 4 <= 2 else "UP"
            return [f"{f0 + 4} {f0 + 6} {btn}"], f"{goal}: cursor row {row} -> {want}", 24
        elif goal == "heal":
            # Items -> first item (Heal Potion in the start inventories) -> on whom? (the
            # leader is the default) -> back out of the item grid and the menu
            mem.pop("goal")
            mem["menu_steps"] = 0
            mem["heals"] = mem.get("heals", 0) + 1
            return [f"{f0 + 4} {f0 + 6} CROSS  # Items", f"{f0 + 34} {f0 + 36} CROSS  # first item",
                    f"{f0 + 64} {f0 + 66} CROSS  # on the leader"] +                 [f"{f0 + 100 + 20 * i} {f0 + 102 + 20 * i} CIRCLE  # close" for i in range(3)],                 f"heal {mem['heals']}: use item (hp {hp}/{mx})", 170
        elif goal == "ability":
            # Abilities -> the leader's slotted list (Flash Sword, Fated Passion, ..; the
            # combination attacks are rows of the same list) -> row k -> use -> CROSS again for
            # a target prompt (abilities on an ally); refused rows (AP short, partner absent)
            # leave the list open: the 'close menu' branch backs out next segment
            mem.pop("goal")
            mem["menu_steps"] = 0
            k_ = mem["rng"].randrange(cfg.ability_rows)
            mem["ability_tries"] = mem.get("ability_tries", 0) + 1
            mem["ability_pick"] = k_
            L_ = [f"{f0 + 4} {f0 + 6} CROSS  # Abilities"]
            f_ = f0 + 40
            for _ in range(k_):
                L_.append(f"{f_} {f_ + 2} DOWN")
                f_ += 16
            L_ += [f"{f_ + 10} {f_ + 12} CROSS  # use ability row {k_}",
                   f"{f_ + 50} {f_ + 52} CROSS  # target / confirm"]
            return L_, f"ability: row {k_} (try {mem['ability_tries']})", f_ + 80 - f0
        elif goal == "item":
            # Items -> item k of the battle item list -> on the leader -> back out
            mem.pop("goal")
            mem["menu_steps"] = 0
            k_ = mem["rng"].randrange(4)
            mem["items"] = mem.get("items", 0) + 1
            L_ = [f"{f0 + 4} {f0 + 6} CROSS  # Items"]
            f_ = f0 + 34
            for _ in range(k_):
                L_.append(f"{f_} {f_ + 2} DOWN")
                f_ += 16
            L_ += [f"{f_ + 4} {f_ + 6} CROSS  # item row {k_}", f"{f_ + 34} {f_ + 36} CROSS  # on the leader"]
            L_ += [f"{f_ + 70 + 20 * i} {f_ + 72 + 20 * i} CIRCLE  # close" for i in range(3)]
            return L_, f"item {mem['items']}: row {k_}", f_ + 140 - f0
        elif goal == "lead":
            # voluntary leader switch: the next member's page, Switch Characters
            mem.pop("goal")
            mem["menu_steps"] = 0
            mem["lead_switch"] = mem.get("lead_switch", 0) + 1
            return [f"{f0 + 4} {f0 + 6} RIGHT  # next member's page",
                    f"{f0 + 44} {f0 + 46} CROSS  # Switch Characters (voluntary)"],                 f"voluntary leader switch {mem['lead_switch']}", 80
        else:
            # "Jaster is down and cannot fight. Switch characters or revive the downed
            mem.pop("goal")
            mem["menu_steps"] = 0
            mem["switch"] = mem.get("switch", 0) + 1
            # character.": the game keeps the menu open (CIRCLE does nothing) and the downed
            # leader's own rows do nothing; RIGHT pages to the next member's menu (the cursor
            # keeps its row) and Switch Characters there makes that member the leader
            # (found with play.py shots, out/route5/m6)
            return [f"{f0 + 4} {f0 + 6} RIGHT  # next member's page",
                    f"{f0 + 44} {f0 + 46} CROSS  # Switch Characters"], f"leader down: switch {mem['switch']}", 80
    ph = r["mode"].split("/")[1] if r["mode"] and r["mode"].startswith("7/") else ""
    if ph.isdigit() and 2000 < int(ph) < 3000:
        # an in-battle prompt (7/2100 seen in the soak, ch01_residential: the action pauses
        # until a button; the stick and L1 do nothing there): CROSS (soak 2026-10-25)
        return [f"{f0 + 4} {f0 + 6} CROSS  # in-battle prompt {r['mode']}"], f"prompt {r['mode']}: CROSS", 30
    if menu:   # left in the menu (a heal that did not go through, or a refusal): back out
        mem["menu_close"] = mem.get("menu_close", 0) + 1
        return [f"{f0 + 4 + 20 * i} {f0 + 6 + 20 * i} CIRCLE  # close the battle menu" for i in range(4)],             "close menu", 90
    if r["mode"] and r["mode"].split("/")[0] in SUBMENU:
        # the battle menu's Items list runs as game mode 17 (17/200 seen, soak2 w_ch10_kuje: the
        # heal's presses left it open): back out to the battle
        return [f"{f0 + 4 + 25 * i} {f0 + 6 + 25 * i} CIRCLE  # leave the item screen" for i in range(4)],             f"item screen {r['mode']}: CIRCLE", 110
    if r["mode"] and not r["mode"].startswith("7/"):
        # an ability's cut-in (game mode 10/*, '(TRIANGLE): Skip') or a Burning Strike: let it
        # play, pressing the face buttons in turn (Burning Strike chips are button prompts)
        m_ = r["mode"].split("/")[0]
        mem.setdefault("modes", {})
        mem["modes"][r["mode"]] = mem["modes"].get(r["mode"], 0) + 1
        if cfg.wide:
            L_ = []
            for i, b in enumerate(("CROSS", "CIRCLE", "SQUARE", "CROSS", "CIRCLE", "SQUARE")):
                L_.append(f"{f0 + 6 + 10 * i} {f0 + 8 + 10 * i} {b}  # burning chip?")
            return L_, f"cut-in {r['mode']}: chips", 70
        return [], f"cut-in {r['mode']}: wait", 40
    if cfg.wide and not low and alive:
        # widened tactics (soak.py --wide): abilities / items / voluntary leader switch on
        # a seeded schedule; the gun on some segments (below)
        roll = mem["rng"].random()
        if roll < cfg.p_ability:
            mem["goal"] = "ability"
            mem["menu_steps"] = 0
            return [f"{f0 + 2} {f0 + 4} TRIANGLE  # ability: battle menu"], "ability: open menu", 50
        if roll < cfg.p_ability + cfg.p_item and mem.get("items", 0) < cfg.max_items:
            mem["goal"] = "item"
            mem["menu_steps"] = 0
            return [f"{f0 + 2} {f0 + 4} TRIANGLE  # item: battle menu"], "item: open menu", 50
        if roll < cfg.p_ability + cfg.p_item + cfg.p_lead and len(r["party"]) > 1:
            mem["goal"] = "lead"
            mem["menu_steps"] = 0
            return [f"{f0 + 2} {f0 + 4} TRIANGLE  # leader switch: battle menu"], "lead: open menu", 50
    if low and mem.get("heals", 0) < cfg.max_heals and mem.get("menu_fail", 0) < 1:
        mem["goal"] = "heal"
        mem["menu_steps"] = 0
        return [f"{f0 + 2} {f0 + 4} TRIANGLE  # heal: battle menu"], f"heal: open menu (hp {hp}/{mx})", 50
    if k % 3 == 0 or low:   # accept the allies' suggestion (often a heal)
        L.append(f"{f0 + 2} {f0 + 4} L1  # suggestion{' (low HP)' if low else ''}")
    if lead and alive:
        lp = lead["pos"]
        skip = mem.get("skip", set())
        cand = [e for e in alive if e["id"] not in skip] or alive
        tgt = min(cand, key=lambda e: _xz(lp, e["pos"]))
        d = _xz(lp, tgt["pos"])
        h = nav.heading(tgt["pos"][0] - lp[0], tgt["pos"][2] - lp[2])
        lx, ly = nav.stick_for(h, r["cam"])
        high = tgt["pos"][1] - lp[1] > cfg.high
        note = f"target {tgt['id']} hp {tgt['hp']} d {d:.0f}{' high' if high else ''}"
        if d > cfg.reach:
            # run at it; most of the segment, then attack if it will be close
            run = min(seg, max(4, int((d - cfg.reach * 0.6) / 3.6 * 2)))   # ~3.6 units per game tick (2 fields)
            L.append(f"#!stick {f0 + 1} {f0 + run} {lx} {ly}  # run at {tgt['id']}")
            f = f0 + run + 2
        else:
            L.append(f"#!stick {f0 + 1} {f0 + 2} {lx} {ly}  # face {tgt['id']}")
            f = f0 + 4
        btn = cfg.attack
        if cfg.wide and (k % cfg.gun_every == cfg.gun_every - 1 or d > 4 * cfg.reach and k % 2):
            btn = "SQUARE"      # the gun ('Firing Guns' help sheet: SQUARE)
            mem["gun"] = mem.get("gun", 0) + 1
            note += " gun"
        while f + 3 <= f0 + seg:
            if high:
                L.append(f"{f} {f + 2} CIRCLE  # jump")
                f += 4
            L.append(f"{f} {f + 2} {btn}")
            f += cfg.tap
    else:
        f = f0 + 2
        while f + 3 <= f0 + seg:
            L.append(f"{f} {f + 2} {cfg.attack}")
            f += cfg.tap
        note = "no enemy read" if not alive else "no leader read"
    return L, note, seg


def fight(state: Path, exe: Path, out: Path, cfg) -> dict:
    """The closed loop (module doc).  Returns the result dict (also out/result.json)."""
    out.mkdir(parents=True, exist_ok=True)
    f0 = fxlib.peek(state)["field"]
    start = f0
    route = ["# autobattle.py route from " + str(state), "#!stick 1 0"]
    tsv = open(out / "fight.tsv", "w", encoding="utf-8")
    tsv.write("field\tmode\tleader_x\tleader_z\thp\tmax\tparty\tenemies_alive\tenemy_hp\tnote\n")
    r = probe(state, exe, out / "probe0")
    first = r
    import random
    mem = {"hist": [], "rng": random.Random(f"{cfg.seed}:{start}")}
    verdict, crash, k = None, [], 0
    prev_states = []
    t0 = time.time()
    while verdict is None:
        if f0 - start >= cfg.max_fields:
            verdict = "timeout"
            break
        # (no heal-success check: the party record HP only follows the HUD once the menu is
        # closed, and the leader may be hit again before the next reading)
        lines, note, n = plan(r, f0, cfg.seg, k, mem, cfg)
        to = f0 + n
        segd = out / f"seg{k:03d}"
        text = "\n".join(route + lines) + "\n"
        rc, log, st = run_seg(exe, state, text, to, segd, to, shots=[to], every=n)
        mem["shot"] = segd / f"s{to:05d}.png"
        crash = fxlib.crash_report(log, exe)
        if cfg.shots and (segd / f"s{to:05d}.png").exists():
            shutil.copyfile(segd / f"s{to:05d}.png", out / f"s{to:05d}.png")
        nr = parse_probe(log, to)
        alive = [e for e in nr["enemies"] if e["hp"] and e["hp"] > 0]
        ehp = sum(e["hp"] for e in alive)
        lead = nr["leader"] or {}
        lp = lead.get("pos") or (None, None, None)
        hp, mx = lead.get("hp") or (None, None)
        tsv.write(f"{to}\t{nr['mode']}\t{lp[0] if lp[0] is None else round(lp[0])}\t"
                  f"{lp[2] if lp[2] is None else round(lp[2])}\t{hp}\t{mx}\t"
                  f"{' '.join(f'{i}:{h}/{m}' for i, h, m in nr['party'])}\t{len(alive)}\t{ehp}\t{note}\n")
        tsv.flush()
        print(f"  {to:6d} {nr['mode'] or '-':8s} hp {hp}/{mx} enemies {len(alive)} ({ehp})  {note}", flush=True)
        if "TIMEOUT" in log:
            verdict = "hang"
        elif crash or rc not in (0,):
            verdict = "crash"
        elif st is None or nr["mode"] is None:
            verdict = f"no state (exit {rc})"
        if verdict:
            break
        route += lines
        mode = nr["mode"]
        if mode in WON:
            verdict = "won"
        elif mode.startswith("7/7"):     # 700 (BattleModeUpdate_280220 result 2) / 701
            verdict = "lost"
        elif mode == "7/600":
            verdict = "escaped"
        elif mode.split("/")[0] in SUBMENU and mem.get("last_mode", "").split("/")[0] in ("7",) + tuple(SUBMENU)                 and mem.get("submenu", 0) < 8:
            mem["submenu"] = mem.get("submenu", 0) + 1     # the item screen of the battle menu
        elif mode.split("/")[0] in CUTIN and k - mem.get("cutin_since", k) < 40:
            # an ability cut-in (10/*) is part of the battle: count it, keep going
            if mem.get("last_mode", "").split("/")[0] not in CUTIN:
                mem["cutins"] = mem.get("cutins", 0) + 1
                mem.setdefault("cutin_since", k)
        elif not mode.startswith("7/"):
            verdict = f"ended ({mode})"
        if mode.startswith("7/"):
            mem.pop("cutin_since", None)
        mem["last_mode"] = mode
        sig = (mode, ehp, hp, lp[0])
        mem["same"] = mem.get("same", 0) + 1 if sig == mem.get("sig") else 0
        mem["sig"] = sig
        if verdict is None and mem["same"] >= 12:
            verdict = f"stuck ({mode})"   # nothing changed for 12 segments: menu or input dead end
        # stuck: no enemy HP lost for 8 segments -> skip the current nearest for a while
        mem["hist"].append(ehp)
        if len(mem["hist"]) > 8 and ehp >= mem["hist"][-9] and alive:
            mem["skip"] = {min(alive, key=lambda e: _xz(lp, e["pos"]) if lp[0] is not None else 0)["id"]}
            mem["hist"] = []
        prev_states.append(st)
        while len(prev_states) > 2:
            old = prev_states.pop(0)
            if old != state:
                old.unlink(missing_ok=True)
        if k > 0:
            shutil.rmtree(out / f"seg{k - 1:03d}" / "saves", ignore_errors=True)
        state, f0, r, k = st, to, nr, k + 1
    tsv.close()
    (out / "route.txt").write_text("\n".join(route) + "\n", encoding="utf-8")
    killed = sum(1 for e in first["enemies"] if e["hp"]) - sum(1 for e in r["enemies"] if e["hp"] and e["hp"] > 0)
    res = {"verdict": verdict, "from_field": start, "to_field": f0, "fields": f0 - start, "segments": k,
           "wall_s": round(time.time() - t0), "enemies_start": len(first["enemies"]), "killed": killed,
           "heals": mem.get("heals", 0), "ability_tries": mem.get("ability_tries", 0),
           "cutins": mem.get("cutins", 0), "items": mem.get("items", 0), "lead_switch": mem.get("lead_switch", 0),
           "switch": mem.get("switch", 0), "gun": mem.get("gun", 0), "other_modes": mem.get("modes", {}),
           "party_end": r["party"], "mode_end": r["mode"], "crash": crash,
           "state_end": str(state), "route_lines": route[2:]}   # soak.py chains on from state_end
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    return res


def options(ap=None):
    ap = ap or argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out")
    ap.add_argument("--seg", type=int, default=40, help="fields per segment")
    ap.add_argument("--max-fields", type=int, default=8000)
    ap.add_argument("--reach", type=float, default=45.0, help="attack distance (world units, XZ)")
    ap.add_argument("--high", type=float, default=25.0, help="target this much higher: jump attacks")
    ap.add_argument("--heal", type=float, default=0.4, help="leader HP fraction that counts as low")
    ap.add_argument("--tap", type=int, default=8, help="fields between attack presses")
    ap.add_argument("--attack", default="CROSS", help="attack button: CROSS sword (default), SQUARE gun "
                    "(retail's 'Basic Battle Controls' tutorial: X sword, SQUARE gun, CIRCLE jump)")
    ap.add_argument("--max-heals", type=int, default=8, help="battle-menu potions per fight")
    ap.add_argument("--shots", action="store_true", help="keep one screenshot per segment in OUT")
    ap.add_argument("--wide", action="store_true",
                    help="widened tactics (soak.py --wide): abilities (battle menu row 0, a seeded row of "
                         "the list: actives and combination attacks), items (row k of Items), voluntary leader "
                         "switches, the gun (SQUARE) every --gun-every segment, face-button presses in cut-ins")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--p-ability", type=float, default=0.12, help="--wide: chance per segment to use an ability")
    ap.add_argument("--p-item", type=float, default=0.03)
    ap.add_argument("--p-lead", type=float, default=0.03)
    ap.add_argument("--max-items", type=int, default=4)
    ap.add_argument("--ability-rows", type=int, default=5, help="--wide: rows of the ability list to pick from")
    ap.add_argument("--gun-every", type=int, default=5)
    return ap


def fight_card(card: str, exe: Path, out: Path | None = None, keep: Path | None = None, **kw) -> dict:
    """prep + fight with default options (bootcheck.py --fight); {'verdict': 'no battle', ..}
    when the card's box walk meets none."""
    cfg = options().parse_args([])
    for k, v in kw.items():
        setattr(cfg, k, v)
    info = prep(card, exe, keep, quiet=True)
    if not info.get("state"):
        return {"verdict": "no battle", "why": info.get("why")}
    return fight(Path(info["state"]), exe, out or fight_dir(exe) / card, cfg)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["prep", "fight", "probe"])
    ap.add_argument("what", help="library card name or .rgstate")
    ap.add_argument("--exe")
    options(ap)
    a = ap.parse_args(argv)
    exe = fxlib.exe_path(a.exe)
    if a.cmd == "prep":
        info = prep(a.what, exe)
        print(json.dumps(info, indent=1))
        return 0 if info.get("state") else 1
    if a.what.endswith(".rgstate"):
        state, name = Path(a.what).resolve(), Path(a.what).stem
    else:
        info = prep(a.what, exe)
        if not info.get("state"):
            print(f"autobattle: {a.what}: no battle state ({info.get('why')})")
            return 1
        state, name = Path(info["state"]), a.what
    if a.cmd == "probe":
        r = probe(state, exe, Path(a.out or fight_dir(exe) / "probe"))
        r.pop("charas", None)
        print(json.dumps(r, indent=1))
        return 0
    out = Path(a.out) if a.out else fight_dir(exe) / name
    res = fight(state, exe, out, a)
    print(json.dumps(res, indent=1))
    return 0 if res["verdict"] == "won" else 1


if __name__ == "__main__":
    sys.exit(main())
