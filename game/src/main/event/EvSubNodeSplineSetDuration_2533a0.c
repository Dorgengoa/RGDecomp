/* rgp:protos */
#define RGP_SELF_EvSubNodeSplineSetDuration_2533a0 1
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
    u8 pad000[0x20];
    s32 m20;
};

s32 EvSubNodeSplineSetDuration_2533a0(struct Obj0 *p0, s32 p1)
{
    s32 r;

    r = (SplinePathSetDuration_256940((p1 + 0x140), p0->m20), (s32)0);
    return 0;
}
