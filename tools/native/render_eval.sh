#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Level-4 image evaluation on the route milestones (docs/NATIVE-RENDER.md "RG_RENDER=native as
# the default?"): for every milestone and scale, an emu and a native run from EXE's fixture
# set (tools/fixtures/regen.py --exe EXE first) with display dumps at milestone + 60, 150, 280,
# then render_imgcmp.py emu vs native.  Also records ms/field of both runs.
#   render_eval.sh EXE TAG [SCALES] [MILESTONES]
#   MILESTONES default: battle battle_won town save_point saved boot:save1
# Output: out/nrender/runs/ev_TAG_*; a summary table on stdout and in out/nrender/runs/ev_TAG.md.
P=../port
exe=$1; tag=$2; scales=${3:-"1 3"}; mss=${4:-"battle battle_won town save_point saved boot:save1"}
S=$P/out/nrender/runs/ev_$tag.md
echo "| milestone | scale | fields | PSNR dB (min) | bad % (max) | SSIM (min) | verdict | emu ms/field | native ms/field |" > $S
echo "| --- | --- | --- | --- | --- | --- | --- | --- | --- |" >> $S
for ms in $mss; do
  # the milestone's field from tools/fixtures/fxlib.py (the route lane re-times them)
  case $ms in
    boot:*) f0=0;;
    *) f0=$(cd $P/tools/fixtures && python -c "import fxlib,sys; print(fxlib.MILESTONE_FIELDS[sys.argv[1]])" $ms);;
  esac
  d="$((f0 + 60)),$((f0 + 150)),$((f0 + 280))"
  [ "$f0" = 0 ] && d="3700,3800,3900"
  fl=300; [ "$f0" = 0 ] && fl=3900
  for s in $scales; do
    n=$(echo $ms | tr ':' '_')
    e=$($P/tools/native/render_fx.sh ev_${tag}_${n}_emu_x$s emu "$exe" $ms $s $fl $d | tail -n 1 | awk '{print $4}')
    v=$($P/tools/native/render_fx.sh ev_${tag}_${n}_nat_x$s native "$exe" $ms $s $fl $d | tail -n 1 | awk '{print $4}')
    r=$(python $P/tools/native/render_imgcmp.py $P/out/nrender/runs/ev_${tag}_${n}_emu_x$s $P/out/nrender/runs/ev_${tag}_${n}_nat_x$s \
          --out $P/out/nrender/runs/ev_${tag}_${n}_cmp_x$s 2>&1)
    sum=$(echo "$r" | awk '$1 ~ /^[0-9]+$/ {n++; if (p == "" || $2 < p) p = $2; if ($3 > b) b = $3; if (q == "" || $4 < q) q = $4}
                           END {if (n) printf "%d | %.2f | %.2f | %.3f", n, p, b, q; else printf "0 | - | - | -"}')
    verdict=$(echo "$r" | tail -n 1)
    echo "| $ms | $s | $sum | $verdict | $e | $v |" | tee -a $S
  done
done
