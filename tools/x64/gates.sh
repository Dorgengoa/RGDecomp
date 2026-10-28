#!/bin/bash
# SPDX-License-Identifier: CC0-1.0
# x64 lane gate set (docs/X64-PLAN.md section 0.7) on one build dir, i686 or x64.
#   sh tools/x64/gates.sh BUILD_DIR OUT_DIR [STEP ..]
# STEPs (default all, in this order): regen verify boot map cam link addr render ctest
#   regen   regen.py --check 300 (rewrites the shared card out/fixtures/cards/save2: it is
#           backed up first and ALWAYS restored afterwards)
#   verify  verify.py (every milestone state + 300 fields: run + frame hash)
#   boot    bootcheck.py --all     map  mapcheck.py     cam  camprobe.py ch01_salgin ch05_factory
#   link    link_audit.py check --forbid all --extra rg_ps2_hwbus (the exe's map)
#   addr    addr_census.py --build BUILD_DIR --check
#   render  render_gate.sh (needs rg-game-oracle.exe in BUILD_DIR)
#   ctest   ctest -j2 -LE fixtures, then -j1 -L fixtures
# Each step writes OUT_DIR/<step>.txt ending in "<step> exit N".  One rg-game at a time:
# run the steps of one OUT_DIR in sequence.  Background shell jobs die at 2 h: split the
# steps over several calls (regen+verify ~40 min, boot ~40 min, ctest ~60 min).
P=../port
B=$(cd "$1" && pwd); R=$2; shift 2
STEPS=${*:-regen verify boot map cam link addr render ctest}
CTEST=../tools/cmake-3.31.7-windows-x86_64/bin/ctest.exe
cd $P
mkdir -p $R
cp -f $B/rg-game.exe $B/rg-game.map $R/ || { echo "gates: cannot copy the exe into $R" >&2; exit 1; }
[ -f $B/rg-game-oracle.exe ] && cp $B/rg-game-oracle.exe $R/
EXE=$R/rg-game.exe
for s in $STEPS; do
  echo "[$(date +%H:%M:%S)] $s" >> $R/gates.log
  case $s in
  regen)
    rm -rf $R/save2_backup && cp -r out/fixtures/cards/save2 $R/save2_backup
    python tools/fixtures/regen.py --exe $EXE --check 300 > $R/regen.txt 2>&1
    echo "regen exit $?" >> $R/regen.txt
    if diff -r out/fixtures/cards/save2 $R/save2_backup > /dev/null; then
      echo "card save2: identical after regen" >> $R/regen.txt
    else
      echo "card save2: DIFFERS after regen -> restored the backup" >> $R/regen.txt
      rm -rf out/fixtures/cards/save2 && cp -r $R/save2_backup out/fixtures/cards/save2
    fi ;;
  verify) python tools/fixtures/verify.py --exe $EXE > $R/verify.txt 2>&1; echo "verify exit $?" >> $R/verify.txt ;;
  boot) python tools/fixtures/bootcheck.py --all --exe $EXE --tsv $R/boot.tsv --keep-logs $R/bootlogs > $R/boot.txt 2>&1
        echo "boot exit $?" >> $R/boot.txt ;;
  map) python tools/fixtures/mapcheck.py --exe $EXE --out $R/mapcheck > $R/map.txt 2>&1; echo "map exit $?" >> $R/map.txt ;;
  cam) python tools/fixtures/camprobe.py --exe $EXE ch01_salgin ch05_factory > $R/cam.txt 2>&1; echo "cam exit $?" >> $R/cam.txt ;;
  link) python tools/native/link_audit.py check $R/rg-game.map --forbid all --extra rg_ps2_hwbus > $R/link.txt 2>&1
        echo "link exit $?" >> $R/link.txt ;;
  addr) python tools/native/addr_census.py --build $B --check > $R/addr.txt 2>&1; echo "addr exit $?" >> $R/addr.txt ;;
  render) sh tools/native/render_gate.sh $R/rg-game-oracle.exe $EXE $(basename $R) > $R/render.txt 2>&1
          echo "render exit $?" >> $R/render.txt ;;
  ctest)
    (cd $B && $CTEST -j2 -LE fixtures --timeout 1800 > $P/$R/ctest.txt 2>&1; echo "ctest exit $?" >> $P/$R/ctest.txt
     $CTEST -j1 -L fixtures --timeout 3600 > $P/$R/ctest_fixtures.txt 2>&1; echo "ctest_fixtures exit $?" >> $P/$R/ctest_fixtures.txt) ;;
  esac
done
echo "[$(date +%H:%M:%S)] done: $STEPS" >> $R/gates.log
