#!/bin/sh
# run.sh NAME EXE FIELDS [rg-game args...]   (widescreen, docs/WIDESCREEN.md "Stage 1")
# Runs land in $RG_WIDE_RUNS/NAME (default out/wide/stage1/runs).
# Golden input, headless, RG_GPU=hw; RG_GS_DUMP at $SHOTS and --shot PNGs (native + -view).
NAME=$1; EXE=$2; FIELDS=$3; shift 3
SHOTS=${SHOTS:-1500,7100,8000,8290,10000,12000,20000,23000,23600,24000,24500}
RUNS=${RG_WIDE_RUNS:-out/wide/stage1/runs}
R=$RUNS/$NAME
rm -rf "$R"; mkdir -p "$R/dump" "$R/saves" "$R/shot"
cp "$EXE" "$R/rg-game.exe"
W=$(cd "$R" && pwd -W)
SA=""
for f in $(echo $SHOTS | tr ',' ' '); do SA="$SA --shot $f:$W/shot/f$f.png"; done
cd "$R"
RG_GPU=hw RG_DATA=data RG_GS_DUMP_DIR=$W/dump \
RG_GS_DUMP_FIELDS=$SHOTS RG_STATUS_EVERY=500 \
  ./rg-game.exe --headless --unthrottled --fields "$FIELDS" --saves $W/saves \
  --input tools/trace/goldens/newgame_battle.input.txt $SA "$@" > log.txt 2>&1
echo "exit $?" >> log.txt
rm -f dump/*.vram rg-game.exe
