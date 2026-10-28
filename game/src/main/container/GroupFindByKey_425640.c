/* rgp:protos */
#define RGP_SELF_GroupFindByKey_425640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    u8 pad0[0x94];
    s32 f94;
    u8 pad2[0x98 - (0x94 + 4)];
} Ent;

typedef struct Owner {
    u8 pad0[0xC];
    Ent *list;
} Owner;

/*rgp*/

s32 GroupFindByKey_425640(Owner *o, s32 a1)
{
    Ent *p;
    s32 i;
    s32 x;

    p = o->list;
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++, p++) {
        x = p->f94;
        if (x != 0 && GroupEntryMatchesKey_3f41b0(x, a1) != 0) {
            return (s32)p;
        }
    }
    return 0;
}
