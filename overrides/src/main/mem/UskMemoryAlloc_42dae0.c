/* rg-override: replaces game/src/main/mem/UskMemoryAlloc_42dae0.c sha256 bc48f1ae71a9ba156c653dd8717fd38b2a41f5f8d932045599317e8c18d602a1
 * why: the inlined search helpers walk the heap's block list (retail $a0 = the heap, untouched), not the list at address `size` (protos passed the helper's own parameter) */
/* rgp:protos */
#define RGP_SELF_UskMemoryAlloc_42dae0 1
#define RGP_SELF_findA 1
#define RGP_SELF_findB 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Hdr {
    u32 size;
    s32 flags;
} Hdr;

typedef struct Blk {
    u8 pad0[0x10];
    Hdr h;
} Blk;


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Blk *findA(void *heap, u32 sz)
{
    Blk *p;
    Hdr *h;

    for (p = ((Blk *)DListGetTail_42ea50(heap)); p != NULL; p = ((Blk *)DListGetPrev_42eb40(p))) {
        h = &p->h;
        if (!(h->flags & 2) && h->size >= sz) {
            return p;
        }
    }
    return NULL;
}

static inline Blk *findB(void *heap, u32 sz)
{
    Blk *p;
    Hdr *h;

    for (p = ((Blk *)DListGetHead_42ea60(heap)); p != NULL; p = ((Blk *)DListGetNext_42eb30(p))) {
        h = &p->h;
        if (!(h->flags & 2) && h->size >= sz) {
            return p;
        }
    }
    return NULL;
}

s32 UskMemoryAlloc_42dae0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 f;
    s32 r;

    if (arg3 != 0) {
        if (arg2 == 0) {
            r = 0;
        } else {
            f = *(s32 *)(arg0 + 0x40);
            if (f & 2) {
                r = 0;
            } else if (f & 1) {
                r = 0;
            } else {
                *(s32 *)(arg0 + 0x40) = f | 1;
                r = ((s32)HeapBlockAllocAtEnd_42dc90(arg0, findA(arg0, (arg1 + 0xF) & ~0xF), arg1, arg2));
                *(s32 *)(arg0 + 0x40) &= ~1;
            }
        }
        return r;
    }
    if (arg2 == 0) {
        return 0;
    }
    f = *(s32 *)(arg0 + 0x40);
    if (f & 2) {
        return 0;
    }
    if (f & 1) {
        return 0;
    }
    *(s32 *)(arg0 + 0x40) = f | 1;
    r = ((s32)HeapBlockAllocAtStart_42ddf0(arg0, findB(arg0, (arg1 + 0xF) & ~0xF), arg1, arg2));
    *(s32 *)(arg0 + 0x40) &= ~1;
    return r;
}
