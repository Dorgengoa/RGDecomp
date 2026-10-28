/* rgp:protos */
#define RGP_SELF_NavRemoveGraphById_30a3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 NavRemoveGraphById_30a3b0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv6;
    s32 r2;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 r7;

    r0 = ((s32)GetNavMgr_2d1950());
    r1 = NavMgrGetCurrent_30cab0(r0);
    rv6 = r1;
    if (r1 != 0) {
        r2 = NavMgrGetCurrent_30cab0(r0);
        r3 = NavGraphGetId_310e90(r2);
        rv5 = r3;
        if (p0 == r3) {
            r4 = NavMgrSetCurrent_30ca70(r0, 0);
            rv5 = r4;
        }
        rv6 = rv5;
    }
    r7 = NavMgrRemoveGraph_30cdd0(r0, p0);
    return r7;
}
