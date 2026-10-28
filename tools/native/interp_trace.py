#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Does interpolated presentation produce even in-between motion?  (docs/NATIVE-RENDER.md
"13c", history "2026-10-26 (interp3)")

Reads the trace rg-game writes with RG_INTERP_TRACE=path (nr_interp.c trace_row: one row per
present request on the GS worker: wall ms, tau, outcome, shown / previous frame, alpha, vis, iv,
the displayed camera position + both endpoints, up to 16 objects key:x,y,z) and checks, over the
presents in order:

  model      the displayed content time S = vis - iv + alpha * iv against the host time tau:
             dS / dtau per present (1 = the shown motion advances exactly with time); holds
             (alpha clamped while presents go on = a repeated image), backwards steps
  objects    per object key (and the camera) with motion: the displayed position's step per
             present over tau; "repeat" a step < 2 % of the local mean between two moving neighbour
             steps (an isolated held image), "jump" a step > 2.5x both neighbour steps, "back" a
             step against the local motion direction, the switch ratio (median step at a
             game-frame switch / the local mean step; 1 = even, ~presents per frame = stepped), the
             share of the motion made at the switches -- and the same for the snap control
             computed from the same trace (every present showing the newest frame: alpha 1).
             Steps into / out of a cut frame (outcome 3: shown as recorded, a snap by design) are
             kept apart (count, largest).
  cuts       outcome 3 rows (no interpolation over a camera cut), the largest camera move P->L an
             interpolated pass spanned, history resets (no log / no previous)
  wall       present request intervals (wall ms): rate, cv, p99, intervals > 1.5 periods (with
             --hz: against that period, else the median)

    python tools/native/interp_trace.py TRACE [--from-ms N] [--hz 144] [--json OUT] [--fail]

