#include "types.h"

extern f32 RandFloat_13c010(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

void MenuObjRandDelayMaybe_385fa0(struct Obj0 *p0)
{
    f32 r0;
    s32 t0;

    r0 = RandFloat_13c010();
    t0 = ((s32)(108.0f + (20.0f * r0)));
    p0->m18 = t0;
}
