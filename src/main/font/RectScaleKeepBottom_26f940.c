#include "types.h"

extern void RectScaleCentered_26f9b0(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void RectScaleKeepBottom_26f940(struct Obj0 *p0, f32 fa0)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    t0 = p0->m00;
    t1 = p0->m04;
    t2 = p0->m08;
    t3 = p0->m0C;
    RectScaleCentered_26f9b0(p0, fa0);
    p0->m00 = t0;
    t4 = p0->m0C;
    p0->m04 = ((t1 + t3) - t4);
    p0->m08 = t2;
}
