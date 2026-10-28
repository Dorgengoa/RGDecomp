/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

struct Hdr {
    u32 size;
    u32 flags;
    struct Owner *owner;
    u32 pad;
    void Clear() {
        flags = 0;
        size = 0;
        owner = 0;
    }
};

struct Owner {
    s32 m0;
    u8 *data;
    u32 size;
};

extern "C" {
void DListNodeInit_42ec10(void *);
void DListNodeDetach_42eb50(void *);
}

struct Block {
    u8 pad[0x10];
    Hdr h;
};

static inline Block *FromData(u8 *p) {
    Block tmp __attribute__((aligned(16)));
    Block *t = &tmp;
    Block *r;
    DListNodeInit_42ec10(t);
    DListNodeInit_42ec10(t);
    t->h.Clear();
    r = (Block *)(p - ((u8 *)(&tmp + 1) - (u8 *)&tmp));
    DListNodeDetach_42eb50(t);
    tmp.h.Clear();
    DListNodeDetach_42eb50(t);
    return r;
}

static inline Block *FromDataX(u8 *p0) {
    Block *r;
    Block *t;
    Block tmp __attribute__((aligned(16)));
    u8 *p;
    p = p0;
    t = &tmp;
    DListNodeInit_42ec10(t);
    DListNodeInit_42ec10(t);
    t->h.Clear();
    r = (Block *)(p - ((u8 *)(&tmp + 1) - (u8 *)&tmp));
    DListNodeDetach_42eb50(t);
    tmp.h.Clear();
    DListNodeDetach_42eb50(t);
    return r;
}
static inline Block *FromDataY(u8 *p0) {
    Block tmp __attribute__((aligned(16)));
    Block *t;
    Block *r;
    u8 *p;
    t = &tmp;
    DListNodeInit_42ec10(t);
    DListNodeInit_42ec10(t);
    t->h.Clear();
    p = p0;
    r = (Block *)(p - ((u8 *)(&tmp + 1) - (u8 *)&tmp));
    DListNodeDetach_42eb50(t);
    tmp.h.Clear();
    DListNodeDetach_42eb50(t);
    return r;
}
static inline Owner *own(Hdr *h) { return h->owner; }
static inline bool valid(void *p) { return p != 0; }

extern "C" {
Block *DListGetTail_42ea50(void *);
Block *DListGetPrev_42eb40(Block *);
Block *DListGetHead_42ea60(void *);
Block *DListGetNext_42eb30(Block *);
Block * HeapBlockFreeCoalesce_42d9c0(void *, Block *, s32, int);
u8 *HeapBlockAllocAtEnd_42dc90(void *, Block *, u32, Owner *);
s32 UskMemoryCompactToEndMaybe_42d040(void *self, volatile u8 flag);
}

s32 UskMemoryCompactToEndMaybe_42d040(void *self, volatile u8 flag)
{
    Block *b;
    s32 count;
    Block *cur;
    Block *next;
    Owner *best;
    Block *bestNode;
    Block *s;
    Hdr *h;
    u32 bestSize;


    count = 0;
    next = DListGetTail_42ea50(self);
    while ((cur = next) != 0) {
        next = DListGetPrev_42eb40(next);
        if (next == 0) {
            break;
        }
        h = &cur->h;
        if (cur->h.flags & 2) {
            continue;
        }
        bestNode = 0;
        best = 0;
        b = DListGetHead_42ea60(self);
        bestSize = 0;
        for (; !(valid(s = b) ^ 1) && b < next; ) {
            b = DListGetNext_42eb30(b);
            Hdr *sh = &s->h;
            if ((s->h.flags & 2) && (s->h.flags & 1)) {
                Owner *o = sh->owner;
                if (o != 0 && o->size <= h->size && bestSize < o->size) {
                    bestSize = o->size;
                    bestNode = s;
                    best = o;
                }
            }
        }
        if (bestNode == 0) {
            if (flag == 0) {
                continue;
            }
            {
            Hdr *nh = &next->h;
            if (!(next->h.flags & 2) || !(next->h.flags & 1)) {
                continue;
            }
            best = nh->owner;
            }
            if (best == 0) {
                continue;
            }
            cur = HeapBlockFreeCoalesce_42d9c0(self, FromData(best->data), 0, 0);
        } else {
            HeapBlockFreeCoalesce_42d9c0(self, FromDataY(best->data), 0, 0);
        }
        next = DListGetPrev_42eb40(FromDataX(HeapBlockAllocAtEnd_42dc90(self, cur, best->size, best)));
        count++;
    }
    return count;
}
