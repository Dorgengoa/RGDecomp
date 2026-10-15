#include "types.h"

extern void * UiFindWidget_290460(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C];
    f32 m4C;
};

f32 UiGetWidgetAlphaTarget_290660(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    f32 t0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        t0 = r0->m4C;
        return t0;
    }
    return 1.0f;
}
