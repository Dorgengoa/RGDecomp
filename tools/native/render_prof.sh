#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Sampling profile of a fixture run (docs/NATIVE-RENDER.md "Tools"): rgprof (tools/perf3d)
# on the run_from.py command line of MILESTONE, then breakdown.py per thread (main, GS
# worker, ...) over the run's fields.
#   render_prof.sh NAME EXE MILESTONE [MODE] [SCALE] [FIELDS] [PERIOD_MS]
#   MILESTONE boot:NAME: power-on with the boot fixture's card and script (as render_fx.sh),
#   FIELDS = the total fields run; PROF_FIELDS=A-B picks the fields analysed (default:
#   from field 21)
# Output: out/nrender/runs/NAME/{prof.tsv,times.tsv,run.log,report.txt}; prints report.txt.
# Extra env passes through (RG_GS_OVERLAP, RG_NR_*, ...).
P=../port
name=$1; exe=$2; ms=$3; mode=${4:-native}; scale=${5:-1}; fields=${6:-300}; per=${7:-2}
R=$P/out/nrender/runs/$name
rm -rf "$R"; mkdir -p "$R"
W=$(cd "$R" && pwd -W)
case $ms in
  boot:*)
    set -- $(cd $P/tools/fixtures && python -c "
import fxlib, sys
n = sys.argv[1]
card = fxlib.BOOT_CARD.get(n, n)
s = fxlib.PORT / 'tools' / 'trace' / 'goldens' / f'boot_{n}.input.txt'
if not s.exists():
    s = fxlib.FIXTURES / 'runs' / 'bootlib' / f'{n}.input.txt'
print(fxlib.FIXTURES / 'cards' / card, s)" "${ms#boot:}")
    rm -rf "$R/saves"; cp -r "$1" "$R/saves"
    cmd="$exe --headless --fields $fields --saves $W/saves --input $(cd "$(dirname "$2")" && pwd -W)/$(basename "$2")" ;;
  *) cmd=$(python $P/tools/fixtures/run_from.py "$ms" --exe "$exe" --no-regen --run "$fields" --print 2>&1 | sed -n 's/^run_from: //p' | tail -n 1) ;;
esac
[ -n "$cmd" ] || { echo "no command for $ms" >&2; exit 2; }
set -- $cmd
bin=$1
saves=$(echo "$cmd" | sed -n 's/.*--saves \([^ ]*\).*/\1/p')
[ -n "$saves" ] && mkdir -p "$(cygpath -u "$saves")"
export RG_DATA=${RG_DATA:-'data'} RG_GPU=hw RG_GPU_SCALE=$scale RG_RENDER=$mode RG_FIELD_TIMES="$W/times.tsv"
$P/tools/perf3d/rgprof.exe "$W/prof.tsv" "$per" $cmd > "$R/run.log" 2>&1
n=$(awk '/^[0-9]/ {n++} END {print n}' "$R/times.tsv")
# offset of field 1: the last sample minus the fields' wall time (the load precedes field 1)
off=$(python -c "import sys
rows=[l.split() for l in open(sys.argv[1]) if l[:1].isdigit()]
ft=[float(l.split()[1]) for l in open(sys.argv[2]) if l[:1].isdigit()]
print(float(rows[-1][0]) - sum(ft) - 50.0)" "$R/prof.tsv" "$R/times.tsv")
RG_PROF_THREADS=${RG_PROF_THREADS:-3} python $P/tools/perf3d/breakdown.py "$R/prof.tsv" "$R/times.tsv" "${bin%.exe}.map" "$bin"   --fields "${PROF_FIELDS:-21-$n}" --offset "$off" --top ${TOP:-30} > "$R/report.txt" 2>&1
cat "$R/report.txt"
