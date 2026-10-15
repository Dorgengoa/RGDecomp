#include "types.h"

extern s32 MapResolveAreaLightRefById_1e5680(s32, s32);
extern void MapAreaGetLightSetOrDefault_1e5430(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapGetAreaLightSetById_1e54d0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = MapResolveAreaLightRefById_1e5680(p0, p1);
    MapAreaGetLightSetOrDefault_1e5430(p0, r0, p2);
}
