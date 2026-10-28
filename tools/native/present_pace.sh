#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Windowed frame pacing per graphics API and presentation mode (docs/NATIVE-VULKAN.md
# "Presentation"): EXE windowed from a save state (play.py --windowed) on the golden route input,
# host-clock pacing, one run per CONFIG, RG_PRESENT_LOG per run, then
# tools/native/present_pacing.py (present intervals against the display period) on all of them.
#   present_pace.sh EXE TAG FROM TO HZ CONFIG...
#   FROM: a fixture milestone (fxlib.MILESTONES, e.g. field) or an .rgstate of EXE;  TO: last field
#   HZ: the display's refresh rate (the period the intervals are judged against)
#   CONFIG: API:RATE:INTERP[:VSYNC]   API d3d11|vulkan, RATE original|30|60|120|144|uncapped
#           (display.frame_rate), INTERP 0|1 (display.interpolation), VSYNC 1 (default) | 0
# INPUT=path overrides the route input (default tools/trace/goldens/newgame_save2.input.txt);
# extra env passes through (RG_PRESENT_COPY=1, RG_VK_PRESENT=0, RG_INTERP_ZSCALE ...).
# Output: out/pace/TAG_<config>/ (play.py log, present.tsv), out/pace/TAG.txt (summary).
P=../port
exe=$1; tag=$2; from=$3; to=$4; hz=$5; shift 5
R=$P/out/pace
mkdir -p $R
W=$(cd $R && pwd -W)
input=${INPUT:-$P/tools/trace/goldens/newgame_save2.input.txt}
logs=""
for cfg in "$@"; do
  api=$(echo $cfg | cut -d: -f1); rate=$(echo $cfg | cut -d: -f2); ip=$(echo $cfg | cut -d: -f3)
  vs=$(echo $cfg | cut -d: -f4); [ -z "$vs" ] && vs=1
  v=${tag}_${api}_${rate}_i${ip}_v${vs}
  rm -rf $R/$v; mkdir -p $R/$v
  $P/tools/native/game_slot.sh
  RG_GPU_API=$api RG_PRESENT_LOG="$W/$v/present.tsv" \
    python $P/tools/fixtures/play.py --windowed --from "$from" --to $to --input "$input" --out $R/$v --exe "$exe" -- \
      --set display.pacing=host --set display.frame_rate=$rate --set display.interpolation=$ip --set display.vsync=$vs \
      > $R/$v/play.txt 2>&1
  echo "$v: $(grep -a 'rg gpu:\|zero-copy\|Vulkan presentation\|interpolated presents' $R/$v/log.txt | cut -c1-160 | tr '\n' ' ')"
  logs="$logs $v=$R/$v/present.tsv"
done
python $P/tools/native/present_pacing.py --hz $hz $logs | tee $R/$tag.txt
