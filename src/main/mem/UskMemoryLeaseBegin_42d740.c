#include "types.h"

typedef struct Hdr {
    u32 size;
    u32 flags;
    void *owner;
    u32 pad;
} Hdr;

typedef struct Block {
    u8 pad0[0x10];
    Hdr h;
} Block;

typedef struct Heap {
    u8 pad0[0x10];
    Block *cur;
    u8 list[0x2C];
    u32 flags;
} Heap;

s32 BumpArenaInit_42e3d0(void *, void *, u32);
Block *DListGetTail_42ea50();
Block *DListGetPrev_42eb40(Block *);

static inline Block *findLargest(void)
{
    Block *b;
    Block *best;
    u32 bestsz;
    Hdr *h;

    bestsz = 0;
    best = NULL;
    for (b = DListGetTail_42ea50(); b != NULL; b = DListGetPrev_42eb40(b)) {
        h = &b->h;
        if (!(h->flags & 2) && bestsz < h->size) {
            bestsz = h->size;
            best = b;
        }
    }
    return best;
}

static inline Block *findFit(u32 size)
{
    Block *b;
    Hdr *h;

    for (b = DListGetTail_42ea50(); b != NULL; b = DListGetPrev_42eb40(b)) {
        h = &b->h;
        if (!(h->flags & 2) && h->size >= size) {
            return b;
        }
    }
    return NULL;
}

void *UskMemoryLeaseBegin_42d740(Heap *self, u32 n)
{
    Block *best;
    Hdr *h;
    void *p;
    u32 size;

    if (self->flags & 2) {
        return NULL;
    }
    if (n == 0) {
        best = findLargest();
    } else {
        size = (n + 0xF) & ~0xF;
        best = findFit(size);
    }
    if (best == NULL) {
        return NULL;
    }
    h = &best->h;
    size = h->size;
    if (size <= 0x20) {
        return NULL;
    }
    p = h + 1;
    if (BumpArenaInit_42e3d0(self->list, p, size - 0x20) == 0) {
        return NULL;
    }
    self->cur = best;
    self->flags |= 2;
    return p;
}
