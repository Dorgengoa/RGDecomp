#include "types.h"

/* Linked-list lookup (id, -1 = first node) -> node payload n+0x10; same idiom as MotionListFindSubEntry_172430.
 * Plain C; formerly a hand-written assembly transcription. */

typedef struct N1721 {
    struct N1721 *next;
    u8 pad04[0x8];
    s32 id;
    u8 data[0x10];
} N1721;

typedef struct L1721 {
    u8 pad00[0x4];
    N1721 *head;
} L1721;

static inline N1721 *Find1721(L1721 *l, s32 id)
{
    N1721 *n = l->head;
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
void MotionListSetBlendSpeedById_172170(void *list, s32 id, f32 fval)
{
    N1721 *n;
    u8 *d;

    n = Find1721((L1721 *)list, id);
    d = n ? n->data : 0;
    if (d) {
        *(f32 *)(d + 0x38) = fval;
    }
}
