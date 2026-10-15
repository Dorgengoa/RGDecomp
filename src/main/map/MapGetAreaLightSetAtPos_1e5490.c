#include "types.h"

extern s32 MapResolveAreaLightRefAtPos_1e5640(s32, s32);
extern void MapAreaGetLightSetOrDefault_1e5430(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapGetAreaLightSetAtPos_1e5490(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = MapResolveAreaLightRefAtPos_1e5640(p0, p1);
    MapAreaGetLightSetOrDefault_1e5430(p0, r0, p2);
}
