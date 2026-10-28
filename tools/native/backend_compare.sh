#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Backend comparison (docs/NATIVE-VULKAN.md "Verification"): the same native-only exe run twice
# from power-on on the golden route (or a boot fixture), once per graphics API ($RG_GPU_API=d3d11 /
# vulkan), display dumps at the same fields, then per-frame PSNR / bad% / SSIM of Vulkan against
# Direct3D 11 (render_imgcmp.py, D3D11 = reference) and the run hashes of both runs (game logic
# must not depend on the backend: they must be equal).  One rg-game at a time.
#   backend_compare.sh NATIVE_EXE TAG [SCALE] [WHAT] [EXTRA rg-game ARGS...]
#   WHAT: route (default: tools/fixtures/fxlib.py milestones + 60 / 150 / 280, as
#         render_route_eval.sh) or boot:FIXTURE (render_fx.sh's boot fixtures, + 40 per milestone)
#   BC_MAX_FIELD=N: only fields <= N (route)    BC_SKIP_D3D=1: keep the D3D11 run already there
# Output: out/nrender/runs/bc_TAG_{d3d11,vulkan}/ (run.log, times.tsv, dumps), bc_TAG_cmp/ (side by
# side + amplified differences), summary lines on stdout and in out/nrender/runs/bc_TAG.txt.
P=../port
exe=$1; tag=$2; scale=${3:-1}; what=${4:-route}; shift 4 2>/dev/null || shift $#
sum=$P/out/nrender/runs/bc_$tag.txt
: > "$sum"
say() { echo "$*"; echo "$*" >> "$sum"; }
case $what in
route)
  F=$(cd $P/tools/fixtures && python -c "
import fxlib, os
mx = int(os.environ.get('BC_MAX_FIELD', '0') or 0)
fs = []
for n, f, _ in fxlib.MILESTONES:
    fs += [x for x in (f + 60, f + 150, f + 280) if not mx or x <= mx]
print(','.join(str(x) for x in fs))")
  ;;
boot:*)
  fx=${what#boot:}
  F=$(cd $P/tools/fixtures && python -c "
import fxlib, sys
fs = []
if fxlib.BOOT_SCRIPT.get(sys.argv[1]) == 'lib':
    fs = [3800, 4000]
else:
    for m in fxlib.BOOT_FIXTURES[sys.argv[1]]:
        fs += [m[1], m[1] + 40]
print(','.join(str(x) for x in fs))" $fx)
  ;;
*) echo "WHAT: route or boot:FIXTURE"; exit 2 ;;
esac
last=$(echo $F | tr ',' '\n' | sort -n | tail -n 1)
say "backend compare $tag: $exe, $what, scale $scale, fields $F, $(date)"
for api in d3d11 vulkan; do
  R=$P/out/nrender/runs/bc_${tag}_$api
  if [ $api = d3d11 ] && [ -n "$BC_SKIP_D3D" ] && [ -f "$R/run.log" ]; then
    say "$api: (kept) $(grep -a 'run_hash' "$R/run.log" | tail -n 1)"; continue
  fi
  $P/tools/native/game_slot.sh
  if [ "$what" = route ]; then
    rm -rf "$R"; mkdir -p "$R/saves"
    W=$(cd "$R" && pwd -W)
    RG_GPU_API=$api RG_DATA='data' RG_GPU=hw RG_GPU_SCALE=$scale RG_RENDER=native RG_FIELD_TIMES="$W/times.tsv" \
    RG_GS_DUMP_DIR="$W" RG_GS_DUMP_FIELDS="$F" \
      "$exe" --headless --fields $((last + 10)) --saves "$W/saves" \
      --input tools/trace/goldens/newgame_save2.input.txt "$@" > "$R/run.log" 2>&1
    echo "rc=$?" >> "$R/run.log"
  else
    RG_GPU_API=$api $P/tools/native/render_fx.sh bc_${tag}_$api native "$exe" $what $scale $((last + 10)) $F > /dev/null
  fi
  dev=$(grep -a "rg gpu:" "$R/run.log" | head -n 1)
  ms=$(python - "$R/times.tsv" <<'EOF'
import sys, os
p = sys.argv[1]
v = [l.split() for l in open(p) if l[:1].isdigit()] if os.path.exists(p) else []
v = [x for x in v if int(x[0]) >= 7400] or v
print("ms/field %.2f over %d fields" % (sum(float(x[1]) for x in v) / max(len(v), 1), len(v)) if v else "no times")
EOF
)
  say "$api: $(grep -a 'run_hash' "$R/run.log" | tail -n 1) $ms ${dev:+($dev)}"
done
ha=$(grep -a run_hash $P/out/nrender/runs/bc_${tag}_d3d11/run.log | tail -n 1 | sed 's/.*run_hash=//')
hb=$(grep -a run_hash $P/out/nrender/runs/bc_${tag}_vulkan/run.log | tail -n 1 | sed 's/.*run_hash=//')
if [ -n "$ha" ] && [ "$ha" = "$hb" ]; then say "run hash: identical ($ha)"; else say "run hash: DIFFER (d3d11 $ha, vulkan $hb)"; fi
r=$(python $P/tools/native/render_imgcmp.py $P/out/nrender/runs/bc_${tag}_d3d11 $P/out/nrender/runs/bc_${tag}_vulkan \
      --out $P/out/nrender/runs/bc_${tag}_cmp 2>&1)
echo "$r" | sed 's/^/  /' >> "$sum"
echo "$r" | awk '$1 ~ /^[0-9]+$/' > $P/out/nrender/runs/bc_${tag}.tsv
say "vulkan vs d3d11: $(echo "$r" | awk '$1 ~ /^[0-9]+$/ {n++; if (p == "" || $2 < p) p = $2; if ($3 > b) b = $3; if (q == "" || $4 < q) q = $4; if ($2 >= 99) e++; if ($5 != "pass") f++}
           END {if (n) printf "%d fields, %d identical, PSNR min %.2f, bad max %.2f %%, SSIM min %.3f, failing %d", n, e, p, b, q, f; else printf "no fields"}')"
