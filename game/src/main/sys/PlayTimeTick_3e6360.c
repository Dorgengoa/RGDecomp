/* rgp:protos */
#define RGP_SELF_PlayTimeTick_3e6360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 PlayTimeTick_3e6360(struct Obj0 *p0, f32 fa0)
{
    s32 t0;
    s32 rv2;
    unsigned long long r0;
    s32 r1;

    t0 = p0->m0C;
    rv2 = 1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        r0 = PlayTimeAdvance_3d61a0(t0, fa0);
        r1 = (EventFireIntervalTriggers_3e0220((long long)(r0)), (s32)0);
        rv2 = 1;
    }
    return rv2;
}
