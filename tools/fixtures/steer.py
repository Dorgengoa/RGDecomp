#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Walk the field leader to a target with `#!stick` lines, closed loop from a
save state (docs/TEST-FIXTURES.md "Navigation (steer.py)").

    python tools/fixtures/steer.py --from STATE --input BASE.txt --out D \\
        (--target X,Z [X,Z ...] | --marker) [--radius 40] [--step 30]
        [--max-steps 200] [--exe EXE] [--stop-on-mode] [--saves DIR]
        [--search [--cell 60] [--max-expand 60]]

Per step: read the leader's position and the camera (tools/trace/navprobe.py,
at the end of the previous segment), aim at the next waypoint (the stick is
camera-relative: navprobe.stick_for), play STEP fields with that stick from
the state, save a state at the end.  A step that gets less than --min-gain of
the expected progress is retried from the same state with headings turned by
+-45, +-90, +-135, 180 degrees; the best one (progress plus --explore x new
ground reached) is kept and followed for --detour
steps (wall following), then the direct heading is tried again.  --marker
takes the first objective marker of the minimap (the yellow star) as the
target.  The game mode is watched: with --stop-on-mode the walk ends when it
leaves 6 (field) or the map id changes (event, battle, area change) and the
state there is kept.

Output in D: `route.txt` = BASE + the accepted stick lines (and a
`# steer:` comment per step), `walk.tsv` (field, x, z, heading, gain, mode),
`last.rgstate` (the state at the end), step dirs s<field>_<k>/.  The stick
lines start after the state's field (play.py rule), so route.txt replays the
walk from STATE and as part of a continuous run.  One rg-game at a time.

