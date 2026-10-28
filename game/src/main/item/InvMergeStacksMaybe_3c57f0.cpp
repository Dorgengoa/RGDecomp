#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f50() { return VCM0(s32, 0x50); }
    s16 m4;
    s16 m6;
    u8 pad8[8];
    s16 *m10;
};

struct Ctx {
    u8 pad[0x168];
    s32 m168;
};

extern "C" {
s32 InvMoveItemMaybe_3c5b10(Ctx *, Obj *, s32, s32, s32, s32, s32, s32);
Obj *InvFindByInvId_3c87d0(Ctx *, s32, s32);
s32 ItemGetStackLimit_3d4480(Obj *);
s32 ItemHasCountFlag_3d44e0(Obj *);
s32 InvGetCategoryOfId_3d56f0(s32);
extern s32 D_00465A08[4];
extern s32 D_00465A10[4];
extern s32 D_00465A38[4];
extern s32 D_00465A40[4];
}

extern "C" bool InvMergeStacksMaybe_3c57f0(Ctx *arg0, Obj *arg1, s32 arg2)
{
    s32 lo;
    s32 n;
    Obj *o;
    s32 r;
    s32 hi;
    bool found;
    s32 kind;
    s32 key;
    s32 id;

    if (arg1 == NULL) {
        return 0;
    }
    if (ItemHasCountFlag_3d44e0(arg1) == 0) {
        return 0;
    }
    n = arg1->f50();
    if (n >= ItemGetStackLimit_3d4480(arg1)) {
        return 0;
    }
    if (arg0->m168 == 0) {
        return 0;
    }
    kind = InvGetCategoryOfId_3d56f0(arg1->m6);
    lo = -1;
    hi = lo;
    switch (kind) {
    case 0:
        lo = D_00465A08[0];
        hi = D_00465A10[0];
        break;
    case 1:
        lo = D_00465A38[0];
        hi = D_00465A40[0];
        break;
    }
    if (lo < 0 || hi < 0) {
        return 0;
    }
    key = *arg1->m10;
    id = arg1->m6;
    found = 0;
    for (; lo <= hi; lo++) {
        if (lo == id) {
            continue;
        }
        o = InvFindByInvId_3c87d0(arg0, lo, 0);
        if (o == NULL) {
            continue;
        }
        if (key != *o->m10) {
            continue;
        }
        r = InvMoveItemMaybe_3c5b10(arg0, o, id, -1, 0, 0, 0, arg2);
        if (r != 0) {
            found = 1;
            if (arg2 != 0) {
                break;
            }
        }
        if (r == 0 || r == 5) {
            break;
        }
    }
    return found;
}
