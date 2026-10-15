#include "types.h"

extern void GameSceneSoundSetVolumeNow_1d0400(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB4AC];
    f32 mB4AC;
    f32 mB4B0;
    f32 mB4B4;
};

void GameSceneSoundFadeVolume_1d0370(struct Obj0 *p0, s32 p1, f32 fa0)
{
    f32 rv1;
    f32 rv2;
    f32 t0;

    if (p1 <= 0) {
        GameSceneSoundSetVolumeNow_1d0400(p0, fa0);
        return;
    }
    rv1 = fa0;
    if (fa0 < 0.0f) {
        rv1 = 0.0f;
    }
    rv2 = rv1;
    if (rv1 > 1.0f) {
        rv2 = 1.0f;
    }
    p0->mB4B0 = rv2;
    t0 = p0->mB4AC;
    p0->mB4B4 = ((rv2 - t0) / ((f32)p1));
}
