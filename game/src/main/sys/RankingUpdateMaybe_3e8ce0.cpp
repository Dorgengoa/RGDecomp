/* rgp:protos */
#line 1
#include "types.h"

struct Rec {
    s16 x0;
    u8 pad2[0xE];
    s32 *arr;
};

struct Entry {
    Rec *p;
    s32 x4;
    s32 x8;
    s16 xC;
    s16 xE;
    s16 x10;
    s16 x12;
};

struct Owner {
    u8 pad0[0x10];
    s32 count;
    Entry *list;
};

struct Base88 {
    s32 x0;
};

struct Holder {
    u8 pad0[0x88];
    Base88 b;
};

struct B94 {
    u8 pad0[0x10];
    Holder *h;
    Owner *owner;
};

struct A8 {
    u8 pad0[0x94];
    B94 *b;
};

struct G18 {
    u8 pad0[0x180];
    s32 x180;
    u8 pad184[0x4C8C - 0x184];
    s32 x4C8C;
    u8 pad4C90[0x4C98 - 0x4C90];
    s32 x4C98;
};

struct Self {
    u8 pad0[8];
    A8 *a;
    u8 padC[4];
    s32 x10;
    u8 pad14[4];
    G18 *g;
};

struct Iter {
    s32 x0;
    s32 x4;
};

extern "C" {
s32 IterNext_370040(Iter *);
void IterInit_370170(Iter *, Base88 *, int, int);
void StateVarSet_3cc9c0(s32, s32, s16, s32);
void StateFlagSet_3ccb70(s32, s32, bool, s32);
s32 StateGetChapter_3cd5b0(s32);
void RankingEntryInit_3fdad0(Entry *);
void *memcpy(void *, const void *, u32);
}

static inline void sortBy8(Owner *o, Entry *tmp) {
    bool lt;
    bool swapped;
    Entry *a;
    s32 j;
    Entry *b;
    do {
        a = o->list;
        swapped = false;
        for (j = 1; j < o->count; j++) {
            b = &o->list[j];
            lt = false;
            if (a->x8 < b->x8) {
                lt = true;
            }
            if (lt) {
                swapped = true;
                RankingEntryInit_3fdad0(tmp);
                memcpy(tmp, b, 0x14);
                memcpy(b, a, 0x14);
                memcpy(a, tmp, 0x14);
            } else {
                a = b;
            }
        }
    } while (swapped);
}

static inline void sortBy4(Owner *o, Entry *tmp) {
    bool lt;
    bool swapped;
    Entry *a;
    s32 j;
    Entry *b;
    do {
        a = o->list;
        swapped = false;
        for (j = 1; j < o->count; j++) {
            b = &o->list[j];
            lt = false;
            if (a->x4 < b->x4) {
                lt = true;
            }
            if (lt) {
                swapped = true;
                RankingEntryInit_3fdad0(tmp);
                memcpy(tmp, b, 0x14);
                memcpy(b, a, 0x14);
                memcpy(a, tmp, 0x14);
            } else {
                a = b;
            }
        }
    } while (swapped);
}

extern "C" s32 RankingUpdateMaybe_3e8ce0(Self *self) {
    Entry *b2;
    Iter it __attribute__((aligned(16)));
    Entry tmp1 __attribute__((aligned(16)));
    Entry tmp2 __attribute__((aligned(16)));
    Owner *o;
    s32 cur;
    s32 prev;
    Entry *e;
    s32 i;
    Rec *p;
    bool swapped;
    Entry *f2;
    Entry *a;
    Entry *b;
    s32 k;
    bool lt;
    Entry *a2;
    s32 j;
    bool sw2;
    bool lt2;
    Entry *f4;
    Entry *f3;
    s32 k4;
    s32 k3;
    s32 n;
    bool f;




    if (self->a == 0) {
        return 0;
    }
    o = self->a->b->owner;
    if (o == 0) {
        return 0;
    }
    if (o->list == 0 || o->count <= 0) {
        return 0;
    }
    cur = ((short)StateGetChapter_3cd5b0(self->x10)) - 1;
    if (cur > 0) {
        prev = cur - 1;
    } else {
        prev = 0;
    }
    for (i = 0, e = o->list; i < o->count; i++, e++) {
        p = e->p;
        if (p != 0) {
            if (p->x0 == 0) {
                e->x4 = self->g->x180;
                e->x8 = self->g->x4C8C;
            } else {
                e->x4 = p->arr[cur];
                e->x8 = p->arr[prev];
            }
        }
    }
    sortBy8(o, &tmp1);
    for (k = 0, f2 = o->list; k < o->count; f2++) {
        f2->xE = ++k;
    }
    sortBy4(o, &tmp2);
    for (k3 = 0, f3 = o->list; k3 < o->count; f3++) {
        f3->xC = ++k3;
    }
    for (k4 = 0, f4 = o->list; k4 < o->count; k4++, f4++) {
        f4->x10 = f4->xE - f4->xC;
    }
    {
        s32 lvl = self->g->x4C98;
        u8 *h = (u8 *)self->a->b->h;
        if (h != 0) {
            h += 0x88;
        }
        IterInit_370170(&it, (Base88 *)h, 0, 0);
        while (IterNext_370040(&it) != 0) {
        }
        n = 0x65 - lvl;
    }
    f = false;
    if (n < 2) {
        n = 0;
    } else if (n >= 0x64) {
        f = true;
        n = 0x64;
    }
    StateFlagSet_3ccb70(self->x10, 0x1E0, f, 0);
    StateVarSet_3cc9c0(self->x10, 0x64, n, 0);
    return 0;
}
