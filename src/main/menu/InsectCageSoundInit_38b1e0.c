#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlot6IsLoadIdle_1d0660(s32);
extern s32 GameSceneSoundSlot6GetHandle_1d0780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004832A0;

s32 InsectCageSoundInit_38b1e0(void)
{
    s32 r0;
    s32 r1;
    s32 rv4;
    s32 r2;
    s32 r3;

    r0 = GetCurrentScene_1f5be0();
    r1 = GameSceneSoundSlot6IsLoadIdle_1d0660(r0);
    rv4 = 1;
    if ((r1 & 0xFF) == 0) {
        rv4 = 0;
    } else {
        r2 = GetCurrentScene_1f5be0();
        r3 = GameSceneSoundSlot6GetHandle_1d0780(r2);
        D_004832A0 = r3;
        rv4 = 1;
    }
    return rv4;
}
