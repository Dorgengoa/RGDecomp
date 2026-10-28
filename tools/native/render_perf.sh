#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# The native renderer lane's performance table (docs/NATIVE-RENDER.md "Performance"):
# emu and native runs of one exe, interleaved (the machine is shared: compare runs made
# back to back), at the given scales, for the golden field route (power-on to 13,010)
# and the battle and town fixtures (300 fields each; the exe's fixture set must exist:
# tools/fixtures/regen.py --exe EXE --only battle,town).
#   render_perf.sh EXE TAG [SCALES] [REPS]      e.g. render_perf.sh out/nrender/rg-game-s29.exe s29 "1 3" 1
# Output: out/nrender/runs/perf_TAG_* and a markdown table on stdout (ms per field,
# RG_FIELD_TIMES wall means).  Extra env passes through (RG_THREADS, ...).
P=../port
exe=$1; tag=$2; scales=${3:-"1 3"}; reps=${4:-1}
W=$(cd "$(dirname "$exe")" && pwd -W)/$(basename "$exe")
ft() { python $P/tools/perf3d/fieldtimes.py "$1" "$2" | tail -n 1 | awk -F'|' '{gsub(/ /, "", $4); print $4}'; }
echo "| scene | scale | emu ms/field | native ms/field |"
echo "| --- | --- | --- | --- |"
for s in $scales; do
  for r in $(seq 1 $reps); do
    for m in emu native; do
      RG_EXE="$W" $P/tools/native/render_run.sh perf_${tag}_f_${m}_x${s}_$r $m 13010 "" $s > /dev/null
      $P/tools/native/render_battle.sh perf_${tag}_b_${m}_x${s}_$r $m "$exe" $s 300 > /dev/null
      R=$P/out/nrender/runs/perf_${tag}_t_${m}_x${s}_$r
      rm -rf "$R"; mkdir -p "$R"
      RG_GPU=hw RG_GPU_SCALE=$s RG_RENDER=$m RG_FIELD_TIMES="$(cd "$R" && pwd -W)/times.tsv" \
        python $P/tools/fixtures/run_from.py town --exe "$exe" --no-regen --run 300 > "$R/run.log" 2>&1
    done
    for sc in "f:8000-9999:field 8000-9999" "f:12000-13009:field 12000-13009" "b:23001-23300:battle" "t:28801-29100:town (Salgin)"; do
      k=${sc%%:*}; rest=${sc#*:}; range=${rest%%:*}; label=${rest#*:}
      e=$(ft $P/out/nrender/runs/perf_${tag}_${k}_emu_x${s}_$r/times.tsv $range)
      n=$(ft $P/out/nrender/runs/perf_${tag}_${k}_native_x${s}_$r/times.tsv $range)
      echo "| $label | $s | $e | $n |"
    done
  done
done
