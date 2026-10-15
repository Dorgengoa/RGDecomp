#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x59D0];
    f32 m59D0;
    u8 pad59D4[0x4];
    f32 m59D8;
    s32 m59DC;
};

f32 SunFlareFadeOut_1cf4d0(struct Obj0 *p0, s32 p1)
{
    f32 t0;

    p0->m59DC = p1;
    t0 = p0->m59D0;
    p0->m59D8 = -(t0 / ((f32)p1));
    return -(t0 / ((f32)p1));
}
