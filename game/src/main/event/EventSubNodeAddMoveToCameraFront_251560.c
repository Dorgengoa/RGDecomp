/* rgp:protos */
#define RGP_SELF_EventSubNodeAddMoveToCameraFront_251560 1
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
    s32 m00;
    u8 pad004[0x1C];
    f32 m20;
    s32 m24;
};

struct Obj0 *EventSubNodeAddMoveToCameraFront_251560(s32 p0, s32 p1, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e70(p0);
    if (r0 != 0) {
        r0->m00 = 0xC;
        r0->m20 = fa0;
        r0->m24 = p1;
    }
    return r0;
}
