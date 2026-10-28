#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# The renderer lane's image gate in one command (docs/NATIVE-RENDER.md "Tools"): the oracle
# twin in emu mode vs the native-only exe from power-on on
#   - the golden route milestones (render_route_eval.sh, SCALE),
#   - the boot fixtures save2 / factory / insectron / save2_battle2 and the four map-regression
#     cards (render_boot_eval.sh),
#   - mapcheck.py on its default cards (native exe only),
#   - the save2 close-up at scale 3 (fields 3,790 / 3,850: texture detail, BRINGUP "User
#     play-test 2"),
# one rg-game at a time (tools/native/game_slot.sh before each run).  Summary lines on stdout
# and in out/nrender/runs/gate_TAG.txt.
#   render_gate.sh ORACLE_EXE NATIVE_EXE TAG [SCALE] [PARTS]   PARTS default "route boot map tex"
# RT_SKIP_EMU=1 passes through to the route evaluation.
P=../port
emu=$1; nat=$2; tag=$3; scale=${4:-1}; parts=${5:-"route boot map tex"}
out=$P/out/nrender/runs/gate_$tag.txt
: > "$out"
say() { echo "$*"; echo "$*" >> "$out"; }
say "gate $tag: oracle $emu, native $nat, scale $scale, $(date)"
for part in $parts; do
  case $part in
  route)
    $P/tools/native/game_slot.sh
    r=$(SLOTS=2 $P/tools/native/render_route_eval.sh "$emu" "$nat" g_$tag $scale 2>&1)
    say "route x$scale:"; echo "$r" | grep -a "run_hash\|ms/field" | sed 's/^/  /' | tee -a "$out"
    echo "$r" | awk '$1 ~ /^[0-9]+$/' > $P/out/nrender/runs/gate_${tag}_route.tsv
    say "  $(echo "$r" | awk '$1 ~ /^[0-9]+$/ {n++; if (p == "" || $2 < p) p = $2; if ($3 > b) b = $3; if ($5 != "pass") f++}
               END {printf "%d fields, PSNR min %.2f, bad max %.2f %%, failing %d", n, p, b, f}')"
    ;;
  boot)
    for fx in ${GATE_FIXTURES:-save2 factory insectron save2_battle2 ch06_vedan ch09_labyrinth ch12_mariglenn ch13_mariglenn}; do
      $P/tools/native/game_slot.sh
      say "  $($P/tools/native/render_boot_eval.sh "$emu" "$nat" g_$tag $scale $fx 2>&1 | tail -n 1)"
    done
    ;;
  map)
    $P/tools/native/game_slot.sh
    python $P/tools/fixtures/mapcheck.py --exe "$nat" --out $P/out/nrender/runs/gate_${tag}_map > $P/out/nrender/runs/gate_${tag}_map.txt 2>&1
    say "mapcheck: $(grep -c DRAWN $P/out/nrender/runs/gate_${tag}_map.txt) DRAWN, $(grep -c MISSING $P/out/nrender/runs/gate_${tag}_map.txt) MISSING"
    ;;
  tex)
    for m in emu native; do
      e=$nat; [ $m = emu ] && e=$emu
      $P/tools/native/game_slot.sh
      $P/tools/native/render_fx.sh gtx_${tag}_$m $m "$e" boot:save2 3 3800 3790,3850 > /dev/null
    done
    say "save2 close-up x3: $(python $P/tools/native/render_imgcmp.py $P/out/nrender/runs/gtx_${tag}_emu $P/out/nrender/runs/gtx_${tag}_native 2>&1 | awk '$1 ~ /^[0-9]+$/ {printf "%s %s dB %s%% ", $1, $2, $3}')"
    ;;
  esac
done
say "gate $tag done $(date)"
