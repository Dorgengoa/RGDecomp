#include "types.h"

struct Iter {
    u8 pad00[8];
};

class VT {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s32 v26(s16 id);
};

struct Holder {
    u8 pad00[0x8];
    VT *obj;
};

struct Owner {
    u8 pad00[0x70];
    Holder *h;
};

struct Node {
    union {
        s16 id;
        s32 ptr;
    } u;
};

extern "C" void IterInit_370170(Iter *it, void *p);
extern "C" void *IterNext_370040(Iter *it);

extern "C" s32 WorldSubsysLinkIds_4039f0(u8 *a0, Owner *a1)
{
    Iter it1;
    Iter it2;
    u8 *e;
    u8 *t1;
    u8 *t2;
    Node *n;
    VT *t;

    if (a1 == 0) {
        return 0;
    }
    t1 = a0;
    if (a0 != 0) {
        t1 = t1 + 0x88;
    }
    IterInit_370170(&it1, t1);
    while (t2 = (u8 *)IterNext_370040(&it1), t2 != 0) {
        if (t2 != 0) {
            t2 = t2 + 0xC;
        }
        IterInit_370170(&it2, t2);
        while ((n = (Node *)IterNext_370040(&it2)) != 0) {
            t = a1->h->obj;
            n->u.ptr = t->v26(n->u.id);
        }
    }
    return 1;
}
