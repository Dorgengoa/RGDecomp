#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Interpolated presentation, headless measurement (docs/NATIVE-RENDER.md "Interpolated presentation"):
# one fixture run of EXE with RG_INTERP=1 and the simulated present clock, PNG of every present in
# DUMP_FIELDS, the exact-replay check, the identity census; then the same clock without passes (the
# snap control) and tools/native/interp_smooth.py on both.
#   interp_run.sh NAME EXE MILESTONE [HZ] [FIELDS] [DUMP_FIELDS a-b] [SCALE]
# Output: out/interp/runs/NAME{,_snap}/ (run.log via render_fx.sh in out/nrender/runs/ip_NAME*), dumps
# in out/interp/runs/NAME_dump and NAME_snap_dump, smoothness summary on stdout.
# RG_FX_SCRIPT=path passes through to render_fx.sh (e.g. tools/native/interp_walk.input.txt with
# boot:save2: walk and right-stick pan); tools/native/interp_census.py NAME_census.tsv summarises
# the identity census.
P=../port
name=$1; exe=$2; ms=$3; hz=${4:-144}; fields=${5:-600}; df=${6:-}; scale=${7:-1}
R=$P/out/interp/runs
mkdir -p $R
W=$(cd $R && pwd -W)
for v in "" _snap; do
  rm -rf $R/${name}${v}_dump; mkdir -p $R/${name}${v}_dump
  snap=0; [ "$v" = _snap ] && snap=1
  chk=1; [ "$v" = _snap ] && chk=0
  RG_INTERP=1 RG_INTERP_SIM=$hz RG_INTERP_SIM_SNAP=$snap RG_INTERP_CHECK=$chk RG_INTERP_CENSUS="$W/${name}${v}_census.tsv" \
  RG_INTERP_DUMP="$W/${name}${v}_dump" RG_INTERP_DUMP_FIELDS="$df" \
    $P/tools/native/render_fx.sh ip_${name}${v} native "$exe" "$ms" $scale $fields > /dev/null 2>&1
  grep -a "^interp\|interpolated presents\|run_hash" $P/out/nrender/runs/ip_${name}${v}/run.log
done
[ -n "$df" ] && python $P/tools/native/interp_smooth.py $R/${name}_dump $R/${name}_snap_dump
