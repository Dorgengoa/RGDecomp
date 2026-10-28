#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Frame pacing from present logs (docs/NATIVE-VULKAN.md "Presentation").

rg-game with RG_PRESENT_LOG=path writes one row per present: the wall time (ms since the log
opened) at which the present call returned, its kind (0 read-back copy, 1 zero-copy, 2 zero-copy
composed on the GS worker, 3 interpolated) and the field.  This prints, per log, the present
intervals against the display period:

    python tools/native/present_pacing.py [--hz 144] [--skip-ms 5000] [--fields A-B] LABEL=LOG ...

  rate      presents per second over the measured span
  mean/med/sd/p1/p5/p95/p99/max   interval statistics, ms
  cv        sd / mean (0 = perfectly even)
  on-time   intervals within +-25 % of the period (one refresh)
  long      intervals > 1.5 periods (a refresh without a new image: visible hitch)
  short     intervals < 0.5 period (two presents in one refresh: one is never seen)
  kinds     presents per kind

--fields keeps presents whose field is in [A, B]; --skip-ms drops the start (loading, warm-up).
"""
import argparse
import statistics
import sys


def load(path):
    rows = []
    with open(path) as f:
        for ln in f:
            if ln.startswith('#') or not ln.strip():
                continue
            p = ln.split('\t')
            rows.append((float(p[0]), int(p[1]), int(p[2])))
    return rows


def pct(xs, q):
    if not xs:
        return 0.0
    i = min(len(xs) - 1, max(0, int(round(q / 100.0 * (len(xs) - 1)))))
    return xs[i]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('logs', nargs='+', help='LABEL=path (or a path)')
    ap.add_argument('--hz', type=float, default=144.0, help='display refresh rate (default 144)')
    ap.add_argument('--skip-ms', type=float, default=5000.0)
    ap.add_argument('--fields', default='', help='A-B: only presents of these fields')
    a = ap.parse_args()
    per = 1000.0 / a.hz
    fa, fb = (0, 1 << 62)
    if a.fields:
        x, y = a.fields.split('-')
        fa, fb = int(x), int(y)
    print('period %.3f ms (%.1f Hz)' % (per, a.hz))
    hdr = '%-14s %7s %7s %6s %6s %6s %6s %6s %6s %6s %7s %5s %7s %6s %6s  kinds'
    print(hdr % ('run', 'n', 'rate', 'mean', 'med', 'sd', 'p1', 'p5', 'p95', 'p99', 'max', 'cv', 'on-time', 'long', 'short'))
    for spec in a.logs:
        lab, _, path = spec.rpartition('=')
        if not lab:
            lab = path
        rows = [r for r in load(path) if r[0] >= a.skip_ms and fa <= r[2] <= fb]
        if len(rows) < 3:
            print('%-14s too few presents (%d)' % (lab, len(rows)))
            continue
        iv = sorted(rows[i + 1][0] - rows[i][0] for i in range(len(rows) - 1))
        span = rows[-1][0] - rows[0][0]
        mean = statistics.fmean(iv)
        sd = statistics.pstdev(iv)
        on = sum(1 for x in iv if abs(x - per) <= 0.25 * per)
        lng = sum(1 for x in iv if x > 1.5 * per)
        sht = sum(1 for x in iv if x < 0.5 * per)
        kinds = {}
        for r in rows:
            kinds[r[1]] = kinds.get(r[1], 0) + 1
        ks = ' '.join('%s:%d' % ({0: 'copy', 1: 'zc', 2: 'zc-ov', 3: 'interp'}.get(k, str(k)), n) for k, n in sorted(kinds.items()))
        print('%-14s %7d %7.1f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %7.2f %5.2f %6.1f%% %5.1f%% %5.1f%%  %s' % (
            lab, len(rows), (len(rows) - 1) * 1000.0 / span if span > 0 else 0.0, mean, pct(iv, 50), sd, pct(iv, 1), pct(iv, 5),
            pct(iv, 95), pct(iv, 99), iv[-1], sd / mean if mean > 0 else 0.0, 100.0 * on / len(iv), 100.0 * lng / len(iv),
            100.0 * sht / len(iv), ks))
    return 0


if __name__ == '__main__':
    sys.exit(main())
