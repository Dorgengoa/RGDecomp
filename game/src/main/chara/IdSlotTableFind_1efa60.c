/* rgp:protos */
#define RGP_SELF_IdSlotTableFind_1efa60 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 IdSlotTableFind_1efa60(s32 p0, s32 p1)
{
    s32 l0;
    s32 t0;

    l0 = 0;
    while (l0 < 0x100) {
        t0 = *(s32 *)((u8 *)p0 + (l0 << 3) + 0x4);
        if (p1 == t0) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
