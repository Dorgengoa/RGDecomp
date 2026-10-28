/* rgp:protos */
#define RGP_SELF_PartyGetSavedMemberLeaderDist_3caf40 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 PartyGetSavedMemberLeaderDist_3caf40(s32 p0, s32 p1)
{
    f32 t0;

    if (p1 < 0 || p1 >= 3) {
        return 0.0f;
    }
    t0 = *(f32 *)((u8 *)(p1 << 2) + p0 + 0xDC);
    return t0;
}
