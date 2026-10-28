/* rgp:protos */
#define RGP_SELF_EvDoorObjOpenByName_2e8f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvDoorObjOpenByName_2e8f30(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = EventObjMgrFindObjByName_2e9920(p0, p1, 9);
    rv2 = 1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = (EvDoorObjPlayOpen_303c90(r0, p2), (s32)0);
        rv2 = 1;
    }
    return rv2;
}
