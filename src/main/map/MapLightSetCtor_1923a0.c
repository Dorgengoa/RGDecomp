#include "types.h"

extern s32 memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1B8];
    s32 m1B8;
    s32 m1BC;
};

struct Obj0 *MapLightSetCtor_1923a0(struct Obj0 *p0)
{
    s32 r0;

    p0->m1BC = 0;
    p0->m1B8 = 0;
    r0 = memset(p0, 0, 0x1D0);
    return p0;
}
