#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Is present / pacing jitter at high refresh caused by presenting on the game thread?
(docs/NATIVE-THREADS.md "3h.2", history "2026-10-26 (interp3)")

Joins a run's $RG_PRESENT_LOG (ms, kind, field, present_ms: the 4th column is the time the
present took on the game thread, from the interpolation pass request to the window's present
returning) with its $RG_FIELD_TIMES (per field: step_ms = the EE phase, sync_ms = draining the GS
worker, pace_ms = sleeping, ...) and splits the present intervals:

  between   no game phase ran between the two presents (interpolated presents inside one
            phase gap): only presentation work and the pacer's sleep sit in the interval
  phase     one or more phases ran in between: their step / sync / audio / pump time is in it

For each class: count, mean, p95 / p99, intervals longer than 1.5 periods ("late") and what the
late ones contained: the phases' game-thread work (step + sync + audio + pump + post) and the
presents' own present_ms.  A present thread can only win back the part of a late interval that
is presentation work on the game thread (present_ms of the presents involved); phase work stays
on the game thread, and the pass the present needs runs on the same GS worker as the phase's GS
input, so a present thread would wait for it too.

    python tools/native/present_thread.py --hz 144 PRESENT_TSV FIELD_TIMES_TSV [--skip-ms 5000]
"""
import argparse
import statistics
import sys


def pct(xs, q):
    xs = sorted(xs)
    return xs[min(len(xs) - 1, int(q * (len(xs) - 1)))] if xs else 0.0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("present")
    ap.add_argument("field_times")
    ap.add_argument("--hz", type=float, default=144.0)
    ap.add_argument("--skip-ms", type=float, default=5000.0)
    a = ap.parse_args(argv)
    pres = []
    for ln in open(a.present, encoding="utf-8", errors="replace"):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split("\t")
        pres.append((float(p[0]), int(p[1]), int(p[2]), float(p[3]) if len(p) > 3 else 0.0,
                     float(p[4]) if len(p) > 4 else 0.0))
    ft = {}
    for ln in open(a.field_times, encoding="utf-8", errors="replace"):
        if ln.startswith("#") or not ln.strip():
            continue
        p = [float(x) for x in ln.split("\t")]
        # field wall step read present gs_wait pace sync pump audio post out
        f = int(p[0])
        work = p[2] + p[7] + p[8] + p[9] + p[10]
        ft[f] = {"wall": p[1], "step": p[2], "sync": p[7], "pace": p[6], "work": work, "present": p[4]}
    pres = [x for x in pres if x[0] >= a.skip_ms]
    if len(pres) < 10:
        print("too few presents")
        return 1
    per = 1000.0 / a.hz
    cls = {"between": [], "phase": []}
    late = {"between": [], "phase": []}
    for (t0, k0, f0, pm0, wm0), (t1, k1, f1, pm1, wm1) in zip(pres, pres[1:]):
        iv = t1 - t0
        c = "between" if f1 == f0 else "phase"
        cls[c].append(iv)
        if iv > 1.5 * per:
            work = sum(ft[f]["work"] for f in range(f0 + 1, f1 + 1) if f in ft)
            step = sum(ft[f]["step"] for f in range(f0 + 1, f1 + 1) if f in ft)
            late[c].append((iv, pm1, work, step, f1 - f0, wm1))
    allv = cls["between"] + cls["phase"]
    span = pres[-1][0] - pres[0][0]
    pms = [x[3] for x in pres]
    wms = [x[4] for x in pres]
    print("%s: %d presents over %.1f s = %.1f /s (period %.2f ms at %g Hz); present_ms on the game thread mean %.2f p95 %.2f p99 %.2f max %.2f" %
          (a.present, len(pres), span / 1000.0, 1000.0 * (len(pres) - 1) / span, per, a.hz,
           statistics.mean(pms), pct(pms, 0.95), pct(pms, 0.99), max(pms)))
    print("  of it the window's present (SDL draw + present call) mean %.2f p95 %.2f p99 %.2f max %.2f; the rest (GS worker: the pass behind "
          "its queue, compose) mean %.2f" % (statistics.mean(wms), pct(wms, 0.95), pct(wms, 0.99), max(wms),
                                             statistics.mean(p - w for p, w in zip(pms, wms))))
    print("  intervals: mean %.2f cv %.2f p99 %.2f; on time (+-25 %%) %.1f %%; late (> 1.5 periods) %d (%.1f %%)" %
          (statistics.mean(allv), statistics.pstdev(allv) / statistics.mean(allv), pct(allv, 0.99),
           100.0 * sum(1 for x in allv if abs(x - per) <= 0.25 * per) / len(allv),
           len(late["between"]) + len(late["phase"]), 100.0 * (len(late["between"]) + len(late["phase"])) / len(allv)))
    steps = [v["step"] for v in ft.values()]
    print("  phases: %d, step ms mean %.2f p95 %.2f p99 %.2f max %.2f; phases longer than one period %.1f %%" %
          (len(steps), statistics.mean(steps), pct(steps, 0.95), pct(steps, 0.99), max(steps),
           100.0 * sum(1 for s in steps if s > per) / len(steps)))
    win = 0.0
    wwin = 0.0
    lost = 0.0
    for c in ("between", "phase"):
        v = cls[c]
        if not v:
            continue
        L = late[c]
        print("  %-8s %6d intervals mean %.2f p95 %.2f p99 %.2f; late %d (%.1f %%)" %
              (c, len(v), statistics.mean(v), pct(v, 0.95), pct(v, 0.99), len(L), 100.0 * len(L) / len(v)), end="")
        if L:
            print("; late ones: interval mean %.2f, of it game-thread phase work %.2f (EE step %.2f), the present's own present_ms %.2f" %
                  (statistics.mean(x[0] for x in L), statistics.mean(x[2] for x in L), statistics.mean(x[3] for x in L),
                   statistics.mean(x[1] for x in L)))
        else:
            print()
        for iv, pm, work, step, nf, wm in L:
            over = iv - per
            lost += over
            win += min(over, pm)   # at best a present thread removes the present's own game-thread time
            wwin += min(over, wm)  # ... of it the window's present alone (the worker part stays serial)
    tot_over = lost
    print("  late time beyond one period: %.0f ms; of it at most %.0f ms (%.0f %%) is the presents' own game-thread time, %.0f ms (%.0f %%)"
          " the window's present alone; phase work in late intervals: %.0f ms" %
          (tot_over, win, 100.0 * win / tot_over if tot_over else 0.0, wwin, 100.0 * wwin / tot_over if tot_over else 0.0,
           sum(x[2] for c in late for x in late[c])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
