/* rgp:protos */
#define RGP_SELF_XformInitIdentity_1a86a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 XformInitIdentity_1a86a0(s32 p0)
{
    s32 r1;

    MtxIdentity_13d2e0(p0);
    r1 = (VecSetOnes4_13e170((p0 + 0x40)), (s32)0);
    return p0;
}
