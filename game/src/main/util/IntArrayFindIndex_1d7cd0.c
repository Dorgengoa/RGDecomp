/* rgp:protos */
#define RGP_SELF_IntArrayFindIndex_1d7cd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 IntArrayFindIndex_1d7cd0(s32 p0, s32 p1, s32 p2)
{
    s32 l0;
    s32 t0;

    l0 = 0;
    while (l0 < p2) {
        t0 = *(s32 *)((u8 *)p1 + (l0 << 2));
        if (p0 == t0) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
