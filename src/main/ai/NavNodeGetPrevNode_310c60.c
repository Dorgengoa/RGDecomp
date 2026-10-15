#include "types.h"

extern s32 NavGraphGetNode_310cd0(s32, s32);
extern s32 NavNodeGetPrev_311920(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 NavNodeGetPrevNode_310c60(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = NavGraphGetNode_310cd0(p0, p1);
    if (r0 != 0) {
        r1 = NavNodeGetPrev_311920(r0);
        r2 = NavGraphGetNode_310cd0(p0, r1);
        return r2;
    }
    return 0;
}
