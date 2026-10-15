#include "types.h"

extern void * PoolAllocAppendNode_2542d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x2C];
    s32 m30;
    f32 m34;
    s32 m38;
};

struct Obj0 *EventCameraNodeAddPlaceObjOnView_2537a0(s32 p0, s32 p1, s32 p2, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_2542d0(p0);
    if (r0 != 0) {
        r0->m00 = 0x23;
        r0->m30 = p1;
        r0->m34 = fa0;
        r0->m38 = p2;
    }
    return r0;
}
