#!/bin/sh
# Run hashes of one build along the route (docs/UB-AUDIT.md): power-on, save a
# state every STEP fields from A to B, print "field run_hash" (SAVESTATE lines).
#   tools/ubaudit/hashwalk.sh EXE A B STEP OUTDIR
exe=$1; a=$2; b=$3; st=$4; out=$5
mkdir -p "$out/saves"; rm -rf "$out/saves"/* "$out"/*.rgstate
args=""
f=$a; while [ $f -le $b ]; do args="$args --save-state $f:$out/s$f.rgstate"; f=$((f+st)); done
RG_DATA=data RG_GPU=hw "$exe" --headless --fields $b --saves "$out/saves" \
  --input tools/trace/goldens/newgame_save2.input.txt $args > "$out/run.log" 2>&1
grep -o "SAVESTATE field=[0-9]* vbl=[0-9]* run_hash=[0-9a-f]*" "$out/run.log" | sed 's/SAVESTATE field=//; s/ vbl=[0-9]* run_hash=/ /'
rm -f "$out"/*.rgstate
