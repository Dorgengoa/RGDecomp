/* rgp:protos */
#define RGP_SELF_PhaseAdvanceWrapPi_28b630 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D1FC;

struct Obj0;

struct Obj0 {
    f32 m00;
};

f32 PhaseAdvanceWrapPi_28b630(struct Obj0 *p0, f32 fa0)
{
    f32 t0;
    f32 t1;

    t0 = p0->m00;
    p0->m00 = (t0 + fa0);
    if ((t0 + fa0) > 0.0f) {
        t1 = D_0047D1FC;
        p0->m00 = ((t0 + fa0) - t1);
        return ((t0 + fa0) - t1);
    }
    return 0.0f;
}
