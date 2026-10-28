#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Summarise a $RG_NR_FILTLOG file (src/gpu/gpu_core.cpp): per textured draw, which texture
filter it got and whether its texture came from a live render target (internal resolution) or
the 1x mirror (docs/BRINGUP.md item 8, history entry "2026-10-24: item 8").

    RG_NR_FILTLOG=out/x/filt.txt rg-game ...
    python tools/native/filtlog.py out/x/filt.txt [--frames A:B] [--tbp 14336,14592] [--rows 40] [--mirror]

Lines (frame = EE frame number, nr_frame_begin; the GS side may lag it by a frame):
  F frame kind tbp T tbw W psm P WxH keep K ord O old L lin N enh E [rt BP bw B psm P h H drawn D] fb F dir D [read R]
      one per textured NATIVE draw (nr_draw_resolved).  ord / old: ordinary texture (the
      graphics.texture_filter override applies) under the current rule (no live target drew
      into its pages since their upload) / the old one (no live target overlaps its pages);
      enh: override applied (-1: GS TEX1 kept); dir: -1 not eligible for direct sampling,
      0 sampled from the live target, 1 stale there, 2 read outside it, 3 another target
      overlaps, 4 no target at the base (1-4: decoded from the 1x mirror)
  G frame fb F bw B psm P box B tme T tbp T tbw W tpsm P read R src S
      one per GS-draw-path batch (flush_batch); src: target, mirror(<why direct_source declined>)
  W ...   a CPU write (host->local transfer) into pages a live target owns
  L ...   a stale target reloaded (only its stale pages)
  C ...   pages of an evicted target copied into the new one at the internal resolution
  S ...   display circuits at a read-out (source target or mirror)
Default: F-line table per (kind, tbp, tbw, psm, size) and the G-line source counts;
--mirror: every G batch sourced from the mirror (frame, fb, texture, read rect, box, reason).
Debug knob that pairs with it: RG_NR_DBGSKIP=K:F:T skips native draws of kind K (m/i/*) into
FBP F with TBP T (-1 any), to find which draw paints a region.
"""
import argparse
import collections
import sys


def parse_f(f):
    d = {"frame": int(f[1]), "kind": f[2]}
    i = 3
    while i < len(f):
        if "x" in f[i] and f[i].split("x")[0].isdigit():   # the size token has no key
            d["size"] = f[i]
            i += 1
            continue
        key = f[i]
        if key in d:            # second "bw"/"psm"/"h": the target's
            key = "rt_" + key
        d[key] = f[i + 1] if i + 1 < len(f) else ""
        i += 2
    return d


def parse_g(f):
    d = {"frame": int(f[1])}
    for i in range(2, len(f) - 1, 2):
        d[f[i]] = f[i + 1]
    return d


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("log")
    ap.add_argument("--frames", help="A:B EE frames (half-open)")
    ap.add_argument("--tbp", help="comma list of texture base pointers")
    ap.add_argument("--rows", type=int, default=40)
    ap.add_argument("--mirror", action="store_true", help="list the G batches sourced from the mirror")
    a = ap.parse_args()
    frames = tuple(int(x) for x in a.frames.split(":")) if a.frames else None
    tbps = {int(x) for x in a.tbp.split(",")} if a.tbp else None
    groups = collections.OrderedDict()
    tot = collections.Counter()
    gsrc = collections.Counter()
    mirror_rows = []
    for line in open(a.log, encoding="utf-8", errors="replace"):
        f = line.split()
        if not f or f[0] not in ("F", "G"):
            continue
        d = parse_f(f) if f[0] == "F" else parse_g(f)
        if frames and not (frames[0] <= d["frame"] < frames[1]):
            continue
        if tbps and int(d.get("tbp", -1)) not in tbps:
            continue
        if f[0] == "G":
            if d.get("tme") != "1":
                continue
            gsrc[d.get("src", "?")] += 1
            if a.mirror and d.get("src", "").startswith("mirror"):
                mirror_rows.append("%d fb %s tbp %s/%s/%s read %s box %s %s" % (
                    d["frame"], d.get("fb"), d.get("tbp"), d.get("tbw"), d.get("tpsm"), d.get("read"), d.get("box"),
                    d.get("src")))
            continue
        key = (d["kind"], int(d["tbp"]), int(d["tbw"]), d["psm"], d.get("size", "?"))
        g = groups.setdefault(key, collections.Counter())
        keep = d.get("keep") == "1"
        ord_, old = d.get("ord") == "1", d.get("old") == "1"
        g["draws"] += 1
        g["gs_now"] += keep or not ord_
        g["gs_old"] += keep or not old
        moved = not keep and ord_ and not old
        g["moved"] += moved
        g["dir_mirror"] += d.get("dir", "-1") not in ("-1", "0")
        if "rt" in d:
            g["rt %s/%s/%s h%s drawn%s" % (d["rt"], d.get("bw"), d.get("rt_psm"), d.get("h", "?"), d.get("drawn", "?"))] += 1
        tot["draws"] += 1
        tot["gs_now"] += keep or not ord_
        tot["gs_old"] += keep or not old
        tot["moved"] += moved
        tot["kept_by_rt"] += (not keep) and not ord_
        tot["keep"] += keep
        tot["dir_mirror"] += d.get("dir", "-1") not in ("-1", "0")
    print("native: %d textured draws (%d sprites/keep); GS filter now %d, old rule %d; moved to ordinary %d; "
          "still GS by a drawn target %d; target textures decoded from the mirror %d"
          % (tot["draws"], tot["keep"], tot["gs_now"], tot["gs_old"], tot["moved"], tot["kept_by_rt"], tot["dir_mirror"]))
    print("GS draw path textured batches by source: " + (", ".join("%s %d" % kv for kv in gsrc.most_common()) or "none"))
    rows = sorted(groups.items(), key=lambda kv: (-kv[1]["moved"], -kv[1]["draws"]))
    print("%-5s %6s %3s %3s %-8s %7s %6s %6s %6s %6s  targets" % ("kind", "tbp", "tbw", "psm", "size", "draws", "gsnow",
                                                                  "gsold", "moved", "mirror"))
    for (kind, tbp, tbw, psm, size), g in rows[: a.rows]:
        rts = ", ".join("%s x%d" % (k[3:], v) for k, v in g.items() if k.startswith("rt "))
        print("%-5s %6d %3d %3s %-8s %7d %6d %6d %6d %6d  %s" % (kind, tbp, tbw, psm, size, g["draws"], g["gs_now"],
                                                                 g["gs_old"], g["moved"], g["dir_mirror"], rts))
    if a.mirror:
        print("GS draw path batches sampling a target's pages through the 1x mirror (%d):" % len(mirror_rows))
        for r in mirror_rows[: a.rows]:
            print("  " + r)
    return 0


if __name__ == "__main__":
    sys.exit(main())
