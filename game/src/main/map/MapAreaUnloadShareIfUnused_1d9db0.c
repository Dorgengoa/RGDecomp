/* rgp:protos */
#define RGP_SELF_MapAreaUnloadShareIfUnused_1d9db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
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

s32 MapAreaUnloadShareIfUnused_1d9db0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 rv11;
    s32 r1;
    s32 rv9;
    s32 rv10;
    s32 r2;
    s32 l3;
    s32 l4;
    s32 r5;
    s32 r6;
    s32 rv8;
    s32 r7;
    s32 r12;

    r0 = MapAreaOwnsShare_1dce40(p0, (int)p1);
    if (r0 == 0) {
        return 0;
    }
    rv11 = p0;
    if (p2 == 0) {
        r1 = MapAreaGetBlocks_1dce30(p0);
        rv9 = p0;
        rv10 = 0;
        if (r1 != 0) {
            r2 = MapAreaGetBlockCount_1dce20(p0);
            l3 = 0;
            l4 = r1;
            while (l3 < r2) {
                r5 = ((short)MapBlockGetShareId_1e0080(l4));
                r6 = ((short)MapDataGetId_1e7bd0(p1));
                rv8 = r6;
                if (r5 == r6) {
                    r7 = ((unsigned char)MapDataIsLoaded_1e79d0(l4));
                    if (r7 != 0) {
                        return 0;
                    }
                    rv8 = 0;
                }
                l3 = (l3 + 1);
                l4 = (l4 + 0xCC);
            }
            rv9 = r2;
            rv10 = l4;
        }
        rv11 = rv9;
    }
    r12 = MapDataUnloadThunk_1e6690(p1, p2);
    return r12;
}
