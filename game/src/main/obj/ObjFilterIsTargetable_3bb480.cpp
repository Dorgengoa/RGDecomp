/* rgp:protos */
#line 1
#include "types.h"

class C3BB480 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vcall(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x22C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 ObjFilterIsTargetable_3bb480(C3BB480 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (p == 0) {
        return 0;
    }
    return p->vcall((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
}
