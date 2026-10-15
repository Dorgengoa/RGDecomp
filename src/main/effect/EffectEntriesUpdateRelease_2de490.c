#include "types.h"

/* Known-positive sibling shape of EffectEntriesDraw_2deac0 (byte-identical, in cunits). */

extern void EffectEntryUpdateRelease_2d95f0(s32, s32);

void EffectEntriesUpdateRelease_2de490(s32 p0)
{
    s32 l0;
    s32 l1;
    s16 t0;

    l1 = 0;
    do {
        t0 = *(s16 *)((u8 *)p0 + (((l1 << 3) - l1) << 5) + 0xB4);
        if (t0 == 3) {
            EffectEntryUpdateRelease_2d95f0((p0 + (((l1 << 3) - l1) << 5)), t0);
        }
        l0 = ((l1 + 1) < 0x30);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
