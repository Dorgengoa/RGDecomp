/* rgp:protos */
#define RGP_SELF_EvMapObjFindById_2e9810 1
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

s32 EvMapObjFindById_2e9810(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 l3;
    s32 r4;
    s32 r5;

    r0 = ((s32)EventObjMgrGetTypeList_2e9d60(p0, 8));
    r1 = DListGetHead_42ea60(r0);
    l2 = r1;
    l3 = r1;
    while (l3 != 0) {
        r4 = ((short)EvMapObjGetId_366b70((l3 + 0x10)));
        if (p1 == r4) {
            return (l3 + 0x10);
        }
        r5 = DListGetNext_42eb30(l3);
        l2 = r5;
        l3 = r5;
    }
    return 0;
}
