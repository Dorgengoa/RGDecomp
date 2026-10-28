/* rgp:protos */
#define RGP_SELF_BlockHeapCarveTop_1c2460 1
#define RGP_SELF_FindFree 1
#define RGP_SELF_IsFree 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
typedef struct Blk {
    u32 start;
    u32 end;
    u32 top;
    struct Blk *next;
    struct Blk *prev;
} Blk;

typedef struct {
    s32 count;
    Blk *pool;
    u8 pad8[0x24 - 0x8];
    Blk *list;
} Heap;

static inline u8 IsFree(Blk *b) {
    return !b->start;
}
static inline Blk *FindFree(Heap *h) {
    s32 i;
    if (h->pool == NULL) {
        return NULL;
    }
    for (i = 0; i < h->count; i++) {
        if (IsFree(&h->pool[i])) {
            return &h->pool[i];
        }
    }
    return NULL;
}

Blk *BlockHeapCarveTop_1c2460(Heap *arg0, u32 arg1, u32 arg2)
{
    Blk *p;
    Blk *b;
    s32 i;
    u32 top;
    u32 rem;
    Blk *n;

    p = arg0->list;
    if (p == NULL) {
        return NULL;
    }
    while (p->next != NULL) {
        p = p->next;
    }
    b = FindFree(arg0);
    if (b == NULL) {
        return NULL;
    }
    b->prev = NULL;
    b->next = NULL;
    b->start = 0;
    b->top = 0;
    b->end = 0;
    while (p != NULL) {
        top = p->top;
        rem = top % arg2;
        if (rem != 0) {
            top -= rem;
        }
        if (top >= p->end && top - p->end >= arg1) {
            b->start = top - arg1;
            b->end = top;
            b->top = p->top;
            p->top = b->start;
            n = p->next;
            b->next = n;
            if (n != NULL) {
                n->prev = b;
            }
            p->next = b;
            b->prev = p;
            return b;
        }
        p = p->prev;
    }
    return NULL;
}
