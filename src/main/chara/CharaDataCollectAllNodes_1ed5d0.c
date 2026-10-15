#include "types.h"

extern s32 CharaDataCollectNodes_1ed670(s32, s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaDataCollectAllNodes_1ed5d0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 l1;
    s32 l0;
    s32 r2;

    l1 = 0;
    l0 = 0;
    do {
        r2 = CharaDataCollectNodes_1ed670(p0, p1, l0, p2, (p3 + (l1 << 2)), (p4 - l1));
        l0 = (l0 + 1);
        l1 = (l1 + r2);
    } while (l0 < 7);
    return l1;
}
