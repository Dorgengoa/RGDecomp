#include "types.h"

extern void EffectEntryReleaseFull_2da420(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EffectEntriesReleaseByGroup_2de680(s32 p0, s32 p1)
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
                EffectEntryReleaseFull_2da420((p0 + (((l1 << 3) - l1) << 5)));
            }
        }
        l0 = ((l1 + 1) < 0x30);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
