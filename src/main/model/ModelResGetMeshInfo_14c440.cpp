#include "types.h"
#pragma divbyzerocheck on

typedef struct Elem {
    struct Elem *next;
    u16 type;
    u16 cnt;
    u8 mul;
} Elem;

typedef struct Node {
    u8 pad0[0x70];
    s32 count;
    Elem *elems;
    u8 pad78[8];
    struct Node *next;
} Node;

typedef struct {
    u8 pad0[0x20];
    s32 num;
    Node *first;
    u8 pad28[4];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
} Hdr;

struct Info {
    Node *f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
    s32 f6;
    s32 f7;
    Info() {}
    Info(const Info &o)
    {
        f0 = o.f0;
        f1 = o.f1;
        f2 = o.f2;
        f3 = o.f3;
        f4 = o.f4;
        f5 = o.f5;
        f6 = o.f6;
        f7 = o.f7;
    }
};

static inline s32 getNum(Hdr *h)
{
    return (h != 0) ? h->num : 0;
}

static inline s32 get2C(Hdr *h)
{
    return (h == 0) ? 0 : h->unk2C;
}

extern "C" Info ModelResGetMeshInfo_14c440(Hdr **arg1, s32 idx)
{
    Info r;
    Node *n;
    Hdr *h;
    Hdr *p;
    Elem *e;
    s32 i;
    s32 total;
    s32 s4;
    s32 s3;
    s32 v;

    p = *arg1;
    if (p == 0) {
        r.f0 = 0;
        r.f1 = 0;
        r.f3 = 0;
        r.f4 = 0;
        r.f5 = 0;
        r.f6 = 0;
        r.f7 = 0;
        return r;
    }
    if (idx < 0 || idx >= getNum(p)) {
        r.f0 = 0;
        r.f1 = 0;
        r.f3 = 0;
        r.f4 = 0;
        r.f5 = 0;
        r.f6 = 0;
        r.f7 = 0;
        return r;
    }
    n = p->first;
    for (i = 0; n != 0; i++) {
        if (i == idx) {
            break;
        }
        n = n->next;
    }
    r.f0 = n;
    h = *(Hdr * volatile *)arg1;
    r.f2 = h->unk30;
    r.f1 = h ? p->unk2C : 0;
    r.f3 = p->unk34;
    r.f4 = n->count;
    total = 0;
    s4 = 0;
    s3 = 0;
    e = n->elems;
    for (i = 0; i < r.f4; i++) {
        v = e->cnt * e->mul;
        switch (e->type) {
        case 3:
            s3 += v / 3;
            break;
        case 4:
            s4 += (v - 2) / 2;
            break;
        }
        e = e->next;
        total += v;
    }
    r.f5 = total;
    r.f6 = s3;
    r.f7 = s4;
    return r;
}
