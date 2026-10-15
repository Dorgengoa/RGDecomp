#include "types.h"

extern void EffectEntryNodeGetParamIntVec_2d9a80(void *, void *, void *, void *);

/* Sweep the 0x30-entry, 0xE0-stride table at p0 and hand every entry whose
   halfword id at +0xE equals a1's word at +8 to EffectEntryNodeGetParamIntVec_2d9a80.
   No `b` to the test at the top => the loop is a do/while, not a while. */

void EffectEntriesGetParamIntVec_2dd9b0(void *p0, void *a1, void *a2, void *a3)
{
    s32 i;
    u8 *e;

    i = 0;
    do {
        e = (u8 *)p0 + i * 0xE0;
        if (*(s16 *)(e + 0xE) == *(s32 *)((u8 *)a1 + 8)) {
            EffectEntryNodeGetParamIntVec_2d9a80(e, a1, a2, a3);
        }
        i++;
    } while (i < 0x30);
}
