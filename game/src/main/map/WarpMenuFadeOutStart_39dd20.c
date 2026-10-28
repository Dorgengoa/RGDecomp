/* rgp:protos */
#define RGP_SELF_WarpMenuFadeOutStart_39dd20 1
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
    f32 m2C;
};

f32 WarpMenuFadeOutStart_39dd20(struct Obj0 *p0, f32 fa0)
{
    f32 t0;

    if (fa0 <= 0.0f) {
        WarpMenuFadeReset_39dd10(p0);
        return;
    }
    t0 = p0->m28;
    p0->m2C = (-t0 / fa0);
    return (-t0 / fa0);
}
