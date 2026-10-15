#include "types.h"

extern s32 EffectTimedSlotStart_2d4c60(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826A4;
extern u8 D_004E39D0[];

s32 EffectTimedSlotSpawn_2d8e40(s32 p0)
{
    s32 t0;
    s32 r0;
    s32 t1;

    t0 = D_004826A4;
    r0 = EffectTimedSlotStart_2d4c60((D_004E39D0 + (t0 << 4)), p0);
    if (r0 != 0) {
        t1 = D_004826A4;
        D_004826A4 = (t1 + 1);
        if ((t1 + 1) >= 0xC) {
            D_004826A4 = 0;
        }
    }
    return r0;
}
