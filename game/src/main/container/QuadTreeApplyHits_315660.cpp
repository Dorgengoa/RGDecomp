#include "types.h"

class Obj {
public:
    u8 pad[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    s32 test(s32 a0) { return VCM(s32, (void *, s32), 0x24, a0); }
    void hit(s32 a0) { VCM(void, (void *, s32), 0x28, a0); }
};

struct Node {
    Obj **h;
    s32 id;
    Node *next;
};

struct Arg1 {
    Obj **h;
    s32 id;
};

struct Box {
    f32 x;
    f32 pad4;
    f32 z;
    f32 padC;
    f32 size;
    Box *child[4];
    Node *list;
};

struct Rect {
    f32 x0;
    f32 pad4;
    f32 z0;
    f32 padC;
    f32 x1;
    f32 pad14;
    f32 z1;
};

extern "C" s32 HitShapeListPairTest_3153d0(s32, s32);

static inline bool valid(Obj **p)
{
    return p != 0;
}

static inline Obj *get(Obj **p)
{
    return p != 0 ? *p : 0;
}

extern "C" void QuadTreeApplyHits_315660(s32 arg0, Arg1 *arg1, Rect *arg2, Box *arg3)
{
    f32 x;
    f32 z;
    f32 h;
    Node *n;
    s32 a;
    s32 b;
    s32 i;
    s32 nb;

    if (arg3 == 0) {
        return;
    }
    h = 0.5f * arg3->size;
    x = arg3->x;
    if (arg2->x0 < x - h) {
        return;
    }
    z = arg3->z;
    if (arg2->z0 < z - h) {
        return;
    }
    if (!(arg2->x1 <= x + h)) {
        return;
    }
    if (!(arg2->z1 <= z + h)) {
        return;
    }
    for (n = arg3->list; n != 0; n = n->next) {
        a = arg1->id;
        b = n->id;
        if (HitShapeListPairTest_3153d0(a, b) != 0) {
            nb = valid(arg1->h) ^ 1;
            if (!nb) {
                if (get(arg1->h)->test(b) != 0) {
                    nb = valid(n->h) ^ 1;
                    if (!nb) {
                        get(n->h)->hit(a);
                    }
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (arg3->child[i] != 0) {
            QuadTreeApplyHits_315660(arg0, arg1, arg2, arg3->child[i]);
        }
    }
}
