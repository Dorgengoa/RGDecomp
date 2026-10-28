/* rgp:protos */
#define RGP_SELF_AbilityDataGetGaugeDrainRate_3f5c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x28];
    f32 m28;
};

f32 AbilityDataGetGaugeDrainRate_3f5c40(s32 p0)
{
    struct Obj0 *r0;
    f32 t0;

    r0 = AbilityDataGetKind0Rec_3f5db0(p0);
    if (r0 != 0) {
        t0 = r0->m28;
        return t0;
    }
    return 0.0f;
}
