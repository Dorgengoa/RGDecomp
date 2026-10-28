#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Env-switch bisection of an image difference on a boot fixture (docs/NATIVE-RENDER.md "Tools"):
# one native run of EXE per "K=V[,K=V]" setting (plus the default), display dumps at FIELDS,
# each compared with the reference run REF_DIR (an emu run of the same exe, e.g.
# out/nrender/runs/bt_TAG_NAME_emu from render_boot_eval.sh).
#   render_bisect.sh EXE FIXTURE FIELDS REF_DIR TAG "SET1" "SET2" ...   (BIS_SCALE=N: internal scale)
# One rg-game at a time (game_slot.sh); prints one line per setting.
P=../port
exe=$1; fx=$2; fields=$3; ref=$4; tag=$5; shift 5
last=$(echo $fields | tr ',' '\n' | sort -n | tail -n 1)
for set in default "$@"; do
  name=bis_${tag}_$(echo "$set" | tr ',=' '__')
  envs=""; [ "$set" != default ] && envs=$(echo "$set" | tr ',' ' ')
  $P/tools/native/game_slot.sh
  env $envs $P/tools/native/render_fx.sh $name native "$exe" boot:$fx ${BIS_SCALE:-1} $((last + 10)) $fields > /dev/null
  r=$(python $P/tools/native/render_imgcmp.py "$ref" $P/out/nrender/runs/$name --fields $fields 2>&1 | awk '$1 ~ /^[0-9]+$/ {printf "%s %s dB %s%%  ", $1, $2, $3}')
  echo "$set: $r"
done
