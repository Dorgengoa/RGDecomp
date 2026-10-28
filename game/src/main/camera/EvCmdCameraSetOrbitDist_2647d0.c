/* rgp:protos */
#define RGP_SELF_EvCmdCameraSetOrbitDist_2647d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;

s32 EvCmdCameraSetOrbitDist_2647d0(s32 p0)
{
    f32 r0;
    s32 t0;
    s32 r1;

    r0 = TaggedGetFloat_26a280(p0);
    t0 = D_00482060;
    r1 = ((s32)EventCameraNodeAddOrbitSetDist_253d40(t0, r0));
    return 1;
}
