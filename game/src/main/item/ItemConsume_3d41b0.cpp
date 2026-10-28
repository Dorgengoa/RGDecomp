/* rgp:protos */
#line 1
#include "types.h"

class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 cnt(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x50, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    void f(s32 x0) { VCM(void, (void *, s32), 0x5C, x0); }
};

extern "C" {
extern void ItemMarkRemoved_3d4130(VC_1 *arg0, s32 arg1);
extern s32 ItemHasCountFlag_3d44e0(VC_1 *arg0);
}

extern "C" s32 ItemConsume_3d41b0(VC_1 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    if (arg1 <= 0) {
        return 0;
    }
    if (arg0->cnt((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) < arg1) {
        return 0;
    }
    if (ItemHasCountFlag_3d44e0(arg0) == 0) {
        ItemMarkRemoved_3d4130(arg0, 1);
    } else {
        arg0->f(-arg1);
        if (arg0->cnt() == 0) {
            ItemMarkRemoved_3d4130(arg0, 1);
        }
    }
    return 1;
}
