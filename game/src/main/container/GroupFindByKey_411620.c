/* rgp:protos */
#define RGP_SELF_GroupFindByKey_411620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 5-clone group headed by GroupFindByKey_40eb80 (132 B each).
   This member differs from the head in the owner's list member and the
   element stride.  The reading is written up in GroupFindByKey_40eb80.c. */

typedef struct Ent40e {
    u8    pad000[0x94];
    void *slot;                 /* +0x94 */
} Ent40e;

typedef struct Own40e {
    u8      pad000[0x50];
    Ent40e *list;               /* +0x50 */
} Own40e;

/*rgp*/

void *GroupFindByKey_411620(Own40e *o, s32 key)
{
    Ent40e *e;
    s32 i;
    s16 k;

    e = o->list;
    if (e == 0) {
        return 0;
    }
    k = (s16)key;
    for (i = 0; i < 2; i++, e = (Ent40e *)((u8 *)e + 0x2F8)) {
        if (e->slot != 0) {
            if (GroupEntryMatchesKey_3f41b0(e->slot, k) != 0) {
                return e;
            }
        }
    }
    return 0;
}
