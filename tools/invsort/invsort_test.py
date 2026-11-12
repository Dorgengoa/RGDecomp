#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Item sort by category (R2 in the item grid): card maker, inventory checker and the
scripted play test (docs/SETTINGS.md "Sort items by category", lane invsort 2026-11-09).

    python tools/invsort/invsort_test.py mkcard OUT_SAVES        # save2 + a mixed inventory
    python tools/invsort/invsort_test.py inv SAVES [--sorted]    # list 0 by slot (+ check)
    python tools/invsort/invsort_test.py play --exe EXE --out DIR  # the whole test (below)

`play` (about 4 runs of the exe, headless):
  1. mkcard -> DIR/saves (save2 = Salgin transporter, + 30 items of every group, in a mixed
     order; tools/fixtures/saveedit.py add_items),
  2. run A (tools/invsort/sort_save.input.txt): CONTINUE, main menu -> Items, shot before,
     R2 (sort), shot after, back to the field, transporter -> Save over FILE 01;
     check: the card's list 0 is in rank order (census/invsort_category.tsv), the same
     objects (unique id, item, count, every other byte but the slot) as before, the
     characters' equipped unique ids unchanged and still in the inventory,
  3. run B (tools/invsort/use_after_sort.input.txt) on the card run A wrote: CONTINUE, Items
     (shot: the sorted order loaded from the save), Stealth Pills -> Use, back, save again;
     check: Stealth Pills count - 1, slots and equipment as after run A,
  4. control run (run A's input without the R2 line) -> the saved inventory equals the
     card's before (no trigger, no change).
  The Salgin transporter refills HP on load, so run B uses Stealth Pills (usable at full HP).
Prints PASS / FAIL lines; exit 1 on any FAIL.
"""
from __future__ import annotations

import argparse
import shutil
import struct
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fxlib  # noqa: E402
import saveedit  # noqa: E402

LIST0_LO, LIST0_HI = 0x000, 0x0EF       # D_00465A08 / D_00465A10 (6 pages x 40)
CARD = PORT / "out" / "fixtures" / "cards" / "save2"
USE_ITEM = 16601    # Stealth Pills (run B uses one from the sorted grid: slot 6 with the USER order)
# a mixed inventory: every group, in an order far from the sorted one (ids: census/invsort_category.tsv)
MIX = ["16580:3", "16143", "16657", "16641", "16251", "16747:5", "16519", "16515", "16557",
       "16683:2", "16303", "16610", "16613", "16199", "16459", "16602:2", "16100", "16355",
       "16407", "16617", "16614", "16634", "16535", "16660", "16283", "16771", "16601:2", "16231",
       "16387", "16491"]


def ranks():
    out = {}
    for l in open(PORT / "census" / "invsort_category.tsv", encoding="utf-8"):
        if l.startswith("#"):
            continue
        f = l.rstrip("\n").split("\t")
        out[int(f[0])] = (int(f[1]), f[3], f[4])
    return out


def list0(saves):
    # the live card (saveedit.find_save would take the newest run's backups/ copy first)
    s = saveedit.Save(Path(saves) / "card1")
    inv = [o for o in s.inventory() if LIST0_LO <= o["slot"] <= LIST0_HI]
    return s, sorted(inv, key=lambda o: o["slot"])


def equipped(s):
    out = {}
    for did, c in s.charas().items():
        out[did] = list(struct.unpack_from("<4h", s.b, c["off"] + 0x23A))
    return out


def body(o):
    """the object's bytes without the slot (+0x2), the flag bits (+0x4: the 'new' marks the
    menu clears) and the item-def pointer (+0xC: a host address, rebuilt on load)"""
    r = o["raw"]
    return (o["kind"], r[:2] + r[8:0xC] + r[0x10:])


def cmd_mkcard(out: Path):
    if out.exists():
        shutil.rmtree(out)
    shutil.copytree(CARD, out)
    s = saveedit.Save(out)
    s.add_items(MIX)
    s.write()
    print(f"mkcard: {out} ({len(s.inventory())} objects)")


def set_hp(saves, frac):
    """Jaster's HP (character +0x10) = frac x max HP (+0x18): nothing else changes."""
    s = saveedit.Save(Path(saves) / "card1")
    c = s.charas()[11001]
    hp_max = struct.unpack_from("<i", s.b, c["off"] + 0x18)[0]
    struct.pack_into("<i", s.b, c["off"] + 0x10, int(hp_max * frac))
    s.write()


def jaster_hp(saves):
    s = saveedit.Save(Path(saves) / "card1")
    return struct.unpack_from("<i", s.b, s.charas()[11001]["off"] + 0x10)[0]


def show(saves, check_sorted=False):
    rk = ranks()
    s, inv = list0(saves)
    bad = 0
    prev = (-1, -1)
    for o in inv:
        r, g, name = rk.get(o["item"], (99, "?", "?"))
        mark = ""
        if (r, o["item"]) < prev:
            mark, bad = "  <-- out of order", bad + 1
        prev = (r, o["item"])
        print(f"  slot {o['slot']:3d} page {o['slot'] // 40} r{o['slot'] % 40 // 8} c{o['slot'] % 8}  "
              f"uid {o['uid']:3d}  {o['item']} x{o['count']:<3d} rank {r:2d} {g:24s} {name}{mark}")
    if check_sorted:
        print(f"{'PASS' if not bad else 'FAIL'} sorted: {len(inv)} items, {bad} out of order")
    return bad == 0


