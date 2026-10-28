# SPDX-License-Identifier: CC0-1.0
"""The game's own tables the save editor and the card library use (docs/SAVE-FORMAT.md
"Game data the save editor uses").  Read from data/DATA0_0 on first use (gamedata.py,
cfgdump.py) and cached under out/fixtures/gamedata/ (game-derived, never committed).

- phases():         rc/param/phase_param_EN (chapter, sub, phase value, title)
- sections():       rc/param/initial_status5 -- the developers' per-chapter start states
                    (party, levels, money, items, story flags / vars), applied in game by
                    the WorldDataCmd* handlers (data2c_00466030 command table)
- planetarea(p,c,s,v): rc/param/planetarea_matrix5 + _param5 -> (area id, sky id) the map
                    loader takes from party +0x6 / +0x8
- map_jumps():      dbg/map_jump_en.txt -- debug jump points (planet id, position, yaw)
- levelup():        rc/param/chara_levelup_param2 (per character: exp, stat increments)
- charas():         rc/param/chara_param_EN (data id -> name)
"""
from __future__ import annotations

import functools
import re
from pathlib import Path

import cfgdump
import gamedata

CACHE = gamedata.PORT / "out" / "fixtures" / "gamedata"
PAC = "rc/param/param_2_en.pac"


def _bytes(name: str) -> bytes:
    p = CACHE / name.replace("/", "_").replace("\\", "_")
    if not p.exists():
        CACHE.mkdir(parents=True, exist_ok=True)
        p.write_bytes(gamedata.Archive().get(name))
    return p.read_bytes()


def table(member: str):
    """Rows (id, args) of a .cfg.bin inside the param pac, or a standalone file."""
    if member.startswith("rc/") or member.startswith("dbg/"):
        b = _bytes(member)
    else:
        pac = _bytes(PAC)
        for nm, off, size in gamedata.pac_members(pac):
            if nm.lower() == member.lower():
                b = pac[off:off + size]
                break
        else:
            raise KeyError(member)
    return list(cfgdump.parse(b))


@functools.lru_cache(None)
def phases():
    """[(chapter, sub, sub_letter, [(phase value, title)]), ...] in slot order (the 15
    progress slots of StateBlock +0xA are these rows in this order) and chapter titles."""
    rows, titles = [], {}
    ch = None
    for cid, a in table("phase_param_EN.cfg.bin"):
        if cid == 104:
            ch = a[0]
            titles[ch] = a[2]
        elif cid == 106:
            rows.append([ch, a[0], a[1], []])
        elif cid == 108:
            rows[-1][3].append((a[0], a[1]))
    return rows, titles


def progress_slots(chapter: int, sub: int, value: int):
    """The 15 progress values for a story point, as ProgressSetChapter_3cd480 ->
    ProgressReapplyChapter_3cd330 leaves them: chapters before = their last phase,
    after = their first, the current (chapter, sub) = value.  Chapter 8's sub-chapters
    A/B/C before `sub` count as done."""
    rows, _ = phases()
    out = []
    for c, s, _, ph in rows:
        if (c, s) == (chapter, sub):
            out.append(value)
        elif c < chapter or (c == chapter and s < sub):
            out.append(ph[-1][0])
        else:
            out.append(ph[0][0])
    return out


