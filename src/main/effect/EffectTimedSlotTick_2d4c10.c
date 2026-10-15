#include "types.h"

extern void EffectTimedSlotReset_2d4cf0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
    f32 m04;
};

void EffectTimedSlotTick_2d4c10(struct Obj0 *p0, f32 fa0)
{
    s16 t0;
    f32 t1;

    t0 = p0->m02;
    if (t0 != 0) {
        t1 = p0->m04;
        p0->m04 = (t1 + fa0);
        if ((t1 + fa0) > 15.0f) {
            EffectTimedSlotReset_2d4cf0(p0);
            return;
        }
        return;
    }
}
