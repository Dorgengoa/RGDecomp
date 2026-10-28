/* rgp:protos */
#line 1
#include "types.h"

struct Iter {
    u8 pad00[8];
};

class VT {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

struct Holder {
    u8 pad00[0xC];
    VT *obj;
};

struct Owner {
    u8 pad00[0x64];
    Holder *h;
};

struct Node {
    union {
        s16 id;
        s32 ptr;
    } u;
};

extern "C" void IterInit_370170(Iter *, void *, int, int);
extern "C" void *IterNext_370040(Iter *it);

extern "C" s32 WorldSubsysLinkParents_415ea0(u8 *a0, Owner *a1, int rgp_a2, int rgp_a3)
{
    Iter it1 __attribute__((aligned(16)));
    Iter it2 __attribute__((aligned(16)));
    u8 *e;
 u8 *parent;
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
    IterInit_370170(&it1, t1, (int)rgp_a2, (int)rgp_a3);
    while (parent = (u8 *)IterNext_370040(&it1), parent != 0) {
        t2=parent;
        if (t2 != 0) {
            t2 = t2 + 0x4;
        }
        IterInit_370170(&it2, t2, 0, 0);
        while ((n = (Node *)IterNext_370040(&it2)) != 0) {
            *(u8 **)((u8 *)n+0x10)=parent;
        }
    }
    return 1;
}
