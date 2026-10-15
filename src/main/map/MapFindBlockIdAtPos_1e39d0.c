#include "types.h"

extern s32 MapFindBlockAtPos_1e3a00(s32, s32, f32);
extern s32 MapDataGetId_1e7bd0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapFindBlockIdAtPos_1e39d0(s32 p0, s32 p1, f32 fa0)
{
    s32 r0;
    s32 r1;

    r0 = MapFindBlockAtPos_1e3a00(p0, p1, fa0);
    if (r0 != 0) {
        r1 = MapDataGetId_1e7bd0(r0);
        return r1;
    }
    return -1;
}
