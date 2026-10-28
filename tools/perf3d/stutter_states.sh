#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# stutter_states.sh EXE OUTDIR [FIELDS...]   (docs/PERF-3D.md "Transition stutter")
# Copies EXE (+ .map) to OUTDIR/bin and writes save states of the golden route
# (newgame_save2) at the given fields (default 22600 = before the first battle,
# 26700 = before it is won; the second run covers results, Hooded Man scene and the
# Salgin load) into OUTDIR/fFIELD.rgstate, headless, RG_GPU=hw.  ~3 min.
# States load only into that exe: tools/perf3d/stutter.py run --exe OUTDIR/bin/rg-game.exe
# --state OUTDIR/f22600.rgstate --fields 23400.
set -e
EXE=$1; OUT=$2; shift 2
[ -n "$OUT" ] || { echo "usage: stutter_states.sh EXE OUTDIR [FIELDS...]" >&2; exit 2; }
FIELDS=${*:-"22600 26700"}
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
mkdir -p "$OUT/bin" "$OUT/saves"
cp "$EXE" "$OUT/bin/rg-game.exe"; cp "${EXE%.exe}.map" "$OUT/bin/rg-game.map" 2>/dev/null || true
W=$(cd "$OUT" && pwd -W 2>/dev/null || pwd)
last=0; args=""
for f in $FIELDS; do args="$args --save-state $f:$W/f$f.rgstate"; [ $f -gt $last ] && last=$f; done
RG_GPU=${RG_GPU:-hw} RG_DATA=${RG_DATA:-$ROOT/data} "$OUT/bin/rg-game.exe" --headless --fields $last \
  --saves "$W/saves" --input "$ROOT/tools/trace/goldens/newgame_save2.input.txt" $args > "$OUT/log.txt" 2>&1
grep -E "SAVESTATE|run_hash" "$OUT/log.txt"