@functools.lru_cache(None)
def sections():
    """{section id: {'name', 'money', 'items': [(slot, item, str)], 'party': [{data id,
    mode, level, exp, hp, mp, equip, abilities}], 'flags': [(n, v)], 'vars': [(i, v)],
    'flags2', 'flags256', 'markers', 'encounter', 'options', 'field'}}"""
    secs = {}
    cur = None
    for cid, a in table("rc/param/initial_status5.cfg.bin"):
        if cid == 100:
            cur = secs[a[0]] = {"id": a[0], "name": a[1], "money": None, "items": [], "party": [],
                                "flags": [], "vars": [], "flags2": [], "flags256": [], "markers": [],
                                "encounter": None, "options": None, "field": None}
        elif cur is None:
            continue
        elif cid == 101:
            cur["money"] = a[0]
        elif cid == 102:
            cur["items"].append(tuple(a))
        elif cid == 103:
            cur["party"].append({"data_id": a[0], "mode": a[1]})
        elif cid == 104:
            cur["party"][-1].update(level=a[0], exp=a[1], hp=a[2], mp=a[3])
        elif cid == 105:
            cur["party"][-1]["equip"] = [x for x in a if isinstance(x, int)]
        elif cid == 106:
            cur["party"][-1]["abilities"] = a[1:1 + a[0]]
        elif cid in (111, 112, 113, 114):
            key = {111: "flags", 112: "vars", 113: "flags2", 114: "flags256"}[cid]
            n = a[0]
            cur[key] += [(a[1 + 2 * i], a[2 + 2 * i]) for i in range(n)]
        elif cid == 115:
            cur["markers"] += a[1:1 + a[0]]
        elif cid == 117:
            cur["encounter"] = a[0]
        elif cid == 109:
            cur["options"] = a
        elif cid == 110:
            cur["field"] = a
    return secs


def section_story_point(sid: int):
    """Section id -> (chapter, sub, phase value): 9050 = ch 9 phase 50, 8120 = ch 8-A
    phase 20, 1021 = ch 1 phase 20 (variant 2), 28010 = Alistia (no chapter)."""
    ch, rest = divmod(sid, 1000)
    if ch == 8:
        sub, v = divmod(rest, 100)
    else:
        sub, v = 0, rest
    return ch, sub, v // 10 * 10


@functools.lru_cache(None)
def planetarea_tables():
    m = {}
    for cid, a in table("planetarea_matrix5.cfg.bin"):
        if cid == 600:
            m[a[0]] = a[1]
    p = {}
    for cid, a in table("planetarea_param5.cfg.bin"):
        if cid == 500:
            p[a[0]] = a
    return m, p


def planetarea(planet: int, chapter: int, sub: int, value: int):
    """(area id, sky id) for party +0x6 / +0x8, or None.  Matrix key = planet * 10^7 +
    chapter * 1000 + sub * 100 + phase value (PlanetAreaMatrixLookupByProgress_3ed840)."""
    m, p = planetarea_tables()
    row = m.get(planet * 10_000_000 + chapter * 1000 + sub * 100 + value)
    if row is None or row not in p:
        return None
    return p[row][1], p[row][2]


@functools.lru_cache(None)
def map_jumps():
    """{id: (planet, x, y, z, yaw, label)}"""
    txt = gamedata.text(_bytes("dbg/map_jump_en.txt"))
    out = {}
    for ln in txt.splitlines():
        m = re.match(r'\s*MAP_JUMP\s+(\d+),\s*(\d+),\s*([-\d.]+)\s*,\s*([-\d.]+)\s*,\s*([-\d.]+)\s*,\s*([-\d.]+)\s*,\s*"(.*)"', ln)
        if m:
            out[int(m.group(1))] = (int(m.group(2)), float(m.group(3)), float(m.group(4)), float(m.group(5)),
                                    float(m.group(6)), m.group(7))
    return out


@functools.lru_cache(None)
def chara_abilities():
    """chara_ability_param3: {chara data id: {ability id: list index (1-based)}} (the list
    CharaLearnAbility_3ad460 finds by the character; bit index-1 of the learned set)."""
    out, cur = {}, None
    for cid, a in table("chara_ability_param3.cfg.bin"):
        if cid == 200:
            cur = out.setdefault(a[0], {})
        elif cid == 202 and cur is not None:
            cur[a[1]] = a[0]
    return out


@functools.lru_cache(None)
def ability_defs():
    """ability_param_EN #4 rows: {id: (m2 passive flag, m3, m4 family, m5 level, name)}."""
    out = {}
    for cid, a in table("ability_param_EN.cfg.bin"):
        if cid == 4 and len(a) >= 7:
            out[a[0]] = (a[3], a[4], a[5], a[6], a[2])
    return out


@functools.lru_cache(None)
def levelup():
    """{data id: {level: (exp, [hp, ap, s2, s3, s4] increments)}}"""
    out, cur, lv = {}, None, None
    for cid, a in table("chara_levelup_param2.cfg.bin"):
        if cid == 4:
            cur = out[a[0]] = {}
        elif cid == 301:
            lv = a[0]
            cur[lv] = [a[1], None]
        elif cid == 302:
            cur[lv][1] = list(a)
    return out


