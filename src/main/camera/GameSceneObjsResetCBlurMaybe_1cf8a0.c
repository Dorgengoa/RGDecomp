#include "types.h"

extern void GameSceneObjSetCBlurMaybe_1cf900(s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameSceneObjsResetCBlurMaybe_1cf8a0(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        GameSceneObjSetCBlurMaybe_1cf900(p0, l1, 0, 1.0f);
        l0 = ((l1 + 1) < 0xE0);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
