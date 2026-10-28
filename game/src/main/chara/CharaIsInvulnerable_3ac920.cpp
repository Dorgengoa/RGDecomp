/* rgp:protos */
#line 1
#include "types.h"

class Obj003AC920 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 UnitBaseIsInvulnerableFalse_3b66e0(void);

extern "C" s32 CharaIsInvulnerable_3ac920(Obj003AC920 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (arg0->v46((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0) {
        return 0;
    }
    return UnitBaseIsInvulnerableFalse_3b66e0();
}
