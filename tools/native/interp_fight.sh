#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Interpolated presentation in a battle with effects in motion (docs/NATIVE-RENDER.md
# "Interpolated presentation", checkpoint 12): the ch07_rosa auto-battle route
# (tools/native/interp_fight_rosa.route.txt, written by tools/fixtures/autobattle.py: run at the
# enemies, sword combos, jumps, the allies' suggestions) replayed from the battle state EXE writes
# (autobattle.py prep, ~70 s, skipped when $STATE is set), with RG_INTERP=1 and the simulated
# present clock (PNG per present in DUMP_FIELDS), then the snap control; interp_smooth.py on both
# (+ --crop when $CROP is set) and interp_census.py on the census.
#   interp_fight.sh NAME EXE [HZ] [TO] [DUMP_FIELDS a-b] [SCALE]
# Extra env passes through (RG_INTERP_ZSCALE, RG_INTERP_2D, ...).  Output: out/interp/fight/NAME{,_snap}/
P=../port
name=$1; exe=$2; hz=${3:-144}; to=${4:-5500}; df=${5:-5380-5420}; scale=${6:-1}
R=$P/out/interp/fight
mkdir -p $R
W=$(cd $R && pwd -W)
route=${ROUTE:-$P/tools/native/interp_fight_rosa.route.txt}
if [ -z "$STATE" ]; then
  python $P/tools/fixtures/autobattle.py prep ${CARD:-ch07_rosa} --exe "$exe" > $R/${name}_prep.log 2>&1
  STATE=$(python -c "import re,sys;print(re.search(r'state (\S+rgstate)',open(sys.argv[1]).read()).group(1))" $R/${name}_prep.log)
fi
echo "state $STATE"
for v in "" _snap; do
  rm -rf $R/${name}${v} $R/${name}${v}_dump; mkdir -p $R/${name}${v}_dump
  snap=0; [ "$v" = _snap ] && snap=1
  chk=1; [ "$v" = _snap ] && chk=0
  RG_GPU=hw RG_GPU_SCALE=$scale RG_INTERP=1 RG_INTERP_SIM=$hz RG_INTERP_SIM_SNAP=$snap RG_INTERP_CHECK=$chk \
  RG_INTERP_CENSUS="$W/${name}${v}_census.tsv" RG_INTERP_DUMP="$W/${name}${v}_dump" RG_INTERP_DUMP_FIELDS="$df" \
  RG_FIELD_TIMES="$W/${name}${v}_times.tsv" \
    python $P/tools/fixtures/play.py --from "$STATE" --to $to --input "$route" --out $R/${name}${v} --exe "$exe" > /dev/null 2>&1
  grep -a "^interp\|interpolated presents\|run_hash\|exit" $R/${name}${v}/log.txt | cut -c1-600
done
python $P/tools/native/interp_census.py $R/${name}_census.tsv
python $P/tools/native/interp_smooth.py $R/${name}_dump $R/${name}_snap_dump
[ -n "$CROP" ] && python $P/tools/native/interp_smooth.py --crop $CROP $R/${name}_dump $R/${name}_snap_dump
exit 0
