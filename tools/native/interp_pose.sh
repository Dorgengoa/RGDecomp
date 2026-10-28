#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Character pose interpolation, measured (docs/NATIVE-RENDER.md "Checkpoint 13"): the ch07_rosa
# auto-battle route (tools/native/interp_fight_rosa.route.txt) from the battle state EXE writes
# (autobattle.py prep, skipped when $STATE is set), at a simulated HZ, PNG per present in DUMP_FIELDS,
# once per RG_INTERP_ZSCALE mode in $MODES (default "0 2 4": composites exact / placement only /
# pose), each with RG_INTERP_ISOLATE=1 (the interpolated frame's composite characters alone on a
# cleared frame: the pose and placement without the scene) and without (the real image); then
# tools/native/interp_smooth.py (pops, step judder) on the real images and tools/native/interp_pose.py
# on each set, with the game-frame switches from the mode-0 isolated run (+ a montage of presents
# MK..MK+5).
#   interp_pose.sh NAME EXE [HZ] [TO] [DUMP_FIELDS a-b] [MK]
# Output: out/interp/pose/NAME_z{mode}{,_iso}_dump, NAME_iso.png / NAME.png montages, NAME.txt.
# Extra env passes through (RG_INTERP_LEAD, ...).
P=../port
name=$1; exe=$2; hz=${3:-144}; to=${4:-5300}; df=${5:-5240-5290}; mk=${6:-60}
modes=${MODES:-0 2 4}
R=$P/out/interp/pose
mkdir -p $R
W=$(cd $R && pwd -W)
route=${ROUTE:-$P/tools/native/interp_fight_rosa.route.txt}
if [ -z "$STATE" ]; then
  python $P/tools/fixtures/autobattle.py prep ${CARD:-ch07_rosa} --exe "$exe" > $R/${name}_prep.log 2>&1
  STATE=$(python -c "import re,sys;print(re.search(r'state (\S+rgstate)',open(sys.argv[1]).read()).group(1))" $R/${name}_prep.log)
fi
echo "state $STATE" | tee $R/${name}.txt
iso_dirs=""; dirs=""
for z in $modes; do
  for iso in 1 0; do
    v=${name}_z${z}; [ $iso = 1 ] && v=${v}_iso
    rm -rf $R/$v $R/${v}_dump; mkdir -p $R/${v}_dump
    RG_GPU=hw RG_INTERP=1 RG_INTERP_SIM=$hz RG_INTERP_ZSCALE=$z RG_INTERP_ISOLATE=$iso \
    RG_INTERP_DUMP="$W/${v}_dump" RG_INTERP_DUMP_FIELDS="$df" \
      python $P/tools/fixtures/play.py --from "$STATE" --to $to --input "$route" --out $R/$v --exe "$exe" > /dev/null 2>&1
    echo "$v: $(grep -a 'run_hash=' $R/$v/log.txt | tail -1) $(grep -a -o 'composite strip groups.*' $R/$v/log.txt | cut -c1-140)" | tee -a $R/${name}.txt
    if [ $iso = 1 ]; then iso_dirs="$iso_dirs $R/${v}_dump"; else dirs="$dirs $R/${v}_dump"; fi
  done
done
sw=""; [ -d $R/${name}_z0_iso_dump ] && sw="--switches $R/${name}_z0_iso_dump"
python $P/tools/native/interp_smooth.py $dirs | tee -a $R/${name}.txt
python $P/tools/native/interp_pose.py $sw $iso_dirs --montage $R/${name}_iso.png --from $mk --count 6 | tee -a $R/${name}.txt
python $P/tools/native/interp_pose.py $sw $dirs --montage $R/${name}.png --from $mk --count 6 | tee -a $R/${name}.txt
exit 0
