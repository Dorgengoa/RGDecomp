#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Scan a 48 kHz s16 stereo WAV for pops (docs/NATIVE-AUDIO.md "Pop scan").

Two detectors:
  clicks  - |second difference| far above its local RMS (a step or spike that the
            surrounding signal does not explain), with an absolute floor so quiet
            noise does not count;
  gaps    - runs of exact digital silence inside non-silent audio; "hard" when a sample
            next to the run is loud (a dropout), soft when a sound decayed into it.

Frames map to fields with the `<wav>.fields.tsv` that RG_AUDIO_WAV writes next to the
WAV.  `--alog <RG_AUDIO_LOG tsv>` adds the host device events per field (starves, pad,
drop: the device-side causes that the engine WAV cannot show) and a correlation.

  python tools/native/audio_popscan.py out/audiocheck/a.wav [--alog out/audiocheck/a.alog.tsv]
"""
import argparse, sys, wave
from pathlib import Path
import numpy as np


def load(path):
    with wave.open(str(path), "rb") as w:
        assert w.getsampwidth() == 2 and w.getnchannels() == 2, "need s16 stereo"
        rate = w.getframerate()
        x = np.frombuffer(w.readframes(w.getnframes()), dtype="<i2").reshape(-1, 2).astype(np.float64)
    return x, rate


def movrms(v, win):
    k = np.ones(win) / win
    return np.sqrt(np.convolve(v * v, k, mode="same"))


def clicks(x, k, floor, win):
    out = []
    for ch in range(2):
        d2 = np.zeros(len(x))
        d2[1:-1] = x[2:, ch] - 2 * x[1:-1, ch] + x[:-2, ch]
        r = movrms(d2, win)
        a = np.abs(d2)
        hit = np.nonzero((a > k * np.maximum(r, 1.0)) & (a > floor))[0]
        out += [(int(i), ch, float(a[i]), float(r[i])) for i in hit]
    out.sort()
    merged = []  # one event per 64-frame neighbourhood
    for e in out:
        if merged and e[0] - merged[-1][0] < 64:
            if e[2] > merged[-1][2]:
                merged[-1] = e
            continue
        merged.append(e)
    return merged


def gaps(x, minlen, ctx_rms):
    z = np.all(x == 0, axis=1)
    lvl = movrms(np.abs(x).max(axis=1), 2048)
    res = []
    i, n = 0, len(z)
    edges = np.flatnonzero(np.diff(np.concatenate(([0], z.astype(np.int8), [0]))))
    for s, e in zip(edges[::2], edges[1::2]):
        if e - s < minlen or s == 0 or e >= n:
            continue
        before = lvl[max(0, s - 1100)]
        after = lvl[min(n - 1, e + 1100)]
        edge = int(max(np.abs(x[s - 1]).max(), np.abs(x[e]).max()))
        if before > ctx_rms and after > ctx_rms:
            res.append((int(s), int(e - s), float(before), float(after), edge))
    return res


def field_map(path):
    p = Path(str(path) + ".fields.tsv")
    if not p.exists():
        return None
    rows = [l.split("\t") for l in p.read_text().splitlines() if l and not l.startswith("#")]
    f = np.array([int(r[0]) for r in rows])
    end = np.array([int(r[3]) for r in rows])
    return f, end


def to_field(fm, frame):
    if fm is None:
        return -1
    i = int(np.searchsorted(fm[1], frame, side="right"))
    return int(fm[0][min(i, len(fm[0]) - 1)])


def splice_events(path):
    """<host wav>.events.tsv (RG_AUDIO_HOST_WAV): frame of each host splice."""
    p = Path(str(path) + ".events.tsv")
    if not p.exists():
        return None
    rows = [l.split("	") for l in p.read_text().splitlines() if l and not l.startswith("#")]
    return [(int(r[0]), f"starved={r[3]} pad={r[4]} drop={r[5]} declick={r[6]}") for r in rows]


def near_splice(sp, frame):
    if not sp:
        return ""
    d, e = min((abs(frame - f), (f, t)) for f, t in sp)
    return f" [splice {e[0] - frame:+d} frames: {e[1]}]" if d < 4096 else " [no splice near]"


def alog_events(path):
    lines = Path(path).read_text().splitlines()
    hdr = lines[0].split("\t")
    col = {h: i for i, h in enumerate(hdr)}
    ev = {}
    for l in lines[1:]:
        r = l.split("\t")
        if len(r) < len(hdr):
            continue
        s, p, d = int(r[col["starves"]]), int(r[col["pad"]]), int(r[col["drop"]])
        if s or p or d:
            ev[int(r[col["field"]])] = (s, int(r[col["starve_frames"]]), p, d, float(r[col["work_ms"]]))
    return ev


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("wav")
    ap.add_argument("--alog", help="RG_AUDIO_LOG tsv of the same run")
    ap.add_argument("--k", type=float, default=12.0, help="click: |d2| > k * local RMS(d2)")
    ap.add_argument("--floor", type=float, default=1500.0, help="click: |d2| absolute floor")
    ap.add_argument("--win", type=int, default=480, help="local RMS window, frames")
    ap.add_argument("--gap", type=int, default=16, help="min zero run, frames")
    ap.add_argument("--edge", type=int, default=64, help="gap: hard if a neighbour sample >= this")
    ap.add_argument("--list", type=int, default=25, help="events to print")
    a = ap.parse_args()
    x, rate = load(a.wav)
    fm = field_map(a.wav)
    sp = splice_events(a.wav)
    c = clicks(x, a.k, a.floor, a.win)
    g = gaps(x, a.gap, 200.0)
    print(f"{a.wav}: {len(x)} frames ({len(x)/rate:.1f} s), peak {int(np.abs(x).max())}")
    hard = [e for e in g if e[4] >= a.edge]
    print(f"clicks {len(c)}  gaps {len(g)} (hard-edged {len(hard)}: a sample >= {a.edge} next to the gap)")
    for i, ch, v, r in c[: a.list]:
        print(f"  click frame {i} field {to_field(fm, i)} ch {ch} |d2| {v:.0f} local {r:.0f} "
              f"x[-2..2] {x[max(0,i-2):i+3, ch].astype(int).tolist()}{near_splice(sp, i)}")
    for s, n, b, af, ed in g[: a.list]:
        print(f"  gap frame {s} field {to_field(fm, s)} len {n} level before {b:.0f} after {af:.0f} "
              f"edge {ed}{' HARD' if ed >= a.edge else ' (soft: a sound decayed out)'}{near_splice(sp, s)}")
    if a.alog:
        ev = alog_events(a.alog)
        print(f"alog: {len(ev)} fields with device events "
              f"(starves {sum(e[0] for e in ev.values())}, starve frames {sum(e[1] for e in ev.values())}, "
              f"pad {sum(e[2] for e in ev.values())}, drop {sum(e[3] for e in ev.values())})")
        for f in sorted(ev)[: a.list]:
            s, sf, p, d, wk = ev[f]
            print(f"  field {f}: starves {s} ({sf} frames) pad {p} drop {d} work {wk:.1f} ms")
        if fm is not None:
            cf = {to_field(fm, e[0]) for e in c} | {to_field(fm, e[0]) for e in g}
            near = sum(1 for f in cf if any(abs(f - q) <= 1 for q in ev))
            print(f"engine-WAV events within 1 field of a device event: {near}/{len(cf)}")
    if sp is not None:
        print(f"host splices: {len(sp)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
