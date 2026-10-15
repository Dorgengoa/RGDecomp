#include "types.h"

extern s32 MapSlotsFindLoadedByName_1e4550(s32, s32, s32);
extern s32 MapDataFindNodeByName_1e7190(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapFindNodeInAreaByName_1e43f0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = MapSlotsFindLoadedByName_1e4550(p0, p1, 0);
    if (r0 != 0) {
        r1 = MapDataFindNodeByName_1e7190(r0, p2);
        return r1;
    }
    return 0;
}
