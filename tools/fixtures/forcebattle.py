#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Random-encounter group forcing: library module (no CLI).  Entry point for users:
`python tools/fixtures/scenario.py run enemy:NAME --exe EXE` (and `scenario.py groups NAME`);
docs/TEST-FIXTURES.md "Scenarios" / "Forced battles", out/scenario/FORCE-API.md.

The `GROUP` form of $RG_FORCE_ENCOUNTER (default unset = generated bodies, run hash unchanged):
override CharaSysEncounterPickFormationMaybe_3a5090 (lane cactugus 2026-11-11; parser
`rg_force_encounter_id` in the CharaSysEncounterStartGroupMaybe_3a5010 override): a RANDOM
encounter whose area table (the encount_param record the party's location selected) LISTS group
GROUP starts GROUP -- the table's weighted roll runs unchanged, its result is replaced by GROUP's
entry; a table without GROUP keeps its roll ("not found, kept").  The earlier substitution in
3a5010 (lane missnrm3) looked the id up as an AREA TABLE id and never forced a group; the inert 3a54f0 /
3a5890 overrides were deleted 2026-11-12 (lane quiet).  Story / fixed battles never pass there (their form is
`fixed:ID[@N]`, rg_game_main.c).  $RG_FORCE_ENCOUNTER_LOG=1 prints a `FORCEENC` line per pick.

So the party must walk in a location whose table lists the group: scenario.py run_enemy uses
tools/fixtures/areaplace.py (lane cactugus: places the party there) and falls back to this
module's zone-card box walk (`run_group` with scenario.ZONE_CARDS), which forces the group only
where the card's walk crosses such a location.

    groups()                 -> [(group id, name, [monster ids])]
    resolve(NAME | ID)       -> group id ('Cactugus': the '<zone>_<Name> Group', else the first holding it)
    holding(NAME)            -> [(group id, name, [member names])] for a name substring
    run_group(card, exe, out, gid, control, ..) -> dict (verdict, why, encounter, fight, found)
"""
from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "fixtures"))
sys.path.insert(0, str(ROOT / "tools" / "native"))
import enc_hunt  # noqa: E402
import rgdata  # noqa: E402


def groups():
    """[(group id, name, [monster ids])] of encount_group_param_EN."""
    out = []
    for kind, r in rgdata.table("encount_group_param_EN.cfg.bin"):
        if kind == 4:
            out.append((r[0], r[1], []))
        elif kind == 102 and out:
            out[-1][2].append(r[0])
    return out


def zone(gid):
    """Zone prefix of a group ('JR05')."""
    return next((g[1].split("_")[0].upper() for g in groups() if g[0] == gid), "")


def resolve(target: str):
    if str(target).isdigit():
        return int(target)
    names = enc_hunt.monster_names()
    ids = {k for k, v in names.items() if v.lower() == target.lower()}
    cand = [g for g in groups() if ids & set(g[2])]
    if not cand:
        raise SystemExit(f"forcebattle: no encounter group holds {target!r}")
    exact = [g for g in cand if g[1].lower().endswith(f"_{target.lower()} group")]
    return (exact or cand)[0][0]


def holding(name: str):
    names = enc_hunt.monster_names()
    ids = {k for k, v in names.items() if name.lower() in v.lower()}
    return [(gid, nm, [names.get(m, str(m)) for m in mem]) for gid, nm, mem in groups() if ids & set(mem)]


def walk_script(control, shift=0, cut=None):
    """bootcheck's card-library script for field control `control` (menu, walk, box walk:
    random encounters roll on the walk); the walk starts `shift` fields later; `cut` ends the
    stick lines before that field."""
    import bootcheck
    L = []
    for ln in bootcheck.lib_script(control).splitlines():
        t = ln.split()
        if ln.startswith("#!stick") and len(t) >= 5 and t[1] != "1":
            a, b = int(t[1]), int(t[2])
            if shift and a >= control + 340:
                a, b = a + shift, b + shift
            if cut is not None:
                if a >= cut:
                    continue
                b = min(b, cut - 1)
            ln = " ".join(["#!stick", str(a), str(b)] + t[3:])
        L.append(ln)
    return "\n".join(L) + "\n"


def run_group(card, exe, out, gid, control, shift=0, expect=None, fields=2600, env=None, every=10):
    """Boot `card` (a library / scenario card name) with the box walk from field control
    `control` and RG_FORCE_ENCOUNTER=gid; -> dict with verdict PASS when a battle reaches the
    fight phase and (with `expect`) an enemy record names it.  `why` names the cause on FAIL:
    'group not loaded on this map' (card in the wrong zone), 'no encounter roll' (no random
    encounter on the walk), 'no fight phase', 'battle has ..'."""
    import autobattle
    import bootcheck
    import fxlib
    out = Path(out)
    out.mkdir(parents=True, exist_ok=True)
    e = {"RG_FORCE_ENCOUNTER": str(gid), "RG_STATUS_DUMP": autobattle.dump_spec(Path(exe))}
    e.update(env or {})
    name = Path(card).name
    rc, log, st = bootcheck.run_status(name, walk_script(control, shift), exe, control + fields, every, [], e,
                                       name + f"_g{gid}", out)
    force = [ln for ln in log.splitlines() if ln.startswith("FORCEENC")]
    enc, fight, found = enc_hunt.enemies(log, enc_hunt.monster_names())
    res = {"group": gid, "zone": zone(gid), "force": force[:1], "encounter": enc, "fight": fight, "found": found,
           "exit": rc, "crash": fxlib.crash_report(log, exe)}
    if res["crash"]:
        res.update(verdict="FAIL", why="crash")
    elif force and not any("(found" in ln for ln in force):
        # the battle is the game's own roll (it may still hold the expected enemy: not a proof)
        res.update(verdict="FAIL", why=f"group {gid} not in the walked area's table (the game's own roll: "
                                       f"{', '.join(dict.fromkeys(x.split('@')[0] for x in found)) or '-'})")
    elif enc is None and not force:
        res.update(verdict="FAIL", why="no encounter roll on the walk")
    elif fight is None:
        res.update(verdict="FAIL", why=f"battle at {enc}, no fight phase")
    elif expect and not any(expect.lower() in x.lower() for x in found):
        res.update(verdict="FAIL", why=f"battle has {found}, want {expect}")
    else:
        res["verdict"] = "PASS"
    return res
