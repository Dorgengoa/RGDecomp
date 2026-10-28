/* rgp:protos */
#define RGP_SELF_EffCurveApplyColorG_1a1970 1
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
    f32 m00;
    u8 pad004[0x90];
    f32 m94;
};

f32 EffCurveApplyColorG_1a1970(s32 p0, struct Obj0 *p1)
{
    f32 t0;
    f32 r0;
    f32 t1;

    t0 = p1->m00;
    r0 = EffCurveEvaluate_197530(p0, t0);
    t1 = p1->m94;
    p1->m94 = (t1 * r0);
    return (t1 * r0);
}
