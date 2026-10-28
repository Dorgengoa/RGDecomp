#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 get374(s32 a0) { return VCM(s32, (void *, s32), 0x374, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 get3BC() { return VCM0(s32, 0x3BC); }
    
    
    
    
    s32 get3D0() { return VCM0(s32, 0x3D0); }
};

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
} Sub;

typedef struct {
    u8 pad0[0x14];
    Sub *unk14;
} Mgr;

typedef struct {
    u8 pad0[0x4];
    s16 unk4;
    u8 pad6[0x10 - 0x6];
    s8 *unk10;
} Arg;

extern "C" {
extern Obj *PoolGetUsedElem_36acb0(s32, s32);
extern Mgr *D_004838E8;
}

extern "C" Obj *PartyFindItemHolder_3d4c20(Arg *arg0)
{
    Obj *res;
    s32 i;
    s32 k;
    Obj *o;
    s32 v;

    if (D_004838E8 == 0) {
        return 0;
    }
    res = 0;
    k = arg0->unk10[2];
    for (i = 0; i < 10; i++) {
        o = PoolGetUsedElem_36acb0(D_004838E8->unk14->unk8, i);
        if (o == 0) {
            continue;
        }
        v = -1;
        switch (k) {
        case 0:
            v = o->get374(0);
            break;
        case 1:
            v = o->get374(1);
            break;
        case 2:
            v = o->get3BC();
            break;
        case 3:
            v = o->get3D0();
            break;
        }
        if (v == arg0->unk4) {
            res = o;
            break;
        }
    }
    return res;
}
