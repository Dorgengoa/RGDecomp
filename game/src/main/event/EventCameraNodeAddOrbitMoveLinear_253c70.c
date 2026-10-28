/* rgp:protos */
#define RGP_SELF_EventCameraNodeAddOrbitMoveLinear_253c70 1
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
    u8 pad004[0xC];
    f32 m10;
    f32 m14;
    f32 m18;
    u8 pad01C[0x14];
    s32 m30;
};

struct Obj0 *EventCameraNodeAddOrbitMoveLinear_253c70(s32 p0, s32 p1, f32 fa0, f32 fa1, f32 fa2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_2543f0(p0);
    if (r0 != 0) {
        r0->m00 = 0x14;
        r0->m10 = fa0;
        r0->m14 = fa1;
        r0->m18 = fa2;
        r0->m30 = p1;
    }
    return r0;
}
