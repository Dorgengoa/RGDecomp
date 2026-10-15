#include "types.h"

extern s32 ObjRecIsFree_1c3d00(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventCastFindFreeObjSlot_2503e0(s32 p0)
{
    s32 l0;
    s32 r1;

    l0 = 0;
    while (l0 < 0x40) {
        r1 = ObjRecIsFree_1c3d00(p0, 1, (l0 + 0x40));
        if (r1 != 0) {
            return (l0 + 0x40);
        }
        l0 = (l0 + 1);
    }
    return -1;
}