def run(exe, saves, inp, fields, out, shots):
    cmd = [str(Path(exe).resolve()), "--headless", "--fields", str(fields), "--saves", str(saves),
           "--input", str(inp)]
    for f in shots:
        cmd += ["--shot", f"{f}:{out / f's{f}.png'}"]
    with open(out / f"run_{Path(inp).stem}.log", "w", encoding="utf-8", errors="replace") as log:
        rc = subprocess.run(cmd, cwd=PORT, env=fxlib.game_env(), stdout=log, stderr=subprocess.STDOUT).returncode
    print(f"run {Path(inp).name}: rc={rc}")
    return rc


def snapshot(saves):
    s, inv = list0(saves)
    return s, {o["uid"]: o for o in inv}


def cmd_play(a) -> int:
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    ok = True

    def res(cond, what):
        nonlocal ok
        print(f"{'PASS' if cond else 'FAIL'} {what}")
        ok = ok and bool(cond)

    # control first: no R2 -> saved inventory unchanged
    fresh = out / "fresh"          # the card before any run (mkcard is deterministic)
    cmd_mkcard(fresh / "saves")
    s0, inv0 = snapshot(fresh / "saves")
    ctl = out / "ctl"
    ctl.mkdir(exist_ok=True)
    if not a.reuse:
        cmd_mkcard(ctl / "saves")
    ctl_inp = ctl / "nosort.input.txt"
    ctl_inp.write_text("".join(l for l in open(HERE / "sort_save.input.txt", encoding="utf-8")
                               if "R2" not in l), encoding="utf-8")
    if not a.reuse:
        run(a.exe, ctl / "saves", ctl_inp, a.fields_a, ctl, [])
    s1, inv1 = snapshot(ctl / "saves")
    res(s1.b != s0.b, "control: run A without R2 saved the card (file changed)")
    res({u: (o["slot"], body(o)) for u, o in inv1.items()} == {u: (o["slot"], body(o)) for u, o in inv0.items()},
        "control: without R2 every list-0 object and slot unchanged")

    # run A: sort + save
    ra = out / "a"
    ra.mkdir(exist_ok=True)
    sb, before = s0, inv0
    eq_before = equipped(sb)
    print("before:")
    show(fresh / "saves")
    if not a.reuse:
        cmd_mkcard(ra / "saves")
        run(a.exe, ra / "saves", HERE / "sort_save.input.txt", a.fields_a, ra, a.shot_a)
    sa, after = snapshot(ra / "saves")
    print("after run A:")
    res(show(ra / "saves", True), "run A: list 0 in category order")
    res(set(after) == set(before), f"run A: same unique ids ({len(after)})")
    res(all(body(after[u]) == body(before[u]) for u in after if u in before),
        "run A: every object unchanged except its slot")
    res(sorted(o["slot"] for o in after.values()) == list(range(len(after))),
        "run A: slots compact from 0")
    eq_after = equipped(sa)
    res(eq_after == eq_before, "run A: equipped unique ids unchanged")
    allu = {o["uid"] for o in sa.inventory()}
    res(all(u in allu for v in eq_after.values() for u in v if u >= 0),
        "run A: every equipped unique id is in the inventory")

    # run B: load the sorted save, use Stealth Pills, save again
    rb = out / "b"
    rb.mkdir(exist_ok=True)
    if not a.reuse:
        if (rb / "saves").exists():
            shutil.rmtree(rb / "saves")
        shutil.copytree(ra / "saves", rb / "saves", ignore=shutil.ignore_patterns("backups"))
        run(a.exe, rb / "saves", HERE / "use_after_sort.input.txt", a.fields_b, rb, a.shot_b)
    sc, after_b = snapshot(rb / "saves")
    hp = [u for u, o in after.items() if o["item"] == USE_ITEM]
    res(len(hp) == 1 and after_b.get(hp[0], {}).get("count") == after[hp[0]]["count"] - 1,
        f"run B: Stealth Pills used once after the sort (count {after[hp[0]]['count'] if hp else '?'} -> "
        f"{after_b.get(hp[0], {}).get('count') if hp else '?'})")
    res(all(after_b[u]["slot"] == after[u]["slot"] for u in after if u in after_b),
        "run B: the sorted slots loaded and saved unchanged")
    res(equipped(sc) == eq_after, "run B: equipment unchanged")
    print("ALL PASS" if ok else "SOME FAIL")
    return 0 if ok else 1


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    p = sp.add_parser("mkcard")
    p.add_argument("out")
    p = sp.add_parser("inv")
    p.add_argument("saves")
    p.add_argument("--sorted", action="store_true")
    p = sp.add_parser("play")
    p.add_argument("--exe", required=True)
    p.add_argument("--out", required=True)
    p.add_argument("--fields-a", type=int, default=5600)
    p.add_argument("--fields-b", type=int, default=5600)
    p.add_argument("--shot-a", type=int, action="append", default=[])
    p.add_argument("--shot-b", type=int, action="append", default=[])
    p.add_argument("--reuse", action="store_true", help="check an earlier play's cards, run nothing")
    p.add_argument("--skip-missing", action="store_true", help="exit 77 without game data / the save2 card")
    a = ap.parse_args()
    if getattr(a, "skip_missing", False) and not ((PORT / "data").is_dir() and CARD.is_dir()):
        print("SKIP: no game data or out/fixtures/cards/save2")
        return 77
    if a.cmd == "mkcard":
        cmd_mkcard(Path(a.out).resolve())
        return 0
    if a.cmd == "inv":
        return 0 if show(Path(a.saves), a.sorted) or not a.sorted else 1
    return cmd_play(a)


if __name__ == "__main__":
    sys.exit(main())
