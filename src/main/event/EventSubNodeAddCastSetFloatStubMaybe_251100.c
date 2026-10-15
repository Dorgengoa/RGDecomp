#include "types.h"

extern void * PoolAllocAppendNode_251db0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x1C];
    f32 m20;
};

struct Obj0 *EventSubNodeAddCastSetFloatStubMaybe_251100(s32 p0, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251db0(p0);
    if (r0 != 0) {
        r0->m00 = 0x1B;
        r0->m20 = fa0;
    }
    return r0;
}
