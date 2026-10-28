/* rgp:protos */
#define RGP_SELF_EventSubNodeAddPlaySound_250e30 1
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
    s32 m20;
    s32 m24;
};

struct Obj0 *EventSubNodeAddPlaySound_250e30(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251c30(p0);
    if (r0 != 0) {
        r0->m00 = 0x25;
        r0->m20 = p1;
        r0->m24 = p2;
    }
    return r0;
}
