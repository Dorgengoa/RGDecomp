#include "types.h"

extern s32 MapFindAreaSlotById_1e4cb0(s32, s32);
extern void MapAreaReleaseAndReset_1e2d60(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapAreaReleaseById_1e2e00(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = MapFindAreaSlotById_1e4cb0(p0, p1);
    MapAreaReleaseAndReset_1e2d60(p0, r0, p2);
}
