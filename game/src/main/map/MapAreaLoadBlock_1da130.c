/* rgp:protos */
#define RGP_SELF_MapAreaLoadBlock_1da130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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

    r0 = ((unsigned char)MapDataIsLoaded_1e79d0(p0));
    if (r0 == 0) {
        return 0;
    }
    r1 = MapAreaOwnsBlock_1dce10(p0, p2);
    if (r1 == 0) {
        rv10 = 0;
    } else {
        r2 = ((unsigned char)MapDataIsLoaded_1e79d0(p2));
        if (r2 != 0) {
            rv9 = 1;
        } else {
            r3 = ((short)MapBlockGetShareId_1e0080(p2));
            r4 = MapAreaFindShareById_1dc820(p0, r3);
            rv6 = r4;
            if (r4 != 0) {
                r5 = ((unsigned char)MapDataIsLoaded_1e79d0(r4));
                if (r5 == 0) {
                    return 0;
                }
                rv6 = r5;
            }
            r7 = ((s32)MapAreaGetRecTable_1dce90(p0));
            r8 = MapBlockLoadRequest_1df0d0(p2, p1, r7, p3, -1);
            rv9 = r8;
        }
        rv10 = rv9;
    }
    return rv10;
}
