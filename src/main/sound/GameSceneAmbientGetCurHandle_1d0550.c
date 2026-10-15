#include "types.h"

extern s32 GameSceneSoundSlotGet_1d0de0(void *, s32);
extern s32 SoundSlotGetHandle_1d2150(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB4A8];
    s8 mB4A8;
};

s32 GameSceneAmbientGetCurHandle_1d0550(struct Obj0 *p0)
{
    s8 t0;
    s32 r0;
    s32 r1;

    t0 = p0->mB4A8;
    r0 = GameSceneSoundSlotGet_1d0de0(p0, t0);
    if (r0 != 0) {
        r1 = SoundSlotGetHandle_1d2150(r0);
        return r1;
    }
    return -1;
}
