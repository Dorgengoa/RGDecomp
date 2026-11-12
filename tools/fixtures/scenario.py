#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Manufacture a starting point from a description: "there's an issue with boss X" -> a memory
card where the party stands at X's battle position at the story point just before it, and a
run that starts that very battle (docs/TEST-FIXTURES.md "Scenarios"; the order of events and
the target list: docs/GAME-PROGRESSION.md, census/progression.tsv from progression.py).

    python tools/fixtures/scenario.py list [QUERY]                 # bosses / fixed battles / areas
    python tools/fixtures/scenario.py card TARGET [--preset story|strong] [--before]
    python tools/fixtures/scenario.py run TARGET --exe EXE [--out D] [--shots] [--state] [--before]
         [--preset ..] [--oracle ORACLE_EXE] [--fields N]
    python tools/fixtures/scenario.py prove --exe EXE [--out D] [--set default|story|post|enemies ..]
         [--resume [--retry-fail]]                                  # proving sets, serial, prove.tsv per target
    python tools/fixtures/scenario.py groups NAME                    # encounter groups holding an enemy
    python tools/fixtures/scenario.py selftest                       # no game run (ctest)

TARGET
  a boss / fixed-battle name or enemy name ('Mud Whooper', 'Jupis', 'Valkog'), 'boss:NAME',
  or its fixed_encount_param id (1005); chapter-14 rematches and ghost-ship EX bosses are
  reached by name too ('Gokilla') or by id; ties go to the earliest story point.
  'enemy:NAME' / 'enemy:GROUP' = a random-encounter enemy: the card standing in the group's
  zone (ZONE_CARDS), box walk, RG_FORCE_ENCOUNTER=GROUP (forcebattle.run_group, library
  module); 'section:SID' = the initial_status5 story point
  (party at the card library's spawn for that chapter); 'event:EVnn-nnnn' = the party at the
  debug jump point of that event, story section just before it.

What `card` makes (out/fixtures/cards/sc_<id>/, a port saves dir; never committed): the route's
save2 + saveedit.py patch: the progression row's story section (the last initial_status5 start
state before the boss's trigger event), the party spawned at the battle's own party position
(fixed_encount_param #301) on the boss's planet, tutorial pop-ups seen.  `--preset strong`:
the levels of the late-game section 13020 kept under the target section (for fights the
section's start levels lose).  No save state: it works with any build.

What `run` does: power-on with the card (bootcheck.py's card-library boot: CONTINUE, recap),
finds field control, then a second run with RG_FORCE_ENCOUNTER=fixed:ID@60 (rg_game_main.c: 60
fields after control the fixed battle ID goes into the game's own pending-encounter slot,
GameDataSetPendingEncounterId_3e67b0, as the story's SetPendingEncounter command does) and a
memory dump every 10 fields; PASS = the battle is reached (game mode 7, fight phase 7/201) and
the enemy records name the expected enemies (enc_hunt.enemies).  --before: no forced battle;
the card alone (the story trigger fires when the party walks in, or the event replays).
--state also writes a save state at fight+4 (RG_SS=1) into out/fixtures/<exe-id>/scenario/ for
play.py --from (exe-bound: regenerate after a rebuild).  --oracle: the same run on the oracle
twin (RG_RENDER=emu) with shots at the same fields.  Prints the commands that start the port
there headless and windowed.
"""
from __future__ import annotations

import argparse
import json
import math
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT / "tools" / "native"))
import bootcheck  # noqa: E402
import cardlib  # noqa: E402
import fxlib  # noqa: E402
import progression  # noqa: E402

CARDS = fxlib.FIXTURES / "cards"
PREFIX = "sc_"
AFTER = 60   # fields of field control before the battle is queued
WALK = 600   # walk-in: fields of stick-forward after control
WALK_BACK = 300   # walk-in: start this far from the event jump
SEARCH = 1440     # search walk (event: targets whose trigger box is not under the spawn): fields of spiral
SEARCH_LEG = 24   # search walk: first leg length (fields); legs grow by this every second turn
EVENT_FIELDS = 14000   # event: targets with a boss: fields after control to reach its battle
# event: cards that start in an event box: the planet the party stands on (default: event_param5
# #100 [0], the planet the event ENDS on).  A trigger action `31 05 (N)` (ScriptFnTransporterWarp_3d8e00)
# pushes game mode 11 with the event row's area: group -2 = party +0x6 (map slot 0 area), -1 = party
# +0xA; TransporterWarpModeUpdate_27f140 runs the row's label in THAT area's map script
# (MapAreaScriptRun_27a9e0) and waits in 11/0 for field control.  An area slot with no script
# (+0xE8 == 0) returns before the call and 11/0 holds forever (lane scenario5).  EV09-0009 (group
# -2, label 10002) ends in space (planet 9): from space (area 900) or the Rose Nebula (800) the
# slot-0 script is NULL (symdump.py: D_004B8C70 slot 0 id 800, script 0) -> hold, port AND retail.
# The story plays it with the Dorgenark docked at Zerard after chapter 8-C (planet 4, area 400
# m04.stb: label 10002 = fade out / BGM stop), then the chapter-9 opening and the Zegram fight.
EVENT_PLANET_FIX = {"EV09-0009": 4}
# The docked Dorgenark's map slot (area 1000) transform per planet: (x, y, z, rot_y) of the slot
# (map manager D_004B8C70 + 0x1928 + k * 0x1CC: +0x30 pos, +0x3C rot_y, MapDataGetMatrix_1e7670:
# MatRotY row vectors), measured with symdump.py; planets 1 / 8 / 9 place the ship at the origin.
# Ship-map event boxes (map/ship01e01/*.cfg) are ship-local: world = local * RotY + pos.
SHIP_DOCK = {4: (-1241.588, -1191.588, 12321.623, 1.5707964)}


def ship_box_world(planet, x, y, z, yaw):
    """A ship-local point (an event box of map/ship01e01) in planet `planet`'s world coordinates."""
    if planet not in SHIP_DOCK:
        return x, y, z, yaw
    px, py, pz, r = SHIP_DOCK[planet]
    c, s = math.cos(r), math.sin(r)
    return x * c + z * s + px, y + py, -x * s + z * c + pz, yaw + r
# enemy: targets: encounter zone (encount_group_param group-name prefix) -> a card-library card
# standing in it: the FALLBACK of enemy: targets (run_enemy tries tools/fixtures/areaplace.py
# first, lane cactugus: the party placed in a location whose area table lists the group).  Also
# the story-section source areaplace takes for a zone.  Checked by `prove --set enemies`.
ZONE_CARDS = {
    "RZ01": "ch01_salgin",      # Rosa, Salgin
    "RZ04": "ch07_rosa",        # Rosa, Sylvazard desert
    "RZ06": "ch09_labyrinth",   # Rosa, labyrinth
    "RZ07": "ch10_kuje",        # Rosa, Kuje desert
    "JR04": "ch02_juraika",     # Juraika, jungle A
    "JR05": "ch03_falls",       # Juraika, jungle B: the falls card stands in location 3504 (table 2502, no
                                # Cactugus group); enemy: targets use areaplace.py (location 3506, table 2503)
    "JR07": "ch08b_juraika",    # Juraika, Leo King's castle
    "ZL04": "ch04_prison",      # Zerard, prison
    "ZL05": "ch05_factory",     # Zerard, factory
    "ZL06": "ch08c_zerard",     # Zerard, Gladius towers
    "BD02": "ch06_vedan",       # Vedan, Myna path
    "BD03": "ch06_mines",       # Vedan, mines
    "BD04": "ch08a_vedan",      # Vedan, Cancer King ruins
    "MG03": "ch11_mariglenn",   # Mariglenn
    "MG04": "ch12_mariglenn",
    "MG05": "ch13_mariglenn",
    "GS01": "ghost_ship",       # ghost ship
    "EX04": "ghost_ship_ex",    # ghost ship EX (10F)
    "AR03": "alistia",          # Alistia
}
# the proving sets (prove --set NAME): 'default' = early, mid, late, an overlay planet, the
# ghost ship EX, an area master; 'story' = every story boss of census/progression.tsv
# (chapters 1-13, by fixed id); 'post' = chapter-14 rematches, ghost-ship EX, Alistia, area
# masters; 'enemies' = one random-encounter group per ZONE_CARDS zone (enemy:GROUP)
PROVE = ["Mark VIII Salamander", "Mud Whooper", "event:EV02-0150", "Jupis Robot", "Drill Rig", "Libra King",
         "Sand Kraken", "Albioth", "Valkog", "Gokilla", "enemy:Cactugus"]


def prove_set(name):
    if name == "default":
        return list(PROVE)
    rs = [r for r in rows() if r["kind"] == "boss"]
    if name == "story":
        rs = [r for r in rs if r["chapter"].isdigit() and int(r["chapter"]) <= 13]
        return [r["id"] for r in sorted(rs, key=lambda r: (int(r["chapter"]), int(r["section"] or 0), int(r["id"])))]
    if name == "post":
        return [r["id"] for r in rs if not (r["chapter"].isdigit() and int(r["chapter"]) <= 13)]
    if name == "enemies":
        import forcebattle
        # per zone: its first group that an area table lists (the GROUP force replaces the roll
        # of a table that lists it); JR05 = the Cactugus group 2506
        listed = {int(x) for r in rows() if r["kind"] == "encounter" for x in r["group_ids"].split()}
        out = []
        for z in ZONE_CARDS:
            g = next((g for g in forcebattle.groups() if g[1].upper().startswith(z + "_") and g[0] in listed
                      and (z != "JR05" or g[0] == 2506)), None)
            if g:
                out.append(f"enemy:{g[0]}")
        return out
    raise SystemExit(f"scenario: no proving set {name!r} (default, story, post, enemies)")


def mem_wait(gb=12.0, poll=30, limit=3600):
    """Wait until the machine's free commit (GlobalMemoryStatusEx ullAvailPageFile, the value
    Win32_OperatingSystem FreeVirtualMemory reports) exceeds `gb` GB (rule for heavy jobs)."""
    if sys.platform != "win32":
        return True
    import ctypes

    class MS(ctypes.Structure):
        _fields_ = [("dwLength", ctypes.c_ulong), ("dwMemoryLoad", ctypes.c_ulong)] + [(n, ctypes.c_ulonglong) for n in ("tp", "ap", "tpf", "apf", "tv", "av", "aev")]
    t0 = time.time()
    while True:
        m = MS()
        m.dwLength = ctypes.sizeof(MS)
        ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(m))
        if m.apf / 2 ** 30 > gb or time.time() - t0 > limit:
            return m.apf / 2 ** 30 > gb
        print(f"scenario: free commit {m.apf / 2 ** 30:.1f} GB <= {gb} GB, waiting", flush=True)
        time.sleep(poll)


def rows():
    return progression.read()


def event_boss(ev):
    """The census boss row an event starts: the census `event` column, else trigscan.starts()
    ('field event': a trigger_param6 action arms the battle and plays the event; lane scenario4:
    EV09-0009 -> 1029 Zegram, EV10-0090 -> 1035 Johanna).  None when the event starts no boss."""
    r = next((r for r in rows() if r["event"] == ev and r["kind"] == "boss"), None)
    if r:
        return r
    import trigscan
    ids = [i for i, ss in sorted(trigscan.starts().items())
           if any(s["kind"] == "field event" and (s.get("event_name") or "").upper() == ev for s in ss)]
    return next((r for r in rows() if r["kind"] == "boss" and ids and int(r["id"]) in ids), None)


def norm(s):
    return re.sub(r"[^a-z0-9]+", " ", s.lower()).strip()


def chapter_rank(r):
    c = r.get("chapter", "")
    return (0, int(c)) if c.isdigit() else (1, 0)


def resolve(target: str):
    """-> ('fixed', row) | ('enemy', name) | ('section', sid) | ('event', ev)."""
    t = target.strip()
    low = t.lower()
    for pre, kind in (("enemy:", "enemy"), ("section:", "section"), ("event:", "event")):
        if low.startswith(pre):
            return kind, t[len(pre):].strip()
    if low.startswith("boss:"):
        t = t[5:].strip()
    fx = [r for r in rows() if r["kind"] in ("boss", "fixed")]
    if t.isdigit():
        hit = [r for r in fx if r["id"] == t]
        if hit:
            return "fixed", hit[0]
        sys.exit(f"scenario: no fixed battle {t}")
    q = norm(t)
    for test in (lambda r: norm(r["name"]) == q, lambda r: q in norm(r["name"]),
                 lambda r: any(norm(e) == q for e in r["enemies"].split(", ")),
                 lambda r: q in norm(r["enemies"])):
        hit = [r for r in fx if test(r)]
        if hit:
            hit.sort(key=lambda r: (r["kind"] != "boss", chapter_rank(r), int(r["id"])))
            return "fixed", hit[0]
    return "enemy", t


def card_name(kind, key):
    return PREFIX + re.sub(r"[^A-Za-z0-9]+", "_", str(key)).strip("_").lower()


def patch(card: Path, args):
    import saveedit
    return saveedit.main(["patch", str(card)] + args)


def make_card(kind, key, preset="story", name=None, walk_in=False, event_state="after", patch_extra=(), at_box=False):
    """Write the scenario card; returns (card name, info dict)."""
    import rgdata
    import saveedit
    info = {"kind": kind, "preset": preset}
    clear = []
    if kind == "fixed":
        r = key
        info.update(id=int(r["id"]), name=r["name"], label=r["label"], section=r["section"], planet=r["planet"],
                    enemies=r["enemies"], spawn=r["spawn"], event=r["event"])
        if not r["section"] or not r["planet"] or not r["spawn"]:
            sys.exit(f"scenario: {r['label']}: no section / planet / position in the census (fill progression.py's "
                     f"SECTION_FIX / PLANET_FIX)")
        secs = [int(r["section"])]
        if secs[0] >= 14000 and secs[0] < 15000 or secs[0] >= 28000:
            secs = [13020] + secs   # post-game sections sit on top of the final story point (cardlib)
        spawn = ["--spawn", f"{r['planet']}:{r['spawn']}"]
        name = name or card_name(kind, r["id"])
    elif kind == "section":
        sid = int(key)
        secs = [sid]
        lib = next((v for v in cardlib.LIBRARY.values() if v[0][-1] // 10 == sid // 10), None) or \
            min(cardlib.LIBRARY.values(), key=lambda v: abs(v[0][-1] - sid))
        sp = lib[1]
        spawn = (["--spawn", "%d:%s,%s,%s,%s" % sp] if isinstance(sp, tuple) else ["--spawn-jump", str(sp)])
        info.update(section=sid, spawn_from=str(sp))
        name = name or card_name(kind, sid)
    elif kind == "event":
        ev = key.upper().replace("_", "-")
        j = rgdata.map_jumps()
        jid = next((k for k, v in sorted(j.items()) if progression.event_of(v[5]) == ev), None)
        boss = event_boss(ev)
        import trigscan
        box = trigscan.event_box(ev)   # the trigger's event box (map .cfg FUNC_DATA "event")
        box = box if box and box["planet"] else None
        if jid is None and not box and not (boss and boss["planet"] and boss["spawn"]):
            sys.exit(f"scenario: no debug jump point names {ev} (and no event box / boss position)")
        flag = {v: k for k, v in rgdata.flag_names().items()}.get(ev)
        secs_all = sorted(rgdata.sections())
        story = [s for s in secs_all if 1000 <= s < 14000]
        before = [s for s in story if flag is None or not any(n == flag and v for n, v in rgdata.sections()[s]["flags"])]
        sid = before[-1] if before else story[0]
        secs = [sid]
        if box and (at_box or jid is None):
            # lane scenario4: the centre of the event box its trigger tests (trigscan.event_box:
            # trigger_param6 #101 `party in event box N`, map .cfg FUNC_POS), on the event's planet
            # (event_param5 #100); the run presses CROSS there (investigate-press triggers).
            # Used when no debug jump names the event (EV09-0009: Dorgenark bridge box 4010) or
            # the jump is outside the box (EV10-0090: jump 129 ~130 units off box 10090)
            pl = EVENT_PLANET_FIX.get(ev, box["planet"])
            bx, by, bz, byaw = box["x"], box["y"], box["z"], box["yaw"]
            if "ship01e01" in box["map"].lower():   # lane scenario5: the docked ship's frame
                bx, by, bz, byaw = ship_box_world(pl, bx, by, bz, byaw)
            spawn = ["--spawn", "%d:%.2f,%.2f,%.2f,%.3f" % (pl, bx, by, bz, byaw)]
            info.update(spawn_from=f"event box {box['box']} ({box['map']}, trigger #{box['trigger']}, zone {box['zone']})",
                        planet=pl)
            name = name or card_name(kind, ev + "_box")
        elif jid is not None:
            spawn = ["--spawn-jump", str(jid)]
        else:
            # no jump, no event box: the party position of the battle the event starts
            spawn = ["--spawn", f"{boss['planet']}:{boss['spawn']}"]
            info.update(spawn_from=f"battle {boss['id']} party position")
        info.update(event=ev, jump=jid, section=sid, flag=flag, event_box=box["box"] if box else None)
        after = [s for s in story if s not in before]
        if event_state == "after" and flag is not None and after:
            # the first section that HAS the event's flag, with every flag it sets beyond the
            # section before cleared: the story flags of the moment before the event, but the
            # party / character records of after it.  The "before" section's own records can be
            # incomplete for the event: EV02-0150 from section 2032 halts after line 201500060
            # on the port AND on retail PCSX2 (Lilika, chara 11006, has no record before she
            # joins); from 2040 minus flags 35/36/37/1400 it plays through part 2 (the
            # tentacles) into the Mud Whooper battle.
            fl = lambda s: {n for n, v in rgdata.sections()[s]["flags"] if v}
            clear = sorted(fl(after[0]) - fl(sid))
            secs = [after[0]]
            info.update(section=after[0], cleared=clear, state="after")
        if walk_in and jid is not None:
            # the party WALKS into the trigger instead of standing on it (a trigger fired on the
            # card's first field can run before the area is set up: EV02-0150 halts at Lilika on
            # both the port and retail).  Start = the nearest 'NPM:' navigation jump on the planet
            # within 1,500 units (the developers' "go to X" marker), else 600 units back along -z;
            # facing the event jump; run() pushes the stick forward.
            pl, ex, ey, ez = j[jid][0], j[jid][1], j[jid][2], j[jid][3]
            # 1st choice: WALK_BACK units from the event jump toward the battle position of the
            # boss this event starts (the side the story arrives from at the spring); else the
            # nearest 'NPM:' navigation jump; else 600 units back along -z
            boss = next((r for r in rows() if r["event"] == ev and r["kind"] == "boss" and r["spawn"]), None)
            npm = [(math.dist((v[1], v[3]), (ex, ez)), v) for k, v in j.items()
                   if v[0] == pl and str(v[5]).startswith("NPM") and 100 < math.dist((v[1], v[3]), (ex, ez)) < 1500]
            if boss:
                bx, by, bz = [float(v) for v in boss["spawn"].split(",")[:3]]
                d = math.dist((bx, bz), (ex, ez)) or 1.0
                sx, sy, sz = ex + (bx - ex) * WALK_BACK / d, ey, ez + (bz - ez) * WALK_BACK / d
            else:
                sx, sy, sz = (min(npm, key=lambda t: t[0])[1][1:4]) if npm else (ex, ey, ez - 600)
            yaw = math.atan2(ex - sx, ez - sz)
            spawn = ["--spawn", f"{pl}:{sx:.2f},{sy:.2f},{sz:.2f},{yaw:.3f}"]
            info.update(walk_in=[round(sx, 1), round(sy, 1), round(sz, 1), round(yaw, 3)],
                        walk_dist=round(math.dist((sx, sz), (ex, ez))))
            name = name or card_name(kind, ev + "_walk")
        name = name or card_name(kind, ev)
    else:
        sys.exit(f"scenario: no card for kind {kind}")
    if kind == "event" and event_state != "after":
        name += "_bstate"
    if preset == "strong" and not name.endswith("_strong"):
        name += "_strong"
    card = CARDS / name
    saveedit.cmd_copy(argparse.Namespace(src=str(CARDS / "save2"), dst=str(card)))
    if preset == "strong":
        patch(card, ["--section", "13020"])
        args = sum((["--section", str(s)] for s in secs), []) + ["--no-levels"]
    else:
        args = sum((["--section", str(s)] for s in secs), [])
    rc = patch(card, args + spawn + ["--no-help"] + sum((["--clear-flag", str(n)] for n in clear), []) + list(patch_extra))
    if rc:
        sys.exit(f"scenario: saveedit patch failed ({rc})")
    info["sections"] = secs
    info["card"] = str(card)
    (card / "scenario.json").write_text(json.dumps(info, indent=1), encoding="utf-8")
    return name, info


def boot_script(control, extra=()):
    """Card-library boot presses before field control `control` (no smoke actions: the party
    stands where the card put it), + extra lines."""
    keep = []
    for ln in bootcheck.lib_script(control).splitlines():
        t = ln.split()
        if ln.startswith("#!stick") and len(t) > 2 and t[1].isdigit() and int(t[1]) >= control:
            continue   # the library's box walk after control: the party stays where the card put it
        if ln.startswith("#") or (t and t[0].isdigit() and int(t[0]) < control):
            keep.append(ln)
    return "\n".join(keep + list(extra)) + "\n"


def advance_lines(start, end, every):
    """CROSS (4 fields) every `every` fields from start + every to end: steps an event scene's
    dialogue (the scene waits on it; the voice lines play out between presses)."""
    return [f"{k} {k + 3} CROSS  # scenario: advance the event" for k in range(start + every, end, every)] if every else []


def spiral_lines(start, end):
    """Stick lines: an outward square spiral (camera-relative forward, right, back, left; legs
    SEARCH_LEG, SEARCH_LEG, 2 x SEARCH_LEG, 2 x ..) from `start` to `end`."""
    out, k, d = [], start, 0
    legs = (("128 0", "forward"), ("255 128", "right"), ("128 255", "back"), ("0 128", "left"))
    while k < end:
        n = SEARCH_LEG * (d // 2 + 1)
        xy, nm = legs[d % 4]
        out.append(f"#!stick {k} {min(k + n, end) - 1} {xy}  # scenario: search {nm}")
        k += n
        d += 1
    return out


def commands(name, fid, exe, control, script_path, end=None):
    env = f"RG_FORCE_ENCOUNTER=fixed:{fid}@{AFTER}" if fid else ""
    head = (f"$env:RG_FORCE_ENCOUNTER='fixed:{fid}@{AFTER}'; " if fid else "")
    return [
        f"headless: {head}python tools\\fixtures\\run_from.py --boot-save {name} --input {script_path} "
        f"--exe {exe} --fields {end or control + 1500}",
        f"windowed: {head}python tools\\fixtures\\run_from.py --boot-save {name} --input {script_path} "
        f"--exe {exe} --fields {control + 100000} --windowed",
        f"play it yourself: copy {CARDS / name} to a saves dir, {('set ' + env + ', ') if env else ''}"
        f"start rg-game --saves DIR, CONTINUE -> FILE 01"
        + (f" (the battle starts {AFTER} fields after control)" if fid else ""),
    ]


def timeline(st, start=0):
    """[(field, ovl, gamemode)] at each change of (ovl, gamemode) from `start` on."""
    out, last = [], None
    for k in sorted(st):
        if k >= start and st[k] != last:
            out.append((k,) + tuple(st[k]))
            last = st[k]
    return out


def pool_verdict(res, key):
    """enemy:GROUP targets: a '<zone>_<Name>&A' group is a member POOL (the battle spawns a subset,
    e.g. 3601 Ancient Knight&A met as Will O' The Wisp x2 + Type-G), so 'its first member' is no
    test: PASS when the force line says the group was forced (`(found`) and every enemy record
    is a member of the group."""
    if not key.isdigit() or res.get("verdict") == "PASS" or res.get("crash") or not res.get("fight"):
        return
    import enc_hunt
    import forcebattle
    g = next((g for g in forcebattle.groups() if g[0] == int(key)), None)
    names = enc_hunt.monster_names()
    mem = {names.get(m, str(m)).lower() for m in (g[2] if g else [])}
    found = [x.split("@")[0].lower() for x in res.get("found") or []]
    if any("(found" in ln for ln in res.get("force") or []) and found and all(f in mem for f in found):
        res.update(verdict="PASS", why="", pool="enemy records are members of the forced group")


def run_enemy(key, exe, out=None, quiet=False, shots=False, oracle=None):
    """enemy:NAME | enemy:GROUP.  1st: tools/fixtures/areaplace.py (lane cactugus): the party
    placed inside a location whose area table lists the group (encount_param #200 location ->
    location_a #900 map boxes), checked at boot, paced there with RG_FORCE_ENCOUNTER=GROUP (the
    override CharaSysEncounterPickFormationMaybe_3a5090 replaces the game's roll by that group).
    Fallback when areaplace cannot place the party: the zone's card (ZONE_CARDS) with the card
    library's box walk (forcebattle.run_group; forces the group only where the walk's table
    lists it).  PASS = a battle whose enemy records name the enemy (group id: its first member)."""
    import bootcheck as bc
    import enc_hunt
    import forcebattle
    t0 = time.time()
    out0 = Path(out or fxlib.FIXTURES / "runs" / "scenario" / card_name("enemy", key))
    try:
        import areaplace
        r = areaplace.run(key, exe, oracle=oracle, shots="+16,+64,+148" if shots else None, out=out0,
                          quiet=True, keep_card=True)
    except SystemExit as e:   # areaplace refusals (no table lists the group, ..)
        r = {"verdict": "FAIL", "why": f"areaplace: {e}"}
    except Exception as e:   # noqa: BLE001 -- an areaplace error: fall back to the zone card
        r = {"verdict": "FAIL", "why": f"areaplace error {type(e).__name__}: {e}"}
    if r.get("verdict") == "PASS" or r.get("encounter") is not None or r.get("crash"):
        res = {**r, "target": f"enemy:{key}", "kind": "enemy", "id": r.get("group"), "via": "areaplace"}
        pool_verdict(res, key)
        return _finish(res, out0, t0, quiet)
    ap_why = r.get("why") or r.get("verdict")
    gid = forcebattle.resolve(key)
    g = next(g for g in forcebattle.groups() if g[0] == gid)
    expect = key if not key.isdigit() else enc_hunt.monster_names().get(g[2][0], str(g[2][0]))
    zone = forcebattle.zone(gid)
    card = ZONE_CARDS.get(zone)
    out = out0 / "zonecard"
    out.mkdir(parents=True, exist_ok=True)
    res = {"target": f"enemy:{key}", "kind": "enemy", "group": gid, "group_name": g[1], "zone": zone,
           "card": card, "expect": expect, "id": gid, "via": "zone card (areaplace: %s)" % ap_why}
    if not card:
        res.update(verdict="FAIL", why=f"no card in zone {zone} (ZONE_CARDS)")
        return _finish(res, out, t0, quiet)
    rc, log, st = bc.run_status(card, bc.lib_script(None), exe, 4700, 1, [], {}, card + "_pass1", out)
    ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v[1] == "6/100"), None)
    res["control"] = ctl
    if ctl is None:
        res.update(verdict="FAIL", why=f"no field control by 4,700 (exit {rc})", crash=fxlib.crash_report(log, exe))
        return _finish(res, out, t0, quiet)
    r = forcebattle.run_group(card, exe, out, gid, ctl, expect=expect)
    res.update({k: v for k, v in r.items()})
    pool_verdict(res, key)
    res["commands"] = [f"headless: $env:RG_FORCE_ENCOUNTER='{gid}'; python tools\\native\\card_shots.py {card} "
                       f"{exe} OUT --control {ctl} --fields {(r['fight'] or ctl + 2600) + 200}"]
    if shots and res["verdict"] == "PASS":
        at = [r["fight"] + 16, r["fight"] + 64, r["fight"] + 148]
        x2 = sum((["--shot", f"{f}:{out / f'nat_f{f}.png'}"] for f in at), [])
        bc.run_status(card, forcebattle.walk_script(ctl), exe, max(at) + 2, 10, x2,
                      {"RG_FORCE_ENCOUNTER": str(gid)}, card + f"_g{gid}_shots", out)
        res["shots"] = [str(out / f"nat_f{f}.png") for f in at]
    return _finish(res, out, t0, quiet)


def run(target, exe, out=None, shots=False, state=False, before=False, preset="story", oracle=None,
        fields=None, quiet=False, shot_at=None, advance=None, walk_in=False, event_state="after", name=None,
        patch_extra=(), search=False):
    import autobattle
    import enc_hunt
    kind, key = resolve(target)
    exe_given = Path(exe)
    exe = bootcheck.snapshot_exe(Path(exe))
    if kind == "enemy":
        return run_enemy(key, exe, out, quiet, shots, oracle)
    t0 = time.time()
    name_arg = name
    name, info = make_card(kind, key, preset, name=name, walk_in=walk_in and kind == "event", event_state=event_state,
                           patch_extra=patch_extra, at_box=search)   # name / patch_extra: chainprove.py (extra saveedit args)
    walk = bool(info.get("walk_in"))
    fid = info.get("id") if kind == "fixed" and not before else None
    out = Path(out or fxlib.FIXTURES / "runs" / "scenario" / name)
    out.mkdir(parents=True, exist_ok=True)
    rc, log, st = bootcheck.run_status(name, bootcheck.lib_script(None), exe, 4700, 1, [], {}, name + "_pass1", out)
    st1 = st
    # the start point: control, or the event scene that an event card's trigger starts within
    # 60 fields of it (EV02-0150: control 3721, scene 3723)
    # control = the first field after the recap with field control (6/100) or an event scene
    # (11/x: an event card's trigger fires on load, the pre-event start point)
    ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and (v[1] == "6/100" or v[1].startswith("11/"))), None)
    res = {"target": target, "card": name, "kind": kind, "control": ctl, **{k: info[k] for k in info if k != "card"}}
    if ctl is None:
        crash = fxlib.crash_report(log, exe)
        res.update(verdict="FAIL", why=f"no field control by 4,700 (exit {rc})", crash=crash)
        return _finish(res, out, t0, quiet)
    if kind == "event" and not walk and not search and info.get("event_box") and             not any(ctl <= k <= ctl + 60 and v[1].startswith("11/") for k, v in st1.items()):
        # no scene on load at the debug jump: stand in the trigger's event box instead (lane scenario4)
        return run(target, exe_given, out, shots, state, before, preset, oracle, fields, quiet, shot_at,
                   advance, walk_in, event_state, name_arg, patch_extra, search=True)
    # event targets that start a boss: run through the cutscene into the battle (self-check)
    boss_row = event_boss(info.get("event")) if kind == "event" else None
    end = fields or (ctl + EVENT_FIELDS if boss_row else ctl + AFTER + 1800)
    sp = fxlib.FIXTURES / "runs" / "bootlib" / f"{name}.input.txt"
    env = {"RG_STATUS_DUMP": autobattle.dump_spec(exe)}
    if fid:
        env["RG_FORCE_ENCOUNTER"] = f"fixed:{fid}@{AFTER}"
    pre = before or kind in ("event", "section")
    if advance is None:
        advance = 120 if kind == "event" else 0
    adv = advance_lines(ctl, 32000, advance) if pre else []   # input scripts stop at 32,636 vblanks
    if walk:   # walk camera-forward into the trigger (the card faces the event jump)
        # from control + 360 as the card library's walk (the stick does nothing before it)
        adv = [f"#!stick {ctl + 360} {ctl + 360 + WALK} 128 0  # scenario: walk into the event trigger"] + \
            advance_lines(ctl + 360 + WALK, 32000, advance)
    elif search:   # lane scenario4: no scene at the debug jump (EV10-0090: the party stands in the
        # house beside the trigger's event box): the card now stands at the box centre
        # (make_card at_box); CROSS every 20 fields + an outward square spiral from control + 360: these
        # triggers fire on an investigate press inside the box (FieldExploreModeUpdate_2833a0:
        # pad 0x40 while standing / walking -> MapAreaTriggerEventsMaybe_200950), then the
        # usual CROSS steps
        adv = spiral_lines(ctl + 360, ctl + 360 + SEARCH) +             advance_lines(ctl + 340, ctl + 360 + SEARCH, 20) + advance_lines(ctl + 360 + SEARCH, 32000, advance)
    if pre:   # every field (the event start is the shot origin); no memory dumps
        env = {}
    every = 1 if pre else 10
    res["advance"] = advance if pre else None
    rc, log, st = bootcheck.run_status(name, boot_script(ctl, adv), exe, end, every, [], env, name, out)
    res["commands"] = commands(name, fid, exe_given, ctl, sp, end)
    crash = fxlib.crash_report(log, exe)
    q = re.search(r"SCENARIO field=(\d+)", log)
    res["queued"] = int(q.group(1)) if q else None
    enc, fight, found = enc_hunt.enemies(log, enc_hunt.monster_names())
    res.update(encounter=enc, fight=fight, found=found, crash=crash, exit=rc)
    res["modes"] = timeline(st, ctl)
    if pre:
        ev0 = next((k for k, v in sorted((st if walk else st1).items())
                    if ctl <= k <= ctl + (WALK + 760 if walk else 60) and v[1].startswith("11/")), None)
        if ev0 is None and not walk and not search:
            # an investigate-press trigger (CROSS inside its box) under the spawn: the first CROSS
            # step (control + advance) starts the scene in the main pass
            ev0 = next((k for k, v in sorted(st.items()) if ctl <= k <= ctl + (advance or 0) + 30
                        and v[1].startswith("11/")), None)
        if search:
            ev0 = next((k for k, v in sorted(st.items()) if ctl <= k <= ctl + 360 + SEARCH + 60
                        and v[1].startswith("11/")), None)
            res["search"] = f"spiral {ctl + 360}-{ctl + 360 + SEARCH}"
        if kind == "event" and search and ev0 is None and event_state == "after" and info.get("event_box"):
            # the "after" section's party can differ (EV09-0009: section 9020 = Zegram alone, no
            # scene in box 4010; from 9010, the last section without the flag, it plays): once more
            # with the "before" story state (lane scenario4)
            return run(target, exe_given, out, shots, state, before, preset, oracle, fields, quiet, shot_at,
                       advance, walk_in, "before", name_arg, patch_extra, search=True)
        if kind == "event" and not walk and not search and ev0 is None:
            # no scene on the spawn: walk a spiral around it (same card), once
            return run(target, exe_given, out, shots, state, before, preset, oracle, fields, quiet, shot_at,
                       advance, walk_in, event_state, name_arg, patch_extra, search=True)
        if walk:
            res["fight_mode_at"] = next((k for k, v in sorted(st.items()) if k > ctl and v[1] == "7/201"), None)
        res["event_started"], res["start"] = ev0, ev0 or ctl
        res["fight_after_event"] = next((k for k, v in sorted(st.items()) if k > ctl and v[1] == "7/201"), None)
        if boss_row:
            res["boss"] = f"{boss_row['id']} {boss_row['name']}"
        if kind == "event":   # PASS = the event scene runs from its start (and into its boss battle)
            ok = res["event_started"] and (res["fight_after_event"] or not boss_row)
            res["verdict"] = "PASS" if not crash and ok else "FAIL"
            if not ok:
                res["why"] = "no event scene" if not res["event_started"] else \
                    f"event never reached the {boss_row['name']} battle by field {end}"
            elif boss_row and not crash:
                # which battle did the event start?  the same inputs again to fight + 40 with the
                # enemy-record dumps (every 10 fields; the scene pass samples every field without
                # dumps): PASS also needs the boss's first enemy there (lane scenario4)
                f = res["fight_after_event"]
                _rc, log2, _st = bootcheck.run_status(name, boot_script(ctl, adv), exe, f + 42, 10, [],
                                                      {"RG_STATUS_DUMP": autobattle.dump_spec(exe)}, name + "_enemies", out)
                _e, f2, found = enc_hunt.enemies(log2, enc_hunt.monster_names())
                want = [e for e in boss_row["enemies"].split(", ") if e][:1]
                res.update(found=found, fight_enemies_pass=f2)
                if not (found and all(w.lower() in " ".join(found).lower() for w in want)):
                    res.update(verdict="FAIL", why=f"battle after the event has {found}, want {want}")
        else:
            res["verdict"] = "PASS" if not crash and any(v[1] in ("6/100", "11/0") for k, v in st.items()
                                                         if k > ctl + 100) else "FAIL"
        if shots:   # also on FAIL (where did the party go)
            at = [res["start"] + int(x) for x in (shot_at or "40,120,240,400,600").split(",")]
            x2 = sum((["--shot", f"{f}:{out / f'nat_f{f}.png'}"] for f in at), [])
            bootcheck.run_status(name, boot_script(ctl, adv), exe, max(at) + 2, every, x2, env, name + "_shots", out)
            res["shots"] = [str(out / f"nat_f{f}.png") for f in at]
        return _finish(res, out, t0, quiet)
    want = [e for e in dict.fromkeys(info.get("enemies", "").split(", ")) if e]
    names = " ".join(found).lower()
    ok_enemy = bool(found) and all(w.lower() in names for w in want[:1])
    if crash:
        res.update(verdict="FAIL", why="crash")
    elif fight is None:
        res.update(verdict="FAIL", why="no battle reached" if enc is None else f"battle at {enc}, no fight phase")
    elif not ok_enemy:
        res.update(verdict="FAIL", why=f"battle has {found}, want {want[:1]}")
    else:
        res["verdict"] = "PASS"
    if res["verdict"] == "PASS" and (shots or state or oracle):
        # --shot-at in battle mode: fields after the ENCOUNTER (the boss intro runs between the
        # encounter and the fight phase); default fight +16 / +64 / +148
        at = [enc + int(x) for x in shot_at.split(",")] if shot_at else [fight + 16, fight + 64, fight + 148]
        x2 = []
        for f in at:
            x2 += ["--shot", f"{f}:{out / f'nat_f{f}.png'}"]
        env2 = dict(env)
        if state:
            sd = fxlib.fixture_dir(exe) / "scenario"
            sd.mkdir(parents=True, exist_ok=True)
            stp = sd / f"{name}_fight.rgstate"
            x2 += ["--save-state", f"{fight + 4}:{stp}"]
            env2["RG_SS"] = "1"
            res["state"] = str(stp)
        bootcheck.run_status(name, boot_script(ctl), exe, max(at) + 2, 10, x2, env2, name + "_shots", out)
        if oracle:
            o = bootcheck.snapshot_exe(Path(oracle))
            x3 = sum((["--shot", f"{f}:{out / f'emu_f{f}.png'}"] for f in at), [])
            rco, logo, sto = bootcheck.run_status(name, boot_script(ctl), o, max(at) + 2, 10, x3,
                                                  dict(env, RG_RENDER="emu"), name + "_oracle", out)
            res["oracle_fight"] = next((k for k, v in sorted(sto.items()) if k > ctl and v[1] == "7/201"), None)
            p = subprocess.run([sys.executable, str(ROOT / "tools" / "native" / "shotpsnr.py"), str(out), str(out)],
                               capture_output=True, text=True)
            res["oracle"] = "same fight field" if res["oracle_fight"] == fight else f"oracle fight {res['oracle_fight']}"
    return _finish(res, out, t0, quiet)


def _finish(res, out, t0, quiet):
    res["wall_s"] = round(time.time() - t0)
    (out / "scenario.json").write_text(json.dumps(res, indent=1, default=str), encoding="utf-8")
    if not quiet:
        print(f"scenario {res.get('target')}: {res['verdict']}  card {res.get('card')}  control {res.get('control')}  "
              f"queued {res.get('queued')}  battle {res.get('encounter')}  fight {res.get('fight')}  "
              f"enemies {', '.join(res.get('found') or []) or '-'}  ({res['wall_s']} s)"
              + (f"  why: {res['why']}" if res.get("why") else ""))
        if res.get("modes"):
            print("  modes after control (field ovl mode): " + "  ".join("%d %d %s" % m for m in res["modes"][:24]))
        for c in res.get("crash") or []:
            print("   ", c)
        for c in res.get("commands") or []:
            print("  " + c)
    return res


def cmd_list(a):
    q = norm(" ".join(a.query)) if a.query else ""
    for r in rows():
        if r["kind"] == "encounter" and not a.areas:
            continue
        if r["kind"] == "phase" and q:
            continue
        line = "  ".join(x for x in (r["kind"], r["id"], f"ch{r['chapter']}" if r["chapter"] else "", r["name"],
                                    r["planet_name"], f"section {r['section']}" if r["section"] else "",
                                    r["event"], r["enemies"], r["condition"] if r["kind"] == "encounter" else "") if x)
        if q and q not in norm(line):
            continue
        print(line)
    return 0


def selftest():
    """ctest fixtures.scenario_selftest: decoder, census and resolution, no rg-game."""
    import condexpr
    if not (ROOT / "data").is_dir():
        print("scenario selftest: SKIP (no data/)")
        return 77
    errs = []
    for s, want in (("jMAcCsQAIAYB", "chapter >= 8"), ("jYgd0pAACsQAeAoB", "progress[10] <= 30"),
                    ("jUAZl9HAHEQAAGA=", "flag[127] == 1"), ("", "always")):
        if condexpr.decode(s) != want:
            errs.append(f"condexpr {s!r}: {condexpr.decode(s)!r}, want {want!r}")
    tmp = fxlib.FIXTURES / "runs" / "scenario" / "selftest.tsv"
    progression.write(tmp)
    rs = progression.read(tmp)
    from collections import Counter
    c = Counter(r["kind"] for r in rs)
    if c["boss"] < 70 or c["encounter"] < 200 or c["phase"] < 40:
        errs.append(f"census kinds {dict(c)}")
    kind, r = resolve("Mud Whooper")
    if kind != "fixed" or (r["id"], r["planet"], r["section"]) != ("1005", "3", "2032"):
        errs.append(f"resolve Mud Whooper -> {kind} {r if kind != 'fixed' else (r['id'], r['planet'], r['section'])}")
    for t, want in (("Valkog", "10011"), ("Gokilla", "1050"), ("boss:1036", "1036")):
        k, r = resolve(t)
        if k != "fixed" or r["id"] != want:
            errs.append(f"resolve {t} -> {r if k != 'fixed' else r['id']}, want {want}")
    if resolve("enemy:Cactugus")[0] != "enemy":
        errs.append("enemy: prefix")
    for e in errs:
        print("  FAIL", e)
    print(f"scenario selftest: {'FAIL' if errs else 'PASS'} ({dict(c)})")
    return 1 if errs else 0


PROVE_COLS = ["target", "verdict", "id", "section", "control", "fight", "enemies", "wall_s", "why"]


def prove_row(r):
    return [r.get("target"), r.get("verdict"), r.get("id"), r.get("section"), r.get("control"), r.get("fight"),
            "|".join(r.get("found") or []), r.get("wall_s"), r.get("why", "")]


def cmd_prove(a):
    """Run a proving set serially (one rg-game at a time, free commit > 12 GB before each),
    rewriting OUT/prove.tsv after every target; --resume keeps the PASS rows of an earlier
    OUT/prove.tsv and runs the rest."""
    out = Path(a.out or fxlib.FIXTURES / "runs" / "scenario" / "prove")
    out.mkdir(parents=True, exist_ok=True)
    tsv = out / "prove.tsv"
    targets = a.only or sum((prove_set(n) for n in a.set), [])
    done = {}
    if a.resume and tsv.exists():
        for ln in tsv.read_text(encoding="utf-8").splitlines()[1:]:
            t = ln.split("\t")
            done[t[0]] = t
    rows_out = {}

    def flush():
        with open(tsv, "w", encoding="utf-8") as f:
            f.write("\t".join(PROVE_COLS) + "\n")
            for t in targets:
                if t in rows_out:
                    f.write("\t".join(str(x) for x in rows_out[t]) + "\n")
    for t in targets:
        if t in done and (done[t][1] == "PASS" or not a.retry_fail):
            rows_out[t] = done[t]
            continue
        mem_wait(a.min_commit_gb)
        try:
            r = run(t, a.exe, out / card_name("t", t), quiet=False)
        except SystemExit as e:   # make_card / resolve refusals: a tool cause, recorded
            r = {"target": t, "verdict": "FAIL", "why": f"tool: {e}"}
        except Exception as e:   # noqa: BLE001 -- keep the batch going, record the cause
            r = {"target": t, "verdict": "FAIL", "why": f"tool exception: {type(e).__name__}: {e}"}
        r["target"] = t
        rows_out[t] = prove_row(r)
        flush()
    flush()
    res = list(rows_out.values())
    npass = sum(r[1] == "PASS" for r in res)
    print(f"scenario prove: {npass}/{len(res)} PASS ({tsv})")
    return 0 if npass == len(res) else 1


def prove_md(tsv):
    """A prove.tsv as a markdown table with the census row's name / chapter (for the docs)."""
    by = {r["id"]: r for r in rows() if r["kind"] in ("boss", "fixed")}
    L = ["| Target | Battle | Ch | Section | Control | Fight | Enemy records | Verdict |",
         "| --- | --- | --- | --- | --- | --- | --- | --- |"]
    for ln in Path(tsv).read_text(encoding="utf-8").splitlines()[1:]:
        t = (ln.split("\t") + [""] * 9)[:9]
        r = by.get(t[0], {})
        from collections import Counter
        c = Counter(e.split("@")[0] for e in t[6].split("|") if e)
        en = ", ".join(f"{k} x{v}" if v > 1 else k for k, v in c.items())
        v = t[1] + (f" ({t[8]})" if t[8] else "")
        L.append(f"| {t[0]} | {r.get('name', '')} | {r.get('chapter', '')} | {t[3]} | {t[4]} | {t[5]} | {en} | {v} |")
    return "\n".join(L)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    ls = sp.add_parser("list")
    ls.add_argument("query", nargs="*")
    ls.add_argument("--areas", action="store_true", help="also the random-encounter area rows")
    for nm in ("card", "run"):
        p = sp.add_parser(nm)
        p.add_argument("target")
        p.add_argument("--preset", choices=["story", "strong"], default="story")
        p.add_argument("--before", action="store_true", help="no forced battle: the card alone")
        if nm == "run":
            p.add_argument("--exe", default=str(fxlib.exe_path()))
            p.add_argument("--out")
            p.add_argument("--shots", action="store_true")
            p.add_argument("--state", action="store_true")
            p.add_argument("--oracle")
            p.add_argument("--fields", type=int)
            p.add_argument("--shot-at", help="pre-event shots: fields after control, comma list (default 40,120,240,400,600)")
            p.add_argument("--event-state", choices=["after", "before"], default="after",
                           help="event: cards: 'after' (default) = the first section with the event's flag, "
                           "its new flags cleared; 'before' = the last section without it")
            p.add_argument("--walk-in", action="store_true", help="event: targets: start at the nearest 'NPM:' "
                           "navigation jump and walk into the trigger (instead of standing on the event jump)")
            p.add_argument("--advance", type=int, help="pre-event: CROSS every N fields after the start point to step "
                           "the event's dialogue (default 120 for event: targets, 0 = none)")
            p.add_argument("--skip-missing", action="store_true", help="exit 77 without data/, the exe or save2")
    sp.add_parser("selftest")
    pv = sp.add_parser("prove")
    pv.add_argument("--exe", default=str(fxlib.exe_path()))
    pv.add_argument("--out")
    pv.add_argument("--only", nargs="*")
    pv.add_argument("--set", nargs="*", default=["default"], help="default | story | post | enemies (several = in order)")
    pv.add_argument("--resume", action="store_true", help="keep the rows of an earlier OUT/prove.tsv")
    pv.add_argument("--retry-fail", action="store_true", help="with --resume: run the FAIL rows again")
    pv.add_argument("--min-commit-gb", type=float, default=12.0)
    pm = sp.add_parser("provemd")
    pm.add_argument("tsv")
    gr = sp.add_parser("groups")
    gr.add_argument("name", nargs="+")
    a = ap.parse_args(argv)
    if a.cmd == "list":
        return cmd_list(a)
    if a.cmd == "selftest":
        return selftest()
    if a.cmd == "card":
        kind, key = resolve(a.target)
        name, info = make_card(kind, key, a.preset)
        print(f"scenario: card {CARDS / name}: {json.dumps(info)}")
        fid = info.get("id") if kind == "fixed" and not a.before else None
        sp_ = fxlib.FIXTURES / "runs" / "bootlib" / f"{name}.input.txt"
        print("  boot it: python tools\\fixtures\\scenario.py run " + json.dumps(a.target) + " --exe EXE "
              "(finds field control and writes " + str(sp_) + ")")
        if fid:
            print(f"  by hand: set RG_FORCE_ENCOUNTER=fixed:{fid}@{AFTER}, start rg-game --saves <copy of the card>, CONTINUE")
        return 0
    if a.cmd == "run":
        if a.skip_missing and not ((ROOT / "data").is_dir() and Path(a.exe).exists() and (CARDS / "save2").is_dir()):
            print("scenario: SKIP (no data/, exe or cards/save2)")
            return 77
        r = run(a.target, a.exe, a.out, a.shots, a.state, a.before, a.preset, a.oracle, a.fields, shot_at=a.shot_at, advance=a.advance, walk_in=a.walk_in, event_state=a.event_state)
        return 0 if r["verdict"] == "PASS" else 1
    if a.cmd == "provemd":
        print(prove_md(a.tsv))
        return 0
    if a.cmd == "groups":
        import forcebattle
        for gid, nm, mem in forcebattle.holding(" ".join(a.name)):
            print(gid, nm, ", ".join(mem), "  card:", ZONE_CARDS.get(nm.split("_")[0].upper(), "-"))
        return 0
    if a.cmd == "prove":
        return cmd_prove(a)
    return 0


if __name__ == "__main__":
    sys.exit(main())
