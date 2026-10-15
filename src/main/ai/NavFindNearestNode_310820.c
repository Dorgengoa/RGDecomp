#include "types.h"

extern s32 NavGraphGetNodes_310cc0(s32);
extern s32 NavXformPointToLocal_310d50(s32, void *, s32);
extern s32 VecCopy_1cbe30(void *, s32);
extern s32 NavFindNearestEdgePoint_310380(s32, void *, void *, s32);
extern s32 NavEdgeNearestNode_30f940(s32, void *, s32, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 NavFindNearestNode_310820(s32 p0, s32 p1, s32 p2)
{
    u128 v50;
    u128 v40;
    s32 r0;
    s32 rv7;
    s32 rv3;
    s32 r1;
    s32 r2;
    s32 r4;
    s32 rv6;
    s32 r5;

    r0 = NavGraphGetNodes_310cc0(p0);
    if (r0 == 0) {
        rv7 = 0;
    } else {
        if ((p2 & 0xFF) == 0) {
            r1 = NavXformPointToLocal_310d50(p0, &v50, p1);
            rv3 = r1;
        } else {
            r2 = VecCopy_1cbe30(&v50, p1);
            rv3 = r2;
        }
        r4 = NavFindNearestEdgePoint_310380(p0, &v40, &v50, 1);
        if (r4 == 0) {
            rv6 = 0;
        } else {
            r5 = NavEdgeNearestNode_30f940(p0, &v50, r4, 1);
            rv6 = r5;
        }
        rv7 = rv6;
    }
    return rv7;
}
