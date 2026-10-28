#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# One battle run for the native renderer lane (docs/NATIVE-RENDER.md "Performance"):
# loads the `battle` fixture of EXE (tools/fixtures; the set must exist: run
# tools/fixtures/regen.py --exe EXE --only battle first) and runs FIELDS fields.
#   render_battle.sh NAME MODE EXE [SCALE] [FIELDS] [DUMP_FIELDS]
#   MODE: emu | native | verify   (RG_RENDER)
# Output: out/nrender/runs/NAME/ (run.log, times.tsv, fNNNNN_display.png).
# Extra env passes through (RG_THREADS, RG_NR_*, RG_GPU_PROFILE, ...).
P=../port
name=$1; mode=$2; exe=$3; scale=${4:-1}; fields=${5:-300}; dump=${6:-}
R=$P/out/nrender/runs/$name
W="out/nrender/runs/$name"
rm -rf "$R"; mkdir -p "$R"
export RG_GPU=hw RG_GPU_SCALE=$scale RG_RENDER=$mode RG_FIELD_TIMES="$W/times.tsv"
[ -n "$dump" ] && export RG_GS_DUMP_DIR="$W" RG_GS_DUMP_FIELDS="$dump"
python $P/tools/fixtures/run_from.py battle --exe "$exe" --no-regen --run "$fields" > "$R/run.log" 2>&1
echo "rc=$?" >> "$R/run.log"
grep -a "native render\|rc=" "$R/run.log" | tail -n 6
