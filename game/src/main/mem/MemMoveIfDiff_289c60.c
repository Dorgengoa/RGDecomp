/* rgp:protos */
#define RGP_SELF_MemMoveIfDiff_289c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memmove(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MemMoveIfDiff_289c60(s32 p0, s32 p1, s32 p2)
{
    if (p2 != p0) {
        memmove(p2, p0, p1);
    }
    return 0;
}