def level_stats(data_id: int, level: int):
    """[hp, ap, s2, s3, s4] at `level` (level 1 row = base, then increments)."""
    t = levelup()[data_id]
    s = [0] * 5
    for lv in range(1, level + 1):
        if lv in t and t[lv][1]:
            s = [x + y for x, y in zip(s, t[lv][1])]
    return s


@functools.lru_cache(None)
def charas():
    return {a[0]: a[2] for cid, a in table("chara_param_EN.cfg.bin") if cid == 4}


@functools.lru_cache(None)
def items():
    """{item id: {'name', 'cat', 'weapon': [5 bytes] or None, 'special': gauge or 0}} from
    item_param_EN (#4 row: id, '', name, category, ...; #106 weapon data, ItemWeaponSetup_3d3730
    copies these five bytes to the item; #114 special-weapon gauge, ItemSpecialWeaponGaugeFill_3d2f90).
    Categories: 0 sword, 1 second weapon, 2 clothes, 3 shield, 4 heal, 5 boosters, 8-10 / 14-19 key
    and quest items, 11 materials, 12 cages, 13 feed, 20 insects, 21 misc.  'code' = def +0x4
    (cages: 1200 Insector Trap = 0x4B0, 1201 Rearing Cage = 0x4B1; insects 2000 + species),
    'index' = def +0x3 (cage number 0..2: InvFindByRecKey_3c8140), 'insect' = #115 data."""
    out, cur = {}, None
    for cid, a in table("item_param_EN.cfg.bin"):
        if cid == 4:
            cur = out[a[0]] = {"name": a[2], "cat": a[3], "weapon": None, "special": 0,
                               "code": a[4], "index": a[5], "insect": None}
        elif cur is None:
            continue
        elif cid == 106:
            cur["weapon"] = list(a[:5])
        elif cid == 115 and len(a) >= 27:
            # insect data (ItemDataCmdInsectSetParams_40ca00 -> def +0x20 record): insector
            # param id, HP lo/hi, attack lo/hi, defense lo/hi, six stat (lo, hi) pairs,
            # growth lo/hi, 3 shorts, 3 favourite feed item ids
            cur["insect"] = {"param": a[0], "hp": a[1:3], "atk": a[3:5], "def": a[5:7],
                             "stats": [a[7 + 2 * i:9 + 2 * i] for i in range(6)], "growth": a[19:21],
                             "w": a[21:24], "feed": a[24:27]}
        elif cid == 114 and a and isinstance(a[0], (int, float)):
            cur["special"] = a[0]
    return out


STACK_CATS = {4, 5, 7, 11, 13, 21}


def item_kind(item_id: int):
    """Inventory object kind (= the kind-11 chunk version, InvObjCreateByKind_3c75c0) the game
    would create for an item (InvObjCreateForItem_3c7110): 2 weapon, 3 special weapon, 1 stack,
    0 plain, 4 insect (ItemDefIsInsect_40e340), 5 Insector Trap (def code 0x4B0), 6 Rearing
    Cage (0x4B1); None for an unknown item."""
    it = items().get(item_id)
    if it is None:
        return None
    if it["weapon"] is not None:
        return 3 if it["special"] else 2
    if it["cat"] == 20:
        return 4
    if it["cat"] == 12:
        return {1200: 5, 1201: 6}.get(it["code"])
    return 1 if it["cat"] in STACK_CATS else 0


@functools.lru_cache(None)
def flag_names():
    """{story flag: name} (bit_flag_param_EN: 'EV01-0010', 'Help Sheet: ...', ...)."""
    return {a[0]: a[1] for cid, a in table("bit_flag_param_EN.cfg.bin") if cid == 203}


@functools.lru_cache(None)
def var_names():
    """{story var: name} (short_flag_param_EN: 5 'Insectron Rank', ...)."""
    return {a[0]: a[1] for cid, a in table("short_flag_param_EN.cfg.bin") if cid == 303}
