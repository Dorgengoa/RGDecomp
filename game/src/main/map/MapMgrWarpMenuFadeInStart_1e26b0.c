/* rgp:protos */
#define RGP_SELF_MapMgrWarpMenuFadeInStart_1e26b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapMgrWarpMenuFadeInStart_1e26b0(s32 p0, s32 p1)
{
    WarpMenuFadeInStart_39dd70((p0 + 0x18B0), ((f32)p1));
}
