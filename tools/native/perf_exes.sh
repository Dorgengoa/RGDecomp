#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Interleaved timing of several exes on one boot fixture (docs/NATIVE-RENDER.md checkpoint 12:
# the title / menu ms after checkpoint 10): REPS rounds, each exe once per round (the machine
# is shared: back-to-back runs), then per bucket of BUCKET fields the mean RG_FIELD_TIMES wall,
# step and gs_wait ms per field of every exe over all rounds.
#   perf_exes.sh TAG MILESTONE FIELDS REPS BUCKET EXE...     e.g.
#   perf_exes.sh t12 boot:save2 300 3 1000 out/nrender2/base/rg-game.exe out/nrf/c12f/rg-game.exe
# (boot:NAME runs from power-on: boot-end + FIELDS fields).  Runs in out/nrender/runs/pe_TAG_*.
P=../port
tag=$1; ms=$2; fl=$3; reps=$4; bk=$5; shift 5
for r in $(seq 1 $reps); do
  i=0
  for exe in "$@"; do
    i=$((i + 1))
    $P/tools/native/render_fx.sh pe_${tag}_${i}_$r native "$exe" $ms 1 $fl > /dev/null
  done
done
python - "$P/out/nrender/runs" "$tag" "$reps" "$bk" "$@" <<'PY'
import sys
from collections import defaultdict
root, tag, reps, bk = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
exes = sys.argv[5:]
cols = {"wall": 1, "step": 2, "gs_wait": 5}
res = []
for i, e in enumerate(exes, 1):
    acc = defaultdict(lambda: defaultdict(list))
    for r in range(1, reps + 1):
        for l in open(f"{root}/pe_{tag}_{i}_{r}/times.tsv"):
            if not l[:1].isdigit():
                continue
            v = l.split()
            f = int(v[0])
            if f <= 20:
                continue
            for c, k in cols.items():
                acc[f // bk][c].append(float(v[k]))
    res.append(acc)
buckets = sorted(set(b for a in res for b in a))
print("fields        " + "  ".join(f"{'exe%d wall/step/gs_wait' % (i + 1):>26}" for i in range(len(exes))))
for b in buckets:
    row = f"{b * bk:5d}-{(b + 1) * bk - 1:5d}  "
    for a in res:
        d = a.get(b)
        if not d:
            row += f"{'-':>26}  "
            continue
        m = {c: sum(d[c]) / len(d[c]) for c in cols}
        row += f"{m['wall']:8.2f} {m['step']:8.2f} {m['gs_wait']:8.2f}  "
    print(row)
for i, (e, a) in enumerate(zip(exes, res), 1):
    w = [x for b in a for x in a[b]["wall"]]
    print(f"exe{i} {e}: all fields {sum(w) / len(w):.2f} ms/field wall ({len(w) // reps} fields x {reps})")
PY
