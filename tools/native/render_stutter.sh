#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Frame-time stutter check for the native renderer lane (docs/NATIVE-RENDER.md "Stutter"):
# for each start point, one run per configuration from EXE's fixture set (or boot:SAVE:
# power-on with the game-save fixture, FIELDS after its boot input),
# RG_FIELD_TIMES (wall minus the `out` column), then per run: mean / p99 / max wall ms per field over all fields, the
# mean of the first 60 fields (scene start) and the count of fields over 33.4 ms.
#   render_stutter.sh EXE TAG [SCALE] [FIELDS] [STARTS]
#   STARTS default: battle battle_won boot:save2
# Configurations: "new" = defaults; "old" = RG_NR_IM=off RG_GS_LAZY=0 RG_NR_STORE=0
# RG_GPU_RT_POOL=0 (the renderer before this lane's slice 3 / lazy transfers / pool), or, with
# ST_OLD_EXE set, that exe with its defaults plus ST_OLD_ENV (e.g. the oracle twin with
# ST_OLD_ENV="RG_NR_FX=0": checkpoint 7's comparison; fixture starts need that exe's own set).
# Output: out/nrender/runs/st_TAG_*; table on stdout and in out/nrender/runs/st_TAG.md.
P=../port
exe=$1; tag=$2; scale=${3:-1}; fields=${4:-300}; starts=${5:-"battle battle_won boot:save2"}
S=$P/out/nrender/runs/st_$tag.md
echo "| start | config | fields | mean ms | p99 ms | max ms | first 60 mean | fields > 33.4 ms |" > $S
echo "| --- | --- | --- | --- | --- | --- | --- | --- |" >> $S
for st in $starts; do
  n=$(echo $st | tr ':' '_')
  fl=$fields
  for cfg in old new; do
    if [ $cfg = old ] && [ -n "$ST_OLD_EXE" ]; then
      env $ST_OLD_ENV $P/tools/native/render_fx.sh st_${tag}_${n}_$cfg native "$ST_OLD_EXE" $st $scale $fl > /dev/null
    elif [ $cfg = old ]; then
      RG_NR_IM=off RG_GS_LAZY=0 RG_NR_STORE=0 RG_GPU_RT_POOL=0 $P/tools/native/render_fx.sh st_${tag}_${n}_$cfg native "$exe" $st $scale $fl > /dev/null
    else
      $P/tools/native/render_fx.sh st_${tag}_${n}_$cfg native "$exe" $st $scale $fl > /dev/null
    fi
    r=$(python - "$P/out/nrender/runs/st_${tag}_${n}_$cfg/times.tsv" "$st" "$fields" <<'EOF'
import sys
rows = [l.split() for l in open(sys.argv[1]) if l[:1].isdigit()]
# wall minus `out` (time spent in the caller between fields: not the runtime's;
# single 0.2-0.6 s spikes there on the shared PC)
v = [float(r[1]) - (float(r[11]) if len(r) > 11 else 0.0) for r in rows]
if sys.argv[2].startswith('boot:'):
    v = v[-int(sys.argv[3]):]   # the run after the save is loaded (run_from.py --run: after the boot input)
s = sorted(v)
n = len(v)
p99 = s[min(n - 1, int(n * 0.99))] if n else 0
print("%d | %.2f | %.2f | %.2f | %.2f | %d" % (n, sum(v) / max(n, 1), p99, max(v) if v else 0,
      sum(v[:60]) / max(min(60, n), 1), sum(1 for x in v if x > 33.4)))
EOF
)
    echo "| $st | $cfg | $r |" | tee -a $S
  done
done
