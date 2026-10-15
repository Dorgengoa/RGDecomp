#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapAreaOwnsBlock_1dce10(s32, s32);
extern s32 MapBlockGetShareId_1e0080(s32);
extern s32 MapAreaFindShareById_1dc820(s32, s32);
extern s32 MapAreaGetRecTable_1dce90(s32);
extern s32 MapBlockLoadRequest_1df0d0(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaLoadBlock_1da130(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 r1;
    s32 rv10;
    s32 r2;
    s32 rv9;
    s32 r3;
    s32 r4;
    s32 rv6;
    s32 r5;
    s32 r7;
    s32 r8;

    r0 = MapDataIsLoaded_1e79d0(p0);
    if (r0 == 0) {
        return 0;
    }
    r1 = MapAreaOwnsBlock_1dce10(p0, p2);
    if (r1 == 0) {
        rv10 = 0;
    } else {
        r2 = MapDataIsLoaded_1e79d0(p2);
        if (r2 != 0) {
            rv9 = 1;
        } else {
            r3 = MapBlockGetShareId_1e0080(p2);
            r4 = MapAreaFindShareById_1dc820(p0, r3);
            rv6 = r4;
            if (r4 != 0) {
                r5 = MapDataIsLoaded_1e79d0(r4);
                if (r5 == 0) {
                    return 0;
                }
                rv6 = r5;
            }
            r7 = MapAreaGetRecTable_1dce90(p0);
            r8 = MapBlockLoadRequest_1df0d0(p2, p1, r7, p3, -1);
            rv9 = r8;
        }
        rv10 = rv9;
    }
    return rv10;
}
