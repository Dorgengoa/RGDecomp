#include "types.h"

/* Member of the 7-member clone group (76 B each).  Bounds-checked dispatch into a
   0x30-entry table of 224-byte records; retail strength-reduces the stride to
   `sll 3 / subu / sll 5` = (i*8 - i)*32.  Both guards share ONE `return 1`,
   which is what puts the second compare in a GPR and duplicates the `$2 = 1`
   into the `bltzl` delay slot (session 24 lever 1). */

typedef struct Idx {
    u8  pad000[0x8];
    s32 m8;
} Idx;

extern void EffectEntryNodeGetPos_2d97b0(void *rec);

s32 EffectEntryGetPosByIdx_2de080(void *base, Idx *p)
{
    s32 i = p->m8;

    if (i < 0 || i >= 0x30) {
        return 1;
    }
    EffectEntryNodeGetPos_2d97b0((u8 *)base + i * 224);
    return 0;
}