--fail exits 1 when the motion check fails: switch ratio > 1.6, any backwards model step,
repeats or jumps > 2 % of the moving object steps.
"""
import argparse
import json
import math
import statistics
import sys


def load(path, from_ms=0.0):
    rows = []
    with open(path, encoding="utf-8", errors="replace") as f:
        for ln in f:
            if ln.startswith("#") or not ln.strip():
                continue
            p = ln.rstrip("\r\n").split("\t")
            if len(p) < 8:
                continue
            r = {"wall": float(p[0]), "tau": float(p[1]), "code": int(p[2]), "frame": int(p[3]),
                 "prev": int(p[4]), "a": float(p[5]), "vis": float(p[6]), "iv": float(p[7]),
                 "cam": None, "camP": None, "camL": None, "obj": {}}
            if len(p) >= 17:
                v = [float(x) for x in p[8:17]]
                if all(math.isfinite(x) for x in v[:3]):
                    r["cam"], r["camP"], r["camL"] = tuple(v[0:3]), tuple(v[3:6]), tuple(v[6:9])
                for o in p[17:]:
                    k, _, xyz = o.partition(":")
                    try:
                        r["obj"][k] = tuple(float(x) for x in xyz.split(","))
                    except ValueError:
                        pass
            if r["wall"] >= from_ms:
                rows.append(r)
    return rows


def sub(a, b):
    return tuple(x - y for x, y in zip(a, b))


def norm(a):
    return math.sqrt(sum(x * x for x in a))


def dot(a, b):
    return sum(x * y for x, y in zip(a, b))


def track_stats(series, frames, taus, codes=None):
    """series: list of (present index, pos) where the track exists (only consecutive presents
    are compared)."""
    out = {"steps": 0, "moving": 0, "repeat": 0, "jump": 0, "back": 0, "sw": [], "cut": [],
           "at_switch": 0.0, "path": 0.0}
    steps = []   # (i, step vector, dtau, frame switch?) or None
    for (i0, p0), (i1, p1) in zip(series, series[1:]):
        if i1 != i0 + 1:
            steps.append(None)
            continue
        dt = taus[i1] - taus[i0]
        if dt <= 1e-6:
            steps.append(None)
            continue
        if codes and (codes[i1] == 3 or codes[i0] == 3):
            # into / out of a cut frame (shown as recorded: a snap by design), kept apart
            out["cut"].append(norm(sub(p1, p0)))
            steps.append(None)
            continue
        steps.append((i1, sub(p1, p0), dt, frames[i1] != frames[i0]))
    for k, s in enumerate(steps):
        if s is None:
            continue
        # local window: 6 steps either side (about two game frames at 144 Hz / 30 Hz logic)
        win = [x for x in steps[max(0, k - 6):k + 7] if x is not None]
        if len(win) < 5:
            continue
        vel = [norm(x[1]) / x[2] for x in win]
        mv = statistics.mean(vel)
        net = [0.0, 0.0, 0.0]
        for x in win:
            for j in range(3):
                net[j] += x[1][j]
        # moving steadily: the window's net displacement is most of its path
        path = sum(norm(x[1]) for x in win)
        if mv <= 1e-4 or path <= 1e-4 or norm(net) < 0.6 * path:
            continue
        out["moving"] += 1
        v = norm(s[1]) / s[2]
        # isolated glitches against the two neighbour steps (a motion that stops or starts for a
        # whole game frame is the game's own motion, not a repeat)
        nbs = [norm(x[1]) / x[2] for x in (steps[k - 1] if k > 0 else None, steps[k + 1] if k + 1 < len(steps) else None)
               if x is not None]
        if len(nbs) == 2 and min(nbs) > 0.3 * mv and v < 0.02 * mv:
            out["repeat"] += 1
        elif len(nbs) == 2 and min(nbs) > 0.1 * mv and v > 2.5 * max(nbs):
            out["jump"] += 1
        if dot(s[1], net) < 0 and norm(s[1]) > 0.1 * mv * s[2]:
            out["back"] += 1
        if s[3]:
            # the step at a game-frame switch against the window's mean speed (1 = even; the
            # snap control: all motion at the switches, about presents-per-frame)
            out["sw"].append(v / mv)
        out["at_switch"] += norm(s[1]) if s[3] else 0.0
        out["path"] += norm(s[1])
        out["steps"] += 1
    return out


def analyse(rows, hz=0.0):
    res = {}
    codes = {}
    for r in rows:
        codes[r["code"]] = codes.get(r["code"], 0) + 1
    res["requests"] = len(rows)
    res["outcomes"] = {{0: "pass", 1: "no log", 2: "no previous", 3: "cut", 4: "alpha 1"}.get(k, str(k)): v
                       for k, v in sorted(codes.items())}
    # model time
    holds, back, dsdt = 0, 0, []
    prevS = prevtau = None
    for r in rows:
        if r["code"] not in (0, 4) or r["iv"] <= 0:
            prevS = prevtau = None
            continue
        s = r["vis"] - r["iv"] + (r["a"] if r["code"] == 0 else 1.0) * r["iv"]
        if prevS is not None:
            dt = r["tau"] - prevtau
            if dt > 1e-6:
                dsdt.append((s - prevS) / dt)
                if s < prevS - 1e-4:
                    back += 1
                elif abs(s - prevS) < 1e-4:
                    holds += 1
        prevS, prevtau = s, r["tau"]
    res["model"] = {"steps": len(dsdt), "dS/dtau mean": statistics.mean(dsdt) if dsdt else 0.0,
                    "dS/dtau sd": statistics.pstdev(dsdt) if len(dsdt) > 1 else 0.0,
                    "holds": holds, "back": back,
                    "within 10 %": sum(1 for q in dsdt if abs(q - 1.0) <= 0.1) / len(dsdt) if dsdt else 0.0}
    # tracks: interpolated (as displayed) and snap (alpha 1 = the shown frame's own position)
    frames = [r["frame"] for r in rows]
    codes_l = [r["code"] for r in rows]
    taus = [r["tau"] for r in rows]
    tracks = {}
    for i, r in enumerate(rows):
        if r["code"] not in (0, 3, 4):
            continue
        if r["cam"]:
            tracks.setdefault("camera", []).append((i, r["cam"]))
        for k, p in r["obj"].items():
            tracks.setdefault(k, []).append((i, p))
    snap = [(i, r["camL"]) for i, r in enumerate(rows) if r["code"] in (0, 3, 4) and r["camL"]]
    tot = {"steps": 0, "moving": 0, "repeat": 0, "jump": 0, "back": 0, "sw": [], "at_switch": 0.0, "path": 0.0,
           "cuts": 0, "cutmax": 0.0}
    cam = None
    for k, ser in tracks.items():
        st = track_stats(ser, frames, taus, codes_l)
        if k == "camera":
            cam = st
        for x in ("steps", "moving", "repeat", "jump", "back", "at_switch", "path"):
            tot[x] += st[x]
        tot["sw"] += st["sw"]
        if st["cut"]:
            tot["cuts"] += len(st["cut"])
            tot["cutmax"] = max(tot["cutmax"], max(st["cut"]))
    snapst = track_stats(snap, frames, taus, codes_l) if snap else None

    def summ(st):
        if not st:
            return None
        m = max(1, st["moving"])
        return {"moving steps": st["moving"], "repeat %": 100.0 * st["repeat"] / m, "jump %": 100.0 * st["jump"] / m,
                "back %": 100.0 * st["back"] / m, "switches": len(st["sw"]),
                "switch ratio": statistics.median(st["sw"]) if st["sw"] else 0.0,
                "motion at switches %": 100.0 * st["at_switch"] / st["path"] if st["path"] else 0.0}
    res["objects"] = summ(tot)
    res["objects"]["tracks"] = len(tracks)
    res["objects"]["steps at cut frames"] = tot["cuts"]
    res["objects"]["largest step at a cut"] = tot["cutmax"]
    res["camera"] = summ(cam)
    res["camera snap control"] = summ(snapst)
    # cuts and resets
    jp = [norm(sub(r["camL"], r["camP"])) for r in rows if r["code"] == 0 and r["camL"]]
    res["cuts"] = {"cut presents": codes.get(3, 0), "cut frames": len({r["frame"] for r in rows if r["code"] == 3}),
                   "largest camera move in a pass": max(jp) if jp else 0.0,
                   "p99 camera move in a pass": sorted(jp)[int(0.99 * (len(jp) - 1))] if jp else 0.0,
                   "resets (no log / no previous)": codes.get(1, 0) + codes.get(2, 0)}
    # wall intervals
    w = [b["wall"] - a["wall"] for a, b in zip(rows, rows[1:])]
    if w:
        med = statistics.median(w)
        per = 1000.0 / hz if hz else med
        res["wall"] = {"rate /s": 1000.0 * len(w) / max(1e-6, rows[-1]["wall"] - rows[0]["wall"]),
                       "mean ms": statistics.mean(w), "median ms": med,
                       "cv": statistics.pstdev(w) / statistics.mean(w) if statistics.mean(w) > 0 else 0.0,
                       "p99 ms": sorted(w)[int(0.99 * (len(w) - 1))], "max ms": max(w),
                       "long (>1.5 period)": sum(1 for x in w if x > 1.5 * per),
                       "on time (+-25 %)": sum(1 for x in w if abs(x - per) <= 0.25 * per) / len(w)}
    return res


def verdict(res):
    bad = []
    o = res["objects"] or {}
    if o.get("switch ratio", 0) > 1.6:
        bad.append("switch ratio %.2f > 1.6" % o["switch ratio"])
    if res["model"]["back"]:
        bad.append("%d backwards model steps" % res["model"]["back"])
    if o.get("repeat %", 0) > 2.0 or o.get("jump %", 0) > 2.0:
        bad.append("repeats %.1f %% / jumps %.1f %%" % (o.get("repeat %", 0), o.get("jump %", 0)))
    return bad


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("trace")
    ap.add_argument("--from-ms", type=float, default=0.0)
    ap.add_argument("--hz", type=float, default=0.0, help="judge wall intervals against this present rate")
    ap.add_argument("--json")
    ap.add_argument("--fail", action="store_true")
    a = ap.parse_args(argv)
    rows = load(a.trace, a.from_ms)
    if len(rows) < 10:
        print("%s: %d rows (run with RG_INTERP=1 RG_INTERP_TRACE=path)" % (a.trace, len(rows)))
        return 1
    res = analyse(rows, a.hz)
    bad = verdict(res)
    res["verdict"] = "FAIL: " + "; ".join(bad) if bad else "PASS"

    def fmt(d):
        return ", ".join("%s %s" % (k, ("%.3f" % v) if isinstance(v, float) else v) for k, v in d.items()) if d else "-"
    print("%s: %d requests; %s" % (a.trace, res["requests"], fmt(res["outcomes"])))
    print("  model:   " + fmt(res["model"]))
    print("  objects: " + fmt(res["objects"]))
    print("  camera:  " + fmt(res["camera"]))
    print("  camera, snap control (alpha 1): " + fmt(res["camera snap control"]))
    print("  cuts:    " + fmt(res["cuts"]))
    if "wall" in res:
        print("  wall:    " + fmt(res["wall"]))
    print("  verdict: " + res["verdict"])
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump(res, f, indent=1)
    return 1 if (a.fail and bad) else 0


if __name__ == "__main__":
    sys.exit(main())
