/* rgp:protos */
#define RGP_SELF_NpcObjFindFreeSlotId_2fb540 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off
#pragma opt_repositioncode off
typedef struct E {
    u16 flags;
    u8 pad[0xC2];
    s16 xC4;
    u8 pad2[0x1A];
} E;
typedef struct L {
    s16 start;
    s16 count;
    E *list;
    s16 n;
} L;

s32 NpcObjFindFreeSlotId_2fb540(L *arg0)
{
    s32 n;
    s32 v;
    s32 end;
    E *p;
    s32 found;
    s32 i;

    if (arg0->list == NULL) {
        return -1;
    }
    v = arg0->start;
    end = v + arg0->count;
    for (; v < end; v++) {
        n = arg0->n;
        found = 0;
        p = arg0->list;
        for (i = 0; i < n; i++, p++) {
            if ((p->flags & 1) && p->xC4 == v) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return v;
        }
    }
    return -1;
}
