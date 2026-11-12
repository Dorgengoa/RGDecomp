#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Place the party where a random-encounter group can be met, and start that battle (lane
cactugus, 2026-11-11; docs/TEST-FIXTURES.md "Area placement").

    python tools/fixtures/areaplace.py where Cactugus            # tables / locations / boxes, no run
    python tools/fixtures/areaplace.py card Cactugus --exe EXE   # card + location self-check
    python tools/fixtures/areaplace.py run Cactugus --exe EXE [--oracle ORACLE_EXE] [--shots +16,+64,+148]
    python tools/fixtures/areaplace.py run 2506 --exe EXE        # a group id works too

The chain the game uses (all read from the game's own data):

  encount_group G  <- listed (#204) in area table T  (rc/param/planet/<pl>_2_en.pac
                      <PL>_encount_param_EN; #200 = location L, #201 = condition)
  location L       -> map box ids (#900 of <PL>_location_a_param_EN)
  map box B        -> MAPBOX_DEF in the planet map's block file map/<dir>/<map>.md (local units
                      x 20 = world units; the same file's BLOCK_START ... MB_ZONE gives the zone)

At run time the party object (CharaSys D_004837C0 +0x18) keeps the locations it stands in
(+0x3A count, +0x3E (key, location) pairs; key = planet) and PartySelectEncounter_3c9c30 puts
the table it selects at +0x7E key / +0x80 table / +0x82 location; the encounter distance
(CharaSys +0x20 object, +0x20 double) runs down only while the party walks inside a location
that has a table, then CharaSysStartQueuedEncounterMaybe_3a54f0 rolls the table's groups.

`card`: copy of save2 + saveedit patch: the story section of the zone's card-library card
(scenario.ZONE_CARDS; JR05 -> ch03_falls = 3040), spawn at the box centre (y = the nearest debug
jump's floor + 50, the game drops the party onto the floor), yaw along the box's long side.
Self-check (boot, status dump of the party's location list): the party stands in L and selected
table T, else the next candidate point (box quarters, then the next box / table).

`run`: the card, field control from pass 1, then pacing forward / back (stick lines every 120
fields) with RG_FORCE_ENCOUNTER=G: the table's own weighted roll still runs and its result is
replaced by G's entry when T lists G (override CharaSysEncounterPickFormationMaybe_3a5090,
FORCE-API.md).  PASS = a battle reaches the fight phase 7/201 and the enemy records name the
enemy.  --oracle: the same run on the oracle twin (RG_RENDER=emu) and shots at the same fields;
--shots: fight + offsets on both, then tools/native/shotpsnr.py oracle vs native.
Outputs out/fixtures/runs/areaplace/<card>/ (areaplace.json, logs, nat/ emu/ shots).
"""
from __future__ import annotations

import argparse
import json
import math
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT / "tools" / "native"))
import cfgdump  # noqa: E402
import fxlib  # noqa: E402
import gamedata  # noqa: E402
import rgdata  # noqa: E402

CARDS = fxlib.FIXTURES / "cards"
RUNS = fxlib.FIXTURES / "runs" / "areaplace"
CACHE = fxlib.FIXTURES / "gamedata" / "areaplace_boxes_mdbin.json"
SCALE = 20.0          # MAPBOX_DEF / MB_LOAD local units -> world units (checked: Mud Whooper's
                      # spring box 4230 holds the EV02-0150 jump; Cactugus' 5070 holds the probe)
PACE = 30             # fields per stick line of the pacing walk (one leg of the square)
PACE_FIELDS = 3000    # pacing length after control
PLACE_RETRIES = 3     # placed cards walked before a FAIL (lane scenario3)
S = chr(92)


# ---------------------------------------------------------------- game data
def groups():
    out = {}
    for k, r in rgdata.table("encount_group_param_EN.cfg.bin"):
        if k == 4:
            out[r[0]] = (r[1], [])
        elif k == 102 and out:
            out[list(out)[-1]][1].append(r[0])
    return out


def resolve(target: str) -> tuple[int, str]:
    """(group id, enemy name to expect).  'Cactugus' -> the '<zone>_Cactugus Group', else the
    first group holding the enemy."""
    import progression
    names = progression.monster_names()
    gs = groups()
    if str(target).isdigit():
        gid = int(target)
        if gid not in gs:
            raise SystemExit(f"areaplace: no encount_group {gid}")
        return gid, names.get(gs[gid][1][0], str(gs[gid][1][0])) if gs[gid][1] else ""
    ids = {k for k, v in names.items() if v.lower() == target.lower()}
    cand = [g for g, (nm, mem) in gs.items() if ids & set(mem)]
    if not cand:
        raise SystemExit(f"areaplace: no encounter group holds {target!r}")
    exact = [g for g in cand if gs[g][0].lower().endswith(f"_{target.lower()} group")]
    return (exact or cand)[0], names[next(iter(ids))]


def tables_for(gid: int):
    """Area tables listing the group: [{id, name, planet, pl, location, condition, groups}],
    'always' tables first."""
    import progression
    by_id, by_code = progression.planets()
    rows = [r for r in progression.encounter_rows() if any(g == gid for g, _ in r["groups"])]
    for r in rows:
        r["pl"] = by_id.get(r["planet"], ("", ""))[0].lower() if r["planet"] != "" else ""
    return sorted(rows, key=lambda r: (r["condition"] != "always", r["id"]))


def location_boxes(pl: str, loc: int):
    """map box ids of a location (#900 of <PL>_location_a_param_EN)."""
    b = gamedata.Archive().get(f"rc{S}param{S}planet{S}{pl}_2_en.pac")
    for nm, off, size in gamedata.pac_members(b):
        if nm.lower() == f"{pl}_location_a_param_en.cfg.bin":
            cur = None
            for k, r in cfgdump.parse(b[off:off + size]):
                if k == 4:
                    cur = r[0]
                elif k == 900 and cur == loc:
                    return list(r[1:1 + r[0]])
    return []


def mapboxes():
    """{map pac: {"zones": [..], "boxes": {id: [x0,y0,z0,x1,y1,z1] world}}} of every map block
    definition the game loads (cached).  Source = the compiled `<map>.md.bin` member of
    map/<dir>/<map>.pac (cfg keys 1205 MB_ZONE, 1301 MAPBOX_DEF [id, name, min xyz, max xyz]);
    lane scenario3 2026-11-11: the loose text `.md` files are stale sources (map/m11/m11.md =
    Alistia has 1 box and no zones, its md.bin 40 boxes in AR01-AR04; m07_area02 26 vs 25)."""
    if CACHE.exists():
        return json.loads(CACHE.read_text())
    a = gamedata.Archive()
    out = {}
    for n in sorted(a.files):
        if not (n.lower().startswith("map" + S) and n.lower().endswith(".pac")):
            continue
        try:
            b = a.get(n)
            mem = list(gamedata.pac_members(b))
        except Exception:   # noqa: BLE001 -- not a member pac
            continue
        for nm, off, size in mem:
            if not nm.lower().endswith(".md.bin"):
                continue
            recs = list(cfgdump.parse(b[off:off + size]))
            zones = sorted({r[0] for k, r in recs if k == 1205 and r})
            boxes = {}
            for k, r in recs:
                if k == 1301 and len(r) >= 8:
                    boxes.setdefault(str(r[0]), [float(x) * SCALE for x in r[2:8]])
            out[n] = {"zones": zones, "boxes": boxes}
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    CACHE.write_text(json.dumps(out))
    return out


def zone_of(gid: int) -> str:
    return groups()[gid][0].split("_")[0].upper()


def boxes_for(zone: str, ids, pl: str = ""):
    """[(box id, [x0,y0,z0,x1,y1,z1])] from the block file that defines the zone (box ids are
    per map: else a map of the table's planet code `pl`, e.g. 'mg', then any map)."""
    mb = mapboxes()
    files = [f for f, v in mb.items() if zone in v["zones"]]
    files += [f for f, v in mb.items() if pl and f not in files and any(z.startswith(pl.upper()) for z in v["zones"])]
    files = files or list(mb)
    out = []
    for i in ids:
        for f in files:
            if str(i) in mb[f]["boxes"]:
                out.append((i, mb[f]["boxes"][str(i)]))
                break
    return out


def floor_y(planet: int, x: float, z: float, box):
    """Spawn height: the nearest debug jump inside the box's y range on the planet (its floor)
    + 50; the box's lower bound + 500 when none."""
    js = [(math.dist((v[1], v[3]), (x, z)), v[2]) for v in rgdata.map_jumps().values()
          if v[0] == planet and box[1] <= v[2] <= box[4]]
    return (min(js)[1] if js else box[1] + 500) + 50


def candidates(box):
    x0, _, z0, x1, _, z1 = box
    cx, cz = (x0 + x1) / 2, (z0 + z1) / 2
    yield cx, cz
    for fx, fz in ((0.25, 0.5), (0.75, 0.5), (0.5, 0.25), (0.5, 0.75), (0.25, 0.25), (0.75, 0.75)):
        yield x0 + (x1 - x0) * fx, z0 + (z1 - z0) * fz


# Ghost ship EX (planet 10, map m07_area02): one location box (1) spans all 100 floors; the
# floor number is the party's map-area id - 20000 (PartyGetFloorNum_3cb000: party +0x04 == 10,
# +0x30 in 20001..20999, set by MapUpdatePlayerLocationMaybe_1ff710) and the floor tables'
# condition reads it.  Floors stand 1200 units apart: the EX floor jumps (dbg/map_jump_en.txt
# 3012-3020 = 20F..100F) sit at y = (F - 15) * 1200.
EX_PLANET = 10
EX_FLOOR_DY = 1200.0


def floor_range(cond: str):
    m = re.search(r"floor >= (\d+)", cond or "")
    n = re.search(r"floor <= (\d+)", cond or "")
    return (int(m.group(1)), int(n.group(1)) if n else int(m.group(1))) if m else None


def floor_points(planet: int, cond: str):
    """Spawn points (x, y, z) on the floors a 'floor' table condition asks for: the x / z of every
    EX floor jump (the floor layouts share them) at that floor's height."""
    fr = floor_range(cond)
    if planet != EX_PLANET or not fr:
        return []
    js = [v for k, v in sorted(rgdata.map_jumps().items()) if v[0] == EX_PLANET and 3012 <= k <= 3020]
    pts = []
    for f in range(fr[0], fr[1] + 1):
        for v in js:
            pts.append((v[1], (f - 15) * EX_FLOOR_DY + 50, v[3], f))
    return pts


def section_for(zone: str, planet: int):
    """(sections, extra saveedit args) of the zone's card-library card."""
    import cardlib
    import scenario
    card = scenario.ZONE_CARDS.get(zone)
    if card is None:   # a library card on the same planet
        js = rgdata.map_jumps()
        card = next((k for k, v in cardlib.LIBRARY.items() if isinstance(v[1], int) and js.get(v[1], (0,))[0] == planet),
                    None)
    if card is None:
        raise SystemExit(f"areaplace: no card-library card for zone {zone} / planet {planet}")
    v = cardlib.LIBRARY[card]
    return list(v[0]), (list(v[3]) if len(v) > 3 else []), card


# ---------------------------------------------------------------- probes
def probe_spec(exe: Path, enemies=True) -> str:
    import autobattle
    r = autobattle._sym_rvas(exe)
    cs = r["D_004837C0"]
    mine = f"p0x{cs:X}/0x18+0x3A:0x4A,p0x{cs:X}/0x20+0:0x28"
    return (autobattle.dump_spec(exe) + "," + mine) if enemies else mine


def parse_loc(log: str):
    """{field: (locations [(key, loc)], (key, table, loc) selected, encounter distance)}"""
    out = {}
    for ln in log.splitlines():
        if not ln.startswith("DUMP field="):
            continue
        w = ln.split()
        if len(w) < 5 or w[-1] == "NULL":
            continue
        try:
            b = bytes.fromhex("".join(w[4:]))
        except ValueError:
            continue
        f = int(w[1].split("=")[1])
        if len(b) == 0x4A:
            n2 = struct.unpack_from("<h", b, 0)[0]
            t2 = struct.unpack_from("<16h", b, 4)
            sel = struct.unpack_from("<3h", b, 0x44)
            out[f] = [[(t2[2 * i], t2[2 * i + 1]) for i in range(max(0, min(n2, 8)))], sel, None]
        elif len(b) == 0x28 and f in out:
            out[f][2] = struct.unpack_from("<d", b, 0x20)[0]
    return out


def boot(card, script, exe, end, env, tag, out, every=10, extra=()):
    import bootcheck
    return bootcheck.run_status(card, script, exe, end, every, list(extra), env, tag, out)


def pace_script(control, until=None):
    """Stick lines from control + 60: a small square (forward, right, back, left, PACE fields
    each), so the party keeps walking (the encounter distance runs down) but stays near the
    spawn point inside its location (lane scenario3: the earlier forward / back walk drifted out
    of the location in Mother's Lair and stuck in a waterway in the Cancer King ruins)."""
    import scenario
    ex, k, d = [], control + 60, 0
    end = until or control + PACE_FIELDS
    legs = (("128 0", "forward"), ("255 128", "right"), ("128 255", "back"), ("0 128", "left"))
    while k < end:
        xy, nm = legs[d % 4]
        ex.append(f"#!stick {k} {k + PACE - 1} {xy}  # areaplace: pace {nm}")
        k += PACE
        d += 1
    return scenario.boot_script(control, ex)


# ---------------------------------------------------------------- card
def points(zone, tabs):
    """Candidate spawn points [(table, box id, box, x, y, z, yaw)] in table order: EX floor points
    (floor_points) first, then each location box's centre / quarters."""
    for t in tabs:
        planet = t["planet"]
        bx = boxes_for(zone, location_boxes(t["pl"], int(t["location"])), t["pl"])
        for x, y, z, f in floor_points(planet, t["condition"]):
            for bid, box in bx:
                if box[0] <= x <= box[3] and box[1] <= y <= box[4] and box[2] <= z <= box[5]:
                    yield t, bid, box, x, y, z, 0.0
                    break
        if floor_range(t["condition"]) and planet == EX_PLANET:
            continue    # the box's centre is no floor of the asked range
        for bid, box in bx:
            for x, z in candidates(box):
                yaw = 0.0 if (box[5] - box[2]) >= (box[3] - box[0]) else math.pi / 2
                yield t, bid, box, x, floor_y(planet, x, z, box), z, yaw


def make_card(target: str, exe: Path, out: Path | None = None, quiet=False, max_tries=8, skip=0):
    """-> info dict with card, control, location, table (or verdict FAIL).  `skip`: start after
    that many candidate points (run() retries the next point when a placed card met no battle)."""
    import bootcheck
    import saveedit
    gid, expect = resolve(target)
    zone = zone_of(gid)
    tabs = tables_for(gid)
    if not tabs:
        raise SystemExit(f"areaplace: group {gid} is in no area table")
    name = f"ap_{gid}"
    out = Path(out or RUNS / name)
    out.mkdir(parents=True, exist_ok=True)
    info = {"target": target, "group": gid, "group_name": groups()[gid][0], "expect": expect, "zone": zone,
            "card": name, "tries": []}
    listing = {r["id"] for r in tabs}   # any table listing the group will do (lane scenario3)
    tries = 0
    for t, bid, box, x, y, z, yaw in points(zone, tabs):
        if tries >= skip + max_tries:
            break
        tries += 1
        if tries <= skip:
            continue
        pl, planet = t["pl"], t["planet"]
        secs, extra, lib = section_for(zone, planet)
        card = CARDS / name
        saveedit.cmd_copy(argparse.Namespace(src=str(CARDS / "save2"), dst=str(card)))
        args = sum((["--section", str(s)] for s in secs), []) + extra
        rc = saveedit.main(["patch", str(card)] + args +
                           ["--spawn", f"{planet}:{x:.2f},{y:.2f},{z:.2f},{yaw:.3f}", "--no-help"])
        if rc:
            raise SystemExit(f"areaplace: saveedit patch failed ({rc})")
        rc, log, st = boot(name, bootcheck.lib_script(None), exe, 4700,
                           {"RG_STATUS_DUMP": probe_spec(exe, enemies=False)}, name + "_place", out)
        ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v[1] == "6/100"), None)
        loc = parse_loc(log)
        last = loc[max(loc)] if loc else None
        ok = bool(last and ctl and last[1][1] in listing)
        rec = {"try": tries, "table": last[1][1] if ok else t["id"], "aimed_table": t["id"],
               "table_name": next((r["name"] for r in tabs if ok and r["id"] == last[1][1]), t["name"]),
               "location": last[1][2] if ok else t["location"], "box": bid,
               "spawn": [round(x, 1), round(y, 1), round(z, 1), round(yaw, 3)], "control": ctl,
               "locations": last[0] if last else None, "selected": list(last[1]) if last else None,
               "ok": ok, "section": secs, "lib_card": lib}
        info["tries"].append(rec)
        if not quiet:
            print(f"areaplace: try {tries} table {t['id']} loc {t['location']} box {bid} spawn "
                  f"({x:.0f},{y:.0f},{z:.0f}) -> control {ctl} at {rec['locations']} selected {rec['selected']}"
                  f" {'OK' if ok else 'no'}", flush=True)
        if ok:
            info.update({k: rec[k] for k in ("try", "table", "table_name", "location", "box", "spawn", "control",
                                             "section", "lib_card")})
            info["verdict"] = "PLACED"
            (card / "areaplace.json").write_text(json.dumps(info, indent=1), encoding="utf-8")
            (out / "areaplace.json").write_text(json.dumps(info, indent=1), encoding="utf-8")
            return info
    info.update(verdict="FAIL", why=f"no candidate point selected a table listing group {gid} ({tries} tries)")
    (out / "areaplace.json").write_text(json.dumps(info, indent=1), encoding="utf-8")
    return info


# ---------------------------------------------------------------- run
def run(target, exe, oracle=None, shots=None, out=None, quiet=False, keep_card=False):
    import enc_hunt
    t0 = time.time()
    exe = Path(exe).resolve()
    gid, expect = resolve(target)
    out = Path(out or RUNS / f"ap_{gid}")
    card = CARDS / f"ap_{gid}"
    info = None
    if keep_card and (card / "areaplace.json").exists():
        info = json.loads((card / "areaplace.json").read_text())
    if not info:
        info = make_card(target, exe, out, quiet)
    walks = []
    for attempt in range(PLACE_RETRIES):
        if info.get("verdict") != "PLACED":
            if walks:
                info.update(walks=walks, verdict="FAIL", why=walks[-1]["why"])
            return _finish(info, out, t0, quiet)
        ctl = info["control"]
        script = pace_script(ctl)
        env = {"RG_FORCE_ENCOUNTER": str(gid), "RG_STATUS_DUMP": probe_spec(exe)}
        rc, log, st = boot(info["card"], script, exe, ctl + PACE_FIELDS + 400, env, info["card"] + f"_g{gid}", out)
        force = [ln for ln in log.splitlines() if ln.startswith("FORCEENC")]
        enc, fight, found = enc_hunt.enemies(log, enc_hunt.monster_names())
        info.update(force=force[:3], encounter=enc, fight=fight, found=found, exit=rc, crash=fxlib.crash_report(log, exe))
        if info["crash"]:
            info.update(verdict="FAIL", why="crash")
        elif enc is None:
            info.update(verdict="FAIL", why="no encounter on the pacing walk")
        elif fight is None:
            info.update(verdict="FAIL", why=f"battle at {enc}, no fight phase")
        elif expect and not any(expect.lower() in x.lower() for x in found):
            info.update(verdict="FAIL", why=f"battle has {found}, want {expect} ({force[:1]})")
        else:
            info["verdict"] = "PASS"
        # placement causes (no battle on the walk, or the walk left for a table without the
        # group): the next candidate point; a crash or a wrong battle stays a FAIL
        if info["verdict"] == "PASS" or info["crash"] or not (enc is None or not any("found" in f and "not found" not in f
                                                                                      for f in force)):
            break
        walks.append({k: info.get(k) for k in ("try", "table", "location", "spawn", "encounter", "why")})
        if not quiet:
            print(f"areaplace: walk from try {info.get('try')} -> {info['why']}; next candidate point", flush=True)
        if attempt + 1 < PLACE_RETRIES:
            nxt = make_card(target, exe, out, quiet, skip=info.get("try", 0))
            if nxt.get("verdict") != "PLACED":
                break
            info = dict(nxt, walks=walks)
    if walks:
        info["walks"] = walks
    sp = fxlib.FIXTURES / "runs" / "bootlib" / f"{info['card']}_g{gid}.input.txt"
    info["commands"] = [
        f"headless: $env:RG_FORCE_ENCOUNTER='{gid}'; python tools\\fixtures\\run_from.py --boot-save {info['card']} "
        f"--input {sp} --exe EXE --fields {(fight or ctl) + 600}",
        f"windowed: same + --windowed (the party walks a small square from field {ctl + 60})",
        f"play it yourself: copy {card} to a saves dir, set RG_FORCE_ENCOUNTER={gid}, CONTINUE -> FILE 01, walk "
        f"around ({info.get('table_name', '')}): the next random encounter there is {info['group_name']}",
    ]
    if info["verdict"] == "PASS" and (shots or oracle):
        offs = [int(x) for x in (shots or "+16,+64,+148").replace("+", "").split(",") if x]
        at = [fight + o for o in offs]
        for kind, x in (("nat", exe), ("emu", Path(oracle).resolve() if oracle else None)):
            if x is None:
                continue
            d = out / kind
            d.mkdir(parents=True, exist_ok=True)
            extra = sum((["--shot", f"{f}:{d / f'f{f:05d}.png'}"] for f in at), [])
            e = dict(env, RG_STATUS_DUMP=probe_spec(x))   # RVAs from that exe's own map
            if kind == "emu":
                e["RG_RENDER"] = "emu"
            rc2, log2, _ = boot(info["card"], script, x, max(at) + 2, extra=extra, env=e,
                                tag=info["card"] + f"_g{gid}_{kind}", out=out)
            enc2, fight2, found2 = enc_hunt.enemies(log2, enc_hunt.monster_names()) if kind == "emu" else (enc, fight, found)
            info[f"{kind}_shots"] = [str(d / f"f{f:05d}.png") for f in at]
            if kind == "emu":
                info.update(oracle_encounter=enc2, oracle_fight=fight2, oracle_found=found2)
        if oracle:
            p = subprocess.run([sys.executable, str(ROOT / "tools/native/shotpsnr.py"), str(out / "emu"), str(out / "nat")],
                               capture_output=True, text=True, errors="replace")
            info["psnr"] = p.stdout.strip().splitlines()
    return _finish(info, out, t0, quiet)


def _finish(info, out, t0, quiet):
    info["seconds"] = round(time.time() - t0)
    out.mkdir(parents=True, exist_ok=True)
    (out / "areaplace.json").write_text(json.dumps(info, indent=1), encoding="utf-8")
    if not quiet:
        print(f"areaplace: {info.get('target')} group {info.get('group')} ({info.get('group_name')}) -> "
              f"{info['verdict']}" + (f" ({info['why']})" if info.get("why") else ""))
        for k in ("table", "location", "spawn", "control", "encounter", "fight", "found", "force", "psnr", "commands"):
            if info.get(k) is not None:
                v = info[k]
                print(f"  {k}: " + ("\n    ".join(v) if k in ("psnr", "commands") else str(v)))
    return info


def cmd_where(target):
    gid, expect = resolve(target)
    zone = zone_of(gid)
    print(f"group {gid} {groups()[gid][0]} (zone {zone}), expect {expect}")
    for t in tables_for(gid):
        ids = location_boxes(t["pl"], int(t["location"]))
        print(f"  table {t['id']} {t['name']!r} [{t['condition']}] location {t['location']} boxes {ids} "
              f"groups {t['group_ids']}")
        for bid, b in boxes_for(zone, ids):
            print(f"    box {bid}: x {b[0]:.0f}..{b[3]:.0f}  y {b[1]:.0f}..{b[4]:.0f}  z {b[2]:.0f}..{b[5]:.0f}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    w = sub.add_parser("where")
    w.add_argument("target")
    c = sub.add_parser("card")
    c.add_argument("target")
    c.add_argument("--exe", required=True)
    r = sub.add_parser("run")
    r.add_argument("target")
    r.add_argument("--exe", required=True)
    r.add_argument("--oracle")
    r.add_argument("--shots", help="fight offsets, e.g. +16,+64,+148 (default with --oracle)")
    r.add_argument("--out")
    r.add_argument("--keep-card", action="store_true", help="reuse a placed card (skip the placement boots)")
    a = ap.parse_args(argv)
    if a.cmd == "where":
        cmd_where(a.target)
        return 0
    import bootcheck
    exe = bootcheck.snapshot_exe(Path(a.exe))
    if a.cmd == "card":
        info = make_card(a.target, exe)
        return 0 if info["verdict"] == "PLACED" else 1
    oracle = bootcheck.snapshot_exe(Path(a.oracle)) if a.oracle else None
    info = run(a.target, exe, oracle, a.shots, a.out, keep_card=a.keep_card)
    return 0 if info["verdict"] == "PASS" else 1


if __name__ == "__main__":
    sys.exit(main())
