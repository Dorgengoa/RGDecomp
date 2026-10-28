/* rg-override: replaces game/src/main/mem/UskMemoryLeaseBegin_42d740.c sha256 fac539e28534fe21e93d1f10ea508939266d70837635a65f5d34378bd478d839
 * why: the inlined search helpers walk the heap's block list (retail $a0 = the heap, untouched), not the list at address `size` (protos passed the helper's own parameter) */
/* rgp:protos */
#define RGP_SELF_UskMemoryLeaseBegin_42d740 1
#define RGP_SELF_findFit 1
#define RGP_SELF_findLargest 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/

static inline Block *findLargest(void *rgp_a0)
{
    Block *b;
    Block *best;
    u32 bestsz;
    Hdr *h;

    bestsz = 0;
    best = NULL;
    for (b = ((Block *)DListGetTail_42ea50((void *)rgp_a0)); b != NULL; b = ((Block *)DListGetPrev_42eb40(b))) {
        h = &b->h;
        if (!(h->flags & 2) && bestsz < h->size) {
            bestsz = h->size;
            best = b;
        }
    }
    return best;
}

static inline Block *findFit(void *heap, u32 size)
{
    Block *b;
    Hdr *h;

    for (b = ((Block *)DListGetTail_42ea50(heap)); b != NULL; b = ((Block *)DListGetPrev_42eb40(b))) {
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
        best = findLargest((void *)self);
    } else {
        size = (n + 0xF) & ~0xF;
        best = findFit((void *)self, size);
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
