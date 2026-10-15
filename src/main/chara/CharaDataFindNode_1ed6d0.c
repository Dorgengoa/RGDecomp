#include "types.h"

extern s32 CharaDataFindSubRecById_1ed710(s32, s32, s32);
extern s32 CharaDataSubRecFindNode_1ee690(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaDataFindNode_1ed6d0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 r1;

    r0 = CharaDataFindSubRecById_1ed710(p0, p1, p2);
    if (r0 == 0) {
        return 0;
    }
    r1 = CharaDataSubRecFindNode_1ee690(r0, p3);
    return r1;
}
