#include "types.h"

/* Head of a 5-member clone group (132 B each): GroupFindByKey_40eb80 / GroupFindByKey_411620 /
   Members differ in two tokens,
   the owner's list member and the element stride.

   Walk the owner's two-entry table and return the first entry whose slot
   passes the s16 key test.  The key is narrowed ONCE, outside the loop --
   retail's `dsll32/dsra32 ..,16` sits in the entry guard's likely slot, not at
   the call site, which is what a declared s16 parameter gives. */

typedef struct Ent40e {
    u8    pad000[0x94];
    void *slot;                 /* +0x94 */
} Ent40e;

typedef struct Own40e {
    u8      pad000[0xC];
    Ent40e *list;               /* +0x0C */
} Own40e;

extern s32 GroupEntryMatchesKey_3f41b0(void *slot, s16 key);

void *GroupFindByKey_40eb80(Own40e *o, s32 key)
{
    Ent40e *e;
    s32 i;
    s16 k;

    e = o->list;
    if (e == 0) {
        return 0;
    }
    k = (s16)key;
    for (i = 0; i < 2; i++, e = (Ent40e *)((u8 *)e + 0x3E0)) {
        if (e->slot != 0) {
            if (GroupEntryMatchesKey_3f41b0(e->slot, k) != 0) {
                return e;
            }
        }
    }
    return 0;
}
