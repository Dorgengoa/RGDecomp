#include "types.h"

extern void * GetCurrentScene_1f5be0(void);
extern void ObjRecGetLiveObject_1c3bc0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
};

void GetCurrentSceneCamera_389d40(void)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = GetCurrentScene_1f5be0();
    t0 = r0->m4344;
    ObjRecGetLiveObject_1c3bc0(r0, t0);
}
