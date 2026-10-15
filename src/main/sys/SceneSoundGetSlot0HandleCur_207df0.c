#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlot0GetHandle_1d07c0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SceneSoundGetSlot0HandleCur_207df0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetCurrentScene_1f5be0();
    if (r0 != 0) {
        r1 = GameSceneSoundSlot0GetHandle_1d07c0(r0);
        return r1;
    }
    return -1;
}
