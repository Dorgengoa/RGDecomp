/* Linked-list lookup (id, -1 = first node); returns payload state field == 4. Plain C; formerly a hand transcription. */
#include "types.h"

typedef struct N171d90 {
    struct N171d90 *next;
    u8 pad04[0x8];
    s32 id;
    u8 data[0x10];
} N171d90;

typedef struct L171d90 {
    u8 pad00[0x4];
    N171d90 *head;
} L171d90;

static inline N171d90 *Find171d90(L171d90 *l, s32 id)
{
    N171d90 *n = l->head;
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

s32 MotionListIsFinished_171d90(void *list, s32 id)
{
    N171d90 *n;
    u8 *d;

    n = Find171d90((L171d90 *)list, id);
    d = n ? n->data : 0;
    if (d == 0) return 0;
    return *(s32 *)(d + 0x24) == 4;
}
