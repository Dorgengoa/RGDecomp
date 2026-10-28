#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Interleaved A/B timing from a fixture (docs/NATIVE-RENDER.md "Tools"): the machine is
# shared, so configurations are run alternately, REPS rounds, and each mean is printed.
#   render_ab.sh EXE MILESTONE SCALE FIELDS REPS "ENV_A" "ENV_B" ["ENV_C" ...]
# ENV_x: space-separated VAR=VALUE assignments ("-" for none), e.g. "RG_GS_ELIDE=0".
# Each run: tools/native/render_fx.sh (RG_RENDER=native unless ENV sets RG_RENDER).
P=../port
exe=$1; ms=$2; sc=$3; fl=$4; reps=$5; shift 5
for r in $(seq 1 $reps); do
  i=0
  for cfg in "$@"; do
    i=$((i + 1))
    e=$cfg; [ "$e" = "-" ] && e=""
    mode=native
    case " $e " in *" RG_RENDER="*) mode=$(echo " $e " | sed 's/.* RG_RENDER=\([a-z]*\) .*/\1/');; esac
    line=$(env $e $P/tools/native/render_fx.sh ab_${i}_$r $mode "$exe" $ms $sc $fl | tail -n 1)
    echo "round $r [$cfg]: $line"
  done
done