--search replaces the greedy walk with A* over a walkability grid sampled on demand
(see search()): slower (8 runs per expanded cell) but it finds ways around walls and
out of pockets the greedy walk oscillates in.
"""
from __future__ import annotations

import argparse
import math
import shutil
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "trace"))
import fxlib  # noqa: E402
import navprobe as nav  # noqa: E402

OFFS = [math.radians(d) for d in (45, -45, 90, -90, 135, -135, 180)]


def search(a, exe, out, saves, state, base, r) -> int:
    """--search: A* over a walkability grid sampled on demand.  A node is a grid cell
    (--cell units) reached by a state; expanding it plays --step fields in 8 world
    headings from that state (one rg-game run each), and every heading that ends in a
    new cell becomes a node (g = walked distance, h = straight distance to the target).
    The probe results are the sampled grid (grid.tsv: cell, x, z, reached-from, mode),
    so walls and dead ends are learnt instead of pushed into.  Ends at the first node
    within --radius of the target; route.txt = BASE + the stick lines of that path
    (each starts after its state's field, so it replays continuously)."""
    import heapq
    if len(a.target) != 1 and not a.marker:
        print("steer: --search takes one --target X,Z (or --marker)")
        return 2
    tx, tz = (float(v) for v in a.target[0].split(",")) if a.target else (None, None)
    if a.marker:
        mk = nav.run_probe(exe, state, base, fxlib.peek(state)["field"] + 4, out / "probe1",
                           marker=True, saves=saves)["markers"]
        if not mk:
            print("steer: no objective marker on the minimap")
            return 2
        tx, tz = mk[0][0], mk[0][2]
    cell = a.cell
    key = lambda p: (int(math.floor(p[0] / cell)), int(math.floor(p[2] / cell)))  # noqa: E731
    f0 = fxlib.peek(state)["field"]
    start = {"pos": r["pos"], "cam": r["cam"], "state": state, "field": f0, "lines": [], "g": 0.0}
    mode0, map0 = r["mode"], r["mapid"]
    seen = {key(r["pos"])}
    heap = [(math.hypot(tx - r["pos"][0], tz - r["pos"][2]), 0, start)]
    grid = open(out / "grid.tsv", "w", encoding="utf-8")
    grid.write("cell_x\tcell_z\tx\tz\tfrom_x\tfrom_z\tmode\n")
    tie, expanded, best = 1, 0, start
    hdg = [math.radians(d) for d in range(0, 360, 45)]
    while heap and expanded < a.max_expand:
        _, _, nd = heapq.heappop(heap)
        p = nd["pos"]
        d = math.hypot(tx - p[0], tz - p[2])
        if d < math.hypot(tx - best["pos"][0], tz - best["pos"][2]):
            best = nd
        if d < a.radius:
            best = nd
            break
        expanded += 1
        print(f"  expand {expanded:3d} cell {key(p)} pos ({p[0]:8.1f}, {p[2]:8.1f}) dist {d:7.1f} "
              f"g {nd['g']:7.1f} open {len(heap)}", flush=True)
        f = nd["field"]
        for k, h in enumerate(hdg):
            lx, ly = nav.stick_for(h, nd["cam"])
            ln = f"#!stick {f + 1} {f + a.step} {lx} {ly}  # steer: heading {math.degrees(h):.0f}\n"
            d_ = out / f"e{expanded:03d}_{k}"
            rr = nav.run_probe(exe, nd["state"], base + "".join(nd["lines"]) + ln, f + a.step, d_,
                               save=f + a.step, saves=saves)
            if not rr["pos"]:
                shutil.rmtree(d_, ignore_errors=True)
                continue
            q = rr["pos"]
            grid.write(f"{key(q)[0]}\t{key(q)[1]}\t{q[0]:.1f}\t{q[2]:.1f}\t{p[0]:.1f}\t{p[2]:.1f}\t{rr['mode']}\n")
            if rr["mode"] != mode0 or rr["mapid"] != map0 or key(q) in seen:
                shutil.rmtree(d_, ignore_errors=True)
                continue
            seen.add(key(q))
            st = out / f"n{tie:04d}.rgstate"
            shutil.copy(rr["state"], st)
            shutil.rmtree(d_, ignore_errors=True)
            child = {"pos": q, "cam": rr["cam"] or nd["cam"], "state": st, "field": f + a.step,
                     "lines": nd["lines"] + [ln], "g": nd["g"] + math.dist((p[0], p[2]), (q[0], q[2]))}
            heapq.heappush(heap, (child["g"] + math.hypot(tx - q[0], tz - q[2]), tie, child))
            tie += 1
        grid.flush()
    grid.close()
    (out / "route.txt").write_text(base + "".join(best["lines"]), encoding="utf-8")
    shutil.copy(best["state"], out / "last.rgstate")
    p = best["pos"]
    d = math.hypot(tx - p[0], tz - p[2])
    ok = d < a.radius
    print(f"steer: search {'arrived' if ok else 'stopped'} after {expanded} expansions at field {best['field']}, "
          f"pos ({p[0]:.1f}, {p[2]:.1f}), {d:.0f} from ({tx:.0f}, {tz:.0f}); {out / 'route.txt'}")
    return 0 if ok else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="frm", required=True, help=".rgstate written by --exe")
    ap.add_argument("--input", required=True, help="base input (lines up to the state's field)")
    ap.add_argument("--out", required=True)
    ap.add_argument("--target", nargs="*", default=[], help="waypoints X,Z")
    ap.add_argument("--marker", action="store_true", help="target = first minimap objective marker")
    ap.add_argument("--radius", type=float, default=40.0)
    ap.add_argument("--step", type=int, default=30)
    ap.add_argument("--max-steps", type=int, default=200)
    ap.add_argument("--min-gain", type=float, default=0.35, help="fraction of the step's expected progress")
    ap.add_argument("--detour", type=int, default=3)
    ap.add_argument("--explore", type=float, default=0.7,
                    help="weight of reaching unvisited ground when the direct heading is blocked")
    ap.add_argument("--stop-on-mode", action="store_true")
    ap.add_argument("--release", type=int, default=0, help="after arriving, play N fields stick-centred")
    ap.add_argument("--keep", action="store_true", help="keep every trial's dir (logs, states)")
    ap.add_argument("--search", action="store_true",
                    help="A* over a grid sampled on demand (8 headings per node) instead of the greedy walk")
    ap.add_argument("--cell", type=float, default=60.0, help="--search grid cell size (units)")
    ap.add_argument("--max-expand", type=int, default=60, help="--search node budget (8 runs each)")
    ap.add_argument("--exe")
    ap.add_argument("--saves", help="memory-card dir for the runs (default: <out>/saves)")
    a = ap.parse_args(argv)

    exe = fxlib.exe_path(a.exe)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    saves = Path(a.saves).resolve() if a.saves else out / "saves"
    state = Path(a.frm).resolve()
    f = fxlib.peek(state)["field"]
    base = Path(a.input).read_text(encoding="utf-8").rstrip("\n") + "\n"
    if "#!stick 1 0" not in base:
        base += "#!stick 1 0\n"
    lines: list[str] = []

    def text():
        return base + "".join(lines)

    r = nav.run_probe(exe, state, text(), f + 4, out / "probe0", saves=saves)
    if a.marker:
        r["markers"] = nav.run_probe(exe, state, text(), f + 4, out / "probe1", marker=True,
                                     saves=saves)["markers"]
    # the probe ran 2 fields past the state with no new input: re-read the
    # position from the state itself would need a run anyway; 2 idle fields
    # do not move a standing leader
    if not r["pos"]:
        print(f"steer: no leader position at field {f} (mode {r['mode']}); is this a field?")
        return 2
    if a.search:
        return search(a, exe, out, saves, state, base, r)
    wps = [tuple(float(v) for v in t.split(",")) for t in a.target]
    if a.marker:
        if not r["markers"]:
            print("steer: no objective marker on the minimap")
            return 2
        mk = r["markers"][0]
        print(f"steer: marker at ({mk[0]:.1f}, {mk[2]:.1f})")
        wps.append((mk[0], mk[2]))
    if not wps:
        print("steer: no target")
        return 2
    pos, cam, mode0, map0 = r["pos"], r["cam"], r["mode"], r["mapid"]
    print(f"steer: field {f} pos ({pos[0]:.1f}, {pos[2]:.1f}) mode {mode0} map {map0}")
    tsv = open(out / "walk.tsv", "w", encoding="utf-8")
    tsv.write("field\tx\tz\theading_deg\tgain\tmode\tmap\n")
    speed = 1.2          # units per field, learned (running is ~2.5)
    detour_h, detour_left = None, 0
    wi = 0
    visited = [(pos[0], pos[2])]
    status = "max-steps"
    for step in range(a.max_steps):
        tx, tz = wps[wi]
        d0 = math.hypot(tx - pos[0], tz - pos[2])
        if d0 < a.radius:
            print(f"steer: waypoint {wi} ({tx:.0f}, {tz:.0f}) reached at field {f}")
            wi += 1
            if wi == len(wps):
                status = "arrived"
                break
            continue
        h_direct = nav.heading(tx - pos[0], tz - pos[2])
        n = min(a.step, max(4, int(d0 / max(speed, 0.5)) + 2))
        want = speed * n

        def trial(h, k):
            lx, ly = nav.stick_for(h, cam)
            ln = f"#!stick {f + 1} {f + n} {lx} {ly}  # steer: heading {math.degrees(h):.0f}\n"
            rr = nav.run_probe(exe, state, base + "".join(lines) + ln, f + n, out / f"s{f}_{k}",
                               save=f + n, saves=saves)
            if not rr["pos"]:
                return None, ln, rr
            g = d0 - math.hypot(tx - rr["pos"][0], tz - rr["pos"][2])
            return g, ln, rr

        cands = []
        first_h = detour_h if detour_left > 0 else h_direct
        g, ln, rr = trial(first_h, 0)
        cands.append((g if g is not None else -1e9, ln, rr, first_h))
        changed = rr["mode"] != mode0 or rr["mapid"] != map0
        if a.stop_on_mode and changed:
            best = cands[0]
        elif g is None or g < a.min_gain * want:
            for k, o in enumerate(OFFS, 1):
                h = h_direct + o
                g2, ln2, rr2 = trial(h, k)
                cands.append((g2 if g2 is not None else -1e9, ln2, rr2, h))
            def score(c):
                # progress toward the waypoint, plus a bonus for reaching ground not walked
                # yet (min distance to every visited position): slides along walls and
                # out of dead ends instead of pushing into them
                if c[2]["mode"] != mode0 and a.stop_on_mode or not c[2]["pos"]:
                    return -1e8
                p2 = (c[2]["pos"][0], c[2]["pos"][2])
                nov = min(math.dist(p2, v) for v in visited)
                stuck = math.dist(p2, (pos[0], pos[2])) < 2.0   # did not move: worst choice
                return c[0] + a.explore * min(nov, want) - (1e6 if stuck else 0)
            best = max(cands, key=score)
            if best[3] != h_direct:
                detour_h, detour_left = best[3], a.detour
            else:
                detour_left = 0
        else:
            best = cands[0]
            if detour_left > 0:
                detour_left -= 1
        g, ln, rr, h = best
        g = g if g > -1e8 else 0.0
        if rr["pos"] is None and rr["mode"] == mode0:
            print(f"steer: field {f}: no position after the step (mode {rr['mode']})")
            status = "lost"
            break
        lines.append(ln)
        f += n
        st = out / f"step{step:03d}.rgstate"
        shutil.copy(rr["state"], st)
        state = st
        if rr["pos"]:
            moved = math.dist((pos[0], pos[2]), (rr["pos"][0], rr["pos"][2]))
            speed = max(0.8, min(4.0, 0.5 * speed + 0.5 * moved / n))
            pos = rr["pos"]
            visited.append((pos[0], pos[2]))
        cam = rr["cam"] or cam
        tsv.write(f"{f}\t{pos[0]:.1f}\t{pos[2]:.1f}\t{math.degrees(h):.0f}\t{g:.1f}\t{rr['mode']}\t{rr['mapid']}\n")
        tsv.flush()
        print(f"  {step:3d} field {f:6d} pos ({pos[0]:8.1f}, {pos[2]:8.1f}) dist {d0 - g:7.1f} "
              f"heading {math.degrees(h):5.0f} gain {g:6.1f} mode {rr['mode']} map {rr['mapid']}"
              f"{' detour' if detour_left else ''}", flush=True)
        (out / "route.txt").write_text(text(), encoding="utf-8")
        if a.stop_on_mode and (rr["mode"] != mode0 or rr["mapid"] != map0):
            status = f"mode {rr['mode']} map {rr['mapid']}"
            break
        # prune step dirs of the trials (keep the accepted state only)
        for k in range(len(OFFS) + 1 if not a.keep else 0):
            shutil.rmtree(out / f"s{f - n}_{k}", ignore_errors=True)
    if a.release and status == "arrived":
        lines.append(f"# steer: release {a.release} fields\n")
        rr = nav.run_probe(exe, state, text(), f + a.release, out / "release", save=f + a.release, saves=saves)
        f += a.release
        shutil.copy(rr["state"], out / "release.rgstate")
        state = out / "release.rgstate"
        print(f"steer: released, pos {rr['pos']} mode {rr['mode']}")
    (out / "route.txt").write_text(text(), encoding="utf-8")
    shutil.copy(state, out / "last.rgstate")
    print(f"steer: {status} at field {f}, pos ({pos[0]:.1f}, {pos[2]:.1f}); {out / 'route.txt'}, "
          f"{out / 'last.rgstate'}")
    return 0 if status == "arrived" else 1


if __name__ == "__main__":
    sys.exit(main())
