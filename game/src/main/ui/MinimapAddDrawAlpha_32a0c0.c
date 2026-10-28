/* rgp:protos */
#define RGP_SELF_MinimapAddDrawAlpha_32a0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 MinimapAddDrawAlpha_32a0c0(s32 p0, f32 fa0)
{
    f32 r0;

    r0 = MinimapGetDrawAlpha_32a180(p0);
    return (fa0 + r0);
}
