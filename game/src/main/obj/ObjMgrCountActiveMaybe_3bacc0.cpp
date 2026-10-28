#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5C() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v234() { return VCM0(s32, 0x234); }
    
    s32 v23C() { return VCM0(s32, 0x23C); }
    
    
    
    s32 v24C() { return VCM0(s32, 0x24C); }
    
    s32 v254() { return VCM0(s32, 0x254); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v434() { return VCM0(s32, 0x434); }
};

extern "C" Obj *PoolGetUsedElem_36acb0(void *, s32);

struct Own { u8 pad[0x10]; void *p10; };
extern "C" s32 ObjMgrCountActiveMaybe_3bacc0(Own *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 count;
    s32 n;
    s32 i;
    Obj *o;

    if (arg0->p10 == NULL) {
        return 0;
    }
    n = *(s32 *)((u8 *)arg0->p10 + 0x14);
    count = 0;
    for (i = 0; i < n; i++) {
        o = PoolGetUsedElem_36acb0(arg0->p10, i);
        if (o != NULL) {
            if (o->v434() == 0 &&
                o->vC0() == 0 &&
                o->v234() != 0 &&
                o->v23C() == 0 &&
                (o->v254() == 0 || arg2 != 0) &&
                (o->v24C() == 0 || arg3 != 0) &&
                (arg1 < 0 || arg1 == o->v5C())) {
                count++;
            }
        }
    }
    return count;
}
