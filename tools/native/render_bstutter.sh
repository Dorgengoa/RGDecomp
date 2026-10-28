#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Battle stutter of one exe on boot:save2_battle2 (docs/NATIVE-RENDER.md "Tools"): the save2
# card + tools/trace/goldens/boot_save2_battle2.input.txt, headless, RG_FIELD_STATS /
# RG_FIELD_TIMES through tools/perf3d/stutter.py, then render_bstutter.py summarises the
# battle window (4,000-6,450: encounter .. won) and the first battle frames.
#   render_bstutter.sh EXE TAG [FIELDS] ["K=V ..."]
# Output: out/nrender/runs/bst_TAG/ (stats.tsv, times.tsv, report.md, summary.txt).
P=../port
exe=$1; tag=$2; fields=${3:-6500}; envs=${4:-}
D=$P/out/nrender/runs/bst_$tag
rm -rf "$D"; mkdir -p "$D"
ea=""
for kv in $envs; do ea="$ea --env $kv"; done
$P/tools/native/game_slot.sh
python $P/tools/perf3d/stutter.py run "$D" --exe "$exe" --boot-save save2 --headless --fields "$fields" \
  --input $P/tools/trace/goldens/boot_save2_battle2.input.txt $ea > "$D/stutter.out" 2>&1
python $P/tools/native/render_bstutter.py "$D" | tee "$D/summary.txt"
