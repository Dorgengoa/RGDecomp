/* rgp:protos */
#line 1
#include "types.h"

extern "C" {

class C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f94(s32 a0) { return VCM(s32, (void *, s32), 0x94, a0); }
    s32 f98(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x98, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
static inline bool lt5(s32 i)
{
    return i < 5;
}
static inline bool valid(s32 i)
{
    return i >= 0 && i < 5;
}

#pragma opt_propagation off
void ItemWeaponSetAttr_3d32e0(C *arg0, s32 arg1, s32 arg2, int rgp_a3) {
    s32 v;
    s32 lo;
    s32 hi;
    u8 *q;

    if (arg1 < 0 || arg1 >= 5) {
        return;
    }
    {
    s32 w = arg2;
    lo = arg0->f98((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3));
    v = w;
    }
    hi = arg0->f94(arg1);
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    *(u8 *)(arg1 + (s32)arg0 + 0x17) = v;
}

}
