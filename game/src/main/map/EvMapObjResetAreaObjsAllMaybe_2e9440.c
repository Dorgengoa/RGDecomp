/* rgp:protos */
#define RGP_SELF_EvMapObjResetAreaObjsAllMaybe_2e9440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EvMapObjResetAreaObjsAllMaybe_2e9440(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 r3;
    s32 r4;

    r0 = ((s32)EventObjMgrGetTypeList_2e9d60(p0, 8));
    r1 = DListGetHead_42ea60(r0);
    l2 = r1;
    while (l2 != 0) {
        r3 = EvMapObjResetAreaObjsMaybe_366750((l2 + 0x10));
        r4 = DListGetNext_42eb30(l2);
        l2 = r4;
    }
}
