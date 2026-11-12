#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# Wait for a free rg-game slot (machine rule: at most 2 rg-game processes machine-wide).
# Every rg-game exe enforces the rule itself (src/game/rg_slots.c: two named mutexes taken
# before main, a third process waits inside the exe), so by default this returns at once and
# the exe's mutex does the waiting.  (Counting processes here, the old behaviour, starved a
# lane whenever other lanes kept two runs going plus one waiting: a waiting exe counts too.)
#   SLOT_POLL=1   the old behaviour: poll tasklist every 2 s until fewer than SLOTS (2)
#                 rg-game / rg-game-oracle processes run
# Lane scripts call it before each run and run one game at a time themselves.
[ "${SLOT_POLL:-0}" = 1 ] || exit 0
SLOTS=${SLOTS:-2}
while :; do
  n=$(tasklist 2>/dev/null | grep -c -i "^rg-game")
  [ "$n" -lt "$SLOTS" ] && exit 0
  sleep 2
done
