#include "types.h"

extern s32 MapDataGetId_1e7bd0(s32);
extern void MapBlockGetName_1dff20(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapBlockGetOwnName_1dfef0(s32 p0)
{
    s32 r0;

    r0 = MapDataGetId_1e7bd0(p0);
    MapBlockGetName_1dff20(p0, r0);
}
