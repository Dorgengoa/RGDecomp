#include "types.h"
#pragma opt_loop_invariants off
typedef struct Ent { s16 id; s16 x; } Ent;
typedef struct List {
    s16 count;
    Ent ents[16];
    u8 pad42[2];
    bool b0 : 1;
} List;

typedef struct Sub { u8 pad0[0x2C]; s16 x2C; } Sub;
typedef struct Mgr { u8 pad0[0xC]; Sub *sub; } Mgr;
extern Mgr *D_004837BC;

extern "C" s32 CharaEventLogKeyRemove_3a6760(List *l, s32 id)
{
    bool found;
    Ent *e;
    s32 i;
    s32 n;

    if (D_004837BC->sub->x2C != 1) {
        return 0;
    }
    found = false;
    n = l->count;
    e = l->ents;
    for (i = 0; i < n; i++, e++) {
        if (e->id == id) {
            while (i < l->count - 1) {
                i++;
                e->id = e[1].id;
                e++;
            }
            e->id = -1;
            found = true;
            l->count--;
            break;
        }
    }
    if (!found) {
        return 0;
    }
    if (l->count == 0) {
        l->b0 = true;
    }
    return 1;
}
