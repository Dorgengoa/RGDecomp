/* rgp:protos */
#define RGP_SELF_EvDoorObjCloseByName_2e8e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvDoorObjCloseByName_2e8e30(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = EventObjMgrFindObjByName_2e9920(p0, p1, 9);
    rv2 = 1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = (EvDoorObjPlayClose_303be0(r0, 1), (s32)0);
        rv2 = 1;
    }
    return rv2;
}
