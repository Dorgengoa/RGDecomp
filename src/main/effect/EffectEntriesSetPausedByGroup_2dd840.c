#include "types.h"

extern void EffectEntrySetPaused_2d95c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EffectEntriesSetPausedByGroup_2dd840(s32 p0, s32 p1, s32 p2)
{
    s32 l0;
    s32 l1;
    s16 t0;
    s32 t1;

    l1 = 0;
    do {
        t0 = *(s16 *)((u8 *)p0 + (((l1 << 3) - l1) << 5) + 0xB4);
        if (t0 != 0) {
            t1 = *(s32 *)((u8 *)p0 + (((l1 << 3) - l1) << 5) + 0x10);
            if (t1 == p1) {
                EffectEntrySetPaused_2d95c0((p0 + (((l1 << 3) - l1) << 5)), p2);
            }
        }
        l0 = ((l1 + 1) < 0x30);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
