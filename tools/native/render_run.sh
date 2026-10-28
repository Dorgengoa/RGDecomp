#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# One deterministic headless golden run for the native renderer lane
# (docs/NATIVE-RENDER.md "Verification").
#   render_run.sh NAME MODE FIELDS DUMP_FIELDS [SCALE]
#   MODE: emu | native   (RG_RENDER)
# Output: out/nrender/runs/NAME/ (fNNNNN_display.png ... from RG_GS_DUMP_*),
#         NAME/run.log, NAME/times.tsv.  Extra env passes through
#         (RG_EXE = the exe, default build/nrender-i686/rg-game.exe).
P=../port
EXE=${RG_EXE:-$P/build/nrender-i686/rg-game.exe}
name=$1; mode=$2; fields=$3; dump=$4; scale=${5:-1}
R=$P/out/nrender/runs/$name
W="out/nrender/runs/$name"
rm -rf "$R"; mkdir -p "$R/saves"
export RG_DATA='data' RG_STATUS_EVERY=500 RG_GPU=hw RG_GPU_SCALE=$scale RG_RENDER=$mode
[ -n "$dump" ] && export RG_GS_DUMP_DIR="$W" RG_GS_DUMP_FIELDS="$dump"
export RG_FIELD_TIMES="$W/times.tsv"
t0=$(date +%s)
"$EXE" --headless --fields "$fields" --saves "$W/saves" \
  --input tools/trace/goldens/newgame_battle.input.txt > "$R/run.log" 2>&1
rc=$?
t1=$(date +%s)
echo "rc=$rc wall=$((t1 - t0))s" >> "$R/run.log"
tail -n 4 "$R/run.log"
