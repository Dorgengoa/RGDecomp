#include "types.h"

/* MAIN PartyLoadSlotSet_2f57b0 -- collects up to 0x40 entries into a stack array
   and appends their +0x8 word to the object's own table.
   `a` and `b` are s32 parameters: they reach CharaCollectEquipEffectRefsMaybe_2f5850 with NO
   widening, so the `sh` at the top is the narrowing, not their type.
   `p->m04` is re-read for the index and again for the increment --
   the store through the table may alias it. */

typedef struct Hdr57b0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    s32 arr[1];         /* 0x08 */
} Hdr57b0;

typedef struct Ent57b0 {
    u8  pad00[8];
    s32 m08;
} Ent57b0;

extern s32 CharaCollectEquipEffectRefsMaybe_2f5850(s32, Ent57b0 **, s32);

void PartyLoadSlotSet_2f57b0(Hdr57b0 *p, s32 a, s32 b)
{
    Ent57b0 *buf[0x40];
    s32 n;
    s32 i;

    p->m00 = a;
    p->m02 = b;
    p->m04 = 0;
    p->m06 = 0;
    n = CharaCollectEquipEffectRefsMaybe_2f5850(a, buf, 0x40);
    for (i = 0; i < n; i++) {
        p->arr[p->m04] = buf[i]->m08;
        p->m04 = p->m04 + 1;
    }
}
