#pragma opt_loop_invariants off
#include "types.h"
typedef rg_u128 u128;

typedef struct Named {
    const char *name;
} Named;

typedef struct NameTbl {
    s32 count;
    Named **items;
} NameTbl;

typedef struct M64 {
    u128 q[4];
} M64;

typedef struct Ctx {
    void *x0;
    u8 pad4[0x100];
    NameTbl *x104;
    struct M64 *x108;
} Ctx;

typedef struct Elem {
    const char *name;
    u8 pad4[0x1C];
    u8 x20[0x40];
    M64 x60;
} Elem;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    s32 x10;
    s32 x14;
} Node;

typedef struct OList {
    s32 count;
    struct Thing **items;
} OList;

struct Pad50 { u8 pad[0x50]; };
struct Thing : public Pad50 {
    VC_VPTR_MEMBER;
    s32 v1(s32 a0) { return VCM(s32, (void *, s32), 0xC, a0); }
};

typedef struct Holder {
    u8 pad[0x128];
    s32 count;
    s32 *ids;
} Holder;

typedef struct Arg {
    s32 x0;
    u8 pad4[8];
    OList *xC;
    u8 pad10[0x34];
    Node *x44;
} Arg;

extern "C" {
void ModelFrameSetMatrix_14a190(void *, void *);
Elem *ArrayGetChecked_14c7f0(void *, s32);
s32 ModelResGetFrameCount_14c850(void *);
void *ArrayGetChecked_152fd0(void *, s32);
}

static inline s32 find(NameTbl *t, const char *name)
{
    s32 i;
    s32 n;
    if (name == 0 || t == 0) {
        return -1;
    }
    n = t->count;
    for (i = 0; i < n; i++) {
        Named *e = t->items[i];
        const char *s;
        const char *q;
        bool eq;
        if (e == 0) {
            continue;
        }
        s = e->name;
        if (s == 0) {
            continue;
        }
        q = name;
if (*s != *q) {
            eq = false;
        } else {
            char c;
            while ((c = *s) != 0 || *q != 0) {
                if (c != *q) {
                    eq = false;
                    goto ne;
                }
                s++;
                q++;
            }
            eq = true;
        }
    ne:
        if (eq) {
            return i;
        }
    }
    return -1;
}

static inline void *lookup(Ctx *c, s32 idx)
{
    return c->x0 ? ArrayGetChecked_152fd0(c->x104, idx) : 0;
}

extern "C" s32 ModelBindFramesByName_150ad0(Ctx *c, Arg *a, void *list)
{
    s32 *ids;
    s32 k;
    s32 m;
    M64 *arr;
    s32 i;
    Elem *e;
    s32 *slot;
    s32 idx;
    s32 ok;
    void *r;
    s32 n;
    s32 cnt;
    s32 *p;
    s32 cnt2;
    Holder *h;
    Thing *t;
    s32 j;
    Node *node;

    if (a == 0 || list == 0) {
        return 0;
    }
    if (a->x0 == 0) {
        return 0;
    }
    ok = 1;
    n = ModelResGetFrameCount_14c850(list);
    for (i = 0; i < n; i++) {
        e = ArrayGetChecked_14c7f0(list, i);
        if (e == 0) {
            continue;
        }
        { const char *nm_ = e->name; idx = find(c->x104, nm_); }
        r = lookup(c, idx);
        if (r == 0) {
            continue;
        }
        ModelFrameSetMatrix_14a190(r, e->x20);
        if (c->x104 == 0) {
            continue;
        }
        arr = c->x108;
        if (arr == 0) {
            continue;
        }
        cnt = c->x104->count;
        if (idx < 0 || idx >= cnt) {
            continue;
        }
        {
            u128 *d = arr[idx].q;
            d[0] = e->x60.q[0];
            d[1] = e->x60.q[1];
            d[2] = e->x60.q[2];
            d[3] = e->x60.q[3];
        }
    }
    for (node = a->x44; node != 0; node = node->next) {
        slot = &node->x10;
        e = ArrayGetChecked_14c7f0(list, node->x14);
        if (e == 0) {
            ok = 0;
            break;
        }
        { const char *nm_ = e->name; idx = find(c->x104, nm_); }
        if (idx < 0) {
            ok = 0;
            break;
        }
        slot[1] = idx;
    }
    {
        cnt2 = a->xC->count;
        for (k = 0; k < cnt2; k++) {
            t = a->xC->items[k];
            if (t == 0) {
                continue;
            }
            h = 0;
            if (t->v1(2)) {
                h = (Holder *)t;
            }
            if (h == 0) {
                return 0;
            }
            {
                m = h->count;
                ids = h->ids;
                if (ids == 0) {
                    continue;
                }
                for (j = 0; j < m; j++) {
                    p = &ids[j];
                    if (*p < 0) {
                        continue;
                    }
                    e = ArrayGetChecked_14c7f0(list, *p);
                    if (e == 0) {
                        ok = 0;
                        break;
                    }
                    { const char *nm_ = e->name; idx = find(c->x104, nm_); }
                    if (idx < 0) {
                        ok = 0;
                        break;
                    }
                    *p = idx;
                }
            }
        }
    }
    if (!ok) {
        a->x0 = 0;
    }
    return ok;
}
