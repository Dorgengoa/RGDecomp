/* rgp:protos */
#define RGP_SELF_Find172430 1
#define RGP_SELF_Find2172430 1
#define RGP_SELF_MotionListFindSubEntry_172430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Ping-pong linked-list lookup: node (by id, -1 = first) in list, then node by id2 in the
 * node payload's sub-list (payload + 0x44). Plain C; formerly a hand transcription. */

typedef struct N172430 {
    struct N172430 *next;
    u8 pad04[0x8];
    s32 id;
    u8 data[0x10];
} N172430;

typedef struct L172430 {
    u8 pad00[0x4];
    N172430 *head;
} L172430;

static inline N172430 *Find172430(L172430 *l, s32 id)
{
    N172430 *n = l->head;
    if (id == -1) {
        if (n) return n;
        return 0;
    }
    while (n) {
        if (id == n->id) return n;
        n = n->next;
    }
    return 0;
}

static inline N172430 *Find2172430(L172430 *l, s32 id)
{
    N172430 *n = l->head;
    while (n) {
        if (id == n->id) return n;
        n = n->next;
    }
    return 0;
}

void *MotionListFindSubEntry_172430(void *list, s32 id, s32 id2)
{
    N172430 *n;
    u8 *d;

    n = Find172430((L172430 *)list, id);
    d = n ? n->data : 0;
    if (d == 0) return 0;
    n = Find2172430((L172430 *)(d + 0x44), id2);
    return n ? n->data : 0;
}
