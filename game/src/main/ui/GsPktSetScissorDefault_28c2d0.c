/* rgp:protos */
#define RGP_SELF_GsPktSetScissorDefault_28c2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047EB50;

void GsPktSetScissorDefault_28c2d0(s32 p0, s32 p1, s32 p2)
{
    GsPktSetScissor_28c2e0(p0, p1, p2, &D_0047EB50);
}
