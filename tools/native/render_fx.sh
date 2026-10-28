#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# One run from a fixture milestone for the native renderer lane (docs/NATIVE-RENDER.md):
# loads MILESTONE of EXE's fixture set (tools/fixtures; generate it first:
# tools/fixtures/regen.py --exe EXE) and runs FIELDS fields.
#   render_fx.sh NAME MODE EXE MILESTONE [SCALE] [FIELDS] [DUMP_FIELDS]
#   MODE: emu | native | verify   (RG_RENDER)
#   MILESTONE: title field battle battle_won town save_point saved, or boot:save1
#              (power-on with the game-save fixture, run_from.py --boot-save)
# Output: out/nrender/runs/NAME/ (run.log, times.tsv, fNNNNN_display.png); prints the
# native-render lines and the mean ms per field of the run (RG_FIELD_TIMES wall).
# Extra env passes through (RG_THREADS, RG_NR_*, RG_GS_OVERLAP, ...).
P=../port
name=$1; mode=$2; exe=$3; ms=$4; scale=${5:-1}; fields=${6:-300}; dump=${7:-}
R=$P/out/nrender/runs/$name
rm -rf "$R"; mkdir -p "$R"
W=$(cd "$R" && pwd -W)
export RG_GPU=hw RG_GPU_SCALE=$scale RG_RENDER=$mode RG_FIELD_TIMES="$W/times.tsv"
[ -n "$dump" ] && export RG_GS_DUMP_DIR="$W" RG_GS_DUMP_FIELDS="$dump"
case $ms in
  boot:*)
    # the card (fxlib.BOOT_CARD: save2_battle2 boots the save2 card), the boot script
    # (goldens/boot_NAME.input.txt, else the card library's generated one in
    # out/fixtures/runs/bootlib), FIELDS after the script's "# boot-end:" (as run_from.py)
    set -- $(cd $P/tools/fixtures && python -c "
import fxlib, sys, pathlib
n = sys.argv[1]
card = fxlib.BOOT_CARD.get(n, n)
s = fxlib.PORT / 'tools' / 'trace' / 'goldens' / f'boot_{n}.input.txt'
if not s.exists():
    s = fxlib.FIXTURES / 'runs' / 'bootlib' / f'{n}.input.txt'
end = 0
for l in s.read_text(encoding='utf-8').splitlines() if s.exists() else []:
    if l.startswith('# boot-end:'):
        end = int(l.split(':', 1)[1].split()[0])
print(fxlib.FIXTURES / 'cards' / card, s, end)" "${ms#boot:}")
    card=$1; script=$2; bend=$3
    [ -n "$RG_FX_SCRIPT" ] && script=$RG_FX_SCRIPT   # another boot script for the same card (same boot-end)
    rm -rf "$R/saves"; cp -r "$card" "$R/saves"
    RG_DATA='data' "$exe" --headless --fields $((bend + fields)) --saves "$W/saves" --input "$(cd "$(dirname "$script")" && pwd -W)/$(basename "$script")" $RG_FX_ARGS > "$R/run.log" 2>&1 ;;
  *) python $P/tools/fixtures/run_from.py "$ms" --exe "$exe" --no-regen --run "$fields" > "$R/run.log" 2>&1 ;;
esac
echo "rc=$?" >> "$R/run.log"
grep -a "native render:\|GS overlap\|rc=" "$R/run.log" | tail -n 4
python - "$R/times.tsv" <<'EOF'
import sys
v = [l.split() for l in open(sys.argv[1]) if l[:1].isdigit()]
v = v[20:] if len(v) > 40 else v   # skip the load's first fields
if v:
    n = len(v)
    print("fields %d  wall %.2f  step %.2f  gs_wait %.2f ms/field" % (
        n, sum(float(x[1]) for x in v) / n, sum(float(x[2]) for x in v) / n, sum(float(x[5]) for x in v) / n))
EOF
