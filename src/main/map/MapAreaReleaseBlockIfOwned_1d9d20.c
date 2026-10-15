#include "types.h"

extern s32 MapAreaOwnsBlock_1dce10(s32);
extern s32 MapBlockRelease_1df030(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaReleaseBlockIfOwned_1d9d20(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = MapAreaOwnsBlock_1dce10(p0);
    if (r0 != 0) {
        r1 = MapBlockRelease_1df030(p1, p2);
        return r1;
    }
    return 0;
}
