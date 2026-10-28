#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Census of full-screen screens in RG_LAYOUT_LOG files (docs/WIDESCREEN.md "Stage 3"):

  menus   tasks laid out as a stage 3 menu (one centred 4:3 element), fields seen
  late    a menu task's first frame: its packets drawn before its first "(menu)" packet,
          laid out by another anchor than the centre (the "first-frame stale position")
  nonidx  candidate menus the stage 3 detection misses: a game task draws a covering
          picture that is NOT indexed-colour (direct colour: a scene capture or a direct
          colour background) and, in the same field, >= --min packets of its own that were
          laid out per element (left / right / centre).  Grouped by (task, bg caller, psm).
  spread  per-element layouts spanning the screen: a game task (not a menu task) whose
          laid-out packets in one field reach from the left third to the right third
          (left AND right anchors, union >= 85 % of the screen): whole-screen designs that
          stage 2 splits into corner groups (fine for HUD, wrong for a screen-sized menu)
  strips  "append:" failures (a background side left to the black clear)

    python tools/wide/menucensus.py LOG [LOG ...] --exe EXE [--min 6] [--fields]
EXE: the exe that wrote the logs (its .map names tasks and callers).
"""
import argparse
import bisect
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from laysum import name, syms  # noqa: E402

PK = re.compile(r"(\d+) pk task=(\w+) caller=(\w+) x=(\S+)\.\.(\S+) y=(\S+)\.\.(\S+) n=(-?\d+) "
                r"psm=(-?\d+) fbp=(\S+) (\S+)( \(menu\)| \(own\))?")
INDEXED = {0x13, 0x14, 0x1B, 0x24, 0x2C}


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("logs", nargs="+")
    ap.add_argument("--exe", required=True)
    ap.add_argument("--min", type=int, default=6)
    ap.add_argument("--fields", action="store_true", help="list the fields of every row")
    a = ap.parse_args(argv)
    tab = syms(a.exe.rsplit(".", 1)[0] + ".map")
    keys = [k for k, _ in tab]
    nm = lambda h: name(tab, keys, int(h, 16))  # noqa: E731
    menus = defaultdict(set)
    late = defaultdict(set)
    nonidx = defaultdict(set)
    fails = defaultdict(int)
    spread = defaultdict(set)
    for lp in a.logs:
        run = Path(lp).name.split(".")[0]
        field = None
        rows = []
        last_menu = {}

        def flush():
            if field is None:
                return
            seen_menu = set()
            pending = defaultdict(list)
            per_task = defaultdict(int)
            box = {}
            anch = defaultdict(set)
            covers = []
            for t, c, x0, x1, y0, y1, psm, dec, tag in rows:
                if tag == " (menu)":
                    if t not in seen_menu and last_menu.get(t, -99) < field - 4:
                        for pc, pdec in pending[t]:
                            if pdec in ("left", "right"):
                                late[(run, nm(t), nm(pc), pdec)].add(field)
                    seen_menu.add(t)
                    menus[(run, nm(t))].add(field)
                elif t not in seen_menu and dec in ("left", "right", "center"):
                    pending[t].append((c, dec))
                if t != "00000000" and dec in ("left", "right", "center") and tag != " (menu)":
                    per_task[t] += 1
                    b = box.get(t, (1e9, -1e9))
                    box[t] = (min(b[0], x0), max(b[1], x1))
                    anch[t].add(dec)
                if (t != "00000000" and dec == "full" and psm >= 0 and psm not in INDEXED and
                        x0 <= 4 and x1 >= 508 and y1 - y0 >= 400):
                    covers.append((t, c, psm))
            for t in seen_menu:
                last_menu[t] = field
            for t, (b0, b1) in box.items():
                if t not in seen_menu and {"left", "right"} <= anch[t] and b1 - b0 >= 0.85 * 512                         and per_task[t] >= a.min:
                    spread[(run, nm(t))].add(field)
            for t, c, psm in covers:
                if t not in seen_menu and per_task[t] >= a.min:
                    nonidx[(run, nm(t), nm(c), psm)].add(field)

        for ln in open(lp, errors="replace"):
            if " frame s=" in ln:
                flush()
                field = int(ln.split()[0])
                rows = []
                continue
            if ln.startswith("  append:"):
                fails[(run, ln.strip().split("(")[0])] += 1
                continue
            m = PK.match(ln)
            if not m:
                continue
            g = m.groups()
            rows.append((g[1], g[2], float(g[3]), float(g[4]), float(g[5]), float(g[6]), int(g[8]),
                         g[10], g[11]))
        flush()

    def rng(fs):
        fs = sorted(fs)
        return f"{len(fs):5d} fields {fs[0]}..{fs[-1]}" + (f" {fs}" if a.fields else "")
    print("== menus (stage 3 menu tasks)")
    for k, fs in sorted(menus.items()):
        print(f"  {k[0]:14s} {k[1]:40s} {rng(fs)}")
    print("== late (menu's first frame: packets before its background, not centred)")
    for k, fs in sorted(late.items()):
        print(f"  {k[0]:14s} {k[1]:36s} {k[2]:36s} {k[3]:6s} {rng(fs)}")
    print(f"== nonidx (direct-colour covering picture + >= {a.min} per-element packets, same task)")
    for k, fs in sorted(nonidx.items()):
        print(f"  {k[0]:14s} {k[1]:36s} {k[2]:36s} psm={k[3]:<3d} {rng(fs)}")
    print(f"== spread (non-menu task, left + right groups spanning >= 85 % of the screen, >= {a.min} packets)")
    for k, fs in sorted(spread.items()):
        print(f"  {k[0]:14s} {k[1]:40s} {rng(fs)}")
    print("== strips: append failures")
    for k, n in sorted(fails.items()):
        print(f"  {k[0]:14s} {k[1]} x{n}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
