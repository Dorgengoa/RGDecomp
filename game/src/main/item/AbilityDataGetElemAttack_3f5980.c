/* rgp:protos */
#define RGP_SELF_AbilityDataGetElemAttack_3f5980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AbilityDataGetElemAttack_3f5980(s32 p0)
{
    s32 r0;

    r0 = AbilityDataGetKind0Rec_3f5db0(p0);
    if (r0 != 0) {
        return (r0 + 0x18);
    }
    return 0;
}
