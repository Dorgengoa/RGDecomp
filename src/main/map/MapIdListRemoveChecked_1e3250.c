#include "types.h"

extern void MapIdListRemove_1e5910(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapIdListRemoveChecked_1e3250(s32 p0, s32 p1, s32 p2)
{
    if (p1 != 0) {
        MapIdListRemove_1e5910(p1, p2);
        return;
    }
}
