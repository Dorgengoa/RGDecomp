/* rgp:protos */
#define RGP_SELF_InsectCageMgrFindSlotById_39b0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMgrFindSlotById_39b0c0(s32 p0, s32 p1)
{
    s32 r2;
    s32 l1;
    s32 l0;

    if (p1 < 0) {
        return 0;
    }
    l0 = 0;
    l1 = p0;
    while (l0 < 3) {
        r2 = ((short)InsectCageSlotGetId_39b460(l1));
        if (p1 == r2) {
            return l1;
        }
        l0 = (l0 + 1);
        l1 = (l1 + 0x30);
    }
    return 0;
}
