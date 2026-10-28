/* rgp:protos */
#define RGP_SELF_EffectGetParamFloatVec_2e0240 1
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
    s16 m00;
};

void EffectGetParamFloatVec_2e0240(s32 p0, struct Obj0 *p1, s32 p2, s32 p3)
{
    s16 t0;

    t0 = p1->m00;
    if (t0 != 2) {
        if (t0 != 3) {
            return;
        }
    }
    EffectEntriesGetParamFloatVec_2dda40((p0 + 0x1674), p1, p2, p3);
}
