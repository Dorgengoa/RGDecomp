#include "types.h"

extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    u16 m1C;
};

void UiSpriteApplyDrawFlags_293240(s32 p0, struct Obj0 *p1)
{
    u16 t0;
    u16 t1;

    t0 = p1->m1C;
    if ((t0 & 1) != 0) {
        GsPktSetBlendMode_13e4f0(p0, 2);
    }
    t1 = p1->m1C;
    if ((t1 & 2) != 0) {
        GsPktSetTexFilter_13e3d0(p0, 1);
    } else {
        GsPktSetTexFilter_13e3d0(p0, 0);
    }
}
