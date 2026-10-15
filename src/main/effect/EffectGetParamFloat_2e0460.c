#include "types.h"

extern void EffectEntriesGetParamFloat_2ddc80(s32, void *, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

void EffectGetParamFloat_2e0460(s32 p0, struct Obj0 *p1, s32 p2, s32 p3)
{
    s16 t0;

    t0 = p1->m00;
    if (t0 != 2) {
        if (t0 != 3) {
            return;
        }
    }
    EffectEntriesGetParamFloat_2ddc80((p0 + 0x1674), p1, p2, p3, t0);
}
