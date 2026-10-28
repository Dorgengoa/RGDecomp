#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Composite pairing census + motion trace on the ch07_rosa battle route (history "2026-10-26
# (interp3)"): one headless run of EXE from STATE (an autobattle.py prep state of that exe) at a
# simulated HZ with RG_INTERP_DEBUG=1 (strip-group lines) and RG_INTERP_TRACE, then
# tools/native/interp_groups.py and tools/native/interp_trace.py.
#   interp3_battle.sh NAME EXE [STATE|-] [HZ] [TO]  STATE - = prep it (autobattle.py prep CARD, default
#   ch07_rosa; save states load only into the exe that wrote them); extra env passes through
#   (RG_INTERP_ZSPAIR=0 ...)
# Output: out/interp3/NAME/ (run/log.txt, trace.tsv, groups.txt, trace.txt)
P=../port
name=$1; exe=$2; state=${3:--}; hz=${4:-144}; to=${5:-5300}
if [ "$state" = - ]; then
  python $P/tools/fixtures/autobattle.py prep ${CARD:-ch07_rosa} --exe "$exe" > /tmp/interp3_prep_$$.log 2>&1
  state=$(python -c "import re,sys;print(re.search(r'state (\S+rgstate)',open(sys.argv[1]).read()).group(1))" /tmp/interp3_prep_$$.log)
fi
R=$P/out/interp3/$name
rm -rf $R; mkdir -p $R
W=$(cd $R && pwd -W)
RG_GPU=hw RG_INTERP=1 RG_INTERP_SIM=$hz RG_INTERP_DEBUG=1 RG_INTERP_TRACE="$W/trace.tsv" \
  python $P/tools/fixtures/play.py --from "$state" --to $to --input ${ROUTE:-$P/tools/native/interp_fight_rosa.route.txt} \
  --out $R/run --exe "$exe" > $R/play.txt 2>&1
echo "$name: $(grep -a 'run_hash=' $R/run/log.txt | tail -1) $(grep -a -o 'composite strip groups.*' $R/run/log.txt | cut -c1-120)"
python $P/tools/native/interp_groups.py $R/run/log.txt > $R/groups.txt; head -12 $R/groups.txt
python $P/tools/native/interp_trace.py $R/trace.tsv > $R/trace.txt; cat $R/trace.txt
