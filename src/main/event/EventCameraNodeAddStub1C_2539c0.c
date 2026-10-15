#include "types.h"

extern void * PoolAllocAppendNode_254390(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

struct Obj0 *EventCameraNodeAddStub1C_2539c0(s32 p0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_254390(p0);
    if (r0 != 0) {
        r0->m00 = 0x1C;
    }
    return r0;
}
