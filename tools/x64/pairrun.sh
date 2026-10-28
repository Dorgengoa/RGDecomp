#!/bin/bash
# SPDX-License-Identifier: CC0-1.0
# pairrun.sh OUT FIELDS I686_EXE X64_EXE [rg-game args..]   (docs/X64-PLAN.md section 0.7)
# The x64 parity run: both exes headless on the golden power-on route to FIELDS (in
# parallel, each in OUT/{i686,x64} with a fresh saves dir), RG_GPU=hw, with RG_HASH_LOG and
# RG_AUDIO_CMDLOG; then tools/x64/hashdiff.py of the two hash logs and the first lines where
# the audio command logs differ (timestamps dropped).  Summary in OUT/pair.txt.
P=../port
O=$1; N=$2; A=$3; X=$4; shift 4
mkdir -p $O
one() {  # tag exe
  W=$O/$1; rm -rf $W; mkdir -p $W/saves
  RG_DATA=$(cygpath -w $P/data) RG_GPU=hw RG_HASH_LOG=$(cygpath -w $W/hash.tsv) \
  RG_AUDIO_CMDLOG=$(cygpath -w $W/cmd.tsv) \
    $2 --headless --fields $N --saves $(cygpath -w $W/saves) \
       --input $(cygpath -w $P/tools/trace/goldens/newgame_save2.input.txt) "${@:3}" > $W/out.txt 2> $W/err.txt
  echo "rc=$?" >> $W/out.txt
}
one i686 $A "$@" &
one x64 $X "$@" &
wait
{
  echo "pairrun fields=$N"
  for t in i686 x64; do echo "$t: $(grep -h 'run_hash=' $O/$t/out.txt $O/$t/err.txt | tail -1) $(tail -1 $O/$t/out.txt)"; done
  python $P/tools/x64/hashdiff.py $O/i686/hash.tsv $O/x64/hash.tsv
  cut -f2- $O/i686/cmd.tsv | grep -v '^V' > $O/i686/cmd.seq
  cut -f2- $O/x64/cmd.tsv | grep -v '^V' > $O/x64/cmd.seq
  echo "audio cmd lines: i686 $(wc -l < $O/i686/cmd.seq) x64 $(wc -l < $O/x64/cmd.seq)"
  if cmp -s $O/i686/cmd.tsv $O/x64/cmd.tsv; then echo "audio cmdlog: IDENTICAL (timestamps included)"
  else echo "audio cmdlog: differs; first sequence differences:"; diff $O/i686/cmd.seq $O/x64/cmd.seq | head -12; fi
} > $O/pair.txt 2>&1
cat $O/pair.txt
