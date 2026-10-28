# SPDX-License-Identifier: CC0-1.0
"""The card library: manufactured game saves across the story (docs/TEST-FIXTURES.md
"Card library").  Each card = the route's own save (cards/save2) + saveedit.py patch:

- the story point: one or more initial_status5 sections (rgdata.sections(): the developers'
  per-chapter start states: party, levels, equipment, items, money, story flags / vars;
  chapter and progress follow from the section id),
- a spawn point from the game's debug jump table (dbg/map_jump_en.txt, rgdata.map_jumps())
  or an event's end position (rc/param/event_param5) -- planet id + position + yaw; the
  area / sky ids come from planetarea_matrix5 for that planet at that story point,
- --no-help (tutorial pop-ups marked seen).

Booted by tools/trace/goldens/boot_lib.input.txt (CONTINUE, recap, walk, main menu, box
walk for an encounter); milestones fxlib.LIB_MS.  `saveedit.py make` builds them all,
`bootcheck.py --lib` checks them.
"""

# name: (sections, spawn, what[, extra patch args])   spawn = map jump id, or (planet, x, y, z, yaw)
# (transporter positions: rc/param/planet/<pl>_2_en.pac <PL>_transp_param_EN, cfgdump.py)
LIBRARY = {
    "ch01_salgin": ([1020], 1, "Ch1 20 'Traveling with Desert Claw': Rosa, Salgin, in front of the church"),
    "ch01_residential": ([1030], 5011, "Ch1 30 'To the Residential Area': Rosa, Salgin streets (signboard)"),
    "ch02_dorgenark": ([2010], 902, "Ch2 10 'Off Rosa and Belowdecks': the Dorgenark, bridge (planet 1)"),
    "ch02_juraika": ([2020], 2, "Ch2 20 'Searching the Jungle': Juraika, jungle entrance"),
    "ch03_burkaqua": ([3010], 23, "Ch3 10 'Searching Burkaqua': Juraika, the chief's house"),
    "ch03_falls": ([3040], 5106, "Ch3 40 'To the Altar by the Falls': Juraika, waterfall area (signboard)"),
    "ch04_zerard": ([4010], 3, "Ch4 10 'To the Galaxy Corporation': Zerard, central plaza"),
    "ch04_prison": ([4020], 1301, "Ch4 20 'Escaping from Prison': Zerard prison, B15 route"),
    "ch05_factory": ([5020], 5203, "Ch5 20 'The Factory': Zerard, Insectron venue / factory district"),
    "ch06_vedan": ([6030], 4, "Ch6 30 'Searching Myna': Vedan, Myna path"),
    "ch06_mines": ([6040], 44, "Ch6 40 'The Mines': Vedan mines (43, at the elevator, refuses the menu)"),
    "ch07_rosa": ([7010], 5004, "Ch7 10 'To the Rizahna Ruins': Rosa, Sil desert (signboard)"),
    "ch08a_vedan": ([8120], 5308, "Ch8-A 20 'Cancer King Ruins': Vedan (signboard)"),
    "ch08b_juraika": ([8220], 5111, "Ch8-B 20 'Leo King's Castle': Juraika, castle (signboard)"),
    "ch08c_zerard": ([8320], 5239, "Ch8-C 20 'Gladius Towers': Zerard, tower 1F (signboard)"),
    "ch09_labyrinth": ([9030], 5008, "Ch9 30 'Solving the Key Piece Mystery': Rosa, labyrinth (signboard)"),
    "ch10_kuje": ([10010], 5006, "Ch10 10 'Kuje Desert': Rosa, Kuje desert (signboard)"),
    "ch11_mariglenn": ([11010], 5400, "Ch11 10 'Ti'atha Forest': Mariglenn, south gate road (signboard; "
                                      "jump 5 'Ti'atha forest' spawns in an unloaded black area)"),
    "ch12_mariglenn": ([12010], 5403, "Ch12 10 'Gathering Drigellums': Mariglenn (signboard)"),
    "ch13_mariglenn": ([13010], 5404, "Ch13 10 'Obtaining the Sacred Sword': Mariglenn (signboard)"),
    "alistia": ([13020, 28010], (21, -668.14, 31.22, -1606.52, -0.5),
                "Alistia [10] (planet 21): Lapatia Village transporter (record 901, AR_transp_param_EN; "
                "the E_EV18-0020 end position replays that event)", ["--location", "901"]),
    "ghost_ship": ([13020, 14010], 62, "Ghost ship (planet 7), docking point"),
    "ghost_ship_ex": ([13020, 14030], 3011, "Ghost ship EX (planet 10), 10F"),
    "space_deck": ([13020], 82, "Space (planet 9): the Dorgenark's deck"),
    # late game: last story section + every main-menu feature the decomp names a gate for
    "late_game": ([13020], 32, "Ch13 20 + Factory row (flag 0x3E8 = 1000, also set by the section), "
                              "Insectron rank var 5 = 3: Zerard spaceport"),
}

LATE_EXTRA = ["--set-flag", "0x3E8", "--var", "5=3"]


