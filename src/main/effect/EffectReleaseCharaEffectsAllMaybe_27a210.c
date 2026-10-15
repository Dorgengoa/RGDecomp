#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectReleaseNodesByKey_2e1250(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EffectReleaseCharaEffectsAllMaybe_27a210(void)
{
    s32 r0;
    s32 l1;

    r0 = GetEffectMgr_2d9040();
    l1 = 0;
    do {
        EffectReleaseNodesByKey_2e1250(r0, l1, 0xFA0);
        l1 = (l1 + 1);
    } while (l1 < 0xC);
}
