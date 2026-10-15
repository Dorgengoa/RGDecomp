#include "types.h"

extern s32 MapDataCloneNames_1e7110(s32, s32);
extern s32 MapBlockBoxListClone_1e03c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapBlockClone_1df760(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = MapDataCloneNames_1e7110(p0, p1);
    rv2 = r1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = MapBlockBoxListClone_1e03c0((p0 + 0x54), p1);
        rv2 = r1;
    }
    return rv2;
}
