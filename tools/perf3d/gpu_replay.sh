#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# gpu_replay.sh TESTS_EXE N REC... : GPU time of GS recordings replayed through
# the renderer alone (rg-gpu-tests scaleS.replay, RG_GPU_PROFILE=1), best of N,
# per field, for each RG_GPU_ANISO in $ANISO (default "0 16") at scale $SC
# (default 3), with the top draw categories of the best run (docs/PERF-3D.md).
# Recordings come from a game run with RG_GS_REC=FILE RG_GS_REC_FIELDS=a-b.
T=$1; N=$2; shift 2
for rec in "$@"; do
  for an in ${ANISO:-0 16}; do
    best=""; bestlog=$(mktemp)
    for i in $(seq 1 "$N"); do
      log=$(mktemp)
      RG_GPU_ANISO=$an RG_GPU_PROFILE=1 RG_GPU_HW=1 RG_DATA=${RG_DATA:-'data'} \
        "$T" "scale${SC:-3}.replay" "$rec" > "$log" 2>&1
      t=$(grep "^  total" "$log" | awk '{print $2}')
      if [ -n "$t" ] && { [ -z "$best" ] || python -c "import sys; sys.exit(0 if $t < $best else 1)"; }; then
        best=$t; cp "$log" "$bestlog"
      fi
      rm -f "$log"
    done
    nf=$(grep -o "[0-9]* fields" "$bestlog" | head -1 | awk '{print $1}')
    echo "$(basename "$rec") x${SC:-3} aniso $an: $(python -c "print('%.1f ms GPU per field (%s fields, best of $N)' % ($best / $nf, $nf))")"
    grep -E "^  (draw|decode|write|load|disp|snap)" "$bestlog" | sort -k5 -t' ' | awk -v nf="$nf" '{
      for (i = 1; i <= NF; i++) if ($i == "calls") { c = $(i-1); ms = $(i+1); name = ""; for (j = 1; j < i - 1; j++) name = name " " $j; }
      printf "    %8.2f ms/field %7.1f calls/field %s\n", ms / nf, c / nf, name }' | sort -nr | head -8
    rm -f "$bestlog"
  done
done
