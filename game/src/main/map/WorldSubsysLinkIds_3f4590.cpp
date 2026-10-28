/* rgp:protos */
#line 1
#include "types.h"

struct Iter {
    u8 pad00[8];
};

class VT {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 id) { return VCM(s32, (void *, s16), 0x70, id); }
};

struct Holder {
    u8 pad00[0x8];
    VT *obj;
};

struct Owner {
    u8 pad00[0x44];
    Holder *h;
};

struct Node {
    s32 pad;
    union {
        s16 id;
        s32 ptr;
    } u;
};

extern "C" void IterInit_370170(Iter *, void *, int, int);
extern "C" void *IterNext_370040(Iter *it);

extern "C" s32 WorldSubsysLinkIds_3f4590(u8 *a0, Owner *a1, int rgp_a2, int rgp_a3)
{
    Iter it1 __attribute__((aligned(16)));
    Iter it2 __attribute__((aligned(16)));
    u8 *e;
    u8 *t1;
    u8 *t2;
    Node *n;
    VT *t;

    if (a1 == 0) {
        return 0;
    }
    if (*(s32 *)(a0+0x8C)==0) return 0;
    t1 = a0;
    if (a0 != 0) {
        t1 = t1 + 0x88;
    }
    IterInit_370170(&it1, t1, (int)rgp_a2, (int)rgp_a3);
    while (t2 = (u8 *)IterNext_370040(&it1), t2 != 0) {
        if (t2 != 0) {
            t2 = t2 + 0x4;
        }
        IterInit_370170(&it2, t2, 0, 0);
        while ((n = (Node *)IterNext_370040(&it2)) != 0) {
            t = a1->h->obj;
            n->u.ptr = t->v26(n->u.id);
        }
    }
    return 1;
}
