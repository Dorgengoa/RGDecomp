#include "types.h"

extern void ObjRecGetLiveObject_1c3bc0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00481F78;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
};

void EventSceneGetCamera_265980(void)
{
    struct Obj0 * t0;
    s32 t1;

    t0 = D_00481F78;
    t1 = D_00481F78->m4344;
    ObjRecGetLiveObject_1c3bc0(t0, t1);
}
