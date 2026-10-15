#include "types.h"

typedef struct Ent {
    u8 pad0[0x94];
    s32 f94;
    u8 pad2[0xA8 - 0x98];
} Ent;

typedef struct Owner {
    u8 pad0[0xC];
    Ent *list;
} Owner;

extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);

s32 GroupFindByKey_4022b0(Owner *o, s32 a1)
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
