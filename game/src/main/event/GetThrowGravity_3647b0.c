/* rgp:protos */
#define RGP_SELF_GetThrowGravity_3647b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D26C;

f32 GetThrowGravity_3647b0(void)
{
    f32 r0;
    f32 t0;

    r0 = GetScaledGravity_23b170();
    t0 = D_0047D26C;
    return (t0 * r0);
}
