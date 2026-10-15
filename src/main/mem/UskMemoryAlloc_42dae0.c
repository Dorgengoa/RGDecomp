#include "types.h"

typedef struct Hdr {
    u32 size;
    s32 flags;
} Hdr;

typedef struct Blk {
    u8 pad0[0x10];
    Hdr h;
} Blk;


extern s32 HeapBlockAllocAtEnd_42dc90(void *, Blk *, s32, s32);
extern s32 HeapBlockAllocAtStart_42ddf0(void *, Blk *, s32, s32);
extern Blk *DListGetTail_42ea50(void);
extern Blk *DListGetHead_42ea60(void);
extern Blk *DListGetNext_42eb30(Blk *);
extern Blk *DListGetPrev_42eb40(Blk *);

static inline Blk *findA(u32 sz)
{
    Blk *p;
    Hdr *h;

    for (p = DListGetTail_42ea50(); p != NULL; p = DListGetPrev_42eb40(p)) {
        h = &p->h;
        if (!(h->flags & 2) && h->size >= sz) {
            return p;
        }
    }
    return NULL;
}

static inline Blk *findB(u32 sz)
{
    Blk *p;
    Hdr *h;

    for (p = DListGetHead_42ea60(); p != NULL; p = DListGetNext_42eb30(p)) {
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
                r = HeapBlockAllocAtEnd_42dc90(arg0, findA((arg1 + 0xF) & ~0xF), arg1, arg2);
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
    r = HeapBlockAllocAtStart_42ddf0(arg0, findB((arg1 + 0xF) & ~0xF), arg1, arg2);
    *(s32 *)(arg0 + 0x40) &= ~1;
    return r;
}
