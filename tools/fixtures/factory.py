#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Factory driver: FACTORY-overlay gameplay to the end, closed loop (docs/TEST-FIXTURES.md
"Factory and Insectron drivers").

    python tools/fixtures/factory.py run    [--exe EXE] [--out D] [--keep]
    python tools/fixtures/factory.py replay ROUTE [--exe EXE] [--out D]

Card: out/fixtures/cards/factory_plans (saveedit.py make factory_plans: save2 + flag 0x3E8
(Factory row) + the 72 'Obtained Factory Hint' flags 1100..1171 = every production plan
(FactoryCompletionUpdate_3e7ae0 marks a plan known when its record's story flag is set) +
5 of each material, category 11).  Boot: boot_factory.input.txt's prefix (CONTINUE ->
main menu -> Factory -> "Linking to the factory via remote control..." -> FACTORY menu,
16/100 at 4,400).

run: from the factory-menu state (written once per exe, out/fixtures/<exe-id>/factory/),
one rg-game segment per phase (play.py rule: lines after the state's field), each ending in
a state + screenshot that the next phase starts from:
  floor     Place: Source Table x2 (carry, place, place again), Move one (pick, UP x2,
            R1 rotate, drop), Remove one, back to the menu
  manual    User's Manual: contents, two pages, back
  plan      Blueprints -> 'Healing vial' (row 4, column 1) -> Set -> Yes -> "Load a parts
            layout template similar to the selected production plan?" Yes -> "Clear out all
            the currently-placed parts?" Yes -> template placed (3 Source Tables, tubes,
            assembler, Completion Table) -> back to the menu
  material  Set Material: per plan slot (Dreamflower Ash, Dream Mushroom, Hoho Bird
            Feather; Alchemy tab, qty preset = the plan's 2) "Select a source table": the
            cursor is walked with D-pad presses and CROSS until the game takes it (closed
            loop: the material grid comes back with the slot's OK; detector grid_open()),
            candidates UP n (middle table), LEFT n (left), RIGHT n (right)
  run       Run -> the factory's verdict: the refusal box "The factory isn't ready yet. Is
            all the machinery connected to a power source? ..." (dialog_open()) or a
            production (no box; FACTORY keeps running); recorded, not judged
  exit      CIRCLE, Go Back -> "Halt factory operations?" Yes -> NORMAL (ovl 3) main menu ->
            CIRCLE -> field (6/100): the FACTORY -> NORMAL switch
Output D (default out/fixtures/<exe-id>/factory/run/): route.txt (the whole input from the
factory state: `play.py --from <state> --input route.txt` replays it), boot_route.txt (the
same from power-on: boot prefix + route; `run_from.py --boot-save factory_plans --input`),
phases.tsv, s*.png, result.json (verdict, picks, final STATUS).

replay: one power-on run of a boot_route.txt (run_from.py --boot-save factory_plans) with
RG_STATUS_EVERY=50 and the phase-end screenshots; result.json = run hash, STATUS rows,
screenshot hashes, crash report.  routecmp.py compares two builds on the boot route (RG_NATIVE_OVL ON / OFF).

One rg-game at a time.

Production (soak2 lane, 2026-10-25): `run --card factory_parts --plan healing_eq --cords
--produce 3000` (factory_parts = factory_plans + 10 of each factory part).  --plan picks a
PROFILES entry (blueprint cell, floor edits, power cords, materials, source-table pick
candidates); `layout` = floor_script() edits (remove / place / move, coarse cells), `cords`
= cord_script() (wall-socket stub -> bend -> the part's power point; the game's own power check
FactoryStep_5069e0 turns every part to state 4/5, verified with out/soak2/fparts.py dumps of the
part groups), `produce` = N fields after a Run that was not refused.  Results: the Run is
ACCEPTED ("OPERATING") once the cords are in; the line then stops on the game's own rules:
healing (raw template): "Not all materials arrived at the assembler on time" (middle route 6
tubes, outer routes 11: the manual's Processing Time rule); healing_eq (routes equalised to 10):
"There were improperly processed materials in the assembler"; freeze (Iron Board is metallic:
Smelter -> Form Press -> Cooler first) the same.  No product yet: the processing rule for the
alchemy materials is the open step (the Place list has no Athanor on this card).

PRODUCED (cov3 lane, 2026-10-25): `run --card factory_prod --plan healing_ath --cords --produce 1000
--save` (~7 min).  The game's rules, from FactoryProduceRun_505e00 (result codes: fdump.py):
  - every material must pass the machine of its class (item_param #4 field 4): 1100 alchemy ->
    Athanor, 1101 mechanical -> Disassembler, 1102 circuit -> Washer, 1104 gem -> Grinder, 1103
    metal -> Smelter, then Form Press, then the tube in front of a Cooler; a raw material at the
    assembler = "improperly processed", a wrong class in a machine = "These parts won't work in ..";
  - all inputs must reach the assembler in the same tick: a part takes len x 30 ticks (Source
    Table / tubes 1, Athanor 6, Assembler III 8; fdump.py lists len), so the routes need equal
    sums of part lengths, not equal tube counts; Assembler I/II/III take 1/2/3 inputs;
  - the plan's materials (types 2..4 also check which input carries which material).
The Athanor (and Assembler III) are NOT in the Place list until unlocked: the list is the item-def
table filtered by ContainerViewItemFilterMatch_40c280 (item_param #102 [3] = unlock group, 34 / 35,
listed once StateBlock +0x880 f64[group] > 0), not the inventory: card factory_prod =
factory_plans + `saveedit.py --unlock-group 34 --unlock-group 35`.  healing_ath = template + one
Athanor per route (outer tables moved down to keep the three routes at 9 length units), eight
cords; then "Success!" -> "Divine Blessing (Healing vial) production was a success!" -> "Obtained
a sample of Divine Blessing!"; --save saves at the card's transporter afterwards and diffs the
written card's inventory (result.json inventory_delta: Divine Blessing +1, the three materials -2
each).  --produce reads the factory's own result code with fdump.py (needs the exe's .map) and
takes the success screens' exit path.  The whole route must stay under the input-script limit
(32,636 VBlanks from power-on, src/host/host_script.c): hence no_demo (no floor / manual phases)
for this profile.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402

CARD = "factory_plans"
BOOT = fxlib.PORT / "tools" / "trace" / "goldens" / "boot_factory.input.txt"
F0 = 4400          # FACTORY menu open (boot_factory.input.txt "boot-end")

# phase scripts: (name, [(offset, button or '#!stick ...'), ...], length)
FLOOR = [(20, "DOWN"), (60, "CROSS"),                        # Place
         (160, "CROSS"), (260, "CROSS"),                     # carry a Source Table, place it
         (300, "TRIANGLE"), (400, "CROSS"), (445, "CIRCLE"),  # back to the list, carry another
         (500, "CIRCLE"),                                    # back to the menu
         (580, "DOWN"), (620, "CROSS"), (720, "CROSS"),      # Move: pick up the part under the cursor
         (760, "UP"), (780, "UP"), (820, "R1"), (860, "CROSS"),  # move, rotate, drop
         (900, "CIRCLE"),
         (980, "DOWN"), (1020, "CROSS"), (1120, "CROSS"),    # Remove the part under the cursor
         (1160, "CIRCLE")]
FLOOR_LEN = 1240
MANUAL = [(20, "DOWN"), (40, "DOWN"), (80, "CROSS"),           # menu row 3 -> 5: User's Manual
          (240, "DOWN"), (270, "CROSS"), (390, "CIRCLE"),    # Factory Basics
          (430, "DOWN"), (460, "CROSS"), (580, "CIRCLE"),    # Work Procedure
          (640, "CIRCLE")]                                   # contents -> menu
MANUAL_LEN = 760
PLAN = [(20, "UP"), (40, "UP"), (60, "UP"), (80, "UP"), (100, "UP"), (140, "CROSS"),  # row 5 -> 0
        (240, "DOWN"), (270, "DOWN"), (300, "DOWN"), (330, "DOWN"), (370, "RIGHT"),   # Healing vial
        (410, "CROSS"),                                      # plan detail
        (510, "CROSS"),                                      # Set
        (640, "CROSS"),                                      # "Set Healing vial as the current plan?" Yes
        (740, "CROSS"),                                      # "... has been set"
        (840, "CROSS"),                                      # "Load a parts layout template?" Yes
        (1040, "CROSS"),                                     # "Clear out all the placed parts?" Yes
        (1240, "CIRCLE"), (1300, "CIRCLE")]                  # "Removed all ..." -> grid -> menu
PLAN_LEN = 1440
# Set Material: menu row 0 -> 4, the Alchemy tab (L1 wraps), item index in the tab (item id
# order: 16681 Flame God's Stone .. ; Dreamflower Ash 5, Dream Mushroom 6, Hoho Bird Feather 3)
MATERIALS = [("Dreamflower Ash", 5), ("Dream Mushroom", 6), ("Hoho Bird Feather", 3)]

# Production profiles (--plan): blueprint cell (row, col), the layout template's power cords,
# materials (name, tab, index in the tab: tabs Metal 0 / Mecha 1 / Circuit 2 / Gem 3 / Alchemy 4,
# L1 = previous tab, items in item-id order), and the source-table pick candidates (closed loop:
# the first press list after which the material grid comes back).  'healing' = the original
# driver (3 Source Tables; its template's middle route is 5 tubes shorter than the outer two, so
# a powered Run ends in ERROR "Not all materials arrived at the assembler on time": the manual's
# 'Processing Time' rule, the template is only "similar"); 'freeze' (Freeze defense: Iron Board
# x5 + Snow Crest x3) has a symmetric two-table template, so it runs to completion.
def _combos(first, second, r1, r2):
    return [[first] * a + [second] * b for t in range(0, 20) for a in r1 for b in r2 if a + b == t]


# Place-list index of the Athanor once unlocked (list = the unlocked category-18 item defs in
# table order)
ATHANOR_INDEX = 12
PROFILES = {
    "healing": {"cell": (4, 1), "cords": None, "tab0": 4,
                "materials": [("Dreamflower Ash", 4, 5), ("Dream Mushroom", 4, 6), ("Hoho Bird Feather", 4, 3)],
                "picks": None},
    # Healing vial with its template EQUALISED (soak2 lane): the middle route rebuilt as a 10-tube
    # detour, the outer tables moved one cell down onto their first tube's cell (outer routes 10
    # tubes too), cords to the moved tables
    "healing_eq": {"cell": (4, 1), "tab0": 4,
                   "floor": ([("remove", 8, y) for y in range(3, 9)]
                             + [("remove", 3, 3), ("remove", 13, 3), ("move", 3, 2, 3, 3), ("move", 13, 2, 13, 3)]
                             + [("place", 4, 8, 3, 1), ("place", 3, 9, 3, 1), ("place", 4, 10, 3, 3)]
                             + [("place", 3, 10, y, 0) for y in range(4, 8)]
                             + [("place", 4, 10, 8, 2), ("place", 3, 9, 8, 3), ("place", 4, 8, 8, 0)]),
                   "cords": [[(13, 2), (13, 10, 1), (12, 10)],    # left Source Table (9, 9), right side
                             [(16, 2), (16, 7, 1), (23, 7)],      # middle Source Table (24, 6), left side
                             [(34, 2), (34, 10, 1), (38, 10)],    # right Source Table (39, 9), left side
                             [(2, 31), (2, 32, 1), (23, 32)],     # Assembler (24, 27), left side
                             [(2, 37), (2, 40, 1), (23, 40)]],    # Completion Table (24, 39), left side
                   "materials": [("Dreamflower Ash", 4, 5), ("Dream Mushroom", 4, 6), ("Hoho Bird Feather", 4, 3)],
                   # material k goes to plan input k: 1 left, 2 middle, 3 right (the blueprint's
                   # 1-2-3 graph; with 1 in the middle the assembler reports "improperly processed
                   # materials")
                   "picks": [_combos("LEFT", "UP", range(1, 9), range(0, 6)) + _combos("LEFT", "DOWN", range(1, 9), range(1, 4)),
                             _combos("RIGHT", "UP", range(1, 9), range(0, 6)) + _combos("RIGHT", "DOWN", range(1, 9), range(1, 4)),
                             _combos("RIGHT", "UP", range(1, 12), range(0, 4)) + _combos("RIGHT", "DOWN", range(1, 12), range(1, 4))]},
    # Healing vial PRODUCED (cov3 lane, card factory_prod).  Alchemy materials (item_param #4 class
    # 1100) must pass an Athanor (FactoryProduceRun_505e00: state 0 -> 5 at the part's middle; raw
    # at the assembler = "improperly processed"), and the three inputs must reach Assembler III in
    # the same tick (a part takes len x 30 ticks: tube 1, Athanor 6).  Template routes: middle 6
    # tubes, outer 11.  Here: the middle Athanor replaces (8, 4..6) -> 3 tubes + Athanor; each outer
    # Source Table moves down to row 7 (its tubes (x, 3..7) removed) and a horizontal Athanor
    # replaces (5..7, 9) / (10..12, 9) -> 3 tube cells + Athanor: all three routes = 9 units.  The
    # carried part is centred on the cursor; d1 = flow +x, d3 = -x.  Cords: the moved tables from
    # side sockets row 16, the horizontal Athanors from top sockets 16 / 37 (points above their
    # entry cell), the middle table from socket 31, the middle Athanor from socket 34, assembler /
    # completion table as healing_eq.  Fits the input-script limit (32,636 VBlanks from power-on)
    # with --save only without the floor / manual demo phases (no_demo).
    "healing_ath": {"cell": (4, 1), "tab0": 4, "no_demo": True,
                    "floor": ([("remove", 3, y) for y in range(3, 8)] + [("move", 3, 2, 3, 7)]
                              + [("remove", x, 9) for x in (5, 6, 7)]
                              + [("remove", 8, y) for y in (4, 5, 6)]
                              + [("remove", x, 9) for x in (10, 11, 12)]
                              + [("remove", 13, y) for y in range(7, 2, -1)] + [("move", 13, 2, 13, 7)]
                              + [("place", ATHANOR_INDEX, 6, 9, 1, 120), ("place", ATHANOR_INDEX, 8, 5, 0, 120),
                                 ("place", ATHANOR_INDEX, 11, 9, 3, 120, 1)]),
                    "cords": [[(45, 16), (45, 22, 1), (42, 22)],  # right Source Table (39, 21), right side
                              [(37, 2), (37, 26)],                # right Athanor (30..38, 27), from above
                              [(34, 2), (34, 13, 1), (27, 13)],   # middle Athanor (24, 12), right side
                              [(31, 2), (31, 7, 1), (27, 7)],     # middle Source Table (24, 6), right side
                              [(16, 2), (16, 26)],                # left Athanor (15..23, 27), from above
                              [(2, 31), (2, 32, 1), (23, 32)],    # Assembler III (24, 27), left side
                              [(2, 37), (2, 40, 1), (23, 40)],    # Completion Table (24, 39), left side
                              [(2, 16), (2, 22, 1), (8, 22)]],    # left Source Table (9, 21), left side
                    "materials": [("Dreamflower Ash", 4, 5), ("Dream Mushroom", 4, 6), ("Hoho Bird Feather", 4, 3)],
                    "picks": None},
    "freeze": {"cell": (3, 0), "tab0": 0,
               "cords": [[(13, 2), (13, 7, 1), (14, 7)],       # left Source Table (15, 6), left side
                         [(31, 2), (31, 7, 1), (30, 7)],       # right Source Table (27, 6), right side
                         [(2, 31), (20, 31)],                  # Assembler II (21, 27): point (-1, 4), straight
                         [(2, 37), (2, 40, 1), (20, 40)]],     # Completion Table (21, 39), left side
               "materials": [("Iron Board", 0, 1), ("Snow Crest", 4, 7)],
               "picks": [_combos("UP", "LEFT", range(2, 8), range(0, 7)),
                         [["RIGHT"] * r for r in range(1, 12)] + _combos("UP", "RIGHT", range(2, 8), range(0, 7))]},
}
# source-table picks for healing_ath (tables left (3, 7), middle (8, 2), right (13, 7)); closed loop,
# the first sequence after which the material grid comes back wins (fdump.py shows which table)
PROFILES["healing_ath"]["picks"] = [
    # from the cords' end cursor (fine (25, 19)) to the left table; seen: LEFT x6 DOWN
    _combos("LEFT", "DOWN", range(1, 9), range(0, 4)) + _combos("LEFT", "UP", range(1, 9), range(1, 4)),
    # the select cursor stays on the table just picked: left -> middle, middle -> right
    _combos("RIGHT", "UP", range(3, 9), range(3, 8)),
    _combos("RIGHT", "DOWN", range(3, 9), range(3, 8))]
RUN = [(20, "CIRCLE"), (110, "DOWN"), (130, "DOWN"), (150, "DOWN"), (190, "CROSS")]  # row 4 -> 7 Run
RUN_LEN = 600
EXIT = [(20, "CIRCLE"), (80, "UP"),                          # close the verdict, row 7 -> 6 Go Back
        (120, "CROSS"), (220, "CROSS"),                      # Go Back, "Halt factory operations?" Yes
        (1300, "CIRCLE")]                                    # NORMAL main menu -> field
EXIT_LEN = 1500
# after a production: "Success!" -> "<product> (<plan>) production was a success!" -> "Obtained a
# sample of <product>!" -> "Soon you'll be able to buy it ..." (one CROSS each, 4), then the menu is
# on row 7 (Run): UP to Go Back, "Halt factory operations?" Yes, NORMAL -> field
EXIT_PRODUCED = [(100, "CROSS"), (220, "CROSS"), (340, "CROSS"), (460, "CROSS"), (600, "UP"), (640, "CROSS"),
                 (740, "CROSS"), (1820, "CIRCLE")]
EXIT_PRODUCED_LEN = 2020


# Power cords (soak2 lane, 2026-10-25): the Healing-vial template's machines and their power
# points (part group +0x20: fine-grid (dx, dy, dir) per part, FactoryGridPointAt_4fe7c0; dir
# 0 +y, 1 +x, 2 -y, 3 -x): Source Tables (9|24|39, 6) at their left / right side middle, the
# Assembler (24, 27) at (-1, 5), the Completion Table (24, 39) at (-1, 1).  A cord runs from a
# wall-socket stub (row 1 below the top sockets, column 1 right of the side sockets): CROSS on
# the cell next to the stub, cursor along the first leg, CROSS = bend, cursor along the second
# leg into the point (the last move must point INTO the part: FactoryStep_5069e0 powers a part
# (state 3 -> 4) only when the cord end's direction equals the point's), CROSS = done.  The
# place cursor starts at fine cell (25, 19); one D-pad press = one fine cell.
CORD_PATHS = [[(13, 2), (13, 7, 1), (12, 7)],       # left Source Table, right side (from socket 13)
              [(16, 2), (16, 7, 1), (23, 7)],       # middle Source Table, left side (socket 16)
              [(34, 2), (34, 7, 1), (38, 7)],       # right Source Table, left side (socket 34)
              [(2, 31), (2, 32, 1), (23, 32)],      # Assembler, left side (side socket row 31)
              [(2, 37), (2, 40, 1), (23, 40)]]      # Completion Table, left side (side socket row 37)


def floor_script(ops, start=(25, 19), item=0, rd=0):
    """[(offset, button)], length, end state for floor edits from the FACTORY menu (row 0):
    ('remove', cx, cy), ('place', part list index, cx, cy, d), ('move', cx, cy, tx, ty) in
    COARSE cells (3 fine; the parts' grid, factory part group +0x30).  Found by booting (soak2
    lane, out/soak2/fparts.py dumps): part modes move the shared floor cursor one coarse cell per
    D-pad press (presses closer than ~30 fields, or during the pick-up, are lost); the Place
    list and the R1 rotation (d -> d - 1; L tube d1 = up+right, d2 = up+left, d3 = left+down,
    d0 = right+down) persist between placements; part list: 0 Source Table, 1 Completion Table,
    2 Power Cord, 3 I tube, 4 L tube, 5 X tube, ..."""
    out, o, cur, row = [], 20, list(start), 0

    def menu(r):
        nonlocal o, row
        while row != r:
            out.append((o, "DOWN" if r > row else "UP"))
            o += 20
            row += 1 if r > row else -1
        out.append((o + 20, "CROSS"))
        o += 120

    def go(cx, cy):
        nonlocal o
        while cur[0] // 3 != cx:
            b = "RIGHT" if cx > cur[0] // 3 else "LEFT"
            out.append((o, b))
            o, cur[0] = o + 32, cur[0] + (3 if b == "RIGHT" else -3)
        while cur[1] // 3 != cy:
            b = "DOWN" if cy > cur[1] // 3 else "UP"
            out.append((o, b))
            o, cur[1] = o + 32, cur[1] + (3 if b == "DOWN" else -3)
    for op in ops:
        if op[0] == "remove":
            menu(3)
            go(op[1], op[2])
            out += [(o + 20, "CROSS"), (o + 100, "CIRCLE")]
            o += 180
        elif op[0] == "place":
            _, k, cx, cy, d = op[:5]
            settle = op[5] if len(op) > 5 else 0    # extra fields before the place CROSS
            # the placement that reaches the part's cap (group +0xA; Athanor 3) leaves the place
            # mode by itself: one CIRCLE less then (op[6] = 1)
            circles = op[6] if len(op) > 6 else 2
            menu(1)
            while item != k:
                out.append((o, "DOWN" if k > item else "UP"))
                o, item = o + 30, item + (1 if k > item else -1)
            out.append((o + 10, "CROSS"))
            o += 150
            go(cx, cy)
            while rd != d:
                out.append((o, "R1"))
                o, rd = o + 40, (rd - 1) % 4
            o += settle
            out += [(o + 20, "CROSS"), (o + 100, "CIRCLE")] + ([(o + 180, "CIRCLE")] if circles > 1 else [])
            o += 260
        elif op[0] == "move":
            _, cx, cy, tx, ty = op
            menu(2)
            go(cx, cy)
            out.append((o + 20, "CROSS"))
            o += 100
            go(tx, ty)
            out += [(o + 20, "CROSS"), (o + 100, "CIRCLE")]
            o += 180
    while row != 0:
        out.append((o, "UP"))
        o, row = o + 20, row - 1
    return out, o + 100, {"cursor": tuple(cur), "item": item, "rd": rd}


def cord_script(paths=None, start=(25, 19), item=0):
    """[(offset, button)] from the FACTORY menu (cursor on row 0): Place -> Power Cord (list
    index 2; the list remembers its cursor = `item`) -> the CORD_PATHS (fine cells; the cord
    cursor moves one fine cell per press) -> back to the menu (row 0)."""
    out = [(20, "DOWN"), (60, "CROSS")]
    o = 160
    while item != 2:
        out.append((o, "DOWN" if item < 2 else "UP"))
        o, item = o + 30, item + (1 if item < 2 else -1)
    out.append((o + 10, "CROSS"))
    o, cx, cy = o + 100, start[0], start[1]

    def go(x, y):
        nonlocal o, cx, cy
        while cx != x:
            out.append((o, "RIGHT" if x > cx else "LEFT"))
            o, cx = o + 16, cx + (1 if x > cx else -1)
        while cy != y:
            out.append((o, "DOWN" if y > cy else "UP"))
            o, cy = o + 16, cy + (1 if y > cy else -1)
    for path in paths:
        go(*path[0])
        out.append((o + 20, "CROSS"))
        o += 80
        for pt in path[1:]:
            go(*pt[:2])
            out.append((o + 20, "CROSS"))
            o += 80
    go(25, 19)        # the place / source-table cursor is shared: back to where Set Material expects it
    out += [(o + 40, "CIRCLE"), (o + 120, "CIRCLE"), (o + 200, "UP")]
    return out, o + 300


# Transporter save (soak.py Session.save): the factory cards stand at save2's transporter
SAVE = [(10, "CROSS"), (90, "CROSS"), (240, "CROSS"), (390, "CROSS"), (440, "LEFT"), (470, "CROSS"),
        (810, "CROSS"), (890, "CIRCLE"), (950, "CIRCLE"), (1010, "CIRCLE")]
SAVE_LEN = 1100


def inventory_delta(card_a, card_b):
    """{item id: (name, count change)} between two saves dirs (saveedit inventory)."""
    import saveedit
    import rgdata

    def counts(d):
        # the slot file itself (Save(dir) would take the first match, possibly under backups/)
        f = next(x for x in sorted(Path(d).rglob("BASCUS-97490LV5RG_*"))
                 if x.is_file() and "backups" not in x.parts)
        c = {}
        for o in saveedit.Save(str(f)).inventory():
            c[o["item"]] = c.get(o["item"], 0) + o["count"]
        return c
    try:
        ca, cb = counts(card_a), counts(card_b)
    except SystemExit as e:
        return {"error": str(e)}
    it = rgdata.items()
    return {k: (it.get(k, {}).get("name", "?"), cb.get(k, 0) - ca.get(k, 0))
            for k in sorted(set(ca) | set(cb)) if cb.get(k, 0) != ca.get(k, 0)}


def lines_at(f0, script):
    return [f"{f0 + o} {f0 + o + 3} {b}" for o, b in script]


# ---- screen detectors (512x448 screenshots) ----
def _px(png, box):
    from PIL import Image
    im = Image.open(png).convert("RGB")
    if im.size != (512, 448):
        im = im.resize((512, 448))
    return list(im.crop(box).getdata())


def grid_open(png) -> bool:
    """Set Material's grid (with the plan's material panel on top) is shown: the panel at
    (70..440, 60..110) is blue (mean B - R > 0); in 'Select a source table' that region is the
    factory wall (B - R ~ -25)."""
    px = _px(png, (70, 60, 440, 110))
    return sum(b - r for r, g, b in px) / len(px) > 0


def dialog_open(png) -> bool:
    """A message box right of the factory menu (the Run verdict): >50% of (300..500,
    190..250) is the box colour (27, 34, 49)."""
    px = _px(png, (300, 190, 500, 250))
    return sum(1 for r, g, b in px if abs(r - 27) < 8 and abs(g - 34) < 8 and abs(b - 49) < 8) / len(px) > 0.5


def png_hash(p):
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()[:16] if Path(p).exists() else None


# ---- running ----
def run_seg(exe, state, route_lines, to, out: Path, shots=(), status=0, save=True, hang_s=300):
    """One segment from `state` to field `to` with the whole route so far (only lines after
    the state's field matter); (rc, log, state at `to` or None)."""
    out.mkdir(parents=True, exist_ok=True)
    inp = out / "input.txt"
    inp.write_text("#!stick 1 0\n" + "\n".join(route_lines) + "\n", encoding="utf-8")
    sv = out / "saves"
    sv.mkdir(exist_ok=True)
    cmd = [str(exe), "--headless", "--fields", str(to), "--saves", str(sv), "--input", str(inp),
           "--load-state", str(Path(state).resolve())]
    st = out / f"f{to}.rgstate" if save else None
    if st:
        cmd += ["--save-state", f"{to}:{st}"]
    for f in shots:
        cmd += ["--shot", f"{f}:{out / f's{f:05d}.png'}"]
    env = {"RG_SS": "1"}
    if status:
        env["RG_STATUS_EVERY"] = str(status)
    rc, log = run_game(cmd, fxlib.game_env(env), hang_s=hang_s)
    (out / "log.txt").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    return rc, log, (st if st and st.exists() else None)


def run_game(cmd, env, hang_s=300):
    """Run rg-game; (rc, log).  The hang timeout counts from the end of the machine-wide
    slot wait (src/game/rg_slots.c: at most 2 headless rg-game processes; other lanes' runs
    can hold both for minutes), i.e. from the first output line that is not the
    "waiting for a free slot" notice.  A hang kills only this process (our own PID)."""
    import threading
    p = subprocess.Popen(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                         errors="replace")
    lines, started = [], [None]

    def reader():
        for ln in p.stdout:
            lines.append(ln)
            if started[0] is None and "waiting for a free slot" not in ln:
                started[0] = time.time()
    th = threading.Thread(target=reader, daemon=True)
    th.start()
    hung = False
    while p.poll() is None:
        time.sleep(0.5)
        if started[0] is not None and time.time() - started[0] > hang_s:
            hung = True
            p.kill()
            break
    p.wait()
    th.join(5)
    log = "".join(lines)
    if hung:
        log += f"\nfactory: TIMEOUT (hang?) after {hang_s} s of running\n"
    return (-9 if hung else p.returncode), log


def status_rows(log):
    rows = []
    for ln in log.splitlines():
        m = re.match(r"STATUS field=(\d+) .*?ovl=(-?\d+) .*?gamemode=(\S+)", ln)
        if m:
            rows.append((int(m.group(1)), int(m.group(2)), m.group(3)))
    return rows


def boot_state(exe: Path) -> Path:
    """The FACTORY-menu state of the factory_plans card at F0 (written once per exe)."""
    d = fxlib.fixture_dir(exe) / "factory"
    d.mkdir(parents=True, exist_ok=True)
    st = d / f"{CARD}_{F0}.rgstate"
    if st.exists():
        return st
    if not (fxlib.CARDS / CARD).is_dir():
        subprocess.run([sys.executable, str(HERE / "saveedit.py"), "make", CARD], check=True)
    cmd = [sys.executable, str(HERE / "run_from.py"), "--boot-save", CARD, "--input", str(BOOT),
           "--exe", str(exe), "--fields", str(F0 + 2), "--", "--save-state", f"{F0}:{st}"]
    p = subprocess.run(cmd, env=fxlib.game_env({"RG_SS": "1", "RG_STATUS_EVERY": "100"}),
                       capture_output=True, text=True, errors="replace")
    (d / "boot.log").write_text(p.stdout + p.stderr, encoding="utf-8")
    if not st.exists():
        raise SystemExit(f"factory: boot state not written (exit {p.returncode}, log {d / 'boot.log'})")
    return st


def boot_prefix():
    """boot_factory.input.txt's lines up to the FACTORY menu (F0)."""
    out = []
    for ln in BOOT.read_text(encoding="utf-8").splitlines():
        t = ln.split("#", 1)[0].split()
        if len(t) >= 3 and t[0].isdigit() and int(t[0]) < F0:
            out.append(ln)
    return out


def cmd_run(a) -> int:
    global CARD
    CARD = a.card or CARD
    exe = fxlib.exe_path(a.exe)
    out = Path(a.out) if a.out else fxlib.fixture_dir(exe) / "factory" / "run"
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    state = boot_state(exe)
    f = F0
    route: list[str] = []
    tsv = open(out / "phases.tsv", "w", encoding="utf-8")
    tsv.write("phase\tfrom\tto\trc\tcheck\tnote\n")
    res = {"exe_id": fxlib.exe_id(exe), "card": CARD, "from_state": str(state), "picks": [], "phases": []}
    t0 = time.time()

    def phase(name, script, length, check=None, note=""):
        nonlocal state, f, route
        lines = lines_at(f, script)
        to = f + length
        rc, log, st = run_seg(exe, state, route + lines, to, out / name, shots=[to], status=50)
        shot = out / name / f"s{to:05d}.png"
        if shot.exists():
            shutil.copyfile(shot, out / f"s{to:05d}_{name}.png")
        crash = fxlib.crash_report(log, exe)
        ok = rc == 0 and st is not None and not crash and (check is None or check(shot, log))
        rows = status_rows(log)
        tsv.write(f"{name}\t{f}\t{to}\t{rc}\t{'ok' if ok else 'FAIL'}\t{note} {rows[-1] if rows else ''}\n")
        tsv.flush()
        res["phases"].append({"phase": name, "from": f, "to": to, "rc": rc, "ok": ok,
                              "status": rows[-1] if rows else None, "crash": crash})
        print(f"  {name:12s} {f}..{to}  {'ok' if ok else 'FAIL'}  {rows[-1] if rows else ''} {note}", flush=True)
        if ok:
            route += lines
            state, f = st, to
        return ok, crash

    def in_factory(shot, log):
        rows = status_rows(log)
        return bool(rows) and rows[-1][1] == 4

    verdict = None
    prof = PROFILES[a.plan]
    plan = PLAN
    if prof["cell"] != (4, 1):
        r_, c_ = prof["cell"]
        plan = [x for x in PLAN if x[0] < 240 or x[0] >= 410]
        o_ = 240
        for _ in range(r_):
            plan.append((o_, "DOWN"))
            o_ += 30
        for _ in range(c_):
            plan.append((o_, "RIGHT"))
            o_ += 30
        plan.sort()
    res["plan"] = a.plan
    phases = [("floor", FLOOR, FLOOR_LEN), ("manual", MANUAL, MANUAL_LEN), ("plan", plan, PLAN_LEN)]
    if a.no_demo or prof.get("no_demo"):
        # the menu is still on row 0 (the demo phases leave it on row 5, PLAN walks UP x5 first)
        phases = [("plan", [x for x in plan if not (x[0] <= 100 and x[1] == "UP")], PLAN_LEN)]
    start, item = (25, 19), 0
    if a.no_demo or prof.get("no_demo"):
        start = (25, 25)    # the floor cursor at FACTORY open; the demo's Move leaves it 2 rows up
    if prof.get("floor"):
        sc, ln, end = floor_script(prof["floor"], start=start)
        phases.append(("layout", sc, ln))
        start, item = end["cursor"], end["item"]
    if a.cords:
        phases.append(("cords",) + cord_script(prof["cords"] or CORD_PATHS, start, item))
    for name, script, length in phases:
        ok, crash = phase(name, script, length, in_factory)
        if not ok:
            verdict = "crash" if crash else f"failed at {name}"
            break
        if a.until == name:
            verdict = f"stopped after {name} (--until)"
            break
    # Set Material: menu row 0 -> 4, CROSS; per slot: tab, item, qty, then the pick search
    if verdict is None:
        ok, crash = phase("material_open", [(20, "DOWN"), (40, "DOWN"), (60, "DOWN"), (80, "DOWN"),
                                            (120, "CROSS")] + ([(260, "L1")] if prof["tab0"] == 4 else []),
                           320, lambda s, l: grid_open(s))
        if not ok:
            verdict = "crash" if crash else "failed at material_open"
    cur = 0      # the grid cursor's item index in the current tab (starts at 0)
    tab = prof["tab0"]
    picks = [("UP", range(1, 25)), ("LEFT", range(1, 16)), ("RIGHT", None)]
    for k, (mat, mtab, idx) in enumerate(prof["materials"] if verdict is None else []):
        moves = []
        if mtab != tab:
            # L1 = previous tab (R1 presses here leave the grid cursor dead, seen 2026-10-25);
            # the cursor keeps its index across tabs
            moves = [(20 + 30 * i, "L1") for i in range((tab - mtab) % 5)]
            tab = mtab
        o0 = 20 + 30 * len(moves) + (80 if moves else 0)    # the tab slides in: presses meanwhile are lost
        moves += [(o0 + 20 * i, "RIGHT" if idx > cur else "LEFT") for i in range(abs(idx - cur))]
        o = (moves[-1][0] if moves else 0) + 50
        sel = moves + [(o, "CROSS"), (o + 70, "CROSS")]      # item -> qty (preset: the plan's) -> select
        ok, crash = phase(f"mat{k + 1}_select", sel, o + 120, lambda s, l: not grid_open(s), note=mat)
        if not ok:
            verdict = "crash" if crash else f"failed at mat{k + 1}_select"
            break
        cur = idx
        if prof["picks"]:
            cands = prof["picks"][k]
            btn = "+".join(sorted(set(b for c in cands for b in c)))
        else:
            btn, cand = picks[k]
            if cand is None:   # right table: past the middle (the left table took LEFT n)
                ln = res["picks"][1]["n"]
                cand = range(ln + 2, 3 * ln + 2)
            cands = [[btn] * n for n in cand]
        took = None
        for seq in cands:
            n = len(seq)
            sc = [(10 + 16 * i, b) for i, b in enumerate(seq)] + [(10 + 16 * n + 20, "CROSS")]
            ln_ = 10 + 16 * n + 60
            lines = lines_at(f, sc)
            d = out / f"mat{k + 1}_pick" / ("".join(b[0] for b in seq) or "none")
            rc, log, st = run_seg(exe, state, route + lines, f + ln_, d, shots=[f + ln_])
            crash = fxlib.crash_report(log, exe)
            if crash or rc != 0:
                verdict = "crash"
                res["crash"] = crash
                break
            if st and grid_open(d / f"s{f + ln_:05d}.png"):
                took = " ".join(seq)
                route += lines
                state, f = st, f + ln_
                break
            if not a.keep:
                shutil.rmtree(d, ignore_errors=True)
        if verdict:
            break
        res["picks"].append({"material": mat, "button": btn, "n": len(took.split()) if took else None, "presses": took})
        tsv.write(f"mat{k + 1}_pick\t\t{f}\t\t{'ok' if took else 'FAIL'}\t{mat}: {btn} x {took}\n")
        print(f"  mat{k + 1}_pick    {mat}: {btn} x {took}", flush=True)
        if took is None:
            verdict = f"no source table took {mat}"
            break
    if verdict is None:
        ok, crash = phase("run", RUN, RUN_LEN, in_factory)
        if not ok:
            verdict = "crash" if crash else "failed at run"
        else:
            shot = out / f"s{f:05d}_run.png"
            verdict = "refused (factory not ready)" if dialog_open(shot) else "running (no refusal box)"
            if verdict.startswith("running") and a.produce:
                # let the line run: shots every 500 fields; the product's inventory count is
                # read from the party's item pool afterwards (produced())
                ok, crash = phase("produce", [], a.produce, None)
                res["produce_fields"] = a.produce
                if not ok:
                    verdict = "crash while producing" if crash else "failed while producing"
                else:
                    # the factory's own verdict (fdump.py: result code at factory obj +0x8)
                    try:
                        import fdump
                        fr = fdump.dump(exe, state, None, f + 2)
                        res["factory_result"] = {"code": fr["result"], "text": fr["result_text"],
                                                 "slots": [x for x in fr["slots"] if x["item"] >= 0]}
                        print(f"  factory result {fr['result']:#x} {fr['result_text']}", flush=True)
                        if fr["result"] == 1:
                            verdict = "produced"
                    except (SystemExit, Exception) as e:  # no map / no object
                        res["factory_result"] = {"error": str(e)[:200]}
    if verdict and not verdict.startswith(("refused", "running", "produced")):
        pass
    else:
        ex, exl = (EXIT_PRODUCED, EXIT_PRODUCED_LEN) if verdict == "produced" else (EXIT, EXIT_LEN)
        ok, crash = phase("exit", ex, exl, lambda s, l: status_rows(l) and status_rows(l)[-1][1:] == (3, "6/100"))
        res["exit_ok"] = ok
        if not ok:
            res["exit_crash"] = crash
        if ok and a.save:
            # the product in the inventory: the card spawns at save2's transporter, so save to
            # FILE 01 there (soak.py's sequence) and diff the written card's inventory against
            # the card's (a state does not carry the memory card: the segment gets a copy)
            shutil.copytree(fxlib.CARDS / CARD, out / "save" / "saves")
            ok2, crash2 = phase("save", SAVE, SAVE_LEN, None)
            res["save_ok"] = ok2
            res["inventory_delta"] = inventory_delta(fxlib.CARDS / CARD, out / "save" / "saves")
            print(f"  inventory delta (written card - card): {res['inventory_delta']}", flush=True)
    tsv.close()
    res.update(verdict=verdict, to_field=f, wall_s=round(time.time() - t0))
    (out / "route.txt").write_text("# factory.py route from " + str(state) + "\n#!stick 1 0\n" + "\n".join(route) + "\n",
                                   encoding="utf-8")
    (out / "boot_route.txt").write_text(
        "# factory.py: boot_factory.input.txt prefix + route (run_from.py --boot-save factory_plans --input)\n"
        f"# boot-end: {F0}\n" + "\n".join(boot_prefix()) + "\n" + "\n".join(route) + "\n", encoding="utf-8")
    res["phase_ends"] = [p["to"] for p in res["phases"]]
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    print(f"factory: {verdict}; exit to field {'ok' if res.get('exit_ok') else 'not reached'}; "
          f"route {out / 'boot_route.txt'} ({time.time() - t0:.0f} s)")
    return 0 if res.get("exit_ok") and verdict.startswith(("refused", "running", "produced")) else 1


def replay(exe: Path, boot_route: Path, out: Path, card: str, shots_at, end, every=50, env_extra=None):
    """One power-on run of a boot route (run_from.py --boot-save CARD); result dict."""
    out.mkdir(parents=True, exist_ok=True)
    extra = []
    for s in shots_at:
        extra += ["--shot", f"{s}:{out / f's{s:05d}.png'}"]
    cmd = [sys.executable, str(HERE / "run_from.py"), "--boot-save", card, "--input", str(boot_route),
           "--exe", str(exe), "--fields", str(end), "--"] + extra
    t0 = time.time()
    p = subprocess.run(cmd, env=fxlib.game_env(dict(env_extra or {}, RG_STATUS_EVERY=str(every))),
                       capture_output=True, text=True, errors="replace")
    log = p.stdout + p.stderr
    (out / "log.txt").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    rh = None
    for ln in log.splitlines():
        m = re.search(r"run_hash=([0-9a-f]{16})", ln)
        if m:
            rh = m.group(1)
    rows = status_rows(log)
    res = {"exe": str(exe), "exe_id": fxlib.exe_id(exe), "card": card, "route": str(boot_route), "rc": p.returncode,
           "end": end, "run_hash": rh, "wall_s": round(time.time() - t0),
           "status": rows, "status_hash": hashlib.sha256(repr(rows).encode()).hexdigest()[:16],
           "shots": {str(s): png_hash(out / f"s{s:05d}.png") for s in shots_at},
           "crash": fxlib.crash_report(log, exe),
           "ovl_unknown": [ln for ln in log.splitlines() if ln.startswith("ovl:")][:20]}
    (out / "result.json").write_text(json.dumps(res, indent=1), encoding="utf-8")
    return res


def cmd_replay(a) -> int:
    exe = fxlib.exe_path(a.exe)
    rt = Path(a.route)
    rj = rt.parent / "result.json"
    ends = json.loads(rj.read_text())["phase_ends"] if rj.exists() else []
    end = max(ends + [int(ln.split()[1]) for ln in rt.read_text().splitlines()
                      if ln and ln.split()[0].isdigit()]) + 50
    out = Path(a.out) if a.out else rt.parent / f"replay_{fxlib.exe_id(exe)}"
    card = a.card or (json.loads(rj.read_text()).get("card") if rj.exists() else None) or CARD
    res = replay(exe, rt, out, card, sorted(set(ends + [F0])), end)
    print(json.dumps({k: v for k, v in res.items() if k != "status"}, indent=1))
    return 0 if res["rc"] == 0 and not res["crash"] else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    r = sp.add_parser("run")
    r.add_argument("--exe")
    r.add_argument("--out")
    r.add_argument("--keep", action="store_true", help="keep every pick trial's dir")
    r.add_argument("--card", help="card (default factory_plans; factory_parts = + 10 of each factory part)")
    r.add_argument("--plan", default="healing", choices=sorted(PROFILES),
                   help="production profile (blueprint, cords, materials, source-table picks)")
    r.add_argument("--cords", action="store_true", help="lay the power cords (CORD_PATHS) after the plan's template")
    r.add_argument("--produce", type=int, default=0, help="after a Run that is not refused, run N more fields")
    r.add_argument("--no-demo", action="store_true", help="skip the floor / manual demo phases (shorter route)")
    r.add_argument("--save", action="store_true",
                   help="after the exit, save at the transporter and report the inventory change "
                        "(result.json inventory_delta: the product +1, the materials used)")
    r.add_argument("--until", help="stop after this setup phase (floor, manual, plan, layout, cords): its state "
                   "is the start for fdump.py / floor experiments")
    r.set_defaults(fn=cmd_run)
    p = sp.add_parser("replay")
    p.add_argument("route", help="a factory.py boot_route.txt")
    p.add_argument("--card", help="card the route boots (default: the run's result.json card)")
    p.add_argument("--exe")
    p.add_argument("--out")
    p.set_defaults(fn=cmd_replay)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
