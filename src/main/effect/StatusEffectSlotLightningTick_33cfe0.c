#include "types.h"

/* Countdown timer on a float field; when it runs out fire the callback and
   reload it with 30.0f.  The reload store is in the bc1f delay slot, i.e. it
   happens unconditionally BEFORE the test, so the decrement is a separate
   statement from the compare. */

struct S {
    u8 pad000[0x14];
    s16 m14;
    u8 pad016[0x7A];
    f32 m90;
};

extern u8 D_004E6110[];
extern void LightningMgrAddObjEmitter_2d6cb0(u8 *, s32, s32);

void StatusEffectSlotLightningTick_33cfe0(struct S *p0)
{
    p0->m90 -= 1.0f;
    if (p0->m90 <= 0.0f) {
        LightningMgrAddObjEmitter_2d6cb0(D_004E6110, p0->m14, 0x1E);
        p0->m90 = 30.0f;
    }
}
