#include "types.h"

extern s32 MapAreaFindBlockById_1dc760(s32, s32);
extern void MapAreaReleaseBlockIfOwned_1d9d20(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapAreaReleaseBlockById_1d9d70(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = MapAreaFindBlockById_1dc760(p0, p1);
    MapAreaReleaseBlockIfOwned_1d9d20(p0, r0, p2);
}
