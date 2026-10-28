#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Real-time interpolated presentation in a real window (history "2026-10-26 (interp3)"): EXE
# windowed from STATE (an .rgstate of EXE, e.g. autobattle.py prep's battle state) to field TO,
# host-clock pacing, display.interpolation on, one run per CONFIG, with RG_INTERP_TRACE (the
# displayed motion, tools/native/interp_trace.py), RG_PRESENT_LOG (+ present_ms) and
# RG_FIELD_TIMES (tools/native/present_thread.py: is the jitter the game thread's?).
# No screen capture: SHOT=FIELD writes the window's own back buffer at the end of FIELD
# (RG_WINDOW_SHOT + RG_WINDOW_SHOT_HOST=1: with the FPS counter, in-process read-back).
#   interp_window.sh TAG EXE STATE TO HZ CONFIG...
#   CONFIG: API:RATE[:VSYNC]   API d3d11|vulkan, RATE 120|144|uncapped (display.frame_rate), VSYNC 1|0
#   HZ: the display's refresh (judging present intervals)
# Extra env passes through (RG_INTERP_ZSPAIR=0, RG_VK_PRESENT=0, ...); INTERP=0 = interpolation off (control).  FPS=mode sets
# display.fps_counter (default detailed).  Output: out/interp3/win/TAG_<config>/.
P=../port
tag=$1; exe=$2; state=$3; to=$4; hz=$5; shift 5
R=$P/out/interp3/win
mkdir -p $R
for cfg in "$@"; do
  api=$(echo $cfg | cut -d: -f1); rate=$(echo $cfg | cut -d: -f2); vs=$(echo $cfg | cut -d: -f3); [ -z "$vs" ] && vs=1
  v=${tag}_${api}_${rate}_v${vs}
  rm -rf $R/$v; mkdir -p $R/$v
  W=$(cd $R/$v && pwd -W)
  shot=""; [ -n "$SHOT" ] && shot="$SHOT:$W/shot.png"
  RG_GPU=hw RG_GPU_API=$api RG_PRESENT_LOG="$W/present.tsv" RG_FIELD_TIMES="$W/times.tsv" RG_INTERP_TRACE="$W/trace.tsv" \
  RG_WINDOW_SHOT="$shot" RG_WINDOW_SHOT_HOST=1 \
    python $P/tools/fixtures/play.py --windowed --from "$state" --to $to --input ${ROUTE:-$P/tools/native/interp_fight_rosa.route.txt} \
      --out $R/$v/run --exe "$exe" -- --set display.pacing=host --set display.frame_rate=$rate --set display.interpolation=${INTERP:-1} \
      --set display.vsync=$vs --set display.fps_counter=${FPS:-detailed} > $R/$v/play.txt 2>&1
  echo "== $v: $(grep -a 'run_hash=' $R/$v/run/log.txt | tail -1) $(grep -a -o 'zero-copy[^;]*\|Vulkan device[^;]*\|reading frames back' $R/$v/run/log.txt | sort -u | tr '\n' ' ')"
  python $P/tools/native/interp_trace.py $R/$v/trace.tsv --hz $hz --from-ms 0
  python $P/tools/native/present_thread.py --hz $hz --skip-ms 2000 $R/$v/present.tsv $R/$v/times.tsv
done
