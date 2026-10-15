#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapAreaOwnsShare_1dce40(s32, s32);
extern s32 MapAreaGetRecTable_1dce90(s32);
extern s32 MapShareLoadRequest_1ece10(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaLoadShare_1da270(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 rv7;
    s32 r1;
    s32 rv6;
    s32 r2;
    s32 rv5;
    s32 r3;
    s32 r4;

    r0 = MapDataIsLoaded_1e79d0(p0);
    rv7 = rv6;
    if (r0 == 0) {
        rv7 = 0;
    } else {
        r1 = MapAreaOwnsShare_1dce40(p0, p2);
        rv6 = rv5;
        if (r1 == 0) {
            rv6 = 0;
        } else {
            r2 = MapDataIsLoaded_1e79d0(p2);
            rv5 = r4;
            if (r2 != 0) {
                rv5 = 1;
            } else {
                r3 = MapAreaGetRecTable_1dce90(p0);
                r4 = MapShareLoadRequest_1ece10(p2, p1, r3, p3);
                rv5 = r4;
            }
            rv6 = rv5;
        }
        rv7 = rv6;
    }
    return rv7;
}
