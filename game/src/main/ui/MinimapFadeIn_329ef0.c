/* rgp:protos */
#define RGP_SELF_MinimapFadeIn_329ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 MinimapFadeIn_329ef0(s32 p0, f32 fa0)
{
    f32 r0;
    f32 r1;
    f32 r2;

    r0 = (MinimapSetFadeDuration_32a170(p0, fa0), (f32)0.0f);
    r1 = MinimapGetDrawAlpha_32a180(p0);
    r2 = (MinimapSetFadeMode_329de0(p0, 1, r1), (f32)0.0f);
    return r2;
}
