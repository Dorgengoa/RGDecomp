# SPDX-License-Identifier: CC0-1.0
"""Summary of a render_bstutter.sh run (docs/NATIVE-RENDER.md "Tools").

    python tools/native/render_bstutter.py DIR [--win A-B] ...

Per window (default: battle 4000-6450 of boot:save2_battle2, the field before it 3800-3990):
wall / step / gs_wait ms per field (mean, p99, max, fields over 33.4 ms of work), and the
RG_FIELD_STATS counters per field (read-backs, read-back wait, KB down / up, CLUT loads,
target write-backs, texture decodes, native mesh uploads).  Also the five most expensive
fields of the window with their counters (first battle frame = the mesh-upload peak).
"""
import argparse
from pathlib import Path


def load(path, key="field"):
    rows, cols = {}, None
    for line in open(path, encoding="utf-8", errors="replace"):
        if line.startswith("# field"):
            cols = line[2:].rstrip("\n").split("\t")
            continue
        if not line[:1].isdigit() or cols is None:
            continue
        v = line.rstrip("\n").split("\t")
        d = {}
        for c, x in zip(cols, v):
            try:
                d[c] = float(x)
            except ValueError:
                d[c] = x
        rows[int(v[0])] = d
    return rows


def pct(v, p):
    if not v:
        return 0.0
    s = sorted(v)
    return s[min(len(s) - 1, int(p * len(s)))]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dir")
    ap.add_argument("--win", action="append")
    a = ap.parse_args()
    d = Path(a.dir)
    t = load(d / "times.tsv")
    s = load(d / "stats.tsv") if (d / "stats.tsv").exists() else {}
    wins = a.win or ["3800-3990", "4000-6450"]
    cnt = ["downloads", "download_ms", "down_kb", "up_kb", "clut_loads", "rt_writebacks", "tex_decodes",
           "nr_tex_decodes", "nr_mesh_uploads", "gpu_batches"]
    for w in wins:
        lo, hi = (int(x) for x in w.split("-"))
        f = [k for k in sorted(t) if lo <= k <= hi]
        if not f:
            print("window %s: no fields" % w)
            continue
        work = [t[k]["step_ms"] for k in f]
        gsw = [t[k]["gs_wait_ms"] for k in f]
        print("window %s: %d fields  step mean %.2f p99 %.2f max %.2f  gs_wait mean %.2f  step>33.4: %d"
              % (w, len(f), sum(work) / len(f), pct(work, 0.99), max(work), sum(gsw) / len(f),
                 sum(1 for x in work if x > 33.4)))
        if s:
            fs = [k for k in f if k in s]
            if fs:
                print("  per field: " + "  ".join("%s %.3f" % (c, sum(s[k].get(c, 0) for k in fs) / len(fs)) for c in cnt))
                print("  totals: " + "  ".join("%s %.0f" % (c, sum(s[k].get(c, 0) for k in fs)) for c in
                                                ("downloads", "download_ms", "nr_mesh_uploads", "nr_tex_decodes")))
        top = sorted(f, key=lambda k: -t[k]["step_ms"])[:5]
        for k in top:
            extra = ""
            if k in s:
                extra = "  " + " ".join("%s=%g" % (c, s[k].get(c, 0)) for c in cnt)
            print("  field %d step %.2f gs_wait %.2f%s" % (k, t[k]["step_ms"], t[k]["gs_wait_ms"], extra))


if __name__ == "__main__":
    main()
