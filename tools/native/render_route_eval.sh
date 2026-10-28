#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Level-4 image evaluation from power-on (docs/NATIVE-RENDER.md "Verification (7)"): one
# golden-route run of the oracle twin in emu mode and one of the native exe (an RG_NATIVE_ONLY
# rg-game cannot run emu, and save states load only into the exe that wrote them), display
# dumps at every route milestone (tools/fixtures/fxlib.py) + 60 / 150 / 280, then
# render_imgcmp.py emu vs native, plus ms/field of both runs (RG_FIELD_TIMES wall, fields
# 7,400 on).  Both runs must end with the same run hash (printed).
#   render_route_eval.sh ORACLE_EXE NATIVE_EXE TAG [SCALE] [EXTRA rg-game ARGS...]
#   RT_MAX_FIELD=N: only milestone fields <= N (run ends there; e.g. while the goldens are re-timed)
#   RT_SKIP_EMU=1: keep the emu run already in out/nrender/runs/rt_TAG_emu (deterministic)
#   e.g. render_route_eval.sh build/nrender-i686/rg-game-oracle.exe build/nrender-i686/rg-game.exe s7 3 --set graphics.aspect=16:9
# Output: out/nrender/runs/rt_TAG_{emu,nat}/ (run.log, times.tsv, dumps), rt_TAG_cmp/, and a
# summary on stdout.  One rg-game at a time.
P=../port
emu=$1; nat=$2; tag=$3; scale=${4:-1}; shift 4 2>/dev/null || shift $#
F=$(cd $P/tools/fixtures && python -c "
import fxlib
fs = []
import os
mx = int(os.environ.get('RT_MAX_FIELD', '0') or 0)
for n, f, _ in fxlib.MILESTONES:
    fs += [x for x in (f + 60, f + 150, f + 280) if not mx or x <= mx]
print(','.join(str(x) for x in fs))")
last=$(echo $F | tr ',' '\n' | sort -n | tail -n 1)
for m in emu nat; do
  R=$P/out/nrender/runs/rt_${tag}_$m
  if [ $m = emu ] && [ -n "$RT_SKIP_EMU" ] && [ -f "$R/run.log" ]; then
    echo "emu: (kept) $(grep -a 'run_hash' "$R/run.log")"; continue
  fi
  rm -rf "$R"; mkdir -p "$R/saves"
  W=$(cd "$R" && pwd -W)
  exe=$emu; mode=emu
  [ $m = nat ] && exe=$nat && mode=native
  RG_DATA='data' RG_GPU=hw RG_GPU_SCALE=$scale RG_RENDER=$mode RG_FIELD_TIMES="$W/times.tsv" \
  RG_GS_DUMP_DIR="$W" RG_GS_DUMP_FIELDS="$F" \
    "$exe" --headless --fields $((last + 10)) --saves "$W/saves" \
    --input tools/trace/goldens/newgame_save2.input.txt "$@" > "$R/run.log" 2>&1
  echo "rc=$?" >> "$R/run.log"
  echo "$m: $(grep -a 'run_hash' "$R/run.log") $(python - "$R/times.tsv" <<'EOF'
import sys
v = [l.split() for l in open(sys.argv[1]) if l[:1].isdigit() and int(l.split()[0]) >= 7400]
print("ms/field %.2f over %d fields" % (sum(float(x[1]) for x in v) / max(len(v), 1), len(v)))
EOF
)"
done
python $P/tools/native/render_imgcmp.py $P/out/nrender/runs/rt_${tag}_emu $P/out/nrender/runs/rt_${tag}_nat \
  --out $P/out/nrender/runs/rt_${tag}_cmp
