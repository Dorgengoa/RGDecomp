#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# perf3d.sh OUT EXE FIELDS RANGES [MODE]  (docs/PERF-3D.md "Rerunning the measurements")
#
# One golden-input run of EXE (rg-game) to FIELDS fields, writing into OUT:
#   times.tsv      per field: wall, step (EE+DMA+VIF+VU+GS+GPU submit), read,
#                  present, GS worker wait (ms)            ($RG_FIELD_TIMES)
#   fA-B_vu.tsv    VU microprogram census per range         ($RG_PERF_CENSUS)
#   fA-B_gs.tsv    GS feature census per range
#   prof.tsv       sampling profile (tools/perf3d/rgprof)    (unless PROF=0)
#   report.md      breakdown.py per range (cost by subsystem, top functions)
#                  + census.py (microprograms, GS features)
# RANGES: comma list of field ranges, e.g. 7400-7999,14000-14999,23000-23399.
# MODE: wu (windowed, unthrottled; default), w (windowed, paced), h (headless).
# The profile run keeps the GS model on the main thread (RG_GS_ASYNC=0) so the
# subsystem shares add up on one thread; set ASYNC=1 to profile the shipping
# configuration.  REPORT_ONLY=1 rewrites report.md from an existing OUT.
# Other env vars pass through (RG_GPU_SCALE, RG_GPU=warp, ...).
# Needs: Git Bash, python, the extracted data (RG_DATA, default data).
set -e
OUT=$1; EXE=$2; FIELDS=$3; RANGES=$4; MODE=${5:-wu}
[ -n "$RANGES" ] || { echo "usage: perf3d.sh OUT EXE FIELDS RANGES [MODE]" >&2; exit 2; }
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/../.." && pwd)
mkdir -p "$OUT/saves"
W=$(cd "$OUT" && pwd -W 2>/dev/null || pwd)
PROFEXE="$HERE/rgprof.exe"
if [ "${PROF:-1}" = 1 ] && [ ! -f "$PROFEXE" ]; then
  # rgprof: a minimal external sampler (i686 target process); built once
  CLANG=${CLANG:-../tools/llvm/bin/clang}
  "$CLANG" -O2 -m32 "$HERE/rgprof.c" -o "$PROFEXE" -lpsapi -lwinmm
fi
case $MODE in h) A="--headless --unthrottled";; w) A="";; *) A="--unthrottled";; esac
export RG_DATA=${RG_DATA:-'data'} RG_GPU=${RG_GPU:-hw}
export RG_FIELD_TIMES="$W/times.tsv" RG_GS_ASYNC=${ASYNC:-0}
if [ "${CENSUS:-1}" = 1 ]; then export RG_PERF_CENSUS="$W:$RANGES"; fi
INPUT="$ROOT/tools/trace/goldens/newgame_battle.input.txt"
if [ "${REPORT_ONLY:-0}" = 1 ]; then
  :   # the run is there already: only the report
elif [ "${PROF:-1}" = 1 ]; then
  "$PROFEXE" "$W/prof.tsv" ${RG_PROF_MS:-5} "$EXE" $A $RGARGS --fields "$FIELDS" --saves "$W/saves" --input "$INPUT" > "$OUT/run.log" 2>&1 || true
else
  "$EXE" $A $RGARGS --fields "$FIELDS" --saves "$W/saves" --input "$INPUT" > "$OUT/run.log" 2>&1 || true
fi
MAP="${EXE%.exe}.map"
{
  echo "# perf3d report: $EXE, $FIELDS fields, mode $MODE, async ${ASYNC:-0}"
  echo
  for r in $(echo "$RANGES" | tr ',' ' '); do
    echo "## Fields $r: time per field"
    echo
    python "$HERE/fieldtimes.py" "$OUT/times.tsv" "$r"
    if [ -f "$OUT/prof.tsv" ]; then
      echo '```'
      RG_PROF_THREADS=${RG_PROF_THREADS:-2} python "$HERE/breakdown.py" "$OUT/prof.tsv" "$OUT/times.tsv" "$MAP" "$EXE" --fields "$r" --top 25
      echo '```'
    fi
    echo
  done
  python "$HERE/census.py" "$OUT"
} > "$OUT/report.md" 2>&1
echo "report: $OUT/report.md"
