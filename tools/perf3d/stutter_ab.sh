#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# stutter_ab.sh STATES OUT ROUNDS "ENV_A" "ENV_B" [WHICH]   (docs/PERF-3D.md "Transition stutter")
# Interleaved A/B of two environment settings on the transition windows, windowed, from the
# states of tools/perf3d/stutter_states.sh (STATES/bin/rg-game.exe, STATES/f22600|f26700):
#   bs = 22600 -> 23400 (battle start), be = 26700 -> 29300 (battle end, results, scene, Salgin load)
# ENV_x: space-separated K=V (e.g. "RG_PACE_CATCHUP=1"; "-" for none).  WHICH: "bs be" (default).
# Per run: OUT/<which>_<A|B>_r<n>/ (times.tsv, stats.tsv, run.log, report.md); at the end the
# summary rows of every report (new-image intervals) side by side in OUT/summary.md.
P=$(cd "$(dirname "$0")/../.." && pwd)
ST=$1; OUT=$2; ROUNDS=${3:-2}; EA=$4; EB=$5; WHICH=${6:-"bs be"}
mkdir -p "$OUT"
for r in $(seq 1 $ROUNDS); do
  for w in $WHICH; do
    case $w in bs) S=22600; F=23400;; be) S=26700; F=29300;; esac
    for c in A B; do
      [ $c = A ] && E=$EA || E=$EB
      envs=""
      for kv in $E; do [ "$kv" != "-" ] && envs="$envs --env $kv"; done
      python "$P/tools/perf3d/stutter.py" run "$OUT/${w}_${c}_r$r" --exe "$ST/bin/rg-game.exe" \
        --state "$ST/f$S.rgstate" --fields $F --env RG_PACE_LOG=1 $envs > /dev/null 2>&1
      echo "$w $c r$r ($E): $(grep '^| whole' "$OUT/${w}_${c}_r$r/report.md")"
    done
  done
done | tee "$OUT/summary.md"
