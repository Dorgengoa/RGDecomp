/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 x3 (jalr-is-cpp-virtual lever): this=arg0 directly (K=0).
   Slots 0xC0/0x2A8/0x32C -> N=46/160/205. */

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v168() { return VCM0(s32, 0x2A8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v201(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x32C, a0, a1, a2); }
    
    
    
    
};

extern "C" s32 CharaKillDelayedMaybe_3b1be0(VE *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg0->v46((int)(long)(arg1), (int)(long)(arg2), (int)(long)(arg3)) != 0) {
        return 0;
    }
    if (arg0->v168() != 0) {
        return 0;
    }
    arg0->v201(arg1, arg2, arg3);
    return 1;
}
