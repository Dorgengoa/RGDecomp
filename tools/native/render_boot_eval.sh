#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Level-4 images on the game-save boot fixtures (docs/NATIVE-RENDER.md "Verification (7)";
# fixtures: docs/TEST-FIXTURES.md, tools/fixtures/fxlib.py BOOT_FIXTURES): per fixture one
# power-on run of the oracle twin in emu mode and one of the native exe with the fixture's card
# and boot script (render_fx.sh boot:NAME), display dumps at each milestone field and + 40,
# then render_imgcmp.py emu vs native.
#   render_boot_eval.sh ORACLE_EXE NATIVE_EXE TAG [SCALE] [FIXTURES]
#   FIXTURES default: save2 factory insectron save2_battle2
# Output: out/nrender/runs/bt_TAG_NAME_{emu,nat,cmp}; one summary line per fixture.
P=../port
emu=$1; nat=$2; tag=$3; scale=${4:-1}; fxs=${5:-"save2 factory insectron save2_battle2"}
for fx in $fxs; do
  F=$(cd $P/tools/fixtures && python -c "
import fxlib, sys
fs = []
if fxlib.BOOT_SCRIPT.get(sys.argv[1]) == 'lib':
    fs = [3800, 4000]     # card library: field control from ~3,730 (milestones are relative to it)
else:
    for m in fxlib.BOOT_FIXTURES[sys.argv[1]]:
        fs += [m[1], m[1] + 40]
print(','.join(str(x) for x in fs))" $fx)
  last=$(echo $F | tr ',' '\n' | sort -n | tail -n 1)
  $P/tools/native/render_fx.sh bt_${tag}_${fx}_emu emu "$emu" boot:$fx $scale $((last + 10)) $F > /dev/null
  $P/tools/native/render_fx.sh bt_${tag}_${fx}_nat native "$nat" boot:$fx $scale $((last + 10)) $F > /dev/null
  he=$(grep -a run_hash $P/out/nrender/runs/bt_${tag}_${fx}_emu/run.log | tail -n 1 | sed 's/.*run_hash=//')
  hn=$(grep -a run_hash $P/out/nrender/runs/bt_${tag}_${fx}_nat/run.log | tail -n 1 | sed 's/.*run_hash=//')
  r=$(python $P/tools/native/render_imgcmp.py $P/out/nrender/runs/bt_${tag}_${fx}_emu $P/out/nrender/runs/bt_${tag}_${fx}_nat \
        --out $P/out/nrender/runs/bt_${tag}_${fx}_cmp 2>&1)
  sum=$(echo "$r" | awk '$1 ~ /^[0-9]+$/ {n++; if (p == "" || $2 < p) p = $2; if ($3 > b) b = $3; if (q == "" || $4 < q) q = $4}
                         END {if (n) printf "%d fields, PSNR min %.2f, bad max %.2f %%, SSIM min %.3f", n, p, b, q; else printf "no fields"}')
  echo "$fx x$scale: $sum: $(echo "$r" | tail -n 1); run hash emu $he native $hn"
done
