#!/bin/bash
# SPDX-License-Identifier: CC0-1.0
# [BUILD_TARGETS="rg-game .."] buildretry.sh DIR ARCH LOG [TRIES] [WAIT_S]: vcninja.ps1 -k 0 in DIR until it succeeds
# (other lanes edit the shared src/ mid-build: a transient compile error is retried after
# WAIT_S seconds, default 120, up to TRIES times, default 15).  Last line of LOG: rc=N.
D=$1; A=$2; L=$3; T=${4:-15}; W=${5:-120}
for i in $(seq 1 $T); do
  echo "=== try $i $(date +%H:%M:%S)" >> $L
  powershell -ExecutionPolicy Bypass -File tools/x64/vcninja.ps1 $D $A -k 0 ${BUILD_TARGETS:-} >> $L 2>&1
  r=$?
  if [ $r = 0 ]; then echo "rc=0" >> $L; exit 0; fi
  grep "error:" $L | tail -3 | sed 's/^/  last: /' >> $L
  sleep $W
done
echo "rc=$r" >> $L
