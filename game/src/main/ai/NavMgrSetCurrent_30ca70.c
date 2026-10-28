/* rgp:protos */
#define RGP_SELF_NavMgrSetCurrent_30ca70 1
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
    s32 m28;
};

s32 NavMgrSetCurrent_30ca70(struct Obj0 *p0, s32 p1)
{
    s32 r0;

    if (p1 == 0) {
        p0->m28 = 0;
        return;
    }
    r0 = NavGraphGetId_310e90(p1);
    p0->m28 = r0;
    return r0;
}
