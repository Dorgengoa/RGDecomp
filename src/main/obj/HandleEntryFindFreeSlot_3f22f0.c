#include "types.h"

/* lane N4 family: HandleEntryFindFreeSlot_3f1500 / HandleEntryFindFreeSlot_3f22f0 (152 B each).
   Substitutions: the list member offset, the element stride and the
   halfword field offset. */

typedef struct {
    u8 pad00[0x10];
    s16 fV;
    u8 tail[0x16];
} Ent;

extern s32 D_004644A8[];
extern s32 D_004644A0[];

s32 HandleEntryFindFreeSlot_3f22f0(u8 *a)
{
    s64 mask;
    Ent *e;
    s32 n;
    s32 m;
    s32 i;
    s32 k;
    s32 v;

    e = *(Ent **)(a + 0x18);
    if (e == 0) {
        return 0;
    }
    n = D_004644A8[0];
    m = D_004644A0[0];
    mask = 0;
    for (i = 0; i < m; i++, e++) {
        v = e->fV;
        if (v >= 0 && v < n) {
            mask |= 1LL << v;
        }
    }
    for (k = 0; k < n; k++) {
        if ((mask & (1LL << k)) == 0) {
            return k;
        }
    }
    return -1;
}