def recipe(name):
    secs, spawn = LIBRARY[name][0], LIBRARY[name][1]
    args = []
    for s in secs:
        args += ["--section", str(s)]
    if isinstance(spawn, tuple):
        pl, x, y, z, yaw = spawn
        args += ["--spawn", f"{pl}:{x},{y},{z},{yaw}"]
    else:
        args += ["--spawn-jump", str(spawn)]
    args += ["--no-help"] + (LIBRARY[name][3] if len(LIBRARY[name]) > 3 else [])
    if name == "late_game":
        args += LATE_EXTRA
    return ("save2", args)


# Widened soak (soak.py --wide, docs/TEST-FIXTURES.md "Widened soak"): every library card
# again as "w_<name>" with the section's abilities applied (saveedit.py --abilities: learned
# bits + equip slots), so autobattle's ability / combination-attack use has something to pick.
# The plain library cards stay as they were (bootcheck / other lanes use them).
WIDE_PREFIX = "w_"
BURNING_CHARAS = (11001, 11002, 11003, 11004, 11005, 11006, 11007, 11008)


def wide_recipe(name):
    base, args = recipe(name[len(WIDE_PREFIX):])
    # + Burning Strike Lv1 (ability 1341, family 0x86: CharaLearnAbility_3ad460 also sets the
    # 'Burning Strike Possible' flag 1005 that CharaResolveActionHitMaybe_3b28d0 tests)
    burn = [a for d in BURNING_CHARAS for a in ("--learn", f"{d}:1341")]
    return base, args + ["--abilities"] + burn


def wide_names():
    return [WIDE_PREFIX + n for n in LIBRARY]


# Map sweep (soak.py --maps): one card per debug jump point, "m_<jump id>", picked per planet
# by greedy farthest-point over the signboards (5001..5414), next-episode markers (1101..1155),
# bases, spaceports, bridges, stations and ghost-ship floors of dbg/map_jump_en.txt, so one
# boot per point lands in a different part of the planet; the late story point (13020, + the
# ghost-ship sections) keeps most areas open and the party strong.  Coverage is counted in
# planet zones (party +0xC, planet_zone_param_2_EN #403: Rosa 8, Juraika 7, Zerard 7, ..).
MAP_PREFIX = "m_"
MAP_PER_PLANET = {1: 2, 2: 12, 3: 10, 4: 14, 5: 10, 6: 8, 7: 3, 8: 2, 9: 2, 10: 6}
MAP_SECTIONS = {7: [13020, 14010], 10: [13020, 14030]}
_MAP_CAND = (list(range(5001, 5415)) + list(range(1101, 1156)) + list(range(1, 10)) + list(range(11, 100))
             + [612, 711, 712, 713, 414, 415, 416, 417, 902, 903, 2001, 2002] + list(range(3011, 3021))
             + list(range(1301, 1339)))


def map_points(per_planet=None):
    """[(jump id, planet)] -- greedy farthest-point picks per planet (3D distance; the first
    pick is the planet's lowest candidate id)."""
    import math
    import rgdata
    per = dict(MAP_PER_PLANET, **(per_planet or {}))
    j = rgdata.map_jumps()
    by = {}
    for k in _MAP_CAND:
        # jump 5 'Ti'atha forest' spawns in an unloaded black area (card library notes)
        if k in j and j[k][1:4] != (0.0, 0.0, 0.0) and k != 5:
            by.setdefault(j[k][0], []).append(k)
    out = []
    for pl, ks in sorted(by.items()):
        n = per.get(pl, 0)
        sel = []
        while ks and len(sel) < n:
            if not sel:
                k = min(ks)
            else:
                k = max(ks, key=lambda c: min(math.dist(j[c][1:4], j[s][1:4]) for s in sel))
                if min(math.dist(j[k][1:4], j[s][1:4]) for s in sel) < 300:
                    break
            sel.append(k)
            ks = [c for c in ks if c != k]
        out += [(k, pl) for k in sel]
    return out


# zones the spread missed in the first soak2 pass (soak.py coverage): Rosa spaceport (12),
# Rizahna ruins (1128), Johannasburg (5014), Juraika swamp side (5103, 5104, 5109), Mariglenn
# palace gate (2002, 5400), the Dorgenark's other spot (904)
MAP_EXTRA = [12, 1128, 5014, 5103, 5104, 5109, 2002, 5400, 904]


def map_names(extra=True):
    pts = [k for k, _ in map_points()]
    return [f"{MAP_PREFIX}{k}" for k in pts + ([k for k in MAP_EXTRA if k not in pts] if extra else [])]


def map_recipe(name):
    import rgdata
    k = int(name[len(MAP_PREFIX):])
    pl = rgdata.map_jumps()[k][0]
    args = []
    for s in MAP_SECTIONS.get(pl, [13020]):
        args += ["--section", str(s)]
    args += ["--abilities", "--spawn-jump", str(k), "--no-help"]
    args += [a for d in BURNING_CHARAS for a in ("--learn", f"{d}:1341")]
    return ("save2", args)
