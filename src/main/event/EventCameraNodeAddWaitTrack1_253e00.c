#include "types.h"

extern void * PoolAllocAppendNode_2543f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x2C];
    s32 m30;
};

struct Obj0 *EventCameraNodeAddWaitTrack1_253e00(s32 p0, s32 p1)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_2543f0(p0);
    if (r0 != 0) {
        r0->m00 = 0xF;
        r0->m30 = p1;
    }
    return r0;
}
