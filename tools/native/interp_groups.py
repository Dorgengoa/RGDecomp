#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Composite strip-group census (docs/NATIVE-RENDER.md "Checkpoint 13" / "interp3"): why
composite calls fall back from pose interpolation to placement.

Reads the `interp group ...` lines RG_INTERP_DEBUG=1 prints (nr_iprec.cpp place_plan, one per
strip group per interpolation pass) from one or more stderr logs and tabulates the groups by
outcome:

  posed            pose 1: bones interpolated, copy moved + widened
  reread           pose 2: re-reads a posed group's work buffer (motion-blur copy), as recorded
  placed why N     paired but not posable (1 parts / clear / not all Z-scale, 2 clear not RGBA 0,
                   3 clear apart, 4 clear too large, 5-7 the pair's box / step) -> own pair's shift
  unpaired ...     no previous-frame group of the same key left for it:
                     key new      the key (work target, destination) has no group in the
                              previous frame
                     surplus      the key has fewer groups in the previous frame
                     (older logs without the kp= / ks= fields: "unpaired")

    python tools/native/interp_groups.py LOG [LOG...] [--by-key] [--json OUT]

Counts are per pass (a game frame shown at 4.8 presents counts ~4.8 times), the same basis as
the run's "composite strip groups placed X of Y, posed Z" summary line.
"""
import argparse
import collections
import json
import re
import sys

RX = re.compile(r"interp group (\d+): key (-?\d+)/(-?\d+) box (\S+),(\S+)-(\S+),(\S+) own (\d+) clear (-?\d+) "
                r"zs (\d+) pose (\d+) why (\d+) pair (-?\d+)(.*)")
RXK = re.compile(r"\bks (\d+) kp (\d+)")
WHY = {1: "parts/clear", 2: "clear not RGBA 0", 3: "clear apart", 4: "clear too large",
       5: "pair box empty", 6: "pair size jump", 7: "pair step too far"}


def classify(m):
    pose, why, pair = int(m.group(11)), int(m.group(12)), int(m.group(13))
    if pose == 1:
        return "posed"
    if pose == 2:
        return "reread"
    if pair >= 0:
        sub = WHY.get(why, str(why))
        if why == 1:
            own, clear, zs = int(m.group(8)), int(m.group(9)), int(m.group(10))
            sub += " (" + ",".join(x for x, c in (("no own parts", not own), ("no clear", clear < 0),
                                                    ("not all zs", own and not zs)) if c) + ")"
        return "placed: " + sub
    k = RXK.search(m.group(14))
    if not k:
        return "unpaired"
    ks, kp = int(k.group(1)), int(k.group(2))
    return "unpaired: key new" if kp == 0 else "unpaired: surplus (%s)" % ("more calls" if ks > kp else "greedy")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("logs", nargs="+")
    ap.add_argument("--by-key", action="store_true", help="also tabulate per key (work/destination tokens)")
    ap.add_argument("--json")
    a = ap.parse_args(argv)
    cls = collections.Counter()
    bykey = collections.defaultdict(collections.Counter)
    n = 0
    for p in a.logs:
        with open(p, "r", encoding="utf-8", errors="replace") as f:
            for line in f:
                if "interp group" not in line:
                    continue
                m = RX.search(line)
                if not m:
                    continue
                c = classify(m)
                cls[c] += 1
                n += 1
                if a.by_key:
                    bykey["%s/%s" % (m.group(2), m.group(3))][c] += 1
    if not n:
        print("no 'interp group' lines (run with RG_INTERP=1 RG_INTERP_DEBUG=1, ZSCALE 4)")
        return 1
    good = cls["posed"] + cls["reread"]
    print("groups %d: posed %d (%.1f %%), reread-of-posed %d, not posed %d (%.1f %%)" %
          (n, cls["posed"], 100.0 * cls["posed"] / n, cls["reread"], n - good, 100.0 * (n - good) / n))
    for k, v in sorted(cls.items(), key=lambda kv: -kv[1]):
        print("  %-44s %8d  %5.1f %%" % (k, v, 100.0 * v / n))
    if a.by_key:
        for key, c in sorted(bykey.items(), key=lambda kv: -sum(kv[1].values())):
            t = sum(c.values())
            print("key %-10s %7d  " % (key, t) + ", ".join("%s %d" % kv for kv in c.most_common()))
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump({"groups": n, "classes": dict(cls)}, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
