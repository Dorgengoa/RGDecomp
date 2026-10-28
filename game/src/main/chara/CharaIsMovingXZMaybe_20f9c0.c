/* rgp:protos */
#define RGP_SELF_CharaIsMovingXZMaybe_20f9c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047DB5C;

s32 CharaIsMovingXZMaybe_20f9c0(s32 p0)
{
    u128 v20;
    f32 r1;
    f32 t0;
    s32 rv2;

    CharaGetPlatformVelMaybe_2384e0(p0, &v20);
    r1 = VecDistSqXZ_1cb390((p0 + 0x80), &v20);
    t0 = D_0047DB5C;
    rv2 = 1;
    if (r1 < t0) {
        rv2 = 0;
    }
    return rv2;
}
